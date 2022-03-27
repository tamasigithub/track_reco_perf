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

#include "plot_props.h"

const char* out_path = "./plots"; 
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
int write_topdf(const char* output_file_name = "PurVsEtaPtPhi_cutCompFCC-hhCompareEta2_5")
{

	char out_file_open[1023];
        sprintf(out_file_open,"%s/%s.pdf(",out_path,output_file_name);
        char out_file_[1023];
        sprintf(out_file_,"%s/%s.pdf",out_path,output_file_name);
        char out_file_close[1023];
        sprintf(out_file_close,"%s/%s.pdf)",out_path,output_file_name);

	//! purity wide cuts
	//! purity TTT barcode matched tracks no kappa cut
	TFile* f0 = TFile::Open("./plots/PU1k_ggF1.0-pur_30mm_eta2.5opt3_2GeV.root");
	//TFile* f0 = TFile::Open("./plots/PU1k_ggF1.0-pur_30mmEC67mm_opt10_1.root");
	TH1D* h0_pt 	= (TH1D*)f0->Get("h_pur_vs_ptPU");
	TH1D* h0_phi	= (TH1D*)f0->Get("h_pur_vs_phiPU");
	TH1D* h0_eta	= (TH1D*)f0->Get("h_pur_vs_etaPU");
	//! purity TTT barcode matched tracks #sigma 5
	//TFile* f1 = TFile::Open("./plots/PU1k_ggF1.0-pur_30mm_eta2.5opt5_2GeV.root");
	TFile* f1 = TFile::Open("./plots/PU1k_ggF1.0-pur_30mmEC67mm_sel3_1.root");
	TH1D* h1_pt = (TH1D*)f1->Get("h_pur_vs_ptPU");
	TH1D* h1_phi	= (TH1D*)f1->Get("h_pur_vs_phiPU");
	TH1D* h1_eta	= (TH1D*)f1->Get("h_pur_vs_etaPU");
	//! purity TTT barcode matched tracks #sigma 4
	TFile* f2 = TFile::Open("./plots/PU1k_ggF1.0-pur_30mm_eta2.5opt5_2GeV.root");
	//TFile* f2 = TFile::Open("./plots/PU1k_ggF1.0-pur_30mmEC67mm_sel4_1.root");
	TH1D* h2_pt = (TH1D*)f2->Get("h_pur_vs_ptPU");
	TH1D* h2_phi	= (TH1D*)f2->Get("h_pur_vs_phiPU");
	TH1D* h2_eta	= (TH1D*)f2->Get("h_pur_vs_etaPU");
	//! purity TTT barcode matched tracks #sigma 3
	//TFile* f3 = TFile::Open("./plots/PU1k_ggF1.0-pur_30mm_eta2.5opt3_2GeV.root");
	TFile* f3 = TFile::Open("./plots/PU1k_ggF1.0-pur_30mmEC67mm_sel5_1.root");
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
	h3_pt->SetMarkerColor(kRed-9);
	h3_phi->SetMarkerColor(kRed-9);
	h3_eta->SetMarkerColor(kRed-9);
        h1_pt->SetMarkerColor(kRed+2);
        h1_phi->SetMarkerColor(kRed+2);
        h1_eta->SetMarkerColor(kRed+2);
	
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
	h2_pt->SetMarkerStyle(kOpenDiamond);
	h2_phi->SetMarkerStyle(kOpenDiamond);
	h2_eta->SetMarkerStyle(kOpenDiamond);
        h0_pt->SetMarkerStyle(kOpenDiamond);
        h0_phi->SetMarkerStyle(kOpenDiamond);
        h0_eta->SetMarkerStyle(kOpenDiamond);
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
	
	h2_pt->GetYaxis()->SetTitleOffset(1.0);
	h2_phi->GetYaxis()->SetTitleOffset(1.0);
	h2_eta->GetYaxis()->SetTitleOffset(1.0);
        h0_pt->GetYaxis()->SetTitleOffset(1.0);
        h0_phi->GetYaxis()->SetTitleOffset(1.0);
        h0_eta->GetYaxis()->SetTitleOffset(1.0);
	h3_pt->GetYaxis()->SetTitleOffset(1.0);
	h3_phi->GetYaxis()->SetTitleOffset(1.0);
	h3_eta->GetYaxis()->SetTitleOffset(1.0);
        h1_pt->GetYaxis()->SetTitleOffset(1.0);
        h1_phi->GetYaxis()->SetTitleOffset(1.0);
        h1_eta->GetYaxis()->SetTitleOffset(1.0);
	
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

	h2_pt->GetYaxis()->SetRangeUser(0.2,1.04);
	h2_phi->GetYaxis()->SetRangeUser(0.65,1.04);
	h2_eta->GetYaxis()->SetRangeUser(0.65,1.04);
        h0_pt->GetYaxis()->SetRangeUser(0.3,1.04);
        h0_phi->GetYaxis()->SetRangeUser(0.65,1.04);
        h0_eta->GetYaxis()->SetRangeUser(0.65,1.04);
	h3_pt->GetYaxis()->SetRangeUser(0.3,1.04);
	h3_phi->GetYaxis()->SetRangeUser(0.65,1.04);
	h3_eta->GetYaxis()->SetRangeUser(0.65,1.04);
        h1_pt->GetYaxis()->SetRangeUser(0.3,1.04);
        h1_phi->GetYaxis()->SetRangeUser(0.65,1.04);
        h1_eta->GetYaxis()->SetRangeUser(0.65,1.04);

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
	
	h2_pt->GetYaxis()->SetTitle("purity");
	h2_phi->GetYaxis()->SetTitle("purity");
	h2_eta->GetYaxis()->SetTitle("purity");
        h0_pt->GetYaxis()->SetTitle("purity");
        h0_phi->GetYaxis()->SetTitle("purity");
        h0_eta->GetYaxis()->SetTitle("purity");
	
	h3_pt->GetYaxis()->SetTitle("purity");
	h3_phi->GetYaxis()->SetTitle("purity");
	h3_eta->GetYaxis()->SetTitle("purity");
        h1_pt->GetYaxis()->SetTitle("purity");
        h1_phi->GetYaxis()->SetTitle("purity");
        h1_eta->GetYaxis()->SetTitle("purity");
	
	h2_pt->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	h2_phi->GetXaxis()->SetTitle("#varphi [rad]");
	h2_eta->GetXaxis()->SetTitle("#eta");
        h0_pt->GetXaxis()->SetTitle("p_{T} [GeV/c]");
        h0_phi->GetXaxis()->SetTitle("#varphi [rad]");
        h0_eta->GetXaxis()->SetTitle("#eta");
	
	h3_pt->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	h3_phi->GetXaxis()->SetTitle("#varphi [rad]");
	h3_eta->GetXaxis()->SetTitle("#eta");
        h1_pt->GetXaxis()->SetTitle("p_{T} [GeV/c]");
        h1_phi->GetXaxis()->SetTitle("#varphi [rad]");
        h1_eta->GetXaxis()->SetTitle("#eta");
	
	ScaleXaxis(h0_pt,1e-3);
	ScaleXaxis(h1_pt,1e-3);
	ScaleXaxis(h2_pt,1e-3);
	ScaleXaxis(h3_pt,1e-3);
	
	TCanvas * C = new TCanvas("C","C",800,800);
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	TGaxis::SetMaxDigits(2);
	//C->SetGridx();
	//C->SetGridy();
	//C->SetTickx();
	//C->SetTicky();
	Legends();

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
	
	Double_t x1= 0.20,y1= 0.2, x2 = 0.35, y2 = 0.4, y11 = 0.15, y22 = 0.35;
	C->SetLogx();
	h0_pt->Draw();
	h1_pt->Draw("same");
	h2_pt->Draw("same");
	h3_pt->Draw("same");
	TLegend *leg_1=new TLegend(x1,y11,x2,y22,"");
	leg_1->SetFillStyle(0);
	leg_1->SetBorderSize(0);
	leg_1->SetTextSize(0.04);
	//leg_1->SetNColumns(2);
	//leg_1->AddEntry(h0_pt,"wide");
	//leg_1->AddEntry((TObject*)0, "(w/o d#phi_{2}, dz_{2}, #kappa_{cut})","");
	//leg_1->AddEntry(h1_pt,"loose");
	//leg_1->AddEntry((TObject*)0,"(w/o #kappa_{cut})","");                 
	//leg_1->AddEntry(h2_pt,"medium");
	//leg_1->AddEntry((TObject*)0,"(#sigma_{#kappa} = 5)","");              
	//leg_1->AddEntry(h3_pt,"tight");
	//leg_1->AddEntry((TObject*)0,"(#sigma_{#kappa} = 3)","");
	leg_1->AddEntry(h0_pt,"|d#kappa| < 3 #sigma_{#kappa} (Ext. Br)");
	leg_1->AddEntry(h1_pt,"|d#kappa| < 3 #sigma_{#kappa}");
	leg_1->AddEntry(h2_pt,"|d#kappa| < 5 #sigma_{#kappa} (Ext. Br)");
	leg_1->AddEntry(h3_pt,"|d#kappa| < 5 #sigma_{#kappa}");
	leg_1->Draw();
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	C->Print(out_file_,"pdf");
	C->SaveAs("./tex/purVsptForAllcuts_Eta2_5.tex");
	h1_pt->Draw();
	h2_pt->Draw("same");
	h3_pt->Draw("same");
	TLegend *leg_1a=new TLegend(x1,y1,x2,y2,"");
	leg_1a->SetFillStyle(0);
	leg_1a->SetBorderSize(0);
	leg_1a->SetTextSize(0.04);
	leg_1a->AddEntry(h1_pt,"|d#kappa| < 3 #sigma_{#kappa}");
	leg_1a->AddEntry(h2_pt,"|d#kappa| < 5 #sigma_{#kappa} (Ext. Br)");
	leg_1a->AddEntry(h3_pt,"|d#kappa| < 5 #sigma_{#kappa}");
	//leg_1a->SetNColumns(2);
	//leg_1a->AddEntry(h1_pt,"loose");
	//leg_1a->AddEntry((TObject*)0, "(w/o #kappa_{cut})","");   
	//leg_1a->AddEntry(h2_pt,"medium");
	//leg_1a->AddEntry((TObject*)0,"(#sigma_{#kappa} = 5)","");
	//leg_1a->AddEntry(h3_pt,"tight");
	//leg_1a->AddEntry((TObject*)0,"(#sigma_{#kappa} = 3)","");
	leg_1a->Draw();
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	C->Print(out_file_,"pdf");
	C->SaveAs("./tex/purVsptFor3cuts_Eta2_5.tex");
	h0_pt->Draw();
	h1_pt->Draw("same");
	TLegend *leg_1b=new TLegend(x1,y11,x2,y22,"");
	leg_1b->SetFillStyle(0);
	leg_1b->SetBorderSize(0);
	leg_1b->SetTextSize(0.04);
	leg_1b->AddEntry(h0_pt,"|d#kappa| < 3 #sigma_{#kappa} (Ext. Br)");
	leg_1b->AddEntry(h1_pt,"|d#kappa| < 3 #sigma_{#kappa}");
	//leg_1b->AddEntry(h0_pt,"wide   (w/o d#phi_{2}, dz_{2}, #kappa_{cut})");
	//leg_1b->AddEntry(h1_pt,"loose  (w/o #kappa_{cut})");                 
	leg_1b->Draw();
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	C->SaveAs("./tex/purVsptFor2cuts_Eta2_5.tex");
	C->Print(out_file_,"pdf");

	C->SetLogx(0);
	h0_phi->Draw();
	h1_phi->Draw("same");
	h2_phi->Draw("same");
	h3_phi->Draw("same");
	TLegend *leg_2=new TLegend(x1,y11,x2,y22,"");
	leg_2->SetFillStyle(0);
	leg_2->SetBorderSize(0);
	leg_2->SetTextSize(0.04);
	leg_2->AddEntry(h0_phi,"w/o #kappa cut");
	leg_2->AddEntry(h1_phi,"|d#kappa| < 5 #sigma_{#kappa}");
	leg_2->AddEntry(h2_phi,"|d#kappa| < 4 #sigma_{#kappa}");
	leg_2->AddEntry(h3_phi,"|d#kappa| < 3 #sigma_{#kappa}");
	//leg_2->SetNColumns(2);
	//leg_2->AddEntry(h0_phi,"wide");
	//leg_2->AddEntry((TObject*)0, "(w/o d#phi_{2}, dz_{2}, #kappa_{cut})","");
	//leg_2->AddEntry(h1_phi,"loose");
	//leg_2->AddEntry((TObject*)0,"(w/o #kappa_{cut})","");                 
	//leg_2->AddEntry(h2_phi,"medium");
	//leg_2->AddEntry((TObject*)0,"(#sigma_{#kappa} = 5)","");              
	//leg_2->AddEntry(h3_phi,"tight");
	//leg_2->AddEntry((TObject*)0,"(#sigma_{#kappa} = 3)","");
	leg_2->Draw();
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	C->Print(out_file_,"pdf");
	C->SaveAs("./tex/purVsphiForAllcuts_Eta2_5.tex");
	h1_phi->Draw();
	h2_phi->Draw("same");
	h3_phi->Draw("same");
	TLegend *leg_2a=new TLegend(x1,y1,x2,y2,"");
	leg_2a->SetFillStyle(0);
	leg_2a->SetBorderSize(0);
	leg_2a->SetTextSize(0.04);
	leg_2a->AddEntry(h1_phi,"|d#kappa| < 5 #sigma_{#kappa}");
	leg_2a->AddEntry(h2_phi,"|d#kappa| < 4 #sigma_{#kappa}");
	leg_2a->AddEntry(h3_phi,"|d#kappa| < 3 #sigma_{#kappa}");
	//leg_2a->SetNColumns(2);
	//leg_2a->AddEntry(h1_phi,"loose");
	//leg_2a->AddEntry((TObject*)0, "(w/o #kappa_{cut})","");   
	//leg_2a->AddEntry(h2_phi,"medium");
	//leg_2a->AddEntry((TObject*)0,"(#sigma_{#kappa} = 5)","");
	//leg_2a->AddEntry(h3_phi,"tight");
	//leg_2a->AddEntry((TObject*)0,"(#sigma_{#kappa} = 3)","");
	leg_2a->Draw();
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	C->Print(out_file_,"pdf");
	C->SaveAs("./tex/purVsphiFor3cuts_Eta2_5.tex");
	h0_phi->Draw();
	h1_phi->Draw("same");
	TLegend *leg_2b=new TLegend(x1,y11,x2,y22,"");
	leg_2b->SetFillStyle(0);
	leg_2b->SetBorderSize(0);
	leg_2b->SetTextSize(0.04);
	leg_2b->AddEntry(h0_phi,"|d#kappa| < 3 #sigma_{#kappa} (Ext. Br)");
	leg_2b->AddEntry(h1_phi,"|d#kappa| < 3 #sigma_{#kappa}");
	//leg_2b->AddEntry(h0_phi,"wide   (w/o d #phi_{2}, dz_{2}, #kappa_{cut})");
	//leg_2b->AddEntry(h1_phi,"loose  (w/o #kappa_{cut})");                 
	leg_2b->Draw();
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	C->SaveAs("./tex/purVsphiFor2cuts_Eta2_5.tex");
	C->Print(out_file_,"pdf");


	h0_eta->Draw();
	h1_eta->Draw("same");
	h2_eta->Draw("same");
	h3_eta->Draw("same");
	TLegend *leg_3=new TLegend(x1,y11,x2,y22,"");
	leg_3->SetFillStyle(0);
	leg_3->SetBorderSize(0); 
	leg_3->SetTextSize(0.04);
	leg_3->AddEntry(h0_eta,"w/o #kappa cut");
	leg_3->AddEntry(h1_eta,"|d#kappa| < 5 #sigma_{#kappa}");
	leg_3->AddEntry(h2_eta,"|d#kappa| < 4 #sigma_{#kappa}");
	leg_3->AddEntry(h3_eta,"|d#kappa| < 3 #sigma_{#kappa}");
	//leg_3->SetNColumns(2);
	//leg_3->AddEntry(h0_eta,"wide");
	//leg_3->AddEntry((TObject*)0, "(w/o d#phi_{2}, dz_{2}, #kappa_{cut})","");
	//leg_3->AddEntry(h1_eta,"loose");
	//leg_3->AddEntry((TObject*)0,"(w/o #kappa_{cut})","");                 
	//leg_3->AddEntry(h2_eta,"medium");
	//leg_3->AddEntry((TObject*)0,"(#sigma_{#kappa} = 5)","");              
	//leg_3->AddEntry(h3_eta,"tight");
	//leg_3->AddEntry((TObject*)0,"(#sigma_{#kappa} = 3)","");             
	leg_3->Draw();
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	C->Print(out_file_,"pdf");
	C->SaveAs("./tex/purVsetaForAllcuts_Eta2_5.tex");
	h1_eta->Draw();
	h2_eta->Draw("same");
	h3_eta->Draw("same");
	TLegend *leg_3a=new TLegend(x1,y1,x2,y2,"");
	leg_3a->SetFillStyle(0);
	leg_3a->SetBorderSize(0);
	leg_3a->SetTextSize(0.04);
	leg_3a->AddEntry(h1_eta,"|d#kappa| < 5 #sigma_{#kappa}");
	leg_3a->AddEntry(h2_eta,"|d#kappa| < 4 #sigma_{#kappa}");
	leg_3a->AddEntry(h3_eta,"|d#kappa| < 3 #sigma_{#kappa}");
	//leg_3a->SetNColumns(2);
	//leg_3a->AddEntry(h1_eta,"loose");
	//leg_3a->AddEntry((TObject*)0, "(w/o #kappa_{cut})","");   
	//leg_3a->AddEntry(h2_eta,"medium");
	//leg_3a->AddEntry((TObject*)0,"(#sigma_{#kappa} = 5)","");
	//leg_3a->AddEntry(h3_eta,"tight");
	//leg_3a->AddEntry((TObject*)0,"(#sigma_{#kappa} = 3)","");
	leg_3a->Draw();
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	C->Print(out_file_,"pdf");
	C->SaveAs("./tex/purVsetaFor3cuts_Eta2_5.tex");
	h0_eta->Draw();
	h1_eta->Draw("same");
	TLegend *leg_3b=new TLegend(x1,y11,x2,y22,"");
	leg_3b->SetFillStyle(0);
	leg_3b->SetBorderSize(0);
	leg_3b->SetTextSize(0.04);
	leg_3b->AddEntry(h0_eta,"|d#kappa| < 3 #sigma_{#kappa} (Ext. Br)");
	leg_3b->AddEntry(h1_eta,"|d#kappa| < 3 #sigma_{#kappa}");
	//leg_3b->AddEntry(h0_eta,"wide   (w/o d #phi_{2}, dz_{2}, #kappa_{cut})");
	//leg_3b->AddEntry(h1_eta,"loose  (w/o #kappa_{cut})");                 
	leg_3b->Draw();
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	C->SaveAs("./tex/purVsetaFor2cuts_Eta2_5.tex");
	

/*	C->Print(out_file_,"pdf");
	C->Clear();
	leg_1->Draw();
*/

	C->Print(out_file_close,"pdf");
return 0;
}

