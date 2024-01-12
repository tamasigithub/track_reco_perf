#include "TROOT.h"
#include "../resolution/plot_props.h"
void avg_fakesPerEvent()
{

	//! Define Cut
	//TCut select    = "Tid==-1 && abs(Pt_n)>2e3 && abs(kappa_pull) < 3 && abs(Eta13) < 1.7";
	TCut select    = "Tid==-1 && abs(Pt_n)>2e3 && abs(kappa_pull) < 3";
	TCut select_all   = "Tid>=-1 && abs(Pt_n)>2e3 && abs(kappa_pull) < 3";
	TCut select_tru   = "Tid>=0 && abs(Pt_n)>2e3 && abs(kappa_pull) < 3";

	TChain recTree("m_recTree");
	TChain recTree_("m_recTree");
	//! PU1k
	////recTree.Add("/home/tamasi/repo_tamasi/rec_files/rec_files/30mm/PU1k/ggFhh4b_SM/*.root");
	//recTree.Add("/user/tkar/from_tachyon/rec_files/30mm/PU1k/ggFhh4b_SM/*.root");// exxtended
	//recTree_.Add("/user/tkar/work/data/rec/sel/Br30mmEC80mm/PU1k/ggF1.0/*.root");// endcap
	//! PU200
	recTree.Add("/user/tkar/from_tachyon/rec_files/30mm/PU200/ggFhh4b_SM/*.root");// exxtended
	recTree_.Add("/user/tkar/work/data/rec/opt/Br30mmEC80mm/PU200/ggF1.0/*.root");// endcap

	int n_entries = recTree.GetEntries();
	int n_entries_ = recTree_.GetEntries();
	std::cout<<"input number of entries: extended:" << n_entries << "  endcap: " << n_entries_ <<std::endl;
  	TObject integer;
  	TObject integer_;
  	integer.SetUniqueID(n_entries);
  	integer_.SetUniqueID(n_entries_);

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

	int inv_pTbins = 20;
	double inv_pT_min = 0, inv_pT_max = 0.6;
	
	TH1::SetDefaultSumw2(true);
        TH1* h_den_vs_etaPU = new TH1F("h_den_vs_etaPU", "Average Fake Count vs #eta;#eta;Average Fake Count", etabin, etamin, etamax);
        TH1* h_den_vs_phiPU = new TH1F("h_den_vs_phiPU", "Average Fake Count vs #phi;#phi [rad];Average Fake Count", phibin, phimin, phimax);
	TH1* h_den_vs_ptPU = new TH1F("h_den_vs_ptPU", "Average Fake Count vs p_{T};p_{T} [GeV/c];Average Fake Count", ptbins, xbins);
	TH1* h_den_vs_invptPU = new TH1F("h_den_vs_invptPU", "Average Fake Count vs 1/p_{T};1/p_{T} [GeV/c]^{-1};Average Fake Count", inv_pTbins, inv_pT_min, inv_pT_max);
	TH1* h_all_vs_ptPU = new TH1F("h_all_vs_ptPU", "p_{T};p_{T} [GeV/c];", ptbins, xbins);
	TH1* h_all_vs_invptPU = new TH1F("h_all_vs_invptPU", "1/p_{T};1/p_{T} [GeV/c]^{-1};", inv_pTbins, inv_pT_min, inv_pT_max);
	TH1* h_tru_vs_ptPU = new TH1F("h_tru_vs_ptPU", "p_{T};p_{T} [GeV/c];", ptbins, xbins);
	TH1* h_tru_vs_invptPU = new TH1F("h_tru_vs_invptPU", "1/p_{T};1/p_{T} [GeV/c]^{-1};", inv_pTbins, inv_pT_min, inv_pT_max);
        // endcap
	TH1* h_den_vs_etaPU_ = new TH1F("h_den_vs_etaPU_", "Average Fake Count vs #eta;#eta;Average Fake Count", etabin, etamin, etamax);
        TH1* h_den_vs_phiPU_ = new TH1F("h_den_vs_phiPU_", "Average Fake Count vs #phi;#phi [rad];Average Fake Count", phibin, phimin, phimax);
	TH1* h_den_vs_ptPU_ = new TH1F("h_den_vs_ptPU_", "Average Fake Count vs p_{T};p_{T} [GeV/c];Average Fake Count", ptbins, xbins);
	TH1* h_den_vs_invptPU_ = new TH1F("h_den_vs_invptPU_", "Average Fake Count vs 1/p_{T};1/p_{T} [GeV/c]^{-1};Average Fake Count", inv_pTbins, inv_pT_min, inv_pT_max);
	TH1* h_all_vs_ptPU_ = new TH1F("h_all_vs_ptPU_", "p_{T};p_{T} [GeV/c];", ptbins, xbins);
	TH1* h_all_vs_invptPU_ = new TH1F("h_all_vs_invptPU_", "1/p_{T};1/p_{T} [GeV/c]^{-1};", inv_pTbins, inv_pT_min, inv_pT_max);
	TH1* h_tru_vs_ptPU_ = new TH1F("h_tru_vs_ptPU_", "p_{T};p_{T} [GeV/c];", ptbins, xbins);
	TH1* h_tru_vs_invptPU_ = new TH1F("h_tru_vs_invptPU_", "1/p_{T};1/p_{T} [GeV/c]^{-1};", inv_pTbins, inv_pT_min, inv_pT_max);



	recTree.Draw("Eta13>>h_den_vs_etaPU",select);
	recTree.Draw("Phi013>>h_den_vs_phiPU",select);
	recTree.Draw("Pt_n*1e-3>>h_den_vs_ptPU",select);//! Fill in GeV
	recTree.Draw("1/Pt_n*1e3>>h_den_vs_invptPU",select);//! Fill in GeV
	recTree.Draw("Pt_n*1e-3>>h_all_vs_ptPU",select_all);//! Fill in GeV
	recTree.Draw("1/Pt_n*1e3>>h_all_vs_invptPU",select_all);//! Fill in GeV
	recTree.Draw("Pt_n*1e-3>>h_tru_vs_ptPU",select_tru);//! Fill in GeV
	recTree.Draw("1/Pt_n*1e3>>h_tru_vs_invptPU",select_tru);//! Fill in GeV
	
	recTree_.Draw("Eta13>>h_den_vs_etaPU_",select);
	recTree_.Draw("Phi013>>h_den_vs_phiPU_",select);
	recTree_.Draw("Pt_n*1e-3>>h_den_vs_ptPU_",select);//! Fill in GeV
	recTree_.Draw("1/Pt_n*1e3>>h_den_vs_invptPU_",select);//! Fill in GeV
	recTree.Draw("Pt_n*1e-3>>h_all_vs_ptPU_",select_all);//! Fill in GeV
	recTree.Draw("1/Pt_n*1e3>>h_all_vs_invptPU_",select_all);//! Fill in GeV
	recTree.Draw("Pt_n*1e-3>>h_tru_vs_ptPU_",select_tru);//! Fill in GeV
	recTree.Draw("1/Pt_n*1e3>>h_tru_vs_invptPU_",select_tru);//! Fill in GeV
	 
	h_den_vs_etaPU->Draw();
	h_den_vs_phiPU->Draw();
	h_den_vs_ptPU->Draw();
	h_den_vs_invptPU->Draw();
	h_all_vs_ptPU->Draw();
	h_all_vs_invptPU->Draw();
	h_tru_vs_ptPU->Draw();
	h_tru_vs_invptPU->Draw();
	
	h_den_vs_etaPU_->Draw();
	h_den_vs_phiPU_->Draw();
	h_den_vs_ptPU_->Draw();
	h_den_vs_invptPU_->Draw();
	h_all_vs_ptPU_->Draw();
	h_all_vs_invptPU_->Draw();
	h_tru_vs_ptPU_->Draw();
	h_tru_vs_invptPU_->Draw();
	
	//h_den_vs_etaPU->Scale(1/n_entries);
	//h_den_vs_phiPU->Scale(1/n_entries);
	//h_den_vs_ptPU->Scale(1/n_entries);


	TCanvas *c = new TCanvas("c","c", 800, 800);
	h_den_vs_etaPU->Draw();
	h_den_vs_phiPU->Draw();
	h_den_vs_ptPU->Draw();

	TFile *fout = new TFile("avg_fakeCountPU200Eta2_5.root","RECREATE");
	h_den_vs_etaPU->Write();
	h_den_vs_phiPU->Write();
	h_den_vs_ptPU->Write();
	h_den_vs_invptPU->Write();
	h_all_vs_ptPU->Write();
	h_all_vs_invptPU->Write();
	h_tru_vs_ptPU->Write();
	h_tru_vs_invptPU->Write();
	
	h_den_vs_etaPU_->Write();
	h_den_vs_phiPU_->Write();
	h_den_vs_ptPU_->Write();
	h_den_vs_invptPU_->Write();
	h_all_vs_ptPU_->Write();
	h_all_vs_invptPU_->Write();
	h_tru_vs_ptPU_->Write();
	h_tru_vs_invptPU_->Write();
  	integer.Write("N_Entries");
  	integer_.Write("N_Entries_");
	fout->Close();

	

	return;
}

