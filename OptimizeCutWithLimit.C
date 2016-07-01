#include "TSystem.h"
#include "TString.h"
#include "TEnv.h"
#include "TH1.h"
#include "TH1F.h"
#include "TGraphErrors.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TVectorD.h"
#include "TLine.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TMath.h"
#include "TSpline.h"
#include <algorithm>
#include "TGraphAsymmErrors.h"
#include "/home/home1/institut_3a/mukherjee/Limit_RPVLFV13TeV/Environment.h"
#include "TLatex.h"
//std::cout << "Outside mail loop" << std::endl;
using namespace std;
using namespace TMath;

void OptimizeCutWithLimit()
{
  std::cout << "Inside get_expected_limit " << std::endl;
  Char_t mass_dir[200];
  Char_t file_title_exp[200];

  int mass_min=300;
  int mass_inter_0=1600;  
  int mass_max=3500;
  int binning_0=1300;
  int binning_1=1900;
  int mass=mass_min;

  TFile* outfile=new TFile("outfile_RPV_limits.root","recreate");

  double expected_MT_1[200];
  double expected_MT_2[200];
  double expected_MT_3[200];
  double expected_MT_4[200];
  double expected_MT_5[200];
  double expected_MT_6[200];
  double expected_MT_7[200];
  double expected_MT_8[200];
  double expected_MT_9[200];
  double expected_MT_10[200];

  double xs_expected_MT_1[200];
  double xs_expected_MT_2[200];
  double xs_expected_MT_3[200];
  double xs_expected_MT_4[200];
  double xs_expected_MT_5[200];
  double xs_expected_MT_6[200];
  double xs_expected_MT_7[200];
  double xs_expected_MT_8[200];
  double xs_expected_MT_9[200];
  double xs_expected_MT_10[200];

  double masses[200];
  double xsec_NLO[200];
  
  std::cout << "Will initialize" << std::endl;

  for(int k=0; k<200; k++)
    {
      expected_MT_1[k]=0.;
      expected_MT_2[k]=0.;
      expected_MT_3[k]=0.;
      expected_MT_4[k]=0.;
      expected_MT_5[k]=0.;
      expected_MT_6[k]=0.;
      expected_MT_7[k]=0.;
      expected_MT_8[k]=0.;
      expected_MT_9[k]=0.;
      expected_MT_10[k]=0.;

      masses[k]=0.;
      xsec_NLO[k]=0.;
      xs_expected_MT_1[k]=0.;
      xs_expected_MT_2[k]=0.;
      xs_expected_MT_3[k]=0.;
      xs_expected_MT_4[k]=0.;
      xs_expected_MT_5[k]=0.;
      xs_expected_MT_6[k]=0.;
      xs_expected_MT_7[k]=0.;
      xs_expected_MT_8[k]=0.;
      xs_expected_MT_9[k]=0.;
      xs_expected_MT_10[k]=0.;
    }
  
  int counter_masses=0;
  
  mass=mass_min;
  
  std::cout << "Will do expected ! " << std::endl ;
  ////////// expected //////////
  while(mass<=mass_max)
    {
      
      masses[counter_masses]=mass;
      sprintf(file_title_exp,"LQD_001_LLE_001_MSnl_scale_down_%d",(int)mass);
      get_environment(file_title_exp);
      //xsec[counter_masses]=BGcrosssection*1000.*BGweight;
      xsec_NLO[counter_masses]=BGcrosssection*BGweight;
      //std::cout<< "Read xs for 0.1 coupling for mass " << mass << std::endl;

      sprintf(mass_dir,"/merged/Mass%i.root",mass);   
      TString basedir_MT_1="/user/mukherjee/out/RPVExpectedLimit_MT_1/";
      TString basedir_MT_2="/user/mukherjee/out/RPVExpectedLimit_MT_2/";
      TString basedir_MT_3="/user/mukherjee/out/RPVExpectedLimit_MT_3/";
      TString basedir_MT_4="/user/mukherjee/out/RPVExpectedLimit_MT_4/";
      TString basedir_MT_5="/user/mukherjee/out/RPVExpectedLimit_MT_5/";
      TString basedir_MT_6="/user/mukherjee/out/RPVExpectedLimit_MT_6/";
      TString basedir_MT_7="/user/mukherjee/out/RPVExpectedLimit_MT_7/";
      TString basedir_MT_8="/user/mukherjee/out/RPVExpectedLimit_MT_8/";
      TString basedir_MT_9="/user/mukherjee/out/RPVExpectedLimit_MT_9/";
      TString basedir_MT_10="/user/mukherjee/out/RPVExpectedLimit_MT_10/";

      TString *massdir=new TString(mass_dir);
      TString filename_MT_1=basedir_MT_1+*massdir;
      TString filename_MT_2=basedir_MT_2+*massdir;
      TString filename_MT_3=basedir_MT_3+*massdir;
      TString filename_MT_4=basedir_MT_4+*massdir;
      TString filename_MT_5=basedir_MT_5+*massdir;
      TString filename_MT_6=basedir_MT_6+*massdir;
      TString filename_MT_7=basedir_MT_7+*massdir;
      TString filename_MT_8=basedir_MT_8+*massdir;
      TString filename_MT_9=basedir_MT_9+*massdir;
      TString filename_MT_10=basedir_MT_10+*massdir;

      // TString filename_observed = basedir+in_dir+*massdir+"/condor/observed.root";

      double limit;
      
      TFile *expected_file_MT_1=new TFile(filename_MT_1);
      TTree *tree_MT_1 = (TTree*)expected_file_MT_1->Get("limit");
      tree_MT_1->ResetBranchAddresses();
      tree_MT_1->SetBranchAddress("limit",&limit);
      int nrEntries_MT_1 = tree_MT_1->GetEntries();
      double limits_MT_1[10000];
      for(int entryNr=0;entryNr<nrEntries_MT_1;entryNr++){
	tree_MT_1->GetEntry(entryNr);
	limits_MT_1[entryNr]=limit;
      }
      tree_MT_1->ResetBranchAddresses();
      std::sort(limits_MT_1, limits_MT_1 + nrEntries_MT_1);
      expected_MT_1[counter_masses]=limits_MT_1[Nint(nrEntries_MT_1*0.5)];
      delete tree_MT_1;
      delete expected_file_MT_1;
      //delete massdir;
      
      xs_expected_MT_1[counter_masses]=expected_MT_1[counter_masses]*xsec_NLO[counter_masses]; ///Aeff[counter_masses];
      cout << "MT 1 : Mass" << mass << "  &   " << xs_expected_MT_1[counter_masses]  <<  " \\\\ "    << endl; 
      //counter_masses++;

      ////
      TFile *expected_file_MT_2=new TFile(filename_MT_2);
      TTree *tree_MT_2 = (TTree*)expected_file_MT_2->Get("limit");
      tree_MT_2->ResetBranchAddresses();
      tree_MT_2->SetBranchAddress("limit",&limit);
      int nrEntries_MT_2 = tree_MT_2->GetEntries();
      double limits_MT_2[10000];
      for(int entryNr=0;entryNr<nrEntries_MT_2;entryNr++){
	tree_MT_2->GetEntry(entryNr);
	limits_MT_2[entryNr]=limit;
      }
      tree_MT_2->ResetBranchAddresses();
      std::sort(limits_MT_2, limits_MT_2 + nrEntries_MT_2);
      expected_MT_2[counter_masses]=limits_MT_2[Nint(nrEntries_MT_2*0.5)];
      delete tree_MT_2;
      delete expected_file_MT_2;
      xs_expected_MT_2[counter_masses]=expected_MT_2[counter_masses]*xsec_NLO[counter_masses]; ///Aeff[counter_masses];
      cout << "MT 2 : Mass" << mass << "  &   " << xs_expected_MT_2[counter_masses]  <<  " \\\\ "    << endl; 
      ///counter_masses++;
      ////

      ////
      TFile *expected_file_MT_3=new TFile(filename_MT_3);
      TTree *tree_MT_3 = (TTree*)expected_file_MT_3->Get("limit");
      tree_MT_3->ResetBranchAddresses();
      tree_MT_3->SetBranchAddress("limit",&limit);
      int nrEntries_MT_3 = tree_MT_3->GetEntries();
      double limits_MT_3[10000];
      for(int entryNr=0;entryNr<nrEntries_MT_3;entryNr++){
	tree_MT_3->GetEntry(entryNr);
	limits_MT_3[entryNr]=limit;
      }
      tree_MT_3->ResetBranchAddresses();
      std::sort(limits_MT_3, limits_MT_3 + nrEntries_MT_3);
      expected_MT_3[counter_masses]=limits_MT_3[Nint(nrEntries_MT_3*0.5)];
      delete tree_MT_3;
      delete expected_file_MT_3;
      xs_expected_MT_3[counter_masses]=expected_MT_3[counter_masses]*xsec_NLO[counter_masses]; ///Aeff[counter_masses];
      cout << "MT 3 : Mass" << mass << "  &   " << xs_expected_MT_3[counter_masses]  <<  " \\\\ "    << endl; 
      //////

      ////
      TFile *expected_file_MT_4=new TFile(filename_MT_4);
      TTree *tree_MT_4 = (TTree*)expected_file_MT_4->Get("limit");
      tree_MT_4->ResetBranchAddresses();
      tree_MT_4->SetBranchAddress("limit",&limit);
      int nrEntries_MT_4 = tree_MT_4->GetEntries();
      double limits_MT_4[10000];
      for(int entryNr=0;entryNr<nrEntries_MT_4;entryNr++){
	tree_MT_4->GetEntry(entryNr);
	limits_MT_4[entryNr]=limit;
      }
      tree_MT_4->ResetBranchAddresses();
      std::sort(limits_MT_4, limits_MT_4 + nrEntries_MT_4);
      expected_MT_4[counter_masses]=limits_MT_4[Nint(nrEntries_MT_4*0.5)];
      delete tree_MT_4;
      delete expected_file_MT_4;
      xs_expected_MT_4[counter_masses]=expected_MT_4[counter_masses]*xsec_NLO[counter_masses]; ///Aeff[counter_masses];
      cout << "MT 4 : Mass" << mass << "  &   " << xs_expected_MT_4[counter_masses]  <<  " \\\\ "    << endl; 
      //////

      ////
      TFile *expected_file_MT_5=new TFile(filename_MT_5);
      TTree *tree_MT_5 = (TTree*)expected_file_MT_5->Get("limit");
      tree_MT_5->ResetBranchAddresses();
      tree_MT_5->SetBranchAddress("limit",&limit);
      int nrEntries_MT_5 = tree_MT_5->GetEntries();
      double limits_MT_5[10000];
      for(int entryNr=0;entryNr<nrEntries_MT_5;entryNr++){
	tree_MT_5->GetEntry(entryNr);
	limits_MT_5[entryNr]=limit;
      }
      tree_MT_5->ResetBranchAddresses();
      std::sort(limits_MT_5, limits_MT_5 + nrEntries_MT_5);
      expected_MT_5[counter_masses]=limits_MT_5[Nint(nrEntries_MT_5*0.5)];
      delete tree_MT_5;
      delete expected_file_MT_5;
      xs_expected_MT_5[counter_masses]=expected_MT_5[counter_masses]*xsec_NLO[counter_masses]; ///Aeff[counter_masses];
      cout << "MT 5 : Mass" << mass << "  &   " << xs_expected_MT_5[counter_masses]  <<  " \\\\ "    << endl; 
      //////

      ////
      TFile *expected_file_MT_6=new TFile(filename_MT_6);
      TTree *tree_MT_6 = (TTree*)expected_file_MT_6->Get("limit");
      tree_MT_6->ResetBranchAddresses();
      tree_MT_6->SetBranchAddress("limit",&limit);
      int nrEntries_MT_6 = tree_MT_6->GetEntries();
      double limits_MT_6[10000];
      for(int entryNr=0;entryNr<nrEntries_MT_6;entryNr++){
	tree_MT_6->GetEntry(entryNr);
	limits_MT_6[entryNr]=limit;
      }
      tree_MT_6->ResetBranchAddresses();
      std::sort(limits_MT_6, limits_MT_6 + nrEntries_MT_6);
      expected_MT_6[counter_masses]=limits_MT_6[Nint(nrEntries_MT_6*0.5)];
      delete tree_MT_6;
      delete expected_file_MT_6;
      xs_expected_MT_6[counter_masses]=expected_MT_6[counter_masses]*xsec_NLO[counter_masses]; ///Aeff[counter_masses];
      cout << "MT 6 : Mass" << mass << "  &   " << xs_expected_MT_6[counter_masses]  <<  " \\\\ "    << endl; 
      //////

      ////                                                                                                                                              
      TFile *expected_file_MT_7=new TFile(filename_MT_7);
      TTree *tree_MT_7 = (TTree*)expected_file_MT_7->Get("limit");
      tree_MT_7->ResetBranchAddresses();
      tree_MT_7->SetBranchAddress("limit",&limit);
      int nrEntries_MT_7 = tree_MT_7->GetEntries();
      double limits_MT_7[10000];
      for(int entryNr=0;entryNr<nrEntries_MT_7;entryNr++){
        tree_MT_7->GetEntry(entryNr);
        limits_MT_7[entryNr]=limit;
      }
      tree_MT_7->ResetBranchAddresses();
      std::sort(limits_MT_7, limits_MT_7 + nrEntries_MT_7);
      expected_MT_7[counter_masses]=limits_MT_7[Nint(nrEntries_MT_7*0.5)];
      delete tree_MT_7;
      delete expected_file_MT_7;
      xs_expected_MT_7[counter_masses]=expected_MT_7[counter_masses]*xsec_NLO[counter_masses]; ///Aeff[counter_masses];                                
      cout << "MT 7 : Mass" << mass << "  &   " << xs_expected_MT_7[counter_masses]  <<  " \\\\ "    << endl;
      //////             

      ////                                                                                                                                              
      TFile *expected_file_MT_8=new TFile(filename_MT_8);
      TTree *tree_MT_8 = (TTree*)expected_file_MT_8->Get("limit");
      tree_MT_8->ResetBranchAddresses();
      tree_MT_8->SetBranchAddress("limit",&limit);
      int nrEntries_MT_8 = tree_MT_8->GetEntries();
      double limits_MT_8[10000];
      for(int entryNr=0;entryNr<nrEntries_MT_8;entryNr++){
        tree_MT_8->GetEntry(entryNr);
        limits_MT_8[entryNr]=limit;
      }
      tree_MT_8->ResetBranchAddresses();
      std::sort(limits_MT_8, limits_MT_8 + nrEntries_MT_8);
      expected_MT_8[counter_masses]=limits_MT_8[Nint(nrEntries_MT_8*0.5)];
      delete tree_MT_8;
      delete expected_file_MT_8;
      xs_expected_MT_8[counter_masses]=expected_MT_8[counter_masses]*xsec_NLO[counter_masses]; ///Aeff[counter_masses];                                
      cout << "MT 8 : Mass" << mass << "  &   " << xs_expected_MT_8[counter_masses]  <<  " \\\\ "    << endl;
      //////             

      ////                                                                                                                                              
      TFile *expected_file_MT_9=new TFile(filename_MT_9);
      TTree *tree_MT_9 = (TTree*)expected_file_MT_9->Get("limit");
      tree_MT_9->ResetBranchAddresses();
      tree_MT_9->SetBranchAddress("limit",&limit);
      int nrEntries_MT_9 = tree_MT_9->GetEntries();
      double limits_MT_9[10000];
      for(int entryNr=0;entryNr<nrEntries_MT_9;entryNr++){
        tree_MT_9->GetEntry(entryNr);
        limits_MT_9[entryNr]=limit;
      }
      tree_MT_9->ResetBranchAddresses();
      std::sort(limits_MT_9, limits_MT_9 + nrEntries_MT_9);
      expected_MT_9[counter_masses]=limits_MT_9[Nint(nrEntries_MT_9*0.5)];
      delete tree_MT_9;
      delete expected_file_MT_9;
      xs_expected_MT_9[counter_masses]=expected_MT_9[counter_masses]*xsec_NLO[counter_masses]; ///Aeff[counter_masses];                                
      cout << "MT 9 : Mass" << mass << "  &   " << xs_expected_MT_9[counter_masses]  <<  " \\\\ "    << endl;
      //////             

      ////                                                                                                                                      
      TFile *expected_file_MT_10=new TFile(filename_MT_10);
      TTree *tree_MT_10 = (TTree*)expected_file_MT_10->Get("limit");
      tree_MT_10->ResetBranchAddresses();
      tree_MT_10->SetBranchAddress("limit",&limit);
      int nrEntries_MT_10 = tree_MT_10->GetEntries();
      double limits_MT_10[10000];
      for(int entryNr=0;entryNr<nrEntries_MT_10;entryNr++){
        tree_MT_10->GetEntry(entryNr);
        limits_MT_10[entryNr]=limit;
      }
      tree_MT_10->ResetBranchAddresses();
      std::sort(limits_MT_10, limits_MT_10 + nrEntries_MT_10);
      expected_MT_10[counter_masses]=limits_MT_10[Nint(nrEntries_MT_10*0.5)];
      delete tree_MT_10;
      delete expected_file_MT_10;
      xs_expected_MT_10[counter_masses]=expected_MT_10[counter_masses]*xsec_NLO[counter_masses]; ///Aeff[counter_masses];                                
      cout << "MT 10 : Mass" << mass << "  &   " << xs_expected_MT_10[counter_masses]  <<  " \\\\ "    << endl;
      //////             
      
      delete massdir;
      counter_masses++;
      ////



      if(mass<mass_inter_0){mass+=binning_0;}
      	  else mass+=binning_1;
    }

  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);  
  gStyle->SetPadTopMargin(0.05);   
  gStyle->SetTitleXSize(0.05);
  gStyle->SetTitleXOffset(1.05);
  gStyle->SetTitleYSize(0.05);
  gStyle->SetTitleYOffset(1.05);

  TCanvas* total = new TCanvas("total","total",800,800);
  total->cd();
  total->SetLogy();
  
  TGraph *graph_expected_total_MT_1 = new TGraph(counter_masses,masses,xs_expected_MT_1);
  //graph_expected_total_MT_1->GetXaxis()->SetRangeUser(mass_min,mass_max);
  //graph_expected_total_MT_1->GetYaxis()->SetRangeUser(0.01,10000.);
  //gPad->SetLogy();
  graph_expected_total_MT_1->SetTitle("");
  graph_expected_total_MT_1->SetMarkerStyle(20);
  graph_expected_total_MT_1->SetMarkerColor(kBlack);
  graph_expected_total_MT_1->SetLineColor(kBlack);
  graph_expected_total_MT_1->SetLineWidth(2);
  graph_expected_total_MT_1->SetLineStyle(1);    
  //graph_expected->GetXaxis()->SetTitle("M_{#tilde{#nu_{#tau}}} [TeV]");
  //graph_expetced->GetYaxis()->SetTitle("#frac{#sigma_{95%CL}}{#sigma_{sig}}");    
  graph_expected_total_MT_1->GetXaxis()->SetTitleFont(42);
  graph_expected_total_MT_1->GetYaxis()->SetTitleFont(42);
  graph_expected_total_MT_1->GetXaxis()->SetLabelFont(42);
  graph_expected_total_MT_1->GetYaxis()->SetLabelFont(42);    
  graph_expected_total_MT_1->GetXaxis()->SetTitle("M_{#tilde{#nu}_{#tau}} (GeV)");
  graph_expected_total_MT_1->GetYaxis()->SetTitle("#sigma^{prod}_{#tilde{#nu_{#tau}}} #times BR ( #tilde{#nu_{#tau}} #rightarrow #mu#tau_h ) (fb)");
  graph_expected_total_MT_1->GetXaxis()->SetRangeUser(mass_min,mass_max);
  graph_expected_total_MT_1->GetYaxis()->SetRangeUser(0.01,10000.);
  graph_expected_total_MT_1->Draw("Apl");   
  //  graph_expected_total_MT_1->Draw("pl,same");  
  
  /////////
  TGraph *graph_expected_total_MT_2 = new TGraph(counter_masses,masses,xs_expected_MT_2);
  //graph_expected_total_MT_2->GetXaxis()->SetRangeUser(mass_min,mass_max);
  //graph_expected_total_MT_2->GetYaxis()->SetRangeUser(1,10000.);
  //gPad->SetLogy();
  graph_expected_total_MT_2->SetTitle("");
  graph_expected_total_MT_2->SetMarkerStyle(20);
  graph_expected_total_MT_2->SetMarkerColor(kRed);
  graph_expected_total_MT_2->SetLineColor(kRed);
  graph_expected_total_MT_2->SetLineWidth(2);
  graph_expected_total_MT_2->SetLineStyle(2);    
  //graph_expected->GetXaxis()->SetTitle("M_{#tilde{#nu_{#tau}}} [TeV]");
  //graph_expetced->GetYaxis()->SetTitle("#frac{#sigma_{95%CL}}{#sigma_{sig}}");    
  graph_expected_total_MT_2->GetXaxis()->SetTitleFont(42);
  graph_expected_total_MT_2->GetYaxis()->SetTitleFont(42);
  graph_expected_total_MT_2->GetXaxis()->SetLabelFont(42);
  graph_expected_total_MT_2->GetYaxis()->SetLabelFont(42);    
  graph_expected_total_MT_2->GetXaxis()->SetTitle("M_{#tilde{#nu}_{#tau}} (GeV)");
  graph_expected_total_MT_2->GetYaxis()->SetTitle("#sigma^{prod}_{#tilde{#nu_{#tau}}} #times BR ( #tilde{#nu_{#tau}} #rightarrow #mu#tau_h ) (fb)");
  graph_expected_total_MT_2->GetXaxis()->SetRangeUser(mass_min,mass_max);
  graph_expected_total_MT_2->GetYaxis()->SetRangeUser(0.01,10000.);
  //graph_expected_total_MT_2->Draw("Apl");   
  graph_expected_total_MT_2->Draw("pl,same");  
  /////////

  /////////
  TGraph *graph_expected_total_MT_3 = new TGraph(counter_masses,masses,xs_expected_MT_3);
  graph_expected_total_MT_3->SetTitle("");
  graph_expected_total_MT_3->SetMarkerStyle(20);
  graph_expected_total_MT_3->SetMarkerColor(kGreen);
  graph_expected_total_MT_3->SetLineColor(kGreen);
  graph_expected_total_MT_3->SetLineWidth(2);
  graph_expected_total_MT_3->SetLineStyle(3);    
  graph_expected_total_MT_3->GetXaxis()->SetTitleFont(42);
  graph_expected_total_MT_3->GetYaxis()->SetTitleFont(42);
  graph_expected_total_MT_3->GetXaxis()->SetLabelFont(42);
  graph_expected_total_MT_3->GetYaxis()->SetLabelFont(42);    
  graph_expected_total_MT_3->GetXaxis()->SetTitle("M_{#tilde{#nu}_{#tau}} (GeV)");
  graph_expected_total_MT_3->GetYaxis()->SetTitle("#sigma^{prod}_{#tilde{#nu_{#tau}}} #times BR ( #tilde{#nu_{#tau}} #rightarrow #mu#tau_h ) (fb)");
  graph_expected_total_MT_3->GetXaxis()->SetRangeUser(mass_min,mass_max);
  graph_expected_total_MT_3->GetYaxis()->SetRangeUser(0.01,10000.);
  graph_expected_total_MT_3->Draw("pl,same");  
  /////////

  /////////
  TGraph *graph_expected_total_MT_4 = new TGraph(counter_masses,masses,xs_expected_MT_4);
  graph_expected_total_MT_4->SetTitle("");
  graph_expected_total_MT_4->SetMarkerStyle(20);
  graph_expected_total_MT_4->SetMarkerColor(kMagenta+2);
  graph_expected_total_MT_4->SetLineColor(kMagenta+2);
  graph_expected_total_MT_4->SetLineWidth(2);
  graph_expected_total_MT_4->SetLineStyle(4);    
  graph_expected_total_MT_4->GetXaxis()->SetTitleFont(42);
  graph_expected_total_MT_4->GetYaxis()->SetTitleFont(42);
  graph_expected_total_MT_4->GetXaxis()->SetLabelFont(42);
  graph_expected_total_MT_4->GetYaxis()->SetLabelFont(42);    
  graph_expected_total_MT_4->GetXaxis()->SetTitle("M_{#tilde{#nu}_{#tau}} (GeV)");
  graph_expected_total_MT_4->GetYaxis()->SetTitle("#sigma^{prod}_{#tilde{#nu_{#tau}}} #times BR ( #tilde{#nu_{#tau}} #rightarrow #mu#tau_h ) (fb)");
  graph_expected_total_MT_4->GetXaxis()->SetRangeUser(mass_min,mass_max);
  graph_expected_total_MT_4->GetYaxis()->SetRangeUser(0.01,10000.);
  graph_expected_total_MT_4->Draw("pl,same");  
  /////////

  /////////
  TGraph *graph_expected_total_MT_5 = new TGraph(counter_masses,masses,xs_expected_MT_5);
  graph_expected_total_MT_5->SetTitle("");
  graph_expected_total_MT_5->SetMarkerStyle(20);
  graph_expected_total_MT_5->SetMarkerColor(kBlue+2);
  graph_expected_total_MT_5->SetLineColor(kBlue+2);
  graph_expected_total_MT_5->SetLineWidth(2);
  graph_expected_total_MT_5->SetLineStyle(5);    
  graph_expected_total_MT_5->GetXaxis()->SetTitleFont(42);
  graph_expected_total_MT_5->GetYaxis()->SetTitleFont(42);
  graph_expected_total_MT_5->GetXaxis()->SetLabelFont(42);
  graph_expected_total_MT_5->GetYaxis()->SetLabelFont(42);    
  graph_expected_total_MT_5->GetXaxis()->SetTitle("M_{#tilde{#nu}_{#tau}} (GeV)");
  graph_expected_total_MT_5->GetYaxis()->SetTitle("#sigma^{prod}_{#tilde{#nu_{#tau}}} #times BR ( #tilde{#nu_{#tau}} #rightarrow #mu#tau_h ) (fb)");
  graph_expected_total_MT_5->GetXaxis()->SetRangeUser(mass_min,mass_max);
  graph_expected_total_MT_5->GetYaxis()->SetRangeUser(0.01,10000.);
  graph_expected_total_MT_5->Draw("pl,same");  
  /////////

  /////////
  TGraph *graph_expected_total_MT_6 = new TGraph(counter_masses,masses,xs_expected_MT_6);
  graph_expected_total_MT_6->SetTitle("");
  graph_expected_total_MT_6->SetMarkerStyle(20);
  graph_expected_total_MT_6->SetMarkerColor(kCyan);
  graph_expected_total_MT_6->SetLineColor(kCyan);
  graph_expected_total_MT_6->SetLineWidth(2);			
  graph_expected_total_MT_6->SetLineStyle(6);    
  graph_expected_total_MT_6->GetXaxis()->SetTitleFont(42);
  graph_expected_total_MT_6->GetYaxis()->SetTitleFont(42);
  graph_expected_total_MT_6->GetXaxis()->SetLabelFont(42);
  graph_expected_total_MT_6->GetYaxis()->SetLabelFont(42);    
  graph_expected_total_MT_6->GetXaxis()->SetTitle("M_{#tilde{#nu}_{#tau}} (GeV)");
  graph_expected_total_MT_6->GetYaxis()->SetTitle("#sigma^{prod}_{#tilde{#nu_{#tau}}} #times BR ( #tilde{#nu_{#tau}} #rightarrow #mu#tau_h ) (fb)");
  graph_expected_total_MT_6->GetXaxis()->SetRangeUser(mass_min,mass_max);
  graph_expected_total_MT_6->GetYaxis()->SetRangeUser(0.01,10000.);
  graph_expected_total_MT_6->Draw("pl,same");  
  /////////

  /////////
  TGraph *graph_expected_total_MT_7 = new TGraph(counter_masses,masses,xs_expected_MT_7);
  graph_expected_total_MT_7->SetTitle("");
  graph_expected_total_MT_7->SetMarkerStyle(20);
  graph_expected_total_MT_7->SetMarkerColor(kCyan+2);
  graph_expected_total_MT_7->SetLineColor(kCyan+2);
  graph_expected_total_MT_7->SetLineWidth(2);
  graph_expected_total_MT_7->SetLineStyle(7);    
  graph_expected_total_MT_7->GetXaxis()->SetTitleFont(42);
  graph_expected_total_MT_7->GetYaxis()->SetTitleFont(42);
  graph_expected_total_MT_7->GetXaxis()->SetLabelFont(42);
  graph_expected_total_MT_7->GetYaxis()->SetLabelFont(42);    
  graph_expected_total_MT_7->GetXaxis()->SetTitle("M_{#tilde{#nu}_{#tau}} (GeV)");
  graph_expected_total_MT_7->GetYaxis()->SetTitle("#sigma^{prod}_{#tilde{#nu_{#tau}}} #times BR ( #tilde{#nu_{#tau}} #rightarrow #mu#tau_h ) (fb)");
  graph_expected_total_MT_7->GetXaxis()->SetRangeUser(mass_min,mass_max);
  graph_expected_total_MT_7->GetYaxis()->SetRangeUser(0.01,10000.);
  graph_expected_total_MT_7->Draw("pl,same");  
  /////////

  /////////
  TGraph *graph_expected_total_MT_8 = new TGraph(counter_masses,masses,xs_expected_MT_8);
  graph_expected_total_MT_8->SetTitle("");
  graph_expected_total_MT_8->SetMarkerStyle(20);
  graph_expected_total_MT_8->SetMarkerColor(kViolet);
  graph_expected_total_MT_8->SetLineColor(kViolet);
  graph_expected_total_MT_8->SetLineWidth(2);
  graph_expected_total_MT_8->SetLineStyle(8);    
  graph_expected_total_MT_8->GetXaxis()->SetTitleFont(42);
  graph_expected_total_MT_8->GetYaxis()->SetTitleFont(42);
  graph_expected_total_MT_8->GetXaxis()->SetLabelFont(42);
  graph_expected_total_MT_8->GetYaxis()->SetLabelFont(42);    
  graph_expected_total_MT_8->GetXaxis()->SetTitle("M_{#tilde{#nu}_{#tau}} (GeV)");
  graph_expected_total_MT_8->GetYaxis()->SetTitle("#sigma^{prod}_{#tilde{#nu_{#tau}}} #times BR ( #tilde{#nu_{#tau}} #rightarrow #mu#tau_h ) (fb)");
  graph_expected_total_MT_8->GetXaxis()->SetRangeUser(mass_min,mass_max);
  graph_expected_total_MT_8->GetYaxis()->SetRangeUser(0.01,10000.);
  graph_expected_total_MT_8->Draw("pl,same");  
  /////////

  /////////
  TGraph *graph_expected_total_MT_9 = new TGraph(counter_masses,masses,xs_expected_MT_9);
  graph_expected_total_MT_9->SetTitle("");
  graph_expected_total_MT_9->SetMarkerStyle(20);
  graph_expected_total_MT_9->SetMarkerColor(kRed+2);
  graph_expected_total_MT_9->SetLineColor(kRed+2);
  graph_expected_total_MT_9->SetLineWidth(2);
  graph_expected_total_MT_9->SetLineStyle(9);    
  graph_expected_total_MT_9->GetXaxis()->SetTitleFont(42);
  graph_expected_total_MT_9->GetYaxis()->SetTitleFont(42);
  graph_expected_total_MT_9->GetXaxis()->SetLabelFont(42);
  graph_expected_total_MT_9->GetYaxis()->SetLabelFont(42);    
  graph_expected_total_MT_9->GetXaxis()->SetTitle("M_{#tilde{#nu}_{#tau}} (GeV)");
  graph_expected_total_MT_9->GetYaxis()->SetTitle("#sigma^{prod}_{#tilde{#nu_{#tau}}} #times BR ( #tilde{#nu_{#tau}} #rightarrow #mu#tau_h ) (fb)");
  graph_expected_total_MT_9->GetXaxis()->SetRangeUser(mass_min,mass_max);
  graph_expected_total_MT_9->GetYaxis()->SetRangeUser(0.01,10000.);
  graph_expected_total_MT_9->Draw("pl,same");  
  /////////

  /////////
  TGraph *graph_expected_total_MT_10 = new TGraph(counter_masses,masses,xs_expected_MT_10);
  graph_expected_total_MT_10->SetTitle("");
  graph_expected_total_MT_10->SetMarkerStyle(20);
  graph_expected_total_MT_10->SetMarkerColor(kCyan+4);
  graph_expected_total_MT_10->SetLineColor(kCyan+4);
  graph_expected_total_MT_10->SetLineWidth(2);
  graph_expected_total_MT_10->SetLineStyle(10);    
  graph_expected_total_MT_10->GetXaxis()->SetTitleFont(42);
  graph_expected_total_MT_10->GetYaxis()->SetTitleFont(42);
  graph_expected_total_MT_10->GetXaxis()->SetLabelFont(42);
  graph_expected_total_MT_10->GetYaxis()->SetLabelFont(42);    
  graph_expected_total_MT_10->GetXaxis()->SetTitle("M_{#tilde{#nu}_{#tau}} (GeV)");
  graph_expected_total_MT_10->GetYaxis()->SetTitle("#sigma^{prod}_{#tilde{#nu_{#tau}}} #times BR ( #tilde{#nu_{#tau}} #rightarrow #mu#tau_h ) (fb)");
  graph_expected_total_MT_10->GetXaxis()->SetRangeUser(mass_min,mass_max);
  graph_expected_total_MT_10->GetYaxis()->SetRangeUser(0.01,10000.);
  graph_expected_total_MT_10->Draw("pl,same");  
  /////////

  std::cout<< "Prepare to draw legend" << std::endl;
  TLegend *leg_total = new TLegend(0.45,0.55,0.95,0.95);
  leg_total->SetFillColor(0);
  leg_total->SetTextFont(42);
  leg_total->SetTextSize(0.032);    
  leg_total->AddEntry(graph_expected_total_MT_1, "MT 1","pl");
  leg_total->AddEntry(graph_expected_total_MT_2, "MT 2","pl");
  leg_total->AddEntry(graph_expected_total_MT_3, "MT 3","pl");
  leg_total->AddEntry(graph_expected_total_MT_4, "MT 4","pl");
  leg_total->AddEntry(graph_expected_total_MT_5, "MT 5","pl");
  leg_total->AddEntry(graph_expected_total_MT_6, "MT 6","pl");
  leg_total->AddEntry(graph_expected_total_MT_7, "MT 7","pl");
  leg_total->AddEntry(graph_expected_total_MT_8, "MT 8","pl");
  leg_total->AddEntry(graph_expected_total_MT_9, "MT 9","pl");
  leg_total->AddEntry(graph_expected_total_MT_10, "MT 10","pl");

  leg_total->Draw("same");
    
  //TLatex* CMS_text = new TLatex(0.20,0.88,"CMS");
  TLatex* CMS_text = new TLatex(0.24,0.88,"CMS");
  CMS_text->SetNDC();
  CMS_text->SetTextSize(0.05);
  CMS_text->SetTextAngle(0);
  CMS_text->Draw("same");
  
  TLatex* CMS_text_2 = new TLatex(0.20,0.83,"Preliminary");
  //TLatex* CMS_text_2 = new TLatex(0.20,0.83," ");
  CMS_text_2->SetNDC();
  CMS_text_2->SetTextFont(42);
  CMS_text_2->SetTextSize(0.05);
  CMS_text_2->SetTextAngle(0);
  CMS_text_2->Draw("same");    
  
  TLatex* lumiText = new TLatex(0.95,0.975,"2.7 fb^{-1} (13 TeV)");
  lumiText->SetNDC();
  lumiText->SetTextFont(42);
  lumiText->SetTextSize(0.04);
  lumiText->SetTextAlign(32);
  lumiText->Draw("same");     
  
}

/*
    outfile->cd();
    //}
    graph_observed_total->Write("limit_observed");
    graph_expected_total_MT_1->Write("limit_expected");    
    total->Write("limit_plot");
    graph_expected_68_up_total->Write("limit_68_up");
    graph_expected_68_down_total->Write("limit_68_down");    
    grshade_95_total->Write("limit_95_shade");
}
*/






//  LocalWords:  endl
