#include "TROOT.h"
#include "plot_props.h"

void create_dca()
{

	TChain c("m_recTree");
	c.Add("/home/tamasi/repo_tamasi/rec_file/rec_file/30mm/PU1k/ggFhh4b_SM/*.root");
	TH1D *h = new TH1D("h","h", 100, -100, 100);
	c.Draw("(dca-M_dca)>>h","Tid > 0 && abs(M_pt) > 2e3 && abs(M_Vz) < 100 && abs(M_Vx) < 5 && abs(M_Vy) < 5 && abs(M_eta) < 1.7");
	//! Todo write to a file "dca.root"

}

void plot_dca()
{

	Legends();

	TFile *f = new TFile("dca.root","READ");
	TCanvas *d = (TCanvas*)f->Get("c1");
	TH1D *h1 = (TH1D*)d->GetPrimitive("h");

	TCanvas *c = new TCanvas("c","c", 800, 800);
	h1->Draw();
	h1->GetXaxis()->SetRangeUser(-50, 50);
	h1->GetXaxis()->SetTitle("dca [mm]");
	h1->GetXaxis()->SetTitleSize(TITLE_SIZE);
	h1->GetXaxis()->CenterTitle();
	int max = h1->GetMaximum();
	h1->GetYaxis()->SetRangeUser(0, 1.3*max);
	h1->Fit("gaus");

	//gROOT->SetStyle("Plain");
	gStyle->SetStatBorderSize(0);
	//gStyle->SetFillStyle(0);
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	//gStyle->SetOptFit(100011);
	//gStyle->SetStatX(0.7);
	//gStyle->SetStatY(0.7);
	//
	TF1 *Func1 = h1->GetFunction("gaus");
	double mean, mean_err, sigma, sigma_err =0;
	mean     = Func1->GetParameter(1);
	mean_err = Func1->GetParError(1);
	sigma    = Func1->GetParameter(2);
	sigma_err= Func1->GetParError(2);

	h1->Draw();

	TLegend *stat = new TLegend(0.25,0.13, 0.45, 0.2);
	stat->AddEntry((TObject*)0, Form("mean = %.3f #pm %.3f mm", mean, mean_err), "");
	stat->AddEntry((TObject*)0, Form("#sigma_{#delta dca} = %.3f #pm %.3f mm", sigma, sigma_err), "");
	//stat->AddEntry((TObject*)0, Form("mean = %.4f [mm]", mean), "");
	//stat->AddEntry((TObject*)0, Form("#sigma_{#delta dca} = %.4f [mm]",sigma), "");
	stat->SetFillStyle(FILL_STYLE);
	stat->SetBorderSize(BORDER_SIZE);
	stat->SetTextSize(TEXT_SIZE);
	stat->Draw();


	leg1->Draw();
	leg2->Draw();
	leg5->Draw();


	c->Update();
	c->SaveAs("./tex/plotdca.tex");
	return;
}