void plot(const char *output_file_name="avg_fakeCountPU1kEta2_5")
{

	Legends();
	char out_root_file [1023];
	sprintf(out_root_file,"%s.root",output_file_name);
	TFile *f = new TFile(out_root_file,"READ");
	TH1D *h_eta = (TH1D*)f->Get("h_den_vs_etaPU");
	TH1D *h_phi = (TH1D*)f->Get("h_den_vs_phiPU");
	TH1D *h_pt = (TH1D*)f->Get("h_den_vs_ptPU");
	TH1D *h_invpt = (TH1D*)f->Get("h_den_vs_invptPU");
	TH1D *h_all_pt = (TH1D*)f->Get("h_all_vs_ptPU");
	TH1D *h_all_invpt = (TH1D*)f->Get("h_all_vs_invptPU");
	TH1D *h_tru_pt = (TH1D*)f->Get("h_tru_vs_ptPU");
	TH1D *h_tru_invpt = (TH1D*)f->Get("h_tru_vs_invptPU");

	TH1D *h_eta_ = (TH1D*)f->Get("h_den_vs_etaPU_");
	TH1D *h_phi_ = (TH1D*)f->Get("h_den_vs_phiPU_");
	TH1D *h_pt_ = (TH1D*)f->Get("h_den_vs_ptPU_");
	TH1D *h_invpt_ = (TH1D*)f->Get("h_den_vs_invptPU_");
	TH1D *h_all_pt_ = (TH1D*)f->Get("h_all_vs_ptPU_");
	TH1D *h_all_invpt_ = (TH1D*)f->Get("h_all_vs_invptPU_");
	TH1D *h_tru_pt_ = (TH1D*)f->Get("h_tru_vs_ptPU_");
	TH1D *h_tru_invpt_ = (TH1D*)f->Get("h_tru_vs_invptPU_");

	TObject *fobj = (TObject*)f->Get("N_Entries");
	TObject *fobj_ = (TObject*)f->Get("N_Entries_");
	float entries = (float)fobj->GetUniqueID(); 
	float entries_ = (float)fobj_->GetUniqueID(); 

	h_eta->Scale(1/entries);
	h_phi->Scale(1/entries);
	h_pt->Scale(1/entries);
	h_invpt->Scale(1/entries);
	h_all_pt->Scale(1/entries);
	h_all_invpt->Scale(1/entries);
	h_tru_pt->Scale(1/entries);
	h_tru_invpt->Scale(1/entries);
	
	h_eta_->Scale(1/entries_);
	h_phi_->Scale(1/entries_);
	h_pt_->Scale(1/entries_);
	h_invpt_->Scale(1/entries_);
	h_all_pt_->Scale(1/entries_);
	h_all_invpt_->Scale(1/entries_);
	h_tru_pt_->Scale(1/entries_);
	h_tru_invpt_->Scale(1/entries_);

	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);

	h_eta->SetLineWidth(LINE_WIDTH);
	h_phi->SetLineWidth(LINE_WIDTH);
	h_pt->SetLineWidth(LINE_WIDTH);
	h_invpt->SetLineWidth(LINE_WIDTH);
	h_all_pt->SetLineWidth(LINE_WIDTH);
	h_all_invpt->SetLineWidth(LINE_WIDTH);
	h_tru_pt->SetLineWidth(LINE_WIDTH);
	h_tru_invpt->SetLineWidth(LINE_WIDTH);
	
	h_eta->SetLineColor(kRed);
	h_phi->SetLineColor(kRed);
	h_pt->SetLineColor(kRed);
	h_invpt->SetLineColor(kRed);
	h_all_pt->SetLineColor(kBlack);
	h_all_invpt->SetLineColor(kBlack);
	h_tru_pt->SetLineColor(kBlue);
	h_tru_invpt->SetLineColor(kBlue);
	
	h_eta_->SetLineWidth(LINE_WIDTH);
	h_phi_->SetLineWidth(LINE_WIDTH);
	h_pt_->SetLineWidth(LINE_WIDTH);
	h_invpt_->SetLineWidth(LINE_WIDTH);
	h_all_pt_->SetLineWidth(LINE_WIDTH);
	h_all_invpt_->SetLineWidth(LINE_WIDTH);
	h_tru_pt_->SetLineWidth(LINE_WIDTH);
	h_tru_invpt_->SetLineWidth(LINE_WIDTH);
		
	h_eta->GetYaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	h_phi->GetYaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	h_pt->GetYaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	h_invpt->GetYaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	
	h_eta->GetYaxis()->SetTitle("Avg. fake count / event");
	h_phi->GetYaxis()->SetTitle("Avg. fake count / event");
	h_pt->GetYaxis()->SetTitle("Avg. fake count / event");
	h_invpt->GetYaxis()->SetTitle("Avg. fake count / event");
	
	h_eta->GetXaxis()->SetTitleSize(TITLE_SIZE);
	h_eta->GetYaxis()->SetTitleSize(TITLE_SIZE);
	h_phi->GetXaxis()->SetTitleSize(TITLE_SIZE);
	h_phi->GetYaxis()->SetTitleSize(TITLE_SIZE);
	h_pt->GetXaxis()->SetTitleSize(TITLE_SIZE);
	h_pt->GetYaxis()->SetTitleSize(TITLE_SIZE);
	h_invpt->GetXaxis()->SetTitleSize(TITLE_SIZE);
	h_invpt->GetYaxis()->SetTitleSize(TITLE_SIZE);
	h_all_pt->GetXaxis()->SetTitleSize(TITLE_SIZE);
	h_all_pt->GetYaxis()->SetTitleSize(TITLE_SIZE);
	h_all_invpt->GetXaxis()->SetTitleSize(TITLE_SIZE);
	h_all_invpt->GetYaxis()->SetTitleSize(TITLE_SIZE);
	
	h_eta->GetXaxis()->CenterTitle();
	h_eta->GetYaxis()->CenterTitle();
	h_phi->GetXaxis()->CenterTitle();
	h_phi->GetYaxis()->CenterTitle();
	h_pt->GetXaxis()->CenterTitle();
	h_pt->GetYaxis()->CenterTitle();
	h_invpt->GetXaxis()->CenterTitle();
	h_invpt->GetYaxis()->CenterTitle();
	h_all_pt->GetXaxis()->CenterTitle();
	h_all_pt->GetYaxis()->CenterTitle();
	h_all_invpt->GetXaxis()->CenterTitle();
	h_all_invpt->GetYaxis()->CenterTitle();

	//! template histogram: truth hist scaled by a factor determined by
	//! the contents of the bin for invpt = 0.4 of truth and fakes and
	//! each bin content of the scaled histogram added by a factor determined
	//! by the content of the first bin of invpt of truth and fakes
	float invpt_1 = 0.01;
	float invpt_2 = 0.35;
	float scale = (h_invpt->GetBinContent(h_invpt->GetXaxis()->FindBin(invpt_1)) - h_invpt->GetBinContent(h_invpt->GetXaxis()->FindBin(invpt_2)))/(h_tru_invpt->GetBinContent(h_tru_invpt->GetXaxis()->FindBin(invpt_1)) - h_tru_invpt->GetBinContent(h_tru_invpt->GetXaxis()->FindBin(invpt_2)));
	float offset = h_invpt->GetBinContent(h_invpt->GetXaxis()->FindBin(invpt_2)) - scale*h_tru_invpt->GetBinContent(h_tru_invpt->GetXaxis()->FindBin(invpt_2));
	std::cout <<"scale, offset: "<<scale <<",  " << offset <<std::endl;
	
	float scale_ = (h_invpt_->GetBinContent(h_invpt_->GetXaxis()->FindBin(invpt_1)) - h_invpt_->GetBinContent(h_invpt_->GetXaxis()->FindBin(invpt_2)))/(h_tru_invpt_->GetBinContent(h_tru_invpt_->GetXaxis()->FindBin(invpt_1)) - h_tru_invpt_->GetBinContent(h_tru_invpt_->GetXaxis()->FindBin(invpt_2)));
	float offset_ = h_invpt_->GetBinContent(h_invpt_->GetXaxis()->FindBin(invpt_2)) - scale_*h_tru_invpt_->GetBinContent(h_tru_invpt_->GetXaxis()->FindBin(invpt_2));
	std::cout <<"scale_, offset_: "<<scale_ <<",  " << offset_ <<std::endl;
	
	TH1F *h1 = (TH1F*)h_tru_invpt->Clone("h1");
	h1->Scale(scale);
	TH1F *h = (TH1F*)h_invpt->Clone("h");
	
	TH1F *h1_ = (TH1F*)h_tru_invpt_->Clone("h1_");
	h1_->Scale(scale_);
	TH1F *h_ = (TH1F*)h_invpt_->Clone("h_");
	for(int i= 1; i <=h1_->GetNbinsX(); i++)
	{	
		h1->AddBinContent(i, offset);
		h->AddBinContent(i, -1*offset);
	
		h1_->AddBinContent(i, offset_);
		h_->AddBinContent(i, -1*offset_);
	}
	//float scale_ = h_invpt_->GetBinContent(h_invpt_->GetXaxis()->FindBin(0.4))/(float)h_tru_invpt_->GetBinContent(h_tru_invpt_->GetXaxis()->FindBin(0.4));
	h->SetLineColor(kGreen);
	h1->SetLineColor(kMagenta);
	h_->SetLineColor(kGreen);
	h1_->SetLineColor(kMagenta);


	const char *out_path = "./";
	char out_file_open[1023];
        sprintf(out_file_open,"%s/%s.pdf(",out_path,output_file_name);
        char out_file_[1023];
        sprintf(out_file_,"%s/%s.pdf",out_path,output_file_name);
        char out_file_close[1023];
        sprintf(out_file_close,"%s/%s.pdf)",out_path,output_file_name);

	//! pg1
	TCanvas *c1 =  new TCanvas("c1","c1",800,800);
	h_eta->Draw();
	h_eta_->Draw("same");
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	c1->SaveAs("./tex/avgFakeVsEta.tex");
	c1->SaveAs("./tex/avgFakeVsEta.root");
	c1->Print(out_file_open,"pdf");
	//! pg2
	h_phi->Draw();
	h_phi_->Draw("same");
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	c1->SaveAs("./tex/avgFakeVsPhi.tex");
	c1->SaveAs("./tex/avgFakeVsPhi.root");
	c1->Print(out_file_,"pdf");
	//! pg3
	c1->SetLogy();
	h_pt->Draw();
	h_pt_->Draw("same");
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	c1->SaveAs("./tex/avgFakeVspT.tex");
	c1->SaveAs("./tex/avgFakeVspT.root");
	c1->Print(out_file_,"pdf");
	//! pg4
	c1->SetLogy(0);
	h_invpt->Draw();
	h_invpt_->Draw("same");
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	c1->SaveAs("./tex/avgFakeVsinvpT.tex");
	c1->SaveAs("./tex/avgFakeVsinvpT.root");
	c1->Print(out_file_,"pdf");
	//! pg5 extended
	c1->SetLogy();
	//c1->SetLogx();
	float max=h_all_pt->GetMaximum()+ 0.1*h_all_pt->GetMaximum();
	float min=0.02;
	//h_pt->GetMinimum()- 0.01*h_pt->GetMinimum();
	h_all_pt->GetYaxis()->SetRangeUser(min,max);
	h_all_pt->Draw();
	h_tru_pt->Draw("same");
	h_pt->Draw("same");
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	c1->SaveAs("./tex/avg_all_tru_fakeVspt.tex");
	c1->SaveAs("./tex/avg_all_tru_fakeVspt.root");
	c1->Print(out_file_,"pdf");
	//! pg6 extended
	c1->SetLogy(0);
	c1->SetLogx(0);
	max=h_all_invpt->GetMaximum()+ 0.1*h_all_invpt->GetMaximum();
	min=h_invpt->GetMinimum()- 0.1*h_invpt->GetMinimum();
	h_all_invpt->GetYaxis()->SetRangeUser(min,max);
	h_all_invpt->Draw();
	h_tru_invpt->Draw("same");
	h_invpt->Draw("same");
	h->Draw("same");
	h1->Draw("same");
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	c1->SaveAs("./tex/avg_all_tru_fakeVsinvpT.tex");
	c1->SaveAs("./tex/avg_all_tru_fakeVsinvpT.root");
	c1->Print(out_file_,"pdf");
	//! pg7 extended
	c1->SetLogy(0);
	c1->SetLogx(0);
	h_invpt->Draw();
	h->Draw("same");
	h1->Draw("same");
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	c1->SaveAs("./tex/avg_template_fakeVsinvpt.tex");
	c1->SaveAs("./tex/avg_template_fakeVsinvpt.root");
	c1->Print(out_file_,"pdf");
	//! pg8 endcap
	c1->SetLogy();
	//c1->SetLogx();
	h_all_pt_->SetLineColor(kBlack);
	h_tru_pt_->SetLineColor(kBlue);
	h_pt_->SetLineColor(kRed);
	max=h_all_pt_->GetMaximum()+ 0.1*h_all_pt_->GetMaximum();
	min=0.02;
	//h_pt_->GetMinimum()- 0.01*h_pt_->GetMinimum();
	h_all_pt_->GetYaxis()->SetRangeUser(min,max);
	h_all_pt_->Draw();
	h_tru_pt_->Draw("same");
	h_pt_->Draw("same");
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	c1->SaveAs("./tex/avg_all_tru_fakeVspt_.tex");
	c1->SaveAs("./tex/avg_all_tru_fakeVspt_.root");
	c1->Print(out_file_,"pdf");
	//! pg9 endcap
	c1->SetLogy(0);
	c1->SetLogx(0);
	h_all_invpt_->SetLineColor(kBlack);
	h_tru_invpt_->SetLineColor(kBlue);
	h_invpt_->SetLineColor(kRed);
	max=h_all_invpt_->GetMaximum()+ 0.1*h_all_invpt_->GetMaximum();
	min=h_invpt_->GetMinimum()- 0.1*h_invpt_->GetMinimum();
	h_all_invpt_->GetYaxis()->SetRangeUser(min,max);
	h_all_invpt_->Draw();
	h_tru_invpt_->Draw("same");
	h_invpt_->Draw("same");
	h_->Draw("same");
	h1_->Draw("same");
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	c1->SaveAs("./tex/avg_all_tru_fakeVsinvpt_.tex");
	c1->SaveAs("./tex/avg_all_tru_fakeVsinvpt_.root");
	c1->Print(out_file_,"pdf");
	//! pg10 endcap
	c1->SetLogy(0);
	c1->SetLogx(0);
	h_invpt_->Draw();
	h_->Draw("same");
	h1_->Draw("same");
	leg1->Draw();
	leg2->Draw();
	leg5->Draw();
	c1->SaveAs("./tex/avg_template_fakeVsinvpt_.tex");
	c1->SaveAs("./tex/avg_template_fakeVsinvpt_.root");
	c1->Print(out_file_close,"pdf");

	return;
}
