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

#include "plot_props.h"

//Float_t LINE_WIDTH = 2.5;
//Float_t TITLE_SIZE = 0.04;
//Float_t MARKER_SIZE = 1.2;
//Float_t AXISTITLE_OFFSET = 1.0;
//Float_t YAXISTITLE_OFFSET = 1.1;

//const char* out_path = "/eos/user/t/tkar/www/TTT/plots/resolution"; 
const char* out_path = "./plots"; 
void ScaleAxis(TAxis *a, Double_t Scale)
{
  if (!a) return; // just a precaution
  if (a->GetXbins()->GetSize())
    {
      // an axis with variable bins
      // note: bins must remain in increasing order, hence the "Scale"
      // function must be strictly (monotonically) increasing
      std::cout<<"variable bin\n";
      TArrayD X(*(a->GetXbins()));
      for(Int_t i = 0; i < X.GetSize(); i++) X[i] = X[i]*Scale;
      a->Set((X.GetSize() - 1), X.GetArray()); // new Xbins
    }
  else
    {
      // an axis with fix bins
      // note: we modify Xmin and Xmax only, hence the "Scale" function
      // must be linear (and Xmax must remain greater than Xmin)
      std::cout<<"fixed bin\n";
      a->Set( a->GetNbins(),
              (a->GetXmin())*Scale, // new Xmin
              (a->GetXmax())*Scale ); // new Xmax
    }
  return;
}

void ScaleXaxis(TH1 *h, Double_t Scale)
{
  if (!h) return; // just a precaution
  ScaleAxis(h->GetXaxis(), Scale);
  return;
}

