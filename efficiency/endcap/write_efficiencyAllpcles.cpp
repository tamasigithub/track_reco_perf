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
TH1D* h1_pt 	= nullptr; 
TH1D* h1_phi	= nullptr; 
TH1D* h1_eta	= nullptr; 
TH1D* hpi_pt 	= nullptr; 
TH1D* hpi_phi	= nullptr; 
TH1D* hpi_eta	= nullptr; 
TH1D* he_pt 	= nullptr; 
TH1D* he_phi	= nullptr; 
TH1D* he_eta	= nullptr; 
TH1D* hmu_pt 	= nullptr; 
TH1D* hmu_phi	= nullptr; 
TH1D* hmu_eta	= nullptr; 
void CenterAxisTitles()
{

	h1_pt->GetYaxis()->CenterTitle();
	hpi_pt->GetYaxis()->CenterTitle();
	he_pt->GetYaxis()->CenterTitle();
	hmu_pt->GetYaxis()->CenterTitle();
	h1_pt->GetXaxis()->CenterTitle();
	hpi_pt->GetXaxis()->CenterTitle();
	he_pt->GetXaxis()->CenterTitle();
	hmu_pt->GetXaxis()->CenterTitle();

	h1_phi->GetYaxis()->CenterTitle();
	hpi_phi->GetYaxis()->CenterTitle();
	he_phi->GetYaxis()->CenterTitle();
	hmu_phi->GetYaxis()->CenterTitle();
	h1_phi->GetXaxis()->CenterTitle();
	hpi_phi->GetXaxis()->CenterTitle();
	he_phi->GetXaxis()->CenterTitle();
	hmu_phi->GetXaxis()->CenterTitle();
	
	h1_eta->GetYaxis()->CenterTitle();
	hpi_eta->GetYaxis()->CenterTitle();
	he_eta->GetYaxis()->CenterTitle();
	hmu_eta->GetYaxis()->CenterTitle();
	h1_eta->GetXaxis()->CenterTitle();
	hpi_eta->GetXaxis()->CenterTitle();
	he_eta->GetXaxis()->CenterTitle();
	hmu_eta->GetXaxis()->CenterTitle();
	
	h1_pt->SetMarkerStyle(kFullCircle);
	hpi_pt->SetMarkerStyle(kFullCircle);
	he_pt->SetMarkerStyle(kFullCircle);
	hmu_pt->SetMarkerStyle(kFullCircle);

	h1_phi->SetMarkerStyle(kFullCircle);
	hpi_phi->SetMarkerStyle(kFullCircle);
	he_phi->SetMarkerStyle(kFullCircle);
	hmu_phi->SetMarkerStyle(kFullCircle);
	
	h1_eta->SetMarkerStyle(kFullCircle);
	hpi_eta->SetMarkerStyle(kFullCircle);
	he_eta->SetMarkerStyle(kFullCircle);
	hmu_eta->SetMarkerStyle(kFullCircle);
	return;
}
const char* out_path = "./plots"; 
//int write_topdf(const char* output_file_name = "EffVsAll_ggF1.0hh4bPU1kOpt3allPcles_30mmEta1_7_1")
//int write_topdf(const char* output_file_name = "EffVsAll_ggF1.0hh4bPU1kOpt3allPcles_30mmEta2_5_2")
int write_topdf(const char* output_file_name = "PU1kallpcles_ggF1.0-eff_30mmEC106mm_opt5_3")
{

	char out_file_open[1023];
        sprintf(out_file_open,"%s/%s.pdf(",out_path,output_file_name);
        char out_file_[1023];
        sprintf(out_file_,"%s/%s.pdf",out_path,output_file_name);
        char out_file_close[1023];
        sprintf(out_file_close,"%s/%s.pdf)",out_path,output_file_name);
	
	//TFile* f1 = TFile::Open("~/repo_tamasi/rec_files/rec_files/plots/PU1kallpcles_ggF1.0-eff_30mm_eta1.7opt3_2GeV_1.root");
	//TFile* f1 = TFile::Open("~/repo_tamasi/rec_files/rec_files/plots/PU1kallpcles_ggF1.0-eff_30mm_eta2.5opt3_2GeV_2.root");
	TFile* f1 = TFile::Open("./plots/PU1kallpcles_ggF1.0-eff_30mmEC106mm_opt5_3.root");
	h1_pt 	= (TH1D*)f1->Get("h_eff_vs_ptPU");
	h1_phi	= (TH1D*)f1->Get("h_eff_vs_phiPU");
	h1_eta	= (TH1D*)f1->Get("h_eff_vs_etaPU");
	hpi_pt 	= (TH1D*)f1->Get("h_eff_vs_ptpi");
	hpi_phi	= (TH1D*)f1->Get("h_eff_vs_phipi");
	hpi_eta	= (TH1D*)f1->Get("h_eff_vs_etapi");
	he_pt 	= (TH1D*)f1->Get("h_eff_vs_pte");
	he_phi	= (TH1D*)f1->Get("h_eff_vs_phie");
	he_eta	= (TH1D*)f1->Get("h_eff_vs_etae");
	hmu_pt 	= (TH1D*)f1->Get("h_eff_vs_ptmu");
	hmu_phi	= (TH1D*)f1->Get("h_eff_vs_phimu");
	hmu_eta	= (TH1D*)f1->Get("h_eff_vs_etamu");

	TCanvas *C = new TCanvas("C","C",800,800);
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);

	Legends();

	ScaleXaxis(h1_pt, 1e-3);
	ScaleXaxis(hpi_pt,1e-3);
	ScaleXaxis(he_pt, 1e-3);
	ScaleXaxis(hmu_pt,1e-3);
	
	h1_pt->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	hpi_pt->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	he_pt->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	hmu_pt->GetXaxis()->SetTitle("p_{T} [GeV/c]");

	CenterAxisTitles();
	
	C->SetLogx();
	h1_pt->Draw();
	hpi_pt->Draw("same");
	he_pt->Draw("same");
	hmu_pt->Draw("same");

	TLegend *leg_1 = new TLegend(0.6,0.13,0.85,0.3);
	leg_1->SetFillStyle(FILL_STYLE);
	leg_1->SetBorderSize(BORDER_SIZE);
	leg_1->SetTextSize(TEXT_SIZE);
	leg_1->AddEntry(h1_pt,  "all particles");
	leg_1->AddEntry(he_pt,  "electrons");
	leg_1->AddEntry(hmu_pt, "muons");
	leg_1->AddEntry(hpi_pt, "pions");
	
	leg_1->Draw();
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	C->Print(out_file_open,"pdf");
	C->SaveAs("./tex/EffVspt30mmEta1_7.tex");

	C->SetLogx(0);
	h1_phi->Draw();
	hpi_phi->Draw("same");
	he_phi->Draw("same");
	hmu_phi->Draw("same");
	leg_1->Draw();
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	C->Print(out_file_,"pdf");
	C->SaveAs("./tex/EffVsphi30mmEta1_7.tex");
	
	C->SetLogx(0);
	h1_eta->Draw();
	hpi_eta->Draw("same");
	he_eta->Draw("same");
	hmu_eta->Draw("same");
	leg_1->Draw();
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	C->Print(out_file_close,"pdf");
	C->SaveAs("./tex/EffVseta30mmEta1_7.tex");
	return 0;
}

