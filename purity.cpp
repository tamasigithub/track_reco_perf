#include <iostream>
#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TPostScript.h"
#include "TLatex.h"
#include <fstream>
#include <string>
#include <math.h>
const char* out_path = "./plots/purity"; 

int InDetpurity_Vs_etaphipt(const char* output_file_name = "testpurity", bool save = false)
{
//! Define Cut
TCut num_select= "InDetTBarcode > 0 && abs(InDetTPt)>2000 && abs(InDetTEta)<1.4 && abs(InDetpt)>2000 && abs(InDeteta)<1.4";
TCut den_select= "abs(InDetpt)>2000 && abs(InDeteta)<1.4";
	
	TChain recTree("m_collectionTree");
        recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/user.tkar.hh4bsig5PU0_2_ntuples1_MYSTREAM/*.root");

	int etabin = 13;
    	double etamin   = -1.3, etamax = 1.3;
	
	int phibin = 15;
    	double phimin   = -3.0, phimax = 3.0;

	int ptbins = 12;
	double xbins[] = {0, 4500, 5500, 14500, 25500, 34500,45500,54500,65500,74500,85500,94500,105500};
	TH1::SetDefaultSumw2(true);
	
	TH1* h_num_vs_etaPU = new TH1F("h_num_vs_etaPU", "Numerator Count vs #eta;#eta;Numerator Count"    , etabin, etamin, etamax);
        TH1* h_den_vs_etaPU = new TH1F("h_den_vs_etaPU", "Denominator Count vs #eta;#eta;Denominator Count", etabin, etamin, etamax);
	
	TH1* h_num_vs_phiPU = new TH1F("h_num_vs_phiPU", "Numerator Count vs #eta;#phi [rad];Numerator Count"    , phibin, phimin, phimax);
        TH1* h_den_vs_phiPU = new TH1F("h_den_vs_phiPU", "Denominator Count vs #eta;#phi [rad];Denominator Count", phibin, phimin, phimax);

	TH1* h_num_vs_ptPU = new TH1F("h_num_vs_ptPU", "Numerator Count vs P_{t};P_{t} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_ptPU = new TH1F("h_den_vs_ptPU", "Denominator Count vs P_{t};P_{t} [MeV/c];Denominator Count", ptbins, xbins);


	recTree.Draw("InDeteta>>h_num_vs_etaPU",   num_select, "goff"/*, num_events*/);
        recTree.Draw("InDeteta>>h_den_vs_etaPU",   den_select, "goff"/*, num_events*/);
	h_num_vs_etaPU->Draw("e1");
	h_den_vs_etaPU->Draw("e1");
	TH1* h_pur_vs_etaPU = dynamic_cast<TH1*>(h_num_vs_etaPU->Clone("h_pur_vs_etaPU"));
        h_pur_vs_etaPU->SetTitle("Purity vs #eta;#eta;Purity");
        h_pur_vs_etaPU->Divide(h_num_vs_etaPU, h_den_vs_etaPU, 1.0, 1.0, "B");
        h_pur_vs_etaPU->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_pur_vs_etaPU->SetMarkerSize(0.95);
        h_pur_vs_etaPU->SetMarkerStyle(kOpenTriangleDown);
        h_pur_vs_etaPU->SetMarkerColor(kBlack);

	recTree.Draw("InDetphi0>>h_num_vs_phiPU",   num_select, "goff"/*, num_events*/);
        recTree.Draw("InDetphi0>>h_den_vs_phiPU",   den_select, "goff"/*, num_events*/);
	h_num_vs_phiPU->Draw("e1");
	h_den_vs_phiPU->Draw("e1");
	TH1* h_pur_vs_phiPU = dynamic_cast<TH1*>(h_num_vs_phiPU->Clone("h_pur_vs_phiPU"));
        h_pur_vs_phiPU->SetTitle("Purity vs #phi;#phi [rad];Purity");
        h_pur_vs_phiPU->Divide(h_num_vs_phiPU, h_den_vs_phiPU, 1.0, 1.0, "B");
        h_pur_vs_phiPU->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_pur_vs_phiPU->SetMarkerSize(0.95);
        h_pur_vs_phiPU->SetMarkerStyle(kOpenTriangleDown);
        h_pur_vs_phiPU->SetMarkerColor(kBlack);

	recTree.Draw("InDetpt>>h_num_vs_ptPU",   num_select, "goff"/*, num_events*/);
	recTree.Draw("InDetpt>>h_den_vs_ptPU",   den_select, "goff"/*, num_events*/);
	h_num_vs_ptPU->Draw("e1");
	h_den_vs_ptPU->Draw("e1");
	TH1* h_pur_vs_ptPU = dynamic_cast<TH1*>(h_num_vs_ptPU->Clone("h_pur_vs_ptPU"));
	h_pur_vs_ptPU->SetTitle("Purity vs P_{t};P_{t} [MeV/c];Purity");
	h_pur_vs_ptPU->Divide(h_num_vs_ptPU, h_den_vs_ptPU, 1.0, 1.0, "B");
	h_pur_vs_ptPU->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_pur_vs_ptPU->GetXaxis()->SetRangeUser(2000.,106000.);
	h_pur_vs_ptPU->SetMarkerSize(0.95);
	h_pur_vs_ptPU->SetMarkerStyle(kOpenTriangleDown);
	h_pur_vs_ptPU->SetMarkerColor(kBlack);	
	
	TCanvas* c1 = new TCanvas();	
	h_pur_vs_etaPU->Draw("e1");

	TCanvas* c2 = new TCanvas();	
	h_pur_vs_phiPU->Draw("e1");
	
	TCanvas* c3 = new TCanvas();	
	h_pur_vs_ptPU->Draw("e1");
	char out_file_root[1023];
        sprintf(out_file_root,"%s/%s.root",out_path,output_file_name);
        TFile* output_file = new TFile(out_file_root, "RECREATE");

	h_num_vs_etaPU->Write();
	h_num_vs_phiPU->Write();
	h_num_vs_ptPU->Write();
	h_den_vs_etaPU->Write();
	h_den_vs_phiPU->Write();
	h_den_vs_ptPU->Write();
	h_pur_vs_etaPU->Write();
	h_pur_vs_phiPU->Write();
	h_pur_vs_ptPU->Write();

	output_file->Close();
}

