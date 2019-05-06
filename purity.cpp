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

int InDetpurity_Vs_etaphipt(const char* output_file_name = "purm1000_3ntuple3InDetdR0.01_eta1.4", bool save = false)
//int InDetpurity_Vs_etaphipt(const char* output_file_name = "newpurity_dR0.1", bool save = false)
{
//! Define Cut
//TCut num_select= "InDetTBarcode > 0 && abs(InDetTPt)>2000 && abs(InDetTEta)<1.4 && abs(InDetpt)>2000 && abs(InDeteta)<1.4 && abs(InDetz0) < 100";
//TCut num_select= "InDetTBarcode > 0 && abs(InDetpt)>2000 && abs(InDeteta)<1.4";
//TCut den_select= "abs(InDetpt)>2000 && abs(InDeteta)<1.4 && abs(InDetz0)";
TCut num_select= "InDetTBarcode > 0 && abs(InDetpt)>2000 && abs(InDeteta)<1.4 && abs(InDetz0) < 100 ";
TCut den_select= "abs(InDetpt)>2000 && abs(InDeteta)<1.4 && abs(InDetz0) < 100 ";
TCut num1_select= "InDetTTTtruthBarcode > 0 && abs(InDetpt)>2000 && abs(InDeteta)<1.4 && abs(InDetz0) < 100 ";
	
	TChain recTree("m_collectionTree");
        //recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/user.tkar.hh4bsig5PU0_3_ntuples1_MYSTREAM/*.root");
	//dR=0.01
        //recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/user.tkar.hh4bsig5PU0_3_ntuples2_MYSTREAM/*.root");
        //recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/dpg2019/user.tkar.hh4bsig5PU0_4_ntuples2_MYSTREAM/*.root");
	//! for the fair comparison (truth container contains only those particles that leave a hit in the outermost layer of the triplet)
	//recTree.Add("/media/tamasi/DriveT1/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/dpg2019/user.tkar.hh4b_m1000sig5PU0_3_ntuples1_MYSTREAM/*.root");
	//recTree.Add("/media/tamasi/DriveT1/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/dpg2019/user.tkar.hh4b_m1000sig5PU0_3_ntuples2_MYSTREAM/*.root");
	recTree.Add("/media/tamasi/DriveT1/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/dpg2019/user.tkar.hh4b_m1000sig5PU0_3_ntuples3_MYSTREAM/*.root");

	int etabin = 13;
    	double etamin   = -1.3, etamax = 1.3;
	
	int phibin = 16;
    	double phimin   = -3.2, phimax = 3.2;

	//int ptbins = 12;
	//double xbins[] = {1000, 3500, 7500, 15000, 25000, 35000, 45000, 55000, 65000, 75000, 85000, 95000, 105000 };	
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
	TH1::SetDefaultSumw2(true);
	
	TH1* h_num_vs_etaPU = new TH1F("h_num_vs_etaPU", "Numerator Count vs #eta;#eta;Numerator Count"    , etabin, etamin, etamax);
        TH1* h_den_vs_etaPU = new TH1F("h_den_vs_etaPU", "Denominator Count vs #eta;#eta;Denominator Count", etabin, etamin, etamax);
	
	TH1* h_num_vs_phiPU = new TH1F("h_num_vs_phiPU", "Numerator Count vs #eta;#phi [rad];Numerator Count"    , phibin, phimin, phimax);
        TH1* h_den_vs_phiPU = new TH1F("h_den_vs_phiPU", "Denominator Count vs #eta;#phi [rad];Denominator Count", phibin, phimin, phimax);

	TH1* h_num_vs_ptPU = new TH1F("h_num_vs_ptPU", "Numerator Count vs P_{t};P_{t} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_ptPU = new TH1F("h_den_vs_ptPU", "Denominator Count vs P_{t};P_{t} [MeV/c];Denominator Count", ptbins, xbins);


	recTree.Draw("InDeteta>>h_num_vs_etaPU",   num_select, "goff"/*, num_events*/);
        recTree.Draw("InDeteta>>h_den_vs_etaPU",   den_select, "goff"/*, num_events*/);
	//recTree.Draw("InDetTEta>>h_num_vs_etaPU",   num_select, "goff"/*, num_events*/);
        //recTree.Draw("InDetTEta>>h_den_vs_etaPU",   den_select, "goff"/*, num_events*/);
	h_num_vs_etaPU->Draw("e1");
	h_den_vs_etaPU->Draw("e1");
	TH1* h_pur_vs_etaPU = dynamic_cast<TH1*>(h_num_vs_etaPU->Clone("h_pur_vs_etaPU"));
        h_pur_vs_etaPU->SetTitle("Purity vs #eta;#eta;Purity");
        h_pur_vs_etaPU->Divide(h_num_vs_etaPU, h_den_vs_etaPU, 1.0, 1.0, "B");
        h_pur_vs_etaPU->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_pur_vs_etaPU->SetMarkerSize(0.95);
        h_pur_vs_etaPU->SetMarkerStyle(kFullTriangleDown);
        h_pur_vs_etaPU->SetMarkerColor(kBlack);

	recTree.Draw("InDetphi0>>h_num_vs_phiPU",   num_select, "goff"/*, num_events*/);
        recTree.Draw("InDetphi0>>h_den_vs_phiPU",   den_select, "goff"/*, num_events*/);
//	recTree.Draw("InDetTPhi0>>h_num_vs_phiPU",   num_select, "goff"/*, num_events*/);
//      recTree.Draw("InDetTPhi0>>h_den_vs_phiPU",   den_select, "goff"/*, num_events*/);
	h_num_vs_phiPU->Draw("e1");
	h_den_vs_phiPU->Draw("e1");
	TH1* h_pur_vs_phiPU = dynamic_cast<TH1*>(h_num_vs_phiPU->Clone("h_pur_vs_phiPU"));
        h_pur_vs_phiPU->SetTitle("Purity vs #phi;#phi [rad];Purity");
        h_pur_vs_phiPU->Divide(h_num_vs_phiPU, h_den_vs_phiPU, 1.0, 1.0, "B");
        h_pur_vs_phiPU->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_pur_vs_phiPU->SetMarkerSize(0.95);
        h_pur_vs_phiPU->SetMarkerStyle(kFullTriangleDown);
        h_pur_vs_phiPU->SetMarkerColor(kBlack);

	recTree.Draw("InDetpt>>h_num_vs_ptPU",   num_select, "goff"/*, num_events*/);
	recTree.Draw("InDetpt>>h_den_vs_ptPU",   den_select, "goff"/*, num_events*/);
	//recTree.Draw("InDetTPt>>h_num_vs_ptPU",   num_select, "goff"/*, num_events*/);
	//recTree.Draw("InDetTPt>>h_den_vs_ptPU",   den_select, "goff"/*, num_events*/);
	h_num_vs_ptPU->Draw("e1");
	h_den_vs_ptPU->Draw("e1");
	TH1* h_pur_vs_ptPU = dynamic_cast<TH1*>(h_num_vs_ptPU->Clone("h_pur_vs_ptPU"));
	h_pur_vs_ptPU->SetTitle("Purity vs P_{t};P_{t} [MeV/c];Purity");
	h_pur_vs_ptPU->Divide(h_num_vs_ptPU, h_den_vs_ptPU, 1.0, 1.0, "B");
	h_pur_vs_ptPU->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_pur_vs_ptPU->GetXaxis()->SetRangeUser(2000.,106000.);
	h_pur_vs_ptPU->SetMarkerSize(0.95);
	h_pur_vs_ptPU->SetMarkerStyle(kFullTriangleDown);
	h_pur_vs_ptPU->SetMarkerColor(kBlack);	
	
	//! TTT truth matched	
	TH1* h_num1_vs_etaPU = new TH1F("h_num1_vs_etaPU", "Numerator Count vs #eta;#eta;Numerator Count"    , etabin, etamin, etamax);
        TH1* h_den1_vs_etaPU = new TH1F("h_den1_vs_etaPU", "Denominator Count vs #eta;#eta;Denominator Count", etabin, etamin, etamax);
	
	TH1* h_num1_vs_phiPU = new TH1F("h_num1_vs_phiPU", "Numerator Count vs #eta;#phi [rad];Numerator Count"    , phibin, phimin, phimax);
        TH1* h_den1_vs_phiPU = new TH1F("h_den1_vs_phiPU", "Denominator Count vs #eta;#phi [rad];Denominator Count", phibin, phimin, phimax);

	TH1* h_num1_vs_ptPU = new TH1F("h_num1_vs_ptPU", "Numerator Count vs P_{t};P_{t} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den1_vs_ptPU = new TH1F("h_den1_vs_ptPU", "Denominator Count vs P_{t};P_{t} [MeV/c];Denominator Count", ptbins, xbins);


	recTree.Draw("InDeteta>>h_num1_vs_etaPU",   num1_select, "goff"/*, num1_events*/);
        recTree.Draw("InDeteta>>h_den1_vs_etaPU",   den_select, "goff"/*, num1_events*/);
	//recTree.Draw("InDetTEta>>h_num1_vs_etaPU",   num1_select, "goff"/*, num1_events*/);
        //recTree.Draw("InDetTEta>>h_den1_vs_etaPU",   den1_select, "goff"/*, num1_events*/);
	h_num1_vs_etaPU->Draw("e1");
	h_den1_vs_etaPU->Draw("e1");
	TH1* h_pur1_vs_etaPU = dynamic_cast<TH1*>(h_num1_vs_etaPU->Clone("h_pur1_vs_etaPU"));
        h_pur1_vs_etaPU->SetTitle("Purity vs #eta;#eta;Purity");
        h_pur1_vs_etaPU->Divide(h_num1_vs_etaPU, h_den1_vs_etaPU, 1.0, 1.0, "B");
        h_pur1_vs_etaPU->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_pur1_vs_etaPU->SetMarkerSize(0.95);
        h_pur1_vs_etaPU->SetMarkerStyle(kOpenTriangleDown);
        h_pur1_vs_etaPU->SetMarkerColor(kBlack);

	recTree.Draw("InDetphi0>>h_num1_vs_phiPU",   num1_select, "goff"/*, num1_events*/);
        recTree.Draw("InDetphi0>>h_den1_vs_phiPU",   den_select, "goff"/*, num1_events*/);
//	recTree.Draw("InDetTPhi0>>h_num1_vs_phiPU",   num1_select, "goff"/*, num1_events*/);
//      recTree.Draw("InDetTPhi0>>h_den1_vs_phiPU",   den1_select, "goff"/*, num1_events*/);
	h_num1_vs_phiPU->Draw("e1");
	h_den1_vs_phiPU->Draw("e1");
	TH1* h_pur1_vs_phiPU = dynamic_cast<TH1*>(h_num1_vs_phiPU->Clone("h_pur1_vs_phiPU"));
        h_pur1_vs_phiPU->SetTitle("Purity vs #phi;#phi [rad];Purity");
        h_pur1_vs_phiPU->Divide(h_num1_vs_phiPU, h_den1_vs_phiPU, 1.0, 1.0, "B");
        h_pur1_vs_phiPU->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_pur1_vs_phiPU->SetMarkerSize(0.95);
        h_pur1_vs_phiPU->SetMarkerStyle(kOpenTriangleDown);
        h_pur1_vs_phiPU->SetMarkerColor(kBlack);

	recTree.Draw("InDetpt>>h_num1_vs_ptPU",   num1_select, "goff"/*, num1_events*/);
	recTree.Draw("InDetpt>>h_den1_vs_ptPU",   den_select, "goff"/*, num1_events*/);
	//recTree.Draw("InDetTPt>>h_num1_vs_ptPU",   num1_select, "goff"/*, num1_events*/);
	//recTree.Draw("InDetTPt>>h_den1_vs_ptPU",   den1_select, "goff"/*, num1_events*/);
	h_num1_vs_ptPU->Draw("e1");
	h_den1_vs_ptPU->Draw("e1");
	TH1* h_pur1_vs_ptPU = dynamic_cast<TH1*>(h_num1_vs_ptPU->Clone("h_pur1_vs_ptPU"));
	h_pur1_vs_ptPU->SetTitle("Purity vs P_{t};P_{t} [MeV/c];Purity");
	h_pur1_vs_ptPU->Divide(h_num1_vs_ptPU, h_den1_vs_ptPU, 1.0, 1.0, "B");
	h_pur1_vs_ptPU->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_pur1_vs_ptPU->GetXaxis()->SetRangeUser(2000.,106000.);
	h_pur1_vs_ptPU->SetMarkerSize(0.95);
	h_pur1_vs_ptPU->SetMarkerStyle(kOpenTriangleDown);
	h_pur1_vs_ptPU->SetMarkerColor(kBlack);	
	
	TCanvas* c1 = new TCanvas();	
	h_pur_vs_etaPU->Draw("e1");
	h_pur1_vs_etaPU->Draw("e1");

	TCanvas* c2 = new TCanvas();	
	h_pur_vs_phiPU->Draw("e1");
	h_pur1_vs_phiPU->Draw("e1");
	
	TCanvas* c3 = new TCanvas();	
	h_pur_vs_ptPU->Draw("e1");
	h_pur1_vs_ptPU->Draw("e1");
	
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
	//! TTT truth matched
	h_num1_vs_etaPU->Write();
	h_num1_vs_phiPU->Write();
	h_num1_vs_ptPU->Write();
	h_den1_vs_etaPU->Write();
	h_den1_vs_phiPU->Write();
	h_den1_vs_ptPU->Write();
	h_pur1_vs_etaPU->Write();
	h_pur1_vs_phiPU->Write();
	h_pur1_vs_ptPU->Write();

	output_file->Close();
}

//////////////// Purity for TTT tracks /////////////////

int TTTpurity_Vs_etaphipt(const char* output_file_name = "purm1000_3ntuple1_TTTdR0.01_eta1.2", bool save = false)
{
//! Define Cut
//TCut num_select= "TTTTBarcode > 0 && abs(TTTTPt)>2000 && abs(TTTTEta)<1.4 && abs(TTTpt)>2000 && abs(TTTeta)<1.4  && abs(TTTz0) < 100";
//TCut num_select= "TTTTBarcode > 0 && abs(TTTpt)>2000 && abs(TTTeta)<1.4";
//TCut den_select= "abs(TTTpt)>2000 && abs(TTTeta)<1.4";
TCut num_select= "TTTTBarcode > 0 && abs(TTTpt)>2000 && abs(TTTeta)<1.2  && abs(TTTz0) < 100";
TCut den_select= "abs(TTTpt)>2000 && abs(TTTeta)<1.2 && abs(TTTz0) < 100";

	TChain recTree("m_collectionTree");
        //recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/user.tkar.hh4bsig5PU0_3_ntuples1_MYSTREAM/*.root");
	// dR=0.01
        //recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/user.tkar.hh4bsig5PU0_3_ntuples2_MYSTREAM/*.root");
        //recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/dpg2019/user.tkar.hh4bsig5PU0_4_ntuples2_MYSTREAM/*.root");
	//! for the fair comparison (truth container contains only those particles that leave a hit in the outermost layer of the triplet)
	recTree.Add("/media/tamasi/DriveT1/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/dpg2019/user.tkar.hh4b_m1000sig5PU0_3_ntuples1_MYSTREAM/*.root");

	int etabin = 13;
    	double etamin   = -1.3, etamax = 1.3;
	
	int phibin = 16;
    	double phimin   = -3.2, phimax = 3.2;

	//int ptbins = 12;
	//double xbins[] = {1000, 3500, 7500, 15000, 25000, 35000, 45000, 55000, 65000, 75000, 85000, 95000, 105000 };
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

	TH1::SetDefaultSumw2(true);
	TH1* h_num_vs_etaPU = new TH1F("h_num_vs_etaPU", "Numerator Count vs #eta;#eta;Numerator Count"    , etabin, etamin, etamax);
        TH1* h_den_vs_etaPU = new TH1F("h_den_vs_etaPU", "Denominator Count vs #eta;#eta;Denominator Count", etabin, etamin, etamax);
	
	TH1* h_num_vs_phiPU = new TH1F("h_num_vs_phiPU", "Numerator Count vs #phi;#phi [rad];Numerator Count"    , phibin, phimin, phimax);
        TH1* h_den_vs_phiPU = new TH1F("h_den_vs_phiPU", "Denominator Count vs #phi;#phi [rad];Denominator Count", phibin, phimin, phimax);

	TH1* h_num_vs_ptPU = new TH1F("h_num_vs_ptPU", "Numerator Count vs P_{t};P_{t} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_ptPU = new TH1F("h_den_vs_ptPU", "Denominator Count vs P_{t};P_{t} [MeV/c];Denominator Count", ptbins, xbins);


	recTree.Draw("TTTeta>>h_num_vs_etaPU",   num_select, "goff"/*, num_events*/);
        recTree.Draw("TTTeta>>h_den_vs_etaPU",   den_select, "goff"/*, num_events*/);
	//recTree.Draw("TTTTEta>>h_num_vs_etaPU",   num_select, "goff"/*, num_events*/);
        //recTree.Draw("TTTTEta>>h_den_vs_etaPU",   den_select, "goff"/*, num_events*/);
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
	//recTree.Draw("TTTTPhi0>>h_num_vs_phiPU",   num_select, "goff"/*, num_events*/);
        //recTree.Draw("TTTTPhi0>>h_den_vs_phiPU",   den_select, "goff"/*, num_events*/);
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
//	recTree.Draw("TTTTPt>>h_num_vs_ptPU",   num_select, "goff"/*, num_events*/);
//	recTree.Draw("TTTTPt>>h_den_vs_ptPU",   den_select, "goff"/*, num_events*/);
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


//////////////// Purity for TTT tracks /////////////////

int newTTTpurity_Vs_etaphipt(const char* output_file_name = "purm1000_3ntuple1_TTTBMatched_eta1.2", bool save = false)
{
//! Define Cut
//TCut num_select= "mTTTTBarcode > 0 && abs(mTTTTPt)>2000 && abs(mTTTTEta)<1.4 && abs(TTTpt)>2000 && abs(TTTeta)<1.4  && abs(TTTz0) < 100";
TCut num_select= "mTTTTBarcode > 0  && abs(TTTpt)>2000 && abs(TTTeta)<1.2  && abs(TTTz0) < 100";
TCut den_select= "mTTTTBarcode >= 0 && abs(TTTpt)>2000 && abs(TTTeta)<1.2 && abs(TTTz0) < 100";

	TChain recTree("m_collectionTree");
        //recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/user.tkar.hh4bsig5PU0_3_ntuples2_MYSTREAM/*.root");
        //recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/dpg2019/user.tkar.hh4bsig5PU0_4_ntuples2_MYSTREAM/*.root");
	//! for the fair comparison (truth container contains only those particles that leave a hit in the outermost layer of the triplet)
	recTree.Add("/media/tamasi/DriveT1/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/dpg2019/user.tkar.hh4b_m1000sig5PU0_3_ntuples1_MYSTREAM/*.root");

	int etabin = 13;
    	double etamin   = -1.3, etamax = 1.3;
	
	int phibin = 16;
    	double phimin   = -3.2, phimax = 3.2;

	//int ptbins = 12;
	//double xbins[] = {1000, 3500, 7500, 15000, 25000, 35000, 45000, 55000, 65000, 75000, 85000, 95000, 105000 };
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
int write_topdf(const char* output_file_name = "purity_InDetTTT_hh4b_dR0.1_noZ0")
{

	char out_file_open[1023];
        sprintf(out_file_open,"%s/%s.pdf(",out_path,output_file_name);
        char out_file_[1023];
        sprintf(out_file_,"%s/%s.pdf",out_path,output_file_name);
        char out_file_close[1023];
        sprintf(out_file_close,"%s/%s.pdf)",out_path,output_file_name);
	//!InDet tracks
	//TFile* f = TFile::Open("./plots/purity/purity_dR0.1.root");
	TFile* f = TFile::Open("./plots/purity/purity_dR0.1_noZ0.root");
	//TFile* f = TFile::Open("./plots/purity/purity_dR0.01.root");
	TH1D* h_eta 	= (TH1D*)f->Get("h_pur_vs_etaPU");
	TH1D* h_pt 	= (TH1D*)f->Get("h_pur_vs_ptPU");
	TH1D* h_phi	= (TH1D*)f->Get("h_pur_vs_phiPU");

	//! TTT tracks
	//TFile* f0 = TFile::Open("./plots/purity/purityTTT_dR0.1.root");
	TFile* f0 = TFile::Open("./plots/purity/purityTTT_dR0.1_noZ0.root");
	//TFile* f0 = TFile::Open("./plots/purity/purityTTT_dR0.01.root");
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
/////////////// write purity to pdf different matching methods/////////////////
//int newwrite_topdf(const char* output_file_name = "purity_InDetTTT_hh4b_all")
int newwrite_topdf(const char* output_file_name = "newpurity_InDetTTT_hh4b_all")
{

	char out_file_open[1023];
        sprintf(out_file_open,"%s/%s.pdf(",out_path,output_file_name);
        char out_file_[1023];
        sprintf(out_file_,"%s/%s.pdf",out_path,output_file_name);
        char out_file_close[1023];
        sprintf(out_file_close,"%s/%s.pdf)",out_path,output_file_name);
	//!InDet tracks
	TFile* fa = TFile::Open("./plots/purity/newpurity_dR0.01.root");
	TH1D* ha_eta 	= (TH1D*)fa->Get("h_pur_vs_etaPU");
	TH1D* ha_pt 	= (TH1D*)fa->Get("h_pur_vs_ptPU");
	TH1D* ha_phi	= (TH1D*)fa->Get("h_pur_vs_phiPU");
	TFile* fb = TFile::Open("./plots/purity/newpurity_dR0.1.root");
	TH1D* hb_eta 	= (TH1D*)fb->Get("h_pur_vs_etaPU");
	TH1D* hb_pt 	= (TH1D*)fb->Get("h_pur_vs_ptPU");
	TH1D* hb_phi	= (TH1D*)fb->Get("h_pur_vs_phiPU");
	/*TFile* fc = TFile::Open("./plots/purity/purity_barcode.root");
	TH1D* hc_eta 	= (TH1D*)fc->Get("h_pur_vs_etaPU");
	TH1D* hc_pt 	= (TH1D*)fc->Get("h_pur_vs_ptPU");
	TH1D* hc_phi	= (TH1D*)fc->Get("h_pur_vs_phiPU");*/

	//! TTT tracks
	TFile* f0 = TFile::Open("./plots/purity/newpurityTTT_dR0.01.root");
	TH1D* h0_eta 	= (TH1D*)f0->Get("h_pur_vs_etaPU");
	TH1D* h0_pt 	= (TH1D*)f0->Get("h_pur_vs_ptPU");
	TH1D* h0_phi	= (TH1D*)f0->Get("h_pur_vs_phiPU");
	TFile* f1 = TFile::Open("./plots/purity/newpurityTTT_dR0.1.root");
	TH1D* h1_eta 	= (TH1D*)f1->Get("h_pur_vs_etaPU");
	TH1D* h1_pt 	= (TH1D*)f1->Get("h_pur_vs_ptPU");
	TH1D* h1_phi	= (TH1D*)f1->Get("h_pur_vs_phiPU");
	TFile* f2 = TFile::Open("./plots/purity/newpurityTTT_barcode.root");
	TH1D* h2_eta 	= (TH1D*)f2->Get("h_pur_vs_etaPU");
	TH1D* h2_pt 	= (TH1D*)f2->Get("h_pur_vs_ptPU");
	TH1D* h2_phi	= (TH1D*)f2->Get("h_pur_vs_phiPU");


	ha_eta->SetStats(0);
	ha_pt->SetStats(0);
       	ha_phi->SetStats(0);
      
	h0_eta->SetStats(0);
        h0_pt->SetStats(0);
        h0_phi->SetStats(0);
	
	hb_eta->SetStats(0);
	hb_pt->SetStats(0);
       	hb_phi->SetStats(0);
      
	h1_eta->SetStats(0);
        h1_pt->SetStats(0);
        h1_phi->SetStats(0);
	
	/*hc_eta->SetStats(0);
	hc_pt->SetStats(0);
       	hc_phi->SetStats(0);
      */
	h2_eta->SetStats(0);
        h2_pt->SetStats(0);
        h2_phi->SetStats(0);
	
	// SET Markercolour
	ha_eta->SetMarkerColor(kRed);
	ha_pt->SetMarkerColor(kRed);
	ha_phi->SetMarkerColor(kRed);
	h0_eta->SetMarkerColor(kBlue);
        h0_pt->SetMarkerColor(kBlue);
        h0_phi->SetMarkerColor(kBlue);
	
	hb_eta->SetMarkerColor(kRed);
	hb_pt->SetMarkerColor(kRed);
	hb_phi->SetMarkerColor(kRed);
	h1_eta->SetMarkerColor(kBlue);
        h1_pt->SetMarkerColor(kBlue);
        h1_phi->SetMarkerColor(kBlue);
	
	/*hc_eta->SetMarkerColor(kRed);
	hc_pt->SetMarkerColor(kRed);
	hc_phi->SetMarkerColor(kRed);
	*/h2_eta->SetMarkerColor(kBlue);
        h2_pt->SetMarkerColor(kBlue);
        h2_phi->SetMarkerColor(kBlue);
	
	//Marker Size	
	ha_eta->SetMarkerSize(1.8);
	ha_pt->SetMarkerSize(1.8);
	ha_phi->SetMarkerSize(1.8);

	h0_eta->SetMarkerSize(1.8);
        h0_pt->SetMarkerSize(1.8);
        h0_phi->SetMarkerSize(1.8);
	
	hb_eta->SetMarkerSize(1.8);
	hb_pt->SetMarkerSize(1.8);
	hb_phi->SetMarkerSize(1.8);

	h1_eta->SetMarkerSize(1.8);
        h1_pt->SetMarkerSize(1.8);
        h1_phi->SetMarkerSize(1.8);
	
	/*hc_eta->SetMarkerSize(1.8);
	hc_pt->SetMarkerSize(1.8);
	hc_phi->SetMarkerSize(1.8);
*/
	h2_eta->SetMarkerSize(1.8);
        h2_pt->SetMarkerSize(1.8);
        h2_phi->SetMarkerSize(1.8);

	//Marker Style	
	ha_eta->SetMarkerStyle(kFullTriangleDown);
	ha_pt->SetMarkerStyle(kFullTriangleDown);
	ha_phi->SetMarkerStyle(kFullTriangleDown);

	h0_eta->SetMarkerStyle(kFullTriangleDown);
        h0_pt->SetMarkerStyle(kFullTriangleDown);
        h0_phi->SetMarkerStyle(kFullTriangleDown);
	
	hb_eta->SetMarkerStyle(kOpenTriangleDown);
	hb_pt->SetMarkerStyle(kOpenTriangleDown);
	hb_phi->SetMarkerStyle(kOpenTriangleDown);

	h1_eta->SetMarkerStyle(kOpenTriangleDown);
        h1_pt->SetMarkerStyle(kOpenTriangleDown);
        h1_phi->SetMarkerStyle(kOpenTriangleDown);
	
	/*hc_eta->SetMarkerStyle(kFullCircle);
	hc_pt->SetMarkerStyle(kFullCircle);
	hc_phi->SetMarkerStyle(kFullCircle);
*/
	h2_eta->SetMarkerStyle(kFullCircle);
        h2_pt->SetMarkerStyle(kFullCircle);
        h2_phi->SetMarkerStyle(kFullCircle);
	
	ha_eta->GetYaxis()->SetTitleOffset(.85);
	ha_pt->GetYaxis()->SetTitleOffset(.85);
	ha_phi->GetYaxis()->SetTitleOffset(.85);
	h0_eta->GetYaxis()->SetTitleOffset(.85);
        h0_pt->GetYaxis()->SetTitleOffset(.85);
        h0_phi->GetYaxis()->SetTitleOffset(.85);
	hb_eta->GetYaxis()->SetTitleOffset(.85);
	hb_pt->GetYaxis()->SetTitleOffset(.85);
	hb_phi->GetYaxis()->SetTitleOffset(.85);
	h1_eta->GetYaxis()->SetTitleOffset(.85);
        h1_pt->GetYaxis()->SetTitleOffset(.85);
        h1_phi->GetYaxis()->SetTitleOffset(.85);
	/*hc_eta->GetYaxis()->SetTitleOffset(.85);
	hc_pt->GetYaxis()->SetTitleOffset(.85);
	hc_phi->GetYaxis()->SetTitleOffset(.85);
	*/h2_eta->GetYaxis()->SetTitleOffset(.85);
        h2_pt->GetYaxis()->SetTitleOffset(.85);
        h2_phi->GetYaxis()->SetTitleOffset(.85);
	
	ha_eta->GetYaxis()->SetTitleSize(.05);
	ha_pt->GetYaxis()->SetTitleSize(.05);
	ha_phi->GetYaxis()->SetTitleSize(.05);
	h0_eta->GetYaxis()->SetTitleSize(.05);
        h0_pt->GetYaxis()->SetTitleSize(.05);
        h0_phi->GetYaxis()->SetTitleSize(.05);
	hb_eta->GetYaxis()->SetTitleSize(.05);
	hb_pt->GetYaxis()->SetTitleSize(.05);
	hb_phi->GetYaxis()->SetTitleSize(.05);
	h1_eta->GetYaxis()->SetTitleSize(.05);
        h1_pt->GetYaxis()->SetTitleSize(.05);
        h1_phi->GetYaxis()->SetTitleSize(.05);
	/*hc_eta->GetYaxis()->SetTitleSize(.05);
	hc_pt->GetYaxis()->SetTitleSize(.05);
	hc_phi->GetYaxis()->SetTitleSize(.05);
	*/h2_eta->GetYaxis()->SetTitleSize(.05);
        h2_pt->GetYaxis()->SetTitleSize(.05);
        h2_phi->GetYaxis()->SetTitleSize(.05);

	ha_eta->GetXaxis()->SetTitleOffset(.85);
	ha_pt->GetXaxis()->SetTitleOffset(.85);
	ha_phi->GetXaxis()->SetTitleOffset(.85);
	h0_eta->GetXaxis()->SetTitleOffset(.85);
        h0_pt->GetXaxis()->SetTitleOffset(.85);
        h0_phi->GetXaxis()->SetTitleOffset(.85);
	hb_eta->GetXaxis()->SetTitleOffset(.85);
	hb_pt->GetXaxis()->SetTitleOffset(.85);
	hb_phi->GetXaxis()->SetTitleOffset(.85);
	h1_eta->GetXaxis()->SetTitleOffset(.85);
        h1_pt->GetXaxis()->SetTitleOffset(.85);
        h1_phi->GetXaxis()->SetTitleOffset(.85);
	/*hc_eta->GetXaxis()->SetTitleOffset(.85);
	hc_pt->GetXaxis()->SetTitleOffset(.85);
	hc_phi->GetXaxis()->SetTitleOffset(.85);
	*/h2_eta->GetXaxis()->SetTitleOffset(.85);
        h2_pt->GetXaxis()->SetTitleOffset(.85);
        h2_phi->GetXaxis()->SetTitleOffset(.85);
	

	ha_eta->GetXaxis()->SetTitleSize(.05);
	ha_pt->GetXaxis()->SetTitleSize(.05);
	ha_phi->GetXaxis()->SetTitleSize(.05);
	h0_eta->GetXaxis()->SetTitleSize(.05);
        h0_pt->GetXaxis()->SetTitleSize(.05);
        h0_phi->GetXaxis()->SetTitleSize(.05);
	hb_eta->GetXaxis()->SetTitleSize(.05);
	hb_pt->GetXaxis()->SetTitleSize(.05);
	hb_phi->GetXaxis()->SetTitleSize(.05);
	h1_eta->GetXaxis()->SetTitleSize(.05);
        h1_pt->GetXaxis()->SetTitleSize(.05);
        h1_phi->GetXaxis()->SetTitleSize(.05);
	/*hc_eta->GetXaxis()->SetTitleSize(.05);
	hc_pt->GetXaxis()->SetTitleSize(.05);
	hc_phi->GetXaxis()->SetTitleSize(.05);
	*/h2_eta->GetXaxis()->SetTitleSize(.05);
        h2_pt->GetXaxis()->SetTitleSize(.05);
        h2_phi->GetXaxis()->SetTitleSize(.05);

	
	TCanvas * C = new TCanvas();
	gStyle->SetOptStat(0);

	C->SetGridx();
	C->SetGridy();
	C->SetTickx();
	C->SetTicky();
	ha_eta->Draw();
	C->Print(out_file_open, "pdf");
	h0_eta->Draw();
	C->Print(out_file_,"pdf");
	hb_eta->Draw();
	C->Print(out_file_open, "pdf");
	h1_eta->Draw();
	C->Print(out_file_,"pdf");
	/*hc_eta->Draw();
	C->Print(out_file_open, "pdf");
	*/h2_eta->Draw();
	C->Print(out_file_,"pdf");

	C->SetLogx();
	ha_pt->Draw();
	C->Print(out_file_, "pdf");
	h0_pt->Draw();
	C->Print(out_file_,"pdf");
	hb_pt->Draw();
	C->Print(out_file_, "pdf");
	h1_pt->Draw();
	C->Print(out_file_,"pdf");
	/*hc_pt->Draw();
	C->Print(out_file_, "pdf");
	*/h2_pt->Draw();
	C->Print(out_file_,"pdf");
	
	C->SetLogx(0);
	ha_phi->Draw();
	C->Print(out_file_, "pdf");
	h0_phi->Draw();
	C->Print(out_file_,"pdf");
	hb_phi->Draw();
	C->Print(out_file_, "pdf");
	h1_phi->Draw();
	C->Print(out_file_,"pdf");
	/*hc_phi->Draw();
	C->Print(out_file_, "pdf");
	*/h2_phi->Draw();
	C->Print(out_file_,"pdf");
	
	Double_t x1= 0.65,y1= 0.7, x2 = 0.9, y2 = 0.9;
	
	ha_eta->GetYaxis()->SetRangeUser(0.75,1.2);
	ha_eta->Draw();
	h0_eta->Draw("same");
	hb_eta->Draw("same");
	h1_eta->Draw("same");
	//hc_eta->Draw("same");
	h2_eta->Draw("same");
	TLegend *leg1=new TLegend(x1,y1,x2,y2,"");
	leg1->SetFillColor(kWhite);
	leg1->SetBorderSize(0);
        leg1->AddEntry(ha_eta,"InDet tracks, dR = 0.01");
        leg1->AddEntry(hb_eta,"InDet tracks, dR = 0.1");
        leg1->AddEntry(h0_eta,"TTT tracks, dR = 0.01");
        leg1->AddEntry(h1_eta,"TTT tracks, dR = 0.1");
        //leg1->AddEntry(hc_eta,"InDet tracks, barcode");
        leg1->AddEntry(h2_eta,"TTT tracks, barcode");
        leg1->Draw();
	C->Print(out_file_,"pdf");
	
	C->SetLogx();
	ha_pt->GetYaxis()->SetRangeUser(0.70,1.2);
	ha_pt->Draw();
	h0_pt->Draw("same");
	hb_pt->Draw("same");
	h1_pt->Draw("same");
	//hc_pt->Draw("same");
	h2_pt->Draw("same");
	TLegend *leg2=new TLegend(x1,y1,x2,y2,"");
	leg2->SetFillColor(kWhite);
	leg2->SetBorderSize(0);
	leg2->AddEntry(ha_pt,"InDet tracks, dR = 0.01");
	leg2->AddEntry(hb_pt,"InDet tracks, dR = 0.1");
	leg2->AddEntry(h0_pt,"TTT tracks, dR = 0.01");
	leg2->AddEntry(h1_pt,"TTT tracks, dR = 0.1");
	//leg2->AddEntry(hc_pt,"InDet tracks, barcode");
	leg2->AddEntry(h2_pt,"TTT tracks, barcode");
	leg2->Draw();
	C->Print(out_file_,"pdf");

	C->SetLogx(0);
	ha_phi->GetYaxis()->SetRangeUser(0.75,1.2);
	ha_phi->Draw();
	h0_phi->Draw("same");
	hb_phi->Draw("same");
	h1_phi->Draw("same");
	//hc_phi->Draw("same");
	h2_phi->Draw("same");
	TLegend *leg3=new TLegend(x1,y1,x2,y2,"");
	leg3->SetFillColor(kWhite);
	leg3->SetBorderSize(0);
	leg3->AddEntry(ha_phi,"InDet tracks, dR = 0.01");
	leg3->AddEntry(hb_phi,"InDet tracks, dR = 0.1");
	leg3->AddEntry(h0_phi,"TTT tracks, dR = 0.01");
	leg3->AddEntry(h1_phi,"TTT tracks, dR = 0.1");
	//leg3->AddEntry(hc_phi,"InDet tracks, barcode");
	leg3->AddEntry(h2_phi,"TTT tracks, barcode");
        leg3->Draw();
	C->Print(out_file_close,"pdf");
return 0;
}
