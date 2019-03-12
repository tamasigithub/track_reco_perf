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
int write_topdf(const char* output_file_name = "PurVsEtaPtPhi_cutCompBmatched")
{

	char out_file_open[1023];
        sprintf(out_file_open,"%s/%s.pdf(",out_path,output_file_name);
        char out_file_[1023];
        sprintf(out_file_,"%s/%s.pdf",out_path,output_file_name);
        char out_file_close[1023];
        sprintf(out_file_close,"%s/%s.pdf)",out_path,output_file_name);

	//! purity wide cuts
	TFile* f0 = TFile::Open("./plots/purity/prev_purwide_TTTBMatched_eta1.4final.root");
	TH1D* h0_pt 	= (TH1D*)f0->Get("h_pur_vs_ptPU");
	TH1D* h0_phi	= (TH1D*)f0->Get("h_pur_vs_phiPU");
	TH1D* h0_eta	= (TH1D*)f0->Get("h_pur_vs_etaPU");
	//! purity TTT barcode matched tracks no kappa cut
	TFile* f1 = TFile::Open("./plots/purity/prev_purnokap_TTTBMatched_eta1.4final.root");
	TH1D* h1_pt = (TH1D*)f1->Get("h_pur_vs_ptPU");
	TH1D* h1_phi	= (TH1D*)f1->Get("h_pur_vs_phiPU");
	TH1D* h1_eta	= (TH1D*)f1->Get("h_pur_vs_etaPU");
	//! purity TTT barcode matched tracks #sigma 5
	TFile* f2 = TFile::Open("./plots/purity/prev_pursig5_TTTBMatched_eta1.4final.root");
	TH1D* h2_pt = (TH1D*)f2->Get("h_pur_vs_ptPU");
	TH1D* h2_phi	= (TH1D*)f2->Get("h_pur_vs_phiPU");
	TH1D* h2_eta	= (TH1D*)f2->Get("h_pur_vs_etaPU");
	//! purity TTT barcode matched tracks #sigma 3
	TFile* f3 = TFile::Open("./plots/purity/prev_pursig3_TTTBMatched_eta1.4final.root");
	TH1D* h3_pt = (TH1D*)f3->Get("h_pur_vs_ptPU");
	TH1D* h3_phi	= (TH1D*)f3->Get("h_pur_vs_phiPU");
	TH1D* h3_eta	= (TH1D*)f3->Get("h_pur_vs_etaPU");


	h2_pt->SetStats(0);
       	h2_phi->SetStats(0);
       	h2_eta->SetStats(0);
        h0_pt->SetStats(0);
        h0_phi->SetStats(0);
        h0_eta->SetStats(0);
	h3_pt->SetStats(0);
       	h3_phi->SetStats(0);
       	h3_eta->SetStats(0);
        h1_pt->SetStats(0);
        h1_phi->SetStats(0);
        h1_eta->SetStats(0);
 	
	// SET Markercolour
	//! efficiency in blue
	//! purity in red
	h2_pt->SetMarkerColor(kRed);
	h2_phi->SetMarkerColor(kRed);
	h2_eta->SetMarkerColor(kRed);
        h0_pt->SetMarkerColor(kBlack);
        h0_phi->SetMarkerColor(kBlack);
        h0_eta->SetMarkerColor(kBlack);
	h3_pt->SetMarkerColor(kRed+2);
	h3_phi->SetMarkerColor(kRed+2);
	h3_eta->SetMarkerColor(kRed+2);
        h1_pt->SetMarkerColor(kRed-9);
        h1_phi->SetMarkerColor(kRed-9);
        h1_eta->SetMarkerColor(kRed-9);
	
	//Marker Size	
	h2_pt->SetMarkerSize(1.8);
	h2_phi->SetMarkerSize(1.8);
	h2_eta->SetMarkerSize(1.8);
        h0_pt->SetMarkerSize(1.8);
        h0_phi->SetMarkerSize(1.8);
        h0_eta->SetMarkerSize(1.8);
	h3_pt->SetMarkerSize(1.8);
	h3_phi->SetMarkerSize(1.8);
	h3_eta->SetMarkerSize(1.8);
        h1_pt->SetMarkerSize(1.8);
        h1_phi->SetMarkerSize(1.8);
        h1_eta->SetMarkerSize(1.8);

	//Marker Style	
	h2_pt->SetMarkerStyle(kFullDiamond);
	h2_phi->SetMarkerStyle(kFullDiamond);
	h2_eta->SetMarkerStyle(kFullDiamond);
        h0_pt->SetMarkerStyle(kFullDiamond);
        h0_phi->SetMarkerStyle(kFullDiamond);
        h0_eta->SetMarkerStyle(kFullDiamond);
	h3_pt->SetMarkerStyle(kFullDiamond);
	h3_phi->SetMarkerStyle(kFullDiamond);
	h3_eta->SetMarkerStyle(kFullDiamond);
        h1_pt->SetMarkerStyle(kFullDiamond);
        h1_phi->SetMarkerStyle(kFullDiamond);
        h1_eta->SetMarkerStyle(kFullDiamond);

	h2_pt->GetXaxis()->SetLabelFont(62);
	h2_phi->GetXaxis()->SetLabelFont(62);
	h2_eta->GetXaxis()->SetLabelFont(62);
        h0_pt->GetXaxis()->SetLabelFont(62);
        h0_phi->GetXaxis()->SetLabelFont(62);
        h0_eta->GetXaxis()->SetLabelFont(62);
	h3_pt->GetXaxis()->SetLabelFont(62);
	h3_phi->GetXaxis()->SetLabelFont(62);
	h3_eta->GetXaxis()->SetLabelFont(62);
        h1_pt->GetXaxis()->SetLabelFont(62);
        h1_phi->GetXaxis()->SetLabelFont(62);
        h1_eta->GetXaxis()->SetLabelFont(62);
        
	h2_pt->GetYaxis()->SetLabelFont(62);
	h2_phi->GetYaxis()->SetLabelFont(62);
	h2_eta->GetYaxis()->SetLabelFont(62);
        h0_pt->GetYaxis()->SetLabelFont(62);
        h0_phi->GetYaxis()->SetLabelFont(62);
        h0_eta->GetYaxis()->SetLabelFont(62);
	h3_pt->GetYaxis()->SetLabelFont(62);
	h3_phi->GetYaxis()->SetLabelFont(62);
	h3_eta->GetYaxis()->SetLabelFont(62);
        h1_pt->GetYaxis()->SetLabelFont(62);
        h1_phi->GetYaxis()->SetLabelFont(62);
        h1_eta->GetYaxis()->SetLabelFont(62);
	
	h2_pt->GetYaxis()->SetTitleOffset(.85);
	h2_phi->GetYaxis()->SetTitleOffset(.85);
	h2_eta->GetYaxis()->SetTitleOffset(.85);
        h0_pt->GetYaxis()->SetTitleOffset(.85);
        h0_phi->GetYaxis()->SetTitleOffset(.85);
        h0_eta->GetYaxis()->SetTitleOffset(.85);
	h3_pt->GetYaxis()->SetTitleOffset(.85);
	h3_phi->GetYaxis()->SetTitleOffset(.85);
	h3_eta->GetYaxis()->SetTitleOffset(.85);
        h1_pt->GetYaxis()->SetTitleOffset(.85);
        h1_phi->GetYaxis()->SetTitleOffset(.85);
        h1_eta->GetYaxis()->SetTitleOffset(.85);
	
	h2_pt->GetYaxis()->CenterTitle();
	h2_phi->GetYaxis()->CenterTitle();
	h2_eta->GetYaxis()->CenterTitle();
        h0_pt->GetYaxis()->CenterTitle();
        h0_phi->GetYaxis()->CenterTitle();
        h0_eta->GetYaxis()->CenterTitle();
	h3_pt->GetYaxis()->CenterTitle();
	h3_phi->GetYaxis()->CenterTitle();
	h3_eta->GetYaxis()->CenterTitle();
        h1_pt->GetYaxis()->CenterTitle();
        h1_phi->GetYaxis()->CenterTitle();
        h1_eta->GetYaxis()->CenterTitle();
	h2_pt->GetXaxis()->CenterTitle();
	h2_phi->GetXaxis()->CenterTitle();
	h2_eta->GetXaxis()->CenterTitle();
        h0_pt->GetXaxis()->CenterTitle();
        h0_phi->GetXaxis()->CenterTitle();
        h0_eta->GetXaxis()->CenterTitle();
	h3_pt->GetXaxis()->CenterTitle();
	h3_phi->GetXaxis()->CenterTitle();
	h3_eta->GetXaxis()->CenterTitle();
        h1_pt->GetXaxis()->CenterTitle();
        h1_phi->GetXaxis()->CenterTitle();
        h1_eta->GetXaxis()->CenterTitle();
	
	h2_pt->GetYaxis()->SetTitleSize(.05);
	h2_phi->GetYaxis()->SetTitleSize(.05);
	h2_eta->GetYaxis()->SetTitleSize(.05);
        h0_pt->GetYaxis()->SetTitleSize(.05);
        h0_phi->GetYaxis()->SetTitleSize(.05);
        h0_eta->GetYaxis()->SetTitleSize(.05);
	h3_pt->GetYaxis()->SetTitleSize(.05);
	h3_phi->GetYaxis()->SetTitleSize(.05);
	h3_eta->GetYaxis()->SetTitleSize(.05);
        h1_pt->GetYaxis()->SetTitleSize(.05);
        h1_phi->GetYaxis()->SetTitleSize(.05);
        h1_eta->GetYaxis()->SetTitleSize(.05);

	h2_pt->GetYaxis()->SetRangeUser(0.9,1.04);
	h2_phi->GetYaxis()->SetRangeUser(0.95,1.04);
	h2_eta->GetYaxis()->SetRangeUser(0.95,1.04);
        h0_pt->GetYaxis()->SetRangeUser(0.1,1.04);
        h0_phi->GetYaxis()->SetRangeUser(0.1,1.04);
        h0_eta->GetYaxis()->SetRangeUser(0.1,1.04);
	h3_pt->GetYaxis()->SetRangeUser(0.9,1.04);
	h3_phi->GetYaxis()->SetRangeUser(0.95,1.04);
	h3_eta->GetYaxis()->SetRangeUser(0.95,1.04);
        h1_pt->GetYaxis()->SetRangeUser(0.9,1.04);
        h1_phi->GetYaxis()->SetRangeUser(0.95,1.04);
        h1_eta->GetYaxis()->SetRangeUser(0.95,1.04);

	h2_pt->GetXaxis()->SetTitleOffset(.85);
	h2_phi->GetXaxis()->SetTitleOffset(.85);
	h2_eta->GetXaxis()->SetTitleOffset(.85);
        h0_pt->GetXaxis()->SetTitleOffset(.85);
        h0_phi->GetXaxis()->SetTitleOffset(.85);
        h0_eta->GetXaxis()->SetTitleOffset(.85);
	
	h3_pt->GetXaxis()->SetTitleOffset(.85);
	h3_phi->GetXaxis()->SetTitleOffset(.85);
	h3_eta->GetXaxis()->SetTitleOffset(.85);
        h1_pt->GetXaxis()->SetTitleOffset(.85);
        h1_phi->GetXaxis()->SetTitleOffset(.85);
        h1_eta->GetXaxis()->SetTitleOffset(.85);
	

	h2_pt->GetXaxis()->SetTitleSize(.05);
	h2_phi->GetXaxis()->SetTitleSize(.05);
	h2_eta->GetXaxis()->SetTitleSize(.05);
        h0_pt->GetXaxis()->SetTitleSize(.05);
        h0_phi->GetXaxis()->SetTitleSize(.05);
        h0_eta->GetXaxis()->SetTitleSize(.05);
	
	h3_pt->GetXaxis()->SetTitleSize(.05);
	h3_phi->GetXaxis()->SetTitleSize(.05);
	h3_eta->GetXaxis()->SetTitleSize(.05);
        h1_pt->GetXaxis()->SetTitleSize(.05);
        h1_phi->GetXaxis()->SetTitleSize(.05);
        h1_eta->GetXaxis()->SetTitleSize(.05);
	
	h2_pt->GetXaxis()->SetTitle("p_{t} [MeV/c]");
	h2_phi->GetXaxis()->SetTitle("#phi [rad]");
	h2_eta->GetXaxis()->SetTitle("#eta");
        h0_pt->GetXaxis()->SetTitle("p_{t} [MeV/c]");
        h0_phi->GetXaxis()->SetTitle("#phi [rad]");
        h0_eta->GetXaxis()->SetTitle("#eta");
	
	h3_pt->GetXaxis()->SetTitle("p_{t} [MeV/c]");
	h3_phi->GetXaxis()->SetTitle("#phi [rad]");
	h3_eta->GetXaxis()->SetTitle("#eta");
        h1_pt->GetXaxis()->SetTitle("p_{t} [MeV/c]");
        h1_phi->GetXaxis()->SetTitle("#phi [rad]");
        h1_eta->GetXaxis()->SetTitle("#eta");
	
	
	TCanvas * C = new TCanvas();
	gStyle->SetOptStat(0);
	TGaxis::SetMaxDigits(2);
	C->SetGridx();
	C->SetGridy();
	C->SetTickx();
	C->SetTicky();
	
	C->SetLogx();
	h2_pt->Draw();
	C->Print(out_file_open, "pdf");
	h0_pt->Draw();
	C->Print(out_file_,"pdf");
	h3_pt->Draw();
	C->Print(out_file_, "pdf");
	h1_pt->Draw();
	C->Print(out_file_,"pdf");

	C->SetLogx(0);
	h2_phi->Draw();
	C->Print(out_file_, "pdf");
	h0_phi->Draw();
	C->Print(out_file_,"pdf");
	h3_phi->Draw();
	C->Print(out_file_, "pdf");
	h1_phi->Draw();
	C->Print(out_file_,"pdf");
	
	h2_eta->Draw();
	C->Print(out_file_, "pdf");
	h0_eta->Draw();
	C->Print(out_file_,"pdf");
	h3_eta->Draw();
	C->Print(out_file_, "pdf");
	h1_eta->Draw();
	C->Print(out_file_,"pdf");
	
	//plot same
	
	Double_t x1= 0.5,y1= 0.7, x2 = 0.85, y2 = 0.85, y11 = 0.55, y22 = 0.75;
	C->SetLogx();
	h0_pt->Draw();
	h1_pt->Draw("same");
	h2_pt->Draw("same");
	h3_pt->Draw("same");
	TLegend *leg1=new TLegend(x1,y11,x2,y22,"");
	leg1->SetFillColor(kWhite);
	leg1->SetBorderSize(0);
	leg1->SetNColumns(2);
	leg1->AddEntry(h0_pt,"wide");
	leg1->AddEntry((TObject*)0, "(w/o d#phi_{2}, dz_{2}, #kappa_{cut})","");
	leg1->AddEntry(h1_pt,"loose");
	leg1->AddEntry((TObject*)0,"(w/o #kappa_{cut})","");                 
	leg1->AddEntry(h2_pt,"medium");
	leg1->AddEntry((TObject*)0,"(#sigma_{#kappa} = 5)","");              
	leg1->AddEntry(h3_pt,"tight");
	leg1->AddEntry((TObject*)0,"(#sigma_{#kappa} = 3)","");
	leg1->Draw();
	C->Print(out_file_,"pdf");
	h1_pt->Draw();
	h2_pt->Draw("same");
	h3_pt->Draw("same");
	TLegend *leg1a=new TLegend(x1,y1,x2,y2,"");
	leg1a->SetFillColor(kWhite);
	leg1a->SetBorderSize(0);
	leg1a->SetNColumns(2);
	leg1a->AddEntry(h1_pt,"loose");
	leg1a->AddEntry((TObject*)0, "(w/o #kappa_{cut})","");   
	leg1a->AddEntry(h2_pt,"medium");
	leg1a->AddEntry((TObject*)0,"(#sigma_{#kappa} = 5)","");
	leg1a->AddEntry(h3_pt,"tight");
	leg1a->AddEntry((TObject*)0,"(#sigma_{#kappa} = 3)","");
	leg1a->Draw();
	C->Print(out_file_,"pdf");
	h0_pt->Draw();
	h1_pt->Draw("same");
	TLegend *leg1b=new TLegend(x1,y11,x2,y22,"");
	leg1b->SetFillColor(kWhite);
	leg1b->SetBorderSize(0);
	leg1b->AddEntry(h0_pt,"wide   (w/o d#phi_{2}, dz_{2}, #kappa_{cut})");
	leg1b->AddEntry(h1_pt,"loose  (w/o #kappa_{cut})");                 
	leg1b->Draw();
	C->Print(out_file_,"pdf");

	C->SetLogx(0);
	h0_phi->Draw();
	h1_phi->Draw("same");
	h2_phi->Draw("same");
	h3_phi->Draw("same");
	TLegend *leg2=new TLegend(x1,y11,x2,y22,"");
	leg2->SetFillColor(kWhite);
	leg2->SetBorderSize(0);
	leg2->SetNColumns(2);
	leg2->AddEntry(h0_phi,"wide");
	leg2->AddEntry((TObject*)0, "(w/o d#phi_{2}, dz_{2}, #kappa_{cut})","");
	leg2->AddEntry(h1_phi,"loose");
	leg2->AddEntry((TObject*)0,"(w/o #kappa_{cut})","");                 
	leg2->AddEntry(h2_phi,"medium");
	leg2->AddEntry((TObject*)0,"(#sigma_{#kappa} = 5)","");              
	leg2->AddEntry(h3_phi,"tight");
	leg2->AddEntry((TObject*)0,"(#sigma_{#kappa} = 3)","");
	leg2->Draw();
	C->Print(out_file_,"pdf");
	h1_phi->Draw();
	h2_phi->Draw("same");
	h3_phi->Draw("same");
	TLegend *leg2a=new TLegend(x1,y1,x2,y2,"");
	leg2a->SetFillColor(kWhite);
	leg2a->SetBorderSize(0);
	leg2a->SetNColumns(2);
	leg2a->AddEntry(h1_phi,"loose");
	leg2a->AddEntry((TObject*)0, "(w/o #kappa_{cut})","");   
	leg2a->AddEntry(h2_phi,"medium");
	leg2a->AddEntry((TObject*)0,"(#sigma_{#kappa} = 5)","");
	leg2a->AddEntry(h3_phi,"tight");
	leg2a->AddEntry((TObject*)0,"(#sigma_{#kappa} = 3)","");
	leg2a->Draw();
	C->Print(out_file_,"pdf");
	h0_phi->Draw();
	h1_phi->Draw("same");
	TLegend *leg2b=new TLegend(x1,y11,x2,y22,"");
	leg2b->SetFillColor(kWhite);
	leg2b->SetBorderSize(0);
	leg2b->AddEntry(h0_phi,"wide   (w/o d #phi_{2}, dz_{2}, #kappa_{cut})");
	leg2b->AddEntry(h1_phi,"loose  (w/o #kappa_{cut})");                 
	leg2b->Draw();
	C->Print(out_file_,"pdf");


	h0_eta->Draw();
	h1_eta->Draw("same");
	h2_eta->Draw("same");
	h3_eta->Draw("same");
	TLegend *leg3=new TLegend(x1,y11,x2,y22,"");
	leg3->SetFillColor(kWhite);
	leg3->SetBorderSize(0); 
	leg3->SetNColumns(2);
	leg3->AddEntry(h0_eta,"wide");
	leg3->AddEntry((TObject*)0, "(w/o d#phi_{2}, dz_{2}, #kappa_{cut})","");
	leg3->AddEntry(h1_eta,"loose");
	leg3->AddEntry((TObject*)0,"(w/o #kappa_{cut})","");                 
	leg3->AddEntry(h2_eta,"medium");
	leg3->AddEntry((TObject*)0,"(#sigma_{#kappa} = 5)","");              
	leg3->AddEntry(h3_eta,"tight");
	leg3->AddEntry((TObject*)0,"(#sigma_{#kappa} = 3)","");             
	leg3->Draw();
	C->Print(out_file_,"pdf");
	h1_eta->Draw();
	h2_eta->Draw("same");
	h3_eta->Draw("same");
	TLegend *leg3a=new TLegend(x1,y1,x2,y2,"");
	leg3a->SetFillColor(kWhite);
	leg3a->SetBorderSize(0);
	leg3a->SetNColumns(2);
	leg3a->AddEntry(h1_eta,"loose");
	leg3a->AddEntry((TObject*)0, "(w/o #kappa_{cut})","");   
	leg3a->AddEntry(h2_eta,"medium");
	leg3a->AddEntry((TObject*)0,"(#sigma_{#kappa} = 5)","");
	leg3a->AddEntry(h3_eta,"tight");
	leg3a->AddEntry((TObject*)0,"(#sigma_{#kappa} = 3)","");
	leg3a->Draw();
	C->Print(out_file_,"pdf");
	h0_eta->Draw();
	h1_eta->Draw("same");
	TLegend *leg3b=new TLegend(x1,y11,x2,y22,"");
	leg3b->SetFillColor(kWhite);
	leg3b->SetBorderSize(0);
	leg3b->AddEntry(h0_eta,"wide   (w/o d #phi_{2}, dz_{2}, #kappa_{cut})");
	leg3b->AddEntry(h1_eta,"loose  (w/o #kappa_{cut})");                 
	leg3b->Draw();
	

/*	C->Print(out_file_,"pdf");
	C->Clear();
	leg1->Draw();
*/

	C->Print(out_file_close,"pdf");
return 0;
}

