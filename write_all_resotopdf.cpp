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
#include "TGaxis.h"
#include "TStyle.h"

#include <fstream>
#include <string>
#include <math.h>
//const char* out_path = "/eos/user/t/tkar/www/TTT/plots/resolution"; 
const char* out_path = "./plots/reso_plots";
int write_topdf(const char* output_file_name = "ResoVs_etaptphi_barcodeMatched")
{

        char out_file_open[1023];
        sprintf(out_file_open,"%s/%s.pdf(",out_path,output_file_name);
        char out_file_[1023];
        sprintf(out_file_,"%s/%s.pdf",out_path,output_file_name);
        char out_file_close[1023];
        sprintf(out_file_close,"%s/%s.pdf)",out_path,output_file_name);
	
	//!Reso vs eta
	TFile* f = TFile::Open("./plots/reso_plots/ResoVseta_barcodeMatched.root");
	TH1D* h_dp 	= (TH1D*)f->Get("h_sigmadp");
	TH1D* h_invpt 	= (TH1D*)f->Get("h_sigma_invPt");
	TH1D* h_phi	= (TH1D*)f->Get("h_sigma_phi");
	TH1D* h_theta	= (TH1D*)f->Get("h_sigma_theta");
	TH1D* h_eta	= (TH1D*)f->Get("h_sigma_eta");
	TH1D* h_z0	= (TH1D*)f->Get("h_sigma_z0");
//	TH1D* h_dca	= (TH1D*)f->Get("h_sigma_dca");

	//!Reso vs phi
	TFile* f0 = TFile::Open("./plots/reso_plots/ResoVsphi_barcodeMatched.root");
	TH1D* h0_dp 	= (TH1D*)f0->Get("h_sigmadp");
	TH1D* h0_invpt 	= (TH1D*)f0->Get("h_sigma_invPt");
	TH1D* h0_phi	= (TH1D*)f0->Get("h_sigma_phi");
	TH1D* h0_theta	= (TH1D*)f0->Get("h_sigma_theta");
	TH1D* h0_eta	= (TH1D*)f0->Get("h_sigma_eta");
	TH1D* h0_z0	= (TH1D*)f0->Get("h_sigma_z0");
//	TH1D* h0_dca	= (TH1D*)f0->Get("h_sigma_dca");

	//!Reso Vs pt
	TFile* f1 = TFile::Open("./plots/reso_plots/ResoVspt_barcodeMatched.root");
	TH1D* h1_dp 	= (TH1D*)f1->Get("h_sigmadp");
	TH1D* h1_invpt 	= (TH1D*)f1->Get("h_sigma_invPt");
	TH1D* h1_phi	= (TH1D*)f1->Get("h_sigma_phi");
	TH1D* h1_theta	= (TH1D*)f1->Get("h_sigma_theta");
	TH1D* h1_eta	= (TH1D*)f1->Get("h_sigma_eta");
	TH1D* h1_z0	= (TH1D*)f1->Get("h_sigma_z0");
//	TH1D* h1_dca	= (TH1D*)f1->Get("h_sigma_dca");

	h_dp->SetStats(0);
	h_invpt->SetStats(0);
       	h_phi->SetStats(0);
       	h_theta->SetStats(0);
       	h_eta->SetStats(0);
       	h_z0->SetStats(0);
//       	h_dca->SetStats(0);
       
	h0_dp->SetStats(0);
        h0_invpt->SetStats(0);
        h0_phi->SetStats(0);
        h0_theta->SetStats(0);
        h0_eta->SetStats(0);
        h0_z0->SetStats(0);
//        h0_dca->SetStats(0);
	h1_dp->SetStats(0);
        h1_invpt->SetStats(0);
        h1_phi->SetStats(0);
        h1_theta->SetStats(0);
        h1_eta->SetStats(0);
        h1_z0->SetStats(0);
//        h1_dca->SetStats(0);
 	
	// SET Markercolour
	h_dp->SetMarkerColor(kBlack);
	h_invpt->SetMarkerColor(kBlack);
	h_phi->SetMarkerColor(kBlack);
	h_theta->SetMarkerColor(kBlack);
	h_eta->SetMarkerColor(kBlack);
	h_z0->SetMarkerColor(kBlack);
//	h_dca->SetMarkerColor(kBlack);

	h0_dp->SetMarkerColor(kBlack);
        h0_invpt->SetMarkerColor(kBlack);
        h0_phi->SetMarkerColor(kBlack);
        h0_theta->SetMarkerColor(kBlack);
        h0_eta->SetMarkerColor(kBlack);
        h0_z0->SetMarkerColor(kBlack);
//        h0_dca->SetMarkerColor(kBlack);
	
	h1_dp->SetMarkerColor(kBlack);
        h1_invpt->SetMarkerColor(kBlack);
        h1_phi->SetMarkerColor(kBlack);
        h1_theta->SetMarkerColor(kBlack);
        h1_eta->SetMarkerColor(kBlack);
        h1_z0->SetMarkerColor(kBlack);
//        h1_dca->SetMarkerColor(kBlack);
	
	//Marker Size	
	h_dp->SetMarkerSize(1.8);
	h_invpt->SetMarkerSize(1.8);
	h_phi->SetMarkerSize(1.8);
	h_theta->SetMarkerSize(1.8);
	h_eta->SetMarkerSize(1.8);
	h_z0->SetMarkerSize(1.8);
//	h_dca->SetMarkerSize(1.8);
	
	h0_dp->SetMarkerSize(1.8);
        h0_invpt->SetMarkerSize(1.8);
        h0_phi->SetMarkerSize(1.8);
        h0_theta->SetMarkerSize(1.8);
        h0_eta->SetMarkerSize(1.8);
        h0_z0->SetMarkerSize(1.8);
//        h0_dca->SetMarkerSize(1.8);

	h1_dp->SetMarkerSize(1.8);
        h1_invpt->SetMarkerSize(1.8);
        h1_phi->SetMarkerSize(1.8);
        h1_theta->SetMarkerSize(1.8);
        h1_eta->SetMarkerSize(1.8);
        h1_z0->SetMarkerSize(1.8);
//        h1_dca->SetMarkerSize(1.8);

//Marker Style	
	h_dp->SetMarkerStyle(kFullTriangleDown);
	h_invpt->SetMarkerStyle(kFullTriangleDown);
	h_phi->SetMarkerStyle(kFullTriangleDown);
	h_theta->SetMarkerStyle(kFullTriangleDown);
	h_eta->SetMarkerStyle(kFullTriangleDown);
	h_z0->SetMarkerStyle(kFullTriangleDown);
//	h_dca->SetMarkerStyle(kFullTriangleDown);

	h0_dp->SetMarkerStyle(kFullTriangleDown);
        h0_invpt->SetMarkerStyle(kFullTriangleDown);
        h0_phi->SetMarkerStyle(kFullTriangleDown);
        h0_theta->SetMarkerStyle(kFullTriangleDown);
        h0_eta->SetMarkerStyle(kFullTriangleDown);
        h0_z0->SetMarkerStyle(kFullTriangleDown);
//        h0_dca->SetMarkerStyle(kFullTriangleDown);
	
	h1_dp->SetMarkerStyle(kFullTriangleDown);
        h1_invpt->SetMarkerStyle(kFullTriangleDown);
        h1_phi->SetMarkerStyle(kFullTriangleDown);
        h1_theta->SetMarkerStyle(kFullTriangleDown);
        h1_eta->SetMarkerStyle(kFullTriangleDown);
        h1_z0->SetMarkerStyle(kFullTriangleDown);
//        h1_dca->SetMarkerStyle(kFullTriangleDown);
	
	h_dp->GetYaxis()->SetTitleOffset(.85);
	h_invpt->GetYaxis()->SetTitleOffset(.85);
	h_phi->GetYaxis()->SetTitleOffset(.85);
	h_theta->GetYaxis()->SetTitleOffset(.85);
	h_eta->GetYaxis()->SetTitleOffset(.85);
	h_z0->GetYaxis()->SetTitleOffset(.85);
//	h_dca->GetYaxis()->SetTitleOffset(.85);

	h0_dp->GetYaxis()->SetTitleOffset(.85);
        h0_invpt->GetYaxis()->SetTitleOffset(.85);
        h0_phi->GetYaxis()->SetTitleOffset(.85);
        h0_theta->GetYaxis()->SetTitleOffset(.85);
        h0_eta->GetYaxis()->SetTitleOffset(.85);
        h0_z0->GetYaxis()->SetTitleOffset(.85);
//        h0_dca->GetYaxis()->SetTitleOffset(.85);
	
	h1_dp->GetYaxis()->SetTitleOffset(.85);
        h1_invpt->GetYaxis()->SetTitleOffset(.85);
        h1_phi->GetYaxis()->SetTitleOffset(.85);
        h1_theta->GetYaxis()->SetTitleOffset(.85);
        h1_eta->GetYaxis()->SetTitleOffset(.85);
        h1_z0->GetYaxis()->SetTitleOffset(.85);
//        h1_dca->GetYaxis()->SetTitleOffset(.85);
	
	h_dp->GetYaxis()->SetTitleSize(.05);
	h_invpt->GetYaxis()->SetTitleSize(.05);
	h_phi->GetYaxis()->SetTitleSize(.05);
	h_theta->GetYaxis()->SetTitleSize(.05);
	h_eta->GetYaxis()->SetTitleSize(.05);
	h_z0->GetYaxis()->SetTitleSize(.05);
//	h_dca->GetYaxis()->SetTitleSize(.05);
	
	h0_dp->GetYaxis()->SetTitleSize(.05);
        h0_invpt->GetYaxis()->SetTitleSize(.05);
        h0_phi->GetYaxis()->SetTitleSize(.05);
        h0_theta->GetYaxis()->SetTitleSize(.05);
        h0_eta->GetYaxis()->SetTitleSize(.05);
        h0_z0->GetYaxis()->SetTitleSize(.05);
//        h0_dca->GetYaxis()->SetTitleSize(.05);


	h1_dp->GetYaxis()->SetTitleSize(.05);
        h1_invpt->GetYaxis()->SetTitleSize(.05);
        h1_phi->GetYaxis()->SetTitleSize(.05);
        h1_theta->GetYaxis()->SetTitleSize(.05);
        h1_eta->GetYaxis()->SetTitleSize(.05);
        h1_z0->GetYaxis()->SetTitleSize(.05);
//        h1_dca->GetYaxis()->SetTitleSize(.05);

	h_dp->GetXaxis()->SetTitleOffset(.85);
	h_invpt->GetXaxis()->SetTitleOffset(.85);
	h_phi->GetXaxis()->SetTitleOffset(.85);
	h_theta->GetXaxis()->SetTitleOffset(.85);
	h_eta->GetXaxis()->SetTitleOffset(.85);
	h_z0->GetXaxis()->SetTitleOffset(.85);
//	h_dca->GetXaxis()->SetTitleOffset(.85);

	h0_dp->GetXaxis()->SetTitleOffset(.85);
        h0_invpt->GetXaxis()->SetTitleOffset(.85);
        h0_phi->GetXaxis()->SetTitleOffset(.85);
        h0_theta->GetXaxis()->SetTitleOffset(.85);
        h0_eta->GetXaxis()->SetTitleOffset(.85);
        h0_z0->GetXaxis()->SetTitleOffset(.85);
//        h0_dca->GetXaxis()->SetTitleOffset(.85);
	
	h1_dp->GetXaxis()->SetTitleOffset(.85);
        h1_invpt->GetXaxis()->SetTitleOffset(.85);
        h1_phi->GetXaxis()->SetTitleOffset(.85);
        h1_theta->GetXaxis()->SetTitleOffset(.85);
        h1_eta->GetXaxis()->SetTitleOffset(.85);
        h1_z0->GetXaxis()->SetTitleOffset(.85);
//        h1_dca->GetXaxis()->SetTitleOffset(.85);
	

	h_dp->GetXaxis()->SetTitleSize(.05);
	h_invpt->GetXaxis()->SetTitleSize(.05);
	h_phi->GetXaxis()->SetTitleSize(.05);
	h_theta->GetXaxis()->SetTitleSize(.05);
	h_eta->GetXaxis()->SetTitleSize(.05);
	h_z0->GetXaxis()->SetTitleSize(.05);
//	h_dca->GetXaxis()->SetTitleSize(.05);

	h0_dp->GetXaxis()->SetTitleSize(.05);
        h0_invpt->GetXaxis()->SetTitleSize(.05);
        h0_phi->GetXaxis()->SetTitleSize(.05);
        h0_theta->GetXaxis()->SetTitleSize(.05);
        h0_eta->GetXaxis()->SetTitleSize(.05);
        h0_z0->GetXaxis()->SetTitleSize(.05);
//        h0_dca->GetXaxis()->SetTitleSize(.05);
	
	h1_dp->GetXaxis()->SetTitleSize(.05);
        h1_invpt->GetXaxis()->SetTitleSize(.05);
        h1_phi->GetXaxis()->SetTitleSize(.05);
        h1_theta->GetXaxis()->SetTitleSize(.05);
        h1_eta->GetXaxis()->SetTitleSize(.05);
        h1_z0->GetXaxis()->SetTitleSize(.05);
//        h1_dca->GetXaxis()->SetTitleSize(.05);
	
	h_dp->GetXaxis()->SetTitle("#eta_{gen}");
	h_invpt->GetXaxis()->SetTitle("#eta_{gen}");
	h_phi->GetXaxis()->SetTitle("#eta_{gen}");
	h_theta->GetXaxis()->SetTitle("#eta_{gen}");
	h_eta->GetXaxis()->SetTitle("#eta_{gen}");
	h_z0->GetXaxis()->SetTitle("#eta_{gen}");
//	h_dca->GetXaxis()->SetTitle("#eta_{gen}");

	h0_dp->GetXaxis()->SetTitle("#phi_{gen} [rad]");
        h0_invpt->GetXaxis()->SetTitle("#phi_{gen} [rad]");
        h0_phi->GetXaxis()->SetTitle("#phi_{gen} [rad]");
        h0_theta->GetXaxis()->SetTitle("#phi_{gen} [rad]");
        h0_eta->GetXaxis()->SetTitle("#phi_{gen} [rad]");
        h0_z0->GetXaxis()->SetTitle("#phi_{gen} [rad]");
//        h0_dca->GetXaxis()->SetTitle("#phi_{gen} [rad]");
	
	h1_dp->GetXaxis()->SetTitle("pt_{gen}  [MeV/c]");
        h1_invpt->GetXaxis()->SetTitle("pt_{gen}  [MeV/c]");
        h1_phi->GetXaxis()->SetTitle("pt_{gen}  [MeV/c]");
        h1_theta->GetXaxis()->SetTitle("pt_{gen}  [MeV/c]");
        h1_eta->GetXaxis()->SetTitle("pt_{gen}  [MeV/c]");
        h1_z0->GetXaxis()->SetTitle("pt_{gen}  [MeV/c]");
//        h1_dca->GetXaxis()->SetTitle("pt_{gen}  [MeV/c]");
	
	Float_t rightmax=0,leftmin=0,scale=0;	
	TCanvas * C = new TCanvas("C","",650,400);
	gStyle->SetOptStat(0);

	C->SetGridx();
	C->SetGridy();
	C->SetTickx();
	C->SetTicky();
	h_dp->Draw();
	//C->SetLogx();
	C->Print(out_file_open, "pdf");
	h0_dp->Draw();
	C->Print(out_file_,"pdf");
	h1_dp->Draw();
	C->Print(out_file_,"pdf");

	h_invpt->Draw();
	C->Print(out_file_, "pdf");
	h0_invpt->Draw();
	C->Print(out_file_,"pdf");
	h1_invpt->Draw();
	C->Print(out_file_,"pdf");
	
	h_phi->Draw();
	C->Print(out_file_, "pdf");
	h0_phi->Draw();
	C->Print(out_file_,"pdf");
	h1_phi->Draw();
	C->Print(out_file_,"pdf");

	h_theta->Draw();
	C->Print(out_file_, "pdf");
	h0_theta->Draw();
	C->Print(out_file_,"pdf");
	h1_theta->Draw();
	C->Print(out_file_,"pdf");
	
	h_eta->Draw();
	C->Print(out_file_, "pdf");
	h0_eta->Draw();
	C->Print(out_file_,"pdf");
	h1_eta->Draw();
	C->Print(out_file_,"pdf");
	
	h_z0->Draw();
	C->Print(out_file_, "pdf");
	h0_z0->Draw();
	C->Print(out_file_,"pdf");
	h1_z0->Draw();
	C->Print(out_file_,"pdf");
	//two scales
	C->SetTicky(0);
	h_invpt->Draw();
	C->Update();
	rightmax = 1.1*h_dp->GetMaximum();
	leftmin = 1*h_dp->GetMinimum();
	scale = gPad->GetUymax()/rightmax;
	h_dp->SetLineColor(kRed);
	h_dp->SetMarkerColor(kRed);
	h_dp->Scale(scale);
	h_dp->Draw("same");
	//draw an axis on the right side
	TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
	axis->SetLineColor(kRed);
	axis->SetLabelColor(kRed);
//	axis->SetLabelSize(0.05);
	axis->SetTitle("#sigma_{#Delta(p_{t})/gen_p_{t}}");
	axis->SetTitleColor(kRed);
	axis->SetTitleSize(0.05);
	axis->SetTitleOffset(1.04);
	axis->Draw();
	
	C->Print(out_file_,"pdf");
	
	C->Clear();
	h0_invpt->Draw();
	C->Update();
	rightmax = 1.1*h0_dp->GetMaximum();
	leftmin = 1*h0_dp->GetMinimum();
	scale = gPad->GetUymax()/rightmax;
	h0_dp->SetLineColor(kRed);
	h0_dp->SetMarkerColor(kRed);
	h0_dp->Scale(scale);
	h0_dp->Draw("same");
	C->Update();
	//draw an axis1 on the right side
	TGaxis *axis1 = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
	axis1->SetLineColor(kRed);
	axis1->SetLabelColor(kRed);
//	axis1->SetLabelSize(0.05);
	axis1->SetTitle("#sigma_{#Delta(p_{t})/gen_p_{t}}");
	axis1->SetTitleColor(kRed);
	axis1->SetTitleSize(0.05);
	axis1->SetTitleOffset(1.04);
 	axis1->Draw();

	C->Print(out_file_,"pdf");
	h1_invpt->Draw();
	C->Update();
	rightmax = 1.1*h1_dp->GetMaximum();
	leftmin = 1*h1_dp->GetMinimum();
	scale = gPad->GetUymax()/rightmax;
	h1_dp->SetLineColor(kRed);
	h1_dp->SetMarkerColor(kRed);
	h1_dp->Scale(scale);
	h1_dp->Draw("same");
	C->Update();
	//draw an axis2 on the right side
	TGaxis *axis2 = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
	axis2->SetLineColor(kRed);
	axis2->SetLabelColor(kRed);
//	axis2->SetLabelSize(0.05);
	axis2->SetTitle("#sigma_{#Delta(p_{t})/gen_p_{t}}");
	axis2->SetTitleColor(kRed);
	axis2->SetTitleSize(0.05);
	axis2->SetTitleOffset(1.04);
	axis2->Draw();
	C->Print(out_file_,"pdf");

	//two scales eta phi
	h_phi->Draw();
	C->Update();
	rightmax = 1.1*h_eta->GetMaximum();
	leftmin = 1*h_eta->GetMinimum();
	scale = gPad->GetUymax()/rightmax;
	h_eta->SetLineColor(kRed);
	h_eta->SetMarkerColor(kRed);
	h_eta->Scale(scale);
	h_eta->Draw("same");
	//draw an axis on the right side
	TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
	axis->SetLineColor(kRed);
	axis->SetLabelColor(kRed);
//	axis->SetLabelSize(0.05);
	axis->SetTitle("#sigma_{#Delta(#eta)}");
	axis->SetTitleColor(kRed);
	axis->SetTitleSize(0.05);
	axis->SetTitleOffset(1.04);
	axis->Draw();
	
	C->Print(out_file_,"pdf");
	
	C->Clear();
	h0_phi->Draw();
	C->Update();
	rightmax = 1.1*h0_eta->GetMaximum();
	leftmin = 1*h0_eta->GetMinimum();
	scale = gPad->GetUymax()/rightmax;
	h0_eta->SetLineColor(kRed);
	h0_eta->SetMarkerColor(kRed);
	h0_eta->Scale(scale);
	h0_eta->Draw("same");
	C->Update();
	//draw an axis1 on the right side
	TGaxis *axis1 = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
	axis1->SetLineColor(kRed);
	axis1->SetLabelColor(kRed);
//	axis1->SetLabelSize(0.05);
	axis1->SetTitle("#sigma_{#Delta(#eta)}");
	axis1->SetTitleColor(kRed);
	axis1->SetTitleSize(0.05);
	axis1->SetTitleOffset(1.04);
 	axis1->Draw();

	C->Print(out_file_,"pdf");
	h1_phi->Draw();
	C->Update();
	rightmax = 1.1*h1_eta->GetMaximum();
	leftmin = 1*h1_eta->GetMinimum();
	scale = gPad->GetUymax()/rightmax;
	h1_eta->SetLineColor(kRed);
	h1_eta->SetMarkerColor(kRed);
	h1_eta->Scale(scale);
	h1_eta->Draw("same");
	C->Update();
	//draw an axis2 on the right side
	TGaxis *axis2 = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
	axis2->SetLineColor(kRed);
	axis2->SetLabelColor(kRed);
//	axis2->SetLabelSize(0.05);
	axis2->SetTitle("#sigma_{#Delta(#eta)}");
	axis2->SetTitleColor(kRed);
	axis2->SetTitleSize(0.05);
	axis2->SetTitleOffset(1.04);
	axis2->Draw();

	C->Print(out_file_close,"pdf");

return 0;
}
