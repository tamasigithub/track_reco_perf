////////////////////Effeciency and purity as a function of pt, eta, phi////////////////////
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
#include "TAxis.h"
#include "TH1.h"
#include "TArrayD.h"
void ScaleAxis(TAxis *a, Double_t Scale)
{
  if (!a) return; // just a precaution
  if (a->GetXbins()->GetSize())
    {
      // an axis with variable bins
      // note: bins must remain in increasing order, hence the "Scale"
      // function must be strictly (monotonically) increasing
      TArrayD X(*(a->GetXbins()));
      for(Int_t i = 0; i < X.GetSize(); i++) X[i] = X[i]*Scale;
      a->Set((X.GetSize() - 1), X.GetArray()); // new Xbins
    }
  else
    {
      // an axis with fix bins
      // note: we modify Xmin and Xmax only, hence the "Scale" function
      // must be linear (and Xmax must remain greater than Xmin)
      a->Set( a->GetNbins(),
              a->GetXmin()*Scale, // new Xmin
              a->GetXmax()*Scale ); // new Xmax
    }
  return;
}

void ScaleXaxis(TH1 *h, Double_t Scale)
{
  if (!h) return; // just a precaution
  ScaleAxis(h->GetXaxis(), Scale);
  return;
}

//const char* out_path = "/eos/user/t/tkar/www/TTT/plots/resolution"; 
//const char* out_path = "./plots/purity"; 
const char* out_path = "./plots"; 
//const char* out_path = "/media/tamasi/DriveT1/tamasi/Desktop/PHD/talks_preps/ctd2k19/plots/efficiency/hh4b"; 
//int write_topdf(const char* output_file_name = "EffPurVsEtaPtPhi_PU1000MB_30mm_samelad")
int write_topdf(const char* output_file_name = "EffPurVsEtaPtPhi_PU1000hh4b_m26030mm_samelad_1")
{

	Double_t pt_min = 4.9e3, pt_max = 110e3;
	char out_file_open[1023];
        sprintf(out_file_open,"%s/%s.pdf(",out_path,output_file_name);
        char out_file_[1023];
        sprintf(out_file_,"%s/%s.pdf",out_path,output_file_name);
        char out_file_close[1023];
        sprintf(out_file_close,"%s/%s.pdf)",out_path,output_file_name);
	//!efficiency Indet and TTT tracks barcode matched
	//TFile* f_ = TFile::Open("./plots/PU1000MB-eff_30mm_samelad_opt5GeV.root");
	TFile* f_ = TFile::Open("./plots/PU1000hh4b-eff_30mm_samelad_opt5GeVp.root");
	/*TH1D* h__pt 	= (TH1D*)f_->Get("h_eff_vs_ptInDet");
	TH1D* h__phi	= (TH1D*)f_->Get("h_eff_vs_phiInDet");
	TH1D* h__eta	= (TH1D*)f_->Get("h_eff_vs_etaInDet");
	TH1D* h_tdR_pt 	= (TH1D*)f_->Get("h_eff_vs_ptTTT");
	TH1D* h_tdR_phi	= (TH1D*)f_->Get("h_eff_vs_phiTTT");
	TH1D* h_tdR_eta	= (TH1D*)f_->Get("h_eff_vs_etaTTT");*/
	TH1D* h_t_pt 	= (TH1D*)f_->Get("h_eff_vs_ptPU");
	TH1D* h_t_phi	= (TH1D*)f_->Get("h_eff_vs_phiPU");
	TH1D* h_t_eta	= (TH1D*)f_->Get("h_eff_vs_etaPU");
	/*TFile* f_3 = TFile::Open("./plots/efficiency/preveffsig5L6BTTT_barcodeEta1.2_final.root.root");
	TH1D* h_3t_pt 	= (TH1D*)f_3->Get("h_eff_vs_ptPU");
	TH1D* h_3t_phi	= (TH1D*)f_3->Get("h_eff_vs_phiPU");
	TH1D* h_3t_eta	= (TH1D*)f_3->Get("h_eff_vs_etaPU");*/

	//! purity Indet tracks
	/*TFile* f0 = TFile::Open("./plots/pur_InDetdR0.01_eta1.2.root");
	TH1D* h0_pt 	= (TH1D*)f0->Get("h_pur_vs_ptPU");
	TH1D* h0_phi	= (TH1D*)f0->Get("h_pur_vs_phiPU");
	TH1D* h0_eta	= (TH1D*)f0->Get("h_pur_vs_etaPU");*/
	//! purity TTT barcode matched tracks
	//TFile* f0t = TFile::Open("../optimisation/plots/pur_PU1000MB_30mm_samelad_opt5GeV.root");
	TFile* f0t = TFile::Open("../optimisation/plots/pur_PU1000hh4b_m260_30mm_samelad_opt5GeV.root");
	TH1D* ht0_pt    = (TH1D*)f0t->Get("h_pur_vs_ptPU");
	TH1D* ht0_phi	= (TH1D*)f0t->Get("h_pur_vs_phiPU");
	TH1D* ht0_eta	= (TH1D*)f0t->Get("h_pur_vs_etaPU");


	/*h__pt->SetStats(0);
       	h__phi->SetStats(0);
       	h__eta->SetStats(0);
	h_tdR_pt->SetStats(0);
       	h_tdR_phi->SetStats(0);
       	h_tdR_eta->SetStats(0);*/
	h_t_pt->SetStats(0);
       	h_t_phi->SetStats(0);
       	h_t_eta->SetStats(0);
	/*h_3t_pt->SetStats(0);
       	h_3t_phi->SetStats(0);
       	h_3t_eta->SetStats(0);*/
        
	/*h0_pt->SetStats(0);
        h0_phi->SetStats(0);
        h0_eta->SetStats(0);*//*
        ht0dR_pt->SetStats(0);
        ht0dR_phi->SetStats(0);
        ht0dR_eta->SetStats(0);*/
        ht0_pt->SetStats(0);
        ht0_phi->SetStats(0);
        ht0_eta->SetStats(0);
 	
	// SET Markercolour
	//! efficiency in blue
	//! purity in red
	/*h__pt->SetMarkerColor(kBlue);
	h__phi->SetMarkerColor(kBlue);
	h__eta->SetMarkerColor(kBlue);
	h_tdR_pt->SetMarkerColor(kBlue);
	h_tdR_phi->SetMarkerColor(kBlue);
	h_tdR_eta->SetMarkerColor(kBlue);*/
	h_t_pt->SetMarkerColor(kBlue);
	h_t_phi->SetMarkerColor(kBlue);
	h_t_eta->SetMarkerColor(kBlue);

	/*h_3t_pt->SetMarkerColor(kBlue);
	h_3t_phi->SetMarkerColor(kBlue);
	h_3t_eta->SetMarkerColor(kBlue);*/
        
	/*h0_pt->SetMarkerColor(kRed);
        h0_phi->SetMarkerColor(kRed);
        h0_eta->SetMarkerColor(kRed);*//*
        ht0dR_pt->SetMarkerColor(kRed);
        ht0dR_phi->SetMarkerColor(kRed);
        ht0dR_eta->SetMarkerColor(kRed);*/
        ht0_pt->SetMarkerColor(kRed);
        ht0_phi->SetMarkerColor(kRed);
        ht0_eta->SetMarkerColor(kRed);
	
	//Marker Size	
	/*h__pt->SetMarkerSize(1.8);
	h__phi->SetMarkerSize(1.8);
	h__eta->SetMarkerSize(1.8);
	h_tdR_pt->SetMarkerSize(1.8);
	h_tdR_phi->SetMarkerSize(1.8);
	h_tdR_eta->SetMarkerSize(1.8);*/
	h_t_pt->SetMarkerSize(1.8);
	h_t_phi->SetMarkerSize(1.8);
	h_t_eta->SetMarkerSize(1.8);/*
	h_3t_pt->SetMarkerSize(1.8);
	h_3t_phi->SetMarkerSize(1.8);
	h_3t_eta->SetMarkerSize(1.8);*/
        
	/*h0_pt->SetMarkerSize(1.8);
        h0_phi->SetMarkerSize(1.8);
        h0_eta->SetMarkerSize(1.8);*//*
        ht0dR_pt->SetMarkerSize(1.8);
        ht0dR_phi->SetMarkerSize(1.8);
        ht0dR_eta->SetMarkerSize(1.8);*/
        ht0_pt->SetMarkerSize(1.8);
        ht0_phi->SetMarkerSize(1.8);
        ht0_eta->SetMarkerSize(1.8);

	//Marker Style	
	/*h__pt->SetMarkerStyle(kFullTriangleDown);
	h__phi->SetMarkerStyle(kFullTriangleDown);
	h__eta->SetMarkerStyle(kFullTriangleDown);
	h_tdR_pt->SetMarkerStyle(kFullDiamond);
	h_tdR_phi->SetMarkerStyle(kFullDiamond);
	h_tdR_eta->SetMarkerStyle(kFullDiamond);*/
	h_t_pt->SetMarkerStyle(kFullCircle);
	h_t_phi->SetMarkerStyle(kFullCircle);
	h_t_eta->SetMarkerStyle(kFullCircle);
	/*h_3t_pt->SetMarkerStyle(kFullCircle);
	h_3t_phi->SetMarkerStyle(kFullCircle);
	h_3t_eta->SetMarkerStyle(kFullCircle);
        */
	/*h0_pt->SetMarkerStyle(kFullTriangleDown);
        h0_phi->SetMarkerStyle(kFullTriangleDown);
        h0_eta->SetMarkerStyle(kFullTriangleDown);*//*
        ht0dR_pt->SetMarkerStyle(kFullDiamond);
        ht0dR_phi->SetMarkerStyle(kFullDiamond);
        ht0dR_eta->SetMarkerStyle(kFullDiamond);*/
        ht0_pt->SetMarkerStyle(kFullCircle);
        ht0_phi->SetMarkerStyle(kFullCircle);
        ht0_eta->SetMarkerStyle(kFullCircle);

	/*h__pt->GetXaxis()->SetLabelFont(62);
	h__phi->GetXaxis()->SetLabelFont(62);
	h__eta->GetXaxis()->SetLabelFont(62);
	h_tdR_pt->GetXaxis()->SetLabelFont(62);
	h_tdR_phi->GetXaxis()->SetLabelFont(62);
	h_tdR_eta->GetXaxis()->SetLabelFont(62);*/
	h_t_pt->GetXaxis()->SetLabelFont(62);
	h_t_phi->GetXaxis()->SetLabelFont(62);
	h_t_eta->GetXaxis()->SetLabelFont(62);/*
	h_3t_pt->GetXaxis()->SetLabelFont(62);
	h_3t_phi->GetXaxis()->SetLabelFont(62);
	h_3t_eta->GetXaxis()->SetLabelFont(62);*/
        /*
	h0_pt->GetXaxis()->SetLabelFont(62);
        h0_phi->GetXaxis()->SetLabelFont(62);
        h0_eta->GetXaxis()->SetLabelFont(62);*//*
        ht0dR_pt->GetXaxis()->SetLabelFont(62);
        ht0dR_phi->GetXaxis()->SetLabelFont(62);
        ht0dR_eta->GetXaxis()->SetLabelFont(62);*/
        ht0_pt->GetXaxis()->SetLabelFont(62);
        ht0_phi->GetXaxis()->SetLabelFont(62);
        ht0_eta->GetXaxis()->SetLabelFont(62);
        /*
	h__pt->GetYaxis()->SetLabelFont(62);
	h__phi->GetYaxis()->SetLabelFont(62);
	h__eta->GetYaxis()->SetLabelFont(62);
	h_tdR_pt->GetYaxis()->SetLabelFont(62);
	h_tdR_phi->GetYaxis()->SetLabelFont(62);
	h_tdR_eta->GetYaxis()->SetLabelFont(62);*/
	h_t_pt->GetYaxis()->SetLabelFont(62);
	h_t_phi->GetYaxis()->SetLabelFont(62);
	h_t_eta->GetYaxis()->SetLabelFont(62);/*
	h_3t_pt->GetYaxis()->SetLabelFont(62);
	h_3t_phi->GetYaxis()->SetLabelFont(62);
	h_3t_eta->GetYaxis()->SetLabelFont(62);*/
        /*
	h0_pt->GetYaxis()->SetLabelFont(62);
        h0_phi->GetYaxis()->SetLabelFont(62);
        h0_eta->GetYaxis()->SetLabelFont(62);*//*
        ht0dR_pt->GetYaxis()->SetLabelFont(62);
        ht0dR_phi->GetYaxis()->SetLabelFont(62);
        ht0dR_eta->GetYaxis()->SetLabelFont(62);*/
        ht0_pt->GetYaxis()->SetLabelFont(62);
        ht0_phi->GetYaxis()->SetLabelFont(62);
        ht0_eta->GetYaxis()->SetLabelFont(62);
	/*
	h__pt->GetYaxis()->SetTitleOffset(1.2);
	h__phi->GetYaxis()->SetTitleOffset(1.2);
	h__eta->GetYaxis()->SetTitleOffset(1.2);
	h_tdR_pt->GetYaxis()->SetTitleOffset(1.2);
	h_tdR_phi->GetYaxis()->SetTitleOffset(1.2);
	h_tdR_eta->GetYaxis()->SetTitleOffset(1.2);*/
	h_t_pt->GetYaxis()->SetTitleOffset(1.2);
	h_t_phi->GetYaxis()->SetTitleOffset(1.2);
	h_t_eta->GetYaxis()->SetTitleOffset(1.2);/*
	h_3t_pt->GetYaxis()->SetTitleOffset(1.2);
	h_3t_phi->GetYaxis()->SetTitleOffset(1.2);
	h_3t_eta->GetYaxis()->SetTitleOffset(1.2);*/
        /*
	h0_pt->GetYaxis()->SetTitleOffset(1.2);
        h0_phi->GetYaxis()->SetTitleOffset(1.2);
        h0_eta->GetYaxis()->SetTitleOffset(1.2);*//*
        ht0dR_pt->GetYaxis()->SetTitleOffset(1.2);
        ht0dR_phi->GetYaxis()->SetTitleOffset(1.2);
        ht0dR_eta->GetYaxis()->SetTitleOffset(1.2);*/
        ht0_pt->GetYaxis()->SetTitleOffset(1.2);
        ht0_phi->GetYaxis()->SetTitleOffset(1.2);
        ht0_eta->GetYaxis()->SetTitleOffset(1.2);
	/*
	h__pt->GetYaxis()->CenterTitle();
	h__phi->GetYaxis()->CenterTitle();
	h__eta->GetYaxis()->CenterTitle();
	h_tdR_pt->GetYaxis()->CenterTitle();
	h_tdR_phi->GetYaxis()->CenterTitle();
	h_tdR_eta->GetYaxis()->CenterTitle();*/
	h_t_pt->GetYaxis()->CenterTitle();
	h_t_phi->GetYaxis()->CenterTitle();
	h_t_eta->GetYaxis()->CenterTitle();/*
	h_3t_pt->GetYaxis()->CenterTitle();
	h_3t_phi->GetYaxis()->CenterTitle();
	h_3t_eta->GetYaxis()->CenterTitle();*/
        /*
	h0_pt->GetYaxis()->CenterTitle();
        h0_phi->GetYaxis()->CenterTitle();
        h0_eta->GetYaxis()->CenterTitle();*//*
        ht0dR_pt->GetYaxis()->CenterTitle();
        ht0dR_phi->GetYaxis()->CenterTitle();
        ht0dR_eta->GetYaxis()->CenterTitle();*/
        ht0_pt->GetYaxis()->CenterTitle();
        ht0_phi->GetYaxis()->CenterTitle();
        ht0_eta->GetYaxis()->CenterTitle();
	/*
	h__pt->GetXaxis()->CenterTitle();
	h__phi->GetXaxis()->CenterTitle();
	h__eta->GetXaxis()->CenterTitle();
	h_tdR_pt->GetXaxis()->CenterTitle();
	h_tdR_phi->GetXaxis()->CenterTitle();
	h_tdR_eta->GetXaxis()->CenterTitle();*/
	h_t_pt->GetXaxis()->CenterTitle();
	h_t_phi->GetXaxis()->CenterTitle();
	h_t_eta->GetXaxis()->CenterTitle();/*
	h_3t_pt->GetXaxis()->CenterTitle();
	h_3t_phi->GetXaxis()->CenterTitle();
	h_3t_eta->GetXaxis()->CenterTitle();*/
        /*
	h0_pt->GetXaxis()->CenterTitle();
        h0_phi->GetXaxis()->CenterTitle();
        h0_eta->GetXaxis()->CenterTitle();*//*
        ht0dR_pt->GetXaxis()->CenterTitle();
        ht0dR_phi->GetXaxis()->CenterTitle();
        ht0dR_eta->GetXaxis()->CenterTitle();*/
        ht0_pt->GetXaxis()->CenterTitle();
        ht0_phi->GetXaxis()->CenterTitle();
        ht0_eta->GetXaxis()->CenterTitle();
	/*
	h__pt->GetYaxis()->SetTitleSize(0.04);
	h__phi->GetYaxis()->SetTitleSize(0.04);
	h__eta->GetYaxis()->SetTitleSize(0.04);
	h_tdR_pt->GetYaxis()->SetTitleSize(0.04);
	h_tdR_phi->GetYaxis()->SetTitleSize(0.04);
	h_tdR_eta->GetYaxis()->SetTitleSize(0.04);*/
	h_t_pt->GetYaxis()->SetTitleSize(0.04);
	h_t_phi->GetYaxis()->SetTitleSize(0.04);
	h_t_eta->GetYaxis()->SetTitleSize(0.04);/*
	h_3t_pt->GetYaxis()->SetTitleSize(0.04);
	h_3t_phi->GetYaxis()->SetTitleSize(0.04);
	h_3t_eta->GetYaxis()->SetTitleSize(0.04);*/
        /*
	h0_pt->GetYaxis()->SetTitleSize(0.04);
        h0_phi->GetYaxis()->SetTitleSize(0.04);
        h0_eta->GetYaxis()->SetTitleSize(0.04);*//*
        ht0dR_pt->GetYaxis()->SetTitleSize(0.04);
        ht0dR_phi->GetYaxis()->SetTitleSize(0.04);
        ht0dR_eta->GetYaxis()->SetTitleSize(0.04);*/
        ht0_pt->GetYaxis()->SetTitleSize(0.04);
        ht0_phi->GetYaxis()->SetTitleSize(0.04);
        ht0_eta->GetYaxis()->SetTitleSize(0.04);
	/*
	h__pt->GetYaxis()->SetRangeUser(0.7,1.04);
	h__phi->GetYaxis()->SetRangeUser(0.7,1.04);
	h__eta->GetYaxis()->SetRangeUser(0.5,1.04);
	h_tdR_pt->GetYaxis()->SetRangeUser(0.7,1.04);
	h_tdR_phi->GetYaxis()->SetRangeUser(0.7,1.04);
	h_tdR_eta->GetYaxis()->SetRangeUser(0.5,1.04);*/
	h_t_pt->GetYaxis()->SetRangeUser(0.6,1.04);
	h_t_phi->GetYaxis()->SetRangeUser(0.6,1.04);
	h_t_eta->GetYaxis()->SetRangeUser(0.6,1.04);/*
	h_3t_pt->GetYaxis()->SetRangeUser(0.7,1.04);
	h_3t_phi->GetYaxis()->SetRangeUser(0.7,1.04);
	h_3t_eta->GetYaxis()->SetRangeUser(0.5,1.04);*/
	h_t_pt->GetXaxis()->SetRangeUser(pt_min,pt_max);
        ht0_pt->GetXaxis()->SetRangeUser(pt_min,pt_max);
        /*
	h0_pt->GetYaxis()->SetRangeUser(0.9,1.04);
        h0_phi->GetYaxis()->SetRangeUser(0.9,1.04);
        h0_eta->GetYaxis()->SetRangeUser(0.9,1.04);*//*
        ht0dR_pt->GetYaxis()->SetRangeUser(0.7,1.04);
        ht0dR_phi->GetYaxis()->SetRangeUser(0.7,1.04);
        ht0dR_eta->GetYaxis()->SetRangeUser(0.7,1.04);*/
        ht0_pt->GetYaxis()->SetRangeUser(0.6,1.04);
        ht0_phi->GetYaxis()->SetRangeUser(0.6,1.04);
        ht0_eta->GetYaxis()->SetRangeUser(0.6,1.04);
	/*
	h__pt->GetXaxis()->SetTitleOffset(1.2);
	h__phi->GetXaxis()->SetTitleOffset(1.2);
	h__eta->GetXaxis()->SetTitleOffset(1.2);
	h_tdR_pt->GetXaxis()->SetTitleOffset(1.2);
	h_tdR_phi->GetXaxis()->SetTitleOffset(1.2);
	h_tdR_eta->GetXaxis()->SetTitleOffset(1.2);*/
	h_t_pt->GetXaxis()->SetTitleOffset(1.2);
	h_t_phi->GetXaxis()->SetTitleOffset(1.2);
	h_t_eta->GetXaxis()->SetTitleOffset(1.2);/*
	h_3t_pt->GetXaxis()->SetTitleOffset(1.2);
	h_3t_phi->GetXaxis()->SetTitleOffset(1.2);
	h_3t_eta->GetXaxis()->SetTitleOffset(1.2);*/
        /*
	h0_pt->GetXaxis()->SetTitleOffset(1.2);
        h0_phi->GetXaxis()->SetTitleOffset(1.2);
        h0_eta->GetXaxis()->SetTitleOffset(1.2);*//*
        ht0dR_pt->GetXaxis()->SetTitleOffset(1.2);
        ht0dR_phi->GetXaxis()->SetTitleOffset(1.2);
        ht0dR_eta->GetXaxis()->SetTitleOffset(1.2);*/
        ht0_pt->GetXaxis()->SetTitleOffset(1.2);
        ht0_phi->GetXaxis()->SetTitleOffset(1.2);
        ht0_eta->GetXaxis()->SetTitleOffset(1.2);
	
	/*
	h__pt->GetXaxis()->SetTitleSize(0.04);
	h__phi->GetXaxis()->SetTitleSize(0.04);
	h__eta->GetXaxis()->SetTitleSize(0.04);
	h_tdR_pt->GetXaxis()->SetTitleSize(0.04);
	h_tdR_phi->GetXaxis()->SetTitleSize(0.04);
	h_tdR_eta->GetXaxis()->SetTitleSize(0.04);*/
	h_t_pt->GetXaxis()->SetTitleSize(0.04);
	h_t_phi->GetXaxis()->SetTitleSize(0.04);
	h_t_eta->GetXaxis()->SetTitleSize(0.04);/*
	h_3t_pt->GetXaxis()->SetTitleSize(0.04);
	h_3t_phi->GetXaxis()->SetTitleSize(0.04);
	h_3t_eta->GetXaxis()->SetTitleSize(0.04);*/
        /*
	h0_pt->GetXaxis()->SetTitleSize(0.04);
        h0_phi->GetXaxis()->SetTitleSize(0.04);
        h0_eta->GetXaxis()->SetTitleSize(0.04);*//*
        ht0dR_pt->GetXaxis()->SetTitleSize(0.04);
        ht0dR_phi->GetXaxis()->SetTitleSize(0.04);
        ht0dR_eta->GetXaxis()->SetTitleSize(0.04);*/
        ht0_pt->GetXaxis()->SetTitleSize(0.04);
        ht0_phi->GetXaxis()->SetTitleSize(0.04);
        ht0_eta->GetXaxis()->SetTitleSize(0.04);
	/*
	h__pt->GetXaxis()->SetTitle("p_{t} [GeV/c]");
	h__phi->GetXaxis()->SetTitle("#phi [rad]");
	h__eta->GetXaxis()->SetTitle("#eta");
	h_tdR_pt->GetXaxis()->SetTitle("p_{t} [GeV/c]");
	h_tdR_phi->GetXaxis()->SetTitle("#phi [rad]");
	h_tdR_eta->GetXaxis()->SetTitle("#eta");*/
	h_t_pt->GetXaxis()->SetTitle("p_{t} [GeV/c]");
	h_t_phi->GetXaxis()->SetTitle("#phi [rad]");
	h_t_eta->GetXaxis()->SetTitle("#eta");/*
	h_3t_pt->GetXaxis()->SetTitle("p_{t} [GeV/c]");
	h_3t_phi->GetXaxis()->SetTitle("#phi [rad]");
	h_3t_eta->GetXaxis()->SetTitle("#eta");*/
        /*
	h0_pt->GetXaxis()->SetTitle("p_{t} [GeV/c]");
        h0_phi->GetXaxis()->SetTitle("#phi [rad]");
        h0_eta->GetXaxis()->SetTitle("#eta");*//*
        ht0dR_pt->GetXaxis()->SetTitle("p_{t} [GeV/c]");
        ht0dR_phi->GetXaxis()->SetTitle("#phi [rad]");
        ht0dR_eta->GetXaxis()->SetTitle("#eta");*/
        ht0_pt->GetXaxis()->SetTitle("p_{t} [GeV/c]");
        ht0_phi->GetXaxis()->SetTitle("#phi [rad]");
        ht0_eta->GetXaxis()->SetTitle("#eta");
	
	//! ToDO scale x axis
	/*
	ScaleXaxis(h__pt,1e-3);
	ScaleXaxis(h_tdR_pt,1e-3);*/
	ScaleXaxis(h_t_pt,1e-3);
	//ScaleXaxis(h_3t_pt,1e-3);
	//ScaleXaxis(h0_pt,1e-3);
        //ScaleXaxis(ht0dR_pt,1e-3);
        ScaleXaxis(ht0_pt,1e-3);
	
	
	//TCanvas * C = new TCanvas();
	TCanvas * C = new TCanvas("C","C",800,800);
	gStyle->SetOptStat(0);
	TGaxis::SetMaxDigits(2);
	C->SetGridx();
	C->SetGridy();
	C->SetTickx();
	C->SetTicky();
	
/*	C->SetLogx();
	
	//plot same
	
	Double_t x1= 0.7,y1= 0.75, x2 = 0.9, y2 = 0.9;
	C->SetLogx();
	h_pt->Draw();
	ht_pt->Draw("same");
	TLegend *leg1=new TLegend(x1,y1,x2,y2,"");
	leg1->SetFillColor(kWhite);
	leg1->SetBorderSize(0);
	leg1->AddEntry(h_pt,"ITK tracks");
	leg1->AddEntry(ht_pt,"TTT tracks");
	leg1->Draw();
	C->Print(out_file_,"pdf");
	h0_pt->Draw();
	ht0_pt->Draw("same");
	TLegend *leg2=new TLegend(x1,y1,x2,y2,"");
	leg2->SetFillColor(kWhite);
	leg2->SetBorderSize(0);
	leg2->AddEntry(h0_pt,"ITK tracks");
	leg2->AddEntry(ht0_pt,"TTT tracks");
	leg2->Draw();
	C->Print(out_file_open, "pdf");

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
	leg1_->AddEntry((TObject*)0,"ITK   TTT","");
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

	h_pt->Draw();
	htdR_pt->Draw("same");
	h__pt->Draw("same");
	h_tdR_pt->Draw("same");
	h_1_pt->Draw("same");
	h_1tdR_pt->Draw("same");
	h_2_pt->Draw("same");
	h_2tdR_pt->Draw("same");
	TLegend *leg1__=new TLegend(0.25,0.3,0.4,0.36,"");
	leg1__->SetFillColor(0);
	leg1__->SetBorderSize(0);
	leg1__->AddEntry((TObject*)0,"ITK   TTTdR","");
	leg1__->Draw();
	TLegend *leg1a_=new TLegend(0.285,0.1,0.6,0.3,"");
	leg1a_->SetNColumns(2);
	leg1a_->SetFillColor(kWhite);
	leg1a_->SetBorderSize(0);
	leg1a_->AddEntry(h_pt,",");
	leg1a_->AddEntry(htdR_pt,"abs(#eta) < 1.4");
	leg1a_->AddEntry(h__pt,",");
	leg1a_->AddEntry(h_tdR_pt,"abs(#eta) < 1.2");
	leg1a_->AddEntry(h_1_pt,",");
	leg1a_->AddEntry(h_1tdR_pt,"abs(#eta) < 1.0");
	leg1a_->AddEntry(h_2_pt,",");
	leg1a_->AddEntry(h_2tdR_pt,"abs(#eta) < 0.8");
	leg1a_->Draw();
	C->Print(out_file_,"pdf");

	htdR_pt->Draw();
	ht_pt->Draw("same");
	h_tdR_pt->Draw("same");
	h_t_pt->Draw("same");
	h_1tdR_pt->Draw("same");
	h_1t_pt->Draw("same");
	h_2tdR_pt->Draw("same");
	h_2t_pt->Draw("same");
	TLegend *leg1___=new TLegend(0.25,0.3,0.4,0.36,"");
	leg1___->SetFillColor(0);
	leg1___->SetBorderSize(0);
	leg1___->AddEntry((TObject*)0,"TTTdR   TTT","");
	leg1___->Draw();
	TLegend *leg1a__=new TLegend(0.285,0.1,0.6,0.3,"");
	leg1a__->SetNColumns(2);
	leg1a__->SetFillColor(kWhite);
	leg1a__->SetBorderSize(0);
	leg1a__->AddEntry(htdR_pt,",");
	leg1a__->AddEntry(ht_pt,"abs(#eta) < 1.4");
	leg1a__->AddEntry(h_tdR_pt,",");
	leg1a__->AddEntry(h_t_pt,"abs(#eta) < 1.2");
	leg1a__->AddEntry(h_1tdR_pt,",");
	leg1a__->AddEntry(h_1t_pt,"abs(#eta) < 1.0");
	leg1a__->AddEntry(h_2tdR_pt,",");
	leg1a__->AddEntry(h_2t_pt,"abs(#eta) < 0.8");
	leg1a__->Draw();
	C->Print(out_file_,"pdf");
	
	h_pt->Draw();
	htdR_pt->Draw("same");
	ht_pt->Draw("same");
	h__pt->Draw("same");
	h_tdR_pt->Draw("same");
	h_t_pt->Draw("same");
	h_1_pt->Draw("same");
	h_1tdR_pt->Draw("same");
	h_1t_pt->Draw("same");
	h_2_pt->Draw("same");
	h_2tdR_pt->Draw("same");
	h_2t_pt->Draw("same");
	TLegend *leg1____=new TLegend(0.25,0.3,0.4,0.36,"");
	leg1____->SetFillColor(0);
	leg1____->SetBorderSize(0);
	leg1____->AddEntry((TObject*)0,"ITK   TTTdR   TTT","");
	leg1____->Draw();
	TLegend *leg1a___=new TLegend(0.285,0.1,0.6,0.3,"");
	leg1a___->SetNColumns(3);
	leg1a___->SetFillColor(kWhite);
	leg1a___->SetBorderSize(0);
	leg1a___->AddEntry(h_pt,",");
	leg1a___->AddEntry(htdR_pt,",");
	leg1a___->AddEntry(ht_pt,"abs(#eta) < 1.4");
	leg1a___->AddEntry(h__pt,",");
	leg1a___->AddEntry(h_tdR_pt,",");
	leg1a___->AddEntry(h_t_pt,"abs(#eta) < 1.2");
	leg1a___->AddEntry(h_1_pt,",");
	leg1a___->AddEntry(h_1tdR_pt,",");
	leg1a___->AddEntry(h_1t_pt,"abs(#eta) < 1.0");
	leg1a___->AddEntry(h_2_pt,",");
	leg1a___->AddEntry(h_2tdR_pt,",");
	leg1a___->AddEntry(h_2t_pt,"abs(#eta) < 0.8");
	leg1a___->Draw();
	C->Print(out_file_,"pdf");
	
	h0_pt->Draw();
	ht0_pt->Draw("same");
	TLegend *leg2=new TLegend(x1,y1,x2,y2,"");
	leg2->SetFillColor(kWhite);
	leg2->SetBorderSize(0);
	leg2->AddEntry(h0_pt,"ITK tracks");
	leg2->AddEntry(ht0_pt,"TTT tracks");
	leg2->Draw();
	C->Print(out_file_,"pdf");

	ht0dR_pt->Draw();
	h0_pt->Draw("same");
	ht0_pt->Draw("same");
	TLegend *leg2_=new TLegend(x1,y1,x2,y2,"");
	leg2_->SetFillColor(kWhite);
	leg2_->SetBorderSize(0);
	leg2_->AddEntry(h0_pt,"ITK tracks");
	leg2_->AddEntry(ht0dR_pt,"TTTdR tracks");
	leg2_->AddEntry(ht0_pt,"TTT tracks");
	leg2_->Draw();
	C->Print(out_file_,"pdf");

	C->SetLogx(0);
	h_phi->Draw();
	ht_phi->Draw("same");
	TLegend *leg3=new TLegend(x1,y1,x2,y2,"");
	leg3->SetFillColor(kWhite);
	leg3->SetBorderSize(0);
        leg3->AddEntry(h_phi,"ITK tracks");
        leg3->AddEntry(ht_phi,"TTT tracks");
        leg3->Draw();
	C->Print(out_file_,"pdf");
	h0_phi->Draw();
	ht0_phi->Draw("same");
	TLegend *leg4=new TLegend(x1,y1,x2,y2,"");
	leg4->SetFillColor(kWhite);
	leg4->SetBorderSize(0);
        leg4->AddEntry(h0_phi,"ITK tracks");
        leg4->AddEntry(ht0_phi,"TTT tracks");
        leg4->Draw();
	C->Print(out_file_,"pdf");

	ht0dR_phi->Draw();
	h0_phi->Draw("same");
	ht0_phi->Draw("same");
	TLegend *leg4_=new TLegend(x1,y1,x2,y2,"");
	leg4_->SetFillColor(kWhite);
	leg4_->SetBorderSize(0);
        leg4_->AddEntry(h0_phi,"ITK tracks");
        leg4_->AddEntry(ht0dR_phi,"TTTdR tracks");
        leg4_->AddEntry(ht0_phi,"TTT tracks");
        leg4_->Draw();
	C->Print(out_file_,"pdf");

	h_eta->Draw();
	ht_eta->Draw("same");
	TLegend *leg5=new TLegend(x1,y1,x2,y2,"");
	leg5->SetFillColor(kWhite);
	leg5->SetBorderSize(0);
        leg5->AddEntry(h_eta,"ITK tracks");
        leg5->AddEntry(ht_eta,"TTT tracks");
        leg5->Draw();
	C->Print(out_file_,"pdf");
	h0_eta->Draw();
	ht0_eta->Draw("same");
	TLegend *leg6=new TLegend(x1,y1,x2,y2,"");
	leg6->SetFillColor(kWhite);
	leg6->SetBorderSize(0);
        leg6->AddEntry(h0_eta,"ITK tracks");
        leg6->AddEntry(ht0_eta,"TTT tracks");
        leg6->Draw();
	C->Print(out_file_,"pdf");

	ht0dR_eta->Draw();
	h0_eta->Draw("same");
	ht0_eta->Draw("same");
	TLegend *leg6_=new TLegend(x1,y1,x2,y2,"");
	leg6_->SetFillColor(kWhite);
	leg6_->SetBorderSize(0);
        leg6_->AddEntry(h0_eta,"ITK tracks");
        leg6_->AddEntry(ht0dR_eta,"TTTdR tracks");
        leg6_->AddEntry(ht0_eta,"TTT tracks");
        leg6_->Draw();
	C->Print(out_file_,"pdf");
*/	

	//two scales eta phi
	C->SetTicky(0);
	h_t_eta->GetYaxis()->SetAxisColor(kBlue);
	h_t_eta->GetYaxis()->SetTitleColor(kBlue);
	h_t_eta->GetYaxis()->SetTitleSize(0.04);
	h_t_eta->GetYaxis()->SetLabelColor(kBlue);
	h_t_eta->SetLineColor(kBlue);
	h_t_eta->SetMarkerColor(kBlue);
	h_t_eta->Draw("");
	C->Update();
	Float_t rightmax = 1*ht0_eta->GetMaximum();
	Float_t scale = gPad->GetUymax()/rightmax;
	ht0_eta->SetLineColor(kRed);
	ht0_eta->SetMarkerColor(kRed);
	ht0_eta->Scale(scale);
	ht0_eta->Draw("same");
	//draw an axis on the right side
	TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	gPad->GetUxmax(), gPad->GetUymax(),0.5,rightmax,510,"+L");
	axis->SetLineColor(kRed);
	axis->SetLabelColor(kRed);
	axis->SetLabelFont(62);
