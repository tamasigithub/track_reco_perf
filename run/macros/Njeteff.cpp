////////////////////NJET efficiency matched to Higgs pt///////////////////
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

const char* out_path = "/nfs/dust/atlas/user/tkar/derivations/run/macros";

int Njeteff(const char* output_file_name = "testNjetcaloTTT", bool debug = true)
{
	//! selections
	int Njet_max = 5;
	const float pt_cut = 60e3;
	const float eta_cut = 1.5;
	const float jvf_cut = 0.6;
	const float jvt_cut = 0.6;
	//! load input files
	TChain tree("m_collectionTree");
	tree.Add("./../test_ntuple.root");
	if(debug) std::cout<<"m_collectionTree opened with " << tree.GetEntries() << " entries" <<std::endl;

	std::vector<float> *Pt_truth = 0;
	std::vector<float> *Pdg_truth = 0;
	std::vector<float> *Eta_truth = 0;
	std::vector<float> *Phi_truth = 0;
        std::vector<float> *Pt_caloTTTjet = 0;
        std::vector<float> *Eta_caloTTTjet = 0;
        std::vector<float> *Phi_caloTTTjet = 0;
        std::vector<float> *JVT_caloTTTjet = 0;
        std::vector<float> *JVF_caloTTTjet = 0;
	//! container consisting of selected calo jets
        float Pt_leadingSMh;
	std::vector<float> Pt_SMh ;
        std::vector<float> Pt_b ;
        std::vector<float> Eta_b ;
        std::vector<float> Pt_caloTTTsel ;
        std::vector<float> Eta_caloTTTsel ;
        std::vector<float> Phi_caloTTTsel ;
        std::vector<float> JVT_caloTTTsel ;
        std::vector<float> JVF_caloTTTsel ;
	tree.SetBranchStatus("truthPt", 1);
	tree.SetBranchStatus("truthPdg",1);
	tree.SetBranchStatus("truthEta",1);
	tree.SetBranchStatus("truthPhi",1);
	/*tree.SetBranchStatus("caloTTTjetPt",1);
	tree.SetBranchStatus("caloTTTjetEta",1);
	tree.SetBranchStatus("caloTTTjetPhi",1);
	tree.SetBranchStatus("caloTTTjetJVT",1);
	tree.SetBranchStatus("caloTTTjetJVF",1);*/
	tree.SetBranchStatus("caloStdjetPt",1);
	tree.SetBranchStatus("caloStdjetEta",1);
	tree.SetBranchStatus("caloStdjetPhi",1);
	tree.SetBranchStatus("caloStdjetJVT",1);
	tree.SetBranchStatus("caloStdjetJVF",1);
	tree.SetBranchAddress("truthPt", &Pt_truth);
	tree.SetBranchAddress("truthPdg",&Pdg_truth);
	tree.SetBranchAddress("truthEta",&Eta_truth);
	tree.SetBranchAddress("truthPhi",&Phi_truth);
	tree.SetBranchAddress("caloStdjetPt", &Pt_caloTTTjet );
	tree.SetBranchAddress("caloStdjetEta",&Eta_caloTTTjet);
	tree.SetBranchAddress("caloStdjetPhi",&Phi_caloTTTjet);
	tree.SetBranchAddress("caloStdjetJVT",&JVT_caloTTTjet);
	tree.SetBranchAddress("caloStdjetJVF",&JVF_caloTTTjet);
        Long64_t n_entries = tree.GetEntries();
	
	const float pt_min = 5e3, pt_max = 500e3; //! in MeV
	Int_t nbins = 50;	

	//! book histograms
	TH1::SetDefaultSumw2(true);
	TH1* h_trigeffnum1 = new TH1F("h_trigeffnum1"," Numerator counts : trigger efficiency for SM higgs", nbins, pt_min, pt_max);
	TH1* h_trigeffnum2 = new TH1F("h_trigeffnum2"," Numerator counts : trigger efficiency for SM higgs", nbins, pt_min, pt_max);
	TH1* h_trigeffnum3 = new TH1F("h_trigeffnum3"," Numerator counts : trigger efficiency for SM higgs", nbins, pt_min, pt_max);
	TH1* h_trigeffnum4 = new TH1F("h_trigeffnum4"," Numerator counts : trigger efficiency for SM higgs", nbins, pt_min, pt_max);
	TH1* h_trigeffnum5 = new TH1F("h_trigeffnum5"," Numerator counts : trigger efficiency for SM higgs", nbins, pt_min, pt_max);
	TH1* h_trigeffden1 = new TH1F("h_trigeffden1"," Denominator counts: trigger efficiency for SM higgs", nbins, pt_min, pt_max);
	TH1* h_trigeffden2 = new TH1F("h_trigeffden2"," Denominator counts: trigger efficiency for SM higgs", nbins, pt_min, pt_max);
	TH1* h_trigeffden3 = new TH1F("h_trigeffden3"," Denominator counts: trigger efficiency for SM higgs", nbins, pt_min, pt_max);
	TH1* h_trigeffden4 = new TH1F("h_trigeffden4"," Denominator counts: trigger efficiency for SM higgs", nbins, pt_min, pt_max);
	TH1* h_trigeffden5 = new TH1F("h_trigeffden5"," Denominator counts: trigger efficiency for SM higgs", nbins, pt_min, pt_max);

	//! loop over the tree and get the entries into the local variable
	for(int it = 0; it < n_entries; it++)
	{
		Pt_leadingSMh = 0;
		Pt_SMh.clear(); 
		Pt_b.clear(); 
		Eta_b.clear(); 
		Pt_caloTTTsel.clear(); 
		Eta_caloTTTsel.clear();
		Phi_caloTTTsel.clear();
		JVT_caloTTTsel.clear();
		JVF_caloTTTsel.clear();

		Pt_caloTTTjet->clear(); 
		Eta_caloTTTjet->clear();
		Phi_caloTTTjet->clear();
		JVT_caloTTTjet->clear();
		JVF_caloTTTjet->clear();

		Pt_truth->clear();
		Pdg_truth->clear();	
		Eta_truth->clear();
		Phi_truth->clear();

		tree.GetEntry(it);
		//! find the leading pt SM higgs in this event if there is atleast one bjet satisfying the selection cuts
		for(int it0 = 0; it0 < Pt_truth->size(); ++it0)
		{
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
	
		if(Pt_b.size() >= Njet_max && Pt_SMh.size()>0) 
		{
			Pt_leadingSMh = *std::max_element(Pt_SMh.begin(), Pt_SMh.end());
		
			h_trigeffden5->Fill(Pt_leadingSMh);
			h_trigeffden4->Fill(Pt_leadingSMh);
			h_trigeffden3->Fill(Pt_leadingSMh);
			h_trigeffden2->Fill(Pt_leadingSMh);
			h_trigeffden1->Fill(Pt_leadingSMh);
		}
		else if(Pt_b.size() >= Njet_max-1  && Pt_SMh.size()>0) 
		{
			Pt_leadingSMh = *std::max_element(Pt_SMh.begin(), Pt_SMh.end());
		
			h_trigeffden4->Fill(Pt_leadingSMh);
			h_trigeffden3->Fill(Pt_leadingSMh);
			h_trigeffden2->Fill(Pt_leadingSMh);
			h_trigeffden1->Fill(Pt_leadingSMh);
		}
		else if(Pt_b.size() >= Njet_max-2 && Pt_SMh.size()>0) 
		{
			Pt_leadingSMh = *std::max_element(Pt_SMh.begin(), Pt_SMh.end());
		
			h_trigeffden3->Fill(Pt_leadingSMh);
			h_trigeffden2->Fill(Pt_leadingSMh);
			h_trigeffden1->Fill(Pt_leadingSMh);
		}
		else if(Pt_b.size() >= Njet_max-3 && Pt_SMh.size()>0) 
		{
			Pt_leadingSMh = *std::max_element(Pt_SMh.begin(), Pt_SMh.end());
		
			h_trigeffden2->Fill(Pt_leadingSMh);
			h_trigeffden1->Fill(Pt_leadingSMh);
		}
		else if(Pt_b.size() >= Njet_max-4 && Pt_SMh.size()>0) 
		{
			Pt_leadingSMh = *std::max_element(Pt_SMh.begin(), Pt_SMh.end());
		
			h_trigeffden1->Fill(Pt_leadingSMh);
		}
		else continue;// go to the next event if denominator is zero

		//! Numerator selection
		for(int it1 = 0; it1 < Pt_caloTTTjet->size(); ++it1)
		{
			//! apply cuts on calo jets
			if((*Pt_caloTTTjet)[it1] < pt_cut) continue;
			if(std::abs((*Eta_caloTTTjet)[it1]) < eta_cut) continue;
			if((*JVF_caloTTTjet)[it1] < jvf_cut) continue;
			//if((*JVT_caloTTTjet)[it1] < jvt_cut) continue;

			Pt_caloTTTsel.push_back((*Pt_caloTTTjet)[it1]);
			Eta_caloTTTsel.push_back((*Eta_caloTTTjet)[it1]);
			Phi_caloTTTsel.push_back((*Phi_caloTTTjet)[it1]);
			JVF_caloTTTsel.push_back((*JVF_caloTTTjet)[it1]);
			JVT_caloTTTsel.push_back((*JVT_caloTTTjet)[it1]);
		}
		//! if there are atleast 5 jets after the above selections in this event
		//! loop over the truthPt of this event and fill the leading pt SM higgs
		if(Pt_caloTTTsel.size() >= Njet_max)
		{
			h_trigeffnum5->Fill(Pt_leadingSMh);
			h_trigeffnum4->Fill(Pt_leadingSMh);
			h_trigeffnum3->Fill(Pt_leadingSMh);
			h_trigeffnum2->Fill(Pt_leadingSMh);
			h_trigeffnum1->Fill(Pt_leadingSMh);
		}
		//! increment n4_tot if there are atleast 4 jets with pt > xbins[i]
		else if (Pt_caloTTTsel.size() >= Njet_max-1)
		{
			h_trigeffnum4->Fill(Pt_leadingSMh);
			h_trigeffnum3->Fill(Pt_leadingSMh);
			h_trigeffnum2->Fill(Pt_leadingSMh);
			h_trigeffnum1->Fill(Pt_leadingSMh);
			
		}
		//! increment n3_tot if there are atleast 3 jets with pt > xbins[i]
		else if (Pt_caloTTTsel.size() >= Njet_max-2)
		{
			h_trigeffnum3->Fill(Pt_leadingSMh);
			h_trigeffnum2->Fill(Pt_leadingSMh);
			h_trigeffnum1->Fill(Pt_leadingSMh);
			
		}
		//! increment n2_tot if there are atleast 2 jets with pt > xbins[i]
		else if (Pt_caloTTTsel.size() >= Njet_max-3)
		{
			h_trigeffnum2->Fill(Pt_leadingSMh);
			h_trigeffnum1->Fill(Pt_leadingSMh);
			
		}
		//! increment n2_tot if there are atleast 2 jets with pt > xbins[i]
		else if (Pt_caloTTTsel.size() >= Njet_max-4)
		{
			h_trigeffnum1->Fill(Pt_leadingSMh);
			
		}

		
	}

	TH1* h_trigeffN1_v1 = dynamic_cast<TH1*>(h_trigeffnum1->Clone("h_trigeffN1_v1"));
	h_trigeffN1_v1->SetTitle("Trigger Efficiency vs P_{t};P_{t} [MeV/c];#epsilon_{Njet}");
	h_trigeffN1_v1->Divide(h_trigeffnum1, h_trigeffden1, 1.0, 1.0, "B");
	h_trigeffN1_v1->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_trigeffN1_v1->SetMarkerSize(0.95);
	h_trigeffN1_v1->SetMarkerStyle(kOpenTriangleDown);
	h_trigeffN1_v1->SetMarkerColor(kBlack);	
	TH1* h_trigeffN2_v1 = dynamic_cast<TH1*>(h_trigeffnum2->Clone("h_trigeffN2_v1"));
	h_trigeffN2_v1->SetTitle("Trigger Efficiency vs P_{t};P_{t} [MeV/c];#epsilon_{Njet}");
	h_trigeffN2_v1->Divide(h_trigeffnum2, h_trigeffden1, 1.0, 1.0, "B");
	h_trigeffN2_v1->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_trigeffN2_v1->SetMarkerSize(0.95);
	h_trigeffN2_v1->SetMarkerStyle(kOpenTriangleDown);
	h_trigeffN2_v1->SetMarkerColor(kBlack);	
	TH1* h_trigeffN3_v1 = dynamic_cast<TH1*>(h_trigeffnum3->Clone("h_trigeffN3_v1"));
	h_trigeffN3_v1->SetTitle("Trigger Efficiency vs P_{t};P_{t} [MeV/c];#epsilon_{Njet}");
	h_trigeffN3_v1->Divide(h_trigeffnum3, h_trigeffden1, 1.0, 1.0, "B");
	h_trigeffN3_v1->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_trigeffN3_v1->SetMarkerSize(0.95);
	h_trigeffN3_v1->SetMarkerStyle(kOpenTriangleDown);
	h_trigeffN3_v1->SetMarkerColor(kBlack);	
	TH1* h_trigeffN4_v1 = dynamic_cast<TH1*>(h_trigeffnum4->Clone("h_trigeffN4_v1"));
	h_trigeffN4_v1->SetTitle("Trigger Efficiency vs P_{t};P_{t} [MeV/c];#epsilon_{Njet}");
	h_trigeffN4_v1->Divide(h_trigeffnum4, h_trigeffden1, 1.0, 1.0, "B");
	h_trigeffN4_v1->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_trigeffN4_v1->SetMarkerSize(0.95);
	h_trigeffN4_v1->SetMarkerStyle(kOpenTriangleDown);
	h_trigeffN4_v1->SetMarkerColor(kBlack);	
	TH1* h_trigeffN5_v1 = dynamic_cast<TH1*>(h_trigeffnum5->Clone("h_trigeffN5_v1"));
	h_trigeffN5_v1->SetTitle("Trigger Efficiency vs P_{t};P_{t} [MeV/c];#epsilon_{Njet}");
	h_trigeffN5_v1->Divide(h_trigeffnum5, h_trigeffden1, 1.0, 1.0, "B");
	h_trigeffN5_v1->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_trigeffN5_v1->SetMarkerSize(0.95);
	h_trigeffN5_v1->SetMarkerStyle(kOpenTriangleDown);
	h_trigeffN5_v1->SetMarkerColor(kBlack);	

	TH1* h_trigeffN1_v2 = dynamic_cast<TH1*>(h_trigeffnum1->Clone("h_trigeffN1_v2"));
	h_trigeffN1_v2->SetTitle("Trigger Efficiency vs P_{t};P_{t} [MeV/c];#epsilon_{Njet}");
	h_trigeffN1_v2->Divide(h_trigeffnum1, h_trigeffden1, 1.0, 1.0, "B");
	h_trigeffN1_v2->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_trigeffN1_v2->SetMarkerSize(0.95);
	h_trigeffN1_v2->SetMarkerStyle(kOpenTriangleDown);
	h_trigeffN1_v2->SetMarkerColor(kBlack);	
	TH1* h_trigeffN2_v2 = dynamic_cast<TH1*>(h_trigeffnum2->Clone("h_trigeffN2_v2"));
	h_trigeffN2_v2->SetTitle("Trigger Efficiency vs P_{t};P_{t} [MeV/c];#epsilon_{Njet}");
	h_trigeffN2_v2->Divide(h_trigeffnum2, h_trigeffden2, 1.0, 1.0, "B");
	h_trigeffN2_v2->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_trigeffN2_v2->SetMarkerSize(0.95);
	h_trigeffN2_v2->SetMarkerStyle(kOpenTriangleDown);
	h_trigeffN2_v2->SetMarkerColor(kBlack);	
	TH1* h_trigeffN3_v2 = dynamic_cast<TH1*>(h_trigeffnum3->Clone("h_trigeffN3_v2"));
	h_trigeffN3_v2->SetTitle("Trigger Efficiency vs P_{t};P_{t} [MeV/c];#epsilon_{Njet}");
	h_trigeffN3_v2->Divide(h_trigeffnum3, h_trigeffden3, 1.0, 1.0, "B");
	h_trigeffN3_v2->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_trigeffN3_v2->SetMarkerSize(0.95);
	h_trigeffN3_v2->SetMarkerStyle(kOpenTriangleDown);
	h_trigeffN3_v2->SetMarkerColor(kBlack);	
	TH1* h_trigeffN4_v2 = dynamic_cast<TH1*>(h_trigeffnum4->Clone("h_trigeffN4_v2"));
	h_trigeffN4_v2->SetTitle("Trigger Efficiency vs P_{t};P_{t} [MeV/c];#epsilon_{Njet}");
	h_trigeffN4_v2->Divide(h_trigeffnum4, h_trigeffden4, 1.0, 1.0, "B");
	h_trigeffN4_v2->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_trigeffN4_v2->SetMarkerSize(0.95);
	h_trigeffN4_v2->SetMarkerStyle(kOpenTriangleDown);
	h_trigeffN4_v2->SetMarkerColor(kBlack);	
	TH1* h_trigeffN5_v2 = dynamic_cast<TH1*>(h_trigeffnum5->Clone("h_trigeffN5_v2"));
	h_trigeffN5_v2->SetTitle("Trigger Efficiency vs P_{t};P_{t} [MeV/c];#epsilon_{Njet}");
	h_trigeffN5_v2->Divide(h_trigeffnum5, h_trigeffden5, 1.0, 1.0, "B");
	h_trigeffN5_v2->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_trigeffN5_v2->SetMarkerSize(0.95);
	h_trigeffN5_v2->SetMarkerStyle(kOpenTriangleDown);
	h_trigeffN5_v2->SetMarkerColor(kBlack);	

	TCanvas* c  = new TCanvas();

	h_trigeffN1_v1->Draw();
	h_trigeffN2_v1->Draw();
	h_trigeffN3_v1->Draw();
	h_trigeffN4_v1->Draw();
	h_trigeffN5_v1->Draw();
	h_trigeffN1_v2->Draw();
	h_trigeffN2_v2->Draw();
	h_trigeffN3_v2->Draw();
	h_trigeffN4_v2->Draw();
	h_trigeffN5_v2->Draw();

	char out_file_root[1023];
        sprintf(out_file_root,"%s/%s.root",out_path,output_file_name);
	TFile* output_file = new TFile(out_file_root, "RECREATE");

	h_trigeffnum5->Write();
	h_trigeffnum4->Write();
	h_trigeffnum3->Write();
	h_trigeffnum2->Write();
	h_trigeffnum1->Write();
	h_trigeffden5->Write();
	h_trigeffden4->Write();
	h_trigeffden3->Write();
	h_trigeffden2->Write();
	h_trigeffden1->Write();


	h_trigeffN1_v1->Write();
	h_trigeffN2_v1->Write();
	h_trigeffN3_v1->Write();
	h_trigeffN4_v1->Write();
	h_trigeffN5_v1->Write();
	h_trigeffN1_v2->Write();
	h_trigeffN2_v2->Write();
	h_trigeffN3_v2->Write();
	h_trigeffN4_v2->Write();
	h_trigeffN5_v2->Write();       
	output_file->Close();

return 0;
}
