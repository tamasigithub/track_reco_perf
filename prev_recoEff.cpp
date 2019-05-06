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
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
template<typename T>
inline T angle_pos(T a)
{
        return a - static_cast<T>(2*M_PI) * std::floor(a / static_cast<T>(2*M_PI));
}

/** calculate the equivalent angle in the [-pi, pi] range */
template<typename T>
inline T angle_sym(T a)
{
        return a - static_cast<T>(2*M_PI) * std::floor((a + static_cast<T>(M_PI)) / static_cast<T>(2*M_PI));
}

const char* out_path = "./plots/efficiency"; 
//////////////// efficiency for TTT tracks  barcode matched////////////////

int newTTTefficiency_Vs_etaphipt(const char* output_file_name = "preveffmsig5_3TTTSiOnly_Eta1.2B", bool save = false)
//int newTTTefficiency_Vs_etaphipt(const char* output_file_name = "inEffinvest_TTTSiOnlysig5L6B_HptCentraleta", bool save = false)
//int newTTTefficiency_Vs_etaphipt(const char* output_file_name = "preveffRelaxedTTT_barcode2GeV1.4final", bool save = false)
{
//! Define Cut
TCut num_select= "r_tid>0 && abs(Vz)<100 && abs(Vx)<2 && abs(Vy)<2 && abs(pt)>2000 && abs(eta)<1.2";
TCut den_select= "r_tid>=0 && abs(Vz)<100 && abs(Vx)<2 && abs(Vy)<2 && abs(pt)>2000 && abs(eta)<1.2";

//TCut num_select= "r_tid>0 && abs(Vz)<100 && abs(Vx)<2 && abs(Vy)<2 && abs(pt)>2000 && abs(eta)<1.4 && abs(r_Dphi2)<1e-4 && abs(r_Dz2)<9e-2 && abs(r_Kappa_pull)<5";
//TCut den_select= "r_tid>=0 && abs(Vz)<100 && abs(Vx)<2 && abs(Vy)<2 && abs(pt)>2000 && abs(eta)<1.4 && abs(r_Dphi2)<1e-4 && abs(r_Dz2)<9e-2 && abs(r_Kappa_pull)<5";

	TChain recTree("m_truthTree");
        
	//recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/user.tkar.hh4bsig5PU0_3_TTTSiOnly.hh4b.root/*.root");
        //! no constraint on the truth particles to have atleast made a hit in the outermost layer
	//recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/user.tkar.tkar309527.hh4bRootWide_3_MYSTREAM/*.root");
	//! Final sets used : 
	//recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/dpg2019/user.tkar.hh4bsig5PU0_4_sig5L6B_1_TTTSiOnly.hh4b.root/*.root");
	//! investigation set used : 
//	recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/user.tkar.hh4bsig5PU0_4_TTTSiOnly.hh4b.root/*.root");
	recTree.Add("/media/tamasi/DriveT1/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/dpg2019/user.tkar.hh4b_m1000sig5PU0_3_TTTSiOnly.hh4b.root/*.root");
	int num_events = 10000;
	int etabin = 13;
    	double etamin   = -1.3, etamax = 1.3;
	
	int phibin = 17;
    	double phimin   = -3.4, phimax = 3.4;

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


	recTree.Draw("eta>>h_num_vs_etaPU",   num_select, "goff", num_events);
        recTree.Draw("eta>>h_den_vs_etaPU",   den_select, "goff", num_events);
	h_num_vs_etaPU->Draw("e1");
	h_den_vs_etaPU->Draw("e1");
	TH1* h_eff_vs_etaPU = dynamic_cast<TH1*>(h_num_vs_etaPU->Clone("h_eff_vs_etaPU"));
        h_eff_vs_etaPU->SetTitle("efficiency vs #eta;#eta;efficiency");
        h_eff_vs_etaPU->Divide(h_num_vs_etaPU, h_den_vs_etaPU, 1.0, 1.0, "B");
        h_eff_vs_etaPU->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_eff_vs_etaPU->SetMarkerSize(0.95);
        h_eff_vs_etaPU->SetMarkerStyle(kOpenTriangleDown);
        h_eff_vs_etaPU->SetMarkerColor(kBlack);

	recTree.Draw("angle_sym(phi)>>h_num_vs_phiPU",   num_select, "goff", num_events);
        recTree.Draw("angle_sym(phi)>>h_den_vs_phiPU",   den_select, "goff", num_events);
	h_num_vs_phiPU->Draw("e1");
	h_den_vs_phiPU->Draw("e1");
	TH1* h_eff_vs_phiPU = dynamic_cast<TH1*>(h_num_vs_phiPU->Clone("h_eff_vs_phiPU"));
        h_eff_vs_phiPU->SetTitle("efficiency vs #phi;#phi [rad];efficiency");
        h_eff_vs_phiPU->Divide(h_num_vs_phiPU, h_den_vs_phiPU, 1.0, 1.0, "B");
        h_eff_vs_phiPU->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_eff_vs_phiPU->SetMarkerSize(0.95);
        h_eff_vs_phiPU->SetMarkerStyle(kOpenTriangleDown);
        h_eff_vs_phiPU->SetMarkerColor(kBlack);

	recTree.Draw("pt>>h_num_vs_ptPU",   num_select, "goff", num_events);
	recTree.Draw("pt>>h_den_vs_ptPU",   den_select, "goff", num_events);
	h_num_vs_ptPU->Draw("e1");
	h_den_vs_ptPU->Draw("e1");
	TH1* h_eff_vs_ptPU = dynamic_cast<TH1*>(h_num_vs_ptPU->Clone("h_eff_vs_ptPU"));
	h_eff_vs_ptPU->SetTitle("efficiency vs P_{t};P_{t} [MeV/c];efficiency");
	h_eff_vs_ptPU->Divide(h_num_vs_ptPU, h_den_vs_ptPU, 1.0, 1.0, "B");
	h_eff_vs_ptPU->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_eff_vs_ptPU->GetXaxis()->SetRangeUser(2000.,106000.);
	h_eff_vs_ptPU->SetMarkerSize(0.95);
	h_eff_vs_ptPU->SetMarkerStyle(kOpenTriangleDown);
	h_eff_vs_ptPU->SetMarkerColor(kBlack);	
	
	
	h_eff_vs_etaPU->Draw("e1");
	h_eff_vs_phiPU->Draw("e1");
	h_eff_vs_ptPU->Draw("e1");
	char out_file_root[1023];
        sprintf(out_file_root,"%s/%s.root",out_path,output_file_name);
        TFile* output_file = new TFile(out_file_root, "RECREATE");

	h_num_vs_etaPU->Write();
	h_num_vs_phiPU->Write();
	h_num_vs_ptPU->Write();
	h_den_vs_etaPU->Write();
	h_den_vs_phiPU->Write();
	h_den_vs_ptPU->Write();
	h_eff_vs_etaPU->Write();
	h_eff_vs_phiPU->Write();
	h_eff_vs_ptPU->Write();

	output_file->Close();
}

