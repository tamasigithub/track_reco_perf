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
int two_scales(const char* output_file_name = "roc_curveTTTB")
{
	
	//! TTT tracks
	//TFile* f0 = TFile::Open("./plots/purity/TTTpurity_1.root");
	TFile* f0 = TFile::Open("./plots/purity/newpurityTTT_barcode.root");
	TH1D* hp_eta 	= (TH1D*)f0->Get("h_pur_vs_etaPU");
	TH1D* hp_pt 	= (TH1D*)f0->Get("h_pur_vs_ptPU");
	TH1D* hp_phi	= (TH1D*)f0->Get("h_pur_vs_phiPU");
	//TFile* f1 = TFile::Open("./plots/efficiency/TTTeff_1.root");
	TFile* f1 = TFile::Open("./plots/efficiency/newefficiency_InDetTTTdR0.01B.root");
	TH1D* he_eta 	= (TH1D*)f1->Get("h_eff_vs_etaPU");
	TH1D* he_pt 	= (TH1D*)f1->Get("h_eff_vs_ptPU");
	TH1D* he_phi	= (TH1D*)f1->Get("h_eff_vs_phiPU");
	
	TCanvas *c1 = new TCanvas("c1","roc curve",600,400);
	gStyle->SetOptStat(0);
	he_eta->Draw();
	c1->Update();

	Float_t rightmax = 1.1*hp_eta->GetMaximum();
	Float_t scale = gPad->GetUymax()/rightmax;
	hp_eta->SetLineColor(kRed);
	hp_eta->Scale(scale);
	hp_eta->Draw("same");

	//draw an axis on the right side
	TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
	axis->SetLineColor(kRed);
	axis->SetLabelColor(kRed);
	axis->Draw();
return 0;
}

int roc_curve()
{
	 //! TTT tracks
        //TFile* f0 = TFile::Open("./plots/purity/TTTpurity_1.root");
        TFile* f0 = TFile::Open("./plots/purity/newpurityTTT_barcode.root");
        TH1D* hp_eta    = (TH1D*)f0->Get("h_pur_vs_etaPU");
        TH1D* hp_pt     = (TH1D*)f0->Get("h_pur_vs_ptPU");
        TH1D* hp_phi    = (TH1D*)f0->Get("h_pur_vs_phiPU");
        //TFile* f1 = TFile::Open("./plots/efficiency/TTTeff_1.root");
        TFile* f1 = TFile::Open("./plots/efficiency/newefficiency_InDetTTTdR0.01B.root");
        TH1D* he_eta    = (TH1D*)f1->Get("h_eff_vs_etaPU");
        TH1D* he_pt     = (TH1D*)f1->Get("h_eff_vs_ptPU");
        TH1D* he_phi    = (TH1D*)f1->Get("h_eff_vs_phiPU");

	// if he_phi is a TH1F* and hp_phi is a TH1F* (with the same number of bins!)

int nbins = he_phi->GetNbinsX();
	TH2F *h_roc = new TH2F("h_roc","roc curve;efficiency;pruity;",10,0.7,1.1,10,0.7,1.1);
	Float_t x , y;
	for(int i = 0; i<40; ++i)
	{
		x = hp_pt->GetBinContent(i);
		y = he_pt->GetBinContent(i);
		std::cout<<"x,y: "<<x <<", " << y <<std::endl;
		h_roc->Fill(y,x);

	}
	TCanvas *c1 = new TCanvas();
	h_roc->SetMarkerStyle(kFullTriangleDown);
	h_roc->SetMarkerSize(1.8);
	h_roc->Draw("c");
	c1->Update();

return 0;
}
