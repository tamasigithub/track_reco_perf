//! plot pull distribution for various theta bins
//!definition used ->  pull = kappa-kap013/sigma(k)
//! sigma(k) = sqrt( ( (6^0.5 * sigma(t)) / (d^2 * sin(Theta13)) )^2 + (t/X) * (1/sin(Theta13)) * (13.6 * kap013 * sin(Theta13)/(0.3 * B * d))^2 )
//! sigma(t) = uncertainty in transverse(azimuthal) direction = 40 * 1e-3 / 12^0.5 ----------------> pixel dimension =40* 40 μm^
//! d = 30mm
//! t/X = 2.0% = 0.02
//! B = 4T
#include <iostream>
#include "TROOT.h"
#include "TFile.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TPostScript.h"
#include "TCut.h"
#include "TMath.h"
#include "TChain.h"
#include "TH1.h"
#include "TLegend.h"
#include <fstream>
#include <string>
#include <math.h>


const double Constant = 0.299760192; 	
const double w  = 40e-3;//mm
const double d	= 40;// gap between the layers in the triplet in mm
const double B	= 4;// magnetic field in Tesla
const double X_0= 0.015;// relative radiation length t/X_0  = 2%
/*const double w = 50e-6;//m
const double d	= 20e-3;// gap between the layers in the triplet in m
const double B	= 2;// magnetic field in Tesla
const double X_0= 0.015;// relative radiation length t/X_0  = 1.5%
*/

const char* out_path = "./plots/optimisation";
////! 25mm
//TCut cut = "Tid>0 && Pt_n>2e3 && abs(Z013)<100 && abs(Eta13)<2.5 && abs(Phi13)<0.018 && abs(Z13)<320 && abs(dphi2)<3.0e-4 && abs(dz2)<0.12*(sin(Theta13)^(-1.1))";
//TCut MS_r = "Tid>0 && Pt_n>2e3 && Pt_n<4e3 && abs(Z013)<100 && abs(Eta13)<2.5 && abs(Phi13)<0.018 && abs(Z13)<320 && abs(dphi2)<3.0e-4 && abs(dz2)<0.12*(sin(Theta13)^(-1.1))";
//TCut Hit_r = "Tid>0 && Pt_n>20e3 && abs(Z013)<100 && abs(Eta13)<2.5 && abs(Phi13)<0.018 && abs(Z13)<320 && abs(dphi2)<3.0e-4 && abs(dz2)<0.12*(sin(Theta13)^(-1.1))";

////! 30mm
//TCut cut = "Tid>0 && Pt_n>2e3 && abs(Z013)<100 && abs(Eta13)<2.5 && abs(Phi13)<0.021 && abs(Z13)<380 && abs(dphi2)<3.0e-4 && abs(dz2)<0.13*(sin(Theta13)^(-1.13))";
//TCut MS_r = "Tid>0 && Pt_n>2e3 && Pt_n<4e3 && abs(Z013)<100 && abs(Eta13)<2.5 && abs(Phi13)<0.021 && abs(Z13)<380 && abs(dphi2)<3.0e-4 && abs(dz2)<0.13*(sin(Theta13)^(-1.13))";
//TCut Hit_r = "Tid>0 && Pt_n>20e3 && abs(Z013)<100 && abs(Eta13)<2.5 && abs(Phi13)<0.021 && abs(Z13)<380 && abs(dphi2)<3.0e-4 && abs(dz2)<0.13*(sin(Theta13)^(-1.13))";