//////////////// Purity for TTT tracks /////////////////

int TTTpurity_Vs_etaphipt(const char* output_file_name = "testpurityTTT", bool save = false)
{
//! Define Cut
TCut num_select= "TTTTBarcode > 0 && abs(TTTTPt)>2000 && abs(TTTTEta)<1.4 && abs(TTTpt)>2000 && abs(TTTeta)<1.4";
TCut den_select= "abs(TTTpt)>2000 && abs(TTTeta)<1.4";

	TChain recTree("m_collectionTree");
        recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/user.tkar.hh4bsig5PU0_2_ntuples1_MYSTREAM/*.root");

	int etabin = 13;
    	double etamin   = -1.3, etamax = 1.3;
	
	int phibin = 15;
    	double phimin   = -3.0, phimax = 3.0;

	int ptbins = 12;
	double xbins[] = {0, 4500, 5500, 14500, 25500, 34500,45500,54500,65500,74500,85500,94500,105500};

	TH1::SetDefaultSumw2(true);
	TH1* h_num_vs_etaPU = new TH1F("h_num_vs_etaPU", "Numerator Count vs #eta;#eta;Numerator Count"    , etabin, etamin, etamax);
        TH1* h_den_vs_etaPU = new TH1F("h_den_vs_etaPU", "Denominator Count vs #eta;#eta;Denominator Count", etabin, etamin, etamax);
	
	TH1* h_num_vs_phiPU = new TH1F("h_num_vs_phiPU", "Numerator Count vs #phi;#phi [rad];Numerator Count"    , phibin, phimin, phimax);
        TH1* h_den_vs_phiPU = new TH1F("h_den_vs_phiPU", "Denominator Count vs #phi;#phi [rad];Denominator Count", phibin, phimin, phimax);

	TH1* h_num_vs_ptPU = new TH1F("h_num_vs_ptPU", "Numerator Count vs P_{t};P_{t} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_ptPU = new TH1F("h_den_vs_ptPU", "Denominator Count vs P_{t};P_{t} [MeV/c];Denominator Count", ptbins, xbins);


	recTree.Draw("TTTeta>>h_num_vs_etaPU",   num_select, "goff"/*, num_events*/);
        recTree.Draw("TTTeta>>h_den_vs_etaPU",   den_select, "goff"/*, num_events*/);
	h_num_vs_etaPU->Draw("e1");
	h_den_vs_etaPU->Draw("e1");
	TH1* h_pur_vs_etaPU = dynamic_cast<TH1*>(h_num_vs_etaPU->Clone("h_pur_vs_etaPU"));
        h_pur_vs_etaPU->SetTitle("Purity vs #eta;#eta;Purity");
        h_pur_vs_etaPU->Divide(h_num_vs_etaPU, h_den_vs_etaPU, 1.0, 1.0, "B");
        h_pur_vs_etaPU->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_pur_vs_etaPU->SetMarkerSize(0.95);
        h_pur_vs_etaPU->SetMarkerStyle(kOpenTriangleDown);
        h_pur_vs_etaPU->SetMarkerColor(kBlack);

	recTree.Draw("TTTphi0>>h_num_vs_phiPU",   num_select, "goff"/*, num_events*/);
        recTree.Draw("TTTphi0>>h_den_vs_phiPU",   den_select, "goff"/*, num_events*/);
	h_num_vs_phiPU->Draw("e1");
	h_den_vs_phiPU->Draw("e1");
	TH1* h_pur_vs_phiPU = dynamic_cast<TH1*>(h_num_vs_phiPU->Clone("h_pur_vs_phiPU"));
        h_pur_vs_phiPU->SetTitle("Purity vs #phi;#phi [rad];Purity");
        h_pur_vs_phiPU->Divide(h_num_vs_phiPU, h_den_vs_phiPU, 1.0, 1.0, "B");
        h_pur_vs_phiPU->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_pur_vs_phiPU->SetMarkerSize(0.95);
        h_pur_vs_phiPU->SetMarkerStyle(kOpenTriangleDown);
        h_pur_vs_phiPU->SetMarkerColor(kBlack);

	recTree.Draw("TTTpt>>h_num_vs_ptPU",   num_select, "goff"/*, num_events*/);
	recTree.Draw("TTTpt>>h_den_vs_ptPU",   den_select, "goff"/*, num_events*/);
	h_num_vs_ptPU->Draw("e1");
	h_den_vs_ptPU->Draw("e1");
	TH1* h_pur_vs_ptPU = dynamic_cast<TH1*>(h_num_vs_ptPU->Clone("h_pur_vs_ptPU"));
	h_pur_vs_ptPU->SetTitle("Purity vs P_{t};P_{t} [MeV/c];Purity");
	h_pur_vs_ptPU->Divide(h_num_vs_ptPU, h_den_vs_ptPU, 1.0, 1.0, "B");
	h_pur_vs_ptPU->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_pur_vs_ptPU->GetXaxis()->SetRangeUser(2000.,106000.);
	h_pur_vs_ptPU->SetMarkerSize(0.95);
	h_pur_vs_ptPU->SetMarkerStyle(kOpenTriangleDown);
	h_pur_vs_ptPU->SetMarkerColor(kBlack);	
	
	
	h_pur_vs_etaPU->Draw("e1");
	h_pur_vs_phiPU->Draw("e1");
	h_pur_vs_ptPU->Draw("e1");
	char out_file_root[1023];
        sprintf(out_file_root,"%s/%s.root",out_path,output_file_name);
        TFile* output_file = new TFile(out_file_root, "RECREATE");

	h_num_vs_etaPU->Write();
	h_num_vs_phiPU->Write();
	h_num_vs_ptPU->Write();
	h_den_vs_etaPU->Write();
	h_den_vs_phiPU->Write();
	h_den_vs_ptPU->Write();
	h_pur_vs_etaPU->Write();
	h_pur_vs_phiPU->Write();
	h_pur_vs_ptPU->Write();

	output_file->Close();
}

