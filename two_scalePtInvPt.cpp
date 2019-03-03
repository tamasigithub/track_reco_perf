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
#include <vector>
int two_scales(const char* output_file_name = "ptInvpt_barcodeMatched")
{
	
	//! TTT tracks
	//TFile* f0 = TFile::Open("./plots/purity/TTTpurity_1.root");
	TFile* f0 = TFile::Open("./plots/reso_plots/ResoVspt_barcodeMatched.root");
        TH1D* h0_dp     = (TH1D*)f0->Get("h_sigmadp");
        TH1D* h0_invpt  = (TH1D*)f0->Get("h_sigma_invPt");
        TH1D* h0_phi    = (TH1D*)f0->Get("h_sigma_phi");
        TH1D* h0_theta  = (TH1D*)f0->Get("h_sigma_theta");
        TH1D* h0_eta    = (TH1D*)f0->Get("h_sigma_eta");
        TH1D* h0_z0     = (TH1D*)f0->Get("h_sigma_z0");

/*	//TFile* f1 = TFile::Open("./plots/efficiency/TTTeff_1.root");
	TFile* f1 = TFile::Open("./plots/efficiency/newefficiency_InDetTTTdR0.01B.root");
	TH1D* he_eta 	= (TH1D*)f1->Get("h_eff_vs_etaPU");
	TH1D* he_pt 	= (TH1D*)f1->Get("h_eff_vs_ptPU");
	TH1D* he_phi	= (TH1D*)f1->Get("h_eff_vs_phiPU");


*/	

	h0_dp->SetMarkerStyle(kFullCircle);
	h0_invpt->SetMarkerStyle(kFullCircle);
	
	h0_dp->SetMarkerColor(kBlack);
	h0_invpt->SetMarkerColor(kRed);
	
	h0_dp->SetMarkerSize(2.0);
	h0_invpt->SetMarkerSize(2.0);
	
	h0_dp->GetYaxis()->SetTitleSize(.05);
	h0_invpt->GetYaxis()->SetTitleSize(.05);
	
	h0_dp->GetXaxis()->SetTitleSize(.05);
	h0_dp->GetXaxis()->SetLabelSize(.05);
	h0_dp->GetYaxis()->SetLabelSize(.05);
	
	h0_dp->GetYaxis()->SetTitleOffset(.85);
	h0_invpt->GetYaxis()->SetTitleOffset(.85);

	TCanvas *c1 = new TCanvas("c1","roc curve",650,400);
	gStyle->SetOptStat(0);
	h0_dp->Draw();
	c1->Update();

	Float_t rightmax = 1.1*h0_invpt->GetMaximum();
	Float_t scale = gPad->GetUymax()/rightmax;
	h0_invpt->SetLineColor(kRed);
	h0_invpt->Scale(scale);
	h0_invpt->Draw("same");

	//draw an axis on the right side
	TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
	axis->SetLineColor(kRed);
	axis->SetLabelColor(kRed);
	axis->SetLabelSize(0.05);
	axis->SetTitle("#sigma_{1/p_t} [MeV/c]^{-1}");
	axis->SetTitleColor(kRed);
	axis->Draw();
return 0;
}