//	axis->SetLabelSize(0.05);
	axis->SetTitle("purity");
	axis->SetTitleColor(kRed);
	axis->SetTitleSize(0.04);
	axis->SetTitleOffset(1.2);
	axis->SetMaxDigits(2);
	axis->CenterTitle();
	axis->Draw();
	
	C->Print(out_file_open,"pdf");
	h_t_phi->GetYaxis()->SetAxisColor(kBlue);
	h_t_phi->GetYaxis()->SetTitleColor(kBlue);
	h_t_phi->GetYaxis()->SetTitleSize(0.04);
	h_t_phi->GetYaxis()->SetLabelColor(kBlue);
	h_t_phi->SetLineColor(kBlue);
	h_t_phi->SetMarkerColor(kBlue);
	h_t_phi->Draw();
	h_t_phi->Draw("same");
	C->Update();
	rightmax = 1*ht0_phi->GetMaximum();
	scale = gPad->GetUymax()/rightmax;
	ht0_phi->SetLineColor(kRed);
	ht0_phi->SetMarkerColor(kRed);
	ht0_phi->Scale(scale);
	ht0_phi->Draw("same");
	//draw an axis on the right side
	TGaxis *axis1 = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	gPad->GetUxmax(), gPad->GetUymax(),0.5,rightmax,510,"+L");
	axis1->SetLineColor(kRed);
	axis1->SetLabelColor(kRed);
