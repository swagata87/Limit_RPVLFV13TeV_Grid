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
#include "/home/home1/institut_3a/mukherjee/EMU_Limit_2016/Limit_RPVLFV13TeV_Grid/Environment.h"
#include "TLatex.h"
//std::cout << "Outside mail loop" << std::endl;
using namespace std;
using namespace TMath;

void get_expected_limit_RPV()
{

  std::cout << "Inside get_expected_limit " << std::endl;
  Char_t mass_dir[200];
  Char_t mass_dir_exp[200];

  Char_t file_title[500];
  Char_t file_title_exp[500];

  Char_t file_title_2[500];
  Char_t file_title_3[500];

  int mass_min=200;
  int mass_inter_0=980;  
  int mass_inter_1=1020;
  int mass_inter_2=1700;  
  int mass_inter_3=2800;
  int mass_inter_4=3000;
  int mass_max=5000;

  int binning_0=20;
  int binning_1=40;
  int binning_2=20;
  int binning_3=100;  
  int binning_4=200;  
  int binning_5=100;

  ///// Expected Limit /////
  int mass_min_exp=200;
  int mass_inter_0_exp=1800;
  int mass_inter_1_exp=2000;
  int mass_inter_2_exp=2800;
  int mass_inter_3_exp=3200;
  int mass_inter_4_exp=4200;
  int mass_max_exp=5000;

  int binning_0_exp=100;
  int binning_1_exp=100;
  int binning_2_exp=100;
  int binning_3_exp=100;
  int binning_4_exp=100;
  int binning_5_exp=100;


  ///// Other /////
  /*
  int mass_min_other=200;
  int mass_inter_0_other=1800;
  int mass_inter_1_other=2000;
  int mass_inter_2_other=3000;
  int mass_inter_3_other=3200;
  int mass_inter_4_other=3400;
  int mass_max_other=4000;

  int binning_0_other=100;
  int binning_1_other=200;
  int binning_2_other=200;
  int binning_3_other=200;
  int binning_4_other=200;
  int binning_5_other=200;
  */
  //////////////////////////

  int mass=mass_min;
  TFile* outfile=new TFile("outfile_RPV_limits.root","recreate");

  ofstream median;
  median.open ("median.txt");
  ofstream upper_68;
  upper_68.open ("upper_68.txt"); 
  ofstream lower_68;
  lower_68.open ("lower_68.txt"); 
  ofstream upper_95;
  upper_95.open ("upper_95.txt"); 
  ofstream lower_95;
  lower_95.open ("lower_95.txt");  

  ofstream observed_limit;
  observed_limit.open ("observed.txt");   

  ofstream observed_limit_mass_kM;
  observed_limit_mass_kM.open ("observed_limit_mass_kM.txt");     
  ofstream expected_limit_mass_kM;
  expected_limit_mass_kM.open ("expected_limit_mass_kM.txt");  

  ofstream observed_limit_xsec;
  observed_limit_xsec.open ("observed_limit_xsec.txt");
  ofstream expected_limit_xsec;
  expected_limit_xsec.open ("expected_limit_xsec.txt");  

  double expected[200];
  double observed[200];  
  double expected_68_up[200];
  double expected_68_down[200];
  double expected_95_up[200];
  double expected_95_down[200];  
  double xs_expected[200];
  double xs_observed[200];  
  double xs_expected_68_up[200];
  double xs_expected_68_down[200];   
  double xs_expected_95_up[200];
  double xs_expected_95_down[200];  

  double masses[200];
  double masses_exp[200];
  double xsec_NLO[200];
  double xsec_NLO_exp[200];

  double xsec_NLO_2[200];
  double xsec_NLO_3[200];


  std::cout << "Will initialize" << std::endl;

  for(int k=0; k<200; k++)
    {
      expected[k]=0.;
      observed[k]=0.;  
      expected_68_up[k]=0.;
      expected_68_down[k]=0.;
      expected_95_up[k]=0.;
      expected_95_down[k]=0.;  
      masses[k]=0.;
      masses_exp[k]=0.; 
      //xsec[k]=0.;
      xsec_NLO[k]=0.;
      xsec_NLO_exp[k]=0.;
      xsec_NLO_2[k]=0.;
      xsec_NLO_3[k]=0.;

      xs_expected[k]=0.;
      xs_observed[k]=0.;  
      xs_expected_68_up[k]=0.;
      xs_expected_68_down[k]=0.;   
      xs_expected_95_up[k]=0.;
      xs_expected_95_down[k]=0.;  
    }

  int counter_masses=0;
  //  int counter_masses_other=0;
  int counter_masses_exp=0;

  double kM=0.;
  double kM_exp=0.;


  while(mass<=mass_max)
    {
      //    std::cout << "Will do file_title_2" << std::endl;
      sprintf(file_title_2,"LQD_01_LLE_01_MSnl_scale_down_%d",(int)mass);
      get_environment(file_title_2);
      xsec_NLO_2[counter_masses]=BGcrosssection ;// *BGweight;
      // std::cout << "Read xs for 0.1 coupling for mass " << mass << "  " << xsec_NLO_2[counter_masses]  << std::endl;
      counter_masses++;
      
      if(mass<mass_inter_0){mass+=binning_0;}
      else { 
        if(mass<mass_inter_1) mass+=binning_1;
        else 
	  {
	    if(mass<mass_inter_2)mass+=binning_2;
	    else 
	      {
		if(mass<mass_inter_3) mass+=binning_3;
		else 
		  {
		    if(mass<mass_inter_4) mass+=binning_4;
		    else mass+=binning_5;
		  }
	      }
	  }
      }
    }
  
  counter_masses=0;
  mass=mass_min;

  /*
  while(mass<=mass_max)
    {
      //      std::cout << "Will do file_title_3" << std::endl;
      sprintf(file_title_3,"LQD_02_LLE_02_MSnl_scale_down_%d",(int)mass);
      get_environment(file_title_3);
      xsec_NLO_3[counter_masses]=BGcrosssection; //*BGweight;
      //std::cout << "Read xs for 0.2 coupling for mass " << mass << " " << xsec_NLO_3[counter_masses]  << std::endl;                                                             
                               
      counter_masses++;

      if(mass<mass_inter_0){mass+=binning_0;}
      else { 
        if(mass<mass_inter_1) mass+=binning_1;
        else 
	  {
	    if(mass<mass_inter_2)mass+=binning_2;
	    else 
	      {
		if(mass<mass_inter_3) mass+=binning_3;
		else 
		  {
		    if(mass<mass_inter_4) mass+=binning_4;
		    else mass+=binning_5;
		  }
	      }
	  }
      }

    }

  counter_masses=0;
  mass=mass_min;
  */

  //  std::cout << "Will do observed ! " << std::endl;  
  ////////// observed //////////
 
  while(mass<=mass_max)
    {
      std::cout << "mass = " << mass ;
      masses[counter_masses]=mass;
      sprintf(file_title,"LQD_001_LLE_001_MSnl_scale_down_%d",(int)mass);
      get_environment(file_title);
      xsec_NLO[counter_masses]=BGcrosssection; // *BGweight;
      //std::cout << "  Read xs for 0.01 coupling for mass " << mass   <<  " " << xsec_NLO[counter_masses]  << std::endl;
  
      //this is in fb , 0.4 is BR, 0.1 is coupling
      kM=(BGcrosssection/0.4)*1./pow(0.01,2);
      
      sprintf(mass_dir,"/merged/Mass%i.root",mass);   
      TString basedir="/user/mukherjee/out/May10_RPV_Observed/";
      TString *massdir=new TString(mass_dir);
      TString filename_observed = basedir+*massdir;
      double limit; //=0.0;
      TFile *observed_file=new TFile(filename_observed);      
      
      delete massdir;
      
      TTree *tree_observed = (TTree*)observed_file->Get("limit");
      tree_observed->ResetBranchAddresses();
      tree_observed->SetBranchAddress("limit",&limit);      
      
      int nrEntries = tree_observed->GetEntries();
      for(int entryNr=0;entryNr<nrEntries;entryNr++){
	tree_observed->GetEntry(entryNr);
	observed_limit << limit << endl;
	std::cout <<  "    obs limit = " << limit << std::endl;
      }
      
      observed[counter_masses]=limit;
      
      //cout << " Mass: " << mass << " observed limit: " << limit ;

      //      xs_expected[counter_masses]=expected[counter_masses]*xsec_NLO[counter_masses]; ///Aeff[counter_masses];
       xs_observed[counter_masses]=observed[counter_masses]*xsec_NLO[counter_masses]; ///Aeff[counter_masses];
       if (mass>4000) xs_observed[counter_masses]=xs_observed[counter_masses-1];
       // std::cout << "  " <<   observed[counter_masses] << " * " << xsec_NLO[counter_masses]  << " = " << xs_observed[counter_masses] << std::endl; 
      //xs_expected_68_up[counter_masses]=expected_68_up[counter_masses]*xsec_NLO[counter_masses];
      //xs_expected_68_down[counter_masses]=expected_68_down[counter_masses]*xsec_NLO[counter_masses];   
      //xs_expected_95_up[counter_masses]=expected_95_up[counter_masses]*xsec_NLO[counter_masses];
      //xs_expected_95_down[counter_masses]=expected_95_down[counter_masses]*xsec_NLO[counter_masses]; 

      observed_limit_xsec << limit*xsec_NLO[counter_masses]  << endl;
      //expected_limit_xsec << xs_expected[counter_masses]  << endl;      

      observed_limit_mass_kM << mass << " " << kM << " " << limit*xsec_NLO[counter_masses] << endl;            
      //expected_limit_mass_kM << mass << " " << kM << " " << xs_expected[counter_masses] << endl;            

      // cout << "   "  << mass << "  &  obs_xsec= " <<   xs_observed[counter_masses]  <<  " \\\\ "    << endl; 
      // std::cout << "Mass " << mass <<  " " << xs_expected[counter_masses] << "=" << expected[counter_masses] << "*" <<xsec_NLO[counter_masses] << std::endl; 

      counter_masses++;
      
      if(mass<mass_inter_0){mass+=binning_0;}
      else { 
        if(mass<mass_inter_1) mass+=binning_1;
        else 
	  {
	    if(mass<mass_inter_2)mass+=binning_2;
	    else 
	      {
		if(mass<mass_inter_3) mass+=binning_3;
		else 
		  {
		    if(mass<mass_inter_4) mass+=binning_4;
		    else mass+=binning_5;
		  }
	      }
	  }
      }
    }



  observed_limit.close();                                                                                                        
  observed_limit_xsec.close();                                                                                                    
  observed_limit_mass_kM.close();   
  
  //  counter_masses=0;
   mass=mass_min_exp;

  

  std::cout << "Will do expected ! " << std::endl ;
  ////////// expected //////////
  while(mass<=mass_max_exp)
    {
      //      std::cout << "mass " << mass << std::endl;
      masses_exp[counter_masses_exp]=mass;
      sprintf(file_title_exp,"LQD_001_LLE_001_MSnl_scale_down_%d",(int)mass);
      get_environment(file_title_exp);
      //xsec[counter_masses]=BGcrosssection*1000.*BGweight;
      xsec_NLO_exp[counter_masses_exp]=BGcrosssection; //*BGweight;
      //std::cout<< "Read xs for 0.1 coupling for mass " << mass << std::endl;

      //this is in fb , 0.4 is BR, 0.1 is coupling
      kM_exp=(BGcrosssection/0.4)*1./pow(0.01,2);
      
      sprintf(mass_dir_exp,"/merged/Mass%i.root",mass);   
      ///user/mukherjee/out/Nov_28_EMU2016_RPV_CategoryComb/
      //      TString basedir_exp="/user/mukherjee/out/Jan23_RPV_CategoryComb_Expected/";
      TString basedir_exp="/user/mukherjee/out/May10_RPV_Expected/";
      TString *massdir_exp=new TString(mass_dir_exp);
      TString filename=basedir_exp+*massdir_exp;
      // TString filename_observed = basedir+in_dir+*massdir+"/condor/observed.root";

      double limit;
      //      std::cout << "get hold of " << filename << std::endl;
      TFile *expected_file=new TFile(filename);
      //      TFile *observed_file=new TFile(filename_observed);      
      
      TTree *tree = (TTree*)expected_file->Get("limit");
      tree->ResetBranchAddresses();
      tree->SetBranchAddress("limit",&limit);
  
      int nrEntries = tree->GetEntries();
      
      double limits[10000];
      
      for(int entryNr=0;entryNr<nrEntries;entryNr++){
	tree->GetEntry(entryNr);
	limits[entryNr]=limit;
      }
      tree->ResetBranchAddresses();
      std::sort(limits, limits + nrEntries);
     
      median << limits[Nint(nrEntries*0.5)] << "\n";
      upper_68 << limits[Nint(nrEntries*0.841344746)] << "\n";
      lower_68 << limits[Nint(nrEntries*0.158655254)] << "\n";
      upper_95 << limits[Nint(nrEntries*0.977249868)] << "\n";
      lower_95 << limits[Nint(nrEntries*0.022750132)] << "\n";
  
      expected[counter_masses_exp]=limits[Nint(nrEntries*0.5)];
      expected_68_up[counter_masses_exp]=limits[Nint(nrEntries*0.841344746)];
      expected_68_down[counter_masses_exp]=limits[Nint(nrEntries*0.158655254)];      
      expected_95_up[counter_masses_exp]=limits[Nint(nrEntries*0.977249868)];
      expected_95_down[counter_masses_exp]=limits[Nint(nrEntries*0.022750132)];           

      delete tree;
      delete expected_file;
      delete massdir_exp;

      
      //TTree *tree_observed = (TTree*)observed_file->Get("limit");

      //tree_observed->ResetBranchAddresses();
      //tree_observed->SetBranchAddress("limit",&limit);      
      
      //nrEntries = tree_observed->GetEntries();
      //for(int entryNr=0;entryNr<nrEntries;entryNr++){
      //	tree_observed->GetEntry(entryNr);
      //	observed_limit << limit << endl;
      // }
      
      //observed[counter_masses]=limit;
      
      // cout << "Mass: " << mass << " observed limit: " << limit ;

      xs_expected[counter_masses_exp]=expected[counter_masses_exp]*xsec_NLO_exp[counter_masses_exp]; ///Aeff[counter_masses];
      //std::cout << mass  << " "  <<  xs_expected[counter_masses_exp] << " = " << expected[counter_masses_exp] << "*" << xsec_NLO_exp[counter_masses_exp]   << std::endl;
      //xs_observed[counter_masses]=observed[counter_masses]*xsec_NLO[counter_masses]; ///Aeff[counter_masses];
      xs_expected_68_up[counter_masses_exp]=expected_68_up[counter_masses_exp]*xsec_NLO_exp[counter_masses_exp];
      xs_expected_68_down[counter_masses_exp]=expected_68_down[counter_masses_exp]*xsec_NLO_exp[counter_masses_exp];   
      xs_expected_95_up[counter_masses_exp]=expected_95_up[counter_masses_exp]*xsec_NLO_exp[counter_masses_exp];
      xs_expected_95_down[counter_masses_exp]=expected_95_down[counter_masses_exp]*xsec_NLO_exp[counter_masses_exp]; 
      if (mass>4500)   xs_expected_95_down[counter_masses_exp]=xs_expected_95_down[counter_masses_exp-1] ;

      //observed_limit_xsec << limit*xsec_NLO[counter_masses]  << endl;
      expected_limit_xsec << xs_expected[counter_masses_exp]  << endl;      

      //observed_limit_mass_kM << mass << " " << kM << " " << limit*xsec_NLO[counter_masses] << endl;            
      expected_limit_mass_kM << mass << " " << kM_exp << " " << xs_expected[counter_masses_exp] << endl;            

      //cout << mass << " GeV :  " << xs_expected[counter_masses_exp]  <<  " fb "    << endl; 
      // std::cout << "Mass " << mass <<  " " << xs_expected[counter_masses] << "=" << expected[counter_masses] << "*" <<xsec_NLO[counter_masses] << std::endl; 

      counter_masses_exp++;

      if(mass<mass_inter_0_exp){mass+=binning_0_exp;}
      else { 
	if(mass<mass_inter_1_exp) mass+=binning_1_exp;
	else { 
	  if(mass<mass_inter_2_exp) mass+=binning_2_exp;
	  else { 
	    if(mass<mass_inter_3_exp) mass+=binning_3_exp;
	    else { 
	      if(mass<mass_inter_4_exp)mass+=binning_4_exp;
	      else mass+=binning_5_exp;
	      //{
	      //if(mass<mass_inter_3)mass+=binning_3;
	      //else mass+=binning_4;
	      //}
	      //}
	    }
	  }
	}
      }
    }      
  
    
  median.close();
  upper_68.close();
  lower_68.close();
  upper_95.close();
  lower_95.close();
  
  //  observed_limit.close();
  // observed_limit_xsec.close();
 
  expected_limit_xsec.close();  
  expected_limit_mass_kM.close();
   // observed_limit_mass_kM.close();



  //limits have been written, now produce the corresponding plots





  


  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);  
  gStyle->SetPadTopMargin(0.05);   
  gStyle->SetTitleXSize(0.05);
  gStyle->SetTitleXOffset(1.05);
  gStyle->SetTitleYSize(0.05);
  gStyle->SetTitleYOffset(1.05);

  TCanvas* ratio = new TCanvas("ratio","ratio",1000,800);

  ratio->cd();
  ratio->SetLogy();
  
  
  TGraph *graph_observed = new TGraph(counter_masses,masses,observed);
  graph_observed->GetXaxis()->SetRangeUser(mass_min,mass_max);
  graph_observed->GetYaxis()->SetRangeUser(0.1,10);
  //gPad->SetLogy();
    graph_observed->SetTitle("");
    graph_observed->SetMarkerStyle(0);
    graph_observed->SetMarkerSize(1.1);
    graph_observed->SetMarkerColor(1);
    graph_observed->SetLineColor(1);
    graph_observed->SetLineWidth(3);   
    graph_observed->GetXaxis()->SetTitle("M_{#tilde{#nu_{#tau}}} (GeV)");
    graph_observed->GetYaxis()->SetTitle("#frac{#sigma_{95%CL}}{#sigma_{sig}#timesBR}");    
  

  TGraph *graph_expected = new TGraph(counter_masses_exp,masses_exp,expected);
  graph_expected->GetXaxis()->SetRangeUser(mass_min_exp,mass_max_exp);
    graph_expected->GetYaxis()->SetRangeUser(0.1,10);
    //gPad->SetLogy();
    graph_expected->SetTitle("");
    graph_expected->SetMarkerStyle(0);
    graph_expected->SetMarkerColor(kBlack);
    graph_expected->SetLineColor(kBlack);
    graph_expected->SetLineWidth(2);
    graph_expected->SetLineStyle(2);    
    //graph_expected->GetXaxis()->SetTitle("M_{#tilde{#nu_{#tau}}} [TeV]");
    //graph_expetced->GetYaxis()->SetTitle("#frac{#sigma_{95%CL}}{#sigma_{sig}}");    

    graph_observed->Draw("Apc");  
    graph_expected->GetXaxis()->SetTitleFont(42);
    graph_expected->GetYaxis()->SetTitleFont(42);
    graph_expected->GetXaxis()->SetLabelFont(42);
    graph_expected->GetYaxis()->SetLabelFont(42);    
    //    graph_expected->GetXaxis()->SetTitle("M_{#tilde{#nu_{#tau}}} (GeV)");
    graph_expected->GetXaxis()->SetTitle("M_{#tilde{#nu_{#tau}}} (GeV)");
    graph_expected->GetYaxis()->SetTitle("#frac{#sigma_{95% CL}}{#sigma_{signal}}");
    graph_expected->GetXaxis()->SetRangeUser(mass_min,mass_max);
    graph_expected->GetYaxis()->SetRangeUser(0.1,80.);
    graph_expected->Draw("Apl");   

    
    TGraph *graph_expected_68_up = new TGraph(counter_masses_exp,masses_exp,expected_68_up);    
    //graph_expected_68_up->Draw("pl,same");
    TGraph *graph_expected_68_down = new TGraph(counter_masses_exp,masses_exp,expected_68_down);    
    //graph_expected_68_down->Draw("pl,same");


    TGraph *grshade_95 = new TGraph(2*counter_masses_exp);
    for (int i=0;i<counter_masses_exp;i++) {
      grshade_95->SetPoint(i,masses_exp[i],expected_95_up[i]);
      grshade_95->SetPoint(counter_masses_exp+i,masses_exp[counter_masses_exp-i-1],expected_95_down[counter_masses_exp-i-1]);
    }
      
    grshade_95->SetFillStyle(1001);
    grshade_95->SetFillColor(kYellow);
    grshade_95->Draw("f");

    TGraph *grshade_68 = new TGraph(2*counter_masses_exp);
    for (int i=0;i<counter_masses_exp;i++) {
      grshade_68->SetPoint(i,masses_exp[i],expected_68_up[i]);
      grshade_68->SetPoint(counter_masses_exp+i,masses_exp[counter_masses_exp-i-1],expected_68_down[counter_masses_exp-i-1]);
    }
      
    grshade_68->SetFillStyle(1001);
    grshade_68->SetFillColor(kGreen);
    grshade_68->Draw("f");



    graph_expected->Draw("pl,same");  
    graph_observed->Draw("pc,same");

    TLine *borderline = new TLine(0.,1.,2000.,1.);
    borderline->SetLineWidth(2);
    borderline->SetLineColor(kBlue);
    borderline->DrawLine(200.,1.,2000.,1.);


    TLegend *leg_example = new TLegend(0.5,0.75,0.5,0.9);
    leg_example->SetFillColor(0);
    leg_example->SetTextFont(42);
    
       leg_example->AddEntry(graph_observed, "observed limit","pl");
    //    leg_example->AddEntry(graph_observed, "95% CL limit","pl"); 
    leg_example->AddEntry(graph_expected, "median expected limit","pl"); 
    leg_example->AddEntry(grshade_68, "68% expected","f");
    leg_example->AddEntry(grshade_95, "95% expected","f");
    //leg_example->AddEntry(borderline, "","l");
    
    leg_example->Draw("same");
  



    //cross section limit

    TCanvas* total = new TCanvas("total","total",1000,800);

    total->cd();

    total->SetLogy();
  
    
    TGraph *graph_observed_total = new TGraph(counter_masses,masses,xs_observed);
    graph_observed->GetXaxis()->SetRangeUser(mass_min,mass_max);
    graph_observed->GetYaxis()->SetRangeUser(1,100.);
    //gPad->SetLogy();
    graph_observed_total->SetTitle("");
    graph_observed_total->SetMarkerStyle(0);
    graph_observed_total->SetMarkerSize(1.1);
    graph_observed_total->SetMarkerColor(1);
    graph_observed_total->SetLineColor(1);
    graph_observed_total->SetLineWidth(3);   
    graph_observed->GetXaxis()->SetTitle("M_{#tilde{#nu_{#tau}}} (GeV)");
    graph_observed->GetYaxis()->SetTitle("#frac{#sigma_{95%CL}}{#sigma_{sig}#timesBR}");    
   

    TGraph *graph_expected_total = new TGraph(counter_masses_exp,masses_exp,xs_expected);
    graph_expected_total->GetXaxis()->SetRangeUser(mass_min_exp,mass_max_exp);
    graph_expected_total->GetYaxis()->SetRangeUser(0.05,1000.);
    //gPad->SetLogy();
    graph_expected_total->SetTitle("");
    graph_expected_total->SetMarkerStyle(0);
    graph_expected_total->SetMarkerColor(kBlack);
    graph_expected_total->SetLineColor(kBlack);
    graph_expected_total->SetLineWidth(2);
    graph_expected_total->SetLineStyle(2);    
    //graph_expected->GetXaxis()->SetTitle("M_{#tilde{#nu_{#tau}}} [TeV]");
    //graph_expetced->GetYaxis()->SetTitle("#frac{#sigma_{95%CL}}{#sigma_{sig}}");    

    //   graph_observed->Draw("Apc");  
    graph_expected_total->GetXaxis()->SetTitleFont(42);
    graph_expected_total->GetYaxis()->SetTitleFont(42);
    graph_expected_total->GetXaxis()->SetLabelFont(42);
    graph_expected_total->GetYaxis()->SetLabelFont(42);    
    //  graph_expected_total->GetXaxis()->SetTitle("M_{#tilde{#nu}_{#tau}} (GeV)");
    //    graph_expected_total->GetYaxis()->SetTitle("#sigma^{prod}_{#tilde{#nu_{#tau}}} #times BR ( #tilde{#nu_{#tau}} #rightarrow e#mu ) (fb)");
    graph_expected_total->GetXaxis()->SetTitle("M_{#tilde{#nu_{#tau}}} (GeV)");
    graph_expected_total->GetYaxis()->SetTitle("#sigma^{prod}_{#tilde{#nu_{#tau}}} #times BR ( #tilde{#nu_{#tau}} #rightarrow e#mu ) (fb)");
    graph_expected_total->GetXaxis()->SetRangeUser(mass_min_exp,mass_max_exp);
    graph_expected_total->GetYaxis()->SetRangeUser(0.05,1000.);
    graph_expected_total->Draw("Apl");   


    TGraph *graph_expected_68_up_total = new TGraph(counter_masses_exp,masses_exp,xs_expected_68_up);    
    //graph_expected_68_up->Draw("pl,same");
    TGraph *graph_expected_68_down_total = new TGraph(counter_masses_exp,masses,xs_expected_68_down);    
    //graph_expected_68_down->Draw("pl,same");


    TGraph *grshade_95_total = new TGraph(2*counter_masses_exp);
    for (int i=0;i<counter_masses_exp;i++) {
      grshade_95_total->SetPoint(i,masses_exp[i],xs_expected_95_up[i]);
      grshade_95_total->SetPoint(counter_masses_exp+i,masses_exp[counter_masses_exp-i-1],xs_expected_95_down[counter_masses_exp-i-1]);
    }
      
    grshade_95_total->SetFillStyle(1001);
    grshade_95_total->SetFillColor(kYellow);
    grshade_95_total->Draw("f");

    TGraph *grshade_68_total = new TGraph(2*counter_masses_exp);
    for (int i=0;i<counter_masses_exp;i++) {
      grshade_68_total->SetPoint(i,masses_exp[i],xs_expected_68_up[i]);
      grshade_68_total->SetPoint(counter_masses_exp+i,masses_exp[counter_masses_exp-i-1],xs_expected_68_down[counter_masses_exp-i-1]);
    }
      
    grshade_68_total->SetFillStyle(1001);
    grshade_68_total->SetFillColor(kGreen);
    grshade_68_total->Draw("f");

    graph_expected_total->Draw("pl,same");  
    graph_observed_total->Draw("pc,same");


    std::cout<< "Prepare to draw graph 1" << std::endl;
    
    TGraph *graph_xsec= new TGraph(counter_masses_exp,masses_exp,xsec_NLO_exp);
    graph_xsec->SetTitle("");
    graph_xsec->SetMarkerStyle(0);
    graph_xsec->SetMarkerSize(1.4);
    graph_xsec->SetMarkerColor(kBlue);
    graph_xsec->SetLineColor(kBlue);
    graph_xsec->SetLineWidth(2);    
    //    graph_xsec->GetXaxis()->SetTitle("M_{#tilde{#nu_{#tau}}} [TeV]");
    graph_xsec->GetXaxis()->SetTitle("M_{RPV} [TeV]");
    graph_xsec->GetYaxis()->SetTitle("95%CL #sigma_{sig}xBR / fb");   
    graph_xsec->Draw("pl,same");
    //g_xsec_scale_up->Draw("l,same");
    //g_xsec_scale_down->Draw("l,same");    
    //fit_xsec_Zprime->Draw("pl,same");
    TSpline3 *s3 = new TSpline3("s3",graph_xsec->GetX(),graph_xsec->GetY(),graph_xsec->GetN());
    s3->SetLineColor(kRed);
    //s3->Draw("l same");
    
    //
    std::cout<< "Prepare to draw graph 2" << std::endl;

    TGraph *graph_xsec_2= new TGraph(counter_masses,masses,xsec_NLO_2);
    graph_xsec_2->SetTitle("");
    graph_xsec_2->SetMarkerStyle(0);
    graph_xsec_2->SetMarkerSize(1.4);
    graph_xsec_2->SetMarkerColor(kRed+2);
    graph_xsec_2->SetLineColor(kRed+2);
    graph_xsec_2->SetLineWidth(2);    
    //    graph_xsec_2->GetXaxis()->SetTitle("M_{#tilde{#nu_{#tau}}} [TeV]");
    graph_xsec_2->GetYaxis()->SetTitle("95%CL #sigma_{sig}xBR / fb");   
    graph_xsec_2->Draw("pl,same");
    //g_xsec_scale_up->Draw("l,same");
    //g_xsec_scale_down->Draw("l,same");    
    //fit_xsec_Zprime->Draw("pl,same");
    TSpline3 *s4 = new TSpline3("s4",graph_xsec_2->GetX(),graph_xsec_2->GetY(),graph_xsec_2->GetN());
    s4->SetLineColor(kRed+2);
    //s3->Draw("l same");
    /*
    TGraph *graph_xsec_3= new TGraph(counter_masses,masses,xsec_NLO_3);
    graph_xsec_3->SetTitle("");
    graph_xsec_3->SetMarkerStyle(0);
    graph_xsec_3->SetMarkerSize(1.4);
    graph_xsec_3->SetMarkerColor(kPink+1);
    graph_xsec_3->SetLineColor(kPink+1);
    graph_xsec_3->SetLineWidth(2);
    //   graph_xsec_3->GetXaxis()->SetTitle("M_{#tilde{#nu_{#tau}}} [TeV]");
    graph_xsec_3->GetYaxis()->SetTitle("95%CL #sigma_{sig}xBR / fb");
    //graph_xsec_3->Draw("pl,same");
    //g_xsec_scale_up->Draw("l,same");     
    //g_xsec_scale_down->Draw("l,same");                                                                                                                                     
    //fit_xsec_Zprime->Draw("pl,same");                                                                                                                                        
    TSpline3 *s5 = new TSpline3("s5",graph_xsec_3->GetX(),graph_xsec_3->GetY(),graph_xsec_3->GetN());
    s5->SetLineColor(kRed+2);
    //s3->Draw("l same");                  

    */
    /*
    TF1* fit_xsec=new TF1("fit_xsec","[0]/([1]+[2]*x+[3]*pow(x,2))",400,2000);
    fit_xsec->SetParameter(0,242580);
    fit_xsec->SetParameter(1,87191.4);
    fit_xsec->SetParameter(2,-440.933);
    fit_xsec->SetParameter(3,0.609692);    
    graph_xsec->Fit(fit_xsec,"","",400,2000);
    */
  
    std::cout<< "Prepare to draw legend" << std::endl;

    TLegend *leg_total = new TLegend(0.65,0.55,0.95,0.95);
    leg_total->SetFillColor(0);
    leg_total->SetTextFont(42);
    leg_total->SetTextSize(0.032);    
    
    //       leg_total->AddEntry(graph_observed, "observed limit","pl");
    //    leg_total->AddEntry(graph_observed, "95% CL limit","pl"); 
    leg_total->AddEntry(graph_expected, "median expected limit","pl"); 
    leg_total->AddEntry(grshade_68, "68% expected","f");
    leg_total->AddEntry(grshade_95, "95% expected","f");
    //leg_total->AddEntry(graph_xsec, "#splitline{RPV signal (NLO)}{#lambda^{I}_{311}=#lambda_{132}=0.01}","l");
    leg_total->AddEntry(graph_xsec, "RPV signal:","");
    //  leg_total->AddEntry(graph_xsec_2, "#lambda^{I}_{311}=#lambda_{132}=#lambda_{231}=0.01","l");
    // leg_total->AddEntry(graph_xsec, "#lambda^{I}_{311}=#lambda_{132}=#lambda_{231}=0.1","l");
    //    leg_total->AddEntry(graph_xsec_3, "#lambda^{I}_{311}=#lambda_{132}=#lambda_{231}=0.2","l");
    leg_total->AddEntry(graph_xsec_2, "#lambda=#lambda'=0.1","l");
    /// leg_total->AddEntry(graph_xsec_3, "#lambda=#lambda'=0.2","l");
    leg_total->AddEntry(graph_xsec, "#lambda=#lambda'=0.01","l");

    //leg_total->AddEntry(fit_xsec_Zprime,"Z'/a' (LO)","l"); 
    //leg_total->AddEntry(borderline," ","");
    
    leg_total->Draw("same");
    
    //TLatex* CMS_text = new TLatex(0.20,0.88,"CMS");
    TLatex* CMS_text = new TLatex(0.45,0.88,"CMS");
    CMS_text->SetNDC();
    CMS_text->SetTextSize(0.05);
    CMS_text->SetTextAngle(0);
    CMS_text->Draw("same");

    TLatex* text_1 = new TLatex(0.45,0.75,"Combined");
    text_1->SetNDC();
    text_1->SetTextSize(0.03);
    text_1->SetTextAngle(0);
    //    text_1->Draw("same");
    
    TLatex* CMS_text_2 = new TLatex(0.45,0.83,"Preliminary");
    //TLatex* CMS_text_2 = new TLatex(0.20,0.83," ");
    CMS_text_2->SetNDC();
    CMS_text_2->SetTextFont(42);
    CMS_text_2->SetTextSize(0.05);
    CMS_text_2->SetTextAngle(0);
    CMS_text_2->Draw("same");    

    TLatex* lumiText = new TLatex(0.95,0.975,"35.9 fb^{-1} (13 TeV)");
    lumiText->SetNDC();
    lumiText->SetTextFont(42);
    lumiText->SetTextSize(0.04);
    lumiText->SetTextAlign(32);
    lumiText->Draw("same");     


  total->Print("limit_RPV.pdf");






    outfile->cd();
    //}
    graph_observed_total->Write("limit_observed");
    graph_expected_total->Write("limit_expected");    
    total->Write("limit_plot");
    graph_expected_68_up_total->Write("limit_68_up");
    graph_expected_68_down_total->Write("limit_68_down");    
    grshade_95_total->Write("limit_95_shade");
}






