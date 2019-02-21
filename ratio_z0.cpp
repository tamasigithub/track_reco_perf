//// Ratio plot of offline and triplet track parameters ////////
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
#include "TCut.h"
#include <vector>
#include <algorithm> 
#include <functional>
#include <fstream>
#include <string>
#include <math.h>

const char* out_path = "./plots";
//TCut InDet_cut = "(abs(InDetpt) > 5e3 && abs(InDeteta)<1.4 && abs(InDetz0)<100)";
//TCut TTT_cut = "(abs(TTTpt) > 5e3 && abs(TTTeta)<1.4 && abs(TTTz0)<100)";
TCut InDet_cut = "weight/abs(weight)*(abs(InDetpt) > 5e3 && abs(InDeteta)<1.4 && abs(InDetz0)<100)";
TCut TTT_cut = "weight/abs(weight)*(abs(TTTpt) > 5e3 && abs(TTTeta)<1.4 && abs(TTTz0)<100)";
int ratio_z0(const char* output_file_name = "ratio_z0", bool debug = false)
{

	int nbins = 20;
	double zmin = -100.0;
	double zmax = 100.0;
	//! load input files
	TChain tree("m_collectionTree");
	tree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/user.tkar.hh4bsig5PU0_2_ntuples1_MYSTREAM/*.root");
	if(debug) std::cout<<"m_collectionTree opened with " << tree.GetEntries() << " entries" <<std::endl;

	TH1F* h1 = new TH1F("h1","reconstructed z0; z0[mm];",nbins, zmin, zmax);//ttt 
	h1->Sumw2();
	TH1F* h2 = new TH1F("h2","h2",nbins, zmin, zmax);
	h2->Sumw2();

	tree.Draw("TTTz0>>h1", TTT_cut);
	tree.Draw("InDetz0>>h2",InDet_cut);
	
        Double_t x1= 0.7,y1= 0.75, x2 = 0.89, y2 = 0.89;
	// Define the Canvas
	TCanvas *c = new TCanvas("c", "canvas", 800, 800);
	gStyle->SetOptStat(0);
	// Upper plot will be in pad1
	TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
	pad1->SetBottomMargin(0); // Upper and lower plot are joined
	pad1->SetGridx();         // Vertical grid
	pad1->SetGridy();         // Vertical grid
	pad1->Draw();             // Draw the upper pad: pad1
	pad1->cd();               // pad1 becomes the current pad
	h1->SetStats(0);          // No statistics on upper plot
	h1->Draw("e1");           // Draw h1
	h2->Draw("e1 same");      // Draw h2 on top of h1
        TLegend *leg1=new TLegend(x1,y1,x2,y2,"");
	leg1->SetFillColor(kWhite);
	leg1->SetBorderSize(0);
	leg1->AddEntry(h1,"triplet tracks");
	leg1->AddEntry(h2,"InDet tracks");
	leg1->SetTextAlign(32);
	leg1->SetTextSize(0.035);
        leg1->Draw();

	// lower plot will be in pad
	c->cd();          // Go back to the main canvas before defining pad2
	TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
	pad2->SetTopMargin(0);
	pad2->SetBottomMargin(0.2);
	pad2->SetGridx(); // vertical grid
	pad2->SetGridy(); // vertical grid
	pad2->Draw();
	pad2->cd();       // pad2 becomes the current pad

	// Define the ratio plot
	TH1F *h3 = (TH1F*)h1->Clone("h3");
	h3->SetLineColor(kBlack);
	h3->SetMinimum(0.7);  // Define Y ..
	h3->SetMaximum(1.4); // .. range
	h3->Sumw2();
	h3->SetStats(0);      // No statistics on lower plot
	h3->Divide(h2);
	h3->SetMarkerStyle(21);
	h3->Draw("e1 p");     // Draw the ratio plot        

	// h1 settings
	h1->SetLineColor(kBlue+1);
	h1->SetLineWidth(2);

	// Y axis h1 plot settings
	h1->GetYaxis()->SetTitleSize(20);
	h1->GetYaxis()->SetTitleFont(43);
	h1->GetYaxis()->SetTitleOffset(1.55);

	// h2 settings
	h2->SetLineColor(kRed);
	h2->SetLineWidth(2);

	// Ratio plot (h3) settings
	h3->SetTitle(""); // Remove the ratio title

	// Y axis ratio plot settings
	h3->GetYaxis()->SetTitle("ratio ");	
	h3->GetYaxis()->SetTitleSize(20);
	h3->GetYaxis()->SetTitleFont(43);
	h3->GetYaxis()->SetTitleOffset(1.55);
	h3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	h3->GetYaxis()->SetLabelSize(15);

	// X axis ratio plot settings
	h3->GetXaxis()->SetTitleSize(20);
	h3->GetXaxis()->SetTitleFont(43);
	h3->GetXaxis()->SetTitleOffset(4.);
	h3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	h3->GetXaxis()->SetLabelSize(15);
	//! Save as pdf
        /*char out_file_open[1023];
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
	*/

return 0;
}