//	axis->SetLabelSize(0.05);
	axis1->SetTitle("purity");
	axis1->SetTitleColor(kRed);
	axis1->SetLabelFont(62);
	axis1->SetTitleSize(0.04);
	axis1->SetTitleOffset(1.2);
	axis1->SetMaxDigits(2);
	axis1->CenterTitle();
	axis1->Draw();
	
	C->Print(out_file_, "pdf");

	h_t_pt->GetYaxis()->SetRangeUser(0.6,1.04);
	ht0_pt->GetYaxis()->SetRangeUser(0.6,1.04);
	h_t_pt->GetYaxis()->SetAxisColor(kBlue);
	h_t_pt->GetYaxis()->SetTitleColor(kBlue);
	h_t_pt->GetYaxis()->SetTitleSize(0.04);
	h_t_pt->GetYaxis()->SetLabelColor(kBlue);
	h_t_pt->SetLineColor(kBlue);
	h_t_pt->SetMarkerColor(kBlue);	
	h_t_pt->Draw();
	C->Update();
	rightmax = 1*ht0_pt->GetMaximum();
	scale = gPad->GetUymax()/rightmax;
	ht0_pt->SetLineColor(kRed);
	ht0_pt->SetMarkerColor(kRed);
	ht0_pt->Scale(scale);
	ht0_pt->Draw("same");
	//draw an axis on the right side
	TGaxis *axis2 = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	gPad->GetUxmax(), gPad->GetUymax(),0.6,rightmax,510,"+L");
	axis2->SetLineColor(kRed);
	axis2->SetLabelColor(kRed);
