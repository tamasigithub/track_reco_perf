
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

int nbins = 500;
float max_cnt = 500.;

//! File paths
//const char *file_path = "/user/tkar/work/data/merge/user.tkar.ggF1.0hh4b_SIMPU200_Br30mmEC80mm";
//const char *file_names = "user.tkar.24726593._0000*.output.merged";
const char *file_path = "/user/tkar/work/data/rec/sel/Br30mmEC80mm/PU1k/ggF_clstrocc";
const char *file_names = "user.tkar_000*.recTree.merged";
const char *out_path = "./root";
const char *out_file_name = "cluster_occ_max_ggF1_PU1k";

//! some variables
int current_layer = -1;
const int tot_layers = 17; //(0-16, missing layerId = 7, BrTTT layerIds= 8,9,10, rest EC)
const int missing_layer = 7;
std::vector<int> vec_max_count(tot_layers, 0);

//! File names;
char input_file_names[1023];
char out_file[1023];

//! root files and TTrees
TFile *f_in  = nullptr;
TFile *f_out = nullptr;

//TTree *t_in  = nullptr;
TTree *t_out = nullptr;

//! input tree variables
std::vector<unsigned int> *sid  = 0;
//std::vector<unsigned int> *cpy_sid  = 0;
//std::vector<unsigned int> *pxid = 0;

//! out tree variables
std::vector<unsigned int> array_unique_sids[tot_layers];
std::vector<int> array_count_sids[tot_layers];
std::vector<unsigned int> unique_sids;
std::vector<int> count_unique_sids;
// max counts for the corresponding layers
TH1F **h = nullptr;

// summarry histo of avg(max_count)per event vs layer radius
//TH2F *h_sum = nullptr;
//
////int max_L0;
////int max_L1;
////int max_L2;
////int max_L3;
////int max_L4;
////int max_L5;
////int max_L6;
////// Br TTT
////int max_L8;
////int max_L9;
////int max_L10;
////// EC TTT
////int max_L11;
////int max_L12;
////int max_L13;
////int max_L14;
////int max_L15;
////int max_L16;



