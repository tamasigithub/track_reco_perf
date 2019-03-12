#include <iostream>
#include "TROOT.h"
#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TPostScript.h"
#include <fstream>
#include <string>
#include <math.h>
//const char* out_path = "/eos/user/t/tkar/www/TTT/plots/resolution"; 
const char* out_path = "./plots/purity"; 
int write_topdf(const char* output_file_name = "EffPurVsEtaPtPhi_InDetTTTBMatchedeta1.2")
{

	char out_file_open[1023];
        sprintf(out_file_open,"%s/%s.pdf(",out_path,output_file_name);
        char out_file_[1023];
        sprintf(out_file_,"%s/%s.pdf",out_path,output_file_name);
        char out_file_close[1023];
        sprintf(out_file_close,"%s/%s.pdf)",out_path,output_file_name);
	//!efficiency Indet and TTT tracks barcode matched
	TFile* f = TFile::Open("./plots/efficiency/eff_InDetTTTdR0.01_eta1.4B.root");
	TH1D* h_pt 	= (TH1D*)f->Get("h_eff_vs_ptInDet");
	TH1D* h_phi	= (TH1D*)f->Get("h_eff_vs_phiInDet");
	TH1D* h_eta	= (TH1D*)f->Get("h_eff_vs_etaInDet");
	TH1D* ht_pt 	= (TH1D*)f->Get("h_eff_vs_ptPU");
	TH1D* ht_phi	= (TH1D*)f->Get("h_eff_vs_phiPU");
	TH1D* ht_eta	= (TH1D*)f->Get("h_eff_vs_etaPU");
	TFile* f_ = TFile::Open("./plots/efficiency/eff_InDetTTTdR0.01_eta1.2B.root");
	TH1D* h__pt 	= (TH1D*)f_->Get("h_eff_vs_ptInDet");
	TH1D* h__phi	= (TH1D*)f_->Get("h_eff_vs_phiInDet");
	TH1D* h__eta	= (TH1D*)f_->Get("h_eff_vs_etaInDet");
	TH1D* h_t_pt 	= (TH1D*)f_->Get("h_eff_vs_ptPU");
	TH1D* h_t_phi	= (TH1D*)f_->Get("h_eff_vs_phiPU");
	TH1D* h_t_eta	= (TH1D*)f_->Get("h_eff_vs_etaPU");
	TFile* f_1 = TFile::Open("./plots/efficiency/eff_InDetTTTdR0.01_eta1.0B.root");
	TH1D* h_1_pt 	= (TH1D*)f_1->Get("h_eff_vs_ptInDet");
	TH1D* h_1_phi	= (TH1D*)f_1->Get("h_eff_vs_phiInDet");
	TH1D* h_1_eta	= (TH1D*)f_1->Get("h_eff_vs_etaInDet");
	TH1D* h_1t_pt 	= (TH1D*)f_1->Get("h_eff_vs_ptPU");
	TH1D* h_1t_phi	= (TH1D*)f_1->Get("h_eff_vs_phiPU");
	TH1D* h_1t_eta	= (TH1D*)f_1->Get("h_eff_vs_etaPU");
	TFile* f_2 = TFile::Open("./plots/efficiency/eff_InDetTTTdR0.01_eta0.8B.root");
	TH1D* h_2_pt 	= (TH1D*)f_2->Get("h_eff_vs_ptInDet");
	TH1D* h_2_phi	= (TH1D*)f_2->Get("h_eff_vs_phiInDet");
	TH1D* h_2_eta	= (TH1D*)f_2->Get("h_eff_vs_etaInDet");
	TH1D* h_2t_pt 	= (TH1D*)f_2->Get("h_eff_vs_ptPU");
	TH1D* h_2t_phi	= (TH1D*)f_2->Get("h_eff_vs_phiPU");
	TH1D* h_2t_eta	= (TH1D*)f_2->Get("h_eff_vs_etaPU");

	//! purity Indet tracks
	TFile* f0 = TFile::Open("./plots/purity/pur_InDetdR0.01_eta1.2.root");
	TH1D* h0_pt 	= (TH1D*)f0->Get("h_pur_vs_ptPU");
	TH1D* h0_phi	= (TH1D*)f0->Get("h_pur_vs_phiPU");
	TH1D* h0_eta	= (TH1D*)f0->Get("h_pur_vs_etaPU");
	//! purity TTT barcode matched tracks
	TFile* f0t = TFile::Open("./plots/purity/pur_TTTBMatched_eta1.2.root");
	TH1D* ht0_pt = (TH1D*)f0t->Get("h_pur_vs_ptPU");
	TH1D* ht0_phi	= (TH1D*)f0t->Get("h_pur_vs_phiPU");
	TH1D* ht0_eta	= (TH1D*)f0t->Get("h_pur_vs_etaPU");


	h_pt->SetStats(0);
       	h_phi->SetStats(0);
       	h_eta->SetStats(0);
	ht_pt->SetStats(0);
       	ht_phi->SetStats(0);
       	ht_eta->SetStats(0);
	h__pt->SetStats(0);
       	h__phi->SetStats(0);
       	h__eta->SetStats(0);
	h_t_pt->SetStats(0);
       	h_t_phi->SetStats(0);
       	h_t_eta->SetStats(0);
	h_1_pt->SetStats(0);
       	h_1_phi->SetStats(0);
       	h_1_eta->SetStats(0);
	h_1t_pt->SetStats(0);
       	h_1t_phi->SetStats(0);
       	h_1t_eta->SetStats(0);
	h_2_pt->SetStats(0);
       	h_2_phi->SetStats(0);
       	h_2_eta->SetStats(0);
	h_2t_pt->SetStats(0);
       	h_2t_phi->SetStats(0);
       	h_2t_eta->SetStats(0);
        
	h0_pt->SetStats(0);
        h0_phi->SetStats(0);
        h0_eta->SetStats(0);
        ht0_pt->SetStats(0);
        ht0_phi->SetStats(0);
        ht0_eta->SetStats(0);
 	
	// SET Markercolour
	//! efficiency in blue
	//! purity in red
	h_pt->SetMarkerColor(kCyan);
	h_phi->SetMarkerColor(kCyan);
	h_eta->SetMarkerColor(kCyan);
	ht_pt->SetMarkerColor(kCyan);
	ht_phi->SetMarkerColor(kCyan);
	ht_eta->SetMarkerColor(kCyan);
	h__pt->SetMarkerColor(kBlue);
	h__phi->SetMarkerColor(kBlue);
	h__eta->SetMarkerColor(kBlue);
	h_t_pt->SetMarkerColor(kBlue);
	h_t_phi->SetMarkerColor(kBlue);
	h_t_eta->SetMarkerColor(kBlue);
	h_1_pt->SetMarkerColor(kBlue-9);
	h_1_phi->SetMarkerColor(kBlue-9);
	h_1_eta->SetMarkerColor(kBlue-9);
	h_1t_pt->SetMarkerColor(kBlue-9);
	h_1t_phi->SetMarkerColor(kBlue-9);
	h_1t_eta->SetMarkerColor(kBlue-9);
	h_2_pt->SetMarkerColor(kBlue+2);
	h_2_phi->SetMarkerColor(kBlue+2);
	h_2_eta->SetMarkerColor(kBlue+2);
	h_2t_pt->SetMarkerColor(kBlue+2);
	h_2t_phi->SetMarkerColor(kBlue+2);
	h_2t_eta->SetMarkerColor(kBlue+2);
        
	h0_pt->SetMarkerColor(kRed);
        h0_phi->SetMarkerColor(kRed);
        h0_eta->SetMarkerColor(kRed);
        ht0_pt->SetMarkerColor(kRed);
        ht0_phi->SetMarkerColor(kRed);
        ht0_eta->SetMarkerColor(kRed);
	
	//Marker Size	
	h_pt->SetMarkerSize(1.8);
	h_phi->SetMarkerSize(1.8);
	h_eta->SetMarkerSize(1.8);
	ht_pt->SetMarkerSize(1.8);
	ht_phi->SetMarkerSize(1.8);
	ht_eta->SetMarkerSize(1.8);
	h__pt->SetMarkerSize(1.8);
	h__phi->SetMarkerSize(1.8);
	h__eta->SetMarkerSize(1.8);
	h_t_pt->SetMarkerSize(1.8);
	h_t_phi->SetMarkerSize(1.8);
	h_t_eta->SetMarkerSize(1.8);
	h_1_pt->SetMarkerSize(1.8);
	h_1_phi->SetMarkerSize(1.8);
	h_1_eta->SetMarkerSize(1.8);
	h_1t_pt->SetMarkerSize(1.8);
	h_1t_phi->SetMarkerSize(1.8);
	h_1t_eta->SetMarkerSize(1.8);
	h_2_pt->SetMarkerSize(1.8);
	h_2_phi->SetMarkerSize(1.8);
	h_2_eta->SetMarkerSize(1.8);
	h_2t_pt->SetMarkerSize(1.8);
	h_2t_phi->SetMarkerSize(1.8);
	h_2t_eta->SetMarkerSize(1.8);
        
	h0_pt->SetMarkerSize(1.8);
        h0_phi->SetMarkerSize(1.8);
        h0_eta->SetMarkerSize(1.8);
        ht0_pt->SetMarkerSize(1.8);
        ht0_phi->SetMarkerSize(1.8);
        ht0_eta->SetMarkerSize(1.8);

	//Marker Style	
	h_pt->SetMarkerStyle(kFullTriangleDown);
	h_phi->SetMarkerStyle(kFullTriangleDown);
	h_eta->SetMarkerStyle(kFullTriangleDown);
	ht_pt->SetMarkerStyle(kFullCircle);
	ht_phi->SetMarkerStyle(kFullCircle);
	ht_eta->SetMarkerStyle(kFullCircle);
	h__pt->SetMarkerStyle(kFullTriangleDown);
	h__phi->SetMarkerStyle(kFullTriangleDown);
	h__eta->SetMarkerStyle(kFullTriangleDown);
	h_t_pt->SetMarkerStyle(kFullCircle);
	h_t_phi->SetMarkerStyle(kFullCircle);
	h_t_eta->SetMarkerStyle(kFullCircle);
	h_1_pt->SetMarkerStyle(kFullTriangleDown);
	h_1_phi->SetMarkerStyle(kFullTriangleDown);
	h_1_eta->SetMarkerStyle(kFullTriangleDown);
	h_1t_pt->SetMarkerStyle(kFullCircle);
	h_1t_phi->SetMarkerStyle(kFullCircle);
	h_1t_eta->SetMarkerStyle(kFullCircle);
	h_2_pt->SetMarkerStyle(kFullTriangleDown);
	h_2_phi->SetMarkerStyle(kFullTriangleDown);
	h_2_eta->SetMarkerStyle(kFullTriangleDown);
	h_2t_pt->SetMarkerStyle(kFullCircle);
	h_2t_phi->SetMarkerStyle(kFullCircle);
	h_2t_eta->SetMarkerStyle(kFullCircle);
        
	h0_pt->SetMarkerStyle(kFullTriangleDown);
        h0_phi->SetMarkerStyle(kFullTriangleDown);
        h0_eta->SetMarkerStyle(kFullTriangleDown);
        ht0_pt->SetMarkerStyle(kFullCircle);
        ht0_phi->SetMarkerStyle(kFullCircle);
        ht0_eta->SetMarkerStyle(kFullCircle);

	h_pt->GetXaxis()->SetLabelFont(62);
	h_phi->GetXaxis()->SetLabelFont(62);
	h_eta->GetXaxis()->SetLabelFont(62);
	ht_pt->GetXaxis()->SetLabelFont(62);
	ht_phi->GetXaxis()->SetLabelFont(62);
	ht_eta->GetXaxis()->SetLabelFont(62);
	h__pt->GetXaxis()->SetLabelFont(62);
	h__phi->GetXaxis()->SetLabelFont(62);
	h__eta->GetXaxis()->SetLabelFont(62);
	h_t_pt->GetXaxis()->SetLabelFont(62);
	h_t_phi->GetXaxis()->SetLabelFont(62);
	h_t_eta->GetXaxis()->SetLabelFont(62);
	h_1_pt->GetXaxis()->SetLabelFont(62);
	h_1_phi->GetXaxis()->SetLabelFont(62);
	h_1_eta->GetXaxis()->SetLabelFont(62);
	h_1t_pt->GetXaxis()->SetLabelFont(62);
	h_1t_phi->GetXaxis()->SetLabelFont(62);
	h_1t_eta->GetXaxis()->SetLabelFont(62);
	h_2_pt->GetXaxis()->SetLabelFont(62);
	h_2_phi->GetXaxis()->SetLabelFont(62);
	h_2_eta->GetXaxis()->SetLabelFont(62);
	h_2t_pt->GetXaxis()->SetLabelFont(62);
	h_2t_phi->GetXaxis()->SetLabelFont(62);
	h_2t_eta->GetXaxis()->SetLabelFont(62);
        
	h0_pt->GetXaxis()->SetLabelFont(62);
        h0_phi->GetXaxis()->SetLabelFont(62);
        h0_eta->GetXaxis()->SetLabelFont(62);
        ht0_pt->GetXaxis()->SetLabelFont(62);
        ht0_phi->GetXaxis()->SetLabelFont(62);
        ht0_eta->GetXaxis()->SetLabelFont(62);
        
	h_pt->GetYaxis()->SetLabelFont(62);
	h_phi->GetYaxis()->SetLabelFont(62);
	h_eta->GetYaxis()->SetLabelFont(62);
	ht_pt->GetYaxis()->SetLabelFont(62);
	ht_phi->GetYaxis()->SetLabelFont(62);
	ht_eta->GetYaxis()->SetLabelFont(62);
	h__pt->GetYaxis()->SetLabelFont(62);
	h__phi->GetYaxis()->SetLabelFont(62);
	h__eta->GetYaxis()->SetLabelFont(62);
	h_t_pt->GetYaxis()->SetLabelFont(62);
	h_t_phi->GetYaxis()->SetLabelFont(62);
	h_t_eta->GetYaxis()->SetLabelFont(62);
	h_1_pt->GetYaxis()->SetLabelFont(62);
	h_1_phi->GetYaxis()->SetLabelFont(62);
	h_1_eta->GetYaxis()->SetLabelFont(62);
	h_1t_pt->GetYaxis()->SetLabelFont(62);
	h_1t_phi->GetYaxis()->SetLabelFont(62);
	h_1t_eta->GetYaxis()->SetLabelFont(62);
	h_2_pt->GetYaxis()->SetLabelFont(62);
	h_2_phi->GetYaxis()->SetLabelFont(62);
	h_2_eta->GetYaxis()->SetLabelFont(62);
	h_2t_pt->GetYaxis()->SetLabelFont(62);
	h_2t_phi->GetYaxis()->SetLabelFont(62);
	h_2t_eta->GetYaxis()->SetLabelFont(62);
        
	h0_pt->GetYaxis()->SetLabelFont(62);
        h0_phi->GetYaxis()->SetLabelFont(62);
        h0_eta->GetYaxis()->SetLabelFont(62);
        ht0_pt->GetYaxis()->SetLabelFont(62);
        ht0_phi->GetYaxis()->SetLabelFont(62);
        ht0_eta->GetYaxis()->SetLabelFont(62);
	
	h_pt->GetYaxis()->SetTitleOffset(.85);
	h_phi->GetYaxis()->SetTitleOffset(.85);
	h_eta->GetYaxis()->SetTitleOffset(.85);
	ht_pt->GetYaxis()->SetTitleOffset(.85);
	ht_phi->GetYaxis()->SetTitleOffset(.85);
	ht_eta->GetYaxis()->SetTitleOffset(.85);
	h__pt->GetYaxis()->SetTitleOffset(.85);
	h__phi->GetYaxis()->SetTitleOffset(.85);
	h__eta->GetYaxis()->SetTitleOffset(.85);
	h_t_pt->GetYaxis()->SetTitleOffset(.85);
	h_t_phi->GetYaxis()->SetTitleOffset(.85);
	h_t_eta->GetYaxis()->SetTitleOffset(.85);
	h_1_pt->GetYaxis()->SetTitleOffset(.85);
	h_1_phi->GetYaxis()->SetTitleOffset(.85);
	h_1_eta->GetYaxis()->SetTitleOffset(.85);
	h_1t_pt->GetYaxis()->SetTitleOffset(.85);
	h_1t_phi->GetYaxis()->SetTitleOffset(.85);
	h_1t_eta->GetYaxis()->SetTitleOffset(.85);
	h_2_pt->GetYaxis()->SetTitleOffset(.85);
	h_2_phi->GetYaxis()->SetTitleOffset(.85);
	h_2_eta->GetYaxis()->SetTitleOffset(.85);
	h_2t_pt->GetYaxis()->SetTitleOffset(.85);
	h_2t_phi->GetYaxis()->SetTitleOffset(.85);
	h_2t_eta->GetYaxis()->SetTitleOffset(.85);
        
	h0_pt->GetYaxis()->SetTitleOffset(.85);
        h0_phi->GetYaxis()->SetTitleOffset(.85);
        h0_eta->GetYaxis()->SetTitleOffset(.85);
        ht0_pt->GetYaxis()->SetTitleOffset(.85);
        ht0_phi->GetYaxis()->SetTitleOffset(.85);
        ht0_eta->GetYaxis()->SetTitleOffset(.85);
	
	h_pt->GetYaxis()->CenterTitle();
	h_phi->GetYaxis()->CenterTitle();
	h_eta->GetYaxis()->CenterTitle();
	ht_pt->GetYaxis()->CenterTitle();
	ht_phi->GetYaxis()->CenterTitle();
	ht_eta->GetYaxis()->CenterTitle();
	h__pt->GetYaxis()->CenterTitle();
	h__phi->GetYaxis()->CenterTitle();
	h__eta->GetYaxis()->CenterTitle();
	h_t_pt->GetYaxis()->CenterTitle();
	h_t_phi->GetYaxis()->CenterTitle();
	h_t_eta->GetYaxis()->CenterTitle();
	h_1_pt->GetYaxis()->CenterTitle();
	h_1_phi->GetYaxis()->CenterTitle();
	h_1_eta->GetYaxis()->CenterTitle();
	h_1t_pt->GetYaxis()->CenterTitle();
	h_1t_phi->GetYaxis()->CenterTitle();
	h_1t_eta->GetYaxis()->CenterTitle();
	h_2_pt->GetYaxis()->CenterTitle();
	h_2_phi->GetYaxis()->CenterTitle();
	h_2_eta->GetYaxis()->CenterTitle();
	h_2t_pt->GetYaxis()->CenterTitle();
	h_2t_phi->GetYaxis()->CenterTitle();
	h_2t_eta->GetYaxis()->CenterTitle();
        
	h0_pt->GetYaxis()->CenterTitle();
        h0_phi->GetYaxis()->CenterTitle();
        h0_eta->GetYaxis()->CenterTitle();
        ht0_pt->GetYaxis()->CenterTitle();
        ht0_phi->GetYaxis()->CenterTitle();
        ht0_eta->GetYaxis()->CenterTitle();
	
	h_pt->GetXaxis()->CenterTitle();
	h_phi->GetXaxis()->CenterTitle();
	h_eta->GetXaxis()->CenterTitle();
	ht_pt->GetXaxis()->CenterTitle();
	ht_phi->GetXaxis()->CenterTitle();
	ht_eta->GetXaxis()->CenterTitle();
	h__pt->GetXaxis()->CenterTitle();
	h__phi->GetXaxis()->CenterTitle();
	h__eta->GetXaxis()->CenterTitle();
	h_t_pt->GetXaxis()->CenterTitle();
	h_t_phi->GetXaxis()->CenterTitle();
	h_t_eta->GetXaxis()->CenterTitle();
	h_1_pt->GetXaxis()->CenterTitle();
	h_1_phi->GetXaxis()->CenterTitle();
	h_1_eta->GetXaxis()->CenterTitle();
	h_1t_pt->GetXaxis()->CenterTitle();
	h_1t_phi->GetXaxis()->CenterTitle();
	h_1t_eta->GetXaxis()->CenterTitle();
	h_2_pt->GetXaxis()->CenterTitle();
	h_2_phi->GetXaxis()->CenterTitle();
	h_2_eta->GetXaxis()->CenterTitle();
	h_2t_pt->GetXaxis()->CenterTitle();
	h_2t_phi->GetXaxis()->CenterTitle();
	h_2t_eta->GetXaxis()->CenterTitle();
        
	h0_pt->GetXaxis()->CenterTitle();
        h0_phi->GetXaxis()->CenterTitle();
        h0_eta->GetXaxis()->CenterTitle();
        ht0_pt->GetXaxis()->CenterTitle();
        ht0_phi->GetXaxis()->CenterTitle();
        ht0_eta->GetXaxis()->CenterTitle();
	
	h_pt->GetYaxis()->SetTitleSize(.05);
	h_phi->GetYaxis()->SetTitleSize(.05);
	h_eta->GetYaxis()->SetTitleSize(.05);
	ht_pt->GetYaxis()->SetTitleSize(.05);
	ht_phi->GetYaxis()->SetTitleSize(.05);
	ht_eta->GetYaxis()->SetTitleSize(.05);
	h__pt->GetYaxis()->SetTitleSize(.05);
	h__phi->GetYaxis()->SetTitleSize(.05);
	h__eta->GetYaxis()->SetTitleSize(.05);
	h_t_pt->GetYaxis()->SetTitleSize(.05);
	h_t_phi->GetYaxis()->SetTitleSize(.05);
	h_t_eta->GetYaxis()->SetTitleSize(.05);
	h_1_pt->GetYaxis()->SetTitleSize(.05);
	h_1_phi->GetYaxis()->SetTitleSize(.05);
	h_1_eta->GetYaxis()->SetTitleSize(.05);
	h_1t_pt->GetYaxis()->SetTitleSize(.05);
	h_1t_phi->GetYaxis()->SetTitleSize(.05);
	h_1t_eta->GetYaxis()->SetTitleSize(.05);
	h_2_pt->GetYaxis()->SetTitleSize(.05);
	h_2_phi->GetYaxis()->SetTitleSize(.05);
	h_2_eta->GetYaxis()->SetTitleSize(.05);
	h_2t_pt->GetYaxis()->SetTitleSize(.05);
	h_2t_phi->GetYaxis()->SetTitleSize(.05);
	h_2t_eta->GetYaxis()->SetTitleSize(.05);
        
	h0_pt->GetYaxis()->SetTitleSize(.05);
        h0_phi->GetYaxis()->SetTitleSize(.05);
        h0_eta->GetYaxis()->SetTitleSize(.05);
        ht0_pt->GetYaxis()->SetTitleSize(.05);
        ht0_phi->GetYaxis()->SetTitleSize(.05);
        ht0_eta->GetYaxis()->SetTitleSize(.05);

	h_pt->GetYaxis()->SetRangeUser(0.7,1.04);
	h_phi->GetYaxis()->SetRangeUser(0.7,1.04);
	h_eta->GetYaxis()->SetRangeUser(0.5,1.04);
	ht_pt->GetYaxis()->SetRangeUser(0.7,1.04);
	ht_phi->GetYaxis()->SetRangeUser(0.7,1.04);
	ht_eta->GetYaxis()->SetRangeUser(0.5,1.04);
	h__pt->GetYaxis()->SetRangeUser(0.7,1.04);
	h__phi->GetYaxis()->SetRangeUser(0.7,1.04);
	h__eta->GetYaxis()->SetRangeUser(0.5,1.04);
	h_t_pt->GetYaxis()->SetRangeUser(0.7,1.04);
	h_t_phi->GetYaxis()->SetRangeUser(0.7,1.04);
	h_t_eta->GetYaxis()->SetRangeUser(0.5,1.04);
	h_1_pt->GetYaxis()->SetRangeUser(0.7,1.04);
	h_1_phi->GetYaxis()->SetRangeUser(0.7,1.04);
	h_1_eta->GetYaxis()->SetRangeUser(0.5,1.04);
	h_1t_pt->GetYaxis()->SetRangeUser(0.7,1.04);
	h_1t_phi->GetYaxis()->SetRangeUser(0.7,1.04);
	h_1t_eta->GetYaxis()->SetRangeUser(0.5,1.04);
	h_2_pt->GetYaxis()->SetRangeUser(0.7,1.04);
	h_2_phi->GetYaxis()->SetRangeUser(0.7,1.04);
	h_2_eta->GetYaxis()->SetRangeUser(0.5,1.04);
	h_2t_pt->GetYaxis()->SetRangeUser(0.7,1.04);
	h_2t_phi->GetYaxis()->SetRangeUser(0.7,1.04);
	h_2t_eta->GetYaxis()->SetRangeUser(0.5,1.04);
        
	h0_pt->GetYaxis()->SetRangeUser(0.9,1.04);
        h0_phi->GetYaxis()->SetRangeUser(0.9,1.04);
        h0_eta->GetYaxis()->SetRangeUser(0.9,1.04);
        ht0_pt->GetYaxis()->SetRangeUser(0.9,1.04);
        ht0_phi->GetYaxis()->SetRangeUser(0.9,1.04);
        ht0_eta->GetYaxis()->SetRangeUser(0.9,1.04);

	h_pt->GetXaxis()->SetTitleOffset(.85);
	h_phi->GetXaxis()->SetTitleOffset(.85);
	h_eta->GetXaxis()->SetTitleOffset(.85);
	ht_pt->GetXaxis()->SetTitleOffset(.85);
	ht_phi->GetXaxis()->SetTitleOffset(.85);
	ht_eta->GetXaxis()->SetTitleOffset(.85);
	h__pt->GetXaxis()->SetTitleOffset(.85);
	h__phi->GetXaxis()->SetTitleOffset(.85);
	h__eta->GetXaxis()->SetTitleOffset(.85);
	h_t_pt->GetXaxis()->SetTitleOffset(.85);
	h_t_phi->GetXaxis()->SetTitleOffset(.85);
	h_t_eta->GetXaxis()->SetTitleOffset(.85);
	h_1_pt->GetXaxis()->SetTitleOffset(.85);
	h_1_phi->GetXaxis()->SetTitleOffset(.85);
	h_1_eta->GetXaxis()->SetTitleOffset(.85);
	h_1t_pt->GetXaxis()->SetTitleOffset(.85);
	h_1t_phi->GetXaxis()->SetTitleOffset(.85);
	h_1t_eta->GetXaxis()->SetTitleOffset(.85);
	h_2_pt->GetXaxis()->SetTitleOffset(.85);
	h_2_phi->GetXaxis()->SetTitleOffset(.85);
	h_2_eta->GetXaxis()->SetTitleOffset(.85);
	h_2t_pt->GetXaxis()->SetTitleOffset(.85);
	h_2t_phi->GetXaxis()->SetTitleOffset(.85);
	h_2t_eta->GetXaxis()->SetTitleOffset(.85);
        
	h0_pt->GetXaxis()->SetTitleOffset(.85);
        h0_phi->GetXaxis()->SetTitleOffset(.85);
        h0_eta->GetXaxis()->SetTitleOffset(.85);
        ht0_pt->GetXaxis()->SetTitleOffset(.85);
        ht0_phi->GetXaxis()->SetTitleOffset(.85);
        ht0_eta->GetXaxis()->SetTitleOffset(.85);
	

	h_pt->GetXaxis()->SetTitleSize(.05);
	h_phi->GetXaxis()->SetTitleSize(.05);
	h_eta->GetXaxis()->SetTitleSize(.05);
	ht_pt->GetXaxis()->SetTitleSize(.05);
	ht_phi->GetXaxis()->SetTitleSize(.05);
	ht_eta->GetXaxis()->SetTitleSize(.05);
	h__pt->GetXaxis()->SetTitleSize(.05);
	h__phi->GetXaxis()->SetTitleSize(.05);
	h__eta->GetXaxis()->SetTitleSize(.05);
	h_t_pt->GetXaxis()->SetTitleSize(.05);
	h_t_phi->GetXaxis()->SetTitleSize(.05);
	h_t_eta->GetXaxis()->SetTitleSize(.05);
	h_1_pt->GetXaxis()->SetTitleSize(.05);
	h_1_phi->GetXaxis()->SetTitleSize(.05);
	h_1_eta->GetXaxis()->SetTitleSize(.05);
	h_1t_pt->GetXaxis()->SetTitleSize(.05);
	h_1t_phi->GetXaxis()->SetTitleSize(.05);
	h_1t_eta->GetXaxis()->SetTitleSize(.05);
	h_2_pt->GetXaxis()->SetTitleSize(.05);
	h_2_phi->GetXaxis()->SetTitleSize(.05);
	h_2_eta->GetXaxis()->SetTitleSize(.05);
	h_2t_pt->GetXaxis()->SetTitleSize(.05);
	h_2t_phi->GetXaxis()->SetTitleSize(.05);
	h_2t_eta->GetXaxis()->SetTitleSize(.05);
        
	h0_pt->GetXaxis()->SetTitleSize(.05);
        h0_phi->GetXaxis()->SetTitleSize(.05);
        h0_eta->GetXaxis()->SetTitleSize(.05);
        ht0_pt->GetXaxis()->SetTitleSize(.05);
        ht0_phi->GetXaxis()->SetTitleSize(.05);
        ht0_eta->GetXaxis()->SetTitleSize(.05);
	
	h_pt->GetXaxis()->SetTitle("p_{t} [MeV/c]");
	h_phi->GetXaxis()->SetTitle("#phi [rad]");
	h_eta->GetXaxis()->SetTitle("#eta");
	ht_pt->GetXaxis()->SetTitle("p_{t} [MeV/c]");
	ht_phi->GetXaxis()->SetTitle("#phi [rad]");
	ht_eta->GetXaxis()->SetTitle("#eta");
	h__pt->GetXaxis()->SetTitle("p_{t} [MeV/c]");
	h__phi->GetXaxis()->SetTitle("#phi [rad]");
	h__eta->GetXaxis()->SetTitle("#eta");
	h_t_pt->GetXaxis()->SetTitle("p_{t} [MeV/c]");
	h_t_phi->GetXaxis()->SetTitle("#phi [rad]");
	h_t_eta->GetXaxis()->SetTitle("#eta");
	h_1_pt->GetXaxis()->SetTitle("p_{t} [MeV/c]");
	h_1_phi->GetXaxis()->SetTitle("#phi [rad]");
	h_1_eta->GetXaxis()->SetTitle("#eta");
	h_1t_pt->GetXaxis()->SetTitle("p_{t} [MeV/c]");
	h_1t_phi->GetXaxis()->SetTitle("#phi [rad]");
	h_1t_eta->GetXaxis()->SetTitle("#eta");
	h_2_pt->GetXaxis()->SetTitle("p_{t} [MeV/c]");
	h_2_phi->GetXaxis()->SetTitle("#phi [rad]");
	h_2_eta->GetXaxis()->SetTitle("#eta");
	h_2t_pt->GetXaxis()->SetTitle("p_{t} [MeV/c]");
	h_2t_phi->GetXaxis()->SetTitle("#phi [rad]");
	h_2t_eta->GetXaxis()->SetTitle("#eta");
        
	h0_pt->GetXaxis()->SetTitle("p_{t} [MeV/c]");
        h0_phi->GetXaxis()->SetTitle("#phi [rad]");
        h0_eta->GetXaxis()->SetTitle("#eta");
        ht0_pt->GetXaxis()->SetTitle("p_{t} [MeV/c]");
        ht0_phi->GetXaxis()->SetTitle("#phi [rad]");
        ht0_eta->GetXaxis()->SetTitle("#eta");
	
	
	TCanvas * C = new TCanvas();
	gStyle->SetOptStat(0);
	TGaxis::SetMaxDigits(2);
	C->SetGridx();
	C->SetGridy();
	C->SetTickx();
	C->SetTicky();
	
	C->SetLogx();
	h_pt->Draw();
	C->Print(out_file_open, "pdf");
	h0_pt->Draw();
	C->Print(out_file_,"pdf");
	ht_pt->Draw();
	C->Print(out_file_, "pdf");
	ht0_pt->Draw();
	C->Print(out_file_,"pdf");

	C->SetLogx(0);
	h_phi->Draw();
	C->Print(out_file_, "pdf");
	h0_phi->Draw();
	C->Print(out_file_,"pdf");
	ht_phi->Draw();
	C->Print(out_file_, "pdf");
	ht0_phi->Draw();
	C->Print(out_file_,"pdf");
	
	h_eta->Draw();
	C->Print(out_file_, "pdf");
	h0_eta->Draw();
	C->Print(out_file_,"pdf");
	ht_eta->Draw();
	C->Print(out_file_, "pdf");
	ht0_eta->Draw();
	C->Print(out_file_,"pdf");
	
	//plot same
	
	Double_t x1= 0.7,y1= 0.75, x2 = 0.9, y2 = 0.9;
	C->SetLogx();
	h_pt->Draw();
	ht_pt->Draw("same");
	TLegend *leg1=new TLegend(x1,y1,x2,y2,"");
	leg1->SetFillColor(kWhite);
	leg1->SetBorderSize(0);
	leg1->AddEntry(h_pt,"Offline tracks");
	leg1->AddEntry(ht_pt,"Triplet tracks");
	leg1->Draw();
	C->Print(out_file_,"pdf");
	h0_pt->Draw();
	ht0_pt->Draw("same");
	TLegend *leg2=new TLegend(x1,y1,x2,y2,"");
	leg2->SetFillColor(kWhite);
	leg2->SetBorderSize(0);
	leg2->AddEntry(h0_pt,"InDet tracks");
	leg2->AddEntry(ht0_pt,"TTT tracks");
	leg2->Draw();
	C->Print(out_file_,"pdf");

	h_pt->Draw();
	ht_pt->Draw("same");
	h__pt->Draw("same");
	h_t_pt->Draw("same");
	h_1_pt->Draw("same");
	h_1t_pt->Draw("same");
	h_2_pt->Draw("same");
	h_2t_pt->Draw("same");
	TLegend *leg1_=new TLegend(0.25,0.3,0.4,0.36,"");
	leg1_->SetFillColor(0);
	leg1_->SetBorderSize(0);
	leg1_->AddEntry((TObject*)0,"InDet   TTT","");
	leg1_->Draw();
	TLegend *leg1a=new TLegend(0.285,0.1,0.6,0.3,"");
	leg1a->SetNColumns(2);
	leg1a->SetFillColor(kWhite);
	leg1a->SetBorderSize(0);
	leg1a->AddEntry(h_pt,",");
	leg1a->AddEntry(ht_pt,"abs(#eta) < 1.4");
	leg1a->AddEntry(h__pt,",");
	leg1a->AddEntry(h_t_pt,"abs(#eta) < 1.2");
	leg1a->AddEntry(h_1_pt,",");
	leg1a->AddEntry(h_1t_pt,"abs(#eta) < 1.0");
	leg1a->AddEntry(h_2_pt,",");
	leg1a->AddEntry(h_2t_pt,"abs(#eta) < 0.8");
	leg1a->Draw();
	C->Print(out_file_,"pdf");
	
	h0_pt->Draw();
	ht0_pt->Draw("same");
	TLegend *leg2=new TLegend(x1,y1,x2,y2,"");
	leg2->SetFillColor(kWhite);
	leg2->SetBorderSize(0);
	leg2->AddEntry(h0_pt,"InDet tracks");
	leg2->AddEntry(ht0_pt,"TTT tracks");
	leg2->Draw();
	C->Print(out_file_,"pdf");

	C->SetLogx(0);
	h_phi->Draw();
	ht_phi->Draw("same");
	TLegend *leg3=new TLegend(x1,y1,x2,y2,"");
	leg3->SetFillColor(kWhite);
	leg3->SetBorderSize(0);
        leg3->AddEntry(h_phi,"InDet tracks");
        leg3->AddEntry(ht_phi,"TTT tracks");
        leg3->Draw();
	C->Print(out_file_,"pdf");
	h0_phi->Draw();
	ht0_phi->Draw("same");
	TLegend *leg4=new TLegend(x1,y1,x2,y2,"");
	leg4->SetFillColor(kWhite);
	leg4->SetBorderSize(0);
        leg4->AddEntry(h0_phi,"InDet tracks");
        leg4->AddEntry(ht0_phi,"TTT tracks");
        leg4->Draw();
	C->Print(out_file_,"pdf");

	h_eta->Draw();
	ht_eta->Draw("same");
	TLegend *leg5=new TLegend(x1,y1,x2,y2,"");
	leg5->SetFillColor(kWhite);
	leg5->SetBorderSize(0);
        leg5->AddEntry(h_eta,"InDet tracks");
        leg5->AddEntry(ht_eta,"TTT tracks");
        leg5->Draw();
	C->Print(out_file_,"pdf");
	h0_eta->Draw();
	ht0_eta->Draw("same");
	TLegend *leg6=new TLegend(x1,y1,x2,y2,"");
	leg6->SetFillColor(kWhite);
	leg6->SetBorderSize(0);
        leg6->AddEntry(h0_eta,"InDet tracks");
        leg6->AddEntry(ht0_eta,"TTT tracks");
        leg6->Draw();
	C->Print(out_file_,"pdf");
	

	//two scales eta phi
	C->SetTicky(0);
	h__eta->GetYaxis()->SetAxisColor(kBlue);
	h__eta->GetYaxis()->SetTitleColor(kBlue);
	h__eta->GetYaxis()->SetTitleSize(0.05);
	h__eta->GetYaxis()->SetLabelColor(kBlue);
	h__eta->SetLineColor(kBlue);
	h_t_eta->SetLineColor(kBlue);
	h__eta->SetMarkerColor(kBlue);
	h_t_eta->SetMarkerColor(kBlue);	
	h__eta->Draw();
	h_t_eta->Draw("same");
	C->Update();
	Float_t rightmax = 1*h0_eta->GetMaximum();
	Float_t scale = gPad->GetUymax()/rightmax;
	h0_eta->SetLineColor(kRed);
	ht0_eta->SetLineColor(kRed);
	h0_eta->SetMarkerColor(kRed);
	ht0_eta->SetMarkerColor(kRed);
	h0_eta->Scale(scale);
	h0_eta->Draw("same");
	ht0_eta->Draw("same");
	//draw an axis on the right side
	TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	gPad->GetUxmax(), gPad->GetUymax(),0.5,rightmax,510,"+L");
	axis->SetLineColor(kRed);
	axis->SetLabelColor(kRed);