//	axis->SetLabelSize(0.05);
	axis2->SetLabelFont(62);
	axis2->SetTitle("purity");
	axis2->SetTitleColor(kRed);
	axis2->SetTitleSize(0.04);
	axis2->SetTitleOffset(1.2);
	axis2->SetMaxDigits(2);
	axis2->CenterTitle();
	axis2->Draw();
	C->SetLogx();

	C->Print(out_file_,"pdf");
	C->SetLogx(0);
	h_t_pt->GetYaxis()->SetAxisColor(kBlue);
	h_t_pt->GetYaxis()->SetTitleColor(kBlue);
	h_t_pt->GetYaxis()->SetTitleSize(0.04);
	h_t_pt->GetYaxis()->SetLabelColor(kBlue);
	h_t_pt->SetLineColor(kBlue);
	h_t_pt->SetMarkerColor(kBlue);	
	h_t_pt->Draw("same");
	C->Update();
	/*rightmax = 1*h0_pt->GetMaximum();
	scale = gPad->GetUymax()/rightmax;
	h0_pt->SetLineColor(kRed);
	ht0_pt->SetLineColor(kRed);
	h0_pt->SetMarkerColor(kRed);
	ht0_pt->SetMarkerColor(kRed);
	h0_pt->Scale(scale);*/
	ht0_pt->Draw("same");
	//draw an axis on the right side
	/*TGaxis *axis3 = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	gPad->GetUxmax(), gPad->GetUymax(),0.7,rightmax,510,"+L");
	axis3->SetLineColor(kRed);
	axis3->SetLabelColor(kRed);
//	axis->SetLabelSize(0.05);
	axis3->SetTitle("purity");
	axis3->SetTitleColor(kRed);
	axis3->SetTitleSize(0.04);
	axis3->SetTitleOffset(1.2);
	axis3->SetMaxDigits(2);
	axis3->CenterTitle();*/
	axis2->Draw();
	C->SetLogx();
	
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
	h_pt->GetYaxis()->SetTitleOffset(1.2);
	h_phi->GetYaxis()->SetTitleOffset(1.2);
	h_eta->GetYaxis()->SetTitleOffset(1.2);
