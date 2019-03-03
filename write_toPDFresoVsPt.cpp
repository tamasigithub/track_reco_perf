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
const char* out_path = "./plots/reso_plots"; 
int write_topdf(const char* output_file_name = "ResoVsPt_InDetTTTBMatched")
{

	char out_file_open[1023];
        sprintf(out_file_open,"%s/%s.pdf(",out_path,output_file_name);
        char out_file_[1023];
        sprintf(out_file_,"%s/%s.pdf",out_path,output_file_name);
        char out_file_close[1023];
        sprintf(out_file_close,"%s/%s.pdf)",out_path,output_file_name);
	//!InDet tracks
	TFile* f = TFile::Open("./plots/reso_plots/ResoVsptInDet_dR0.01Matched.root");
	TH1D* h_dp 	= (TH1D*)f->Get("h_sigmadp");
	TH1D* h_invpt 	= (TH1D*)f->Get("h_sigma_invPt");
	TH1D* h_phi	= (TH1D*)f->Get("h_sigma_phi");
	TH1D* h_theta	= (TH1D*)f->Get("h_sigma_theta");
	TH1D* h_eta	= (TH1D*)f->Get("h_sigma_eta");
	TH1D* h_z0	= (TH1D*)f->Get("h_sigma_z0");
//	TH1D* h_dca	= (TH1D*)f->Get("h_sigma_dca");

	//! TTT tracks/ TTT barcode matched
	TFile* f0 = TFile::Open("./plots/reso_plots/ResoVspt_barcodeMatched.root");
	TH1D* h0_dp 	= (TH1D*)f0->Get("h_sigmadp");
	TH1D* h0_invpt 	= (TH1D*)f0->Get("h_sigma_invPt");
	TH1D* h0_phi	= (TH1D*)f0->Get("h_sigma_phi");
	TH1D* h0_theta	= (TH1D*)f0->Get("h_sigma_theta");
	TH1D* h0_eta	= (TH1D*)f0->Get("h_sigma_eta");
	TH1D* h0_z0	= (TH1D*)f0->Get("h_sigma_z0");
//	TH1D* h0_dca	= (TH1D*)f0->Get("h_sigma_dca");


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
 	
	// SET Markercolour
	h_dp->SetMarkerColor(kRed);
	h_invpt->SetMarkerColor(kRed);
	h_phi->SetMarkerColor(kRed);
	h_theta->SetMarkerColor(kRed);
	h_eta->SetMarkerColor(kRed);
	h_z0->SetMarkerColor(kRed);
//	h_dca->SetMarkerColor(kRed);

	h0_dp->SetMarkerColor(kRed);
        h0_invpt->SetMarkerColor(kRed);
        h0_phi->SetMarkerColor(kRed);
        h0_theta->SetMarkerColor(kRed);
        h0_eta->SetMarkerColor(kRed);
        h0_z0->SetMarkerColor(kRed);
//        h0_dca->SetMarkerColor(kRed);
	
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

	//Marker Style	
	h_dp->SetMarkerStyle(kFullTriangleDown);
	h_invpt->SetMarkerStyle(kFullTriangleDown);
	h_phi->SetMarkerStyle(kFullTriangleDown);
	h_theta->SetMarkerStyle(kFullTriangleDown);
	h_eta->SetMarkerStyle(kFullTriangleDown);
	h_z0->SetMarkerStyle(kFullTriangleDown);
//	h_dca->SetMarkerStyle(kFullTriangleDown);

	h0_dp->SetMarkerStyle(kFullCircle);
        h0_invpt->SetMarkerStyle(kFullCircle);
        h0_phi->SetMarkerStyle(kFullCircle);
        h0_theta->SetMarkerStyle(kFullCircle);
        h0_eta->SetMarkerStyle(kFullCircle);
        h0_z0->SetMarkerStyle(kFullCircle);
//        h0_dca->SetMarkerStyle(kFullCircle);
	h_dp->GetXaxis()->SetLabelFont(62);
	h_invpt->GetXaxis()->SetLabelFont(62);
	h_phi->GetXaxis()->SetLabelFont(62);
	h_theta->GetXaxis()->SetLabelFont(62);
	h_eta->GetXaxis()->SetLabelFont(62);
	h_z0->GetXaxis()->SetLabelFont(62);
//	h_dca->GetXaxis()->SetLabelFont(62);

	h0_dp->GetXaxis()->SetLabelFont(62);
        h0_invpt->GetXaxis()->SetLabelFont(62);
        h0_phi->GetXaxis()->SetLabelFont(62);
        h0_theta->GetXaxis()->SetLabelFont(62);
        h0_eta->GetXaxis()->SetLabelFont(62);
        h0_z0->GetXaxis()->SetLabelFont(62);
//       
	h_dp->GetYaxis()->SetLabelFont(62);
	h_invpt->GetYaxis()->SetLabelFont(62);
	h_phi->GetYaxis()->SetLabelFont(62);
	h_theta->GetYaxis()->SetLabelFont(62);
	h_eta->GetYaxis()->SetLabelFont(62);
	h_z0->GetYaxis()->SetLabelFont(62);
//	h_dca->GetYaxis()->SetLabelFont(62);

	h0_dp->GetYaxis()->SetLabelFont(62);
        h0_invpt->GetYaxis()->SetLabelFont(62);
        h0_phi->GetYaxis()->SetLabelFont(62);
        h0_theta->GetYaxis()->SetLabelFont(62);
        h0_eta->GetYaxis()->SetLabelFont(62);
        h0_z0->GetYaxis()->SetLabelFont(62);
//       h0_dca->GetYaxis()->SetLabelFont(62);
	
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
	h_dp->GetYaxis()->CenterTitle();
	h_invpt->GetYaxis()->CenterTitle();
	h_phi->GetYaxis()->CenterTitle();
	h_theta->GetYaxis()->CenterTitle();
	h_eta->GetYaxis()->CenterTitle();
	h_z0->GetYaxis()->CenterTitle();
//	h_dca->GetYaxis()->CenterTitle();

	h0_dp->GetYaxis()->CenterTitle();
        h0_invpt->GetYaxis()->CenterTitle();
        h0_phi->GetYaxis()->CenterTitle();
        h0_theta->GetYaxis()->CenterTitle();
        h0_eta->GetYaxis()->CenterTitle();
        h0_z0->GetYaxis()->CenterTitle();
//        h0_dca->GetYaxis()->CenterTitle();
	
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
	h_invpt->GetYaxis()->SetTitle("#sigma_{#Delta(1/p_{t})} [MeV/c]^{-1}");
        h0_invpt->GetYaxis()->SetTitle("#sigma_{#Delta(1/p_{t})} [MeV/c]^{-1}");
	
	h_dp->GetXaxis()->SetTitle("p_{t_gen} [MeV/c]");
	h_invpt->GetXaxis()->SetTitle("p_{t_gen} [MeV/c]");
	h_phi->GetXaxis()->SetTitle("p_{t_gen} [MeV/c]");
	h_theta->GetXaxis()->SetTitle("p_{t_gen} [MeV/c]");
	h_eta->GetXaxis()->SetTitle("p_{t_gen} [MeV/c]");
	h_z0->GetXaxis()->SetTitle("p_{t_gen} [MeV/c]");
//	h_dca->GetXaxis()->SetTitle("P_{t_gen} [MeV/c]");

	h0_dp->GetXaxis()->SetTitle("p_{t_gen} [MeV/c]");
        h0_invpt->GetXaxis()->SetTitle("p_{t_gen} [MeV/c]");
        h0_phi->GetXaxis()->SetTitle("p_{t_gen} [MeV/c]");
        h0_theta->GetXaxis()->SetTitle("p_{t_gen} [MeV/c]");
        h0_eta->GetXaxis()->SetTitle("p_{t_gen} [MeV/c]");
        h0_z0->GetXaxis()->SetTitle("p_{t_gen} [MeV/c]");
//        h0_dca->GetXaxis()->SetTitle("P_{t_gen} [MeV/c]");
	
	
	TCanvas * C = new TCanvas();
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

	h_invpt->Draw();
	C->Print(out_file_, "pdf");
	h0_invpt->Draw();
	C->Print(out_file_,"pdf");
	
	h_phi->Draw();
	C->Print(out_file_, "pdf");
	h0_phi->Draw();
	C->Print(out_file_,"pdf");

	h_theta->Draw();
	C->Print(out_file_, "pdf");
	h0_theta->Draw();
	C->Print(out_file_,"pdf");
	
	h_eta->Draw();
	C->Print(out_file_, "pdf");
	h0_eta->Draw();
	C->Print(out_file_,"pdf");
	
	h_z0->Draw();
	C->Print(out_file_, "pdf");
	h0_z0->Draw();
	C->Print(out_file_,"pdf");
	
	/*h_dca->Draw();
	C->Print(out_file_, "pdf");
	h0_dca->Draw();
	C->Print(out_file_,"pdf");
	*/

	//plot same
	
	Double_t x1= 0.7,y1= 0.75, x2 = 0.9, y2 = 0.9;
	h_dp->GetYaxis()->SetRangeUser(0,0.35);
	h_dp->Draw();
	h0_dp->Draw("same");
	TLegend *leg1=new TLegend(x1,y1,x2,y2,"");
	leg1->SetFillColor(kWhite);
	leg1->SetBorderSize(0);
        leg1->AddEntry(h_dp,"InDet tracks");
        leg1->AddEntry(h0_dp,"TTT tracks");
        leg1->Draw();
	C->Print(out_file_,"pdf");
	h_invpt->GetYaxis()->SetRangeUser(0,8e-6);
	h_invpt->Draw();
	h0_invpt->Draw("same");
	TLegend *leg2=new TLegend(x1,y1,x2,y2,"");
	leg2->SetFillColor(kWhite);
	leg2->SetBorderSize(0);
	leg2->AddEntry(h_invpt,"InDet tracks");
	leg2->AddEntry(h0_invpt,"TTT tracks");
	leg2->Draw();
	C->Print(out_file_,"pdf");

	h_phi->GetYaxis()->SetRangeUser(0,0.0025);
	h_phi->Draw();
	h0_phi->Draw("same");
	TLegend *leg3=new TLegend(x1,y1,x2,y2,"");
	leg3->SetFillColor(kWhite);
	leg3->SetBorderSize(0);
        leg3->AddEntry(h_phi,"InDet tracks");
        leg3->AddEntry(h0_phi,"TTT tracks");
        leg3->Draw();
	C->Print(out_file_,"pdf");
	
	h_theta->GetYaxis()->SetRangeUser(0,0.0025);
	h_theta->Draw();
	h0_theta->Draw("same");
	TLegend *leg4=new TLegend(x1,y1,x2,y2,"");
	leg4->SetFillColor(kWhite);
	leg4->SetBorderSize(0);
        leg4->AddEntry(h_theta,"InDet tracks");
        leg4->AddEntry(h0_theta,"TTT tracks");
        leg4->Draw();
	C->Print(out_file_,"pdf");
	
	h_eta->GetYaxis()->SetRangeUser(0,0.0025);
	h_eta->Draw();
	h0_eta->Draw("same");
	TLegend *leg5=new TLegend(x1,y1,x2,y2,"");
	leg5->SetFillColor(kWhite);
	leg5->SetBorderSize(0);
        leg5->AddEntry(h_eta,"InDet tracks");
        leg5->AddEntry(h0_eta,"TTT tracks");
        leg5->Draw();
	C->Print(out_file_,"pdf");
	
	h_z0->GetYaxis()->SetRangeUser(0.0,1.5);
	h_z0->Draw();
	h0_z0->Draw("same");
	TLegend *leg6=new TLegend(x1,y1,x2,y2,"");
	leg6->SetFillColor(kWhite);
	leg6->SetBorderSize(0);
        leg6->AddEntry(h_z0,"InDet tracks");
        leg6->AddEntry(h0_z0,"TTT tracks");
        leg6->Draw();
	C->Print(out_file_,"pdf");
	
	/*h_dca->GetYaxis()->SetRangeUser(10,40);
	h_dca->Draw();
	h0_dca->Draw("same");
	TLegend *leg7=new TLegend(x1,y1,x2,y2,"");
        leg7->AddEntry(h_dca,"InDet tracks");
        leg7->AddEntry(h0_dca,"TTT tracks");
        leg7->Draw();*/

	
	//two scales eta phi
	C->SetTicky(0);
	h_phi->SetLineColor(kBlack);
	h0_phi->SetLineColor(kBlack);
	h_phi->SetMarkerColor(kBlack);
	h0_phi->SetMarkerColor(kBlack);	
	h_phi->Draw();
	h0_phi->Draw("same");
	C->Update();
	Float_t rightmax = 1*h_eta->GetMaximum();
	Float_t scale = gPad->GetUymax()/rightmax;
	h_eta->SetLineColor(kBlue);
	h0_eta->SetLineColor(kBlack);
	h_eta->SetMarkerColor(kBlue);
	h0_eta->SetMarkerColor(kBlue);
	h_eta->Scale(scale);
	h_eta->Draw("same");
	h0_eta->Draw("same");
	//draw an axis on the right side
	TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
	axis->SetLineColor(kBlue);
	axis->SetLabelColor(kBlue);
//	axis->SetLabelSize(0.05);
	axis->SetTitle("#sigma_{#Delta(#eta)}");
	axis->SetTitleColor(kBlue);
	axis->SetTitleSize(0.05);
	axis->SetTitleOffset(1.04);
	axis->CenterTitle();
	axis->Draw();
	
	C->Print(out_file_,"pdf");
	C->Clear();
	leg1->Draw();

	C->Print(out_file_close,"pdf");
return 0;
}

