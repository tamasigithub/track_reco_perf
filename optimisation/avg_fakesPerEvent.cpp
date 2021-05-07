#include "TROOT.h"
#include "../resolution/plot_props.h"
void avg_fakesPerEvent()
{

	//! Define Cut
	TCut select    = "Tid==-1 && abs(Pt_n)>2e3 && abs(kappa_pull) < 3 && abs(Eta13) < 1.7";

	TChain recTree("m_recTree");
	recTree.Add("/home/tamasi/repo_tamasi/rec_files/rec_files/30mm/PU1k/ggFhh4b_SM/*.root");

	int n_entries = recTree.GetEntries();
	std::cout<<"input number of entries:" << n_entries <<std::endl;
  	TObject integer;
  	integer.SetUniqueID(n_entries);

	int etabin = 25;
    	double etamin   = -2.5, etamax = 2.5;
	
	int phibin = 16;
    	//double phimin   = -3.2, phimax = 3.2;
    	double phimin   = 0, phimax = 6.4;

	/// LOG BINS
	/// Variable bin width
	const int ptbins = 40;//no. of bins
	Double_t xbins[ptbins+1];//elements of this array are
	double dx = 5./ptbins;//5 -> implies max until 10^5
	double l10 = TMath::Log(10);
	for (int i = 0; i<=ptbins; i++)
	{
	        std::cout<<"i,dx : " <<i << ", "<<dx <<std::endl;
		xbins[i] = TMath::Exp(l10*i*dx)*1e-3;// in GeV now
	        std::cout<<"xbin[i] : " <<xbins[i] <<std::endl;
	}
	
	TH1::SetDefaultSumw2(true);
        TH1* h_den_vs_etaPU = new TH1F("h_den_vs_etaPU", "Average Fake Count vs #eta;#eta;Average Fake Count", etabin, etamin, etamax);
        TH1* h_den_vs_phiPU = new TH1F("h_den_vs_phiPU", "Average Fake Count vs #phi;#phi [rad];Average Fake Count", phibin, phimin, phimax);
	TH1* h_den_vs_ptPU = new TH1F("h_den_vs_ptPU", "Average Fake Count vs p_{T};p_{T} [GeV/c];Average Fake Count", ptbins, xbins);



	recTree.Draw("Eta13>>h_den_vs_etaPU",select);
	recTree.Draw("Phi013>>h_den_vs_phiPU",select);
	recTree.Draw("Pt_n*1e-3>>h_den_vs_ptPU",select);//! Fill in GeV
	 
	h_den_vs_etaPU->Draw();
	h_den_vs_phiPU->Draw();
	h_den_vs_ptPU->Draw();
	
	//h_den_vs_etaPU->Scale(1/n_entries);
	//h_den_vs_phiPU->Scale(1/n_entries);
	//h_den_vs_ptPU->Scale(1/n_entries);


	TCanvas *c = new TCanvas("c","c", 800, 800);
	h_den_vs_etaPU->Draw();
	h_den_vs_phiPU->Draw();
	h_den_vs_ptPU->Draw();

	TFile *fout = new TFile("avg_fakeCountPU1kEta1_7.root","RECREATE");
	h_den_vs_etaPU->Write();
	h_den_vs_phiPU->Write();
	h_den_vs_ptPU->Write();
  	integer.Write("N_Entries");
	fout->Close();

	

	return;
}

void plot()
{

	Legends();
	TFile *f = new TFile("avg_fakeCountPU1kEta1_7.root","READ");
	TH1D *h_eta = (TH1D*)f->Get("h_den_vs_etaPU");
	TH1D *h_phi = (TH1D*)f->Get("h_den_vs_phiPU");
	TH1D *h_pt = (TH1D*)f->Get("h_den_vs_ptPU");
	TObject *fobj = (TObject*)f->Get("N_Entries");
	float entries = (float)fobj->GetUniqueID(); 

	h_eta->Scale(1/entries);
	h_phi->Scale(1/entries);
	h_pt->Scale(1/entries);

	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);

	h_eta->SetLineWidth(LINE_WIDTH);
	h_phi->SetLineWidth(LINE_WIDTH);
	h_pt->SetLineWidth(LINE_WIDTH);
		
	h_eta->GetYaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	h_phi->GetYaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	h_pt->GetYaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	
	h_eta->GetYaxis()->SetTitle("Avg. fake count / event");
	h_phi->GetYaxis()->SetTitle("Avg. fake count / event");
	h_pt->GetYaxis()->SetTitle("Avg. fake count / event");
	
	h_eta->GetXaxis()->SetTitleSize(TITLE_SIZE);
	h_eta->GetYaxis()->SetTitleSize(TITLE_SIZE);
	h_phi->GetXaxis()->SetTitleSize(TITLE_SIZE);
	h_phi->GetYaxis()->SetTitleSize(TITLE_SIZE);
	h_pt->GetXaxis()->SetTitleSize(TITLE_SIZE);
	h_pt->GetYaxis()->SetTitleSize(TITLE_SIZE);
	
	h_eta->GetXaxis()->CenterTitle();
	h_eta->GetYaxis()->CenterTitle();
	h_phi->GetXaxis()->CenterTitle();
	h_phi->GetYaxis()->CenterTitle();
	h_pt->GetXaxis()->CenterTitle();
	h_pt->GetYaxis()->CenterTitle();

	TCanvas *c1 =  new TCanvas("c1","c1",800,800);
	h_eta->Draw();
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	c1->SaveAs("./tex/avgFakeVsEta.tex");

	h_phi->Draw();
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	c1->SaveAs("./tex/avgFakeVsPhi.tex");
	
	c1->SetLogy();
	h_pt->Draw();
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	c1->SaveAs("./tex/avgFakeVspT.tex");

	return;
}
