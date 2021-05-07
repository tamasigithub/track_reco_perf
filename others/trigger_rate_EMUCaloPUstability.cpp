#include <iostream>
#include <fstream>
#include <string>
#include<math.h>

#include "TROOT.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TPostScript.h"

#include "TAxis.h"
#include "TGaxis.h"
#include "TF1.h"

double X_MIN = 0.5e3, X_MAX = 0.9e3;
double Y_MIN = 0.7e-1, Y_MAX = 60;

TFile *f1 = nullptr;
TFile *f2 = nullptr;
TFile *f3 = nullptr;//f3 not used in this macro

TH1D *h2_1 = nullptr;
TH1D *h3_1 = nullptr;
TH1D *h4_1 = nullptr;
TH1D *h5_1 = nullptr;

TH1D *h2_2 = nullptr;
TH1D *h3_2 = nullptr;
TH1D *h4_2 = nullptr;
TH1D *h5_2 = nullptr;

TH1D *h2_3 = nullptr;
TH1D *h3_3 = nullptr;
TH1D *h4_3 = nullptr;
TH1D *h5_3 = nullptr;

void plot_rate()
{
	f1 = new TFile("/media/tamasi/Z/PhD/FCC/Castellated/TriggerStudies/CELL1_a50c3_ALL_PU1kMB_ETA2.5_30mm_R0.4_2.root");
	f2 = new TFile("/media/tamasi/Z/PhD/FCC/Castellated/TriggerStudies/CELL1_a50c3_ALL_PU1kMB_ETA2.5_30mm_R0.4SPU_2.root");
	f3 = new TFile("/media/tamasi/Z/PhD/FCC/Castellated/TriggerStudies/CELL1_a50c3_ALL_PU1kMB_ETA2.5_30mm_R0.2_2.root");

	
	h2_1 = (TH1D*)f1->Get("hb_PUNLpt");
	h3_1 = (TH1D*)f1->Get("hb_PUNNLpt");
	h4_1 = (TH1D*)f1->Get("hb_PUNNNLpt");
	h5_1 = (TH1D*)f1->Get("hb_PUNNNNLpt");
	
	h2_2 = (TH1D*)f2->Get("hb_PUNLpt");
	h3_2 = (TH1D*)f2->Get("hb_PUNNLpt");
	h4_2 = (TH1D*)f2->Get("hb_PUNNNLpt");
	h5_2 = (TH1D*)f2->Get("hb_PUNNNNLpt");
	
	h2_3 = (TH1D*)f3->Get("hb_PUNLpt");
	h3_3 = (TH1D*)f3->Get("hb_PUNNLpt");
	h4_3 = (TH1D*)f3->Get("hb_PUNNNLpt");
	h5_3 = (TH1D*)f3->Get("hb_PUNNNNLpt");

	h2_2->SetLineStyle(7);
	h3_2->SetLineStyle(7);
	h4_2->SetLineStyle(7);
	h5_2->SetLineStyle(7);

	h2_3->SetLineStyle(2);
	h3_3->SetLineStyle(2);
	h4_3->SetLineStyle(2);
	h5_3->SetLineStyle(2);


	TCanvas *c = new TCanvas("c","c", 800, 800);
	c->SetGridx();
	c->SetGridy();
	//c->SetTickx();
	c->SetTicky();
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);

	h2_1->GetXaxis()->SetRangeUser(X_MIN, X_MAX);
	h2_1->GetYaxis()->SetRangeUser(Y_MIN, Y_MAX);
	h2_1->GetXaxis()->SetTitle("p_{T} thresh. [GeV/c]");
	h2_1->GetYaxis()->SetTitle("trigger rate [MHz]");
	h2_1->GetXaxis()->CenterTitle();
	h2_1->GetYaxis()->CenterTitle();
	h2_1->Draw("hist ");
	h3_1->Draw("hist same");
	h4_1->Draw("hist same");
	h5_1->Draw("hist same");

	h2_2->Draw("hist same");
	h3_2->Draw("hist same");
	h4_2->Draw("hist same");
	h5_2->Draw("hist same");

	//h2_3->Draw("hist same");
	//h3_3->Draw("hist same");
	//h4_3->Draw("hist same");
	//h5_3->Draw("hist same");

	TLegend *leg = new TLegend(0.1,0.45,0.3,0.56);
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->AddEntry(h2_1,"<#mu> = 1k","l");
	leg->AddEntry(h2_2,"|#mu| < 965","l");
	//leg->AddEntry(h2_3,"#Delta R = 0.2","l");
        leg->SetTextSize(0.04);
	leg->Draw();
	TLegend *leg1 = new TLegend(0.1,0.2,0.30,0.4);
	leg1->SetFillStyle(0);
	leg1->SetBorderSize(0);
	leg1->AddEntry(h2_1,"2^{nd} leading","l");
	leg1->AddEntry(h3_1,"3^{rd} leading","l");
	leg1->AddEntry(h4_1,"4^{th} leading","l");
	leg1->AddEntry(h5_1,"5^{th} leading","l");
        leg1->SetTextSize(0.04);
	leg1->Draw();
	TLegend *cms_E = new TLegend(0.2,0.85,0.89,0.97);
        cms_E->SetFillStyle(0);
        cms_E->SetBorderSize(0);
        cms_E->AddEntry((TObject*)0, "#sqrt{s} = 100 TeV, B=4T, |#eta| < 2.5", "");
        cms_E->AddEntry((TObject*)0, "MB only <#mu> = 1k, Emul. calo-jet", "");
        cms_E->SetTextSize(0.04);
	cms_E->Draw();

	c->SetLogy();
	c->SaveAs("/media/tamasi/Z/PhD/FCC/Castellated/TriggerStudies/CELL1_calo_trigRateSPU_2.tex");

	//c->SetLogy(0);
	//TH2D *h2d_ = (TH2D*)f1->Get("h2d");
	//h2d_->SetMaximum(200);
   	//Double_t zcontours[5] = {0, 20, 40, 80, 120};
   	//h2d_->SetContour(5, zcontours);
   	//h2d_->GetZaxis()->SetTickSize(0.01);
   	//h2d_->GetZaxis()->SetLabelOffset(0.01);
   	//gPad->SetRightMargin(0.13);
   	////h2d_->SetTitle("User contours, CJUST");
   	//h2d_->SetMarkerStyle(3);
	////h2d_->Draw("COL2 Z CJUST");
	//h2d_->Draw("BOX");
	return;
}
