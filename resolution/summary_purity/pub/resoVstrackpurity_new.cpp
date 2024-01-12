#include "fit_Gauss.cpp"
#include "resoVstrackpurity_new.h"
	

//! clears the txt file
void deleteText(const char* pileup) {
    sprintf(txt_file,"%s/FCCsummary%d-%d_rmsVspurity_PU%s.txt",txt_path, (int)X_min, (int)X_max, pileup);
    std::ofstream ofs;
    ofs.open(txt_file, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    sprintf(txt_file,"%s/FCCsummary%d-%d_rmsZvtxVspurity_PU%s.txt",txt_path, (int)X_min, (int)X_max, pileup);
    ofs.open(txt_file, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

//! writes the gapsize,purity,rms and error in a txt file
void write_file(const char* gapsize, const char* pileup, double purity , double rms, double error)
{
    std::cout<<"Writing to txt file...." <<std::endl;
    sprintf(txt_file,"%s/FCCsummary%d-%d_rmsVspurity_PU%s.txt",txt_path, (int)X_min, (int)X_max, pileup);
    std::ofstream ofs;
    ofs.open (txt_file, std::ofstream::out | std::ofstream::app);
    ofs<<gapsize<<" "<<purity<<" "<<rms<<" "<<error<<"\n";
    ofs.close();

}

void write_file_Zvtx(const char* gapsize, const char* pileup, double purity , double rms, double error)
{
    std::cout<<"Writing to txt file...." <<std::endl;
    sprintf(txt_file,"%s/FCCsummary%d-%d_rmsZvtxVspurity_PU%s.txt",txt_path, (int)X_min, (int)X_max, pileup);
    std::ofstream ofs;
    ofs.open (txt_file, std::ofstream::out | std::ofstream::app);
    ofs<<gapsize<<" "<<purity<<" "<<rms<<" "<<error<<"\n";
    ofs.close();

}

void Init()
{

	//! LOG BINS
	for (int i = 0; i<=ptbins; i++)
	{
	        std::cout<<"i,dx : " <<i << ", "<<dx <<std::endl;
		xbins[i] = TMath::Exp(l10*i*dx);
	        std::cout<<"xbin["<<i<<"]: " <<xbins[i] <<std::endl;
	}
	
	TH1::SetDefaultSumw2(true);
	
	h_num_vs_ptPU = new TH1F("h_num_vs_ptPU", "Numerator Count vs P_{t};P_{t} [MeV/c];Numerator Count"    , ptbins, xbins);
	h_den_vs_ptPU = new TH1F("h_den_vs_ptPU", "Denominator Count vs P_{t};P_{t} [MeV/c];Denominator Count", ptbins, xbins);
	

	return;
}
//! opens the reconstructed root file with gap size = "run_no" and momentum "p"(e.g. 10GeV/c)
//! hence calls the draw function. 
//! This function draws the resolution plots and fits a gaus function and
//! fetches the rms and errors from the fit and hence calls the write function.
//! the write function creates a txt file and prints 
//! the run_no, the momentum p, rms, and error..

//! run_no - run number of the single particle file
//! first two numbers of which are identical to gap size
void weighted_avgPurity(const char *pileup, const char *gapsize)
{
	//! calculate track purity
	Init();

	TChain rec("m_recTree");
	sprintf(signal_file_names, "%s/%smm/PU%s/ggFhh4b_SM/*.root",file_path,gapsize,pileup);
	rec.Add(signal_file_names);
	std::cout<<"rec tree opened with " << rec.GetEntries() <<"entries\n";
	Int_t num_events = 2000;
	//Int_t num_events = rec.GetEntries();

	rec.Draw("Pt_n>>h_num_vs_ptPU",   num_select, "goff", num_events);
	rec.Draw("Pt_n>>h_den_vs_ptPU",   den_select, "goff", num_events);
	
	h_pur_vs_ptPU = dynamic_cast<TH1*>(h_num_vs_ptPU->Clone("h_pur_vs_ptPU"));
	h_pur_vs_ptPU->SetTitle("Purity vs P_{t};P_{t} [MeV/c];Purity");
	h_pur_vs_ptPU->Divide(h_num_vs_ptPU, h_den_vs_ptPU, 1.0, 1.0, "B");
	h_pur_vs_ptPU->GetYaxis()->SetRangeUser(0.1, 1.1);
	//h_pur_vs_ptPU->GetXaxis()->SetRangeUser(2000.,1000000.);
	h_pur_vs_ptPU->SetMarkerSize(0.95);
	h_pur_vs_ptPU->SetMarkerStyle(kOpenTriangleDown);
	h_pur_vs_ptPU->SetMarkerColor(kBlack);	
	
	if (h_pur_vs_ptPU->GetSumw2N() == 0) h_pur_vs_ptPU->Sumw2(kTRUE);	
	h_pur_vs_ptPU->Draw("Hist e1");
	
	//! calculate integral of purity in the high pt region
	//! https://root.cern.ch/root/roottalk/roottalk03/2211.html
	TAxis *axis = h_pur_vs_ptPU->GetXaxis();
	int bmin = axis->FindBin(X_min*1e3); 
	int bmax = axis->FindBin(X_max*1e3);

	double integral     = 0;
	double ithBin_pur   = 0;
	int weight          = 0;
	int tot_weight      = 0;
	for(int i = bmin; i < bmax+1; i++)
	{
		weight 	    = h_den_vs_ptPU->GetBinContent(i);
		ithBin_pur  = h_pur_vs_ptPU->GetBinContent(i);
		integral   += weight * ithBin_pur;		
		tot_weight += weight;

		std::cout<<"weight: " <<weight <<std::endl;
		std::cout<<"ithBin_pur: " <<ithBin_pur <<std::endl;

	}	

	weighted_avg = integral/tot_weight;
	std::cout<<"purity in the pt range [" <<X_min << "," << X_max <<"] = " << weighted_avg << std::endl;
	
	delete h_num_vs_ptPU;
	delete h_den_vs_ptPU;
	delete h_pur_vs_ptPU;
	
	return;
}
void rmsVspurity(const char *run_no, const char *pileup, const char *gapsize)
{
	//! calculate rel pt resolution using single pions
	//TFile *f = TFile::Open(rec_file_names);
	//TTree *t = (TTree*)f->Get("m_recTree");
	TChain t("m_recTree");
	sprintf(rec_file_names, "%s/pi*_recTree_%s.root",file_path,run_no);
	t.Add(rec_file_names);
	
	c1->Clear();
	char histo_title[1023];
	sprintf(histo_title,"Relative p_{T} Resolution, triplet gapsize %s, 10GeV single #pi",gapsize);
	h_p = new TH1F("h_p", histo_title, binNum, relptmin, relptmax);
	t.Draw("(Pt_n - M_pt)/M_pt>>h_p",all_cut);
	h_p->SetXTitle("#delta p [MeV/c]");
	h_p->SetTitle(histo_title);
	h_p->Draw();
	fit_Gauss(h_p);
	c1->Update();
	//h1->GetFunction("gaus")->GetParameter(2), h1->GetFunction("gaus")->GetParError(2)
	//double pRMS = h_p->GetRMS();
	//double PRMS_err = h_p->GetRMSError();
	double pRMS = h_p->GetFunction("gaus")->GetParameter(2);
	double PRMS_err = h_p->GetFunction("gaus")->GetParError(2);
	write_file(gapsize, pileup, weighted_avg, pRMS, PRMS_err);
	delete h_p;
}
void rmsZvtxVspurity(const char *run_no, const char *pileup, const char *gapsize)
{
	
	//! calculate rel pt resolution using single pions
	//TFile *f = TFile::Open(rec_file_names);
	//TTree *t = (TTree*)f->Get("m_recTree");
	TChain t("m_recTree");
	sprintf(rec_file_names, "%s/pi*_recTree_%s.root",file_path,run_no);
	t.Add(rec_file_names);
	
	c1->Clear();
	char histo_title[1023];
	sprintf(histo_title,"z_{0} Resolution, triplet gapsize %s, 10GeV single #pi",gapsize);
	
	h_p = new TH1F("h_p",histo_title,binNum,zmin,zmax);
	t.Draw("Z013 - M_Vz>>h_p",all_cut);
	h_p->SetXTitle("#delta z [mm]");
	h_p->SetTitle(histo_title);
	h_p->Draw();
	fit_Gauss(h_p);
	c1->Update();
	
	double pRMS = h_p->GetFunction("gaus")->GetParameter(2);
	double PRMS_err = h_p->GetFunction("gaus")->GetParError(2);
	write_file_Zvtx(gapsize, pileup, weighted_avg, pRMS, PRMS_err);
	delete h_p;
}

int writePU0()
{
	
	deleteText("0");	
	weighted_avgPurity("0", "20");
	rmsVspurity("200010","0","20");
	rmsZvtxVspurity("200010","0","20");
	
	weighted_avgPurity("0", "25");
	rmsVspurity("250010","0","25");
	rmsZvtxVspurity("250010","0","25");
	
	weighted_avgPurity("0", "30");
	rmsVspurity("300010","0","30");
	rmsZvtxVspurity("300010","0","30");
	
	weighted_avgPurity("0", "35");
	rmsVspurity("350010","0","35");
	rmsZvtxVspurity("350010","0","35");
	
	weighted_avgPurity("0", "40");
	rmsVspurity("400010","0","40");
	rmsZvtxVspurity("400010","0","40");
	return 0;
}
int writePU200()
{
	
	deleteText("200");	
	weighted_avgPurity("200", "20");
	rmsVspurity("200010","200","20");
	rmsZvtxVspurity("200010","200","20");
	
	weighted_avgPurity("200", "25");
	rmsVspurity("250010","200","25");
	rmsZvtxVspurity("250010","200","25");
	
	weighted_avgPurity("200", "30");
	rmsVspurity("300010","200","30");
	rmsZvtxVspurity("300010","200","30");
	
	weighted_avgPurity("200", "35");
	rmsVspurity("350010","200","35");
	rmsZvtxVspurity("350010","200","35");
	
	weighted_avgPurity("200", "40");
	rmsVspurity("400010","200","40");
	rmsZvtxVspurity("400010","200","40");
	return 0;
}
int writePU1000()
{
	
	deleteText("1k");	
	weighted_avgPurity("1k", "20");
	rmsVspurity("200010","1k","20");
	rmsZvtxVspurity("200010","1k","20");
	
	weighted_avgPurity("1k", "25");
	rmsVspurity("250010","1k","25");
	rmsZvtxVspurity("250010","1k","25");
	
	weighted_avgPurity("1k", "30");
	rmsVspurity("300010","1k","30");
	rmsZvtxVspurity("300010","1k","30");
	
	weighted_avgPurity("1k", "35");
	rmsVspurity("350010","1k","35");
	rmsZvtxVspurity("350010","1k","35");
	
	weighted_avgPurity("1k", "40");
	rmsVspurity("400010","1k","40");
	rmsZvtxVspurity("400010","1k","40");
	return 0;
}

//****************************** PLOT *******************************************//
void SaveCanvas(TCanvas *C, char *name)
{
    char full_name[1023];
    sprintf(full_name,"%s/summary_%s.root", plot_path, name);
    C->SaveAs(full_name);
    sprintf(full_name,"%s/summary_%s.pdf", plot_path, name);
    C->SaveAs(full_name);
    sprintf(full_name,"%s/summary_%s.tex", plot_path, name);
    C->SaveAs(full_name);
    sprintf(full_name,"%s/summary_%s.C", plot_path, name);
    C->SaveAs(full_name);

}
void summary_relptVspurity()
{
	//Multi Graph
	c1->Clear();
	c1->SetLeftMargin(LEFT_MARGIN);
	//c1->SetGridx();
	//c1->SetGridy();
	
	char txt_file1[1023];//PU1000
	char txt_file2[1023];//PU200
	char txt_file3[1023];//PU0

	char plot_title[1023];
	//! PU 1000
	sprintf(txt_file1,"%s/FCCsummary%d-%d_rmsVspurity_PU%s.txt",txt_path, (int)X_min, (int)X_max, "1k");
	//! PU 200
	sprintf(txt_file2,"%s/FCCsummary%d-%d_rmsVspurity_PU%s.txt",txt_path,(int)X_min, (int)X_max, "200");
	//! PU 0
	sprintf(txt_file3,"%s/FCCsummary%d-%d_rmsVspurity_PU%s.txt",txt_path,(int)X_min, (int)X_max, "0");

	sprintf(plot_title,"Relative p_{T} resolution Vs track purity for various gap sizes of the TTT");

	TTree *t1 = new TTree ("t1", "t1");
	t1->ReadFile(txt_file1,"gapsize:purity:rms:err");
	t1->Draw("purity:rms*100:err","","goff");

	TGraphErrors *g1 = new TGraphErrors(n,t1->GetV1(),t1->GetV2(),0,t1->GetV3());
	g1->SetTitle(plot_title);
	g1->GetXaxis()->SetTitle(Form("purity, p_{T} #in (%d, %d) GeV/c", (int)X_min, (int)X_max));
	g1->GetYaxis()->SetTitle("#sigma_{#delta p_{T}/p_{T, gen}} [%], at p_{T} #sim 10 GeV/c");
	//g1->GetXaxis()->SetLimits(0.84,1);
	g1->GetXaxis()->SetLimits(0.83,1);
	//g1->GetYaxis()->SetRangeUser(0.6,1.1);
	g1->GetYaxis()->SetRangeUser(1.4,2.5);
	g1->SetMarkerStyle(kFullCircle);
	g1->GetXaxis()->CenterTitle();
	g1->GetYaxis()->CenterTitle();
	g1->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	g1->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);
	g1->GetXaxis()->SetTitleSize(TITLE_SIZE);
	g1->GetYaxis()->SetTitleSize(TITLE_SIZE);
	c1->cd(4);
	g1->SetFillStyle(0);
	g1->Draw("ALPe1");
	//g1->Draw("ALPe1");
	
	//TTree *t2 = new TTree ("t2", "t2");
	//t2->ReadFile(txt_file2,"gapsize:purity:rms:err");
	//t2->Draw("purity:rms*100:err","","goff");
	//
	//TGraphErrors *g2 = new TGraphErrors(n,t2->GetV1(),t2->GetV2(),0,t2->GetV3());
	//g2->SetTitle(plot_title);
	//g2->GetXaxis()->SetTitle(Form("Average track purity, p_{T} #in (%d, %d) GeV/c", (int)X_min, (int)X_max));
	//g2->GetYaxis()->SetTitle("#sigma_{#delta p_{T}/p_{T, gen}} [%], at p_{T} = 10 GeV/c");
	//g2->GetYaxis()->SetRangeUser(0,1.3);
	//g2->GetXaxis()->SetLimits(0.84,1);
	//g2->SetMarkerStyle(kFullTriangleUp);
	//g2->GetXaxis()->CenterTitle();
	//g2->GetYaxis()->CenterTitle();
	//g2->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	//g2->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);
	//g2->GetXaxis()->SetTitleSize(TITLE_SIZE);
	//g2->GetYaxis()->SetTitleSize(TITLE_SIZE);
	//c1->cd(4);
	//g2->SetFillStyle(0);
	//g2->Draw("LPe1");
	//
	//TTree *t3 = new TTree ("t3", "t3");
	//t3->ReadFile(txt_file3,"gapsize:purity:rms:err");
	//t3->Draw("purity:rms*100:err","","goff");
	//
	//TGraphErrors *g3 = new TGraphErrors(n,t3->GetV1(),t3->GetV2(),0,t3->GetV3());
	//g3->SetTitle(plot_title);
	//g3->GetXaxis()->SetTitle(Form("Average track purity, p_{T} #in (%d, %d) GeV/c", (int)X_min, (int)X_max));
	//g3->GetYaxis()->SetTitle("#sigma_{#delta p_{T}/p_{T, gen}} [%], at p_{T} = 10 GeV/c");
	//g3->GetYaxis()->SetRangeUser(0,1.3);
	//g3->GetXaxis()->SetLimits(0.84,1);
	//g3->SetMarkerStyle(kFullSquare);
	//g3->GetXaxis()->CenterTitle();
	//g3->GetYaxis()->CenterTitle();
	//g3->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	//g3->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);
	//g3->GetXaxis()->SetTitleSize(TITLE_SIZE);
	//g3->GetYaxis()->SetTitleSize(TITLE_SIZE);
	//c1->cd(4);
	//g3->SetFillStyle(0);
	//g3->Draw("LPe1");
	////g2->Draw("Pe1");

////////////////////////////////////////////////////////////////
	//
	////TMultiGraph *g = new TMultiGraph();
	////g->Add(g1);
	////g->Add(g2);
	//////g->Add(g3);
	////g->Draw("APe1");

	////g->SetTitle(plot_title);
	////g->GetXaxis()->SetTitle("Track Purity");
	////g->GetXaxis()->SetRangeUser(0.7,1);
	////g->GetYaxis()->SetTitleOffset(1.5);
	////g->GetYaxis()->SetTitle("#sigma_{#Delta(p_{T})/gen_p_{T}} @ p_{T} = 10 GeV/c");
	////g->GetYaxis()->SetRangeUser(0,0.015);
/////////////////////////////////////////////////////////////

	// get the points in the graph and put them into an array
	Double_t *nx1 = g1->GetX();
	Double_t *ny1 = g1->GetY();
	//Double_t *nx2 = g2->GetX();
	//Double_t *ny2 = g2->GetY();
	//Double_t *nx3 = g3->GetX();
	//Double_t *ny3 = g3->GetY();
	
        TLegend *leg1 = new TLegend(0.71,0.6,0.89,0.79, "~~ gap size");
	//TLegend *leg1=new TLegend(X1,Y1,X2,Y2," ~~~gap size");
	leg1->SetFillStyle(FILL_STYLE);
	leg1->SetFillColor(kWhite);
	leg1->SetBorderSize(BORDER_SIZE);
	leg1->SetTextSize(TEXT_SIZE);
	leg1->SetTextFont(TEXT_FONT);
	header = (TLegendEntry*)leg1->GetListOfPrimitives()->First();
	header->SetTextSize(TEXT_SIZE);
	header->SetTextFont(TEXT_FONT);
	
	TLegend *leg=new TLegend(X1+0.01,Y1,X2+0.01,Y2,"1k 200   0");
	leg->SetFillStyle(FILL_STYLE);
	leg->SetFillColor(kWhite);
	leg->SetBorderSize(BORDER_SIZE);
	leg->SetNColumns(3);
	leg->SetTextSize(TEXT_SIZE);
	leg->SetTextFont(TEXT_FONT);
	header = (TLegendEntry*)leg->GetListOfPrimitives()->First();
	header->SetTextSize(TEXT_SIZE);
	header->SetTextFont(TEXT_FONT);
	
	// create markers of different colors
	Int_t j =0;
	for (j=0; j<n; j++) {
	std::cout << "j , nx, ny: " << j << ", " << nx1 << ", " << ny1 <<std::endl;
	std::cout << "color code : " << (kRed-10) + (3*j) <<std::endl;
	
	TMarker *m1 = new TMarker(nx1[j], ny1[j], kFullCircle);
	m1->SetMarkerSize(MARKER_SIZE);
	m1->SetMarkerColor(j+1);
	m1->Draw();
	
	//TMarker *m2 = new TMarker(nx2[j], ny2[j], kFullTriangleUp);
	//m2->SetMarkerSize(MARKER_SIZE);
	//m2->SetMarkerColor(j+1);
	//m2->Draw();
	//
	//TMarker *m3 = new TMarker(nx3[j], ny3[j], kFullSquare);
	//m3->SetMarkerSize(MARKER_SIZE);
	//m3->SetMarkerColor(j+1);
	//m3->Draw();
	
	//if(j == n - 5) 
	//{
	//	//leg1->AddEntry(m1,"   ");
	//	//leg1->AddEntry(m2,"   ");
	//	leg1->AddEntry(m1,"   20mm");
	//}
	//if(j == n - 4) 
	//{
	//	//leg1->AddEntry(m1,"   ");
	//	//leg1->AddEntry(m2,"   ");
	//	leg1->AddEntry(m1,"   25mm");
	//}
	//if(j == n - 3) 
	//{
	//	//leg1->AddEntry(m1,"   ");
	//	//leg1->AddEntry(m2,"   ");
	//	leg1->AddEntry(m1,"   30mm");
	//}
	//if(j == n - 2)
	//{
	//	//leg1->AddEntry(m1,"   ");
	//	//leg1->AddEntry(m2,"   ");
	//	leg1->AddEntry(m1,"   35mm");
	//}
	//if(j == n -1)
	//{
	//	//leg1->AddEntry(m1,"   ");
	//	//leg1->AddEntry(m2,"   ");
	//	leg1->AddEntry(m1,"   40mm");
	//}
	//}
	if(j == n - 5) 
	{
		leg1->AddEntry(m1,"   53mm");
	}
	if(j == n - 4) 
	{
		leg1->AddEntry(m1,"   67mm");
	}
	if(j == n - 3) 
	{
		leg1->AddEntry(m1,"   80mm");
	}
	if(j == n - 2)
	{
		leg1->AddEntry(m1,"   93mm");
	}
	if(j == n -1)
	{
		leg1->AddEntry(m1,"  106mm");
	}
	}
	//leg->Draw();
	leg1->Draw();
	c1->Update();

        //TLegend *cms_E = new TLegend(0.35,0.91,0.65,0.96);
        TLegend *cms_E = new TLegend(0.55,0.85,0.9,0.9);
        cms_E->SetFillStyle(0);
        cms_E->SetBorderSize(0);
        cms_E->AddEntry((TObject*)0, "#sqrt{s} = 100 TeV", "");
        cms_E->SetTextSize(0.04);
        cms_E->Draw();  
        c1->Update();
        
	TLegend *signal = new TLegend(0.5,0.75,0.9,0.9);
        signal->SetFillStyle(0);
        signal->SetBorderSize(0);
        signal->AddEntry((TObject*)0, "HH #rightarrow b#bar{b}b#bar{b} <#mu> = 1k", "");
        signal->SetTextSize(0.04);
        signal->Draw();
        c1->Update();
	  
	SaveCanvas(c1, out_file_name_pt);

}
void summary_ZvtxVspurity()
{
	//Multi Graph
	c1->Clear();
	c1->SetLeftMargin(LEFT_MARGIN);
	//c1->SetGridx();
	//c1->SetGridy();
	char txt_file1[1023];//PU1000
	char txt_file2[1023];//PU200
	char txt_file3[1023];//PU0

	char plot_title[1023];
	//! PU 1000
	sprintf(txt_file1,"%s/FCCsummary%d-%d_rmsZvtxVspurity_PU%s.txt",txt_path, (int)X_min, (int)X_max, "1k");
	//! PU 200
	sprintf(txt_file2,"%s/FCCsummary%d-%d_rmsZvtxVspurity_PU%s.txt",txt_path, (int)X_min, (int)X_max, "200");
	//! PU 0
	sprintf(txt_file3,"%s/FCCsummary%d-%d_rmsZvtxVspurity_PU%s.txt",txt_path, (int)X_min, (int)X_max, "0");

	sprintf(plot_title,"z_{0} resolution Vs track purity for various gap sizes of the TTT");

	TTree *t1 = new TTree ("t1", "t1");
	t1->ReadFile(txt_file1,"gapsize:purity:rms:err");
	t1->Draw("purity:rms:err","","goff");
	//    TGraphErrors *g1 = new TGraphErrors(24,t1->GetV1(),t1->GetV2(),0,t1->GetV3());

	TGraphErrors *g1 = new TGraphErrors(n,t1->GetV1(),t1->GetV2(),0,t1->GetV3());
	g1->SetTitle(plot_title);
	g1->GetXaxis()->SetTitle(Form("purity, p_{T} #in (%d, %d) GeV/c", (int)X_min, (int)X_max));
	//g1->GetXaxis()->SetLimits(0.84,1);
	g1->GetXaxis()->SetLimits(0.83,1);
	g1->GetYaxis()->SetTitle("#sigma_{#delta z }[mm], at p_{T} #sim 10 GeV/c");
	//g1->GetYaxis()->SetRangeUser(0.25,0.5);
	g1->GetYaxis()->SetRangeUser(0.85,1.8);
	g1->SetMarkerStyle(kFullCircle);
	g1->GetXaxis()->CenterTitle();
	g1->GetYaxis()->CenterTitle();
	g1->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	g1->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);
	g1->GetXaxis()->SetTitleSize(TITLE_SIZE);
	g1->GetYaxis()->SetTitleSize(TITLE_SIZE);
	c1->cd(4);
	g1->SetFillStyle(0);
	g1->Draw("ALPe1");
	
	//TTree *t2 = new TTree ("t2", "t2");
	//t2->ReadFile(txt_file2,"gapsize:purity:rms:err");
	//t2->Draw("purity:rms:err","","goff");
	//TGraphErrors *g2 = new TGraphErrors(n,t2->GetV1(),t2->GetV2(),0,t2->GetV3());
	//g2->SetTitle(plot_title);
	//g2->GetXaxis()->SetTitle(Form("Average track purity, p_{T} #in (%d, %d) GeV/c", (int)X_min, (int)X_max));
	//g2->GetXaxis()->SetLimits(0.84,1);
	//g2->GetYaxis()->SetTitle("#sigma_{#delta z}[mm], at p_{T} = 10 GeV/c");
	//g2->GetYaxis()->SetRangeUser(0,0.6);
	//g2->SetMarkerStyle(kFullTriangleUp);
	//g2->GetXaxis()->CenterTitle();
	//g2->GetYaxis()->CenterTitle();
	//g2->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	//g2->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);
	//g2->GetXaxis()->SetTitleSize(TITLE_SIZE);
	//g2->GetYaxis()->SetTitleSize(TITLE_SIZE);
	//c1->cd(4);
	//g2->SetFillStyle(0);
	//g2->Draw("LPe1");
	//
	//TTree *t3 = new TTree ("t3", "t3");
	//t3->ReadFile(txt_file3,"gapsize:purity:rms:err");
	//t3->Draw("purity:rms:err","","goff");
	//TGraphErrors *g3 = new TGraphErrors(n,t3->GetV1(),t3->GetV2(),0,t3->GetV3());
	//g3->SetTitle(plot_title);
	//g3->GetXaxis()->SetTitle(Form("Average track purity, p_{T} #in (%d, %d) GeV/c", (int)X_min, (int)X_max));
	//g3->GetXaxis()->SetLimits(0.84,1);
	//g3->GetYaxis()->SetTitle("#sigma_{#delta z}[mm], at p_{T} = 10 GeV/c");
	//g3->GetYaxis()->SetRangeUser(0,0.6);
	//g3->SetMarkerStyle(kFullTriangleUp);
	//g3->GetXaxis()->CenterTitle();
	//g3->GetYaxis()->CenterTitle();
	//g3->GetXaxis()->SetTitleOffset(AXISTITLE_OFFSET);
	//g3->GetYaxis()->SetTitleOffset(YAXISTITLE_OFFSET);
	//g3->GetXaxis()->SetTitleSize(TITLE_SIZE);
	//g3->GetYaxis()->SetTitleSize(TITLE_SIZE);
	//c1->cd(4);
	//g3->SetFillStyle(0);
	//g3->Draw("LPe1");


////////////////////////////////////////////////////////////////
	///*
	//TMultiGraph *g = new TMultiGraph();
	////g->Add(g1);
	//g->Add(g2);
	////g->Add(g3);
	//g->Draw("APe1");

	//g->SetTitle(plot_title);
	//g->GetXaxis()->SetTitle("Track Purity");
	//g->GetXaxis()->SetRangeUser(0.7,1);
	//g->GetYaxis()->SetTitleOffset(1.5);
	//g->GetYaxis()->SetTitle("#sigma_{#Delta(p_{T})/gen_p_{T}} @ p_{T} = 10 GeV/c");
	//g->GetYaxis()->SetRangeUser(0,0.015);*/
///////////////////////////////////////////////////////////////

	// get the points in the graph and put them into an array
	Double_t *nx1 = g1->GetX();
	Double_t *ny1 = g1->GetY();
	//Double_t *nx2 = g2->GetX();
	//Double_t *ny2 = g2->GetY();
	//Double_t *nx3 = g3->GetX();
	//Double_t *ny3 = g3->GetY();
	
        TLegend *leg1 = new TLegend(0.71,0.6,0.89,0.79, "~~ gap size");
	//TLegend *leg1=new TLegend(X1,Y2,X2,Y2+0.07,"  ~~~~  gap size");
	leg1->SetFillStyle(FILL_STYLE);
	leg1->SetFillColor(kWhite);
	leg1->SetBorderSize(BORDER_SIZE);
	leg1->SetTextSize(TEXT_SIZE);
	leg1->SetTextFont(TEXT_FONT);
	header = (TLegendEntry*)leg1->GetListOfPrimitives()->First();
	header->SetTextSize(TEXT_SIZE);
	header->SetTextFont(TEXT_FONT);
	
	TLegend *leg=new TLegend(X1+0.01,Y1,X2+0.01,Y2,"1k 200   0");
	leg->SetFillStyle(FILL_STYLE);
	leg->SetFillColor(kWhite);
	leg->SetBorderSize(BORDER_SIZE);
	leg->SetNColumns(3);
	leg->SetTextSize(TEXT_SIZE);
	leg->SetTextFont(TEXT_FONT);
	header = (TLegendEntry*)leg->GetListOfPrimitives()->First();
	header->SetTextSize(TEXT_SIZE);
	header->SetTextFont(TEXT_FONT);
	
	// create markers of different colors
	Int_t j =0;
	for (j=0; j<n; j++) {
	std::cout << "j , nx, ny: " << j << ", " << nx1 << ", " << ny1 <<std::endl;
	std::cout << "color code : " << (kRed-10) + (3*j) <<std::endl;
	
	TMarker *m1 = new TMarker(nx1[j], ny1[j], kFullCircle);
	m1->SetMarkerSize(MARKER_SIZE);
	m1->SetMarkerColor(j+1);
	m1->Draw();
	
	//TMarker *m2 = new TMarker(nx2[j], ny2[j], kFullTriangleUp);
	//m2->SetMarkerSize(MARKER_SIZE);
	//m2->SetMarkerColor(j+1);
	//m2->Draw();
	//
	//TMarker *m3 = new TMarker(nx3[j], ny3[j], kFullSquare);
	//m3->SetMarkerSize(MARKER_SIZE);
	//m3->SetMarkerColor(j+1);
	//m3->Draw();
		
	//if(j == n - 5) 
	//{
	//	leg1->AddEntry(m1,"   20mm");
	//}
	//if(j == n - 4) 
	//{
	//	leg1->AddEntry(m1,"   25mm");
	//}
	//if(j == n - 3) 
	//{
	//	leg1->AddEntry(m1,"   30mm");
	//}
	//if(j == n - 2)
	//{
	//	leg1->AddEntry(m1,"   35mm");
	//}
	//if(j == n -1)
	//{
	//	leg1->AddEntry(m1,"   40mm");
	//}
	//}
	if(j == n - 5) 
	{
		leg1->AddEntry(m1,"   53mm");
	}
	if(j == n - 4) 
	{
		leg1->AddEntry(m1,"   67mm");
	}
	if(j == n - 3) 
	{
		leg1->AddEntry(m1,"   80mm");
	}
	if(j == n - 2)
	{
		leg1->AddEntry(m1,"   93mm");
	}
	if(j == n -1)
	{
		leg1->AddEntry(m1,"  106mm");
	}
	}
	//leg->Draw();
	leg1->Draw();
	c1->Update();

        //TLegend *cms_E = new TLegend(0.35,0.91,0.65,0.96);
        TLegend *cms_E = new TLegend(0.55,0.85,0.9,0.9);
        cms_E->SetFillStyle(0);
        cms_E->SetBorderSize(0);
        cms_E->AddEntry((TObject*)0, "#sqrt{s} = 100 TeV", "");
        cms_E->SetTextSize(0.04);
        cms_E->Draw();  
        c1->Update();
        
	TLegend *signal = new TLegend(0.5,0.75,0.9,0.9);
        signal->SetFillStyle(0);
        signal->SetBorderSize(0);
        signal->AddEntry((TObject*)0, "HH #rightarrow b#bar{b}b#bar{b}, <#mu>=1k", "");
        signal->SetTextSize(0.04);
        signal->Draw();
        c1->Update();
	SaveCanvas(c1,out_file_name_z);

}

void plot_all()
{

	writePU1000();
	summary_relptVspurity();
	summary_ZvtxVspurity();
}