/*        h0_pt->GetYaxis()->SetTitleOffset(1.2);
        h0_phi->GetYaxis()->SetTitleOffset(1.2);
        h0_eta->GetYaxis()->SetTitleOffset(1.2);
*/	ht_pt->GetYaxis()->SetTitleOffset(1.2);
	ht_phi->GetYaxis()->SetTitleOffset(1.2);
	ht_eta->GetYaxis()->SetTitleOffset(1.2);
/*        ht0_pt->GetYaxis()->SetTitleOffset(1.2);
        ht0_phi->GetYaxis()->SetTitleOffset(1.2);
        ht0_eta->GetYaxis()->SetTitleOffset(1.2);
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
	h_pt->GetYaxis()->SetTitleSize(0.04);
	h_phi->GetYaxis()->SetTitleSize(0.04);
	h_eta->GetYaxis()->SetTitleSize(0.04);
/*        h0_pt->GetYaxis()->SetTitleSize(0.04);
        h0_phi->GetYaxis()->SetTitleSize(0.04);
        h0_eta->GetYaxis()->SetTitleSize(0.04);
*/	ht_pt->GetYaxis()->SetTitleSize(0.04);
	ht_phi->GetYaxis()->SetTitleSize(0.04);
	ht_eta->GetYaxis()->SetTitleSize(0.04);
