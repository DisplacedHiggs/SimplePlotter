#include "TStyle.h"
#include "TROOT.h"
#include "TPad.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TFileCollection.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TF1.h"
#include "TProfile.h"

#include "tdrstyle.C"

#include <iostream>
#include <fstream>

using namespace std;




void load_trees(){

  TString path = "root://cmsxrootd.fnal.gov//store/group/lpchbb/noreplica/stata/AnalysisTrees/addedHistos/";
  
  std::vector<TString> files_TT;
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_0.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_1.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_10.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_11.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_12.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_13.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_14.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_15.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_16.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_17.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_18.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_19.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_2.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_20.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_21.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_3.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_4.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_5.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_6.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_7.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_8.root");
  files_TT.push_back(path+"allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_9.root");
  

}




class sample {
 public:
  sample(TString);
  ~sample();

  TString tree_name = "treeR";

  TString name;
  TString humanName;

  TFile* file;
  TTree* tree;

  UInt_t color = kBlack;
  
  TH1D lastHisto;
};
sample::sample(TString temp){
  name = temp;
  file = TFile::Open(name);
  tree = (TTree*)file->Get("treeR");
}
sample::~sample(){
  file->Close();
}


class sample2 {
 public:
  sample2(std::vector<TString>);
  ~sample2();

  TString tree_name = "treeR";

  TString name;
  TString humanName;

  std::vector<TString> files;
  TChain* tree;

  UInt_t color = kBlack;
  
  TH1D lastHisto;
};
sample2::sample2(std::vector<TString> temp){
  
  files = temp;

  ofstream myfile;
  myfile.open ("files.txt");
  for(unsigned int i=0; i<files.size(); i++){
    myfile << files.at(i).Data();
    myfile << "\n";
  }
  myfile.close();
}
sample2::~sample2(){

}


void drawPlots(std::vector<sample*> sampleVector, const TString varname, const int nbins, const float low, const float high,
	       const TString xtitle, const TString ytitle, const TString cutstring = "1")
{
  std::cout << "Start drawing" << std::endl;
  gStyle->SetOptStat(0);

  bool log_y = false;

  //TStyle* theStyle = 0;
  //initStyle(theStyle);
  //gROOT->SetStyle("CMS");
  setTDRStyle();

  std::map<TString, TH1D> histos;

  std::cout << "size " << sampleVector.size() << std::endl;

  double plotMinimum_ = 0;
  if(log_y) plotMinimum_ = 1e-7;

  TCanvas thecanvas("c1", "c1", 640, 640);
  thecanvas.cd();
  
  float leg_x1=0.5, leg_y1=0.6, leg_x2=0.9, leg_y2=0.88;
  TLegend leg(leg_x1, leg_y1, leg_x2, leg_y2);
  leg.SetBorderSize(0);
  leg.SetLineStyle(0);
  leg.SetTextFont(42);
  leg.SetFillStyle(0);

  //Draw Histograms
  double max = 0;
  for(unsigned int isample=0; isample<sampleVector.size(); isample++) {

    //Create histogram
    TString hname = "h";
    hname+=isample;  
    histos[sampleVector.at(isample)->name] = TH1D(hname, hname, nbins, low, high);
    histos[sampleVector.at(isample)->name].Sumw2();

    cout << sampleVector.at(isample)->name << endl;
    cout << sampleVector.at(isample)->tree->GetName() << endl;

    //Project
    (sampleVector.at(isample)->tree)->Project(hname, varname, cutstring);

    //Temp
    for(int i=0; i<histos[sampleVector.at(isample)->name].GetNbinsX(); i++) cout << i << " " << histos[sampleVector.at(isample)->name].GetBinContent(i) << endl;

    //Normalize
    cout << "!! HISTOGRAM IS NORMALIZED !!" << endl;
    histos[sampleVector.at(isample)->name].Scale(1.0/histos[sampleVector.at(isample)->name].Integral());

    //Save to last Histo
    sampleVector.at(isample)->lastHisto = *(TH1D*)histos[sampleVector.at(isample)->name].Clone("last_"+hname);
    //sampleVector.at(isample)->lastHisto = histos[sampleVector.at(isample)->name].Clone("last_"+hname);
    //sampleVector.at(isample)->lastHisto->SetDirectory(0);

    //Get what you want from histogram
    if( histos[sampleVector.at(isample)->name].GetMaximum() > max ) max = histos[sampleVector.at(isample)->name].GetMaximum();
    
  }

  //Second loop to draw (knowing max)
  int ndrawn = 0;
  for(unsigned int isample=0; isample<sampleVector.size(); isample++) {
    
    //Style
    if(isample==0) histos[sampleVector.at(isample)->name].SetTitle("");
    histos[sampleVector.at(isample)->name].SetLineWidth(2);
    histos[sampleVector.at(isample)->name].SetLineColor(sampleVector.at(isample)->color);
    histos[sampleVector.at(isample)->name].SetMarkerColor(sampleVector.at(isample)->color);
    histos[sampleVector.at(isample)->name].SetXTitle(xtitle);
    histos[sampleVector.at(isample)->name].SetYTitle(ytitle);
    if(high-low < 1.0)  histos[sampleVector.at(isample)->name].SetNdivisions(506);

    //Add to legend
    leg.AddEntry(&histos[sampleVector.at(isample)->name], sampleVector.at(isample)->humanName, "L");


    //Draw histogram
    TString drawOptions = "HIST E";
    if(ndrawn>0) drawOptions += " SAME";
    if(ndrawn==0) histos[sampleVector.at(isample)->name].SetMaximum(1.1*max);
    if(ndrawn==0) histos[sampleVector.at(isample)->name].SetMinimum(plotMinimum_);
    histos[sampleVector.at(isample)->name].Draw(drawOptions);
    ndrawn++;
  }
  
  leg.Draw();

  if(log_y) thecanvas.SetLogy();
  TString log_string = "";
  if(log_y) log_string = "_log";

  thecanvas.SaveAs("h_"+varname+log_string+".pdf");

}//end of drawPlots


