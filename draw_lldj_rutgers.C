#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TString.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TPaveStats.h"

#include <iostream>

using namespace std;

struct plotInfo {
  TString var1;
  TString var2;
  int nbins;
  double min;
  double max;
};

void unit_norm(TH1D* h){
  h->Scale(1.0/h->Integral());
}

void project_version(){

  
  TFile* fin1 = TFile::Open("/uscms_data/d2/kreis/LLDJ/20170919/LLDJ_slc6_530_CMSSW_8_0_26_patch1/src/LLDJstandalones/ntuples/config/lldjntuple_mc.root");
  TTree* tree1 = (TTree*)fin1->Get("lldjNtuple/EventTree");

  TFile* fin2 = TFile::Open("");
  TTree* tree2 = (TTree*)fin2->Get("treeR");

  plotInfo alphamax;
  alphamax.var1 = "AODCaloJetAlphaMax";
  alphamax.var2 = "ALPHAMAX_BASICCALOJETS1PT20";
  alphamax.nbins = 20;
  alphamax.min = 0;
  alphamax.max = 1.01;

  std::vector<plotInfo> plotinfo_vec;
  plotinfo_vec.push_back(alphamax);

  for(unsigned int i=0; i<plotinfo_vec.size(); i++){
    
    TString hname = "h_"; 
    hname += plotinfo_vec[i].var1;

    TH1D h(hname,hname, plotinfo_vec[i].nbins, plotinfo_vec[i].min, plotinfo_vec[i].max);
    tree1->Project(hname, alphamax.var1);
    

    TCanvas c("c", "c", 640, 480);
    h.Draw("HIST E");
    c.SaveAs("c.pdf");
  }


}