//	axis->SetLabelSize(0.05);
	axis->SetTitle("purity");
	axis->SetTitleColor(kRed);
	axis->SetTitleSize(0.05);
	axis->SetTitleOffset(1.08);
	axis->SetMaxDigits(2);
	axis->CenterTitle();
	axis->Draw();
	
	C->Print(out_file_,"pdf");
	h__phi->GetYaxis()->SetAxisColor(kBlue);
	h__phi->GetYaxis()->SetTitleColor(kBlue);
	h__phi->GetYaxis()->SetTitleSize(0.05);
	h__phi->GetYaxis()->SetLabelColor(kBlue);
	h__phi->SetLineColor(kBlue);
	h_t_phi->SetLineColor(kBlue);
	h__phi->SetMarkerColor(kBlue);
	h_t_phi->SetMarkerColor(kBlue);	
	h__phi->Draw();
	h_t_phi->Draw("same");
	C->Update();
	rightmax = 1*h0_phi->GetMaximum();
	scale = gPad->GetUymax()/rightmax;
	h0_phi->SetLineColor(kRed);
	ht0_phi->SetLineColor(kRed);
	h0_phi->SetMarkerColor(kRed);
	ht0_phi->SetMarkerColor(kRed);
	h0_phi->Scale(scale);
	h0_phi->Draw("same");
	ht0_phi->Draw("same");
	//draw an axis on the right side
	TGaxis *axis1 = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	gPad->GetUxmax(), gPad->GetUymax(),0.7,rightmax,510,"+L");
	axis1->SetLineColor(kRed);
	axis1->SetLabelColor(kRed);