void ScaleYaxis(TH1 *h, Double_t Scale)
{
  if (!h) return; // just a precaution
  ScaleAxis(h->GetYaxis(), Scale);
  return;
}
//int write_topdf(const char* output_file_name = "ResoVsPt_FCC_PU0hh4b_m260_20mm")
int write_topdf(const char* output_file_name = "ResoVspt_VxVy5_1.7_1.7_2.5ExBr_2.5BrEC80mm_2")
{

	char out_file_open[1023];
        sprintf(out_file_open,"%s/%s.pdf(",out_path,output_file_name);
        char out_file_[1023];
        sprintf(out_file_,"%s/%s.pdf",out_path,output_file_name);
        char out_file_close[1023];
        sprintf(out_file_close,"%s/%s.pdf)",out_path,output_file_name);
	gStyle->SetErrorX(0.); 
	//! Ext Barrel eta < 1.7
	TFile* f = TFile::Open("./plots/ResoVspt_VxVy5_ggFhh4bPU1k_30mm_eta1.7_1.root");
	TH1D* h_dp 	= (TH1D*)f->Get("h_sigmadp");
	TH1D* h_invpt 	= (TH1D*)f->Get("h_sigma_invPt");
	TH1D* h_phi	= (TH1D*)f->Get("h_sigma_phi");
	TH1D* h_theta	= (TH1D*)f->Get("h_sigma_theta");
	TH1D* h_eta	= (TH1D*)f->Get("h_sigma_eta");
	TH1D* h_z0	= (TH1D*)f->Get("h_sigma_z0");
	TH1D* h_dca	= (TH1D*)f->Get("h_sigma_dca");

	//! Ext Barrel eta > 1.7 and eta < 2.5 
	TFile* f0 = TFile::Open("./plots/ResoVspt_VxVy5_ggFhh4bPU1k_30mm_eta1.7_2.5_1.root");
	//TFile* f0 = TFile::Open("./plots/ResoVspt_VxVy5_ggFhh4bPU1k_30mmEC67mm_eta1.7_2.0_1.root");
	TH1D* h0_dp 	= (TH1D*)f0->Get("h_sigmadp");
	TH1D* h0_invpt 	= (TH1D*)f0->Get("h_sigma_invPt");
	TH1D* h0_phi	= (TH1D*)f0->Get("h_sigma_phi");
	TH1D* h0_theta	= (TH1D*)f0->Get("h_sigma_theta");
	TH1D* h0_eta	= (TH1D*)f0->Get("h_sigma_eta");
	TH1D* h0_z0	= (TH1D*)f0->Get("h_sigma_z0");
	TH1D* h0_dca	= (TH1D*)f0->Get("h_sigma_dca");

	//! Barrel Endcap eta > 1.7 and eta < 2.5 
	//TFile* f1 = TFile::Open("./plots/ResoVspt_VxVy5_ggFhh4bPU1k_30mmEC80mm_eta1.7_2.5_2.root");
	TFile* f1 = TFile::Open("../../plots/ResoVspt_VxVy5_ggFhh4bPU1k_30mmEC80mm_eta1.7_2.5_2.root");
	TH1D* h1_dp 	= (TH1D*)f1->Get("h_sigmadp");
	TH1D* h1_invpt 	= (TH1D*)f1->Get("h_sigma_invPt");
	TH1D* h1_phi	= (TH1D*)f1->Get("h_sigma_phi");
	TH1D* h1_theta	= (TH1D*)f1->Get("h_sigma_theta");
	TH1D* h1_eta	= (TH1D*)f1->Get("h_sigma_eta");
	TH1D* h1_z0	= (TH1D*)f1->Get("h_sigma_z0");
	TH1D* h1_dca	= (TH1D*)f1->Get("h_sigma_dca");

	TGaxis::SetMaxDigits(3);
	gStyle->SetOptTitle(0);
	h_dp->SetStats(0);
	h_invpt->SetStats(0);
       	h_phi->SetStats(0);
       	h_theta->SetStats(0);
       	h_eta->SetStats(0);
       	h_z0->SetStats(0);
       	h_dca->SetStats(0);
       
	h0_dp->SetStats(0);
        h0_invpt->SetStats(0);
        h0_phi->SetStats(0);
        h0_theta->SetStats(0);
        h0_eta->SetStats(0);
        h0_z0->SetStats(0);
        h0_dca->SetStats(0);
	
	h1_dp->SetStats(0);
        h1_invpt->SetStats(0);
        h1_phi->SetStats(0);
        h1_theta->SetStats(0);
        h1_eta->SetStats(0);
        h1_z0->SetStats(0);
        h1_dca->SetStats(0);
 	
	// SET Markercolour
	h_dp->SetMarkerColor(kRed);
	h_invpt->SetMarkerColor(kRed);
	h_phi->SetMarkerColor(kRed);
	h_theta->SetMarkerColor(kRed);
	h_eta->SetMarkerColor(kRed);
	h_z0->SetMarkerColor(kRed);
	h_dca->SetMarkerColor(kRed);

	h0_dp->SetMarkerColor(kRed);
        h0_invpt->SetMarkerColor(kRed);
        h0_phi->SetMarkerColor(kRed);
        h0_theta->SetMarkerColor(kRed);
        h0_eta->SetMarkerColor(kRed);
        h0_z0->SetMarkerColor(kRed);
        h0_dca->SetMarkerColor(kRed);
	
	h1_dp->SetMarkerColor(kRed);
        h1_invpt->SetMarkerColor(kRed);
        h1_phi->SetMarkerColor(kRed);
        h1_theta->SetMarkerColor(kRed);
        h1_eta->SetMarkerColor(kRed);
        h1_z0->SetMarkerColor(kRed);
        h1_dca->SetMarkerColor(kRed);
	
	//Marker Size	
	h_dp->SetMarkerSize(MARKER_SIZE);
	h_invpt->SetMarkerSize(MARKER_SIZE);
	h_phi->SetMarkerSize(MARKER_SIZE);
	h_theta->SetMarkerSize(MARKER_SIZE);
	h_eta->SetMarkerSize(MARKER_SIZE);
	h_z0->SetMarkerSize(MARKER_SIZE);
	h_dca->SetMarkerSize(MARKER_SIZE);

	h0_dp->SetMarkerSize(MARKER_SIZE);
        h0_invpt->SetMarkerSize(MARKER_SIZE);
        h0_phi->SetMarkerSize(MARKER_SIZE);
        h0_theta->SetMarkerSize(MARKER_SIZE);
        h0_eta->SetMarkerSize(MARKER_SIZE);
        h0_z0->SetMarkerSize(MARKER_SIZE);
        h0_dca->SetMarkerSize(MARKER_SIZE);
	
	h1_dp->SetMarkerSize(MARKER_SIZE);
        h1_invpt->SetMarkerSize(MARKER_SIZE);
        h1_phi->SetMarkerSize(MARKER_SIZE);
        h1_theta->SetMarkerSize(MARKER_SIZE);
        h1_eta->SetMarkerSize(MARKER_SIZE);
        h1_z0->SetMarkerSize(MARKER_SIZE);
        h1_dca->SetMarkerSize(MARKER_SIZE);

	//Marker Style	
	h_dp->SetMarkerStyle(kOpenCircle);
	h_invpt->SetMarkerStyle(kOpenCircle);
	h_phi->SetMarkerStyle(kOpenCircle);
	h_theta->SetMarkerStyle(kOpenCircle);
	h_eta->SetMarkerStyle(kOpenCircle);
	h_z0->SetMarkerStyle(kOpenCircle);
	h_dca->SetMarkerStyle(kOpenCircle);

	h0_dp->SetMarkerStyle(kOpenTriangleDown);
        h0_invpt->SetMarkerStyle(kOpenTriangleDown);
        h0_phi->SetMarkerStyle(kOpenTriangleDown);
        h0_theta->SetMarkerStyle(kOpenTriangleDown);
        h0_eta->SetMarkerStyle(kOpenTriangleDown);
        h0_z0->SetMarkerStyle(kOpenTriangleDown);
        h0_dca->SetMarkerStyle(kOpenTriangleDown);
	
	h1_dp->SetMarkerStyle(kFullTriangleDown);
        h1_invpt->SetMarkerStyle(kFullTriangleDown);
        h1_phi->SetMarkerStyle(kFullTriangleDown);
        h1_theta->SetMarkerStyle(kFullTriangleDown);
        h1_eta->SetMarkerStyle(kFullTriangleDown);
        h1_z0->SetMarkerStyle(kFullTriangleDown);
        h1_dca->SetMarkerStyle(kFullTriangleDown);
	
	//Label Font
	h_dp->GetXaxis()->SetLabelFont(62);
	h_invpt->GetXaxis()->SetLabelFont(62);
	h_phi->GetXaxis()->SetLabelFont(62);
	h_theta->GetXaxis()->SetLabelFont(62);
	h_eta->GetXaxis()->SetLabelFont(62);
	h_z0->GetXaxis()->SetLabelFont(62);
	h_dca->GetXaxis()->SetLabelFont(62);

	h0_dp->GetXaxis()->SetLabelFont(62);
        h0_invpt->GetXaxis()->SetLabelFont(62);
        h0_phi->GetXaxis()->SetLabelFont(62);
        h0_theta->GetXaxis()->SetLabelFont(62);
        h0_eta->GetXaxis()->SetLabelFont(62);
        h0_z0->GetXaxis()->SetLabelFont(62);
        h0_dca->GetXaxis()->SetLabelFont(62);
	
	h1_dp->GetXaxis()->SetLabelFont(62);
        h1_invpt->GetXaxis()->SetLabelFont(62);
        h1_phi->GetXaxis()->SetLabelFont(62);
        h1_theta->GetXaxis()->SetLabelFont(62);
        h1_eta->GetXaxis()->SetLabelFont(62);
        h1_z0->GetXaxis()->SetLabelFont(62);
        h1_dca->GetXaxis()->SetLabelFont(62);
	//       
	h_dp->GetYaxis()->SetLabelFont(62);
	h_invpt->GetYaxis()->SetLabelFont(62);
	h_phi->GetYaxis()->SetLabelFont(62);
	h_theta->GetYaxis()->SetLabelFont(62);
	h_eta->GetYaxis()->SetLabelFont(62);
	h_z0->GetYaxis()->SetLabelFont(62);
	h_dca->GetYaxis()->SetLabelFont(62);

	h0_dp->GetYaxis()->SetLabelFont(62);
        h0_invpt->GetYaxis()->SetLabelFont(62);
        h0_phi->GetYaxis()->SetLabelFont(62);
        h0_theta->GetYaxis()->SetLabelFont(62);
        h0_eta->GetYaxis()->SetLabelFont(62);
        h0_z0->GetYaxis()->SetLabelFont(62);
        h0_dca->GetYaxis()->SetLabelFont(62);
	
	h1_dp->GetYaxis()->SetLabelFont(62);
        h1_invpt->GetYaxis()->SetLabelFont(62);
        h1_phi->GetYaxis()->SetLabelFont(62);
        h1_theta->GetYaxis()->SetLabelFont(62);
        h1_eta->GetYaxis()->SetLabelFont(62);
        h1_z0->GetYaxis()->SetLabelFont(62);
        h1_dca->GetYaxis()->SetLabelFont(62);
	
	//h_dp->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);
	//h_invpt->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);
	//h_phi->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);
	//h_theta->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);
	//h_eta->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);
	//h_z0->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);
//	//h_dca->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);

	h0_dp->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
        h0_invpt->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
        h0_phi->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
        h0_theta->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
        h0_eta->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
        h0_z0->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
        h0_dca->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	
	h0_dp->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);
        h0_invpt->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);
        h0_phi->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);
        h0_theta->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);
        h0_eta->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);
        h0_z0->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);
        h0_dca->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);
	//h_dp->GetYaxis()->CenterTitle();
	//h_invpt->GetYaxis()->CenterTitle();
	//h_phi->GetYaxis()->CenterTitle();
	//h_theta->GetYaxis()->CenterTitle();
	//h_eta->GetYaxis()->CenterTitle();
	//h_z0->GetYaxis()->CenterTitle();
