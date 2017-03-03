#include "draw.h"

using namespace std;


void files_test(){
  std::vector<TString> test;
  test.push_back("a.root");
  test.push_back("b.root");
  sample2 mysample2(test);
}

void eff_vs_x_fromJetTrees(){

  TString path = "root://cmsxrootd.fnal.gov//store/group/lpchbb/noreplica/stata/AnalysisTrees/addedHistos/";

  std::vector<sample*> sampleVector;

  std::vector<TString> sampleNames;
  //ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1 10.11
  //ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1 26.23
  //ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1 44.09
  //ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1 38.09
  //ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1 38.09
  //WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 61467
  //ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8 0.8696*0.577*0.102
  //DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 6025
  //DYJetsToLL_M-5to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 7160
  //WZ_TuneCUETP8M1_13TeV-pythia8 63
  //ZZ_TuneCUETP8M1_13TeV-pythia8 10.32
  //WW_TuneCUETP8M1_13TeV-pythia8 118.7

  sample sample1(path+"allHistos_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0.root");
  sample1.tree_name = "tree_BASICCALOJETS1PT20MATCHED";
  sample1.humanName = "DY";
  sample1.color = kBlue;
  sampleVector.push_back(&sample1);

  /*sample sample2(path+"allHistos_ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_0.root");
  sample2.tree_name = "tree_BASICCALOJETS1PT20MATCHED";
  sample2.humanName = "ZH, MS=40, dddd";
  sample2.color = kRed;
  sampleVector.push_back(&sample2);
  */

  //80 studies
  TString var1 = "NBASICCALOJETS1PT20MATCHED";
  double min = 0, max = 8, nbins = 8, maxEff = 0.006;

  TString tag_string = "(ALPHAMAX_BASICCALOJETS1PT20MATCHED<0.25 && MEDIANIPLOG10SIG_BASICCALOJETS1PT20MATCHED>0.5)";//E
  //TString tag_string = "(ALPHAMAX_BASICCALOJETS1PT20MATCHED<0.25 && MEDIANIPLOG10SIG_BASICCALOJETS1PT20MATCHED>0.5 && NMATCHEDTRACKS_BASICCALOJETS1PT20>4)";//E

  //ALL JETS
  drawPlots(sampleVector, var1, nbins, min, max, var1, "Events", "");
  TH1D* h_all1 = (TH1D*)sample1.lastHisto.Clone("all_1");
  //TH1D* h_all2 = (TH1D*)sample2.lastHisto.Clone("all_2");
  h_all1->SetTitle("all");
  //h_all2->SetTitle("all");

  //TAGGED
  drawPlots(sampleVector, var1, nbins, min, max, var1, "Events", tag_string);
  TH1D* h_tagged1 = (TH1D*)sample1.lastHisto.Clone("tagged");
  //TH1D* h_tagged2 = (TH1D*)sample2.lastHisto.Clone("tagged");
  h_tagged1->SetTitle("tagged");
  //h_tagged2->SetTitle("tagged");

  TH1D* h_eff1 = (TH1D*)h_tagged1->Clone("eff1");
  h_eff1->Divide(h_all1);
  h_eff1->SetTitle("eff");
  /*
  TH1D* h_eff2  = (TH1D*)h_tagged2->Clone("eff2");
  h_eff2->Divide(h_all2);
  h_eff2->SetTitle("eff");
  h_eff2->SetLineColor(kRed);
  */
  TCanvas* c1 = new TCanvas("c1", "c1", 1*480, 3*480);
  c1->Divide(1,3);
  c1->cd(1);
  h_tagged1->DrawNormalized();
  //h_tagged2->DrawNormalized("SAME");
  c1->cd(2);
  h_all1->DrawNormalized();
  //h_all2->DrawNormalized("SAME");
  c1->cd(3);
  //  h_eff2->SetMinimum(0);
  //h_eff2->SetMaximum(.28);
  //h_eff2->Draw("SAME");
  h_eff1->Draw();
  c1->Print("c.pdf");

}