/*        ht0_pt->GetYaxis()->SetTitleSize(0.04);
        ht0_phi->GetYaxis()->SetTitleSize(0.04);
        ht0_eta->GetYaxis()->SetTitleSize(0.04);
*/
	h_pt->GetYaxis()->SetRangeUser(0.6,1.04);
	h_phi->GetYaxis()->SetRangeUser(0.6,1.04);
	h_eta->GetYaxis()->SetRangeUser(0.6,1.04);
/*        h0_pt->GetYaxis()->SetRangeUser(0.9,1.04);
        h0_phi->GetYaxis()->SetRangeUser(0.9,1.04);
        h0_eta->GetYaxis()->SetRangeUser(0.9,1.04);
*/	ht_pt->GetYaxis()->SetRangeUser(0.6,1.04);
	ht_phi->GetYaxis()->SetRangeUser(0.6,1.04);
	ht_eta->GetYaxis()->SetRangeUser(0.6,1.04);
/*        ht0_pt->GetYaxis()->SetRangeUser(0.9,1.04);
        ht0_phi->GetYaxis()->SetRangeUser(0.9,1.04);
        ht0_eta->GetYaxis()->SetRangeUser(0.9,1.04);
*/
	h_pt->GetXaxis()->SetTitleOffset(1.2);
	h_phi->GetXaxis()->SetTitleOffset(1.2);
	h_eta->GetXaxis()->SetTitleOffset(1.2);
