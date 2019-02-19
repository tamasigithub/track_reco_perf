////////////////////NTrackJET efficiency matched to Higgs pt///////////////////
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
#include "TChain.h"
#include <vector>
#include <algorithm> 
#include <functional>
#include <fstream>
#include <string>
#include <math.h>

const char* out_path = "./plots";

//int Njeteff(const char* output_file_name = "NjeteffcaloTTT_501.5no0.6", bool debug = false)
int Njeteff_trkjets(const char* output_file_name = "Njeteffttt4trk_501.5", bool debug = false)
{
	//! selections
	int Njet_max = 5;
	const float pt_cut = 50e3;
	const float eta_cut = 1.5;
	//! load input files
	TChain tree("m_collectionTree");
	tree.Add("/nfs/dust/atlas/user/tkar/derivations/grid_files/user.tkar.hh4bsig5_16_ntuples1_MYSTREAM/*.root");
	//tree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/user.tkar.hh4bsig5_16_ntuples1_MYSTREAM/*.root");
	if(debug) std::cout<<"m_collectionTree opened with " << tree.GetEntries() << " entries" <<std::endl;

	std::vector<float> *Pt_truth = 0;
	std::vector<int> *Pdg_truth = 0;
	std::vector<float> *Eta_truth = 0;
	std::vector<float> *Phi_truth = 0;
        std::vector<float> *Pt_TTTtrkjet = 0;
        std::vector<float> *Eta_TTTtrkjet = 0;
        std::vector<float> *Phi_TTTtrkjet = 0;
	//! container consisting of selected calo jets
        float Pt_leadingSMh;
	std::vector<float> Pt_SMh ;
        std::vector<float> Pt_b ;
        std::vector<float> Eta_b ;
        std::vector<float> Pt_trkJetTTTsel ;
        std::vector<float> Eta_trkJetTTTsel ;
        std::vector<float> Phi_trkJetTTTsel ;
	tree.SetBranchStatus("truthPt", 1);
	tree.SetBranchStatus("truthPdg",1);
	tree.SetBranchStatus("truthEta",1);
	tree.SetBranchStatus("truthPhi",1);
	tree.SetBranchStatus("ttt4trkjetPt",1);
	tree.SetBranchStatus("ttt4trkjetEta",1);
	tree.SetBranchStatus("ttt4trkjetPhi",1);
	tree.SetBranchAddress("truthPt", &Pt_truth);
	tree.SetBranchAddress("truthPdg",&Pdg_truth);
	tree.SetBranchAddress("truthEta",&Eta_truth);
	tree.SetBranchAddress("truthPhi",&Phi_truth);
	tree.SetBranchAddress("ttt4trkjetPt", &Pt_TTTtrkjet );
	tree.SetBranchAddress("ttt4trkjetEta",&Eta_TTTtrkjet);
	tree.SetBranchAddress("ttt4trkjetPhi",&Phi_TTTtrkjet);
        Long64_t n_entries = tree.GetEntries();
	
	const float pt_min = 20e3, pt_max = 800e3; //! in MeV
	Int_t nbins = 10;	

	//! book histograms
	TH1::SetDefaultSumw2(true);
	TH1* h_trigeffnum1 = new TH1F("h_trigeffnum1"," Numerator counts : trigger efficiency for SM higgs", nbins, pt_min, pt_max);
	TH1* h_trigeffnum2 = new TH1F("h_trigeffnum2"," Numerator counts : trigger efficiency for SM higgs", nbins, pt_min, pt_max);
	TH1* h_trigeffnum3 = new TH1F("h_trigeffnum3"," Numerator counts : trigger efficiency for SM higgs", nbins, pt_min, pt_max);
	TH1* h_trigeffnum4 = new TH1F("h_trigeffnum4"," Numerator counts : trigger efficiency for SM higgs", nbins, pt_min, pt_max);
	TH1* h_trigeffden1 = new TH1F("h_trigeffden1"," Denominator counts: trigger efficiency for SM higgs", nbins, pt_min, pt_max);
	TH1* h_trigeffden2 = new TH1F("h_trigeffden2"," Denominator counts: trigger efficiency for SM higgs", nbins, pt_min, pt_max);
	TH1* h_trigeffden3 = new TH1F("h_trigeffden3"," Denominator counts: trigger efficiency for SM higgs", nbins, pt_min, pt_max);
	TH1* h_trigeffden4 = new TH1F("h_trigeffden4"," Denominator counts: trigger efficiency for SM higgs", nbins, pt_min, pt_max);

	//! loop over the tree and get the entries into the local variable
	for(int it = 0; it < n_entries; it++)
	{
		Pt_leadingSMh = 0;
		Pt_SMh.clear(); 
		Pt_b.clear(); 
		Eta_b.clear(); 
		Pt_trkJetTTTsel.clear(); 
		Eta_trkJetTTTsel.clear();
		Phi_trkJetTTTsel.clear();

		Pt_TTTtrkjet->clear(); 
		Eta_TTTtrkjet->clear();
		Phi_TTTtrkjet->clear();

		Pt_truth->clear();
		Pdg_truth->clear();	
		Eta_truth->clear();
		Phi_truth->clear();

		tree.GetEntry(it);
		if(debug) std::cout<<"got entries for event : "<< it << ", truthPt size : " << Pt_truth->size() <<std::endl;

		//! find the leading pt SM higgs in this event if there is atleast one bjet satisfying the selection cuts
		for(int it0 = 0; it0 < Pt_truth->size(); ++it0)
		{
			if(debug) std::cout<<"pdg, pt, eta : " << (*Pdg_truth)[it0] << ", " << (*Pt_truth)[it0] << ", " << (*Eta_truth)[it0] << std::endl;
			if(std::abs((*Pdg_truth)[it0]) == 5) 
			{
				if((*Pt_truth)[it0] < pt_cut) continue;
				if(std::abs((*Eta_truth)[it0]) > eta_cut) continue;
				Pt_b.push_back((*Pt_truth)[it0]);
				Eta_b.push_back((*Eta_truth)[it0]);
			}
			else if((*Pdg_truth)[it0] == 25)
			{
				Pt_SMh.push_back((*Pt_truth)[it0]);
			}

		}
	
		
		if(Pt_b.size() >= Njet_max-1  && Pt_SMh.size()>0) 
		{
			Pt_leadingSMh = *std::max_element(Pt_SMh.begin(), Pt_SMh.end());
		
			h_trigeffden4->Fill(Pt_leadingSMh);
			h_trigeffden3->Fill(Pt_leadingSMh);
			h_trigeffden2->Fill(Pt_leadingSMh);
			h_trigeffden1->Fill(Pt_leadingSMh);
			if(debug) std::cout<<"at least 4 jets, Pt_leading SMh : " << Pt_leadingSMh << std::endl; 
		}
		else if(Pt_b.size() >= Njet_max-2 && Pt_SMh.size()>0) 
		{
			Pt_leadingSMh = *std::max_element(Pt_SMh.begin(), Pt_SMh.end());
		
			h_trigeffden3->Fill(Pt_leadingSMh);
			h_trigeffden2->Fill(Pt_leadingSMh);
			h_trigeffden1->Fill(Pt_leadingSMh);
			if(debug) std::cout<<"at least 3 jets, Pt_leading SMh : " << Pt_leadingSMh << std::endl; 
		}
		else if(Pt_b.size() >= Njet_max-3 && Pt_SMh.size()>0) 
		{
			Pt_leadingSMh = *std::max_element(Pt_SMh.begin(), Pt_SMh.end());
		
			h_trigeffden2->Fill(Pt_leadingSMh);
			h_trigeffden1->Fill(Pt_leadingSMh);
			if(debug) std::cout<<"at least 2 jets, Pt_leading SMh : " << Pt_leadingSMh << std::endl; 
		}
		else if(Pt_b.size() >= Njet_max-4 && Pt_SMh.size()>0) 
		{
			Pt_leadingSMh = *std::max_element(Pt_SMh.begin(), Pt_SMh.end());
		
			h_trigeffden1->Fill(Pt_leadingSMh);
			if(debug) std::cout<<"at least 1 jets, Pt_leading SMh : " << Pt_leadingSMh << std::endl; 
		}
		else continue;// go to the next event if denominator is zero

		//! Numerator selection
		for(int it1 = 0; it1 < Pt_TTTtrkjet->size(); ++it1)
		{
			if(debug)
			{
				std::cout<<"pt, eta = " << (*Pt_TTTtrkjet)[it1] << ", " << (*Eta_TTTtrkjet)[it1] << std::endl;
			}
			//! apply cuts on calo jets
			if((*Pt_TTTtrkjet)[it1] < pt_cut) continue;
			if(debug)std::cout<<"pt selection passed!"<<std::endl;
			if(std::abs((*Eta_TTTtrkjet)[it1]) > eta_cut) continue;
			if(debug)std::cout<<"eta selection passed!"<<std::endl;

			if(debug) std::cout<<"selection passed" <<std::endl;
			Pt_trkJetTTTsel.push_back((*Pt_TTTtrkjet)[it1]);
			Eta_trkJetTTTsel.push_back((*Eta_TTTtrkjet)[it1]);
			Phi_trkJetTTTsel.push_back((*Phi_TTTtrkjet)[it1]);
		}
		//! loop over the truthPt of this event and fill the leading pt SM higgs
		
		//! increment n4_tot if there are atleast 4 jets with pt > xbins[i]
		if (Pt_trkJetTTTsel.size() >= Njet_max-1)
		{
			h_trigeffnum4->Fill(Pt_leadingSMh);
			h_trigeffnum3->Fill(Pt_leadingSMh);
			h_trigeffnum2->Fill(Pt_leadingSMh);
			h_trigeffnum1->Fill(Pt_leadingSMh);
			if(debug) std::cout<<" Num :atleast 4 jets, Pt_leading SMh : " << Pt_leadingSMh << std::endl; 
			
		}
		//! increment n3_tot if there are atleast 3 jets with pt > xbins[i]
		else if (Pt_trkJetTTTsel.size() >= Njet_max-2)
		{
			h_trigeffnum3->Fill(Pt_leadingSMh);
			h_trigeffnum2->Fill(Pt_leadingSMh);
			h_trigeffnum1->Fill(Pt_leadingSMh);
			if(debug) std::cout<<" Num :atleast 3 jets, Pt_leading SMh : " << Pt_leadingSMh << std::endl; 
			
		}
		//! increment n2_tot if there are atleast 2 jets with pt > xbins[i]
		else if (Pt_trkJetTTTsel.size() >= Njet_max-3)
		{
			h_trigeffnum2->Fill(Pt_leadingSMh);
			h_trigeffnum1->Fill(Pt_leadingSMh);
			if(debug) std::cout<<" Num :atleast 2 jets, Pt_leading SMh : " << Pt_leadingSMh << std::endl; 
			
		}
		//! increment n2_tot if there are atleast 2 jets with pt > xbins[i]
		else if (Pt_trkJetTTTsel.size() >= Njet_max-4)
		{
			h_trigeffnum1->Fill(Pt_leadingSMh);
			if(debug) std::cout<<" Num :atleast 1 jets, Pt_leading SMh : " << Pt_leadingSMh << std::endl; 
			
		}

		
	}

	TH1* h_trigeffN1_v1 = dynamic_cast<TH1*>(h_trigeffnum1->Clone("h_trigeffN1_v1"));
	h_trigeffN1_v1->SetTitle("Trigger Efficiency vs P_{t};Leading Higgs P_{t} [MeV/c];#epsilon_{Njet}");
	h_trigeffN1_v1->Divide(h_trigeffnum1, h_trigeffden1, 1.0, 1.0, "B");
	h_trigeffN1_v1->GetYaxis()->SetRangeUser(0.0, 1.5);
	h_trigeffN1_v1->SetMarkerSize(1.2);
	h_trigeffN1_v1->SetMarkerStyle(kFullTriangleDown);
	h_trigeffN1_v1->SetMarkerColor(kBlack);	
	TH1* h_trigeffN2_v1 = dynamic_cast<TH1*>(h_trigeffnum2->Clone("h_trigeffN2_v1"));
	h_trigeffN2_v1->SetTitle("Trigger Efficiency vs P_{t};Leading Higgs P_{t} [MeV/c];#epsilon_{Njet}");
	h_trigeffN2_v1->Divide(h_trigeffnum2, h_trigeffden1, 1.0, 1.0, "B");
	h_trigeffN2_v1->GetYaxis()->SetRangeUser(0.0, 1.5);
	h_trigeffN2_v1->SetMarkerSize(1.2);
	h_trigeffN2_v1->SetMarkerStyle(kFullTriangleDown);
	h_trigeffN2_v1->SetMarkerColor(kRed);	
	TH1* h_trigeffN3_v1 = dynamic_cast<TH1*>(h_trigeffnum3->Clone("h_trigeffN3_v1"));
	h_trigeffN3_v1->SetTitle("Trigger Efficiency vs P_{t};Leading Higgs P_{t} [MeV/c];#epsilon_{Njet}");
	h_trigeffN3_v1->Divide(h_trigeffnum3, h_trigeffden1, 1.0, 1.0, "B");
	h_trigeffN3_v1->GetYaxis()->SetRangeUser(0.0, 1.5);
	h_trigeffN3_v1->SetMarkerSize(1.2);
	h_trigeffN3_v1->SetMarkerStyle(kFullTriangleDown);
	h_trigeffN3_v1->SetMarkerColor(kGreen);	
	TH1* h_trigeffN4_v1 = dynamic_cast<TH1*>(h_trigeffnum4->Clone("h_trigeffN4_v1"));
	h_trigeffN4_v1->SetTitle("Trigger Efficiency vs P_{t};Leading Higgs P_{t} [MeV/c];#epsilon_{Njet}");
	h_trigeffN4_v1->Divide(h_trigeffnum4, h_trigeffden1, 1.0, 1.0, "B");
	h_trigeffN4_v1->GetYaxis()->SetRangeUser(0.0, 1.5);
	h_trigeffN4_v1->SetMarkerSize(1.2);
	h_trigeffN4_v1->SetMarkerStyle(kFullTriangleDown);
	h_trigeffN4_v1->SetMarkerColor(kBlue);	

	TH1* h_trigeffN1_v2 = dynamic_cast<TH1*>(h_trigeffnum1->Clone("h_trigeffN1_v2"));
	h_trigeffN1_v2->SetTitle("Trigger Efficiency vs P_{t};Leading Higgs P_{t} [MeV/c];#epsilon_{Njet}");
	h_trigeffN1_v2->Divide(h_trigeffnum1, h_trigeffden1, 1.0, 1.0, "B");
	h_trigeffN1_v2->GetYaxis()->SetRangeUser(0.0, 1.5);
	h_trigeffN1_v2->SetMarkerSize(1.2);
	h_trigeffN1_v2->SetMarkerStyle(kFullTriangleDown);
	h_trigeffN1_v2->SetMarkerColor(kBlack);	
	TH1* h_trigeffN2_v2 = dynamic_cast<TH1*>(h_trigeffnum2->Clone("h_trigeffN2_v2"));
	h_trigeffN2_v2->SetTitle("Trigger Efficiency vs P_{t};Leading Higgs P_{t} [MeV/c];#epsilon_{Njet}");
	h_trigeffN2_v2->Divide(h_trigeffnum2, h_trigeffden2, 1.0, 1.0, "B");
	h_trigeffN2_v2->GetYaxis()->SetRangeUser(0.0, 1.5);
	h_trigeffN2_v2->SetMarkerSize(1.2);
	h_trigeffN2_v2->SetMarkerStyle(kFullTriangleDown);
	h_trigeffN2_v2->SetMarkerColor(kRed);	
	TH1* h_trigeffN3_v2 = dynamic_cast<TH1*>(h_trigeffnum3->Clone("h_trigeffN3_v2"));
	h_trigeffN3_v2->SetTitle("Trigger Efficiency vs P_{t};Leading Higgs P_{t} [MeV/c];#epsilon_{Njet}");
	h_trigeffN3_v2->Divide(h_trigeffnum3, h_trigeffden3, 1.0, 1.0, "B");
	h_trigeffN3_v2->GetYaxis()->SetRangeUser(0.0, 1.5);
	h_trigeffN3_v2->SetMarkerSize(1.2);
	h_trigeffN3_v2->SetMarkerStyle(kFullTriangleDown);
	h_trigeffN3_v2->SetMarkerColor(kGreen);	
	TH1* h_trigeffN4_v2 = dynamic_cast<TH1*>(h_trigeffnum4->Clone("h_trigeffN4_v2"));
	h_trigeffN4_v2->SetTitle("Trigger Efficiency vs P_{t};Leading Higgs P_{t} [MeV/c];#epsilon_{Njet}");
	h_trigeffN4_v2->Divide(h_trigeffnum4, h_trigeffden4, 1.0, 1.0, "B");
	h_trigeffN4_v2->GetYaxis()->SetRangeUser(0.0, 1.5);
	h_trigeffN4_v2->SetMarkerSize(1.2);
	h_trigeffN4_v2->SetMarkerStyle(kFullTriangleDown);
	h_trigeffN4_v2->SetMarkerColor(kBlue);	


        Double_t x1= 0.6,y1= 0.75, x2 = 0.89, y2 = 0.89;
        Double_t xx1= 0.105,yy1= 0.75, xx2 = 0.22, yy2 = 0.89;
	TCanvas* c1  = new TCanvas();
        gStyle->SetOptStat(0);

	h_trigeffN1_v1->Draw();
	h_trigeffN2_v1->Draw("same");
	h_trigeffN3_v1->Draw("same");
	h_trigeffN4_v1->Draw("same");
        TLegend *leg1=new TLegend(x1,y1,x2,y2,"Atleast N triplet track jets");
	leg1->SetFillColor(kWhite);
	leg1->SetBorderSize(0);
        leg1->AddEntry(h_trigeffN1_v1,"1 triplet track jet","p");
        leg1->AddEntry(h_trigeffN2_v1,"2 triplet track jets","p");
        leg1->AddEntry(h_trigeffN3_v1,"3 triplet track jets","p");
        leg1->AddEntry(h_trigeffN4_v1,"4 triplet track jets","p");
	leg1->SetTextAlign(12);
	leg1->SetTextSize(0.035);
        leg1->Draw();
        auto leg1a=new TLegend(xx1,yy1,xx2,yy2,"cuts used");
	leg1a->SetFillColor(kWhite);
	leg1a->SetBorderSize(0);
        leg1a->AddEntry((TObject*)0,"pt > 50 GeV/c","");
        leg1a->AddEntry((TObject*)0,"abs(#eta) < 1.5","");
	leg1a->SetTextAlign(32);
	leg1a->SetTextSize(0.035);
        leg1a->Draw();
	c1->Update();

	TCanvas* c2  = new TCanvas();
	h_trigeffN1_v2->Draw();
	h_trigeffN2_v2->Draw("same");
	h_trigeffN3_v2->Draw("same");
	h_trigeffN4_v2->Draw("same");
        TLegend *leg2=new TLegend(x1,y1,x2,y2,"Atleast N triplet track jets");
	leg2->SetFillColor(kWhite);
	leg2->SetBorderSize(0);
	leg2->SetTextAlign(32);
	leg2->SetTextSize(0.035);
        leg2->AddEntry(h_trigeffN1_v2,"1 triplet track jet","p");
        leg2->AddEntry(h_trigeffN2_v2,"2 triplet track jets","p");
        leg2->AddEntry(h_trigeffN3_v2,"3 triplet track jets","p");
        leg2->AddEntry(h_trigeffN4_v2,"4 triplet track jets","p");
        leg2->Draw();
	leg1a->Draw();
	c2->Update();

	char out_file_root[1023];
        sprintf(out_file_root,"%s/%s.root",out_path,output_file_name);
	TFile* output_file = new TFile(out_file_root, "RECREATE");

	h_trigeffnum4->Write();
	h_trigeffnum3->Write();
	h_trigeffnum2->Write();
	h_trigeffnum1->Write();
	h_trigeffden4->Write();
	h_trigeffden3->Write();
	h_trigeffden2->Write();
	h_trigeffden1->Write();

	h_trigeffN1_v1->Write();
	h_trigeffN2_v1->Write();
	h_trigeffN3_v1->Write();
	h_trigeffN4_v1->Write();
	h_trigeffN1_v2->Write();
	h_trigeffN2_v2->Write();
	h_trigeffN3_v2->Write();
	h_trigeffN4_v2->Write();
	c1->Write();
	c2->Write();
	output_file->Close();

return 0;
}