//	//h_dca->GetYaxis()->CenterTitle();

	h0_dp->GetXaxis()->CenterTitle();
        h0_invpt->GetXaxis()->CenterTitle();
        h0_phi->GetXaxis()->CenterTitle();
        h0_theta->GetXaxis()->CenterTitle();
        h0_eta->GetXaxis()->CenterTitle();
        h0_z0->GetXaxis()->CenterTitle();
        h0_dca->GetXaxis()->CenterTitle();
	
	h0_dp->GetYaxis()->CenterTitle();
        h0_invpt->GetYaxis()->CenterTitle();
        h0_phi->GetYaxis()->CenterTitle();
        h0_theta->GetYaxis()->CenterTitle();
        h0_eta->GetYaxis()->CenterTitle();
        h0_z0->GetYaxis()->CenterTitle();
        h0_dca->GetYaxis()->CenterTitle();
	
	//h_dp->GetYaxis()->SetTitleSize(TITLE_SIZE);
	//h_invpt->GetYaxis()->SetTitleSize(TITLE_SIZE);
	//h_phi->GetYaxis()->SetTitleSize(TITLE_SIZE);
	//h_theta->GetYaxis()->SetTitleSize(TITLE_SIZE);
	//h_eta->GetYaxis()->SetTitleSize(TITLE_SIZE);
	//h_z0->GetYaxis()->SetTitleSize(TITLE_SIZE);
