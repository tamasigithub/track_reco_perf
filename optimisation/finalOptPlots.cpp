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

//const char *reco_files = "/home/tamasi/repo_tamasi/rec_files/for_optimization/30mm/ggFhh4b_SM/*.root";
const char *reco_files = "/user/tkar/work/data/rec/for_opt/ggF1.0/user.tkar_0000*.root";

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

TCut cut1 = "Tid >= -1 && Pt_n < 20e3";

void finalOptPlots()
{

	//int num_events = 2;
	TChain rec("m_recTree");
	rec.Add(reco_files);
	//TFile *f__ = new TFile("/home/tamasi/repo_tamasi/rec_files/for_optimization/30mm/ggFhh4b_SM/user.tkar.20161856._000001.recTree.root","READ");
	//TTree *rec = (TTree*)f__->Get("m_recTree");

	TCanvas *c = new TCanvas("c","c", 800., 800.);
	//c->SetLeftMargin(LEFT_MARGIN);

	Legends();
	gStyle->SetOptStat(0);	
	gStyle->SetOptTitle(0);	

	//! Books histograms
        TH1::SetDefaultSumw2(true);

	TH2F* h1 = new TH2F("h1","p_{T, rec} Vs #phi_{13};#phi_{13};p_{T, rec} [GeV/c]", 300,-0.04,0.04,300,1,25); 	

	//! phi13
	//rec.Draw("Pt_n*1e-3:Phi13>>h1", cut1,"", num_events);
	rec.Draw("Pt_n*1e-3:Phi13>>h1", cut1);
	h1->GetXaxis()->CenterTitle();
	h1->GetYaxis()->CenterTitle();
	h1->GetXaxis()->SetTitleSize(TITLE_SIZE);
	h1->GetYaxis()->SetTitleSize(TITLE_SIZE);
	h1->Draw();
	leg1->Draw();
	leg2->Draw();
	c->SaveAs("./tex/phi13.tex");
	c->SaveAs("./pdf/phi13.pdf");
	
	//TH2F* h2 = new TH2F("h2","p_{T, rec} Vs z_{13};z_{13} [mm];p_{T, rec} [GeV/c];", 300,-500,500,300,1,25); 		
	TH2F* h2 = new TH2F("h2","|#eta_{013}| Vs z_{13};z_{13} [mm];|#eta_{013}|;", 300,-500,500,300,0,3); 		
	//! Z13
	//rec.Draw("Pt_n*1e-3:Z13>>h2", cut1, "", num_events);
	rec.Draw("abs(Eta13):Z13>>h2", cut1);
	h2->GetXaxis()->CenterTitle();
	h2->GetYaxis()->CenterTitle();
	h2->GetXaxis()->SetTitleSize(TITLE_SIZE);
	h2->GetYaxis()->SetTitleSize(TITLE_SIZE);
	h2->Draw();
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	c->SaveAs("./tex/z13_eta.tex");
	c->SaveAs("./pdf/z13_eta.pdf");

	//! dphi2
	TFile *f = new TFile("./plots/optimisation/control_30mm_ggF_1.root","READ");
	TH2F *H24 = (TH2F*)f->Get("h24");
	TH2F *H25 = (TH2F*)f->Get("h25");
	H24->GetXaxis()->CenterTitle();
	H24->GetYaxis()->CenterTitle();
	H24->GetXaxis()->SetTitle("sin(#theta_{13})");
	H24->GetYaxis()->SetTitle("|d#phi_{2}|");
	H24->GetXaxis()->SetTitleSize(TITLE_SIZE);
	H24->GetYaxis()->SetTitleSize(TITLE_SIZE);
	H24->SetLineWidth(LINE_WIDTH);
	H25->SetLineWidth(LINE_WIDTH);
	H24->SetMarkerStyle(MARKER_STYLE);
	H25->SetMarkerStyle(MARKER_STYLE);
	H24->Draw();
	c->Update();
	H25->Draw("same");
	leg1->Draw();
	TLegend *leg = new TLegend(Xr1+0.22, Yu1-0.23, Xr2,Yu1-0.11);
	leg->AddEntry(H24,"fakes","l");
	leg->AddEntry(H25,"matched","l");
	leg->SetTextAlign(kHAlignCenter+kVAlignCenter);
	//leg->SetFillStyle(FILL_STYLE);
	leg->SetBorderSize(BORDER_SIZE);
	leg->SetTextSize(TEXT_SIZE);
	leg->Draw();
	//leg3->Draw();
	leg2->Draw();
	c->SaveAs("./pdf/dphi2.root");
	c->SaveAs("./tex/dphi2.tex");
	c->SaveAs("./pdf/dphi2.pdf");
	
	//! dz2
	TH2F *H27 = (TH2F*)f->Get("h27");
	TH2F *H28 = (TH2F*)f->Get("h28");
	TF1 *fun  = (TF1*)f->Get("fdz2");
	TF1 *fun_ = (TF1*)f->Get("fdz2_");
	H27->GetXaxis()->CenterTitle();
	H27->GetYaxis()->CenterTitle();
	H27->GetXaxis()->SetTitle("sin(#theta_{13})");
	H27->GetYaxis()->SetTitle("dz_{2} [mm]");
	H27->GetXaxis()->SetTitleSize(TITLE_SIZE);
	H27->GetYaxis()->SetTitleSize(TITLE_SIZE);
	H27->GetYaxis()->SetTitleOffset(1.1);
	H27->SetLineWidth(LINE_WIDTH);
	H28->SetLineWidth(LINE_WIDTH);
	H27->SetMarkerStyle(MARKER_STYLE);
	H28->SetMarkerStyle(MARKER_STYLE);
	H27->Draw();
	c->Update();
	H28->Draw("same");
	fun->Draw("same");
	fun_->Draw("same");
	leg1->Draw();
	leg->Draw();
	//leg3->Draw();
	leg2->Draw();
	c->SaveAs("./tex/dz2.tex");
	c->SaveAs("./pdf/dz2.pdf");
	c->SaveAs("./pdf/dz2.root");
	
	//! kappa_013 Vs kappa_123
	TH2F *H128 = (TH2F*)f->Get("h128");
	H128->GetXaxis()->CenterTitle();
	H128->GetYaxis()->CenterTitle();
	H128->GetXaxis()->SetTitle("#kappa_{123} [mm^{-1}]");
	H128->GetYaxis()->SetTitle("#kappa_{013} [mm^{-1}]");
	H128->GetXaxis()->SetTitleSize(TITLE_SIZE);
	H128->GetYaxis()->SetTitleSize(TITLE_SIZE);
	H128->GetYaxis()->SetTitleOffset(1.1);
	H128->GetXaxis()->SetMaxDigits(3);
	H128->SetLineWidth(LINE_WIDTH);
	H128->SetMarkerStyle(MARKER_STYLE);
	H128->Draw();
	c->Update();
	leg1->Draw();
	leg3->Draw();
	leg2->Draw();
	c->SaveAs("./tex/kappa123Vs013_all.tex");
	c->SaveAs("./pdf/kappa123Vs013_all.pdf");
	//! kappa_013 Vs kappa_123
	TH2F *H129 = (TH2F*)f->Get("h129");
	H129->GetXaxis()->CenterTitle();
	H129->GetYaxis()->CenterTitle();
	H129->GetXaxis()->SetTitle("#kappa_{123} [mm^{-1}]");
	H129->GetYaxis()->SetTitle("#kappa_{013} [mm^{-1}]");
	H129->GetXaxis()->SetTitleSize(TITLE_SIZE);
	H129->GetYaxis()->SetTitleSize(TITLE_SIZE);
	H129->GetYaxis()->SetTitleOffset(1.1);
	H129->GetXaxis()->SetMaxDigits(3);
	H129->SetLineWidth(LINE_WIDTH);
	H129->SetMarkerStyle(MARKER_STYLE);
	H129->Draw();
	c->Update();
	leg1->Draw();
	leg3->Draw();
	leg2->Draw();
	c->SaveAs("./tex/kappa123Vs013_pi.tex");
	c->SaveAs("./pdf/kappa123Vs013_pi.pdf");
	//! kappa_013 Vs kappa_123
	TH2F *H130 = (TH2F*)f->Get("h130");
	H130->GetXaxis()->CenterTitle();
	H130->GetYaxis()->CenterTitle();
	H130->GetXaxis()->SetTitle("#kappa_{123} [mm^{-1}]");
	H130->GetYaxis()->SetTitle("#kappa_{013} [mm^{-1}]");
	H130->GetXaxis()->SetTitleSize(TITLE_SIZE);
	H130->GetYaxis()->SetTitleSize(TITLE_SIZE);
	H130->GetYaxis()->SetTitleOffset(1.1);
	H130->GetXaxis()->SetMaxDigits(3);
	H130->SetLineWidth(LINE_WIDTH);
	H130->SetMarkerStyle(MARKER_STYLE);
	H130->Draw();
	c->Update();
	leg1->Draw();
	leg3->Draw();
	leg2->Draw();
	c->SaveAs("./tex/kappa123Vs013_e.tex");
	c->SaveAs("./pdf/kappa123Vs013_e.pdf");
	//! kappa_013 Vs kappa_123
	TH2F *H131 = (TH2F*)f->Get("h131");
	H131->GetXaxis()->CenterTitle();
	H131->GetYaxis()->CenterTitle();
	H131->GetXaxis()->SetTitle("#kappa_{123} [mm^{-1}]");
	H131->GetYaxis()->SetTitle("#kappa_{013} [mm^{-1}]");
	H131->GetXaxis()->SetTitleSize(TITLE_SIZE);
	H131->GetYaxis()->SetTitleSize(TITLE_SIZE);
	H131->GetYaxis()->SetTitleOffset(1.1);
	H131->GetXaxis()->SetMaxDigits(3);
	H131->SetLineWidth(LINE_WIDTH);
	H131->SetMarkerStyle(MARKER_STYLE);
	H131->Draw();
	c->Update();
	leg1->Draw();
	leg3->Draw();
	leg2->Draw();
	c->SaveAs("./tex/kappa123Vs013_mu.tex");
	c->SaveAs("./pdf/kappa123Vs013_mu.pdf");

	//! kappa_013/kappa_truth
	TH1F *H132 = (TH1F*)f->Get("h132");
	H132->GetXaxis()->CenterTitle();
	H132->GetYaxis()->CenterTitle();
	H132->GetXaxis()->SetTitle("#kappa_{013}/#kappa_{truth}");
	//H132->GetYaxis()->SetTitle("#kappa_{013}");
	H132->GetXaxis()->SetTitleSize(TITLE_SIZE);
	H132->GetYaxis()->SetTitleSize(TITLE_SIZE);
	H132->GetYaxis()->SetTitleOffset(1.1);
	H132->GetXaxis()->SetMaxDigits(3);
	H132->SetLineWidth(LINE_WIDTH);
	H132->SetMarkerStyle(MARKER_STYLE);
	H132->Draw();
	c->Update();
	leg1->Draw();
	leg3->Draw();
	leg2->Draw();
	c->SetLogy();
	c->SaveAs("./tex/ratiokappa013truth_all.tex");
	c->SaveAs("./pdf/ratiokappa013truth_all.pdf");
	//! kappa_013/kappa_truth
	TH1F *H133 = (TH1F*)f->Get("h133");
	H133->GetXaxis()->CenterTitle();
	H133->GetYaxis()->CenterTitle();
	H133->GetXaxis()->SetTitle("#kappa_{013}/#kappa_{truth}");
	//H133->GetYaxis()->SetTitle("#kappa_{013}");
	H133->GetXaxis()->SetTitleSize(TITLE_SIZE);
	H133->GetYaxis()->SetTitleSize(TITLE_SIZE);
	H133->GetYaxis()->SetTitleOffset(1.1);
	H133->GetXaxis()->SetMaxDigits(3);
	H133->SetLineWidth(LINE_WIDTH);
	H133->SetMarkerStyle(MARKER_STYLE);
	H133->Draw();
	c->Update();
	leg1->Draw();
	leg3->Draw();
	leg2->Draw();
	c->SetLogy();
	c->SaveAs("./tex/ratiokappa013truth_pi.tex");
	c->SaveAs("./pdf/ratiokappa013truth_pi.pdf");
	//! kappa_013/kappa_truth
	TH1F *H134 = (TH1F*)f->Get("h134");
	H134->GetXaxis()->CenterTitle();
	H134->GetYaxis()->CenterTitle();
	H134->GetXaxis()->SetTitle("#kappa_{013}/#kappa_{truth}");
	//H134->GetYaxis()->SetTitle("#kappa_{013}");
	H134->GetXaxis()->SetTitleSize(TITLE_SIZE);
	H134->GetYaxis()->SetTitleSize(TITLE_SIZE);
	H134->GetYaxis()->SetTitleOffset(1.1);
	H134->GetXaxis()->SetMaxDigits(3);
	H134->SetLineWidth(LINE_WIDTH);
	H134->SetMarkerStyle(MARKER_STYLE);
	H134->Draw();
	c->Update();
	leg1->Draw();
	leg3->Draw();
	leg2->Draw();
	c->SetLogy();
	c->SaveAs("./tex/ratiokappa013truth_e.tex");
	c->SaveAs("./pdf/ratiokappa013truth_e.pdf");
	//! kappa_013/kappa_truth
	TH1F *H135 = (TH1F*)f->Get("h135");
	H135->GetXaxis()->CenterTitle();
	H135->GetYaxis()->CenterTitle();
	H135->GetXaxis()->SetTitle("#kappa_{013}/#kappa_{truth}");
	//H135->GetYaxis()->SetTitle("#kappa_{013}");
	H135->GetXaxis()->SetTitleSize(TITLE_SIZE);
	H135->GetYaxis()->SetTitleSize(TITLE_SIZE);
	H135->GetYaxis()->SetTitleOffset(1.1);
	H135->GetXaxis()->SetMaxDigits(3);
	H135->SetLineWidth(LINE_WIDTH);
	H135->SetMarkerStyle(MARKER_STYLE);
	H135->Draw();
	c->Update();
	leg1->Draw();
	leg3->Draw();
	leg2->Draw();
	c->SetLogy();
	c->SaveAs("./tex/ratiokappa013truth_mu.tex");
	c->SaveAs("./pdf/ratiokappa013truth_mu.pdf");

	c->SetLogy(0);	
	//! dkappa Vs r = (hypot{M_vx, M_vy})
	TH2F *H140 = (TH2F*)f->Get("h140");
	H140->GetXaxis()->CenterTitle();
	H140->GetYaxis()->CenterTitle();
	H140->GetYaxis()->SetTitle("d#kappa [mm^{-1}]");
	H140->GetXaxis()->SetTitle("r [mm]");
	H140->GetXaxis()->SetTitleSize(TITLE_SIZE);
	H140->GetYaxis()->SetTitleSize(TITLE_SIZE);
	H140->GetYaxis()->SetTitleOffset(1.1);
	H140->GetXaxis()->SetMaxDigits(3);
	H140->SetLineWidth(LINE_WIDTH);
	H140->SetMarkerStyle(MARKER_STYLE);
	H140->Draw();
	c->Update();
	leg1->Draw();
	leg3->Draw();
	leg2->Draw();
	c->SaveAs("./tex/dkappaVsR_all.tex");
	c->SaveAs("./pdf/dkappaVsR_all.pdf");
	//! dkappa Vs r = (hypot{M_vx, M_vy})
	TH2F *H141 = (TH2F*)f->Get("h141");
	H141->GetXaxis()->CenterTitle();
	H141->GetYaxis()->CenterTitle();
	H141->GetYaxis()->SetTitle("d#kappa [mm^{-1}]");
	H141->GetXaxis()->SetTitle("r [mm]");
	H141->GetXaxis()->SetTitleSize(TITLE_SIZE);
	H141->GetYaxis()->SetTitleSize(TITLE_SIZE);
	H141->GetYaxis()->SetTitleOffset(1.1);
	H141->GetXaxis()->SetMaxDigits(3);
	H141->SetLineWidth(LINE_WIDTH);
	H141->SetMarkerStyle(MARKER_STYLE);
	H141->Draw();
	c->Update();
	leg1->Draw();
	leg3->Draw();
	leg2->Draw();
	c->SaveAs("./tex/dkappaVsR_pi.tex");
	c->SaveAs("./pdf/dkappaVsR_pi.pdf");
	//! dkappa Vs r = (hypot{M_vx, M_vy})
	TH2F *H142 = (TH2F*)f->Get("h142");
	H142->GetXaxis()->CenterTitle();
	H142->GetYaxis()->CenterTitle();
	H142->GetYaxis()->SetTitle("d#kappa [mm^{-1}]");
	H142->GetXaxis()->SetTitle("r [mm]");
	H142->GetXaxis()->SetTitleSize(TITLE_SIZE);
	H142->GetYaxis()->SetTitleSize(TITLE_SIZE);
	H142->GetYaxis()->SetTitleOffset(1.1);
	H142->GetXaxis()->SetMaxDigits(3);
	H142->SetLineWidth(LINE_WIDTH);
	H142->SetMarkerStyle(MARKER_STYLE);
	H142->Draw();
	c->Update();
	leg1->Draw();
	leg3->Draw();
	leg2->Draw();
	c->SaveAs("./tex/dkappaVsR_e.tex");
	c->SaveAs("./pdf/dkappaVsR_e.pdf");
	//! dkappa Vs r = (hypot{M_vx, M_vy})
	TH2F *H143 = (TH2F*)f->Get("h143");
	H143->GetXaxis()->CenterTitle();
	H143->GetYaxis()->CenterTitle();
	H143->GetYaxis()->SetTitle("d#kappa [mm^{-1}]");
	H143->GetXaxis()->SetTitle("r [mm]");
	H143->GetXaxis()->SetTitleSize(TITLE_SIZE);
	H143->GetYaxis()->SetTitleSize(TITLE_SIZE);
	H143->GetYaxis()->SetTitleOffset(1.1);
	H143->GetXaxis()->SetMaxDigits(3);
	H143->SetLineWidth(LINE_WIDTH);
	H143->SetMarkerStyle(MARKER_STYLE);
	H143->Draw();
	c->Update();
	leg1->Draw();
	leg3->Draw();
	leg2->Draw();
	c->SaveAs("./tex/dkappaVsR_mu.tex");
	c->SaveAs("./pdf/dkappaVsR_mu.pdf");

	//! kappa_013/kappa_truth Vs r = (hypot{M_vx, M_vy})
	TH2F *H144 = (TH2F*)f->Get("h144");
	H144->GetXaxis()->CenterTitle();
	H144->GetYaxis()->CenterTitle();
	H144->GetYaxis()->SetTitle("#kappa_{013}/#kappa_{truth}");
	H144->GetXaxis()->SetTitle("r [mm]");
	H144->GetXaxis()->SetTitleSize(TITLE_SIZE);
	H144->GetYaxis()->SetTitleSize(TITLE_SIZE);
	H144->GetYaxis()->SetTitleOffset(1.1);
	H144->GetXaxis()->SetMaxDigits(3);
	H144->SetLineWidth(LINE_WIDTH);
	H144->SetMarkerStyle(MARKER_STYLE);
	H144->Draw();
	c->Update();
	leg1->Draw();
	leg3->Draw();
	leg2->Draw();
	c->SaveAs("./tex/ratiokappa013truthVsR_all.tex");
	c->SaveAs("./pdf/ratiokappa013truthVsR_all.pdf");
	//! kappa_013/kappa_truth Vs r = (hypot{M_vx, M_vy})
	TH2F *H145 = (TH2F*)f->Get("h145");
	H145->GetXaxis()->CenterTitle();
	H145->GetYaxis()->CenterTitle();
	H145->GetYaxis()->SetTitle("#kappa_{013}/#kappa_{truth}");
	H145->GetXaxis()->SetTitle("r [mm]");
	H145->GetXaxis()->SetTitleSize(TITLE_SIZE);
	H145->GetYaxis()->SetTitleSize(TITLE_SIZE);
	H145->GetYaxis()->SetTitleOffset(1.1);
	H145->GetXaxis()->SetMaxDigits(3);
	H145->SetLineWidth(LINE_WIDTH);
	H145->SetMarkerStyle(MARKER_STYLE);
	H145->Draw();
	c->Update();
	leg1->Draw();
	leg3->Draw();
	leg2->Draw();
	c->SaveAs("./tex/ratiokappa013truthVsR_pi.tex");
	c->SaveAs("./pdf/ratiokappa013truthVsR_pi.pdf");
	//! kappa_013/kappa_truth Vs r = (hypot{M_vx, M_vy})
	TH2F *H146 = (TH2F*)f->Get("h146");
	H146->GetXaxis()->CenterTitle();
	H146->GetYaxis()->CenterTitle();
	H146->GetYaxis()->SetTitle("#kappa_{013}/#kappa_{truth}");
	H146->GetXaxis()->SetTitle("r [mm]");
	H146->GetXaxis()->SetTitleSize(TITLE_SIZE);
	H146->GetYaxis()->SetTitleSize(TITLE_SIZE);
	H146->GetYaxis()->SetTitleOffset(1.1);
	H146->GetXaxis()->SetMaxDigits(3);
	H146->SetLineWidth(LINE_WIDTH);
	H146->SetMarkerStyle(MARKER_STYLE);
	H146->Draw();
	c->Update();
	leg1->Draw();
	leg3->Draw();
	leg2->Draw();
	c->SaveAs("./tex/ratiokappa013truthVsR_e.tex");
	c->SaveAs("./pdf/ratiokappa013truthVsR_e.pdf");
	//! kappa_013/kappa_truth Vs r = (hypot{M_vx, M_vy})
	TH2F *H147 = (TH2F*)f->Get("h147");
	H147->GetXaxis()->CenterTitle();
	H147->GetYaxis()->CenterTitle();
	H147->GetYaxis()->SetTitle("#kappa_{013}/#kappa_{truth}");
	H147->GetXaxis()->SetTitle("r [mm]");
	H147->GetXaxis()->SetTitleSize(TITLE_SIZE);
	H147->GetYaxis()->SetTitleSize(TITLE_SIZE);
	H147->GetYaxis()->SetTitleOffset(1.1);
	H147->GetXaxis()->SetMaxDigits(3);
	H147->SetLineWidth(LINE_WIDTH);
	H147->SetMarkerStyle(MARKER_STYLE);
	H147->Draw();
	c->Update();
	leg1->Draw();
	leg3->Draw();
	leg2->Draw();
	c->SaveAs("./tex/ratiokappa013truthVsR_mu.tex");
	c->SaveAs("./pdf/ratiokappa013truthVsR_mu.pdf");

	TCanvas *c1 = new TCanvas("c1", "c1", 700, 500);
	
	//! kappa Vs dkappa
	TH2F *H37 = (TH2F*)f->Get("th37");
	TH2F *H39 = (TH2F*)f->Get("th39");
	TH2F *H40 = (TH2F*)f->Get("th40");
	TH2F *H41 = (TH2F*)f->Get("th41");
	H37->GetXaxis()->CenterTitle();
	H37->GetYaxis()->CenterTitle();
	H37->GetXaxis()->SetTitle("#kappa_{013} [mm^{-1}]");
	H37->GetYaxis()->SetTitle("d#kappa [mm^{-1}]");
	H37->GetXaxis()->SetTitleSize(TITLE_SIZE);
	H37->GetYaxis()->SetTitleSize(TITLE_SIZE);
	H37->GetYaxis()->SetTitleOffset(1.1);
	H37->SetLineWidth(LINE_WIDTH);
	H39->SetLineWidth(LINE_WIDTH);
	H40->SetLineWidth(LINE_WIDTH);
	H41->SetLineWidth(LINE_WIDTH);
	H37->SetMarkerStyle(MARKER_STYLE);
	H39->SetMarkerStyle(MARKER_STYLE);
	H40->SetMarkerStyle(MARKER_STYLE);
	H41->SetMarkerStyle(MARKER_STYLE);
	H37->SetMarkerColor(kCyan);
	H39->SetMarkerColor(kAzure+1);
	H41->SetMarkerColor(kBlue+2);
	H37->SetLineColor(kCyan);
	H39->SetLineColor(kAzure+1);
	H41->SetLineColor(kBlue+2);
	H37->Draw();
	H39->Draw("same");
	//H40->Draw("same");
	H41->Draw("same");
	leg1->Draw();
	TLegend *leg_ = new TLegend(0.13, Yu1-0.23, Xl2-0.03,Yu1-0.03,"#kappa cut");
	leg_->AddEntry(H41,"|d#kappa| < 3 #sigma_{#kappa}","l");
	//leg_->AddEntry(H40,"medium","l");
	leg_->AddEntry(H39,"|d#kappa| < 5 #sigma_{#kappa}","l");
	leg_->AddEntry(H37,"--","l");

	leg_->SetTextAlign(kHAlignCenter+kVAlignCenter);
	//leg_->SetFillStyle(FILL_STYLE);
	leg_->SetBorderSize(BORDER_SIZE);
	leg_->SetTextSize(TEXT_SIZE);
	leg_->Draw();
	leg4->Draw();
	leg3->Draw();
	leg2->Draw();
	c1->SaveAs("./tex/dkappa.tex");
	c1->SaveAs("./pdf/dkappa.pdf");
	return;
}
