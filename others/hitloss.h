
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>

#include "TROOT.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TLegend.h"
#include "TPostScript.h"
#include "TAxis.h"
#include "TGaxis.h"
#include "TF1.h"

//! some histo vars
const int bins = 150;
float max_bin = 150.;

//! File paths
const char *in_path = "./root";
const char *out_path = "./root";
const char *in_file_name = "cluster_occ_max_ggF1_PU1k";
const char *out_file_name = "cluster_occ_max_ggF1_PU1k";
//const char *in_file_name = "occ_max_ggF1_PU200";
//const char *out_file_name = "occ_summ_ggF1_PU200";
char in_file[1023];
char out_file[1023];

//! input root file
TFile *f = nullptr;
//! input ttree
TTree *t = nullptr;
//! input hitograms
TH1F *h_count8 =nullptr; 
TH1F *h_count9 =nullptr;
TH1F *h_count10=nullptr;

TH1F *h0 = nullptr;
TH1F *h1 = nullptr;
TH1F *h2 = nullptr;
TH1F *h3 = nullptr;
TH1F *h4 = nullptr;
TH1F *h5 = nullptr;
TH1F *h6 = nullptr;
TH1F *h8 = nullptr;
TH1F *h9 = nullptr;
TH1F *h10= nullptr;
TH1F *h11= nullptr;
TH1F *h12= nullptr;
TH1F *h13= nullptr;
TH1F *h14= nullptr;
TH1F *h15= nullptr;
TH1F *h16= nullptr;

//!output root file
TFile *fout = nullptr;
//! output historgrams
//! x.f(x) histo; i.e. counts * n_events(counts)
TH1F *ht_count8 =nullptr; 
TH1F *ht_count9 =nullptr;
TH1F *ht_count10=nullptr;
//! hit efficiency
TH1F *he_8 =nullptr; 
TH1F *he_9 =nullptr;
TH1F *he_10=nullptr;
//! hit loss
TH1F *hl_8 =nullptr; 
TH1F *hl_9 =nullptr;
TH1F *hl_10=nullptr;

//! some more variables
int normalization[3];// integral 0 to inf
double integral8[bins]; //integral 0 to cut value(bin number or counts)
double integral9[bins]; //integral 0 to cut value(bin number or counts)
double integral10[bins]; //integral 0 to cut value(bin number or counts)
double epcilon8[bins]; 
double epcilon9[bins]; 
double epcilon10[bins];
