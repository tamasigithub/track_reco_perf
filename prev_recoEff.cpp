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
const char* out_path = "./plots/efficiency"; 
//////////////// efficiency for TTT tracks  barcode matched////////////////

//int newTTTefficiency_Vs_etaphipt(const char* output_file_name = "prevefficiencyTTT_barcode_mu", bool save = false)
int newTTTefficiency_Vs_etaphipt(const char* output_file_name = "prevefficiencyTTT_barcode", bool save = false)
{
//! Define Cut
//TCut num_select= "r_tid>0 && abs(Vz)<100 && abs(Vx)<15 && abs(Vy)<15 && abs(pt)>2000 && abs(eta)<1.4 && abs(truthPdg)==13";
//TCut den_select= "r_tid>=0 && abs(Vz)<100 && abs(Vx)<15 && abs(Vy)<15 && abs(pt)>2000 && abs(eta)<1.4 && abs(truthPdg)==13";

TCut num_select= "r_tid>0 && abs(Vz)<100 && abs(Vx)<15 && abs(Vy)<15 && abs(pt)>2000 && abs(eta)<1.4 ";
TCut den_select= "r_tid>=0 && abs(Vz)<100 && abs(Vx)<15 && abs(Vy)<15 && abs(pt)>2000 && abs(eta)<1.4";

TChain recTree("m_truthTree");
        recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/user.tkar.hh4bsig5PU0_3_TTTSiOnly.hh4b.root/*.root");

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


	recTree.Draw("eta>>h_num_vs_etaPU",   num_select, "goff"/*, num_events*/);
        recTree.Draw("eta>>h_den_vs_etaPU",   den_select, "goff"/*, num_events*/);
	h_num_vs_etaPU->Draw("e1");
	h_den_vs_etaPU->Draw("e1");
	TH1* h_eff_vs_etaPU = dynamic_cast<TH1*>(h_num_vs_etaPU->Clone("h_eff_vs_etaPU"));
        h_eff_vs_etaPU->SetTitle("efficiency vs #eta;#eta;efficiency");
        h_eff_vs_etaPU->Divide(h_num_vs_etaPU, h_den_vs_etaPU, 1.0, 1.0, "B");
        h_eff_vs_etaPU->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_eff_vs_etaPU->SetMarkerSize(0.95);
        h_eff_vs_etaPU->SetMarkerStyle(kOpenTriangleDown);
        h_eff_vs_etaPU->SetMarkerColor(kBlack);

	recTree.Draw("phi>>h_num_vs_phiPU",   num_select, "goff"/*, num_events*/);
        recTree.Draw("phi>>h_den_vs_phiPU",   den_select, "goff"/*, num_events*/);
	h_num_vs_phiPU->Draw("e1");
	h_den_vs_phiPU->Draw("e1");
	TH1* h_eff_vs_phiPU = dynamic_cast<TH1*>(h_num_vs_phiPU->Clone("h_eff_vs_phiPU"));
        h_eff_vs_phiPU->SetTitle("efficiency vs #phi;#phi [rad];efficiency");
        h_eff_vs_phiPU->Divide(h_num_vs_phiPU, h_den_vs_phiPU, 1.0, 1.0, "B");
        h_eff_vs_phiPU->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_eff_vs_phiPU->SetMarkerSize(0.95);
        h_eff_vs_phiPU->SetMarkerStyle(kOpenTriangleDown);
        h_eff_vs_phiPU->SetMarkerColor(kBlack);

	recTree.Draw("pt>>h_num_vs_ptPU",   num_select, "goff"/*, num_events*/);
	recTree.Draw("pt>>h_den_vs_ptPU",   den_select, "goff"/*, num_events*/);
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