/////////////// write purity to pdf /////////////////
int write_topdf(const char* output_file_name = "purity_InDetTTT_hh4b")
{

	char out_file_open[1023];
        sprintf(out_file_open,"%s/%s.pdf(",out_path,output_file_name);
        char out_file_[1023];
        sprintf(out_file_,"%s/%s.pdf",out_path,output_file_name);
        char out_file_close[1023];
        sprintf(out_file_close,"%s/%s.pdf)",out_path,output_file_name);
	//!InDet tracks
	TFile* f = TFile::Open("./plots/purity/testpurity.root");
	TH1D* h_eta 	= (TH1D*)f->Get("h_pur_vs_etaPU");
	TH1D* h_pt 	= (TH1D*)f->Get("h_pur_vs_ptPU");
	TH1D* h_phi	= (TH1D*)f->Get("h_pur_vs_phiPU");

	//! TTT tracks
	TFile* f0 = TFile::Open("./plots/purity/testpurityTTT.root");
	TH1D* h0_eta 	= (TH1D*)f0->Get("h_pur_vs_etaPU");
	TH1D* h0_pt 	= (TH1D*)f0->Get("h_pur_vs_ptPU");
	TH1D* h0_phi	= (TH1D*)f0->Get("h_pur_vs_phiPU");


	h_eta->SetStats(0);
	h_pt->SetStats(0);
       	h_phi->SetStats(0);
      
	h0_eta->SetStats(0);
        h0_pt->SetStats(0);
        h0_phi->SetStats(0);
	
	// SET Markercolour
	h_eta->SetMarkerColor(kRed);
	h_pt->SetMarkerColor(kRed);
	h_phi->SetMarkerColor(kRed);
	h0_eta->SetMarkerColor(kBlue);
        h0_pt->SetMarkerColor(kBlue);
        h0_phi->SetMarkerColor(kBlue);
	
	//Marker Size	
	h_eta->SetMarkerSize(1.8);
	h_pt->SetMarkerSize(1.8);
	h_phi->SetMarkerSize(1.8);

	h0_eta->SetMarkerSize(1.8);
        h0_pt->SetMarkerSize(1.8);
        h0_phi->SetMarkerSize(1.8);

	//Marker Style	
	h_eta->SetMarkerStyle(kFullTriangleDown);
	h_pt->SetMarkerStyle(kFullTriangleDown);
	h_phi->SetMarkerStyle(kFullTriangleDown);

	h0_eta->SetMarkerStyle(kFullTriangleDown);
        h0_pt->SetMarkerStyle(kFullTriangleDown);
        h0_phi->SetMarkerStyle(kFullTriangleDown);
	
	h_eta->GetYaxis()->SetTitleOffset(.85);
	h_pt->GetYaxis()->SetTitleOffset(.85);
	h_phi->GetYaxis()->SetTitleOffset(.85);

	h0_eta->GetYaxis()->SetTitleOffset(.85);
        h0_pt->GetYaxis()->SetTitleOffset(.85);
        h0_phi->GetYaxis()->SetTitleOffset(.85);
	
	h_eta->GetYaxis()->SetTitleSize(.05);
	h_pt->GetYaxis()->SetTitleSize(.05);
	h_phi->GetYaxis()->SetTitleSize(.05);

	h0_eta->GetYaxis()->SetTitleSize(.05);
        h0_pt->GetYaxis()->SetTitleSize(.05);
        h0_phi->GetYaxis()->SetTitleSize(.05);

	h_eta->GetXaxis()->SetTitleOffset(.85);
	h_pt->GetXaxis()->SetTitleOffset(.85);
	h_phi->GetXaxis()->SetTitleOffset(.85);

	h0_eta->GetXaxis()->SetTitleOffset(.85);
        h0_pt->GetXaxis()->SetTitleOffset(.85);
        h0_phi->GetXaxis()->SetTitleOffset(.85);
	

	h_eta->GetXaxis()->SetTitleSize(.05);
	h_pt->GetXaxis()->SetTitleSize(.05);
	h_phi->GetXaxis()->SetTitleSize(.05);

	h0_eta->GetXaxis()->SetTitleSize(.05);
        h0_pt->GetXaxis()->SetTitleSize(.05);
        h0_phi->GetXaxis()->SetTitleSize(.05);
	
/*	h_eta->GetXaxis()->SetTitle("#eta_{gen}");
	h_pt->GetXaxis()->SetTitle("#eta_{gen}");
	h_phi->GetXaxis()->SetTitle("#eta_{gen}");

	h0_eta->GetXaxis()->SetTitle("#eta_{gen}");
        h0_pt->GetXaxis()->SetTitle("#eta_{gen}");
        h0_phi->GetXaxis()->SetTitle("#eta_{gen}");
*/	
	
	TCanvas * C = new TCanvas();
	gStyle->SetOptStat(0);

	C->SetGridx();
	C->SetGridy();
	C->SetTickx();
	C->SetTicky();
	h_eta->Draw();
	//C->SetLogx();
	C->Print(out_file_open, "pdf");
	h0_eta->Draw();
	C->Print(out_file_,"pdf");

	h_pt->Draw();
	C->Print(out_file_, "pdf");
	h0_pt->Draw();
	C->Print(out_file_,"pdf");
	
	h_phi->Draw();
	C->Print(out_file_, "pdf");
	h0_phi->Draw();
	C->Print(out_file_,"pdf");
	
	Double_t x1= 0.7,y1= 0.75, x2 = 0.9, y2 = 0.9;
	
	h_eta->GetYaxis()->SetRangeUser(0.6,1.1);
	h_eta->Draw();
	h0_eta->Draw("same");
	TLegend *leg1=new TLegend(x1,y1,x2,y2,"");
	leg1->SetFillColor(kWhite);
	leg1->SetBorderSize(0);
        leg1->AddEntry(h_eta,"InDet tracks");
        leg1->AddEntry(h0_eta,"TTT tracks");
        leg1->Draw();
	C->Print(out_file_,"pdf");
	
	h_pt->GetYaxis()->SetRangeUser(0.6,1.1);
	h_pt->Draw();
	h0_pt->Draw("same");
	TLegend *leg2=new TLegend(x1,y1,x2,y2,"");
	leg2->SetFillColor(kWhite);
	leg2->SetBorderSize(0);
	leg2->AddEntry(h_pt,"InDet tracks");
	leg2->AddEntry(h0_pt,"TTT tracks");
	leg2->Draw();
	C->Print(out_file_,"pdf");

	h_phi->GetYaxis()->SetRangeUser(0.6,1.1);
	h_phi->Draw();
	h0_phi->Draw("same");
	TLegend *leg3=new TLegend(x1,y1,x2,y2,"");
	leg3->SetFillColor(kWhite);
	leg3->SetBorderSize(0);
        leg3->AddEntry(h_phi,"InDet tracks");
        leg3->AddEntry(h0_phi,"TTT tracks");
        leg3->Draw();
	C->Print(out_file_close,"pdf");
return 0;
}