//	//h_dca->GetYaxis()->SetTitleSize(TITLE_SIZE);

	h0_dp->GetYaxis()->SetTitleSize(TITLE_SIZE);
        h0_invpt->GetYaxis()->SetTitleSize(TITLE_SIZE);
        h0_phi->GetYaxis()->SetTitleSize(TITLE_SIZE);
        h0_theta->GetYaxis()->SetTitleSize(TITLE_SIZE);
        h0_eta->GetYaxis()->SetTitleSize(TITLE_SIZE);
        h0_z0->GetYaxis()->SetTitleSize(TITLE_SIZE);
        h0_dca->GetYaxis()->SetTitleSize(TITLE_SIZE);

	//h_dp->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	//h_invpt->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	//h_phi->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	//h_theta->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	//h_eta->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	//h_z0->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
//	//h_dca->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);

	h0_dp->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
        h0_invpt->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
        h0_phi->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
        h0_theta->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
        h0_eta->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
        h0_z0->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
        h0_dca->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	

	//h_dp->GetXaxis()->SetTitleSize(TITLE_SIZE);
	//h_invpt->GetXaxis()->SetTitleSize(TITLE_SIZE);
	//h_phi->GetXaxis()->SetTitleSize(TITLE_SIZE);
	//h_theta->GetXaxis()->SetTitleSize(TITLE_SIZE);
	//h_eta->GetXaxis()->SetTitleSize(TITLE_SIZE);
	//h_z0->GetXaxis()->SetTitleSize(TITLE_SIZE);
