//! draws a summary plot 
//! of single particle resolution as a function of track purity 
//! for various gap sizes of the TTT
//! write the rms of resolution, its error and track purity for each gap size into a text file
//! read this txt file to draw a graph of reso Vs track purity for various gap sizes for a given pileup
//! do the same for various pileups and draw a multigraph
#include <iostream>
#include "TROOT.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TGraphErrors.h"
#include "TPostScript.h"
#include <fstream>
#include <string>
#include <math.h>

char *out_file_name_pt = "rms_pT_Vs_purity";
char *out_file_name_z  = "rms_z_Vs_purity";
const char* plot_path = "./summary_purity";

const char* txt_path = "./txt_files";
char txt_file[1023];

const char *file_path = "/user/tkar/work/data/rec/opt";
char signal_file_names[1023];
char rec_file_names[1023];//single particle file

//! Variable bin width
const int ptbins = 40;//no. of bins
Double_t xbins[ptbins+1];//elements of this array are
double dx = 5./ptbins;//5 -> implies max until 10^5
double l10 = TMath::Log(10);

//! pt range to integrate over
//! in GeV/c
double X_min = 10;
double X_max = 100;
//! single particle resolution
double binNum = 100;
double relptmin = -0.1, relptmax = 0.1;
double zmin = -6, zmax = 6;

//! the selection cuts below are only to select tracks correctly reconstructed and fakes
//! assumes the files fed are reconstructed with optimised cuts already
TCut num_select    = "abs(station)==1 && Tid>0 && abs(Eta13) > 1.7 && abs(kappa_pull) <= 3";
TCut den_select    = "abs(station)==1 && Tid>-2 && abs(Eta13) > 1.7 && abs(kappa_pull) <= 3";

//! use the cut below to calculate single particle resolution for 10GeV pions
TCut all_cut= "abs(station)==1 && Tid > 0 && abs(Eta13) > 1.7 && abs(kappa_pull) <= 3 && abs(M_pt)>9e3 && abs(M_pt)<11e3 && abs(M_eta)>1.7 && abs(M_Vz) < 100 && abs(M_Vx) < 10 && abs(M_Vy) < 10 && abs(M_pdg)==211";

TCanvas *c1 = new TCanvas("c1","c1", 800, 800);

double weighted_avg = 0;

TH1* h_num_vs_ptPU = nullptr; 
TH1* h_den_vs_ptPU = nullptr; 
TH1* h_pur_vs_ptPU = nullptr;

TH1F* h_p 	   = nullptr;

//! no. of points to be plotted
Int_t n = 5;

Float_t LINE_WIDTH = 2.5;
Float_t TITLE_SIZE = 0.04;
Float_t MARKER_SIZE = 2.0;
Float_t AXISTITLE_OFFSET = 1.2;
Float_t YAXISTITLE_OFFSET = 1.2;

Float_t LEFT_MARGIN = 0.13;

//********** Legend Properties ************//
//! Draw Legends

TLegendEntry *header = nullptr;
double X1= 0.14,Y1= 0.11, X2 = 0.44, Y2 = 0.31;
Float_t ENTRY_SEP = 0.05;
Float_t FILL_STYLE = 0;
Float_t BORDER_SIZE = 0;
Float_t TEXT_ALIGN = 32;
Float_t TEXT_ALIGN_1 = 12;
Float_t TEXT_FONT = 62;
Float_t TEXT_SIZE = 0.04;