void flavor_study(){

  std::vector<sample*> sampleVector;

  sample sample1("ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-0_TuneCUETP8M1_13TeV-powheg-pythia8.root");
  sample1.humanName = "ZH, MS=40, bbbb";
  sample1.color = kBlue;
  sampleVector.push_back(&sample1);

  sample sample2("ZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-0_TuneCUETP8M1_13TeV-powheg-pythia8.root");
  sample2.humanName = "ZH, MS=40, dddd";
  sample2.color = kRed;
  sampleVector.push_back(&sample2);

   //80 studies
  TString var1 = "PT_BASICCALOJETS1PT20";
  TString var2 = "PT_INCLUSIVETAGGEDCALOJETSE";
  double min = 0, max = 150, nbins = 10, maxEff = 0.006;
  //TString var1 = "SELFDELTAR_BASICCALOJETS1PT20";
  //TString var2 = "BASICCALOJETS1PT20DELTAR_INCLUSIVETAGGEDCALOJETSE";
  //double min = 0, max = 5, nbins = 10, maxEff = 0.006;

  //ALL JETS
  drawPlots(sampleVector, var1, nbins, min, max, var1, "Events", "");
  TH1D* h_all1 = (TH1D*)sample1.lastHisto.Clone("all_1");
  TH1D* h_all2 = (TH1D*)sample2.lastHisto.Clone("all_2");
  h_all1->SetTitle("all");
  h_all2->SetTitle("all");
  h_all2->SetLineColor(kRed);

  //TAGGED
  drawPlots(sampleVector, var2, nbins, min, max, var2, "Events", "");
  TH1D* h_tagged1 = (TH1D*)sample1.lastHisto.Clone("tagged");
  TH1D* h_tagged2 = (TH1D*)sample2.lastHisto.Clone("tagged");
  h_tagged1->SetTitle("tagged");
  h_tagged2->SetTitle("tagged");
  h_tagged2->SetLineColor(kRed);

  TH1D* h_eff1 = (TH1D*)h_tagged1->Clone("eff1");
  h_eff1->Divide(h_all1);
  h_eff1->SetTitle("eff");

  TH1D* h_eff2  = (TH1D*)h_tagged2->Clone("eff2");
  h_eff2->Divide(h_all2);
  h_eff2->SetTitle("eff");
  h_eff2->SetLineColor(kRed);

  TCanvas* c1 = new TCanvas("c1", "c1", 1*480, 3*480);
  c1->Divide(1,3);
  c1->cd(1);
  h_tagged2->DrawNormalized();
  h_tagged1->DrawNormalized("SAME");
  c1->cd(2);
  h_all2->DrawNormalized();
  h_all1->DrawNormalized("SAME");
  c1->cd(3);
  h_eff2->SetMinimum(0);
  h_eff2->SetMaximum(.28);
  h_eff2->Draw();
  h_eff1->Draw("SAME");
  c1->Print("c.pdf");

  
}


void ttbar_emu(){

  TString path = "root://cmsxrootd.fnal.gov//store/user/lpchbb/mwalker/AnalysisTrees/";

  std::vector<sample*> sampleVector;

  sample sample1(path+"TT_TuneCUETP8M1_13TeV-powheg-pythia8/addedHistos/allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8.root");
  sample1.humanName = "TTbar";
  sample1.color = kBlue;
  sampleVector.push_back(&sample1);

  //80 studies
  TString var1 = "NINCLUSIVETAGGEDCALOJETSE";
  double min = 0, max = 7, nbins = 7, maxEff = 0.006;
  
  //SF
  drawPlots(sampleVector, var1, nbins, min, max, var1, "Events", "(NGOODMUONS[0]==2 || NGOODELECTRONS[0]==2)");
  TH1D* h_sf = (TH1D*)sample1.lastHisto.Clone("sf");

  //EMU
  drawPlots(sampleVector, var1, nbins, min, max, var1, "Events", "NGOODMUONS[0]==1 && NGOODELECTRONS[0]==1");
  TH1D* h_emu = (TH1D*)sample1.lastHisto.Clone("emu");
  h_emu->SetLineColor(kRed); 

  TCanvas* c1 = new TCanvas("c1", "c1", 1*480, 1*480);
  h_emu->DrawNormalized();
  h_sf->DrawNormalized("SAME");
  c1->Print("c.pdf");
  gPad->SetLogy();
  c1->Print("c_log.pdf");
  
}