//	axis->SetLabelSize(0.05);
	axis1->SetTitle("purity");
	axis1->SetTitleColor(kRed);
	axis1->SetTitleSize(0.05);
	axis1->SetTitleOffset(1.08);
	axis1->SetMaxDigits(2);
	axis1->CenterTitle();
	axis1->Draw();
	
	C->Print(out_file_,"pdf");
	h__pt->GetYaxis()->SetAxisColor(kBlue);
	h__pt->GetYaxis()->SetTitleColor(kBlue);
	h__pt->GetYaxis()->SetTitleSize(0.05);
	h__pt->GetYaxis()->SetLabelColor(kBlue);
	h__pt->SetLineColor(kBlue);
	h_t_pt->SetLineColor(kBlue);
	h__pt->SetMarkerColor(kBlue);
	h_t_pt->SetMarkerColor(kBlue);	
	h__pt->Draw();
	h_t_pt->Draw("same");
	C->Update();
	rightmax = 1*h0_pt->GetMaximum();
	scale = gPad->GetUymax()/rightmax;
	h0_pt->SetLineColor(kRed);
	ht0_pt->SetLineColor(kRed);
	h0_pt->SetMarkerColor(kRed);
	ht0_pt->SetMarkerColor(kRed);
	h0_pt->Scale(scale);
	h0_pt->Draw("same");
	ht0_pt->Draw("same");
	//draw an axis on the right side
	TGaxis *axis2 = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	gPad->GetUxmax(), gPad->GetUymax(),0.7,rightmax,510,"+L");
	axis2->SetLineColor(kRed);
	axis2->SetLabelColor(kRed);
