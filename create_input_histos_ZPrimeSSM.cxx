//#include "create_input_histos.h"

#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TString.h"
#include <sstream>
#include "TH1.h"
#include "TF1.h"
#include "TString.h"
#include "Environment.h"
#include <iostream>
#include <fstream>
#include <TMath.h>
#include "TKey.h"
#include "TLegend.h"
#include "TString.h"
#include "TGraphErrors.h"
#include "TIterator.h"
#include <cstring>
#include <string>

//using namespace RooFit ;
using namespace std;
bool debug = 0;

void create_input_histos_ZPrimeSSM(int stage){
  std::cout << "Starting .... " ;
  std::cout << " stage " << stage << std::endl; 
  TFile* infile; 
  ///net/scratch_cms/institut_3a/mukherjee/EMULimitJan20
  TString rootfilenames[] = {
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ttbar_tot.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/WW_tot.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/SingleTop_tot.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/DY_tot.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/WZ_tot.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZZ_tot.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/Wgamma.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/Bkg_DataDriven_MuJet.root"
};

  TString sample_names[] = {"TT_tot","WW_tot","single_top_tot","DY_tot","WZ_tot","ZZ_tot","Wgamma","datadriven"};
  const int arraySize = sizeof(sample_names)/sizeof(sample_names[0]);  

  //names of systematics for shape-based input
  TString syst_names[] ={"pileup_syst_","eleID_syst_","Ele_syst_Scale","Muon_syst_Scale","Muon_syst_Resolution","muoID_syst_", "topShape_syst_"};
  const int arraySize_systs = sizeof(syst_names)/sizeof(syst_names[0]);    

  std::cout << "No- of systematics " << arraySize_systs << "  No. of bkg MC samples " << arraySize << std::endl;
 
  Char_t filename_sig[400];
  Char_t file_title[400];
  Char_t file_title1[400];
  Char_t dir_title[400];
  Char_t dir_title1[400];
  Char_t dir_title_syst[400];  

  //outfile for all histos
  
  sprintf(file_title1,"root_out/out_Stage%i.root", stage);
  sprintf(dir_title1,"txt_out/normalization_Stage%i.txt", stage);
  TFile *outfile = new TFile(file_title1,"recreate");
  
  //outfile for all text to be used as input for the limit cfgs
  ofstream myfile;
  myfile.open (dir_title1);
  
  if (debug) std::cout << "will start initializer loop" << std::endl;
  
  //
  //  PDF Systematics
  //
  /*
  TString pdffilename = "/net/scratch_cms/institut_3a/erdweg/public/13TeV_rpv/76_test/for_limit.root";
  TFile* pdffile = new TFile(pdffilename);
  std::cout << "File for PDF uncert : " << pdffilename << std::endl;
  TH1D* hist_pdf_mean=(TH1D*)pdffile->Get("PDF4LHC15_nnlo_mc_mean");
  TH1D* hist_pdf_up=(TH1D*)pdffile->Get("PDF4LHC15_nnlo_mc_up");
  TH1D* hist_pdf_down=(TH1D*)pdffile->Get("PDF4LHC15_nnlo_mc_down");

  TH1D* hist_pdf_rel_up = new TH1D("reluppdf", "pdfuprel", 6200, 0, 6200);   //  = ((*hist_pdf_up)/(*hist_pdf_mean));
  TH1D* hist_pdf_rel_down = new TH1D("reldownpdf", "pdfdownrel", 6200, 0, 6200);//= ((*hist_pdf_down)/(*hist_pdf_mean));

  for (int i=1; i<6201; i++) {
    double up=hist_pdf_up->GetBinContent(i);
    double down=hist_pdf_down->GetBinContent(i);
    double mean=hist_pdf_mean->GetBinContent(i);
    double rel_up = 0;   
    double rel_down = 0; 
    if (mean!=0.0) rel_up =   up/mean;
    if (mean!=0.0) rel_down = down/mean;

    //std::cout << "bin " << i << "rel_up " << rel_up << "  rel_down " << rel_down << std::endl;
    hist_pdf_rel_up->SetBinContent(i,rel_up);
    hist_pdf_rel_down->SetBinContent(i,rel_down);
  }
  */

  //###############
  //loop over backgrounds
  //###############  
  if (debug) std::cout << "will start background loop"<< std::endl;

  //////////////////////////////////////
  //              UPDATE              //
  double Lumi_bkg = (36458.8/1000.0);
  std::cout << "Lumi scale factor for bkg : " << Lumi_bkg << std::endl;
  /////////////////////////////////////
  

  double ttbar_kfact = 1.116;
  double WW_kfact = 1.1619;
  for (int i = 0; i < arraySize; ++i){
    if (debug) std::cout << "will get the bkg root file"<< std::endl;
    std::cout << "\n\nrootfilename " << rootfilenames[i] << "  sample_name " << sample_names[i] << std::endl;
    TFile* infile = new TFile(rootfilenames[i]);
    
    //TAG change to one input file per bkg
    TH1D* hist_ori;
    //    cout << ((TString)(sample_names[i]) + "_7_0/"+(TString)(sample_names[i])+ "_ori").Data() << endl;
    if (debug) std::cout << "will get the hist h1_2_emu_Mass"<< std::endl;
    char name1[100]; 
    sprintf (name1, "emu/Stage_%i/h1_%i_emu_Mass", stage, stage); 
    hist_ori=(TH1D*)infile->Get(name1);
    if (sample_names[i] != "datadriven")  hist_ori->Scale(Lumi_bkg);
    if (sample_names[i]=="TT_tot") {
      std::cout << "Extra k-factor scaling will be done for TTbar background" << std::endl;
      hist_ori->Scale(ttbar_kfact);
    }

    if (sample_names[i]=="WW_tot") {
      std::cout << "Extra k-factor scaling will be done for WW background" << std::endl;
      hist_ori->Scale(WW_kfact);
    }
      
    hist_ori->SetName(sample_names[i]);
    
    outfile->cd();
    hist_ori->Write(sample_names[i]);
    
    //TAG check which binning is used for the histograms (here: 1-10000, 1 GeV binning)
    std::cout  << "bkg " << sample_names[i] << " " << hist_ori->Integral(1,10000) << "\n";
    myfile << "bkg " << sample_names[i] << " " << hist_ori->Integral(1,10000) << "\n";
    
    
    //    if (debug) std::cout << "Now multiply mass_mean_hist_bkg with pdf_rel (up and down) hist" << std::endl;
    /*
    if (sample_names[i] != "datadriven") {
      TH1D* hist_pdf_thisBkg_Up = new TH1D("bkgUPpdf", "BkgUpPDF", 6200, 0, 6200);   //  = hist_pdf_rel_up *(*hist_ori);
      TH1D* hist_pdf_thisBkg_Down = new TH1D("bkgDOWNpdf", "BkgDOWNPDF", 6200, 0, 6200); ; //= hist_pdf_rel_down *(*hist_ori);
      
      for (int ii=1; ii<6201; ii++) {
	double my_up=hist_pdf_rel_up->GetBinContent(ii);
	double my_down=hist_pdf_rel_down->GetBinContent(ii);
	double my_mean=hist_ori->GetBinContent(ii);
	double mul_my_up = my_up*my_mean;
	double mul_my_down = my_down*my_mean;
	
	hist_pdf_thisBkg_Up->SetBinContent(ii,mul_my_up);
	hist_pdf_thisBkg_Down->SetBinContent(ii,mul_my_down);
      }
      
      //  hist_pdf_thisBkg_Up.Scale( (hist_ori->Integral()) / (hist_pdf_thisBkg_Up.Integral()) );
      hist_pdf_thisBkg_Up->SetName(sample_names[i]+"_"+"pdf_syst"+"Up");
      hist_pdf_thisBkg_Up->Write();
      std::cout << "MEAN hist classname " << hist_ori->ClassName() << std::endl;
      std::cout << "UP hist classname " << hist_pdf_thisBkg_Up->ClassName() << std::endl;
      myfile << "bkg " << sample_names[i]+"_"+"pdf_syst"+"Up" << " " << hist_pdf_thisBkg_Up->Integral(1,10000) << "\n";
      
      // hist_pdf_thisBkg_Down.Scale( (hist_ori->Integral()) / (hist_pdf_thisBkg_Down.Integral()) );
      hist_pdf_thisBkg_Down->SetName(sample_names[i]+"_"+"pdf_syst"+"Down");
      hist_pdf_thisBkg_Down->Write(); 
      myfile << "bkg " << sample_names[i]+"_"+"pdf_syst"+"Down" << " " << hist_pdf_thisBkg_Down->Integral(1,10000) << "\n";
    }
    */

    //###############
    //loop over other systematics
    //###############  
    if (debug) std::cout << "will start the syst loop"<< std::endl;
    
    if (sample_names[i] != "datadriven") {
      for(int k=0; k<arraySize_systs; k++)
	{
	  TH1D* hist_syst_up;
	  TH1D* hist_syst_down;	
	  
	  //hist_syst_up=(TH1F*)infile->Get(((TString)(sample_names[i]) + "_7_0/"+(TString)(sample_names[i])+ "_" + syst_names[k] + "Up").Data());
	  if (debug) std::cout << "will get syst hist UP"<< std::endl;
	  char name2[150]; 
	  sprintf (name2, "emu/Stage_%i/sys/h1_%i_emu_Mass_", stage, stage);
	  std::cout << name2 <<  std::endl;
	  hist_syst_up   = (TH1D*)infile->Get(name2+syst_names[k]+"Up");
	  std::cout << "Lumi scaling for " << sample_names[i] << " and " << syst_names[k] << " UP"  << std::endl;
	  hist_syst_up->Scale(Lumi_bkg);
	  
	  char name3[150]; 
	  sprintf (name3, "emu/Stage_%i/sys/h1_%i_emu_Mass_", stage, stage);
	  hist_syst_down = (TH1D*)infile->Get(name3+syst_names[k]+"Down");
	  std::cout << "Lumi scaling for " << sample_names[i]  << " and " << syst_names[k] << " DOWN"  << std::endl;
	  hist_syst_down->Scale(Lumi_bkg);
	  hist_syst_up->SetName(sample_names[i]+"_"+syst_names[k]+"Up");
	  hist_syst_up->Write(); 
	  myfile << "bkg " << sample_names[i]+"_"+syst_names[k]+"Up" << " " << hist_syst_up->Integral(1,10000) << "\n";
	  
	  hist_syst_down->SetName(sample_names[i]+"_"+syst_names[k]+"Down");
	  hist_syst_down->Write(); 
	  myfile << "bkg " << sample_names[i]+"_"+syst_names[k]+"Down" << " " << hist_syst_down->Integral(1,10000) << "\n";
	  
	  if (debug) std::cout << "Will delete hist_syst_up hist_syst_down "<< std::endl;
	  
	  delete hist_syst_up;
	  delete hist_syst_down;	
	if (debug) std::cout << "Successfully deleted hist_syst_up hist_syst_down "<< std::endl;
	
      }
    }
    if (debug) std::cout << "Will delete hist_ori "<< std::endl;
    delete hist_ori;
    if (debug) std::cout << "Successfully deleted hist_ori "<< std::endl;
    
    
  }
  
  
  //###############
  //end loop over backgrounds
  //###############    

  //get datahist

  //TAG get the file with the data histogram
  if (debug) std::cout << "will get data root file"<< std::endl;
  TFile* data_file = new TFile("/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/allData.root");
  TH1D* data;
  //  data=(TH1F*)data_file->Get("h1_inv_mass_1mu_1tau_aligned_7_0");
  //if (debug) 
  std::cout << "will get data hist"<< std::endl;
  char name4[100]; 
  sprintf (name4, "emu/Stage_%i/h1_%i_emu_Mass", stage, stage);
  data=(TH1D*)data_file->Get(name4); 

  outfile->cd();
  data->SetName("data_obs");
  data->Write();

  myfile << "data " << "data" << " " << data->Integral(1,10000) << "\n";
  std::cout << "data " << "data" << " " << data->Integral() << "\n";

  TFile* infile_sig_all;
  TString rootfilenames_sig_all[] = {
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_600_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_700_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_800_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_900_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_1000_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_1100_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_1200_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_1300_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_1400_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_1500_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_1600_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_1700_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_1800_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_1900_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_2000_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_2200_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_2400_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_2600_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_2800_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_3000_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_3500_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_4000_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_4500_13TeV_P8.root",
    "/net/scratch_cms/institut_3a/mukherjee/EMULimitJan20/ZPrimeToEMu_M_5000_13TeV_P8.root",
  };

  std::string sample_names_sig[] = {"600", "700", "800", "900", "1000", "1100", "1200", "1300", "1400", "1500", "1600", "1700", "1800", "1900", "2000", "2200", "2400", "2600", "2800", "3000", "3500", "4000", "4500", "5000"};
  //std::string sample_names_sig[] = {"5000"};
  const int arraySize_sig = sizeof(sample_names_sig)/sizeof(sample_names_sig[0]);

  TString syst_names_sig[] ={"pileup_syst_","eleID_syst_","Ele_syst_Scale","Muon_syst_Scale","Muon_syst_Resolution","muoID_syst_"};
  const int arraySize_systs_sig = sizeof(syst_names_sig)/sizeof(syst_names_sig[0]);

  std::cout << "No- of systematics " << arraySize_systs_sig << "  No. of signal MC samples " << arraySize_sig << std::endl;

  for (int k = 0; k < arraySize_sig; ++k){
    TFile* infile_sig_all = new TFile(rootfilenames_sig_all[k]);
    //   TFile* infile_sig = new TFile(rootfilenames_sig[k]);

    TH1D* signal_temp;
    sprintf(file_title,"root_out/out_mass_%s_Stage%i.root",sample_names_sig[k].c_str(), stage);
    sprintf(dir_title,"txt_out/normalization_Mass_%s_Stage%i_input_histos.txt",sample_names_sig[k].c_str(), stage);
    ofstream myfile_temp;
    myfile_temp.open(dir_title);
    TFile* outfile_signal = new TFile(file_title,"recreate");
    outfile_signal->cd();
    
    int counter_histos=0;
  
      TKey *key;
      TIter next(outfile->GetListOfKeys());

      while ((key = (TKey*)next())) {

	TH1 *h1 = (TH1*)key->ReadObj();
	TString *name = new TString(h1->GetName());
	
	if(strcmp(h1->GetName(),"data_obs") ==0 )
	  {
	    myfile_temp << "data " << h1->GetName() << " " << h1->Integral(1,10000) << "\n";	    
	  }	
	else
	  {
	    myfile_temp << "bkg " << h1->GetName() << " " << h1->Integral(1,10000) << "\n"; 
	  }
	
	h1->Write();

	counter_histos++;

	delete name;
	delete h1;

      }
      char name5[100]; 
      sprintf (name5, "emu/Stage_%i/h1_%i_emu_Mass", stage, stage);
      signal_temp=(TH1D*)infile_sig_all->Get(name5);
      //std::cout << "Nbin = " << signal_temp->GetXaxis()->GetNbins() << std::endl;
      std::cout << "signal mass: " << sample_names_sig[k] << " Nevt="  << signal_temp->Integral(1,10000)  << "  Mass resolution = " << signal_temp->GetRMS() << std::endl;
      signal_temp->Scale(Lumi_bkg);
      myfile << "signal " << sample_names_sig[k] << " " << signal_temp->Integral(1,10000) << "\n";
      myfile_temp << "signal " << sample_names_sig[k] << " " << signal_temp->Integral(1,10000) << "\n";

      // Write in output file
      outfile_signal->cd();
      signal_temp->Write("signal");

      for(int kk=0; kk<arraySize_systs_sig; kk++)
	{
	  TH1D* sig_hist_syst_up;
	  TH1D* sig_hist_syst_down;
	  char name6[150]; 
	  sprintf (name6, "emu/Stage_%i/sys/h1_%i_emu_Mass_", stage, stage);
	  sig_hist_syst_up   = (TH1D*)infile_sig_all->Get(name6+syst_names_sig[kk]+"Up");
	  //std::cout << "Lumi scaling for " << sample_names_sig[k] << " and " << syst_names_sig[kk] << " UP"  << std::endl;
	  sig_hist_syst_up->Scale(Lumi_bkg);

	  char name7[150]; 
	  sprintf (name7, "emu/Stage_%i/sys/h1_%i_emu_Mass_", stage, stage);
	  sig_hist_syst_down = (TH1D*)infile_sig_all->Get(name7+syst_names_sig[kk]+"Down");
	  // std::cout << "Lumi scaling for " << sample_names_sig[k]  << " and " << syst_names_sig[kk] << " DOWN"  << std::endl;
	  sig_hist_syst_down->Scale(Lumi_bkg);
	  sig_hist_syst_up->SetName("signal_"+syst_names_sig[kk]+"Up");
	  sig_hist_syst_up->Write();
	  myfile << "signal syst " << sample_names_sig[k] << " " << "signal_"+syst_names_sig[kk]+"Up" << " " << sig_hist_syst_up->Integral(1,10000) << "\n";
	  myfile_temp << "signal syst " << sample_names_sig[k] << " " << "signal_"+syst_names_sig[kk]+"Up" << " " << sig_hist_syst_up->Integral(1,10000) << "\n";
	  
	  sig_hist_syst_down->SetName("signal_"+syst_names_sig[kk]+"Down");
	  sig_hist_syst_down->Write();
	  myfile << "signal syst " << sample_names_sig[k] << " " << "signal_"+syst_names[kk]+"Down" << " " << sig_hist_syst_down->Integral(1,10000) << "\n";
	  myfile_temp << "signal syst " << sample_names_sig[k] << " " << "signal_"+syst_names[kk]+"Down" << " " << sig_hist_syst_down->Integral(1,10000) << "\n";
	  
	  if (debug) std::cout << "Will delete hist_syst_up hist_syst_down "<< std::endl;
	  
	  delete sig_hist_syst_up;
	  delete sig_hist_syst_down;
	  if (debug) std::cout << "Successfully deleted hist_syst_up hist_syst_down "<< std::endl;
	  
	}
      delete signal_temp;
      myfile_temp.close();
      
  }
  
  myfile.close();
  
}