//	//h_dca->GetXaxis()->SetTitleSize(TITLE_SIZE);

	h0_dp->GetXaxis()->SetTitleSize(TITLE_SIZE);
        h0_invpt->GetXaxis()->SetTitleSize(TITLE_SIZE);
        h0_phi->GetXaxis()->SetTitleSize(TITLE_SIZE);
        h0_theta->GetXaxis()->SetTitleSize(TITLE_SIZE);
        h0_eta->GetXaxis()->SetTitleSize(TITLE_SIZE);
        h0_z0->GetXaxis()->SetTitleSize(TITLE_SIZE);
        h0_dca->GetXaxis()->SetTitleSize(TITLE_SIZE);	
	//h_invpt->GetYaxis()->SetTitle("#sigma_{#Delta(1/p_{t})} [GeV/c]^{-1}");
 
	h0_dp->GetYaxis()->SetTitle("#sigma_{#delta p_{T}/p_{T}} [%]");
        h0_invpt->GetYaxis()->SetTitle("#sigma_{#delta(1/p_{T})} [GeV/c]^{-1}");
        h0_phi->GetYaxis()->SetTitle("#sigma_{#delta#phi} [mrad]");
        h0_theta->GetYaxis()->SetTitle("#sigma_{#delta#theta} [mrad]");
        h0_eta->GetYaxis()->SetTitle("#sigma_{#delta#eta}");
        h0_z0->GetYaxis()->SetTitle("#sigma_{#deltaz_0} [mm]");
        h0_dca->GetYaxis()->SetTitle("#sigma_{#deltadca} [mm]");
//        h0_dca->GetYaxis()->SetTitle("P_{t_gen} [GeV/c]");       h0_invpt->GetYaxis()->SetTitle("#sigma_{#Delta(1/p_{t})} [GeV/c]^{-1}");
	//
	//h_dp->GetXaxis()->SetTitle("p_{t_gen} [GeV/c]");
	//h_invpt->GetXaxis()->SetTitle("p_{t_gen} [GeV/c]");
	//h_phi->GetXaxis()->SetTitle("p_{t_gen} [GeV/c]");
	//h_theta->GetXaxis()->SetTitle("p_{t_gen} [GeV/c]");
	//h_eta->GetXaxis()->SetTitle("p_{t_gen} [GeV/c]");
	//h_z0->GetXaxis()->SetTitle("p_{t_gen} [GeV/c]");
