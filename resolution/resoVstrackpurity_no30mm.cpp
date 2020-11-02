//! draws a summary plot 
//! of single particle resolution as a function of track purity 
//! for various gap sizes of the TTT
//! write the rms of resolution, its error and track purity for each gap size into a text file
//! read this txt file to draw a graph of reso Vs track purity for various gap sizes for a given pileup
//! do the same for various pileups and draw a multigraph

#include <iostream>
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
#include <fstream>
#include <string>
#include<math.h>
//! the selection cuts below are only to select tracks correctly reconstructed and fakes
//! assumes the files fed are reconstructed with optimised cuts already
TCut num_select    = "Tid>0 && abs(Eta13) < 1.7 && abs(kappa_pull) < 3";
TCut den_select    = "Tid>-2 && abs(Eta13) < 1.7 && abs(kappa_pull) < 3";
//! use the cut below to calculate single particle resolution for 10GeV pions
TCut all_cut= "Tid > 0 && abs(Eta13) < 1.7 && abs(kappa_pull) < 3 && abs(M_pt)>9e3 && abs(M_pt)<11e3 && abs(M_eta)<1.7 && abs(M_Vz) < 100 && abs(M_Vx) < 2 && abs(M_Vy) < 2 && abs(M_pdg)==211";
TCanvas *c1 = new TCanvas();
char buf[4096];
//! User defined Gauss fit function to optimise the fit 
void fit_Gauss(TH1F* h)
{
	h->SetLineWidth(2);
	float xmin = h->GetXaxis()->GetXmin(), xmin_ = xmin;
	float xmax = h->GetXaxis()->GetXmax(), xmax_ = xmax;
	//! repeat the fit thrice 
	for(int i = 0; i < 3; i++) 
	{
    	h->Fit("gaus", "QLL", "", xmin_, xmax_);
    	xmin_ = h->GetFunction("gaus")->GetParameter(1) - 1.3 * h->GetFunction("gaus")->GetParameter(2);
    	xmax_ = h->GetFunction("gaus")->GetParameter(1) + 1.3 * h->GetFunction("gaus")->GetParameter(2);
  	}

	h->GetFunction("gaus")->SetLineColor(2);
  	h->GetFunction("gaus")->SetLineWidth(2);

	h->GetYaxis()->SetRangeUser(0, 1.1 * h->GetMaximum());
	float ymin = 0;
	float ymax = 1.1 * h->GetMaximum();

	TLatex lat;
	sprintf(buf, "#mu = %.2f", h->GetFunction("gaus")->GetParameter(1));
	lat.DrawLatex(xmin + 0.6 * (xmax - xmin), 0.80 * ymax, buf);
	sprintf(buf, "#sigma = %.2f", h->GetFunction("gaus")->GetParameter(2));
	lat.DrawLatex(xmin + 0.6 * (xmax - xmin), 0.75 * ymax, buf);
}
//! clears the txt file
void deleteText(const char* pileup) {
    const char* txt_path = "./txt_files";
    char txt_file[1023];
    //sprintf(txt_file,"%s/summary10-100_rmsVspurity_PU%s.txt",txt_path, pileup);
    sprintf(txt_file,"%s/summary_rmsVspurityNo30mm_PU%s.txt",txt_path, pileup);
    std::ofstream ofs;
    ofs.open(txt_file, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}
//writes the gapsize,purity,rms and error in a txt file
void write_file(const char* gapsize, const char* pileup, double purity , double rms, double error)
{
    std::cout<<"Writing to txt file...." <<std::endl;
    const char* txt_path = "./txt_files";
    char txt_file[1023];
    sprintf(txt_file,"%s/FCCsummary5-100_rmsVspurity_PU%s.txt",txt_path, pileup);
    std::ofstream ofs;
    ofs.open (txt_file, std::ofstream::out | std::ofstream::app);
    ofs<<gapsize<<" "<<purity<<" "<<rms<<" "<<error<<"\n";
    ofs.close();

}
void write_file_Zvtx(const char* gapsize, const char* pileup, double purity , double rms, double error)
{
    std::cout<<"Writing to txt file...." <<std::endl;
    const char* txt_path = "./txt_files";
    char txt_file[1023];
    sprintf(txt_file,"%s/FCCsummary5-100_rmsZvtxVspurity_PU%s.txt",txt_path, pileup);
    std::ofstream ofs;
    ofs.open (txt_file, std::ofstream::out | std::ofstream::app);
    ofs<<gapsize<<" "<<purity<<" "<<rms<<" "<<error<<"\n";
    ofs.close();

}

//! opens the reconstructed root file with gap size = "run_no" and momentum "p"(e.g. 10GeV/c)
//! hence calls the draw function. 
//! This function draws the resolution plots and fits a gaus function and
//! fetches the rms and errors from the fit and hence calls the write function.
//! the write function creates a txt file and prints 
//! the run_no, the momentum p, rms, and error..

//! run_no - run number of the single particle file
//! first two numbers of which are identical to gap size
void rmsVspurity(const char *run_no, const char *pileup, const char *gapsize)
{
	Int_t num_events = 425;
	//! calculate track purity
	//const char *file_path = "/media/tamasi/DriveT1/tamasi/Desktop/PHD/talks_preps/ctd2k19/data_files/hh4b/pileup_samples/rec-files";
	const char *file_path = "/home/tamasi/repo_tamasi/rec_files/rec_files";
	char signal_file_names[1023];//e.g. PU200hh4b_recOPTsig5_005004.root
	//sprintf(signal_file_names, "%s/PU%shh4b_recOPTsig5_00%s*.root",file_path,pileup,gapsize);
	sprintf(signal_file_names, "%s/%smm/PU%s/ggFhh4b_SM/*.root",file_path,gapsize,pileup);
	TChain rec("m_recTree");
	rec.Add(signal_file_names);
	std::cout<<"rec tree opened with " << rec.GetEntries() <<"entries\n";
	/// LOG BINS
	/// Variable bin width
	const int ptbins = 40;//no. of bins
	Double_t xbins[ptbins+1];//elements of this array are
	double dx = 5./ptbins;//5 -> implies max until 10^5
	double l10 = TMath::Log(10);
	for (int i = 0; i<=ptbins; i++)
	{
	//        std::cout<<"i,dx : " <<i << ", "<<dx <<std::endl;
		xbins[i] = TMath::Exp(l10*i*dx);
	//        std::cout<<"xbin[i] : " <<xbins[i] <<std::endl;
	}
	TCanvas *c = new TCanvas();	
        TH1::SetDefaultSumw2(true);
	TH1* h_num_vs_ptPU = new TH1F("h_num_vs_ptPU", "Numerator Count vs P_{t};P_{t} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_ptPU = new TH1F("h_den_vs_ptPU", "Denominator Count vs P_{t};P_{t} [MeV/c];Denominator Count", ptbins, xbins);
	rec.Draw("Pt_n>>h_num_vs_ptPU",   num_select, "goff", num_events);
	rec.Draw("Pt_n>>h_den_vs_ptPU",   den_select, "goff", num_events);
	TH1* h_pur_vs_ptPU = dynamic_cast<TH1*>(h_num_vs_ptPU->Clone("h_pur_vs_ptPU"));
	h_pur_vs_ptPU->SetTitle("Purity vs P_{t};P_{t} [MeV/c];Purity");
	h_pur_vs_ptPU->Divide(h_num_vs_ptPU, h_den_vs_ptPU, 1.0, 1.0, "B");
	h_pur_vs_ptPU->GetYaxis()->SetRangeUser(0.1, 1.1);
//	h_pur_vs_ptPU->GetXaxis()->SetRangeUser(2000.,1000000.);
	h_pur_vs_ptPU->SetMarkerSize(0.95);
	h_pur_vs_ptPU->SetMarkerStyle(kOpenTriangleDown);
	h_pur_vs_ptPU->SetMarkerColor(kBlack);	
	if (h_pur_vs_ptPU->GetSumw2N() == 0) h_pur_vs_ptPU->Sumw2(kTRUE);	
	h_pur_vs_ptPU->Draw("Hist e1");
	//! calculate integral of purity in the high pt region
	//! https://root.cern.ch/root/roottalk/roottalk03/2211.html
	//double integral = h_pur_vs_ptPU->Integral();
	double xmin = 5e3, xmax = 100e3;
	TAxis *axis = h_pur_vs_ptPU->GetXaxis();
	int bmin = axis->FindBin(xmin); 
	int bmax = axis->FindBin(xmax); 
	/*double integral = 0;
	for(int i = bmin; i < bmax+1; ++i)
	{
		integral += (h_pur_vs_ptPU->GetBinContent(i)*h_pur_vs_ptPU->GetBinCenter(i));
		std::cout << "bin content "<< i << " = " << h_pur_vs_ptPU->GetBinContent(i) << ", with bincenter : " << h_pur_vs_ptPU->GetBinCenter(i) <<std::endl;
	}
*/	double norm = axis->GetBinUpEdge(bmax) - axis->GetBinLowEdge(bmin);	
	std::cout<<"norm = " << norm <<std::endl;
	
	double integral = h_pur_vs_ptPU->Integral(bmin,bmax,"width");
	/*double integral = h_pur_vs_ptPU->Integral(bmin,bmax,"");
	std::cout<<"bmax - bmin : " << bmax << " - " << bmin << " = " << bmax -bmin <<std::endl;
	integral -= h_pur_vs_ptPU->GetBinContent(bmin)*(xmin-axis->GetBinLowEdge(bmin))/axis->GetBinWidth(bmin);
	integral -= h_pur_vs_ptPU->GetBinContent(bmax)*(axis->GetBinUpEdge(bmax)-xmax)/axis->GetBinWidth(bmax);*/
	double purity = integral/norm;
	std::cout<<"purity in the pt range [" <<xmin << "," << xmax <<"] = " <<integral/norm << std::endl;
	
	//! calculate rel pt resolution using single pions
	//const char *file_path1 = "/media/tamasi/DriveT1/tamasi/Desktop/PHD/talks_preps/ctd2k19/data_files/single_particle/rec-files";
	char rec_file_names[1023];//e.g. pi-_recOPTsig5_005010.root
	//sprintf(rec_file_name, "%s/pi-_recOPTsig5_00%s.root",file_path1,run_no);
	//TFile *f = TFile::Open(rec_file_name);
	//TTree *t = (TTree*)f->Get("m_recTree");
	sprintf(rec_file_names, "%s/pi*_recTree_%s.root",file_path,run_no);
	TChain t("m_recTree");
	t.Add(rec_file_names);
	double binNum = 100;
	double relptmin = -0.1, relptmax = 0.1;
	c1->Clear();
	char histo_title[1023];
	sprintf(histo_title,"Relative p_{t} Resolution, triplet gapsize %s, 10GeV single #pi",gapsize);
	TH1F* h_p = new TH1F("h_p","histo_title",binNum,relptmin,relptmax);
	t.Draw("(Pt_n - M_pt)/M_pt>>h_p",all_cut);
	h_p->SetXTitle("delta p [MeV/c]");
	h_p->SetTitle(histo_title);
	h_p->Draw();
	fit_Gauss(h_p);
	c1->Update();
	//h1->GetFunction("gaus")->GetParameter(2), h1->GetFunction("gaus")->GetParError(2)
	//double pRMS = h_p->GetRMS();
	//double PRMS_err = h_p->GetRMSError();
	double pRMS = h_p->GetFunction("gaus")->GetParameter(2);
	double PRMS_err = h_p->GetFunction("gaus")->GetParError(2);
	write_file(gapsize, pileup, purity, pRMS, PRMS_err);
	delete h_num_vs_ptPU;
	delete h_den_vs_ptPU;
	delete h_p;
}
void rmsZvtxVspurity(const char *run_no, const char *pileup, const char *gapsize)
{
	Int_t num_events = 425;
	//! calculate track purity
	//const char *file_path = "/media/tamasi/DriveT1/tamasi/Desktop/PHD/talks_preps/ctd2k19/data_files/hh4b/pileup_samples/rec-files";
	const char *file_path = "/home/tamasi/repo_tamasi/rec_files/rec_files";
	char signal_file_names[1023];//e.g. PU200hh4b_recOPTsig5_005004.root
	//sprintf(signal_file_names, "%s/PU%shh4b_recOPTsig5_00%s*.root",file_path,pileup,gapsize);
	sprintf(signal_file_names, "%s/%smm/PU%s/ggFhh4b_SM/*.root",file_path,gapsize,pileup);
	TChain rec("m_recTree");
	rec.Add(signal_file_names);
	std::cout<<"rec tree opened with " << rec.GetEntries() <<"entries\n";
	/// LOG BINS
	/// Variable bin width
	const int ptbins = 40;//no. of bins
	Double_t xbins[ptbins+1];//elements of this array are
	double dx = 5./ptbins;//5 -> implies max until 10^5
	double l10 = TMath::Log(10);
	for (int i = 0; i<=ptbins; i++)
	{
	//        std::cout<<"i,dx : " <<i << ", "<<dx <<std::endl;
		xbins[i] = TMath::Exp(l10*i*dx);
	//        std::cout<<"xbin[i] : " <<xbins[i] <<std::endl;
	}
	TCanvas *c = new TCanvas();	
        TH1::SetDefaultSumw2(true);
	TH1* h_num_vs_ptPU = new TH1F("h_num_vs_ptPU", "Numerator Count vs P_{t};P_{t} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_ptPU = new TH1F("h_den_vs_ptPU", "Denominator Count vs P_{t};P_{t} [MeV/c];Denominator Count", ptbins, xbins);
	rec.Draw("Pt_n>>h_num_vs_ptPU",   num_select, "goff", num_events);
	rec.Draw("Pt_n>>h_den_vs_ptPU",   den_select, "goff", num_events);
	TH1* h_pur_vs_ptPU = dynamic_cast<TH1*>(h_num_vs_ptPU->Clone("h_pur_vs_ptPU"));
	h_pur_vs_ptPU->SetTitle("Purity vs P_{t};P_{t} [MeV/c];Purity");
	h_pur_vs_ptPU->Divide(h_num_vs_ptPU, h_den_vs_ptPU, 1.0, 1.0, "B");
	h_pur_vs_ptPU->GetYaxis()->SetRangeUser(0.1, 1.1);
//	h_pur_vs_ptPU->GetXaxis()->SetRangeUser(2000.,1000000.);
	h_pur_vs_ptPU->SetMarkerSize(0.95);
	h_pur_vs_ptPU->SetMarkerStyle(kOpenTriangleDown);
	h_pur_vs_ptPU->SetMarkerColor(kBlack);	
	if (h_pur_vs_ptPU->GetSumw2N() == 0) h_pur_vs_ptPU->Sumw2(kTRUE);	
	h_pur_vs_ptPU->Draw("Hist e1");
	//! calculate integral of purity in the high pt region
	//! https://root.cern.ch/root/roottalk/roottalk03/2211.html
	//double integral = h_pur_vs_ptPU->Integral();
	double xmin = 5e3, xmax = 100e3;
	TAxis *axis = h_pur_vs_ptPU->GetXaxis();
	int bmin = axis->FindBin(xmin); 
	int bmax = axis->FindBin(xmax); 
	/*double integral = 0;
	for(int i = bmin; i < bmax+1; ++i)
	{
		integral += (h_pur_vs_ptPU->GetBinContent(i)*h_pur_vs_ptPU->GetBinCenter(i));
		std::cout << "bin content "<< i << " = " << h_pur_vs_ptPU->GetBinContent(i) << ", with bincenter : " << h_pur_vs_ptPU->GetBinCenter(i) <<std::endl;
	}
*/	double norm = axis->GetBinUpEdge(bmax) - axis->GetBinLowEdge(bmin);	
	std::cout<<"norm = " << norm <<std::endl;
	
	double integral = h_pur_vs_ptPU->Integral(bmin,bmax,"width");
	/*double integral = h_pur_vs_ptPU->Integral(bmin,bmax,"");
	std::cout<<"bmax - bmin : " << bmax << " - " << bmin << " = " << bmax -bmin <<std::endl;
	integral -= h_pur_vs_ptPU->GetBinContent(bmin)*(xmin-axis->GetBinLowEdge(bmin))/axis->GetBinWidth(bmin);
	integral -= h_pur_vs_ptPU->GetBinContent(bmax)*(axis->GetBinUpEdge(bmax)-xmax)/axis->GetBinWidth(bmax);*/
	double purity = integral/norm;
	std::cout<<"purity in the pt range [" <<xmin << "," << xmax <<"] = " <<integral/norm << std::endl;
	
	//! calculate rel pt resolution using single pions
	//const char *file_path1 = "/media/tamasi/DriveT1/tamasi/Desktop/PHD/talks_preps/ctd2k19/data_files/single_particle/rec-files";
	char rec_file_names[1023];//e.g. pi-_recOPTsig5_005010.root
	//sprintf(rec_file_names, "%s/pi-_recOPTsig5_00%s.root",file_path1,run_no);
	//TFile *f = TFile::Open(rec_file_names);
	//TTree *t = (TTree*)f->Get("m_recTree");
	sprintf(rec_file_names, "%s/pi*_recTree_%s.root",file_path,run_no);
	TChain t("m_recTree");
	t.Add(rec_file_names);
	double binNum = 100;
	double zmin = -6, zmax = 6;
	c1->Clear();
	char histo_title[1023];
	sprintf(histo_title,"z_{0} Resolution, triplet gapsize %s, 10GeV single #pi",gapsize);
	TH1F* h_p = new TH1F("h_p","histo_title",binNum,zmin,zmax);
	t.Draw("Z013 - M_Vz>>h_p",all_cut);
	h_p->SetXTitle("delta z [mm]");
	h_p->SetTitle(histo_title);
	h_p->Draw();
	fit_Gauss(h_p);
	c1->Update();
	//h1->GetFunction("gaus")->GetParameter(2), h1->GetFunction("gaus")->GetParError(2)
	//double pRMS = h_p->GetRMS();
	//double PRMS_err = h_p->GetRMSError();
	double pRMS = h_p->GetFunction("gaus")->GetParameter(2);
	double PRMS_err = h_p->GetFunction("gaus")->GetParError(2);
	write_file_Zvtx(gapsize, pileup, purity, pRMS, PRMS_err);
	delete h_num_vs_ptPU;
	delete h_den_vs_ptPU;
	delete h_p;
}

int writePU200()
{
	rmsVspurity("5010","200","50");
	rmsVspurity("4010","200","40");
	rmsVspurity("2010","200","20");
	rmsZvtxVspurity("5010","200","50");
	rmsZvtxVspurity("4010","200","40");
	rmsZvtxVspurity("2010","200","20");
	return 0;
}
int writePU1000()
{
	//rmsVspurity("5010","1000","50");
	//rmsVspurity("4010","1000","40");
	//rmsVspurity("2010","1000","20");
	//rmsZvtxVspurity("5010","1000","50");
	//rmsZvtxVspurity("4010","1000","40");
	//rmsZvtxVspurity("2010","1000","20");
	
	rmsVspurity("250010","1k","25");
	rmsVspurity("300010","1k","30");
	rmsVspurity("350010","1k","35");
	rmsVspurity("400010","1k","40");
	rmsZvtxVspurity("250010","1k","25");
	rmsZvtxVspurity("300010","1k","30");
	rmsZvtxVspurity("350010","1k","35");
	rmsZvtxVspurity("400010","1k","40");
	return 0;
}
void SaveCanvas(TCanvas *C, char *name)
{
    const char *path = "./summary_purity";
    char full_name[1023];
    sprintf(full_name,"%s/summary_%s.root", path, name);
    C->SaveAs(full_name);
    sprintf(full_name,"%s/summary_%s.pdf", path, name);
    C->SaveAs(full_name);
    sprintf(full_name,"%s/summary_%s.png", path, name);
    C->SaveAs(full_name);
    sprintf(full_name,"%s/summary_%s.C", path, name);
    C->SaveAs(full_name);

}
void summary_relptVspurity()
{
	//! no. of points to be plotted
	Int_t n = 4;
	//Multi Graph
	c1->Clear();
	c1->SetGridx();
	c1->SetGridy();
	const char* txt_path = "./txt_files";
	char txt_file1[1023];//PU1000
	char txt_file2[1023];//PU200
	//char txt_file3[1023];//PU0

	char plot_title[1023];
	//! PU 1000
	sprintf(txt_file1,"%s/FCCsummary10-100_rmsVspurity_PU%s.txt",txt_path,"1k");
	//! PU 200
	sprintf(txt_file2,"%s/FCCsummary10-100_rmsVspurity_PU%s.txt",txt_path,"1k");
	//sprintf(txt_file2,"%s/summary10-100_rmsVspurityNo30mm_PU%s.txt",txt_path,"200");
	//sprintf(txt_file3,"%s/summary20-100_rmsVspurity_PU%s.txt",txt_path,pileup);

	sprintf(plot_title,"Relative p_{t} resolution Vs track purity for various gap sizes of the TTT");

	TTree *t1 = new TTree ("t1", "t1");
	t1->ReadFile(txt_file1,"gapsize:purity:rms:err");
	t1->Draw("purity:rms*100:err","","goff");
	//    TGraphErrors *g1 = new TGraphErrors(24,t1->GetV1(),t1->GetV2(),0,t1->GetV3());

	TGraphErrors *g1 = new TGraphErrors(n,t1->GetV1(),t1->GetV2(),0,t1->GetV3());
	g1->SetTitle(plot_title);
	g1->GetXaxis()->SetTitle("Track Purity for p_{t} > 10GeV/c");
	g1->GetXaxis()->SetRangeUser(0.5,1);
	g1->GetYaxis()->SetTitleOffset(1.2);
	g1->GetYaxis()->SetTitle("#sigma_{#Delta(p_{t})/p_{t_{gen}}} [%]@ p_{t} = 10 GeV/c");
	g1->GetYaxis()->SetRangeUser(0,1.3);
	g1->SetMarkerStyle(kFullCircle);
	c1->cd(4);
	g1->SetFillStyle(0);
//	g1->SetTitle("<#mu> = 960");
	g1->Draw("ACPe1");
	//g1->Draw("APe1");
	
	TTree *t2 = new TTree ("t2", "t2");
	t2->ReadFile(txt_file2,"gapsize:purity:rms:err");
	t2->Draw("purity:rms*100:err","","goff");
	//    TGraphErrors *g2 = new TGraphErrors(24,t2->GetV1(),t2->GetV2(),0,t2->GetV3());
	//TGraph *g2 = new TGraph(n,t2->GetV1(),t2->GetV2());
	TGraphErrors *g2 = new TGraphErrors(n,t2->GetV1(),t2->GetV2(),0,t2->GetV3());
	g2->SetTitle(plot_title);
	g2->GetXaxis()->SetTitle("Track Purity for p_{t} > 10GeV/c");
	g2->GetXaxis()->SetRangeUser(0.5,1);
	g2->GetYaxis()->SetTitleOffset(1.2);
	g2->GetYaxis()->SetTitle("#sigma_{#Delta(p_{t})/p_{t_{gen}}} [%] @ p_{t} = 10 GeV/c");
	g2->GetYaxis()->SetRangeUser(0,1.3);
	g2->SetMarkerStyle(kFullTriangleUp);
	c1->cd(4);
	g2->SetFillStyle(0);
//	g2->SetTitle("<#mu> = 160");
	g2->Draw("CPe1");
	//g2->Draw("Pe1");

	/*TTree *t3 = new TTree ("t3", "t3");
	t3->ReadFile(txt_file3,"run_Num:pt:rms:err");
	t3->Draw("pt:rms:err","","goff");
	//    TGraphErrors *g3 = new TGraphErrors(24,t3->GetV1(),t3->GetV2(),0,t3->GetV3());

	TGraphErrors *g3 = new TGraphErrors(15,t3->GetV1(),t3->GetV2(),0,t3->GetV3());
	g3->SetMarkerColor(kGreen);
	g3->SetLineColor(kGreen);
	g3->SetLineWidth(2);
	g3->SetMarkerStyle(3);
	g3->SetFillStyle(0);
	g3->SetTitle("Inner Triplet ~ 7cm");
*/
//////////////////////////////////////////////////////////////
	/*
	TMultiGraph *g = new TMultiGraph();
	//g->Add(g1);
	g->Add(g2);
	//g->Add(g3);
	g->Draw("APe1");

	g->SetTitle(plot_title);
	g->GetXaxis()->SetTitle("Track Purity");
	g->GetXaxis()->SetRangeUser(0.7,1);
	g->GetYaxis()->SetTitleOffset(1.5);
	g->GetYaxis()->SetTitle("#sigma_{#Delta(p_{t})/gen_p_{t}} @ p_{t} = 10 GeV/c");
	g->GetYaxis()->SetRangeUser(0,0.015);*/
/////////////////////////////////////////////////////////////

	// get the points in the graph and put them into an array
	Double_t *nx1 = g1->GetX();
	Double_t *ny1 = g1->GetY();
	Double_t *nx = g2->GetX();
	Double_t *ny = g2->GetY();
	
	Double_t x1= 0.11,y1= 0.11, x2 = 0.31, y2 = 0.31;
	TLegend *leg=new TLegend(x1,y2,x2,y2+0.1,"<#mu>,  gap size");
	leg->SetFillColor(kWhite);
	leg->SetBorderSize(0);
	
	TLegend *leg1=new TLegend(x1,y1,x2,y2,"960, 160");
	leg1->SetFillColor(kWhite);
	leg1->SetBorderSize(0);
	leg1->SetNColumns(2);
	// create markers of different colors
	Int_t j =0;
	for (j=0; j<n; j++) {
	std::cout << "j , nx, ny: " << j << ", " << nx << ", " << ny <<std::endl;
	std::cout << "color code : " << (kRed-10) + (3*j) <<std::endl;
	TMarker *m1 = new TMarker(nx1[j], ny1[j], kFullCircle);
	m1->SetMarkerSize(2);
	//m1->SetMarkerColor((kBlue-10) + (3*j));
	m1->SetMarkerColor(j+1);
	m1->Draw();
	TMarker *m = new TMarker(nx[j], ny[j], kFullTriangleUp);
	m->SetMarkerSize(2);
	//m->SetMarkerColor((kRed-10) + (3*j));
	m->SetMarkerColor(j+1);
	m->Draw();
	if(j == 0) 
	{
		leg1->AddEntry(m1,",");
		leg1->AddEntry(m,"   25mm");
	}
	if(j == 1) 
	{
		leg1->AddEntry(m1,",");
		leg1->AddEntry(m,"   30mm");
	}
	if(j == 2)
	{
		leg1->AddEntry(m1,",");
		leg1->AddEntry(m,"   35mm");
	}
	if(j == 3)
	{
		leg1->AddEntry(m1,",");
		leg1->AddEntry(m,"   40mm");
	}
	}
	leg->Draw();
	leg1->Draw();
	c1->Update();
	SaveCanvas(c1,"relptVspurityNo30mm10GeV_varPU1");

}
void summary_ZvtxVspurity()
{
	//! no. of points to be plotted
	Int_t n = 3;
	//Multi Graph
	c1->Clear();
	c1->SetGridx();
	c1->SetGridy();
	const char* txt_path = "./txt_files";
	char txt_file1[1023];//PU1000
	char txt_file2[1023];//PU200
	//char txt_file3[1023];//PU0

	char plot_title[1023];
	//! PU 1000
	sprintf(txt_file1,"%s/summary10-100_rmsZvtxVspurityNo30mm_PU%s.txt",txt_path,"1000");
	//! PU 200
	sprintf(txt_file2,"%s/summary10-100_rmsZvtxVspurityNo30mm_PU%s.txt",txt_path,"200");
	//sprintf(txt_file3,"%s/summary20-100_rmsVspurity_PU%s.txt",txt_path,pileup);

	sprintf(plot_title,"z_{0} resolution Vs track purity for various gap sizes of the TTT");

	TTree *t1 = new TTree ("t1", "t1");
	t1->ReadFile(txt_file1,"gapsize:purity:rms:err");
	t1->Draw("purity:rms:err","","goff");
	//    TGraphErrors *g1 = new TGraphErrors(24,t1->GetV1(),t1->GetV2(),0,t1->GetV3());

	TGraphErrors *g1 = new TGraphErrors(n,t1->GetV1(),t1->GetV2(),0,t1->GetV3());
	g1->SetTitle(plot_title);
	g1->GetXaxis()->SetTitle("Track Purity for p_{t} > 10GeV/c");
	g1->GetXaxis()->SetRangeUser(0.6,1);
	g1->GetYaxis()->SetTitleOffset(1.2);
	g1->GetYaxis()->SetTitle("#sigma_{#Delta(z)}[mm] @ p_{t} = 10 GeV/c");
	g1->GetYaxis()->SetRangeUser(0,0.6);
	g1->SetMarkerStyle(kFullCircle);
	c1->cd(4);
	g1->SetFillStyle(0);
//	g1->SetTitle("<#mu> = 960");
	g1->Draw("ACPe1");
	//g1->Draw("APe1");
	
	TTree *t2 = new TTree ("t2", "t2");
	t2->ReadFile(txt_file2,"gapsize:purity:rms:err");
	t2->Draw("purity:rms:err","","goff");
	//    TGraphErrors *g2 = new TGraphErrors(24,t2->GetV1(),t2->GetV2(),0,t2->GetV3());
	//TGraph *g2 = new TGraph(n,t2->GetV1(),t2->GetV2());
	TGraphErrors *g2 = new TGraphErrors(n,t2->GetV1(),t2->GetV2(),0,t2->GetV3());
	g2->SetTitle(plot_title);
	g2->GetXaxis()->SetTitle("Track Purity for p_{t} > 10GeV/c");
	g2->GetXaxis()->SetRangeUser(0.6,1);
	g2->GetYaxis()->SetTitleOffset(1.2);
	g2->GetYaxis()->SetTitle("#sigma_{#Delta(z)}[mm] @ p_{t} = 10 GeV/c");
	g2->GetYaxis()->SetRangeUser(0,0.6);
	g2->SetMarkerStyle(kFullTriangleUp);
	c1->cd(4);
	g2->SetFillStyle(0);
//	g2->SetTitle("<#mu> = 160");
	g2->Draw("CPe1");
	//g2->Draw("Pe1");

	/*TTree *t3 = new TTree ("t3", "t3");
	t3->ReadFile(txt_file3,"run_Num:pt:rms:err");
	t3->Draw("pt:rms:err","","goff");
	//    TGraphErrors *g3 = new TGraphErrors(24,t3->GetV1(),t3->GetV2(),0,t3->GetV3());

	TGraphErrors *g3 = new TGraphErrors(15,t3->GetV1(),t3->GetV2(),0,t3->GetV3());
	g3->SetMarkerColor(kGreen);
	g3->SetLineColor(kGreen);
	g3->SetLineWidth(2);
	g3->SetMarkerStyle(3);
	g3->SetFillStyle(0);
	g3->SetTitle("Inner Triplet ~ 7cm");
*/
//////////////////////////////////////////////////////////////
	/*
	TMultiGraph *g = new TMultiGraph();
	//g->Add(g1);
	g->Add(g2);
	//g->Add(g3);
	g->Draw("APe1");

	g->SetTitle(plot_title);
	g->GetXaxis()->SetTitle("Track Purity");
	g->GetXaxis()->SetRangeUser(0.7,1);
	g->GetYaxis()->SetTitleOffset(1.5);
	g->GetYaxis()->SetTitle("#sigma_{#Delta(p_{t})/gen_p_{t}} @ p_{t} = 10 GeV/c");
	g->GetYaxis()->SetRangeUser(0,0.015);*/
/////////////////////////////////////////////////////////////

	// get the points in the graph and put them into an array
	Double_t *nx1 = g1->GetX();
	Double_t *ny1 = g1->GetY();
	Double_t *nx = g2->GetX();
	Double_t *ny = g2->GetY();
	
	Double_t x1= 0.1,y1= 0.1, x2 = 0.3, y2 = 0.3;
	TLegend *leg=new TLegend(x1,y2,x2,y2+0.1,"<#mu>,  gap size");
	leg->SetFillColor(kWhite);
	leg->SetBorderSize(0);
	
	TLegend *leg1=new TLegend(x1,y1,x2,y2,"960, 160");
	leg1->SetFillColor(kWhite);
	leg1->SetBorderSize(0);
	leg1->SetNColumns(2);
	// create markers of different colors
	Int_t j =0;
	for (j=0; j<n; j++) {
	std::cout << "j , nx, ny: " << j << ", " << nx << ", " << ny <<std::endl;
	std::cout << "color code : " << (kRed-10) + (3*j) <<std::endl;
	TMarker *m1 = new TMarker(nx1[j], ny1[j], kFullCircle);
	m1->SetMarkerSize(2);
	//m1->SetMarkerColor((kBlue-10) + (3*j));
	m1->SetMarkerColor(j+1);
	m1->Draw();
	TMarker *m = new TMarker(nx[j], ny[j], kFullTriangleUp);
	m->SetMarkerSize(2);
	//m->SetMarkerColor((kRed-10) + (3*j));
	m->SetMarkerColor(j+1);
	m->Draw();
	if(j == 0) 
	{
		leg1->AddEntry(m1,",");
		leg1->AddEntry(m,"   50mm");
	}
	if(j == 1) 
	{
		leg1->AddEntry(m1,",");
		leg1->AddEntry(m,"   40mm");
	}
	if(j == 2)
	{
		leg1->AddEntry(m1,",");
		leg1->AddEntry(m,"   20mm");
	}
	}
	leg->Draw();
	leg1->Draw();
	c1->Update();
	SaveCanvas(c1,"ZvtxVspurityNo30mm10GeV_varPU1");

}