////! 35mm
//TCut cut = "Tid>0 && Pt_n>2e3 && abs(Z013)<100 && abs(Eta13)<2.5 && abs(Phi13)<0.025 && abs(Z13)<430 && abs(dphi2)<3.0e-4 && abs(dz2)<0.15*(sin(Theta13)^(-1.18))";
//TCut MS_r = "Tid>0 && Pt_n>2e3 && Pt_n<4e3 && abs(Z013)<100 && abs(Eta13)<2.5 && abs(Phi13)<0.025 && abs(Z13)<430 && abs(dphi2)<3.0e-4 && abs(dz2)<0.15*(sin(Theta13)^(-1.18))";
//TCut Hit_r = "Tid>0 && Pt_n>20e3 && abs(Z013)<100 && abs(Eta13)<2.5 && abs(Phi13)<0.025 && abs(Z13)<430 && abs(dphi2)<3.0e-4 && abs(dz2)<0.15*(sin(Theta13)^(-1.18))";

//! 40mm
TCut cut = "Tid>0 && Pt_n>2e3 && abs(Z013)<100 && abs(Eta13)<2.5 && abs(Phi13)<0.028 && abs(Z13)<480 && abs(dphi2)<3e-4 && abs(dz2)<0.16*(sin(Theta13)^(-1.30))";
TCut MS_r = "Tid>0 && Pt_n>2e3 && Pt_n<4e3 && abs(Z013)<100 && abs(Eta13)<2.5 && abs(Phi13)<0.028 && abs(Z13)<480 && abs(dphi2)<3e-4 && abs(dz2)<0.16*(sin(Theta13)^(-1.30))";
TCut Hit_r = "Tid>0 && Pt_n>20e3 && abs(Z013)<100 && abs(Eta13)<2.5 && abs(Phi13)<0.028 && abs(Z13)<480 && abs(dphi2)<3e-4 && abs(dz2)<0.16*(sin(Theta13)^(-1.30))";