//	//h_dca->GetXaxis()->SetTitle("P_{t_gen} [GeV/c]");

	h0_dp->GetXaxis()->SetTitle("p_{T} [GeV/c]");
        h0_invpt->GetXaxis()->SetTitle("p_{T} [GeV/c]");
        h0_phi->GetXaxis()->SetTitle("p_{T} [GeV/c]");
        h0_theta->GetXaxis()->SetTitle("p_{T} [GeV/c]");
        h0_eta->GetXaxis()->SetTitle("p_{T} [GeV/c]");
        h0_z0->GetXaxis()->SetTitle("p_{T} [GeV/c]");
        h0_dca->GetXaxis()->SetTitle("p_{T} [GeV/c]");

	h_phi->Scale(1.0e3);
	h_theta->Scale(1.0e3);
	h0_phi->Scale(1.0e3);
	h0_theta->Scale(1.0e3);
	h1_phi->Scale(1.0e3);
	h1_theta->Scale(1.0e3);
	
	h0_phi->GetYaxis()->SetRangeUser(0,1.5);
	h0_theta->GetYaxis()->SetRangeUser(0,1.5);
	////h_invpt->Scale(1.0e3);
        //h0_invpt->Scale(1.0e3);
	////h_invpt->GetYaxis()->SetRangeUser(0,8e-3);
	//h0_invpt->GetYaxis()->SetRangeUser(0,8e-3);
	//////ScaleYaxis(h_invpt,1.0e3);
        //////ScaleYaxis(h0_invpt,1.0e3);
	////ScaleXaxis(h_invpt,1.0e-3);
        //ScaleXaxis(h0_invpt,1.0e-3);
	////ScaleXaxis(h_dp,1e-3);
	////ScaleXaxis(h_phi,1e-3);
	////ScaleXaxis(h_theta,1e-3);
	////ScaleXaxis(h_eta,1e-3);
	////ScaleXaxis(h_z0,1e-3);
	//ScaleXaxis(h0_dp,1e-3);
        //ScaleXaxis(h0_phi,1e-3);
        //ScaleXaxis(h0_theta,1e-3);
        //ScaleXaxis(h0_eta,1e-3);
        //ScaleXaxis(h0_z0,1e-3);
	
	TCanvas *C = new TCanvas("C","C", 800, 800);
	gStyle->SetOptStat(0);
	
	Legends();
	Double_t x1= 0.25,y1= 0.35, x2 = 0.9, y2 = 0.55;
	TLegend *leg_1=new TLegend(x1,y1,x2,y2,"");
	leg_1->SetFillStyle(FILL_STYLE);
	leg_1->SetBorderSize(BORDER_SIZE);
	leg_1->SetTextSize(TEXT_SIZE);
        leg_1->AddEntry(h_dp,"Central Barrel (#eta < 1.7)");
        leg_1->AddEntry(h0_dp,"Forward Barrel (1.7 < #eta < 2.5)");
        leg_1->AddEntry(h1_dp,"Endcap (1.7 < #eta < 2.5)");
        leg_1->Draw();
	C->Print(out_file_open,"pdf");
	C->SaveAs("./tex/leg.tex");

	//C->SetGridx();
	//C->SetGridy();
	//C->SetTickx();
	//C->SetTicky();
	h1_dp->GetXaxis()->CenterTitle();
	h1_dp->GetYaxis()->CenterTitle();
	h1_dp->GetYaxis()->SetRangeUser(0,10);
	h1_dp->Draw();
	h_dp->Draw("same");
	////C->SetLogx();
	//C->Print(out_file_open, "pdf");
	h0_dp->Draw("same");
	leg1->Draw();
	leg2->Draw();
	//leg5->Draw();
	C->Print(out_file_,"pdf");
	C->SaveAs("./tex/reso_dpt.tex");

	//h1_invpt->GetXaxis()->SetRangeUser(0, 60);
	h1_invpt->GetXaxis()->CenterTitle();
	h1_invpt->GetYaxis()->CenterTitle();
	h1_invpt->Draw();
	h_invpt->Draw("same");
	//C->Print(out_file_, "pdf");
	h0_invpt->Draw("same");
	leg1->Draw();
	leg2->Draw();
	//leg5->Draw();
        //leg_1->Draw();
	C->Print(out_file_,"pdf");
	C->SaveAs("./tex/reso_invpt.tex");
	
	h0_phi->GetXaxis()->CenterTitle();
	h0_phi->GetYaxis()->CenterTitle();
	h0_phi->Draw();
	h1_phi->Draw("same");
	h_phi->Draw("same");
	//C->Print(out_file_, "pdf");
	leg1->Draw();
	leg2->Draw();
	//leg5->Draw();
        //leg_1->Draw();
	C->Print(out_file_,"pdf");
	C->SaveAs("./tex/reso_phi.tex");

	h0_theta->GetXaxis()->CenterTitle();
	h0_theta->GetYaxis()->CenterTitle();
	h0_theta->Draw();
	h1_theta->Draw("same");
	h_theta->Draw("same");
	//C->Print(out_file_, "pdf");
	leg1->Draw();
	leg2->Draw();
	//leg5->Draw();
        //leg_1->Draw();
	C->Print(out_file_,"pdf");
	C->SaveAs("./tex/reso_theta.tex");
	
	h0_eta->GetXaxis()->CenterTitle();
	h0_eta->GetYaxis()->CenterTitle();
	h0_eta->Draw();
	h1_eta->Draw("same");
	h_eta->Draw("same");
	//C->Print(out_file_, "pdf");
	leg1->Draw();
	leg2->Draw();
	//leg5->Draw();
        //leg_1->Draw();
	C->Print(out_file_,"pdf");
	C->SaveAs("./tex/reso_eta.tex");
	
	h0_z0->GetXaxis()->CenterTitle();
	h0_z0->GetYaxis()->CenterTitle();
	h0_z0->Draw();
	h1_z0->Draw("same");
	h_z0->Draw("same");
	//C->Print(out_file_, "pdf");
	leg1->Draw();
	leg2->Draw();
	//leg5->Draw();
        //leg_1->Draw();
	C->Print(out_file_,"pdf");
	C->SaveAs("./tex/reso_z0.tex");
	
	h1_dca->Draw();
	h_dca->Draw("same");
	//C->Print(out_file_, "pdf");
	h0_dca->Draw("same");
	leg1->Draw();
	leg2->Draw();
	//leg5->Draw();
        //leg_1->Draw();
	C->SaveAs("./tex/reso_dca.tex");
	//C->Print(out_file_,"pdf");
	

	//plot same
	
	//Double_t x1= 0.7,y1= 0.75, x2 = 0.9, y2 = 0.9;
	//h_dp->GetYaxis()->SetRangeUser(0,0.35);
	//h_dp->Draw();
	//h0_dp->Draw("same");
	//TLegend *leg1=new TLegend(x1,y1,x2,y2,"");
	//leg1->SetFillColor(kWhite);
	//leg1->SetBorderSize(0);
        //leg1->AddEntry(h_dp,"ITK tracks");
        //leg1->AddEntry(h0_dp,"TTT tracks");
        //leg1->Draw();
	//C->Print(out_file_,"pdf");
	////h_invpt->GetYaxis()->SetRangeUser(0,8e-6);
	//h_invpt->Draw();
	//h0_invpt->Draw("same");
	//TLegend *leg2=new TLegend(x1,y1,x2,y2,"");
	//leg2->SetFillColor(kWhite);
	//leg2->SetBorderSize(0);
	//leg2->AddEntry(h_invpt,"ITK tracks");
	//leg2->AddEntry(h0_invpt,"TTT tracks");
	//leg2->Draw();
	//C->Print(out_file_,"pdf");

	//h_phi->GetYaxis()->SetRangeUser(0,0.0025);
	//h_phi->Draw();
	//h0_phi->Draw("same");
	//TLegend *leg3=new TLegend(x1,y1,x2,y2,"");
	//leg3->SetFillColor(kWhite);
	//leg3->SetBorderSize(0);
        //leg3->AddEntry(h_phi,"ITK tracks");
        //leg3->AddEntry(h0_phi,"TTT tracks");
        //leg3->Draw();
	//C->Print(out_file_,"pdf");
	//
	//h_theta->GetYaxis()->SetRangeUser(0,0.0025);
	//h_theta->Draw();
	//h0_theta->Draw("same");
	//TLegend *leg4=new TLegend(x1,y1,x2,y2,"");
	//leg4->SetFillColor(kWhite);
	//leg4->SetBorderSize(0);
        //leg4->AddEntry(h_theta,"ITK tracks");
        //leg4->AddEntry(h0_theta,"TTT tracks");
        //leg4->Draw();
	//C->Print(out_file_,"pdf");
	//
	//h_eta->GetYaxis()->SetRangeUser(0,0.0025);
	//h_eta->Draw();
	//h0_eta->Draw("same");
	//TLegend *leg5=new TLegend(x1,y1,x2,y2,"");
	//leg5->SetFillColor(kWhite);
	//leg5->SetBorderSize(0);
        //leg5->AddEntry(h_eta,"ITK tracks");
        //leg5->AddEntry(h0_eta,"TTT tracks");
        //leg5->Draw();
	//C->Print(out_file_,"pdf");
	//
	//h_z0->GetYaxis()->SetRangeUser(0.0,1.5);
	//h_z0->Draw();
	//h0_z0->Draw("same");
	//TLegend *leg6=new TLegend(x1,y1,x2,y2,"");
	//leg6->SetFillColor(kWhite);
	//leg6->SetBorderSize(0);
        //leg6->AddEntry(h_z0,"ITK tracks");
        //leg6->AddEntry(h0_z0,"TTT tracks");
        //leg6->Draw();
	//C->Print(out_file_,"pdf");
	//
	///*h_dca->GetYaxis()->SetRangeUser(10,40);
	//h_dca->Draw();
	//h0_dca->Draw("same");
	//TLegend *leg7=new TLegend(x1,y1,x2,y2,"");
        //leg7->AddEntry(h_dca,"ITK tracks");
        //leg7->AddEntry(h0_dca,"TTT tracks");
        //leg7->Draw();*/

	//
	////two scales eta phi
	//C->SetTicky(0);
	//h_phi->SetLineColor(kBlack);
	//h0_phi->SetLineColor(kBlack);
	//h_phi->SetMarkerColor(kBlack);
	//h0_phi->SetMarkerColor(kBlack);	
	//h_phi->Draw();
	//h0_phi->Draw("same");
	//C->Update();
	//Float_t rightmax = 1*h_eta->GetMaximum();
	//Float_t scale = gPad->GetUymax()/rightmax;
	//h_eta->SetLineColor(kBlue);
	//h0_eta->SetLineColor(kBlack);
	//h_eta->SetMarkerColor(kBlue);
	//h0_eta->SetMarkerColor(kBlue);
	//h_eta->Scale(scale);
	//h_eta->Draw("same");
	//h0_eta->Draw("same");
	////draw an axis on the right side
	//TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
	//gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
	//axis->SetLineColor(kBlue);
	//axis->SetLabelColor(kBlue);
//	//axis->SetLabelSize(0.05);
	//axis->SetTitle("#sigma_{#Delta(#eta)}");
	//axis->SetTitleColor(kBlue);
	//axis->SetTitleSize(TITLE_SIZE);
	//axis->SetTitleOffset(1.04);
	//axis->CenterTitle();
	//axis->Draw();
	//
	//C->Print(out_file_,"pdf");
	//C->Clear();
	//leg1->Draw();

	C->Print(out_file_close,"pdf");
	TCanvas *c1 = new TCanvas();
	h0_dp->Draw();
	TCanvas *c2 = new TCanvas();
	h0_invpt->Draw();
	TCanvas *c3 = new TCanvas();
	h0_z0->Draw();


return 0;
}

