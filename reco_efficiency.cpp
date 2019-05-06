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
#include <vector>
const char* out_path = "./plots/efficiency"; 
//! Define Cut

//TCut num_select= "r_TTTtid > 0  && truthBarcode > 0 && truthStatus == 1 && abs(truthPt) > 2000 && abs(truthEta)<1.4 && abs(truthVz) < 100 && abs(truthVx) < 2 && abs(truthVy) < 2 ";
//TCut den_select= "r_TTTtid >= 0 && truthBarcode > 0 && truthStatus == 1 && abs(truthPt) > 2000 && abs(truthEta)<1.4 && abs(truthVz) < 100 && abs(truthVx) < 2 && abs(truthVy) < 2 ";

int eff_Vs_etaphipt_dR_barcode(const char* output_file_name = "effm1000_3ntuples2_InDetTTTdR0.01_eta1.4B_1", bool save = false)
//int eff_Vs_etaphipt_dR_barcode(const char* output_file_name = "eff_InDetTTTdR0.01_eta1.4B", bool save = false)
{
	TChain recTree("m_collectionTree");
        //recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/user.tkar.hh4bsig5PU0_3_ntuples1_MYSTREAM/*.root");
	//dR=0.01
        //recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/user.tkar.hh4bsig5PU0_3_ntuples2_MYSTREAM/*.root");
        //! final set used - 0.01
	//recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/dpg2019/user.tkar.hh4bsig5PU0_4_ntuples1_MYSTREAM/*.root");
	//recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/dpg2019/user.tkar.hh4bsig5PU0_4_ntuples2_MYSTREAM/*.root");
	//! for the fair comparison (truth container contains only those particles that leave a hit in the outermost layer of the triplet)
	//recTree.Add("/media/tamasi/DriveT1/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/dpg2019/user.tkar.hh4b_m1000sig5PU0_3_ntuples1_MYSTREAM/*.root");
	recTree.Add("/media/tamasi/DriveT1/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/dpg2019/user.tkar.hh4b_m1000sig5PU0_3_ntuples2_MYSTREAM/*.root");


	//! define a local vector<double> to store the reconstructed pt values
	//! always initialise a pointer!!
	std::vector<int>   *tstatus = 0;
        std::vector<int>   *barcode = 0;	
        std::vector<int>   *pdg = 0;	
        std::vector<float> *pt = 0;	
        std::vector<float> *phi = 0;	
        std::vector<float> *eta = 0;	
        std::vector<float> *Vx = 0;	
        std::vector<float> *Vy = 0;	
        std::vector<float> *Vz = 0;	
        std::vector<int>   *match_barcodeInDet = 0;
        std::vector<int>   *match_barcodeTTT   = 0;
        std::vector<int>   *match_barcodeTTT_bc= 0;
        //std::vector<int>   *rtid = 0;

	recTree.SetBranchStatus("*",            0);
	/*recTree.SetBranchStatus("truthStatus",  1);
	recTree.SetBranchStatus("truthBarcode", 1);
	recTree.SetBranchStatus("truthPdg",     1);
	recTree.SetBranchStatus("truthPt", 	1);
	recTree.SetBranchStatus("truthPhi", 	1);
	recTree.SetBranchStatus("truthEta", 	1);
	recTree.SetBranchStatus("truthVx", 	1);
	recTree.SetBranchStatus("truthVy", 	1);
	recTree.SetBranchStatus("truthVz", 	1);*/
	recTree.SetBranchStatus("TTTtruthStatus",  1);
	recTree.SetBranchStatus("TTTtruthBarcode", 1);
	recTree.SetBranchStatus("TTTtruthPdg",     1);
	recTree.SetBranchStatus("TTTtruthPt", 	   1);
	recTree.SetBranchStatus("TTTtruthPhi0",	   1);
	recTree.SetBranchStatus("TTTtruthEta", 	   1);
	recTree.SetBranchStatus("TTTtruthVx", 	   1);
	recTree.SetBranchStatus("TTTtruthVy", 	   1);
	recTree.SetBranchStatus("TTTtruthVz", 	   1);
	recTree.SetBranchStatus("InDetTBarcode",   1);
	recTree.SetBranchStatus("TTTTBarcode",     1);
	recTree.SetBranchStatus("mTTTTBarcode",    1);
	//recTree.SetBranchStatus("r_TTTtid",     1);
	/*recTree.SetBranchAddress("truthStatus",  &tstatus);
	recTree.SetBranchAddress("truthBarcode", &barcode);
	recTree.SetBranchAddress("truthPdg",     &pdg);
	recTree.SetBranchAddress("truthPt", 	 &pt);
	recTree.SetBranchAddress("truthPhi", 	 &phi);
	recTree.SetBranchAddress("truthEta", 	 &eta);
	recTree.SetBranchAddress("truthVx", 	 &Vx);
	recTree.SetBranchAddress("truthVy", 	 &Vy);
	recTree.SetBranchAddress("truthVz", 	 &Vz);*/
	recTree.SetBranchAddress("TTTtruthStatus",  &tstatus);
	recTree.SetBranchAddress("TTTtruthBarcode", &barcode);
	recTree.SetBranchAddress("TTTtruthPdg",     &pdg);
	recTree.SetBranchAddress("TTTtruthPt", 	    &pt);
	recTree.SetBranchAddress("TTTtruthPhi0",    &phi);
	recTree.SetBranchAddress("TTTtruthEta",     &eta);
	recTree.SetBranchAddress("TTTtruthVx", 	    &Vx);
	recTree.SetBranchAddress("TTTtruthVy", 	    &Vy);
	recTree.SetBranchAddress("TTTtruthVz", 	    &Vz);
	recTree.SetBranchAddress("InDetTBarcode",   &match_barcodeInDet);
	recTree.SetBranchAddress("TTTTBarcode",     &match_barcodeTTT);
	recTree.SetBranchAddress("mTTTTBarcode",    &match_barcodeTTT_bc);
	//recTree.SetBranchAddress("r_TTTtid",     &rtid);

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
	        //std::cout<<"i,dx : " <<i << ", "<<dx <<std::endl;
		xbins[i] = TMath::Exp(l10*i*dx);
	        //std::cout<<"xbin[i] : " <<xbins[i] <<std::endl;
	}
	TH1::SetDefaultSumw2(true);
	
	TH1* h_num_vs_etaInDet = new TH1F("h_num_vs_etaInDet", "Numerator Count vs #eta;#eta;Numerator Count"    , etabin, etamin, etamax);
        TH1* h_den_vs_etaInDet = new TH1F("h_den_vs_etaInDet", "Denominator Count vs #eta;#eta;Denominator Count", etabin, etamin, etamax);
	
	TH1* h_num_vs_phiInDet = new TH1F("h_num_vs_phiInDet", "Numerator Count vs #eta;#phi [rad];Numerator Count"    , phibin, phimin, phimax);
        TH1* h_den_vs_phiInDet = new TH1F("h_den_vs_phiInDet", "Denominator Count vs #eta;#phi [rad];Denominator Count", phibin, phimin, phimax);

	TH1* h_num_vs_ptInDet = new TH1F("h_num_vs_ptInDet", "Numerator Count vs P_{t};P_{t} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_ptInDet = new TH1F("h_den_vs_ptInDet", "Denominator Count vs P_{t};P_{t} [MeV/c];Denominator Count", ptbins, xbins);

	//! TTT tracks histos
	TH1* h_num_vs_etaTTT = new TH1F("h_num_vs_etaTTT", "Numerator Count vs #eta;#eta;Numerator Count"    , etabin, etamin, etamax);
        TH1* h_den_vs_etaTTT = new TH1F("h_den_vs_etaTTT", "Denominator Count vs #eta;#eta;Denominator Count", etabin, etamin, etamax);
	
	TH1* h_num_vs_phiTTT = new TH1F("h_num_vs_phiTTT", "Numerator Count vs #eta;#phi [rad];Numerator Count"    , phibin, phimin, phimax);
        TH1* h_den_vs_phiTTT = new TH1F("h_den_vs_phiTTT", "Denominator Count vs #eta;#phi [rad];Denominator Count", phibin, phimin, phimax);

	TH1* h_num_vs_ptTTT = new TH1F("h_num_vs_ptTTT", "Numerator Count vs P_{t};P_{t} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_ptTTT = new TH1F("h_den_vs_ptTTT", "Denominator Count vs P_{t};P_{t} [MeV/c];Denominator Count", ptbins, xbins);
	//! TTT barcode matched
	TH1* h_num_vs_etaPU = new TH1F("h_num_vs_etaPU", "Numerator Count vs #eta;#eta;Numerator Count"    , etabin, etamin, etamax);
        TH1* h_den_vs_etaPU = new TH1F("h_den_vs_etaPU", "Denominator Count vs #eta;#eta;Denominator Count", etabin, etamin, etamax);
	
	TH1* h_num_vs_phiPU = new TH1F("h_num_vs_phiPU", "Numerator Count vs #phi;#phi [rad];Numerator Count"    , phibin, phimin, phimax);
        TH1* h_den_vs_phiPU = new TH1F("h_den_vs_phiPU", "Denominator Count vs #phi;#phi [rad];Denominator Count", phibin, phimin, phimax);

	TH1* h_num_vs_ptPU = new TH1F("h_num_vs_ptPU", "Numerator Count vs P_{t};P_{t} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_ptPU = new TH1F("h_den_vs_ptPU", "Denominator Count vs P_{t};P_{t} [MeV/c];Denominator Count", ptbins, xbins);

	std::cout<<"total number of entries: " << recTree.GetEntries()<<std::endl;

	//for(int i = 0; i < recTree.GetEntries(); ++i)
	for(int i = 0; i < 10000; ++i)
	{
		
		recTree.GetEntry(i);
		//! loop over the truth particles and select stable charge particles passing the selections
		for(int i1 = 0; i1 < barcode->size(); ++i1)
		{
			bool match_flagInDet = false;
			bool match_flagTTT = false;
			bool match_flagTTT_bc = false;
			if(tstatus->at(i1) != 1)		continue;
			if(std::fabs(pt->at(i1)) < 2e3 )	continue;
			if(std::fabs(eta->at(i1)) > 1.4)	continue;
			if(std::fabs(Vz->at(i1)) > 100 )	continue;
			if(std::fabs(Vx->at(i1)) > 2 )		continue;
			if(std::fabs(Vy->at(i1)) > 2 )		continue;
			if(barcode->at(i1) <= 0) 		continue;
			//if(std::abs(pdg->at(i1)) != 321) 	continue;

			//! loop over InDet tracks and then find the corresponding particle it was matched to
			for(int i2 = 0; i2 < match_barcodeInDet->size(); ++i2)
			{
				//! if a match is found fill truth variables both in numerator and denominator
				//! else fill truth variables only in the denominator
				if((*match_barcodeInDet)[i2] == (*barcode)[i1])
				{
					match_flagInDet = true;
					break;
				}
				else
				{
					match_flagInDet = false;
				}
			}
			//! loop over TTT tracks and the find the corresponding particle it was matched to
			for(int i2 = 0; i2 < match_barcodeTTT->size(); ++i2)
			{
				//! if a match is found fill truth variables both in numerator and denominator
				//! else fill truth variables only in the denominator
				if((*match_barcodeTTT)[i2] == (*barcode)[i1])
				{
					match_flagTTT = true;
					break;
				}
				else
				{
					match_flagTTT = false;
				}
			}
			//! loop over TTT tracks and the find the corresponding particle it was matched to (with barcode matching)
			for(int i2 = 0; i2 < match_barcodeTTT_bc->size(); ++i2)
			{
				//std::cout<<"truth barcode: " << (*barcode)[i1] << ",  matched barcode: " << (*match_barcodeTTT_bc)[i2] <<std::endl;
				//! if a match is found fill truth variables both in numerator and denominator
				//! else fill truth variables only in the denominator
				if((*match_barcodeTTT_bc)[i2] == (*barcode)[i1])
				{
					match_flagTTT_bc = true;
					//std::cout<<"match track!"<<std::endl;
					break;
				}
				else
				{
					match_flagTTT_bc = false;
					//std::cout<<"fake track!"<<std::endl;
				}
			}
			if(match_flagInDet)
			{
				h_num_vs_etaInDet->Fill((*eta)[i1]);
				h_num_vs_phiInDet->Fill((*phi)[i1]);
				h_num_vs_ptInDet->Fill((*pt)[i1]);
			}
			h_den_vs_etaInDet->Fill((*eta)[i1]);
			h_den_vs_phiInDet->Fill((*phi)[i1]);
			h_den_vs_ptInDet->Fill((*pt)[i1]);
			if(match_flagTTT)
			{
				h_num_vs_etaTTT->Fill((*eta)[i1]);
				h_num_vs_phiTTT->Fill((*phi)[i1]);
				h_num_vs_ptTTT->Fill((*pt)[i1]);
			}
			h_den_vs_etaTTT->Fill((*eta)[i1]);
			h_den_vs_phiTTT->Fill((*phi)[i1]);
			h_den_vs_ptTTT->Fill((*pt)[i1]);
			if(match_flagTTT_bc)
			{
				h_num_vs_etaPU->Fill((*eta)[i1]);
				h_num_vs_phiPU->Fill((*phi)[i1]);
				h_num_vs_ptPU->Fill((*pt)[i1]);
			}
			h_den_vs_etaPU->Fill((*eta)[i1]);
			h_den_vs_phiPU->Fill((*phi)[i1]);
			h_den_vs_ptPU->Fill((*pt)[i1]);
		}
	}

	h_num_vs_etaInDet->Draw("e1");
	h_den_vs_etaInDet->Draw("e1");
	TH1* h_eff_vs_etaInDet = dynamic_cast<TH1*>(h_num_vs_etaInDet->Clone("h_eff_vs_etaInDet"));
        h_eff_vs_etaInDet->Divide(h_num_vs_etaInDet, h_den_vs_etaInDet, 1.0, 1.0, "B");
	h_num_vs_phiInDet->Draw("e1");
	h_den_vs_phiInDet->Draw("e1");
	TH1* h_eff_vs_phiInDet = dynamic_cast<TH1*>(h_num_vs_phiInDet->Clone("h_eff_vs_phiInDet"));
        h_eff_vs_phiInDet->Divide(h_num_vs_phiInDet, h_den_vs_phiInDet, 1.0, 1.0, "B");
	h_num_vs_ptInDet->Draw("e1");
	h_den_vs_ptInDet->Draw("e1");
	TH1* h_eff_vs_ptInDet = dynamic_cast<TH1*>(h_num_vs_ptInDet->Clone("h_eff_vs_ptInDet"));
	h_eff_vs_ptInDet->Divide(h_num_vs_ptInDet, h_den_vs_ptInDet, 1.0, 1.0, "B");
	h_num_vs_etaTTT->Draw("e1");
	h_den_vs_etaTTT->Draw("e1");
	TH1* h_eff_vs_etaTTT = dynamic_cast<TH1*>(h_num_vs_etaTTT->Clone("h_eff_vs_etaTTT"));
        h_eff_vs_etaTTT->Divide(h_num_vs_etaTTT, h_den_vs_etaTTT, 1.0, 1.0, "B");
	h_num_vs_phiTTT->Draw("e1");
	h_den_vs_phiTTT->Draw("e1");
	TH1* h_eff_vs_phiTTT = dynamic_cast<TH1*>(h_num_vs_phiTTT->Clone("h_eff_vs_phiTTT"));
        h_eff_vs_phiTTT->Divide(h_num_vs_phiTTT, h_den_vs_phiTTT, 1.0, 1.0, "B");
	h_num_vs_ptTTT->Draw("e1");
	h_den_vs_ptTTT->Draw("e1");
	TH1* h_eff_vs_ptTTT = dynamic_cast<TH1*>(h_num_vs_ptTTT->Clone("h_eff_vs_ptTTT"));
	h_eff_vs_ptTTT->Divide(h_num_vs_ptTTT, h_den_vs_ptTTT, 1.0, 1.0, "B");
	//! barcode matched TTT
 	//recTree.Draw("truthPt>>h_num_vs_ptPU",   num_select, "goff");
 	//recTree.Draw("truthPt>>h_den_vs_ptPU",   den_select, "goff");
	h_num_vs_etaPU->Draw("e1");
	h_den_vs_etaPU->Draw("e1");
	TH1* h_eff_vs_etaPU = dynamic_cast<TH1*>(h_num_vs_etaPU->Clone("h_eff_vs_etaPU"));
        h_eff_vs_etaPU->Divide(h_num_vs_etaPU, h_den_vs_etaPU, 1.0, 1.0, "B");
	h_num_vs_phiPU->Draw("e1");
	h_den_vs_phiPU->Draw("e1");
	TH1* h_eff_vs_phiPU = dynamic_cast<TH1*>(h_num_vs_phiPU->Clone("h_eff_vs_phiPU"));
        h_eff_vs_phiPU->Divide(h_num_vs_phiPU, h_den_vs_phiPU, 1.0, 1.0, "B");
	h_num_vs_ptPU->Draw("e1");
	h_den_vs_ptPU->Draw("e1");
	TH1* h_eff_vs_ptPU = dynamic_cast<TH1*>(h_num_vs_ptPU->Clone("h_eff_vs_ptPU"));
	h_eff_vs_ptPU->Divide(h_num_vs_ptPU, h_den_vs_ptPU, 1.0, 1.0, "B");

        h_eff_vs_etaInDet->SetTitle("efficiency vs #eta;#eta;efficiency");
        h_eff_vs_phiInDet->SetTitle("efficiency vs #phi;#phi [rad];efficiency");
	h_eff_vs_ptInDet->SetTitle("efficiency vs P_{t};P_{t} [MeV/c];efficiency");
        h_eff_vs_etaTTT->SetTitle("efficiency vs #eta;#eta;efficiency");
        h_eff_vs_phiTTT->SetTitle("efficiency vs #phi;#phi [rad];efficiency");
	h_eff_vs_ptTTT->SetTitle("efficiency vs P_{t};P_{t} [MeV/c];efficiency");
        h_eff_vs_etaPU->SetTitle("efficiency vs #eta;#eta;efficiency");
        h_eff_vs_phiPU->SetTitle("efficiency vs #phi;#phi [rad];efficiency");
	h_eff_vs_ptPU->SetTitle("efficiency vs P_{t};P_{t} [MeV/c];efficiency");
        
	h_eff_vs_ptInDet->GetXaxis()->SetRangeUser(2000.,106000.);
	h_eff_vs_ptTTT->GetXaxis()->SetRangeUser(2000.,106000.);
	h_eff_vs_ptPU->GetXaxis()->SetRangeUser(2000.,106000.);
	
	h_eff_vs_etaInDet->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_eff_vs_phiInDet->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_eff_vs_ptInDet->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_eff_vs_etaTTT->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_eff_vs_phiTTT->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_eff_vs_ptTTT->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_eff_vs_etaPU->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_eff_vs_phiPU->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_eff_vs_ptPU->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_eff_vs_etaInDet->GetYaxis()->SetTitleOffset(0.85);
        h_eff_vs_phiInDet->GetYaxis()->SetTitleOffset(0.85);
	h_eff_vs_ptInDet->GetYaxis()->SetTitleOffset(0.85);
        h_eff_vs_etaTTT->GetYaxis()->SetTitleOffset(0.85);
        h_eff_vs_phiTTT->GetYaxis()->SetTitleOffset(0.85);
	h_eff_vs_ptTTT->GetYaxis()->SetTitleOffset(0.85);
        h_eff_vs_etaPU->GetYaxis()->SetTitleOffset(0.85);
        h_eff_vs_phiPU->GetYaxis()->SetTitleOffset(0.85);
	h_eff_vs_ptPU->GetYaxis()->SetTitleOffset(0.85);
	h_eff_vs_etaInDet->GetYaxis()->SetTitleSize(0.05);
        h_eff_vs_phiInDet->GetYaxis()->SetTitleSize(0.05);
	h_eff_vs_ptInDet->GetYaxis()->SetTitleSize(0.05);
        h_eff_vs_etaTTT->GetYaxis()->SetTitleSize(0.05);
        h_eff_vs_phiTTT->GetYaxis()->SetTitleSize(0.05);
	h_eff_vs_ptTTT->GetYaxis()->SetTitleSize(0.05);
        h_eff_vs_etaPU->GetYaxis()->SetTitleSize(0.05);
        h_eff_vs_phiPU->GetYaxis()->SetTitleSize(0.05);
	h_eff_vs_ptPU->GetYaxis()->SetTitleSize(0.05);
	h_eff_vs_etaInDet->GetXaxis()->SetTitleOffset(0.85);
        h_eff_vs_phiInDet->GetXaxis()->SetTitleOffset(0.85);
	h_eff_vs_ptInDet->GetXaxis()->SetTitleOffset(0.85);
        h_eff_vs_etaTTT->GetXaxis()->SetTitleOffset(0.85);
        h_eff_vs_phiTTT->GetXaxis()->SetTitleOffset(0.85);
	h_eff_vs_ptTTT->GetXaxis()->SetTitleOffset(0.85);
        h_eff_vs_etaPU->GetXaxis()->SetTitleOffset(0.85);
        h_eff_vs_phiPU->GetXaxis()->SetTitleOffset(0.85);
	h_eff_vs_ptPU->GetXaxis()->SetTitleOffset(0.85);
	h_eff_vs_etaInDet->GetXaxis()->SetTitleSize(0.05);
        h_eff_vs_phiInDet->GetXaxis()->SetTitleSize(0.05);
	h_eff_vs_ptInDet->GetXaxis()->SetTitleSize(0.05);
        h_eff_vs_etaTTT->GetXaxis()->SetTitleSize(0.05);
        h_eff_vs_phiTTT->GetXaxis()->SetTitleSize(0.05);
	h_eff_vs_ptTTT->GetXaxis()->SetTitleSize(0.05);
        h_eff_vs_etaPU->GetXaxis()->SetTitleSize(0.05);
        h_eff_vs_phiPU->GetXaxis()->SetTitleSize(0.05);
	h_eff_vs_ptPU->GetXaxis()->SetTitleSize(0.05);
        
	h_eff_vs_etaInDet->SetMarkerSize(1.8);
        h_eff_vs_phiInDet->SetMarkerSize(1.8);
	h_eff_vs_ptInDet->SetMarkerSize(1.8);
        h_eff_vs_etaTTT->SetMarkerSize(1.8);
        h_eff_vs_phiTTT->SetMarkerSize(1.8);
	h_eff_vs_ptTTT->SetMarkerSize(1.8);
        h_eff_vs_etaPU->SetMarkerSize(1.8);
        h_eff_vs_phiPU->SetMarkerSize(1.8);
	h_eff_vs_ptPU->SetMarkerSize(1.8);
        
	h_eff_vs_etaInDet->SetMarkerStyle(kFullTriangleDown);
        h_eff_vs_phiInDet->SetMarkerStyle(kFullTriangleDown);
	h_eff_vs_ptInDet->SetMarkerStyle(kFullTriangleDown);
        h_eff_vs_etaTTT->SetMarkerStyle(kFullTriangleDown);
        h_eff_vs_phiTTT->SetMarkerStyle(kFullTriangleDown);
	h_eff_vs_ptTTT->SetMarkerStyle(kFullTriangleDown);
        h_eff_vs_etaPU->SetMarkerStyle(kFullTriangleDown);
        h_eff_vs_phiPU->SetMarkerStyle(kFullTriangleDown);
	h_eff_vs_ptPU->SetMarkerStyle(kFullTriangleDown);
        
	h_eff_vs_etaInDet->SetMarkerColor(kRed);
        h_eff_vs_phiInDet->SetMarkerColor(kRed);
	h_eff_vs_ptInDet->SetMarkerColor(kRed);	
        h_eff_vs_etaTTT->SetMarkerColor(kBlue);
        h_eff_vs_phiTTT->SetMarkerColor(kBlue);
	h_eff_vs_ptTTT->SetMarkerColor(kBlue);
        h_eff_vs_etaPU->SetMarkerColor(kBlack);
        h_eff_vs_phiPU->SetMarkerColor(kBlack);
	h_eff_vs_ptPU->SetMarkerColor(kBlack);	
	

	//! write 
	TCanvas* c1 = new TCanvas();	
	h_eff_vs_etaInDet->Draw("e1");
	h_eff_vs_etaTTT->Draw("e1");

	TCanvas* c2 = new TCanvas();	
	h_eff_vs_phiInDet->Draw("e1");
	h_eff_vs_phiTTT->Draw("e1");

	
	TCanvas* c3 = new TCanvas();	
	h_eff_vs_ptInDet->Draw("e1");
	h_eff_vs_ptTTT->Draw("e1");

	h_eff_vs_etaPU->Draw("e1");
	h_eff_vs_phiPU->Draw("e1");
	h_eff_vs_ptPU->Draw("e1");
	char out_file_root[1023];
        sprintf(out_file_root,"%s/%s.root",out_path,output_file_name);
        TFile* output_file = new TFile(out_file_root, "RECREATE");

	h_num_vs_etaInDet->Write();
	h_num_vs_phiInDet->Write();
	h_num_vs_ptInDet->Write();
	h_den_vs_etaInDet->Write();
	h_den_vs_phiInDet->Write();
	h_den_vs_ptInDet->Write();
	h_eff_vs_etaInDet->Write();
	h_eff_vs_phiInDet->Write();
	h_eff_vs_ptInDet->Write();
	h_num_vs_etaTTT->Write();
	h_num_vs_phiTTT->Write();
	h_num_vs_ptTTT->Write();
	h_den_vs_etaTTT->Write();
	h_den_vs_phiTTT->Write();
	h_den_vs_ptTTT->Write();
	h_eff_vs_etaTTT->Write();
	h_eff_vs_phiTTT->Write();
	h_eff_vs_ptTTT->Write();
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

/////////////// write efficiency to pdf /////////////////
int write_topdf(const char* output_file_name = "efficiency_InDetTTT_hh4b_dR0.1_noZ0")
{

	char out_file_open[1023];
        sprintf(out_file_open,"%s/%s.pdf(",out_path,output_file_name);
        char out_file_[1023];
        sprintf(out_file_,"%s/%s.pdf",out_path,output_file_name);
        char out_file_close[1023];
        sprintf(out_file_close,"%s/%s.pdf)",out_path,output_file_name);
	//!InDet tracks
	//TFile* f = TFile::Open("./plots/efficiency/efficiency_dR0.1.root");
	TFile* f = TFile::Open("./plots/efficiency/efficiency_dR0.1_noZ0.root");
	//TFile* f = TFile::Open("./plots/efficiency/efficiency_dR0.01.root");
	TH1D* h_eta 	= (TH1D*)f->Get("h_eff_vs_etaPU");
	TH1D* h_pt 	= (TH1D*)f->Get("h_eff_vs_ptPU");
	TH1D* h_phi	= (TH1D*)f->Get("h_eff_vs_phiPU");

	//! TTT tracks
	//TFile* f0 = TFile::Open("./plots/efficiency/efficiencyTTT_dR0.1.root");
	TFile* f0 = TFile::Open("./plots/efficiency/efficiencyTTT_dR0.1_noZ0.root");
	//TFile* f0 = TFile::Open("./plots/efficiency/efficiencyTTT_dR0.01.root");
	TH1D* h0_eta 	= (TH1D*)f0->Get("h_eff_vs_etaPU");
	TH1D* h0_pt 	= (TH1D*)f0->Get("h_eff_vs_ptPU");
	TH1D* h0_phi	= (TH1D*)f0->Get("h_eff_vs_phiPU");


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
/////////////// write efficiency to pdf different matching methods/////////////////
//int newwrite_topdf(const char* output_file_name = "efficiency_InDetTTT_hh4b_all")
int newwrite_topdf(const char* output_file_name = "newefficiency_InDetTTT_hh4b_all")
{

	char out_file_open[1023];
        sprintf(out_file_open,"%s/%s.pdf(",out_path,output_file_name);
        char out_file_[1023];
        sprintf(out_file_,"%s/%s.pdf",out_path,output_file_name);
        char out_file_close[1023];
        sprintf(out_file_close,"%s/%s.pdf)",out_path,output_file_name);
	//!InDet tracks
	TFile* fa = TFile::Open("./plots/efficiency/newefficiency_dR0.01.root");
	TH1D* ha_eta 	= (TH1D*)fa->Get("h_eff_vs_etaPU");
	TH1D* ha_pt 	= (TH1D*)fa->Get("h_eff_vs_ptPU");
	TH1D* ha_phi	= (TH1D*)fa->Get("h_eff_vs_phiPU");
	TFile* fb = TFile::Open("./plots/efficiency/newefficiency_dR0.1.root");
	TH1D* hb_eta 	= (TH1D*)fb->Get("h_eff_vs_etaPU");
	TH1D* hb_pt 	= (TH1D*)fb->Get("h_eff_vs_ptPU");
	TH1D* hb_phi	= (TH1D*)fb->Get("h_eff_vs_phiPU");
	/*TFile* fc = TFile::Open("./plots/efficiency/efficiency_barcode.root");
	TH1D* hc_eta 	= (TH1D*)fc->Get("h_eff_vs_etaPU");
	TH1D* hc_pt 	= (TH1D*)fc->Get("h_eff_vs_ptPU");
	TH1D* hc_phi	= (TH1D*)fc->Get("h_eff_vs_phiPU");*/

	//! TTT tracks
	TFile* f0 = TFile::Open("./plots/efficiency/newefficiencyTTT_dR0.01.root");
	TH1D* h0_eta 	= (TH1D*)f0->Get("h_eff_vs_etaPU");
	TH1D* h0_pt 	= (TH1D*)f0->Get("h_eff_vs_ptPU");
	TH1D* h0_phi	= (TH1D*)f0->Get("h_eff_vs_phiPU");
	TFile* f1 = TFile::Open("./plots/efficiency/newefficiencyTTT_dR0.1.root");
	TH1D* h1_eta 	= (TH1D*)f1->Get("h_eff_vs_etaPU");
	TH1D* h1_pt 	= (TH1D*)f1->Get("h_eff_vs_ptPU");
	TH1D* h1_phi	= (TH1D*)f1->Get("h_eff_vs_phiPU");
	TFile* f2 = TFile::Open("./plots/efficiency/newefficiencyTTT_barcode.root");
	TH1D* h2_eta 	= (TH1D*)f2->Get("h_eff_vs_etaPU");
	TH1D* h2_pt 	= (TH1D*)f2->Get("h_eff_vs_ptPU");
	TH1D* h2_phi	= (TH1D*)f2->Get("h_eff_vs_phiPU");


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
	
	hb_eta->SetMarkerStyle(kFullTriangleDown);
	hb_pt->SetMarkerStyle(kFullTriangleDown);
	hb_phi->SetMarkerStyle(kFullTriangleDown);

	h1_eta->SetMarkerStyle(kFullTriangleDown);
        h1_pt->SetMarkerStyle(kFullTriangleDown);
        h1_phi->SetMarkerStyle(kFullTriangleDown);
	
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