////! 20mm
//TCut cut = "Tid>0 && Pt_n>2e3 && abs(Z013)<100 && abs(Eta13)<1.7 && abs(Phi13)<0.015 && abs(Z13)<115 && abs(dphi2)<1e-4 && abs(dz2)<1.3*(sin(Theta13)^(-0.9))";
//TCut MS_r = "Tid>0 && Pt_n>2e3 && Pt_n<4e3 && abs(Z013)<100 && abs(Eta13)<1.7 && abs(Phi13)<0.015 && abs(Z13)<115 && abs(dphi2)<1e-4 && abs(dz2)<1.3*(sin(Theta13)^(-0.9))";
//TCut Hit_r = "Tid>0 && Pt_n>20e3 && abs(Z013)<100 && abs(Eta13)<1.7 && abs(Phi13)<0.015 && abs(Z13)<115 && abs(dphi2)<1e-4 && abs(dz2)<1.3*(sin(Theta13)^(-0.9))";
////! 50mm
//TCut cut = "Tid>0 && Pt_n>2e3 && abs(Z013)<100 && abs(Eta13)<1.6 && abs(Phi13)<0.032 && abs(Z13)<260 && abs(dphi2)<6e-4 && abs(dz2)<0.17*(sin(Theta13)^(-1.5))";
//TCut MS_r = "Tid>0 && Pt_n>2e3 && Pt_n<4e3 && abs(Z013)<100 && abs(Eta13)<1.6 && abs(Phi13)<0.032 && abs(Z13)<260 && abs(dphi2)<6e-4 && abs(dz2)<0.17*(sin(Theta13)^(-1.5))";
//TCut Hit_r = "Tid>0 && Pt_n>20e3 && abs(Z013)<100 && abs(Eta13)<1.6 && abs(Phi13)<0.032 && abs(Z13)<260 && abs(dphi2)<6e-4 && abs(dz2)<0.17*(sin(Theta13)^(-1.5))";
int pull(const char* output_file_name = "pullggF_40mm", const char* constants ="B")
{
	TChain rec("m_recTree");
        rec.Add("/home/tamasi/repo_tamasi/rec_files/for_optimization/40mm/ggFhh4b_SM/*.root");
	
	//! 20mm
	//rec.Add("/home/tamasi/repo_tamasi/rec_files/MB_recTree_20000*_samelad.root");
	//! 25mm
	//rec.Add("/media/tamasi/Elements/PhD/FCC/data_files/rec_files/25mm/ggFhh4b_SM/*.root");
	//! 30mm
	//rec.Add("/media/tamasi/Elements/PhD/FCC/data_files/rec_files/30mm/ggFhh4b_SM/*.root");
	//rec.Add("/home/tamasi/repo_tamasi/rec_files/MB_recTree_30000*_samelad.root");
	//! 35mm
	//rec.Add("/media/tamasi/Elements/PhD/FCC/data_files/rec_files/35mm/ggFhh4b_SM/*.root");
	//! 40mm
	//rec.Add("/media/tamasi/Elements/PhD/FCC/data_files/rec_files/40mm/ggFhh4b_SM/*.root");
	//rec.Add("/home/tamasi/repo_tamasi/rec_files/MB_recTree_40000*.root");
	//! 50mm
	//rec.Add("/home/tamasi/repo_tamasi/rec_files/MB_recTree_50000*.root");


	std::cout<<"rec tree entries: "<< rec.GetEntries() << std::endl;
	 gStyle->SetOptFit(1011);
	//! bin quantities
	int nbins = 50;
	//double xmin = 0.4, xmax = 2.8;
	double xmin = 0.1, xmax = 3.1;
	double xmin1,xmax1;
	//! Book histograms
	TH1F *h	  = new TH1F("h"  ,"Theta distribution; #theta_{013} [rad]",nbins,xmin,xmax);
	rec.Draw("Theta13>>h",cut,"",1e5);

	
	char plot_var[1024];
	char plot_varMS[1024];
	char plot_varHit[1024];
	char plot_var1[1024];
	char plot_var2[1024];
	double hit_C = 0.0, MS_C = 0.0;
	//const double hit_C, MS_C;
	if(constants == "A"){
	hit_C = 0.0054;
	MS_C = 0.0134;
	//! constants from Andre
	sprintf(plot_var,"((kappa-kap013)*1e3)/sqrt(%f + %f *1e6*kap013^2) >>h0",hit_C,MS_C);
	sprintf(plot_varMS,"((kappa-kap013)*1e3)/sqrt(%f + %f *1e6*kap013^2) >>hMS",hit_C,MS_C);
	sprintf(plot_varHit,"((kappa-kap013)*1e3)/sqrt(%f + %f *1e6*kap013^2) >>hHit",hit_C,MS_C);
	sprintf(plot_var1,"((kappa-kap013)*1e3)/sqrt(%f+ %f *1e6*kap013^2) >>h_1",hit_C,MS_C);
	sprintf(plot_var2,"kap013*1e3 : ((kappa-kap013)*1e3)/sqrt(%f+ %f *1e6*kap013^2) >>h_2",hit_C,MS_C);
	}
	else
	{
	hit_C = 0.5*std::pow((w/std::pow(d,2)),2);
	MS_C  = X_0*std::pow((13.6/(Constant*B*d)),2);
	std::cout<<"hit_c:"<<hit_C<<"\n";
	std::cout<<"MS_c:"<<MS_C<<"\n";
	//! with formula
	/*
	sprintf(plot_var, "(kappa-kap013)/sqrt(%e + %e *sin(Theta13) * kap013 * kap013 )>>h0",hit_C,MS_C);
	sprintf(plot_varMS, "(kappa-kap013)/sqrt(%e + %e *sin(Theta13) * kap013 * kap013 )>>hMS",hit_C,MS_C);
	sprintf(plot_varHit, "(kappa-kap013)/sqrt(%e + %e *sin(Theta13) * kap013 * kap013 )>>hHit",hit_C,MS_C);
	sprintf(plot_var1,"(kappa-kap013)/sqrt(%e + %e *sin(Theta13) * kap013 * kap013 )>>h_1",hit_C,MS_C);
	sprintf(plot_var2,"kap013 : (kappa-kap013)/sqrt(%e + %e *sin(Theta13) * kap013 * kap013 )>>h_2",hit_C,MS_C);
	//! with formula
	*/
	sprintf(plot_var, "(kappa-kap013)/sqrt(%e + %e * (1/sin(Theta13)) * kap013 * kap013 )>>h0",hit_C,MS_C);
	sprintf(plot_varMS, "(kappa-kap013)/sqrt(%e + %e * (1/sin(Theta13)) * kap013 * kap013 )>>hMS",hit_C,MS_C);
	sprintf(plot_varHit, "(kappa-kap013)/sqrt(%e + %e * (1/sin(Theta13)) * kap013 * kap013 )>>hHit",hit_C,MS_C);
	sprintf(plot_var1,"(kappa-kap013)/sqrt(%e + %e * (1/sin(Theta13)) * kap013 * kap013 )>>h_1",hit_C,MS_C);
	sprintf(plot_var2,"kap013 : (kappa-kap013)/sqrt(%e + %e * (1/sin(Theta13)) * kap013 * kap013 )>>h_2",hit_C,MS_C);
	}

        char out_file_root[1023];
        sprintf(out_file_root,"%s/%s.root",out_path,output_file_name);
        TFile* output_file = new TFile(out_file_root, "RECREATE");
	h->Write();

	char buffer[1024];
	char hist_name[1024];
	char hist_nameMS[1024];
	char hist_nameHit[1024];
	for(int i = 0; i<10; ++i)
	{
		xmin1 = xmin + i*0.3;
		xmax1 = xmin + (i+1)*0.3;

		std::cout<<"xmin1 :" <<xmin1 <<"\n";
		std::cout<<"xmax1 :" <<xmax1 <<"\n";
		
		TH1D *h0  = new TH1D("h0" ,"Pull distribution; dkappa/#sigma_{k}",nbins,-6,6);
		TH1D *hMS  = new TH1D("hMS" ,"Pull distribution for p_{t} < 4GeV/c; dkappa/#sigma_{k}",nbins,-6,6);
		TH1D *hHit  = new TH1D("hHit" ,"Pull distribution for p_{t} > 20GeV/c; dkappa/#sigma_{k}",nbins,-6,6);

		sprintf(buffer,"Theta13 > %f && Theta13 < %f",xmin1,xmax1);
		sprintf(hist_name,"h%d",i);
		sprintf(hist_nameMS,"hMS%d",i);
		sprintf(hist_nameHit,"hHit%d",i);

		rec.Draw(plot_var,cut && TCut(buffer),"",1e5);
		h0->Fit("gaus");
		printf("thetabin = %d => mu = %.6f, rms = %.6f, rms err = %.6f\n", i,h0->GetFunction("gaus")->GetParameter(1),h0->GetFunction("gaus")->GetParameter(2), h0->GetFunction("gaus")->GetParError(2));
		//printf("thetabin = %d => mu = %.6f, rms = %.6f, rms err = %.6f\n", i,h0->GetMean(),h0->GetRMS(), h0->GetRMSError());
		h0->Write(hist_name);	
		rec.Draw(plot_varMS,MS_r && TCut(buffer),"",1e5);
		hMS->Fit("gaus");
		printf("thetabin = %d => mu = %.6f, rms = %.6f, rms err = %.6f\n", i,hMS->GetFunction("gaus")->GetParameter(1),hMS->GetFunction("gaus")->GetParameter(2), hMS->GetFunction("gaus")->GetParError(2));
		//printf("thetabin = %d => mu = %.6f, rms = %.6f, rms err = %.6f\n", i,hMS->GetMean(),hMS->GetRMS(), hMS->GetRMSError());
		hMS->Write(hist_nameMS);	
		rec.Draw(plot_varHit,Hit_r && TCut(buffer),"",1e5);
		hHit->Fit("gaus");
		printf("thetabin = %d => mu = %.6f, rms = %.6f, rms err = %.6f\n", i,hHit->GetFunction("gaus")->GetParameter(1),hHit->GetFunction("gaus")->GetParameter(2), hHit->GetFunction("gaus")->GetParError(2));
		//printf("thetabin = %d => mu = %.6f, rms = %.6f, rms err = %.6f\n", i,hHit->GetMean(),hHit->GetRMS(), hHit->GetRMSError());
		hHit->Write(hist_nameHit);	
		delete h0;
		delete hMS;
		delete hHit;
	}
	TH1D *h_1  = new TH1D("h_1" ,"Pull distribution; dkappa/#sigma_{k}",nbins,-6,6);
	TH2D *h_2  = new TH2D("h_2" ,"kappa Vs pull; dkappa/#sigma_{k}; #kappa_{013}[mm^{-1}]",300,-6,6,nbins,-7e-4,7e-4);
	rec.Draw(plot_var1,cut,"",1e5);
	h_1->Fit("gaus");
	rec.Draw(plot_var2,cut,"",1e5);
	h_1->Write();
	h_2->Write();
	output_file->Close();
return 0;
}

