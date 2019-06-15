//! draws a summary plot 
//! of hit occupancy as a function of detector layer radius  
//! for various pileup configurations 0,200,1000 for e.g.
//! extract the number of entries and n_events for each layer and write the following to a text file
//! n_events n_hits n_modules layer_radius pileup
//! read this txt file to draw a graph of n_hits/cm^2/event Vs radius for a given pileup
//! do the same for various pileups and draw a multigraph

#include <iostream>
#include <fstream>
#include <string>
#include<math.h>

#include "TROOT.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TPostScript.h"

#include "TAxis.h"
#include "TGaxis.h"
#include "TF1.h"

//! clears the txt file
void deleteText(const char* pileup) {
    const char* txt_path = "./txt_files";
    char txt_file[1023];
    //sprintf(txt_file,"%s/summary10-100_rmsVspurity_PU%s.txt",txt_path, pileup);
    sprintf(txt_file,"%s/summary_rmsVspurityNo30mm_PU%s.txt",txt_path, pileup);
    std::ofstream ofs;
    ofs.open(txt_file, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}


//! opens the reconstructed root file with gap size = "run_no" and momentum "p"(e.g. 10GeV/c)
//! hence calls the draw function. 
//! This function draws the resolution plots and fits a gaus function and
//! fetches the rms and errors from the fit and hence calls the write function.
//! the write function creates a txt file and prints 
//! the run_no, the momentum p, rms, and error..

//! run_no - run number of the single particle file
//! first two numbers of which are identical to gap size
void hit_occ(const char *pileup, const char *gapsize)
{
	Int_t num_events = 0;
	const int num_layers = 11;
	//! default values for TTT with 20mm gap size
	Int_t n_modules[num_layers] = {10,20,32,48,18, 26, 34, 48, 58, 58, 58};
	Double_t layer_radius[num_layers] = {2.5,6,10,15,27, 40, 52, 75, 82.7, 85.7, 88.7};
	Double_t sensor_area, module_area ; //in cm^2
	Int_t n_sensors; //number of sensors in a module
	Double_t num_hits[num_layers] = {0};
	Double_t hit_occ[num_layers] = {0};//  #/cm^2/event

	//! Fetch the histograms
	const char *file_path = "/home/tamasi/repo_tamasi/rec_files";
	char signal_file_names[1023];
	//sprintf(signal_file_names, "%s/PU%shh4b_m260_recTree_%s0001_opt.root",file_path,pileup,gapsize);
	sprintf(signal_file_names, "%s/PU%shh4b_recTree_%s0002_samelad_opt.root",file_path,pileup,gapsize);
	TFile *f = new TFile(signal_file_names, "READ");
	TTree *tree = (TTree*)f->Get("m_recTree");
	num_events = tree->GetEntries();	
	TH1F *L1 = (TH1F*)f->Get("hitL1");
	TH1F *L2 = (TH1F*)f->Get("hitL2");
	TH1F *L3 = (TH1F*)f->Get("hitL3");
	TH1F *L4 = (TH1F*)f->Get("hitL4");
	TH1F *L5 = (TH1F*)f->Get("hitL5");
	TH1F *L6 = (TH1F*)f->Get("hitL6");
	TH1F *L7 = (TH1F*)f->Get("hitL7");
	TH1F *L8 = (TH1F*)f->Get("hitL8");
	TH1F *L9 = (TH1F*)f->Get("hitL9");
	TH1F *L10 = (TH1F*)f->Get("hitL10");
	TH1F *L11 = (TH1F*)f->Get("hitL11");
	
	TCanvas *c = new TCanvas();	
        TH1::SetDefaultSumw2(true);
	
	//! Fill num_hits
	num_hits[0] = L1->GetEntries();
	num_hits[1] = L2->GetEntries();
	num_hits[2] = L3->GetEntries();
	num_hits[3] = L4->GetEntries();
	num_hits[4] = L5->GetEntries();
	num_hits[5] = L6->GetEntries();
	num_hits[6] = L7->GetEntries();
	num_hits[7] = L8->GetEntries();
	num_hits[8] = L9->GetEntries();
	num_hits[9] = L10->GetEntries();
	num_hits[10] = L11->GetEntries();

	//! calculate hit occupancy
	for(int i = 0; i < num_layers; i++)
	{
		if(i < 4)
		{
			sensor_area = 2.0 * 2.0; //in cm^2
			n_sensors = 225; //number of sensors in a module
		}
		else
		{
			sensor_area = 10 * 9.98; //in cm^2
			n_sensors = 45; //number of sensors in a module
			
		}
		module_area = sensor_area * n_sensors;
		hit_occ[i] = num_hits[i]/(num_events * module_area * n_modules[i]);
	}

        //! write to a text file
	std::cout<<"Writing to txt file...." <<std::endl;
        const char* txt_path = "./txt_files";
        char txt_file[1023];
        sprintf(txt_file,"%s/summary_hitOccVsRadius_PU%s_%s.txt",txt_path, pileup,gapsize);
        std::ofstream ofs;
        ofs.open (txt_file, std::ofstream::out | std::ofstream::app);
	for(int i = 0; i < num_layers; i++)
	{
        	ofs<<layer_radius[i]<<" "<<hit_occ[i]<<"\n";
	}
        ofs.close();
}


void SaveCanvas(TCanvas *C, char *name)
{
    const char *path = "./summary_plots";
    char full_name[1023];
    sprintf(full_name,"%s/summary_%s.root", path, name);
    C->SaveAs(full_name);
    sprintf(full_name,"%s/summary_%s.pdf", path, name);
    C->SaveAs(full_name);
    sprintf(full_name,"%s/summary_%s.png", path, name);
    C->SaveAs(full_name);
    sprintf(full_name,"%s/summary_%s.C", path, name);
    C->SaveAs(full_name);

}
void summary_hitOccVsRadius()
{
	//! no. of points to be plotted
	Int_t n = 11;
	Double_t Xmin_range = 0.0, Xmax_range = 1.0e2;
	Double_t Ymin_range = 5e-4, Ymax_range = 5.0e1;
	//Multi Graph
	TCanvas * c1 = new TCanvas();
	c1->Clear();
	c1->SetGridx();
	c1->SetGridy();
	const char* txt_path = "./txt_files";
	char txt_file1[1023];//PU1000
	char txt_file2[1023];//PU200
	char txt_file3[1023];//PU0

	char plot_title[1023];
	//! PU 1000
	sprintf(txt_file1,"%s/summary_hitOccVsRadius_PU%s_30.txt",txt_path,"1000");
	//! PU 200
	sprintf(txt_file2,"%s/summary_hitOccVsRadius_PU%s.txt",txt_path,"200");
	//! no pileup
	sprintf(txt_file3,"%s/summary_hitOccVsRadius_PU%s_30.txt",txt_path,"0");

	sprintf(plot_title,"Hit Occupancy as a function of layer radius");

	TTree *t1 = new TTree ("t1", "t1");
	t1->ReadFile(txt_file1,"radius:hitOcc");
	t1->Draw("radius:hitOcc","","goff");
	//    TGraphErrors *g1 = new TGraphErrors(24,t1->GetV1(),t1->GetV2(),0,t1->GetV3());

	TGraphErrors *g1 = new TGraphErrors(n,t1->GetV1(),t1->GetV2(),0,0);
	g1->SetTitle(plot_title);
	g1->GetXaxis()->SetTitle("Layer Radius [cm]");
	g1->GetXaxis()->SetRangeUser(Xmin_range, Xmax_range);
	g1->GetYaxis()->SetTitleOffset(1.2);
	g1->GetYaxis()->SetTitle("hit occupancy [/event/cm^{2}]");
	g1->GetYaxis()->SetRangeUser(Ymin_range, Ymax_range);
	g1->SetMarkerStyle(20);//kFullCircle);
	g1->SetMarkerSize(1.9);
	c1->cd(4);
	g1->SetFillStyle(0);
	g1->SetTitle("<#mu> = 960");
	//g1->Draw("ACPe1");
	g1->Draw("APe1");
	
	TTree *t2 = new TTree ("t2", "t2");
	t2->ReadFile(txt_file2,"radius:hitOcc");
	t2->Draw("radius:hitOcc","","goff");
	//    TGraphErrors *g2 =new TGraphErrors(24,t2->GetV1(),t2->GetV2(),0,t2->GetV3());
	//TGraph *g2 = new TGraph(n,t2->GetV1(),t2->GetV2());
	TGraphErrors *g2 = new TGraphErrors(n,t2->GetV1(),t2->GetV2(),0,0);
	g2->SetTitle(plot_title);
	g2->GetXaxis()->SetTitle("Layer Radius [cm]");
	g2->GetXaxis()->SetRangeUser(Xmin_range, Xmax_range);
	g2->GetYaxis()->SetTitleOffset(1.2);
	g2->GetYaxis()->SetTitle("hit occupancy [/event/cm^{2}]");
	g2->GetYaxis()->SetRangeUser(Ymin_range, Ymax_range);
	g2->SetMarkerStyle(22);//kFullTriangleUp);
	g2->SetMarkerSize(1.9);
	c1->cd(4);
	g2->SetFillStyle(0);
	g2->SetTitle("<#mu> = 160");
	//g2->Draw("CPe1");
	g2->Draw("Pe1");

	TTree *t3 = new TTree ("t3", "t3");
	t3->ReadFile(txt_file3,"radius:hitOcc");
	t3->Draw("radius:hitOcc","","goff");
	//    TGraphErrors *g3 =new TGraphErrors(24,t3->GetV1(),t3->GetV2(),0,t3->GetV3());
	//TGraph *g3 = new TGraph(n,t3->GetV1(),t3->GetV2());
	TGraphErrors *g3 = new TGraphErrors(n,t3->GetV1(),t3->GetV2(),0,0);
	g3->SetTitle(plot_title);
	g3->GetXaxis()->SetTitle("Layer Radius [cm]");
	g3->GetXaxis()->SetRangeUser(Xmin_range, Xmax_range);
	g3->GetYaxis()->SetTitleOffset(1.2);
	g3->GetYaxis()->SetTitle("hit occupancy [/event/cm^{2}]");
	g3->GetYaxis()->SetRangeUser(Ymin_range, Ymax_range);
	g3->SetMarkerStyle(29);//kFullStar);
	g3->SetMarkerSize(2.5);
	c1->cd(4);
	g3->SetFillStyle(0);
	g3->SetTitle("<#mu> = 0");
	//g3->Draw("CPe1");
	g3->Draw("Pe1");


//////////////////////////////////////////////////////////////
	
	Double_t x1= 0.7,y1= 0.7, x2 = 0.89, y2 = 0.89;
	TMultiGraph *g = new TMultiGraph();
	g->Add(g1);
	g->Add(g2);
	g->Add(g3);
	g->Draw("AP");
	g->SetTitle(plot_title);
	g->GetXaxis()->SetTitle("Layer Radius [cm]");
	g->GetYaxis()->SetTitle("hit occupancy [/event/cm^{2}]");
	g->GetXaxis()->SetTitleSize(0.04);
	g->GetYaxis()->SetTitleSize(0.04);
	//g->GetXaxis()->SetRangeUser(0,100);
	//g->GetYaxis()->SetTitleOffset(1.5);
	g->GetYaxis()->SetRangeUser(Ymin_range, Ymax_range);
	c1->BuildLegend(x1,y1,x2,y2,"pileup");

	//! draw a second Y axis
	// scale rightmax to pad co-o
	//Float_t rightmax = 1.0*g->GetHistogram()->GetMaximum();
	//std::cout<< "rightmax: " << rightmax << std::endl;
	//std::cout<< "Uxmax: " << gPad->GetUxmax() << std::endl;
	//std::cout<< "Uymin: " << gPad->GetUymin() << std::endl;
	//std::cout<< "Uymax: " << gPad->GetUymax() << std::endl;
	//Float_t scale = 32.0/25.0;
	//TGaxis *A1 = new TGaxis(gPad->GetUxmax(), gPad->GetUymin(), gPad->GetUxmax(), rightmax, 0, Ymax_range*scale, 510, "+");
	//A1->Draw();
	c1->SetLogy();
	c1->Update();
	SaveCanvas(c1,"summary_hitOcc_variousPU");
/////////////////////////////////////////////////////////////

	// get the points in the graph and put them into an array
	/*Double_t *nx1 = g1->GetX();
	Double_t *ny1 = g1->GetY();
	Double_t *nx = g2->GetX();
	Double_t *ny = g2->GetY();
	
	Double_t x1= 0.1,y1= 0.1, x2 = 0.3, y2 = 0.3;
	TLegend *leg=new TLegend(x1,y2,x2,y2+0.1,"<#mu>,  gap size");
	leg->SetFillColor(kWhite);
	leg->SetBorderSize(0);
	
	TLegend *leg1=new TLegend(x1,y1,x2,y2,"960, 160");
	leg1->SetFillColor(kWhite);
	leg1->SetBorderSize(0);
	leg1->SetNColumns(2);
	// create markers of different colors
	Int_t j =0;
	for (j=0; j<n; j++) {
	std::cout << "j , nx, ny: " << j << ", " << nx << ", " << ny <<std::endl;
	std::cout << "color code : " << (kRed-10) + (3*j) <<std::endl;
	TMarker *m1 = new TMarker(nx1[j], ny1[j], kFullCircle);
	m1->SetMarkerSize(2);
	//m1->SetMarkerColor((kBlue-10) + (3*j));
	m1->SetMarkerColor(j+1);
	m1->Draw();
	TMarker *m = new TMarker(nx[j], ny[j], kFullTriangleUp);
	m->SetMarkerSize(2);
	//m->SetMarkerColor((kRed-10) + (3*j));
	m->SetMarkerColor(j+1);
	m->Draw();
	if(j == 0) 
	{
		leg1->AddEntry(m1,",");
		leg1->AddEntry(m,"   50mm");
	}
	if(j == 1) 
	{
		leg1->AddEntry(m1,",");
		leg1->AddEntry(m,"   40mm");
	}
	if(j == 2)
	{
		leg1->AddEntry(m1,",");
		leg1->AddEntry(m,"   20mm");
	}
	}
	leg->Draw();
	leg1->Draw();
	c1->Update();
	SaveCanvas(c1,"relptVspurityNo30mm10GeV_varPU1");*/

}

