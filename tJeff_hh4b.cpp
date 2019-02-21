///////////////////Track jet efficiency for different pt cuts///////////////////
//
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

int tJeff_hh4b(const char* output_file_name = "test", bool debug = false)
{
	//! selections
	int Njet_max = 5;
	float eta_cut = 1.5;
	//! load input files
	TChain tree("m_collectionTree");
	tree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/user.tkar.hh4bsig5_16_ntuples1_MYSTREAM/*.root");
	if(debug) std::cout<<"m_collectionTree opened with " << tree.GetEntries() << " entries" <<std::endl;

	std::vector<float> *Pt_ttt4trkjet = 0;
        std::vector<float> *Eta_ttt4trkjet = 0;
	tree.SetBranchStatus("ttt4trkjetPt",1);
        tree.SetBranchStatus("ttt4trkjetEta",1);
        tree.SetBranchAddress("ttt4trkjetPt", &Pt_ttt4trkjet);
        tree.SetBranchAddress("ttt4trkjetEta", &Eta_ttt4trkjet);
	/*tree.SetBranchStatus("ttt2trkjetPt",1);
        tree.SetBranchStatus("ttt2trkjetEta",1);
        tree.SetBranchAddress("ttt2trkjetPt", &Pt_ttt4trkjet);
        tree.SetBranchAddress("ttt2trkjetEta", &Eta_ttt4trkjet);*/
        Long64_t n_entries = tree.GetEntries();
	
	const float pt_min = 0, pt_max = 100e3; //! in MeV
	const float ptcut_width = 5e3; 
	const int nbins = pt_max/ptcut_width;
	if(debug)
	{
		std::cout<<"pt_min, pt_max : " << pt_min << ", " << pt_max <<std::endl;
		std::cout<<"ptcut_width, nbins : " << ptcut_width << ", " << nbins <<std::endl;
	}		
	Float_t xbins[nbins + 1];
	for(int i = 0; i <= nbins; i++)
	{
		xbins[i] = pt_min + i*ptcut_width;
		if(debug) std::cout<< "xbin[ " << i << "] : " <<xbins[i] <<std::endl; 
	}

	//! book histograms
	TH1::SetDefaultSumw2(true);
	TH1* h_tJeff2 = new TH1F("h_tJeff2"," Track Jet efficiency", nbins, xbins);
	TH1* h_tJeff3 = new TH1F("h_tJeff3"," Track Jet efficiency", nbins, xbins);
	TH1* h_tJeff4 = new TH1F("h_tJeff4"," Track Jet efficiency", nbins, xbins);
	TH1* h_tJeff5 = new TH1F("h_tJeff5"," Track Jet efficiency", nbins, xbins);

	//! define local parameters to fill the histograms
	int n2_tot[20] = {0};
	int n3_tot[20] = {0};
	int n4_tot[20] = {0};
	int n5_tot[20] = {0};

	/*int n2_tot[10] = {0};
	int n3_tot[10] = {0};
	int n4_tot[10] = {0};
	int n5_tot[10] = {0};*/
	//! loop over the tree and get the entries into the local variable
	for(int it = 0; it < n_entries; it++)
	{
		tree.GetEntry(it);
		
		for(int i2 = 0; i2 < nbins; i2++)
		{
			//! increment n5_tot if there are atleast 5 jets with pt > xbins[i]
			if(Pt_ttt4trkjet->size() >= Njet_max)
			{
				if((*Pt_ttt4trkjet)[4] > xbins[i2]) n5_tot[i2] += 1;
				if((*Pt_ttt4trkjet)[3] > xbins[i2]) n4_tot[i2] += 1;
				if((*Pt_ttt4trkjet)[2] > xbins[i2]) n3_tot[i2] += 1;
				if((*Pt_ttt4trkjet)[1] > xbins[i2]) n2_tot[i2] += 1;
			}
			//! increment n4_tot if there are atleast 4 jets with pt > xbins[i]
			else if (Pt_ttt4trkjet->size() >= Njet_max-1)
			{
				if((*Pt_ttt4trkjet)[3] > xbins[i2]) n4_tot[i2] += 1;
				if((*Pt_ttt4trkjet)[2] > xbins[i2]) n3_tot[i2] += 1;
				if((*Pt_ttt4trkjet)[1] > xbins[i2]) n2_tot[i2] += 1;
				
			}
			//! increment n3_tot if there are atleast 3 jets with pt > xbins[i]
			else if (Pt_ttt4trkjet->size() >= Njet_max-2)
			{
				if((*Pt_ttt4trkjet)[2] > xbins[i2]) n3_tot[i2] += 1;
				if((*Pt_ttt4trkjet)[1] > xbins[i2]) n2_tot[i2] += 1;
				
			}
			//! increment n2_tot if there are atleast 2 jets with pt > xbins[i]
			else if (Pt_ttt4trkjet->size() >= Njet_max-3)
			{
				if((*Pt_ttt4trkjet)[1] > xbins[i2]) n2_tot[i2] += 1;
				
			}
		}

		
	}
	if(debug)
	{
		for(int ii=0; ii<nbins; ii++)
		{
			std::cout<< "n5_tot[ " << ii << "] : " <<n5_tot[ii] << ",   " <<  "n4_tot[ " << ii << "] : " <<n4_tot[ii] << ",   " << "n3_tot[ " << ii << "] : " <<n3_tot[ii] << ",   " << "n2_tot[ " << ii << "] : " <<n2_tot[ii] <<std::endl;
		}
	}
	//! Fill the jth bin of the respective histograms with the corresponding weight 
	for(int j = 0; j < nbins; ++j)
	{
		h_tJeff5->Fill(xbins[j], (1.0*n5_tot[j])/n5_tot[0]);
		h_tJeff4->Fill(xbins[j], (1.0*n4_tot[j])/n4_tot[0]);
		h_tJeff3->Fill(xbins[j], (1.0*n3_tot[j])/n3_tot[0]);
		h_tJeff2->Fill(xbins[j], (1.0*n2_tot[j])/n2_tot[0]);
	
		/*h_tJeff5->Fill(xbins[j], (1.0*n5_tot[j])/n_entries);
		h_tJeff4->Fill(xbins[j], (1.0*n4_tot[j])/n_entries);
		h_tJeff3->Fill(xbins[j], (1.0*n3_tot[j])/n_entries);
		h_tJeff2->Fill(xbins[j], (1.0*n2_tot[j])/n_entries);*/
	}
	TCanvas* c  = new TCanvas();

	h_tJeff5->Draw("hist");
	h_tJeff4->Draw("hist");
	h_tJeff3->Draw("hist");
	h_tJeff2->Draw("hist");

	h_tJeff5->SetLineColor(kBlue);
	h_tJeff4->SetLineColor(kGreen);
	h_tJeff3->SetLineColor(kRed);
	h_tJeff2->SetLineColor(kBlack);

	h_tJeff5->SetLineWidth(3);
	h_tJeff4->SetLineWidth(3);
	h_tJeff3->SetLineWidth(3);
	h_tJeff2->SetLineWidth(3);

	h_tJeff5->GetYaxis()->SetTitle("#epsilon_{Njets}");
	h_tJeff4->GetYaxis()->SetTitle("#epsilon_{Njets}");
	h_tJeff3->GetYaxis()->SetTitle("#epsilon_{Njets}");
	h_tJeff2->GetYaxis()->SetTitle("#epsilon_{Njets}");

	h_tJeff5->GetXaxis()->SetTitle("P_{t} [MeV/c]");
	h_tJeff4->GetXaxis()->SetTitle("P_{t} [MeV/c]");
	h_tJeff3->GetXaxis()->SetTitle("P_{t} [MeV/c]");
	h_tJeff2->GetXaxis()->SetTitle("P_{t} [MeV/c]");


	char out_file_root[1023];
        sprintf(out_file_root,"%s/%s.root",out_path,output_file_name);
        TFile* output_file = new TFile(out_file_root, "RECREATE");
	h_tJeff5->Write();
	h_tJeff4->Write();
	h_tJeff3->Write();
	h_tJeff2->Write();
	output_file->Close();

        //! Save as pdf
        char out_file_open[1023];
        sprintf(out_file_open,"%s/%s.pdf(",out_path,output_file_name);
        char out_file_[1023];
        sprintf(out_file_,"%s/%s.pdf",out_path,output_file_name);
        char out_file_close[1023];
        sprintf(out_file_close,"%s/%s.pdf)",out_path,output_file_name);

        TCanvas *C = new TCanvas();
        gStyle->SetOptStat(0);

        h_tJeff2->Draw("hist");
        C->Print(out_file_open,"pdf");
        h_tJeff3->Draw("hist");
        C->Print(out_file_,"pdf");
        h_tJeff4->Draw("hist");
        C->Print(out_file_,"pdf");
        h_tJeff5->Draw("hist");
        C->Print(out_file_,"pdf");


        //! plot same
        Double_t x1= 0.805,y1= 0.6, x2 = 0.995, y2 = 0.9;

        //PUNNNLpt->GetYaxis()->SetRangeUser(1e-2, 5 * h_tJeff2->GetMaximum());
        h_tJeff5->Draw("hist");
        h_tJeff4->Draw("hist same");
        h_tJeff3->Draw("hist same");
        h_tJeff2->Draw("hist same");
        TLegend *leg2=new TLegend(x1,y1,x2,y2,"Atleast N track jets");
        leg2->AddEntry(h_tJeff2,"2 track jets");
        leg2->AddEntry(h_tJeff3,"3 track jets");
        leg2->AddEntry(h_tJeff4,"4 track jets");
        leg2->AddEntry(h_tJeff5,"5 track jets");
        leg2->Draw();
	C->Update();
        C->Print(out_file_close,"pdf");


return 0;
}
