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
const char* out_path = "/media/tamasi/DriveT/tamasi/Desktop/PHD/talks_preps/ctd2k19/plots/efficiency/hh4b"; 
//const char* out_path = "/media/tamasi/DriveT/tamasi/Desktop/PHD/talks_preps/ctd2k19/plots/efficiency/singleParticles; 

int eff_Vs_etaphipt_dR_barcode(const char* output_file_name = "PU200hh4b-eff_30mm", bool save = false)
//int eff_Vs_etaphipt_dR_barcode(const char* output_file_name = "pi-effvxvy20secondary_30mm", bool save = false)
{
	TChain recTree("m_recTree");
	TChain truthTree("tracks");
	//! pileup samples
	recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/talks_preps/ctd2k19/data_files/hh4b/pileup_samples/rec-files/PU200hh4b_rec_003*.root");
	truthTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/talks_preps/ctd2k19/data_files/hh4b/pileup_samples/rec-files/PU200hh4b_rec_003*.root");
	//! single particles
	/*recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/talks_preps/ctd2k19/data_files/single_particle/rec-files/pi-_rec_003*.root");
	truthTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/talks_preps/ctd2k19/data_files/single_particle/rec-files/pi-_rec_003*.root");
*/

	//! define a local vector<double> to store the reconstructed pt values
	//! always initialise a pointer!!
	std::vector<int>   *tinteraction = 0;
        std::vector<int>   *barcode = 0;	
        std::vector<int>   *pdg = 0;	
        std::vector<double> *pt = 0;	
        std::vector<double> *phi = 0;	
        std::vector<double> *eta = 0;	
        std::vector<double> *Vx = 0;	
        std::vector<double> *Vy = 0;	
        std::vector<double> *Vz = 0;	
        std::vector<int>   *match_barcodeTTT_bc = 0;

	truthTree.SetBranchStatus("*",          0);
	truthTree.SetBranchStatus("type_traj", 	1);
	truthTree.SetBranchStatus("tid", 	1);
	truthTree.SetBranchStatus("pid",     	1);
	truthTree.SetBranchStatus("pt", 	1);
	truthTree.SetBranchStatus("phi", 	1);
	truthTree.SetBranchStatus("eta", 	1);
	truthTree.SetBranchStatus("vx", 	1);
	truthTree.SetBranchStatus("vy", 	1);
	truthTree.SetBranchStatus("vz", 	1);

	recTree.SetBranchStatus("*",            0);
	recTree.SetBranchStatus("Tid",  	1);
	
	truthTree.SetBranchAddress("type_traj", &tinteraction);
	truthTree.SetBranchAddress("tid", 	&barcode);
	truthTree.SetBranchAddress("pid", 	&pdg);
	truthTree.SetBranchAddress("pt", 	&pt);
	truthTree.SetBranchAddress("phi", 	&phi);
	truthTree.SetBranchAddress("eta", 	&eta);
	truthTree.SetBranchAddress("vx", 	&Vx);
	truthTree.SetBranchAddress("vy", 	&Vy);
	truthTree.SetBranchAddress("vz", 	&Vz);

	recTree.SetBranchAddress("Tid", &match_barcodeTTT_bc);

	int etabin = 17;
    	double etamin   = -1.7, etamax = 1.7;
	
	int phibin = 16;
    	double phimin   = -3.2, phimax = 3.2;

	// variable bin for single particles
/*	int ptbins = 12;
	double xbins[] = {1000, 3500, 7500, 15000, 25000, 35000, 45000, 55000, 65000, 75000, 85000, 95000, 105000 };	
*/	/// LOG BINS for signal sample
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
	//! TTT barcode matched
	TH1* h_num_vs_etaPU = new TH1F("h_num_vs_etaPU", "Numerator Count vs #eta;#eta;Numerator Count"    , etabin, etamin, etamax);
        TH1* h_den_vs_etaPU = new TH1F("h_den_vs_etaPU", "Denominator Count vs #eta;#eta;Denominator Count", etabin, etamin, etamax);
	
	TH1* h_num_vs_phiPU = new TH1F("h_num_vs_phiPU", "Numerator Count vs #phi;#phi [rad];Numerator Count"    , phibin, phimin, phimax);
        TH1* h_den_vs_phiPU = new TH1F("h_den_vs_phiPU", "Denominator Count vs #phi;#phi [rad];Denominator Count", phibin, phimin, phimax);

	TH1* h_num_vs_ptPU = new TH1F("h_num_vs_ptPU", "Numerator Count vs P_{t};P_{t} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_ptPU = new TH1F("h_den_vs_ptPU", "Denominator Count vs P_{t};P_{t} [MeV/c];Denominator Count", ptbins, xbins);



	for(int i = 0; i < truthTree.GetEntries(); ++i)
	//for(int i = 0; i < 10000; ++i)
	{
		//! get entries for the ith event
		truthTree.GetEntry(i);
		recTree.GetEntry(i);
		//! loop over the truth particles and select stable charge particles passing the selections
		for(int i1 = 0; i1 < barcode->size(); ++i1)
		{
			int match_flagTTT_bc = -1;
			if(std::fabs(pt->at(i1)) < 2e3 )	continue;
			if(std::fabs(eta->at(i1)) > 1.6)	continue;
			if(std::fabs(Vz->at(i1)) > 100 )	continue;
			if(std::fabs(Vx->at(i1)) > 2 )		continue;
			if(std::fabs(Vy->at(i1)) > 2 )		continue;
			if(barcode->at(i1) <= 0) 		continue;
			//if((*tinteraction)[i1] > 0)		continue;
			//if(std::abs(pdg->at(i1)) != 321) 	continue;

			//! loop over TTT tracks and the find the corresponding particle it was matched to (with barcode matching)
			for(int i2 = 0; i2 < match_barcodeTTT_bc->size(); ++i2)
			{
				//! get rid of the fakes and double counted reconstructed tracks
				if((*match_barcodeTTT_bc)[i2] < 0) 
				{
					match_flagTTT_bc = -1;
					continue;
				}
				//! if a match is found fill truth variables both in numerator and denominator
				//! else fill truth variables only in the denominator
				if((*match_barcodeTTT_bc)[i2] == (*barcode)[i1])
				{
					match_flagTTT_bc = 1;
					break;
				}
				else
				{
					match_flagTTT_bc = 0;
				}
			}
			if(match_flagTTT_bc == 1)
			{
				h_num_vs_etaPU->Fill((*eta)[i1]);
				h_num_vs_phiPU->Fill((*phi)[i1]);
				h_num_vs_ptPU->Fill((*pt)[i1]);
			}
			if(match_flagTTT_bc > -1)
			{
				h_den_vs_etaPU->Fill((*eta)[i1]);
				h_den_vs_phiPU->Fill((*phi)[i1]);
				h_den_vs_ptPU->Fill((*pt)[i1]);
			}
		}
	}

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

        h_eff_vs_etaPU->SetTitle("efficiency vs #eta;#eta;efficiency");
        h_eff_vs_phiPU->SetTitle("efficiency vs #phi;#phi [rad];efficiency");
	h_eff_vs_ptPU->SetTitle("efficiency vs P_{t};P_{t} [MeV/c];efficiency");
        
	h_eff_vs_ptPU->GetXaxis()->SetRangeUser(2000.,106000.);
	
        h_eff_vs_etaPU->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_eff_vs_phiPU->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_eff_vs_ptPU->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_eff_vs_etaPU->GetYaxis()->SetTitleOffset(0.85);
        h_eff_vs_phiPU->GetYaxis()->SetTitleOffset(0.85);
	h_eff_vs_ptPU->GetYaxis()->SetTitleOffset(0.85);
        h_eff_vs_etaPU->GetYaxis()->SetTitleSize(0.05);
        h_eff_vs_phiPU->GetYaxis()->SetTitleSize(0.05);
	h_eff_vs_ptPU->GetYaxis()->SetTitleSize(0.05);
        h_eff_vs_etaPU->GetXaxis()->SetTitleOffset(0.85);
        h_eff_vs_phiPU->GetXaxis()->SetTitleOffset(0.85);
	h_eff_vs_ptPU->GetXaxis()->SetTitleOffset(0.85);
        h_eff_vs_etaPU->GetXaxis()->SetTitleSize(0.05);
        h_eff_vs_phiPU->GetXaxis()->SetTitleSize(0.05);
	h_eff_vs_ptPU->GetXaxis()->SetTitleSize(0.05);
        
        h_eff_vs_etaPU->SetMarkerSize(1.8);
        h_eff_vs_phiPU->SetMarkerSize(1.8);
	h_eff_vs_ptPU->SetMarkerSize(1.8);
        
        h_eff_vs_etaPU->SetMarkerStyle(kFullTriangleDown);
        h_eff_vs_phiPU->SetMarkerStyle(kFullTriangleDown);
	h_eff_vs_ptPU->SetMarkerStyle(kFullTriangleDown);
        
        h_eff_vs_etaPU->SetMarkerColor(kBlack);
        h_eff_vs_phiPU->SetMarkerColor(kBlack);
	h_eff_vs_ptPU->SetMarkerColor(kBlack);	
	

	//! write 
	TCanvas* c1 = new TCanvas();	

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
