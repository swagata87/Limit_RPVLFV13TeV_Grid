#include <iostream>
#include <algorithm>
#include "TLatex.h"
#include <iomanip>
#include <vector>
#include "TPad.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TSystem.h"
#include "TImage.h"
#include "TKey.h"
#include "TH1.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TObjArray.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TPostScript.h"
#include <TPaveStats.h>
#include "TLegend.h"
#include <TProfile.h>
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "THStack.h"

int plotGOF() {

  //  TFile *file_toy  = new TFile("workdir/output_masses/Mass_1000_Stage_0_output/higgsCombineTest.GoodnessOfFit.mH120.123456.root");
  TFile *file_toy  = new TFile("/user/mukherjee/out/March29_GOF_AD_Toy/merged/Mass1000.root");
  TFile *file_data  = new TFile("/user/mukherjee/out/March29_GOF_AD_Data/merged/Mass1000.root");
  //  TFile *file_data = new TFile("workdir/output_masses/Mass_1000_Stage_0_output/higgsCombineDATA.GoodnessOfFit.mH120.root");


  //  TH1F *ne = new TH1F("ne", "Num electrons",80,0,20);


  TH1F* h1_GOF_toy  = new TH1F("h1_GOF_toy", "GOF",35,0,7);    //(TH1D*)file_toy->Get("limit/limit");

  double limit;

  TTree *tree = (TTree*)file_toy->Get("limit");
  tree->ResetBranchAddresses();
  tree->SetBranchAddress("limit",&limit);
  int nrEntries = tree->GetEntries();
  for(int entryNr=0;entryNr<nrEntries;entryNr++){
    tree->GetEntry(entryNr);
    std::cout << "limit = " << limit << std::endl;
    h1_GOF_toy->Fill(limit);
  }


  //  std::cout << "h1_GOF_toy " << h1_GOF_toy << std::endl;
  h1_GOF_toy->SetLineColor(kBlack);
  h1_GOF_toy->SetLineWidth(2);
  h1_GOF_toy->GetXaxis()->SetTitle("q_{GOF}");

  
  double limit1;
  TTree *tree1 = (TTree*)file_data->Get("limit");
  tree1->ResetBranchAddresses();
  tree1->SetBranchAddress("limit",&limit1);
  int nrEntries1 = tree1->GetEntries();
  for(int entryNr=0;entryNr<nrEntries1;entryNr++){
    tree1->GetEntry(entryNr);
  }


  //  TH1D* h1_GOF_data = (TH1D*)file_data->Get("limit/limit");
  // std::cout << "h1_GOF_data " << h1_GOF_data << std::endl;
    std::cout << "limit1 = " << limit1 << std::endl;
   

  TArrow *ar3 = new TArrow(limit1,0,limit1,100,0.04,"<|");
  ar3->SetAngle(40);
  ar3->SetLineWidth(2);
  ar3->SetLineColor(4);
  ar3->SetFillColor(4);

  TCanvas* my_canvas = new TCanvas("gof","gof",800,600);
  my_canvas->cd();

  h1_GOF_toy->Draw("HIST");
  ar3->Draw();
  
  TLatex* text_1 = new TLatex(0.46,0.78,"Anderson-Darling");
  text_1->SetNDC();
  text_1->SetTextSize(0.03);
  text_1->SetTextAngle(0);
  text_1->Draw("same");


  // h1_GOF_data->Draw("same");
  my_canvas->Print("gof.pdf");
  return 0;
}