int write_to_pdf(const char* input_file_name = "pullggF_40mm.root", const char* output_file_name = "pullggF_40mm")
{
	
	char in_file[1023];
	sprintf(in_file, "%s/%s",out_path,input_file_name);
	TFile *f = TFile::Open(in_file);
	
	TH1F* H   = (TH1F*)f->Get("h");
	TH1F* H_1 = (TH1F*)f->Get("h_1");
	TH1F* H_2 = (TH1F*)f->Get("h_2");
	TH1F* H0  = (TH1F*)f->Get("h0");
	TH1F* H1  = (TH1F*)f->Get("h1");
	TH1F* H2  = (TH1F*)f->Get("h2");
	TH1F* H3  = (TH1F*)f->Get("h3");
	TH1F* H4  = (TH1F*)f->Get("h4");
	TH1F* H5  = (TH1F*)f->Get("h5");
	TH1F* H6  = (TH1F*)f->Get("h6");
	TH1F* H7  = (TH1F*)f->Get("h7");
	TH1F* H8  = (TH1F*)f->Get("h8");
	TH1F* H9  = (TH1F*)f->Get("h9");
	//TH1F* H10 = (TH1F*)f->Get("h10");
	//TH1F* H11 = (TH1F*)f->Get("h11");
	//TH1F* H11 = (TH1F*)f->Get("h12");
	//TH1F* H11 = (TH1F*)f->Get("h13");

	TH1F* HMS0  = (TH1F*)f->Get("hMS0");
	TH1F* HMS1  = (TH1F*)f->Get("hMS1");
	TH1F* HMS2  = (TH1F*)f->Get("hMS2");
	TH1F* HMS3  = (TH1F*)f->Get("hMS3");
	TH1F* HMS4  = (TH1F*)f->Get("hMS4");
	TH1F* HMS5  = (TH1F*)f->Get("hMS5");
	TH1F* HMS6  = (TH1F*)f->Get("hMS6");
	TH1F* HMS7  = (TH1F*)f->Get("hMS7");
	TH1F* HMS8  = (TH1F*)f->Get("hMS8");
	TH1F* HMS9  = (TH1F*)f->Get("hMS9");
	//TH1F* HMS10 = (TH1F*)f->Get("hMS10");
	//TH1F* HMS11 = (TH1F*)f->Get("hMS11");
	//TH1F* HMS11 = (TH1F*)f->Get("hMS12");
	//TH1F* HMS11 = (TH1F*)f->Get("hMS13");
	
	TH1F* Hhit0  = (TH1F*)f->Get("hHit0");
	TH1F* Hhit1  = (TH1F*)f->Get("hHit1");
	TH1F* Hhit2  = (TH1F*)f->Get("hHit2");
	TH1F* Hhit3  = (TH1F*)f->Get("hHit3");
	TH1F* Hhit4  = (TH1F*)f->Get("hHit4");
	TH1F* Hhit5  = (TH1F*)f->Get("hHit5");
	TH1F* Hhit6  = (TH1F*)f->Get("hHit6");
	TH1F* Hhit7  = (TH1F*)f->Get("hHit7");
	TH1F* Hhit8  = (TH1F*)f->Get("hHit8");
	TH1F* Hhit9  = (TH1F*)f->Get("hHit9");
	//TH1F* Hhit10 = (TH1F*)f->Get("hHit10");
	//TH1F* Hhit11 = (TH1F*)f->Get("hHit11");
	//TH1F* Hhit11 = (TH1F*)f->Get("hHit12");
	//TH1F* Hhit11 = (TH1F*)f->Get("hHit13");


	char out_file_open[1023];
        sprintf(out_file_open,"%s/%s.pdf(",out_path,output_file_name);
        char out_file_[1023];
        sprintf(out_file_,"%s/%s.pdf",out_path,output_file_name);
        char out_file_close[1023];
        sprintf(out_file_close,"%s/%s.pdf)",out_path,output_file_name);

	gStyle->SetOptFit(1111);
	Double_t x1= 0.1,y1= 0.8, x2 = 0.3, y2 = 0.9;
	TCanvas* S =  new TCanvas();
	H->Draw();
	S->Print(out_file_open,"pdf");
	S->SetLogy();
	H_1->Draw();
	TLegend *l_1=new TLegend(x1,y1,x2,y2,"#theta = 0.1 - 3.1");
	l_1->Draw();
	l_1->SetTextSize(0.03);
	S->Print(out_file_,"pdf");
	S->Clear();
	S->SetLogy(0);
	H_2->Draw();
	TLegend *l_2=new TLegend(x1,y1,x2,y2,"#theta = 0.1 - 3.1");
	l_2->Draw();
	l_2->SetTextSize(0.03);
	S->Print(out_file_,"pdf");
	S->Clear();
	S->Divide(2,2);
	S->cd(1);
	H0->Draw();
	TLegend *l0=new TLegend(x1,y1,x2,y2,"#theta = 0.1 - 0.4");
	l0->Draw();
	l0->SetTextSize(0.04);
	S->cd(2);
	H1->Draw();
	TLegend *l1=new TLegend(x1,y1,x2,y2,"#theta = 0.4 - 0.7");
	l1->Draw();
	l1->SetTextSize(0.04);
	S->cd(3);
	H2->Draw();
	TLegend *l2=new TLegend(x1,y1,x2,y2,"#theta = 0.7 - 1.0");
	l2->Draw();
	l2->SetTextSize(0.04);
	S->cd(4);
	H3->Draw();
	TLegend *l3=new TLegend(x1,y1,x2,y2,"#theta = 1.0 - 1.3");
	l3->Draw();
	l3->SetTextSize(0.04);
	S->Print(out_file_,"pdf");
	S->Clear();
	S->Divide(2,2);
	S->cd(1);
	H4->Draw();
	TLegend *l4=new TLegend(x1,y1,x2,y2,"#theta = 1.3 - 1.6");
	l4->Draw();
	l4->SetTextSize(0.04);
	S->cd(2);
	H5->Draw();
	TLegend *l5=new TLegend(x1,y1,x2,y2,"#theta = 1.6 - 1.9");
	l5->Draw();
	l5->SetTextSize(0.04);
	S->cd(3);
	H6->Draw();
	TLegend *l6=new TLegend(x1,y1,x2,y2,"#theta = 1.9 - 2.2");
	l6->Draw();
	l6->SetTextSize(0.04);
	S->cd(4);
	H7->Draw();
	TLegend *l7=new TLegend(x1,y1,x2,y2,"#theta = 2.2 - 2.5");
	l7->Draw();
	l7->SetTextSize(0.04);
	S->Print(out_file_,"pdf");
	S->Clear();
	S->Divide(2,2);
	S->cd(1);
	H8->Draw();
	TLegend *l8=new TLegend(x1,y1,x2,y2,"#theta = 2.5 - 2.8");
	l8->Draw();
	l8->SetTextSize(0.04);
	S->cd(2);
	H9->Draw();
	TLegend *l9=new TLegend(x1,y1,x2,y2,"#theta = 2.8 - 3.1");
	l9->Draw();
	l9->SetTextSize(0.04);
	//S->cd(3);
	//H10->Draw();
	//TLegend *l10=new TLegend(x1,y1,x2,y2,"#theta = 2.1 - 2.3");
	//l10->Draw();
	//l10->SetTextSize(0.04);
	//S->cd(4);
	//H11->Draw();
	//TLegend *l11=new TLegend(x1,y1,x2,y2,"#theta = 2.3 - 2.5");
	//l11->Draw();
	//l11->SetTextSize(0.04);
	S->Print(out_file_,"pdf");
	S->Clear();
	S->Divide(2,2);
	S->cd(1);
	HMS0->Draw();
	TLegend *lM0=new TLegend(x1,y1,x2,y2,"#theta = 0.1 - 0.4");
	lM0->Draw();
	lM0->SetTextSize(0.04);
	S->cd(2);
	HMS1->Draw();
	TLegend *lM1=new TLegend(x1,y1,x2,y2,"#theta = 0.4 - 0.7");
	lM1->Draw();
	lM1->SetTextSize(0.04);
	S->cd(3);
	HMS2->Draw();
	TLegend *lM2=new TLegend(x1,y1,x2,y2,"#theta = 0.7 - 1.0");
	lM2->Draw();
	lM2->SetTextSize(0.04);
	S->cd(4);
	HMS3->Draw();
	TLegend *lM3=new TLegend(x1,y1,x2,y2,"#theta = 1.0 - 1.3");
	lM3->Draw();
	lM3->SetTextSize(0.04);
	S->Print(out_file_,"pdf");
	S->Clear();
	S->Divide(2,2);
	S->cd(1);
	HMS4->Draw();
	TLegend *lM4=new TLegend(x1,y1,x2,y2,"#theta = 1.3 - 1.6");
	lM4->Draw();
	lM4->SetTextSize(0.04);
	S->cd(2);
	HMS5->Draw();
	TLegend *lM5=new TLegend(x1,y1,x2,y2,"#theta = 1.6 - 1.9");
	lM5->Draw();
	lM5->SetTextSize(0.04);
	S->cd(3);
	HMS6->Draw();
	TLegend *lM6=new TLegend(x1,y1,x2,y2,"#theta = 1.9 - 2.2");
	lM6->Draw();
	lM6->SetTextSize(0.04);
	S->cd(4);
	HMS7->Draw();
	TLegend *lM7=new TLegend(x1,y1,x2,y2,"#theta = 2.2 - 2.5");
	lM7->Draw();
	lM7->SetTextSize(0.04);
	S->Print(out_file_,"pdf");
	S->Clear();
	S->Divide(2,2);
	S->cd(1);
	HMS8->Draw();
	TLegend *lM8=new TLegend(x1,y1,x2,y2,"#theta = 2.5 - 2.8");
	lM8->Draw();
	lM8->SetTextSize(0.04);
	S->cd(2);
	HMS9->Draw();
	TLegend *lM9=new TLegend(x1,y1,x2,y2,"#theta = 2.8 - 3.1");
	lM9->Draw();
	lM9->SetTextSize(0.04);
	//S->cd(3);
	//HMS10->Draw();
	//TLegend *lM10=new TLegend(x1,y1,x2,y2,"#theta = 2.4 - 2.6");
	//lM10->Draw();
	//lM10->SetTextSize(0.04);
	//S->cd(4);
	//HMS11->Draw();
	//TLegend *lM11=new TLegend(x1,y1,x2,y2,"#theta = 2.6 - 2.8");
	//lM11->Draw();
	//lM11->SetTextSize(0.04);
	S->Print(out_file_,"pdf");
	S->Clear();
	S->Divide(2,2);
	S->cd(1);
	Hhit0->Draw();
	TLegend *lh0=new TLegend(x1,y1,x2,y2,"#theta = 0.1 - 0.4");
	lh0->Draw();
	lh0->SetTextSize(0.04);
	S->cd(2);
	Hhit1->Draw();
	TLegend *lh1=new TLegend(x1,y1,x2,y2,"#theta = 0.4 - 0.7");
	lh1->Draw();
	lh1->SetTextSize(0.04);
	S->cd(3);
	Hhit2->Draw();
	TLegend *lh2=new TLegend(x1,y1,x2,y2,"#theta = 0.7 - 1.0");
	lh2->Draw();
	lh2->SetTextSize(0.04);
	S->cd(4);
	Hhit3->Draw();
	TLegend *lh3=new TLegend(x1,y1,x2,y2,"#theta = 1.0 - 1.3");
	lh3->Draw();
	lh3->SetTextSize(0.04);
	S->Print(out_file_,"pdf");
	S->Clear();
	S->Divide(2,2);
	S->cd(1);
	Hhit4->Draw();
	TLegend *lh4=new TLegend(x1,y1,x2,y2,"#theta = 1.3 - 1.6");
	lh4->Draw();
	lh4->SetTextSize(0.04);
	S->cd(2);
	Hhit5->Draw();
	TLegend *lh5=new TLegend(x1,y1,x2,y2,"#theta = 1.6 - 1.9");
	lh5->Draw();
	lh5->SetTextSize(0.04);
	S->cd(3);
	Hhit6->Draw();
	TLegend *lh6=new TLegend(x1,y1,x2,y2,"#theta = 1.9 - 2.2");
	lh6->Draw();
	lh6->SetTextSize(0.04);
	S->cd(4);
	Hhit7->Draw();
	TLegend *lh7=new TLegend(x1,y1,x2,y2,"#theta = 2.2 - 2.5");
	lh7->Draw();
	lh7->SetTextSize(0.04);
	S->Print(out_file_,"pdf");
	S->Clear();
	S->Divide(2,2);
	S->cd(1);
	Hhit8->Draw();
	TLegend *lh8=new TLegend(x1,y1,x2,y2,"#theta = 2.5 - 2.8");
	lh8->Draw();
	lh8->SetTextSize(0.04);
	S->cd(2);
	Hhit9->Draw();
	TLegend *lh9=new TLegend(x1,y1,x2,y2,"#theta = 2.8 - 3.1");
	lh9->Draw();
	lh9->SetTextSize(0.04);
	//S->cd(3);
	//Hhit10->Draw();
	//TLegend *lh10=new TLegend(x1,y1,x2,y2,"#theta = 2.4 - 2.6");
	//lh10->Draw();
	//lh10->SetTextSize(0.04);
	//S->cd(4);
	//Hhit11->Draw();
	//TLegend *lh11=new TLegend(x1,y1,x2,y2,"#theta = 2.6 - 2.8");
	//lh11->Draw();
	//lh11->SetTextSize(0.04);
	S->Print(out_file_close,"pdf");

return 0;
}
	/*sprintf(plot_var,"(kappa-kap013)*1e3/sqrt(%f*sin(Theta13)^2 + %f*(1+0.038*log(0.015/sin(Theta13)))^2 *(kap013)^2 *sin(Theta13))>>h0",hit_C,MS_C);
	sprintf(plot_var1,"(kappa-kap013)*1e3/sqrt(%f*sin(Theta13)^2+ %f*(1+0.038*log(0.015/sin(Theta13)))^2 *(kap013)^2 *sin(Theta13))>>h_1",hit_C,MS_C);*/
//rec.Draw("(kappa-kap013)/sqrt(0.5*(50e-3/(20)^2)^2)^2+(0.015*(13.6/(2*20))^2*(1/sin(Theta13))*kap013^2))>>h1")