/*        h0_pt->GetXaxis()->SetTitleOffset(1.2);
        h0_phi->GetXaxis()->SetTitleOffset(1.2);
        h0_eta->GetXaxis()->SetTitleOffset(1.2);
*/	
	ht_pt->GetXaxis()->SetTitleOffset(1.2);
	ht_phi->GetXaxis()->SetTitleOffset(1.2);
	ht_eta->GetXaxis()->SetTitleOffset(1.2);
/*        ht0_pt->GetXaxis()->SetTitleOffset(1.2);
        ht0_phi->GetXaxis()->SetTitleOffset(1.2);
        ht0_eta->GetXaxis()->SetTitleOffset(1.2);
*/	

	h_pt->GetXaxis()->SetTitleSize(0.04);
	h_phi->GetXaxis()->SetTitleSize(0.04);
	h_eta->GetXaxis()->SetTitleSize(0.04);
/*        h0_pt->GetXaxis()->SetTitleSize(0.04);
        h0_phi->GetXaxis()->SetTitleSize(0.04);
        h0_eta->GetXaxis()->SetTitleSize(0.04);
*/	
	ht_pt->GetXaxis()->SetTitleSize(0.04);
	ht_phi->GetXaxis()->SetTitleSize(0.04);
	ht_eta->GetXaxis()->SetTitleSize(0.04);