//	axis->SetLabelSize(0.05);
	axis2->SetTitle("purity");
	axis2->SetTitleColor(kRed);
	axis2->SetTitleSize(0.05);
	axis2->SetTitleOffset(1.08);
	axis2->SetMaxDigits(2);
	axis2->CenterTitle();
	axis2->Draw();
	C->SetLogx();
	
	C->Print(out_file_,"pdf");
	C->Clear();
	h_pt->SetMarkerColor(kBlack);
	ht_pt->SetMarkerColor(kBlack);
	h_pt->SetLineColor(kBlack);
	ht_pt->SetLineColor(kBlack);
	leg1->Draw();
	C->Print(out_file_,"pdf");
	C->Clear();
	h_pt->SetMarkerColor(kRed);
	ht_pt->SetMarkerColor(kRed);
	h_pt->SetLineColor(kRed);
	ht_pt->SetLineColor(kRed);
	leg1->Draw();


	C->Print(out_file_close,"pdf");
return 0;
}

int writeEff_topdf(const char* output_file_name = "EffVsEtaPtPhi_TTTsig5L6BMatchedfinal")
{

	char out_file_open[1023];
        sprintf(out_file_open,"%s/%s.pdf(",out_path,output_file_name);
        char out_file_[1023];
        sprintf(out_file_,"%s/%s.pdf",out_path,output_file_name);
        char out_file_close[1023];
        sprintf(out_file_close,"%s/%s.pdf)",out_path,output_file_name);
	//!efficiency /*Indet and*/ TTT tracks barcode matched
	TFile* f = TFile::Open("./plots/efficiency/eff_InDetTTTdR0.01_eta1.4Bfinal.root");
	//TFile* f = TFile::Open("./plots/efficiency/eff_InDetTTTdR0.01_eta1.4B.root");
	/*TH1D* h_pt 	= (TH1D*)f->Get("h_eff_vs_ptInDet");
	TH1D* h_phi	= (TH1D*)f->Get("h_eff_vs_phiInDet");
	TH1D* h_eta	= (TH1D*)f->Get("h_eff_vs_etaInDet");
	*/TH1D* h_pt 	= (TH1D*)f->Get("h_eff_vs_ptPU");
	TH1D* h_phi	= (TH1D*)f->Get("h_eff_vs_phiPU");
	TH1D* h_eta	= (TH1D*)f->Get("h_eff_vs_etaPU");
	//! efficieny with sig5 layer = 6 and Barrel , barcode matched 
	TFile* f_ = TFile::Open("./plots/efficiency/preveffsig5L6BTTT_barcode_mufinal.root");
	/*TH1D* h_pt 	= (TH1D*)f->Get("h_eff_vs_ptInDet");
	TH1D* h_phi	= (TH1D*)f->Get("h_eff_vs_phiInDet");
	TH1D* h_eta	= (TH1D*)f->Get("h_eff_vs_etaInDet");
	*/TH1D* ht_pt 	= (TH1D*)f_->Get("h_eff_vs_ptPU");
	TH1D* ht_phi	= (TH1D*)f_->Get("h_eff_vs_phiPU");
	TH1D* ht_eta	= (TH1D*)f_->Get("h_eff_vs_etaPU");

	//! purity Indet tracks
/*	TFile* f0 = TFile::Open("./plots/purity/pur_InDetdR0.01_eta1.4.root");
	TH1D* h0_pt 	= (TH1D*)f0->Get("h_pur_vs_ptPU");
	TH1D* h0_phi	= (TH1D*)f0->Get("h_pur_vs_phiPU");
	TH1D* h0_eta	= (TH1D*)f0->Get("h_pur_vs_etaPU");
	//! purity TTT barcode matched tracks
	TFile* f0t = TFile::Open("./plots/purity/pur_TTTBMatched_eta1.4.root");
	TH1D* ht0_pt = (TH1D*)f0t->Get("h_pur_vs_ptPU");
	TH1D* ht0_phi	= (TH1D*)f0t->Get("h_pur_vs_phiPU");
	TH1D* ht0_eta	= (TH1D*)f0t->Get("h_pur_vs_etaPU");
*/

	h_pt->SetStats(0);
       	h_phi->SetStats(0);
       	h_eta->SetStats(0);
/*        h0_pt->SetStats(0);
        h0_phi->SetStats(0);
        h0_eta->SetStats(0);
*/	ht_pt->SetStats(0);
       	ht_phi->SetStats(0);
       	ht_eta->SetStats(0);
/*        ht0_pt->SetStats(0);
        ht0_phi->SetStats(0);
        ht0_eta->SetStats(0);
*/ 	
	// SET Markercolour
	//! efficiency in blue
	//! purity in red
	h_pt->SetMarkerColor(kBlue);
	h_phi->SetMarkerColor(kBlue);
	h_eta->SetMarkerColor(kBlue);
/*        h0_pt->SetMarkerColor(kRed);
        h0_phi->SetMarkerColor(kRed);
        h0_eta->SetMarkerColor(kRed);
*/	ht_pt->SetMarkerColor(kBlack);
	ht_phi->SetMarkerColor(kBlack);
	ht_eta->SetMarkerColor(kBlack);
/*        ht0_pt->SetMarkerColor(kRed);
        ht0_phi->SetMarkerColor(kRed);
        ht0_eta->SetMarkerColor(kRed);
*/	
	//Marker Size	
	h_pt->SetMarkerSize(1.8);
	h_phi->SetMarkerSize(1.8);
	h_eta->SetMarkerSize(1.8);
/*        h0_pt->SetMarkerSize(1.8);
        h0_phi->SetMarkerSize(1.8);
        h0_eta->SetMarkerSize(1.8);
*/	ht_pt->SetMarkerSize(1.8);
	ht_phi->SetMarkerSize(1.8);
	ht_eta->SetMarkerSize(1.8);
/*        ht0_pt->SetMarkerSize(1.8);
        ht0_phi->SetMarkerSize(1.8);
        ht0_eta->SetMarkerSize(1.8);
*/
	//Marker Style	
	h_pt->SetMarkerStyle(kFullCircle);
	h_phi->SetMarkerStyle(kFullCircle);
	h_eta->SetMarkerStyle(kFullCircle);
/*        h0_pt->SetMarkerStyle(kFullTriangleDown);
        h0_phi->SetMarkerStyle(kFullTriangleDown);
        h0_eta->SetMarkerStyle(kFullTriangleDown);
*/	ht_pt->SetMarkerStyle(kFullCircle);
	ht_phi->SetMarkerStyle(kFullCircle);
	ht_eta->SetMarkerStyle(kFullCircle);
/*        ht0_pt->SetMarkerStyle(kFullCircle);
        ht0_phi->SetMarkerStyle(kFullCircle);
        ht0_eta->SetMarkerStyle(kFullCircle);
*/
	h_pt->GetXaxis()->SetLabelFont(62);
	h_phi->GetXaxis()->SetLabelFont(62);
	h_eta->GetXaxis()->SetLabelFont(62);
/*        h0_pt->GetXaxis()->SetLabelFont(62);
        h0_phi->GetXaxis()->SetLabelFont(62);
        h0_eta->GetXaxis()->SetLabelFont(62);
*/	ht_pt->GetXaxis()->SetLabelFont(62);
	ht_phi->GetXaxis()->SetLabelFont(62);
	ht_eta->GetXaxis()->SetLabelFont(62);
/*        ht0_pt->GetXaxis()->SetLabelFont(62);
        ht0_phi->GetXaxis()->SetLabelFont(62);
        ht0_eta->GetXaxis()->SetLabelFont(62);
*/        
	h_pt->GetYaxis()->SetLabelFont(62);
	h_phi->GetYaxis()->SetLabelFont(62);
	h_eta->GetYaxis()->SetLabelFont(62);
/*        h0_pt->GetYaxis()->SetLabelFont(62);
        h0_phi->GetYaxis()->SetLabelFont(62);
        h0_eta->GetYaxis()->SetLabelFont(62);
*/	ht_pt->GetYaxis()->SetLabelFont(62);
	ht_phi->GetYaxis()->SetLabelFont(62);
	ht_eta->GetYaxis()->SetLabelFont(62);
/*        ht0_pt->GetYaxis()->SetLabelFont(62);
        ht0_phi->GetYaxis()->SetLabelFont(62);
        ht0_eta->GetYaxis()->SetLabelFont(62);
*/	
	h_pt->GetYaxis()->SetTitleOffset(.85);
	h_phi->GetYaxis()->SetTitleOffset(.85);
	h_eta->GetYaxis()->SetTitleOffset(.85);
/*        h0_pt->GetYaxis()->SetTitleOffset(.85);
        h0_phi->GetYaxis()->SetTitleOffset(.85);
        h0_eta->GetYaxis()->SetTitleOffset(.85);
*/	ht_pt->GetYaxis()->SetTitleOffset(.85);
	ht_phi->GetYaxis()->SetTitleOffset(.85);
	ht_eta->GetYaxis()->SetTitleOffset(.85);
/*        ht0_pt->GetYaxis()->SetTitleOffset(.85);
        ht0_phi->GetYaxis()->SetTitleOffset(.85);
        ht0_eta->GetYaxis()->SetTitleOffset(.85);
*/	
	h_pt->GetYaxis()->CenterTitle();
	h_phi->GetYaxis()->CenterTitle();
	h_eta->GetYaxis()->CenterTitle();
/*        h0_pt->GetYaxis()->CenterTitle();
        h0_phi->GetYaxis()->CenterTitle();
        h0_eta->GetYaxis()->CenterTitle();
*/	ht_pt->GetYaxis()->CenterTitle();
	ht_phi->GetYaxis()->CenterTitle();
	ht_eta->GetYaxis()->CenterTitle();
/*        ht0_pt->GetYaxis()->CenterTitle();
        ht0_phi->GetYaxis()->CenterTitle();
        ht0_eta->GetYaxis()->CenterTitle();
*/	h_pt->GetXaxis()->CenterTitle();
	h_phi->GetXaxis()->CenterTitle();
	h_eta->GetXaxis()->CenterTitle();
/*        h0_pt->GetXaxis()->CenterTitle();
        h0_phi->GetXaxis()->CenterTitle();
        h0_eta->GetXaxis()->CenterTitle();
*/	ht_pt->GetXaxis()->CenterTitle();
	ht_phi->GetXaxis()->CenterTitle();
	ht_eta->GetXaxis()->CenterTitle();
/*        ht0_pt->GetXaxis()->CenterTitle();
        ht0_phi->GetXaxis()->CenterTitle();
        ht0_eta->GetXaxis()->CenterTitle();
*/	
	h_pt->GetYaxis()->SetTitleSize(.05);
	h_phi->GetYaxis()->SetTitleSize(.05);
	h_eta->GetYaxis()->SetTitleSize(.05);
/*        h0_pt->GetYaxis()->SetTitleSize(.05);
        h0_phi->GetYaxis()->SetTitleSize(.05);
        h0_eta->GetYaxis()->SetTitleSize(.05);
*/	ht_pt->GetYaxis()->SetTitleSize(.05);
	ht_phi->GetYaxis()->SetTitleSize(.05);
	ht_eta->GetYaxis()->SetTitleSize(.05);
/*        ht0_pt->GetYaxis()->SetTitleSize(.05);
        ht0_phi->GetYaxis()->SetTitleSize(.05);
        ht0_eta->GetYaxis()->SetTitleSize(.05);
*/
	h_pt->GetYaxis()->SetRangeUser(0.7,1.04);
	h_phi->GetYaxis()->SetRangeUser(0.7,1.04);
	h_eta->GetYaxis()->SetRangeUser(0.5,1.04);
/*        h0_pt->GetYaxis()->SetRangeUser(0.9,1.04);
        h0_phi->GetYaxis()->SetRangeUser(0.9,1.04);
        h0_eta->GetYaxis()->SetRangeUser(0.9,1.04);
*/	ht_pt->GetYaxis()->SetRangeUser(0.7,1.04);
	ht_phi->GetYaxis()->SetRangeUser(0.7,1.04);
	ht_eta->GetYaxis()->SetRangeUser(0.5,1.04);
/*        ht0_pt->GetYaxis()->SetRangeUser(0.9,1.04);
        ht0_phi->GetYaxis()->SetRangeUser(0.9,1.04);
        ht0_eta->GetYaxis()->SetRangeUser(0.9,1.04);
*/
	h_pt->GetXaxis()->SetTitleOffset(.85);
	h_phi->GetXaxis()->SetTitleOffset(.85);
	h_eta->GetXaxis()->SetTitleOffset(.85);
/*        h0_pt->GetXaxis()->SetTitleOffset(.85);
        h0_phi->GetXaxis()->SetTitleOffset(.85);
        h0_eta->GetXaxis()->SetTitleOffset(.85);
*/	
	ht_pt->GetXaxis()->SetTitleOffset(.85);
	ht_phi->GetXaxis()->SetTitleOffset(.85);
	ht_eta->GetXaxis()->SetTitleOffset(.85);
/*        ht0_pt->GetXaxis()->SetTitleOffset(.85);
        ht0_phi->GetXaxis()->SetTitleOffset(.85);
        ht0_eta->GetXaxis()->SetTitleOffset(.85);
*/	

	h_pt->GetXaxis()->SetTitleSize(.05);
	h_phi->GetXaxis()->SetTitleSize(.05);
	h_eta->GetXaxis()->SetTitleSize(.05);
/*        h0_pt->GetXaxis()->SetTitleSize(.05);
        h0_phi->GetXaxis()->SetTitleSize(.05);
        h0_eta->GetXaxis()->SetTitleSize(.05);
*/	
	ht_pt->GetXaxis()->SetTitleSize(.05);
	ht_phi->GetXaxis()->SetTitleSize(.05);
	ht_eta->GetXaxis()->SetTitleSize(.05);
/*        ht0_pt->GetXaxis()->SetTitleSize(.05);
        ht0_phi->GetXaxis()->SetTitleSize(.05);
        ht0_eta->GetXaxis()->SetTitleSize(.05);
*/	
	h_pt->GetXaxis()->SetTitle("p_{t} [MeV/c]");
	h_phi->GetXaxis()->SetTitle("#phi [rad]");
	h_eta->GetXaxis()->SetTitle("#eta");
/*        h0_pt->GetXaxis()->SetTitle("p_{t} [MeV/c]");
        h0_phi->GetXaxis()->SetTitle("#phi [rad]");
        h0_eta->GetXaxis()->SetTitle("#eta");
*/	
	ht_pt->GetXaxis()->SetTitle("p_{t} [MeV/c]");
	ht_phi->GetXaxis()->SetTitle("#phi [rad]");
	ht_eta->GetXaxis()->SetTitle("#eta");
/*        ht0_pt->GetXaxis()->SetTitle("p_{t} [MeV/c]");
        ht0_phi->GetXaxis()->SetTitle("#phi [rad]");
        ht0_eta->GetXaxis()->SetTitle("#eta");
*/	
	
	TCanvas * C = new TCanvas();
	gStyle->SetOptStat(0);
	TGaxis::SetMaxDigits(2);
	C->SetGridx();
	C->SetGridy();
	C->SetTickx();
	C->SetTicky();
	
	C->SetLogx();
	h_pt->Draw();
	C->Print(out_file_open, "pdf");
/*	h0_pt->Draw();
	C->Print(out_file_,"pdf");
*/	ht_pt->Draw();
	C->Print(out_file_, "pdf");
/*	ht0_pt->Draw();
	C->Print(out_file_,"pdf");
*/
	C->SetLogx(0);
	h_phi->Draw();
	C->Print(out_file_, "pdf");
/*	h0_phi->Draw();
	C->Print(out_file_,"pdf");
*/	ht_phi->Draw();
	C->Print(out_file_, "pdf");
/*	ht0_phi->Draw();
	C->Print(out_file_,"pdf");
*/	
	h_eta->Draw();
	C->Print(out_file_, "pdf");
/*	h0_eta->Draw();
	C->Print(out_file_,"pdf");
*/	ht_eta->Draw();
	C->Print(out_file_, "pdf");
/*	ht0_eta->Draw();
	C->Print(out_file_,"pdf");
*/	
	//plot same
	gStyle->SetLegendFont(62);
	Double_t x1= 0.7,y1= 0.75, x2 = 0.9, y2 = 0.9, y11 = 0.1, y22 = 0.33, x11=0.25, x22 = 0.85;
	C->SetLogx();
	h_pt->Draw();
	ht_pt->Draw("same");
//	TLegend *leg1=new TLegend(x11,y11,x22,y22,"Efficiency of TTT Tracks with denominator consisting:");
	TLegend *leg1=new TLegend(x11,y11,x22,y22,"");
	leg1->SetFillColor(kWhite);
	leg1->SetBorderSize(0);
//	leg1->SetNColumns(2);
	leg1->AddEntry((TObject*)0, "TTT Tracks #epsilon with denominator","");   
//	leg1->AddEntry((TObject*)0, "with denominator consisting:","");   
	leg1->AddEntry(h_pt,"all truth particles");
//	leg1->AddEntry((TObject*)0, "","");   
	leg1->AddEntry(ht_pt,"truth particles making a hit in the ");
	leg1->AddEntry((TObject*)0, "outermost layer of the triplet","");   
//	leg1->AddEntry((TObject*)0, "#splitline{truth particles making a}{hit in the outermost layer}","");   
	leg1->Draw();
	C->Print(out_file_,"pdf");
/*	h0_pt->Draw();
	ht0_pt->Draw("same");
	TLegend *leg2=new TLegend(x1,y1,x2,y2,"");
	leg2->SetFillColor(kWhite);
	leg2->SetBorderSize(0);
	leg2->AddEntry(h0_pt,"InDet tracks");
	leg2->AddEntry(ht0_pt,"TTT tracks");
	leg2->Draw();
	C->Print(out_file_,"pdf");
*/
	C->SetLogx(0);
	h_phi->Draw();
	ht_phi->Draw("same");
	/*TLegend *leg3=new TLegend(x1,y1,x2,y2,"");
	leg3->SetFillColor(kWhite);
	leg3->SetBorderSize(0);
        leg3->AddEntry(h_phi,"InDet tracks");
        leg3->AddEntry(ht_phi,"TTT tracks");
        leg3->Draw();*/
	leg1->Draw();
	C->Print(out_file_,"pdf");
/*	h0_phi->Draw();
	ht0_phi->Draw("same");
	TLegend *leg4=new TLegend(x1,y1,x2,y2,"");
	leg4->SetFillColor(kWhite);
	leg4->SetBorderSize(0);
        leg4->AddEntry(h0_phi,"InDet tracks");
        leg4->AddEntry(ht0_phi,"TTT tracks");
        leg4->Draw();
	C->Print(out_file_,"pdf");
*/
	h_eta->Draw();
	ht_eta->Draw("same");
	/*TLegend *leg5=new TLegend(x1,y1,x2,y2,"");
	leg5->SetFillColor(kWhite);
	leg5->SetBorderSize(0);
        leg5->AddEntry(h_eta,"InDet tracks");
        leg5->AddEntry(ht_eta,"TTT tracks");
        leg5->Draw();*/
	leg1->Draw();
//	C->Print(out_file_,"pdf");
/*	h0_eta->Draw();
	ht0_eta->Draw("same");
	TLegend *leg6=new TLegend(x1,y1,x2,y2,"");
	leg6->SetFillColor(kWhite);
	leg6->SetBorderSize(0);
        leg6->AddEntry(h0_eta,"InDet tracks");
        leg6->AddEntry(ht0_eta,"TTT tracks");
        leg6->Draw();
	C->Print(out_file_,"pdf");
*/	

/*	//two scales eta phi
	C->SetTicky(0);
	h_eta->GetYaxis()->SetAxisColor(kBlue);
	h_eta->GetYaxis()->SetTitleColor(kBlue);
	h_eta->GetYaxis()->SetTitleSize(0.05);
	h_eta->GetYaxis()->SetLabelColor(kBlue);
	h_eta->SetLineColor(kBlue);
	ht_eta->SetLineColor(kBlue);
	h_eta->SetMarkerColor(kBlue);
	ht_eta->SetMarkerColor(kBlue);	
	h_eta->Draw();
	ht_eta->Draw("same");
	C->Update();
	Float_t rightmax = 1*h0_eta->GetMaximum();
	Float_t scale = gPad->GetUymax()/rightmax;
	h0_eta->SetLineColor(kRed);
	ht0_eta->SetLineColor(kRed);
	h0_eta->SetMarkerColor(kRed);
	ht0_eta->SetMarkerColor(kRed);
	h0_eta->Scale(scale);
	h0_eta->Draw("same");
	ht0_eta->Draw("same");
	//draw an axis on the right side
	TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	gPad->GetUxmax(), gPad->GetUymax(),0.5,rightmax,510,"+L");
	axis->SetLineColor(kRed);
	axis->SetLabelColor(kRed);
//	axis->SetLabelSize(0.05);
	axis->SetTitle("purity");
	axis->SetTitleColor(kRed);
	axis->SetTitleSize(0.05);
	axis->SetTitleOffset(1.08);
	axis->SetMaxDigits(2);
	axis->CenterTitle();
	axis->Draw();
	
	C->Print(out_file_,"pdf");
	h_phi->GetYaxis()->SetAxisColor(kBlue);
	h_phi->GetYaxis()->SetTitleColor(kBlue);
	h_phi->GetYaxis()->SetTitleSize(0.05);
	h_phi->GetYaxis()->SetLabelColor(kBlue);
	h_phi->SetLineColor(kBlue);
	ht_phi->SetLineColor(kBlue);
	h_phi->SetMarkerColor(kBlue);
	ht_phi->SetMarkerColor(kBlue);	
	h_phi->Draw();
	ht_phi->Draw("same");
	C->Update();
	rightmax = 1*h0_phi->GetMaximum();
	scale = gPad->GetUymax()/rightmax;
	h0_phi->SetLineColor(kRed);
	ht0_phi->SetLineColor(kRed);
	h0_phi->SetMarkerColor(kRed);
	ht0_phi->SetMarkerColor(kRed);
	h0_phi->Scale(scale);
	h0_phi->Draw("same");
	ht0_phi->Draw("same");
	//draw an axis on the right side
	TGaxis *axis1 = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	gPad->GetUxmax(), gPad->GetUymax(),0.7,rightmax,510,"+L");
	axis1->SetLineColor(kRed);
	axis1->SetLabelColor(kRed);
//	axis->SetLabelSize(0.05);
	axis1->SetTitle("purity");
	axis1->SetTitleColor(kRed);
	axis1->SetTitleSize(0.05);
	axis1->SetTitleOffset(1.08);
	axis1->SetMaxDigits(2);
	axis1->CenterTitle();
	axis1->Draw();
	
	C->Print(out_file_,"pdf");
	h_pt->GetYaxis()->SetAxisColor(kBlue);
	h_pt->GetYaxis()->SetTitleColor(kBlue);
	h_pt->GetYaxis()->SetTitleSize(0.05);
	h_pt->GetYaxis()->SetLabelColor(kBlue);
	h_pt->SetLineColor(kBlue);
	ht_pt->SetLineColor(kBlue);
	h_pt->SetMarkerColor(kBlue);
	ht_pt->SetMarkerColor(kBlue);	
	h_pt->Draw();
	ht_pt->Draw("same");
	C->Update();
	rightmax = 1*h0_pt->GetMaximum();
	scale = gPad->GetUymax()/rightmax;
	h0_pt->SetLineColor(kRed);
	ht0_pt->SetLineColor(kRed);
	h0_pt->SetMarkerColor(kRed);
	ht0_pt->SetMarkerColor(kRed);
	h0_pt->Scale(scale);
	h0_pt->Draw("same");
	ht0_pt->Draw("same");
	//draw an axis on the right side
	TGaxis *axis2 = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	gPad->GetUxmax(), gPad->GetUymax(),0.7,rightmax,510,"+L");
	axis2->SetLineColor(kRed);
	axis2->SetLabelColor(kRed);
//	axis->SetLabelSize(0.05);
	axis2->SetTitle("purity");
	axis2->SetTitleColor(kRed);
	axis2->SetTitleSize(0.05);
	axis2->SetTitleOffset(1.08);
	axis2->SetMaxDigits(2);
	axis2->CenterTitle();
	axis2->Draw();
	C->SetLogx();
	
	C->Print(out_file_,"pdf");
	C->Clear();
	h_pt->SetMarkerColor(kBlack);
	ht_pt->SetMarkerColor(kBlack);
	h_pt->SetLineColor(kBlack);
	ht_pt->SetLineColor(kBlack);
	leg1->Draw();
	C->Print(out_file_,"pdf");
	C->Clear();
	h_pt->SetMarkerColor(kRed);
	ht_pt->SetMarkerColor(kRed);
	h_pt->SetLineColor(kRed);
	ht_pt->SetLineColor(kRed);
	leg1->Draw();

*/
	C->Print(out_file_close,"pdf");
return 0;
}