void looping(){
  gStyle->SetOptStat(111111);

  ////////////////
  // LLDJ
  ///////////////
  TFile* fin1 = TFile::Open("/uscms_data/d2/kreis/LLDJ/20170919/LLDJ_slc6_530_CMSSW_8_0_26_patch1/src/LLDJstandalones/ntuples/config/lldjntuple_mc.root");
  TTree* tree1 = (TTree*)fin1->Get("lldjNtuple/EventTree");
  cout << tree1<< endl;

  vector<float>* AODCaloJetAlphaMax = 0;
  vector<float>* AODCaloJetPt = 0;
  vector<float>* jetAlphaMaxD = 0;
  vector<float>* jetPt = 0;
  tree1->SetBranchAddress("AODCaloJetAlphaMax", &AODCaloJetAlphaMax);
  tree1->SetBranchAddress("AODCaloJetPt", &AODCaloJetPt);
  tree1->SetBranchAddress("jetAlphaMaxD", &jetAlphaMaxD);
  tree1->SetBranchAddress("jetPt", &jetPt);

  TH1D* h_alphamax_aod = new TH1D("h_alphamax_aod", "h_alphamax_aod", 20, 0, 1.01);
  TH1D* h_alphamax_miniaod = new TH1D("h_alphamax_miniaod", "h_alphamax_miniaod", 20, 0, 1.01);
  h_alphamax_aod->Sumw2();
  h_alphamax_miniaod->Sumw2();

  int tree1_entries = tree1->GetEntries();
  for(int i=0; i<tree1_entries; i++){

    tree1->GetEntry(i);

    //aod jets
    for(unsigned int j=0; j<AODCaloJetPt->size(); j++){
      if(AODCaloJetPt->at(j) < 20) continue;
      h_alphamax_aod->Fill(AODCaloJetAlphaMax->at(j));
    }

    //mini
    for(unsigned int j=0; j<jetPt->size(); j++){
      if(jetPt->at(j) < 20) continue;
      h_alphamax_miniaod->Fill(jetAlphaMaxD->at(j));
    }
    
  }//event loop

  //////////////
  // RUTGERS
  //////////////
  TFile* fin2 = TFile::Open("root://cmsxrootd.fnal.gov//store/user/lpchbb/kreis/AnalysisTrees/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_TuneCUETP8M1_13TeV-powheg-pythia8/histo_ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_TuneCUETP8M1_13TeV-powheg-pythia8_161018_172901_1.root");
  TTree* tree2 = (TTree*)fin2->Get("treeR");

  vector<double> * ALPHAMAX_BASICCALOJETS1PT20         = 0;
  vector<double> * ALPHAMAX_ALLCALOJETS         = 0;
  vector<double> * PT_ALLCALOJETS         = 0;
  tree2->SetBranchAddress("ALPHAMAX_BASICCALOJETS1PT20", &ALPHAMAX_BASICCALOJETS1PT20);
  tree2->SetBranchAddress("ALPHAMAX_ALLCALOJETS", &ALPHAMAX_ALLCALOJETS);
  tree2->SetBranchAddress("PT_ALLCALOJETS", &PT_ALLCALOJETS);
  
  TH1D* h_alphamax_rutgers= new TH1D("h_alphamax_rutgers", "h_alphamax_rutgers", 20, 0, 1.01);
  TH1D* h_alphamax_all20_rutgers = new TH1D("h_alphamax_all20_rutgers", "h_alphamax_all20_rutgers", 20, 0, 1.01);
  h_alphamax_rutgers->Sumw2();
  h_alphamax_all20_rutgers->Sumw2();

  int tree2_entries = tree2->GetEntries();
  for(int i=0; i<tree2_entries; i++){

    tree2->GetEntry(i);
    
    for(unsigned int j=0; j<ALPHAMAX_BASICCALOJETS1PT20->size(); j++){
      h_alphamax_rutgers->Fill(ALPHAMAX_BASICCALOJETS1PT20->at(j));
    }
    for(unsigned int j=0; j<ALPHAMAX_ALLCALOJETS->size(); j++){
      if(PT_ALLCALOJETS->at(j)<20) continue;
      h_alphamax_all20_rutgers->Fill(ALPHAMAX_ALLCALOJETS->at(j));
    }
    
  }//event loop
  
  h_alphamax_aod->SetLineWidth(2);
  h_alphamax_aod->SetLineColor(kRed);
  h_alphamax_aod->SetMarkerStyle(1);

  h_alphamax_miniaod->SetLineWidth(2);
  h_alphamax_miniaod->SetLineColor(kBlue);
  h_alphamax_miniaod->SetMarkerStyle(1);

  h_alphamax_rutgers->SetLineWidth(2);
  h_alphamax_rutgers->SetLineColor(kGreen+1);
  h_alphamax_rutgers->SetMarkerStyle(1);

  h_alphamax_all20_rutgers->SetLineWidth(2);
  h_alphamax_all20_rutgers->SetLineColor(kViolet);
  h_alphamax_all20_rutgers->SetMarkerStyle(1);

  unit_norm(h_alphamax_aod);
  unit_norm(h_alphamax_miniaod);
  unit_norm(h_alphamax_rutgers);
  unit_norm(h_alphamax_all20_rutgers);
  
  TLegend leg(0.25, 0.66, 0.55, 0.85);
  leg.SetBorderSize(0);
  leg.SetLineStyle(0);
  leg.SetTextFont(42);
  leg.SetFillStyle(0);

  h_alphamax_aod->SetMaximum(.3);

  TCanvas c("c", "c", 640, 480);
  h_alphamax_aod->Draw("HIST E");
  c.Modified(); c.Update();
  TPaveStats *stats =(TPaveStats*)c.GetPrimitive("stats");
  stats->SetName("h1stats");
  stats->SetY1NDC(1);
  stats->SetY2NDC(.9);
  stats->SetTextColor(kRed);
  leg.AddEntry(h_alphamax_aod, "LLDJ: AODCaloJetAlphaMax", "l");

  h_alphamax_miniaod->Draw("HIST E SAMES");
  c.Modified(); c.Update();
  TPaveStats *stats2 = (TPaveStats*)c.GetPrimitive("stats");
  stats2->SetName("h1stats2");
  stats2->SetY1NDC(.9);
  stats2->SetY2NDC(.8);
  stats2->SetTextColor(kBlue);
  leg.AddEntry(h_alphamax_miniaod, "LLDJ: jetAlphaMaxD", "l");

  h_alphamax_rutgers->Draw("HIST E SAMES");
  c.Modified(); c.Update();
  TPaveStats *stats3 = (TPaveStats*)c.GetPrimitive("stats");
  stats3->SetName("h1stats3");
  stats3->SetY1NDC(.8);
  stats3->SetY2NDC(.7);
  stats3->SetTextColor(kGreen+1);
  leg.AddEntry(h_alphamax_rutgers, "Rutgers: AlphaMax (good jets)", "l");

  h_alphamax_all20_rutgers->Draw("HIST E SAMES");
  c.Modified(); c.Update();
  TPaveStats *stats4 = (TPaveStats*)c.GetPrimitive("stats");
  stats4->SetName("h1stats4");
  stats4->SetY1NDC(.7);
  stats4->SetY2NDC(.6);
  stats4->SetTextColor(kViolet);
  leg.AddEntry(h_alphamax_all20_rutgers, "Rutgers: AlphaMax (all pT>20)", "l");
  
  leg.Draw();

  c.SaveAs("c.pdf");

}


void draw_lldj_rutgers(){
  looping();
}