/*        ht0_pt->GetXaxis()->SetTitleSize(0.04);
        ht0_phi->GetXaxis()->SetTitleSize(0.04);
        ht0_eta->GetXaxis()->SetTitleSize(0.04);
*/	
	h_pt->GetXaxis()->SetTitle("p_{t} [GeV/c]");
	h_phi->GetXaxis()->SetTitle("#phi [rad]");
	h_eta->GetXaxis()->SetTitle("#eta");
/*        h0_pt->GetXaxis()->SetTitle("p_{t} [GeV/c]");
        h0_phi->GetXaxis()->SetTitle("#phi [rad]");
        h0_eta->GetXaxis()->SetTitle("#eta");
*/	
	ht_pt->GetXaxis()->SetTitle("p_{t} [GeV/c]");
	ht_phi->GetXaxis()->SetTitle("#phi [rad]");
	ht_eta->GetXaxis()->SetTitle("#eta");
/*        ht0_pt->GetXaxis()->SetTitle("p_{t} [GeV/c]");
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
	ScaleXaxis(ht_pt,1e-3);
	ht_pt->Draw();
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
	h_eta->GetYaxis()->SetTitleSize(0.04);
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
	axis->SetTitleSize(0.04);
	axis->SetTitleOffset(1.2);
	axis->SetMaxDigits(2);
	axis->CenterTitle();
	axis->Draw();
	
	C->Print(out_file_,"pdf");
	h_phi->GetYaxis()->SetAxisColor(kBlue);
	h_phi->GetYaxis()->SetTitleColor(kBlue);
	h_phi->GetYaxis()->SetTitleSize(0.04);
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
	axis1->SetTitleSize(0.04);
	axis1->SetTitleOffset(1.2);
	axis1->SetMaxDigits(2);
	axis1->CenterTitle();
	axis1->Draw();
	
	C->Print(out_file_,"pdf");
	h_pt->GetYaxis()->SetAxisColor(kBlue);
	h_pt->GetYaxis()->SetTitleColor(kBlue);
	h_pt->GetYaxis()->SetTitleSize(0.04);
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
	axis2->SetTitleSize(0.04);
	axis2->SetTitleOffset(1.2);
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