void DY_pt(){

  TString path = "root://cmsxrootd.fnal.gov//store/user/lpchbb/mwalker/AnalysisTrees/";

  std::vector<sample*> sampleVector;

  sample sample1(path+"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/addedHistos/allHistos_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  sample1.humanName = "DY";
  sample1.color = kBlue;
  sampleVector.push_back(&sample1);

  //80 studies
  TString var1 = "NINCLUSIVETAGGEDCALOJETSE";
  double min = 0, max = 7, nbins = 7, maxEff = 0.006;
  
  //SF
  drawPlots(sampleVector, var1, nbins, min, max, var1, "Events", "NOSSF == 1 && ONZ");
  TH1D* h_sf = (TH1D*)sample1.lastHisto.Clone("sf");

  //EMU
  drawPlots(sampleVector, var1, nbins, min, max, var1, "Events", "NOSSF == 1 && !ONZ");
  TH1D* h_emu = (TH1D*)sample1.lastHisto.Clone("emu");
  h_emu->SetLineColor(kRed); 

  TCanvas* c1 = new TCanvas("c1", "c1", 1*480, 1*480);
  h_emu->DrawNormalized();
  h_sf->DrawNormalized("SAME");
  c1->Print("c.pdf");
  gPad->SetLogy();
  c1->Print("c_log.pdf");
  
}



void qcd_jets(){

  //TString path = "root://cmsxrootd.fnal.gov//store/user/lpchbb/mwalker/AnalysisTrees/";
  TString path = "root://cmsxrootd.fnal.gov//store/group/lpchbb/kreis/AnalysisTrees/";

  std::vector<sample*> sampleVector;

  sample sample1(path+"DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/add_noSkim/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  sample1.humanName = "DY";
  sample1.color = kBlue;
  sampleVector.push_back(&sample1);

  sample sample2(path+"GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/add_noSkim/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  sample2.humanName = "GJets";
  sample2.color = kViolet;
  sampleVector.push_back(&sample2);

  sample sample3(path+"QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/add_noSkim/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  sample3.humanName = "QCD";
  sample3.color = kRed;
  sampleVector.push_back(&sample3);

  //80 studies tagger
  TString var1 = "NINCLUSIVETAGGEDCALOJETSE";
  double min = 0, max = 7, nbins = 7;
  drawPlots(sampleVector, var1, nbins, min, max, var1, "Events", "");
  TH1D* h1 = (TH1D*)sample1.lastHisto.Clone("DY");
  TH1D* h2 = (TH1D*)sample2.lastHisto.Clone("GJets");
  TH1D* r = (TH1D*)h1->Clone("r");
  r->Divide(h2);
  r->SetMinimum(0);
  r->SetMaximum(5);
  TCanvas* cr = new TCanvas("cr", "cr", 640, 480);
  r->Draw("hist e");
  cr->SaveAs("h_Ratio.pdf");


  //80 studies tagger
  TString var2 = "HT";
  min = 0; max = 300; nbins = 30;
  drawPlots(sampleVector, var2, nbins, min, max, var2, "Events", "");

  //80 studies tagger
  TString var3 = "NBASICCALOJETS1PT20";
  min = 0; max = 10; nbins = 10;
  drawPlots(sampleVector, var3, nbins, min, max, var3, "Events", "");

  //80 studies tagger
  TString var4 = "PT_BASICCALOJETS1PT20";
  min = 0; max = 100; nbins = 10;
  drawPlots(sampleVector, var4, nbins, min, max, var4, "Events", "");

  //80 studies tagger
  TString var5 = "N_bJetsCSVL";
  min = 0; max = 11; nbins = 10;
  drawPlots(sampleVector, var5, nbins, min, max, var4, "Events", "");

  //80 studies tagger
  TString var6 = "N_bJetsCSVM";
  min = 0; max = 11; nbins = 10;
  drawPlots(sampleVector, var6, nbins, min, max, var4, "Events", "");

  
}


void draw_2D(){
  gStyle->SetOptTitle(1);

  TString path = "root://cmsxrootd.fnal.gov//store/user/stata/AnalysisTrees/addedHistos/";

  std::vector<sample*> sampleVector;

  //sample sample1(path+"allHistos_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");                                           
  sample sample1(path+"allHistos_DYJetsToLL_BGenFilter_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0.root");
  sample1.humanName = "sample 1";
  sample1.color = kRed;
  sampleVector.push_back(&sample1);

  //TH2D* h = new TH2D("h", "h", 40, 0, 40, 20, 0, 5);
  //TH2D* h = new TH2D("h", "h", 40, 0, 40, 8, 1, 9);
  TH2D* h = new TH2D("h", "h", 20, 0, 40, 20, 0, 40);
  h->Sumw2();
  //(sampleVector.at(0)->tree)->Project("h", "BASICCALOJETS1DELTAR_BASICCALOJETS1:PT_BASICCALOJETS1", "");
  //(sampleVector.at(0)->tree)->Project("h", "BASICCALOJETS1DELTAR_BASICCALOJETS1:PTOSSF", "");
  //(sampleVector.at(0)->tree)->Project("h", "NBASICCALOJETS1:PTOSSF", "");
  //(sampleVector.at(0)->tree)->Project("h", "PT_BASICCALOJETS1:PTOSSF", "");
  //(sampleVector.at(0)->tree)->Project("h", "PT_BASICCALOJETS1[1]:PTOSSF", "");
  //(sampleVector.at(0)->tree)->Project("h", "PT_BASICCALOJETS1[1]:PT_BASICCALOJETS1[0]", "");
  
  TProfile *px = h->ProfileX("px");
  
  
  TCanvas myC("myC", "myC", 480, 480);
  myC.cd();
  //h->Draw("COLZ");
  px->Draw();
  myC.Print("c1.pdf");

}

void draw_jetpt_vs_zpt(){
  gStyle->SetOptTitle(1);
  gStyle->SetOptStat(0);

  TString path = "root://cmsxrootd.fnal.gov//store/user/stata/AnalysisTrees/addedHistos/";

  std::vector<sample*> sampleVector;

  //sample sample1(path+"allHistos_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");                                           
  sample sample1(path+"allHistos_DYJetsToLL_BGenFilter_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0.root");
  sample1.humanName = "sample 1";
  sample1.color = kRed;
  sampleVector.push_back(&sample1);

  TH2D* h0 = new TH2D("h0", "h0", 20, 0, 60, 20, 0, 60);
  TH2D* h1 = new TH2D("h1", "h1", 20, 0, 60, 20, 0, 60);
  TH2D* h2 = new TH2D("h2", "h2", 20, 0, 60, 20, 0, 60);
  h0->Sumw2();
  h1->Sumw2();
  h2->Sumw2();
  (sampleVector.at(0)->tree)->Project("h0", "PT_BASICCALOJETS1[0]:PTOSSF", "");
  (sampleVector.at(0)->tree)->Project("h1", "PT_BASICCALOJETS1[1]:PTOSSF", "");
  (sampleVector.at(0)->tree)->Project("h2", "PT_BASICCALOJETS1[2]:PTOSSF", "");
   
  TProfile *px0 = h0->ProfileX("px0");
  TProfile *px1 = h1->ProfileX("px1");
  TProfile *px2 = h2->ProfileX("px2");
  
  px1->SetLineColor(kBlue);
  px2->SetLineColor(kRed);
  
  TCanvas myC("myC", "myC", 480, 480);
  myC.cd();
  //h->Draw("COLZ");
  px0->Draw();
  px1->Draw("SAME");
  px2->Draw("SAME");
  myC.Print("c1.pdf");


  TH2D* hjj = new TH2D("hjj", "hjj", 20, 0, 60, 20, 0, 60);
  hjj->Sumw2();
  (sampleVector.at(0)->tree)->Project("hjj", "PT_BASICCALOJETS1[1]:PT_BASICCALOJETS1[0]", "NBASICCALOJETS1>=2");
  TProfile *pxjj = hjj->ProfileX("pxjj");
  hjj->Draw("COLZ");
  pxjj->Draw("SAME");
  myC.Print("c2.pdf");


  TH2D* hRZ = new TH2D("hRZ", "hRZ", 20, 0, 80, 20, 0, 5);
  hRZ->Sumw2();
  (sampleVector.at(0)->tree)->Project("hRZ", "SELFDELTAR_BASICCALOJETS1:PTOSSF", "");
  TProfile *pxRZ = hRZ->ProfileX("pxRZ");
  hRZ->Draw("COLZ");
  pxRZ->Draw("SAME");
  myC.Print("c3.pdf");


  TString tag_string = "(BETA_BASICCALOJETS1>0.9 && MEDIANIPLOG10SIG_BASICCALOJETS1>0.868 && MEDIANLOG10TRACKANGLE_BASICCALOJETS1>-1.8";
  tag_string += "&& TOTALTRACKANGLE_BASICCALOJETS1>0.1 && SUMIPSIG_BASICCALOJETS1>50 && TOTALTRACKPT_BASICCALOJETS1>5)"; 

  TH2D* hRP     = new TH2D("hRP", "hRP",         6, 0, 60, 8, 0, 5);
  TH2D* hRP_tag = new TH2D("hRP_tag", "hRP_tag", 6, 0, 60, 8, 0, 5);
  hRP->Sumw2();
  hRP_tag->Sumw2();
  (sampleVector.at(0)->tree)->Project("hRP",     "SELFDELTAR_BASICCALOJETS1:PT_BASICCALOJETS1", "");
  (sampleVector.at(0)->tree)->Project("hRP_tag", "SELFDELTAR_BASICCALOJETS1:PT_BASICCALOJETS1", tag_string);
  
  TH2D* h_eff = (TH2D*)hRP_tag->Clone("eff");
  h_eff->Divide(hRP);
  h_eff->SetMinimum(0);
  h_eff->SetMaximum(0.01);

  TCanvas* c1 = new TCanvas("c1", "c1", 480, 3*480);
  c1->Divide(1,3);
  c1->cd(1);
  gPad->SetRightMargin(.15);
  hRP_tag->Draw("COLZ");
  c1->cd(2);
  gPad->SetRightMargin(.15);
  hRP->Draw("COLZ");
  c1->cd(3);
  gPad->SetRightMargin(.15);
  h_eff->Draw("COLZ");
  c1->SaveAs("c4.pdf");

  myC.cd();
  gPad->SetLogz();
  TH2D* hNP = new TH2D("hNP", "hNP", 20, 0, 80, 10, 0, 10);
  hNP->Sumw2();
  (sampleVector.at(0)->tree)->Project("hNP", "NMATCHEDTRACKS_BASICCALOJETS1:PT_BASICCALOJETS1", "");
  TProfile *pxNP = hNP->ProfileX("pxNP");
  hNP->Draw("COLZ");
  pxNP->Draw("SAME");
  myC.Print("c5.pdf");

  //all tagging variables
  

}


void draw_correlation_fromTrees(){
  gStyle->SetOptTitle(1);

  TString path = "root://cmsxrootd.fnal.gov//store/user/lpchbb/mwalker/AnalysisTrees/";

  std::vector<sample*> sampleVector;

  sample sample1(path+"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8//addedHistos//allHistos_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  //sample sample1(path+"WplusH_HToSSTobbbb_WToLNu_MH-125_MS-40_ctauS-1_TuneCUETP8M1_13TeV-powheg-pythia8/addedHistos/allHistos_WplusH_HToSSTobbbb_WToLNu_MH-125_MS-40_ctauS-1_TuneCUETP8M1_13TeV-powheg-pythia8_0.root");
  sample1.humanName = "sample 1";
  sample1.color = kRed;
  sampleVector.push_back(&sample1);

  //76 studies
  //TString var1 = "PT_BASICCALOJETS1";
  //TString var2 = "PT_INCLUSIVETAGGEDCALOJETSC";

  //80 studies
  TString var1 = "PT_BASICCALOJETS1PT20";
  TString var2 = "PT_INCLUSIVETAGGEDCALOJETSE";
  double min = 0, max = 10, nbins = 10, maxEff = 0.006;

  //ALL JETS
  drawPlots(sampleVector, var1, nbins, min, max, var1, "Events", "");
  TH1D* h_all = (TH1D*)sample1.lastHisto.Clone("all");
  h_all->SetTitle("all");

  //TAGGED
  drawPlots(sampleVector, var2, nbins, min, max, var2, "Events", "");
  TH1D* h_tagged = (TH1D*)sample1.lastHisto.Clone("tagged");
  h_tagged->SetTitle("tagged");

  TH1D* h_eff = (TH1D*)h_tagged->Clone("eff");
  h_eff->Divide(h_all);
  h_eff->SetTitle("eff");

  TCanvas* c1 = new TCanvas("c1", "c1", 1*480, 3*480);
  c1->Divide(1,3);
  c1->cd(1);
  h_tagged->Draw();
  c1->cd(2);
  h_all->Draw();
  c1->cd(3);
  h_eff->Draw();
  c1->Print("c1.pdf");

}

void draw_correlation(){
  gStyle->SetOptTitle(1);

  TString path = "root://cmsxrootd.fnal.gov//store/user/lpchbb/mwalker/AnalysisTrees/";

  std::vector<sample*> sampleVector;

  sample sample1(path+"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8//addedHistos//allHistos_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  //sample sample1("~/jan3/histo_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_161018_170954_970.root");
  //sample sample1(path+"TT_TuneCUETP8M1_13TeV-powheg-pythia8/addedHistos/allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8.root");
  sample1.humanName = "sample 1";
  sample1.color = kRed;
  sampleVector.push_back(&sample1);
  
  TString tag_string = "(ALPHAMAX_BASICCALOJETS1PT20<0.25 && MEDIANIPLOG10SIG_BASICCALOJETS1PT20>0.5)";//E
  //TString tag_string = "(ALPHAMAX_BASICCALOJETS1PT20<0.5 && MEDIANIPLOG10SIG_BASICCALOJETS1PT20>0.0)";//F

  //TString var = "NGOODVERTICES";
  //double min = 0, max = 30, nbins = 15,  maxEff = 0.006;
  //TString var = "NMATCHEDTRACKS_BASICCALOJETS1PT20";
  //double min = 1, max = 9, nbins = 8, maxEff = 0.006;
  //TString var = "BASICCALOJETS1PT20DELTAR_BASICCALOJETS1PT20";
  //TString var = "SELFDELTAR_BASICCALOJETS1PT20";
  //double min = 0, max = 5, nbins = 20, maxEff = 0.006;
  //TString var = "SELFDELTAR_BASICCALOJETS1PT20";
  //double min = 0, max = 5, nbins = 20, maxEff = 0.006;
  TString var = "NBASICCALOJETS1PT20";
  double min = 1, max = 9, nbins = 8, maxEff = 0.006;
  //TString var = "HT";
  //double min = 0, max = 300, nbins = 20, maxEff = 0.006;
  //TString var = "PTOSSF";
  //double min = 0, max = 100, nbins = 20, maxEff = 0.006;
  //TString var = "PT_BASICCALOJETS1PT20";
  //double min = 0, max = 100, nbins = 20, maxEff = 0.006;

  //ALL JETS
  drawPlots(sampleVector, var, nbins, min, max, var, "Events", "");
  TH1D* h_all = (TH1D*)sample1.lastHisto.Clone("all");
  h_all->SetTitle("all");

  drawPlots(sampleVector, var, nbins, min, max, var, "Events", tag_string);
  TH1D* h_tagged = (TH1D*)sample1.lastHisto.Clone("tagged");
  h_tagged->SetTitle("tagged");

  TH1D* h_eff = (TH1D*)h_tagged->Clone("eff");
  h_eff->Divide(h_all);
  h_eff->SetTitle("eff");
  //h_eff->SetMaximum(maxEff);
  //h_eff->SetMinimum(0);

  //FIT
  TF1 *f1 = new TF1("f1", "pol1", 1, max);
  h_eff->Fit("f1", "R");

  //PT CUT
  drawPlots(sampleVector, var, nbins, min, max, var, "Events", "PT_BASICCALOJETS1PT20>60");
  TH1D* h_all_ptCut = (TH1D*)sample1.lastHisto.Clone("all_ptCut");
  h_all_ptCut->SetTitle("all_ptCut");

  drawPlots(sampleVector, var, nbins, min, max, var, "Events", tag_string + "&& PT_BASICCALOJETS1PT20>60");
  TH1D* h_tagged_ptCut = (TH1D*)sample1.lastHisto.Clone("tagged_ptCut");
  h_tagged_ptCut->SetTitle("tagged_ptCut");

  TH1D* h_eff_ptCut = (TH1D*)h_tagged_ptCut->Clone("eff_ptCut");
  h_eff_ptCut->Divide(h_all_ptCut);
  h_eff_ptCut->SetTitle("eff_ptCut");
  //h_eff_ptCut->SetMaximum(maxEff);
  //h_eff_ptCut->SetMinimum(0);

  //FIT
  TF1 *f2 = new TF1("f2", "pol1", 1, max);
  h_eff_ptCut->Fit("f2", "R");

  TCanvas* c1 = new TCanvas("c1", "c1", 2*480, 3*480);
  c1->Divide(2,3);
  c1->cd(1);
  h_tagged->Draw();
  c1->cd(2);
  h_tagged_ptCut->Draw();
  c1->cd(3);
  h_all->Draw();
  c1->cd(4);
  h_all_ptCut->Draw();
  c1->cd(5);
  h_eff->Draw();
  f1->Draw("SAME");
  c1->cd(6);
  h_eff_ptCut->Draw();
  f2->Draw("SAME");
  c1->SaveAs("c1.pdf");
  c1->SaveAs("c1.png");

  /*
  TFile f1("file.root","RECREATE");
  f1.cd();
  h_all->Write();
  h_tagged->Write();
  h_eff->Write();
  h_all_ptCut->Write();
  h_tagged_ptCut->Write();
  h_eff_ptCut->Write();
  f1.Close();
  */
}

void draw_pt_eff(){
  gStyle->SetOptTitle(1);

  TString path = "root://cmsxrootd.fnal.gov//store/user/stata/AnalysisTrees/addedHistos/";

  std::vector<sample*> sampleVector;

  sample sample1(path+"allHistos_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  sample1.humanName = "sample 1";
  sample1.color = kRed;
  sampleVector.push_back(&sample1);
  
  TString tag_string = "(BETA_BASICCALOJETS>0.9 && MEDIANIPLOG10SIG_BASICCALOJETS>0.868 && MEDIANLOG10TRACKANGLE_BASICCALOJETS>-1.8";
  tag_string += "&& TOTALTRACKANGLE_BASICCALOJETS>0.1 && SUMIPSIG_BASICCALOJETS>50 && TOTALTRACKPT_BASICCALOJETS>5)"; 

  TString var = "PT_BASICCALOJETS";
  double min = 5, max = 200, nbins = 20;

  //ALL JETS
  drawPlots(sampleVector, var, nbins, min, max, var, "Events", "");
  TH1D* h_all = (TH1D*)sample1.lastHisto.Clone("all");
  h_all->SetTitle("all");

  drawPlots(sampleVector, var, nbins, min, max, var, "Events", tag_string);
  TH1D* h_tagged = (TH1D*)sample1.lastHisto.Clone("tagged");
  h_tagged->SetTitle("tagged");

  TH1D* h_eff = (TH1D*)h_tagged->Clone("eff");
  h_eff->Divide(h_all);
  h_eff->SetTitle("eff");

  TCanvas* c1 = new TCanvas("c1", "c1", 1*480, 3*480);
  c1->Divide(1,3);
  c1->cd(1);
  h_tagged->Draw();
  c1->cd(2);
  h_all->Draw();
  c1->cd(3);
  h_eff->Draw();
  c1->SaveAs("c1.pdf");
  c1->SaveAs("c1.png");
}

void draw_in_PV_slices(){

  //TString path = "/uscms_data/d3/mwalker/VHdisplaced/20160426_runAnalyisTrees/";
  TString path = "root://cmsxrootd.fnal.gov//store/user/lpchbb/mwalker/AnalysisTrees/";

  std::vector<sample*> sampleVector;

  sample sample1(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS25_ctauS100_13TeV.root");
  sample1.humanName = "sample 1";
  sample1.color = kRed;
  sampleVector.push_back(&sample1);

  sample sample2(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS10_ctauS10_13TeV.root");
  sample2.humanName = "sample 2";
  sample2.color = kBlue;
  //sampleVector.push_back(&sample2);

  //drawPlots(sampleVector, "ALPHAMAX_ALLCALOJETS", 20, 0, 1, "ALPHAMAX_ALLCALOJETS", "Events", "NGOODVERTICES<10");

  //Gymnastics to plot same sample mutiple times with different cuts
  //TString var = "ALPHAMAX_ALLCALOJETSMATCHED"; double min = 0; double max = 1; double ymax = -1;
  //TString var = "MEDIANIPLOG10SIG_ALLCALOJETS"; double min = -2; double max = 4; double ymax = 0.25;
  //TString var = "MEDIANLOG10TRACKANGLE_ALLCALOJETS"; double min = -4.5; double max = 0.5; double ymax = 0.35;
  TString var = "BETA_BASICCALOJETSMATCHED"; double min = 0; double max = 1; double ymax = -1;

  std::vector<TH1D*> hvec;
  drawPlots(sampleVector, var, 20, min, max, var, "Events", "NGOODVERTICES<=5");
  hvec.push_back((TH1D*)sample1.lastHisto.Clone("upto5"));
  drawPlots(sampleVector, var, 20, min, max, var, "Events", "NGOODVERTICES>5&&NGOODVERTICES<=10");
  hvec.push_back((TH1D*)sample1.lastHisto.Clone("5to10"));
  drawPlots(sampleVector, var, 20, min, max, var, "Events", "NGOODVERTICES>10&&NGOODVERTICES<=15");
  hvec.push_back((TH1D*)sample1.lastHisto.Clone("10to15"));
  drawPlots(sampleVector, var, 20, min, max, var, "Events", "NGOODVERTICES>15&&NGOODVERTICES<=20");
  hvec.push_back((TH1D*)sample1.lastHisto.Clone("15to20"));
  drawPlots(sampleVector, var, 20, min, max, var, "Events", "NGOODVERTICES>20");
  hvec.push_back((TH1D*)sample1.lastHisto.Clone("20up"));

  const int color[7]={1,2,3,4,6,7,8};
  TLegend leg(0.7, 0.6, 0.88, 0.88);
  leg.SetBorderSize(0);
  leg.SetLineStyle(0);
  leg.SetTextFont(42);
  leg.SetFillStyle(0);
  TCanvas c("c", "c1", 640, 640);
  c.cd();
  for(unsigned int i = 0; i<hvec.size(); i++){
    hvec.at(i)->Scale(1.0/hvec.at(i)->Integral());
    if(i==0) hvec.at(i)->GetXaxis()->SetTitle(var);
    if(i==0) hvec.at(i)->GetYaxis()->SetTitle("Arb.");
    if(i==0 && ymax>0) hvec.at(i)->SetMaximum(ymax);
    hvec.at(i)->SetLineColor(color[i]);
    hvec.at(i)->SetLineWidth(2);
    //hvec.at(i)->DrawNormalized("HIST SAMES");
    hvec.at(i)->Draw("HIST SAMES");
    leg.AddEntry(hvec.at(i),hvec.at(i)->GetName(),"L");
  }
  leg.Draw();
  c.Print("overlay_"+var+".pdf");

}


void draw_fixedmass_varylifetime(){

  //TString path = "/uscms_data/d3/mwalker/VHdisplaced/20160426_runAnalyisTrees/";
  TString path = "root://cmsxrootd.fnal.gov//store/user/lpchbb/mwalker/AnalysisTrees/";
    
  std::vector<sample*> sampleVector;
  
  //WH, pick mass, overlay lifetime
  TString masspoint = "40";
  sample sample1(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS"+masspoint+"_ctauS0_13TeV.root");
  sample1.humanName = "WH, bbbb, mS="+masspoint+", ctau=0";
  sample1.color = kMagenta;
  sampleVector.push_back(&sample1);

  sample sample2(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS"+masspoint+"_ctauS1_13TeV.root");
  sample2.humanName = "WH, bbbb, mS="+masspoint+", ctau=1";
  sample2.color = kMagenta+1;
  sampleVector.push_back(&sample2);

  sample sample3(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS"+masspoint+"_ctauS10_13TeV.root");
  sample3.humanName = "WH, bbbb, mS="+masspoint+", ctau=10";
  sample3.color = kMagenta+2;
  sampleVector.push_back(&sample3);

  sample sample4(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS"+masspoint+"_ctauS100_13TeV.root");
  sample4.humanName = "WH, bbbb, mS="+masspoint+", ctau=100";
  sample4.color = kMagenta+3;
  sampleVector.push_back(&sample4);

  sample sample5(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS"+masspoint+"_ctauS1000_13TeV.root");
  sample5.humanName = "WH, bbbb, mS="+masspoint+", ctau=1000";
  sample5.color = kMagenta+4;
  sampleVector.push_back(&sample5);

  drawPlots(sampleVector, "ALPHAMAX_ALLCALOJETS", 20, 0, 1, "ALPHAMAX_ALLCALOJETS", "Events");
  drawPlots(sampleVector, "MEDIANIPLOG10SIG_ALLCALOJETS", 20, -2, 4, "MEDIANIPLOG10SIG_ALLCALOJETS", "Events");
  drawPlots(sampleVector, "MEDIANLOG10TRACKANGLE_ALLCALOJETS", 20, -4.5, 0.5, "MEDIANLOG10TRACKANGLE_ALLCALOJETS", "Events");
  
}


void draw_varymass_fixlifetime(){

  //TString path = "/uscms_data/d3/mwalker/VHdisplaced/20160426_runAnalyisTrees/";
  TString path = "root://cmsxrootd.fnal.gov//store/user/lpchbb/mwalker/AnalysisTrees/";

  std::vector<sample*> sampleVector;
  
  //WH, pick lifetime, vary mass
  TString ctaupoint = "1000";
  sample sample1(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS10_ctauS"+ctaupoint+"_13TeV.root");
  sample1.humanName = "WH, bbbb, mS=10, ctau="+ctaupoint+"";
  sample1.color = kMagenta;
  sampleVector.push_back(&sample1);

  sample sample2(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS25_ctauS"+ctaupoint+"_13TeV.root");
  sample2.humanName = "WH, bbbb, mS=25, ctau="+ctaupoint+"";
  sample2.color = kMagenta+1;
  sampleVector.push_back(&sample2);

  sample sample3(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS40_ctauS"+ctaupoint+"_13TeV.root");
  sample3.humanName = "WH, bbbb, mS=40, ctau="+ctaupoint+"";
  sample3.color = kMagenta+2;
  sampleVector.push_back(&sample3);

  drawPlots(sampleVector, "TOTALTRACKPT_BASICCALOJETSMATCHED", 20, 0, 50, "TOTALTRACKPT_BASICCALOJETSMATCHED", "Events");
  //drawPlots(sampleVector, "ALPHAMAX_ALLCALOJETS", 20, 0, 1, "ALPHAMAX_ALLCALOJETS", "Events");
  //drawPlots(sampleVector, "MEDIANIPLOG10SIG_ALLCALOJETS", 20, -2, 4, "MEDIANIPLOG10SIG_ALLCALOJETS", "Events");
  //drawPlots(sampleVector, "MEDIANLOG10TRACKANGLE_ALLCALOJETS", 20, -4.5, 0.5, "MEDIANLOG10TRACKANGLE_ALLCALOJETS", "Events");
  
}

void draw_light(){

  //TString path = "/uscms_data/d3/mwalker/VHdisplaced/20160426_runAnalyisTrees/";
  TString path = "root://cmsxrootd.fnal.gov//store/user/lpchbb/mwalker/AnalysisTrees/";

  std::vector<sample*> sampleVector;
  
  //WH, pick lifetime, vary mass
  sample sample1(path+"allHistos_WH_HToSSTodddd_WToLNu_MH125_MS25_ctauS10_13TeV.root");
  sample1.humanName = "WH, dddd, mS=25, ctau=10";
  sample1.color = kMagenta;
  sampleVector.push_back(&sample1);

  sample sample2(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS25_ctauS10_13TeV.root");
  sample2.humanName = "WH, bbbb, mS=25, ctau=10";
  sample2.color = kMagenta+1;
  sampleVector.push_back(&sample2);

  drawPlots(sampleVector, "ALPHAMAX_BASICCALOJETSMATCHED", 20, 0, 1, "ALPHAMAX_BASICCALOJETSMATCHED", "Events");
  drawPlots(sampleVector, "BETA_BASICCALOJETSMATCHED", 20, 0, 1, "BETA_BASICCALOJETSMATCHED", "Events");
  drawPlots(sampleVector, "MEDIANIPLOG10SIG_BASICCALOJETSMATCHED", 20, -2, 4, "MEDIANIPLOG10SIG_BASICCALOJETSMATCHED", "Events");
  drawPlots(sampleVector, "MEDIANLOG10TRACKANGLE_BASICCALOJETSMATCHED", 20, -4.5, 0.5, "MEDIANLOG10TRACKANGLE_BASICCALOJETSMATCHED", "Events");
  drawPlots(sampleVector, "NMATCHEDTRACKS_BASICCALOJETSMATCHED", 20, 0, 20, "NMATCHEDTRACKS_BASICCALOJETSMATCHED", "Events");
  drawPlots(sampleVector, "AVFVERTEXTRACKMASS_BASICCALOJETSMATCHED", 20, 0, 20, "AVFVERTEXTRACKMASS_BASICCALOJETSMATCHED", "Events");
  drawPlots(sampleVector, "TOTALTRACKPT_BASICCALOJETSMATCHED", 20, 0, 50, "TOTALTRACKPT_BASICCALOJETSMATCHED", "Events");
  
}


void draw(){
  draw_2D();
  //draw_in_PV_slices();
  //  draw_correlation();
  //draw_pt_eff();
  //draw_light();
  //draw_varymass_fixlifetime();
}
