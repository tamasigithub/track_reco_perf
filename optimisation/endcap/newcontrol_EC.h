#include <iostream>
#include "TROOT.h"
#include "TFile.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TPostScript.h"
#include "TMath.h"
#include "TChain.h"
#include "TH1.h"
#include "TLegend.h"
#include <fstream>
#include <string>
#include <math.h>

//! kappa cut based on hit uncertainty and MS formula
//http://tkar.web.cern.ch/tkar/TTT/cuts_2.pdf

const char* out_path = "./root_files";

//! HIstogram variables
int nbins = 300;
double pt_min       = 1e3,   pt_max       = 25e3;
double phi_min      = -0.04, phi_max      = 0.04;
double zij_min      = -520., zij_max      = 520.;
double z0_min       = -125., z0_max       = 125.;
double dphi2_min    = -5e-3, dphi2_max    = 5e-3;
double deta2_min    = -5e-3, deta2_max    = 5e-3;
double dz2_min      = -1,    dz2_max      = 1;
double dr2_min      = -10,   dr2_max      = 10;
double theta_min    = 0,     theta_max    = 3;
double cosTheta_min = 0,    cosTheta_max = 0.45;
double sinTheta_min = 0,     sinTheta_max = 1.1;
double dca_min      = -850,  dca_max      = 850;
double kTru_min     = -8e-4, kTru_max     = 8e-4;
double k013_min     = -8e-4, k013_max     = 8e-4;
double k123_min     = -0.01, k123_max     = 0.01;
double k013Ratio_min= 0.5,   k013Ratio_max= 1.5;
double k123Ratio_min= 20.,   k123Ratio_max= 20.;
double r_min        = 0,     r_max        = 850;
//! Books histograms

TH1F* h3   = nullptr;
TH1F* h5   = nullptr;
TH1F* h5a  = nullptr;

TH2F* h1   = nullptr;
TH2F* h2   = nullptr;
TH2F* h4   = nullptr;
TH2F* h6   = nullptr;
TH2F* h7   = nullptr;
TH2F* h8   = nullptr;
TH2F* h9   = nullptr;
TH2F* h10  = nullptr;

TH2F* h11  = nullptr;

TH2F* h12  = nullptr;
TH2F* h13  = nullptr;
TH2F* h14  = nullptr;
TH1F* h14a = nullptr;
TH2F* h15  = nullptr;
TH2F* h16  = nullptr;
TH2F* h17  = nullptr;
TH1F* h17a = nullptr;
 
TH2F* h18  = nullptr;
TH2F* h19  = nullptr;
TH2F* h20  = nullptr;
TH2F* h21  = nullptr;
TH2F* h22  = nullptr;
TH2F* h23  = nullptr;

TH1F* th22 = nullptr;
TH1F* th23 = nullptr;

TH2F* th24 = nullptr;
TH2F* th25a= nullptr;
TH2F* th25 = nullptr;
TH2F* th26 = nullptr;
TH1F* th27 = nullptr;
TH1F* th28a= nullptr;
TH1F* th28 = nullptr;
TH1F* th29 = nullptr;

TH2F* h24  = nullptr;
TH2F* h25a = nullptr;
TH2F* h25  = nullptr;
TH2F* h26  = nullptr;
TH2F* h_24 = nullptr;
TH2F* h_25a= nullptr;
TH2F* h_25 = nullptr;
TH2F* h_26 = nullptr;
TH1F* h27  = nullptr;
TH1F* h28a = nullptr;
TH1F* h28  = nullptr;
TH1F* h29  = nullptr;
TH2F* h_27 = nullptr;
TH2F* h_28a= nullptr;
TH2F* h_28 = nullptr;
TH2F* h_29 = nullptr;

TH2F* h30  = nullptr;
TH2F* h31  = nullptr;
TH2F* h32  = nullptr;
TH2F* h33  = nullptr;
TH2F* h34  = nullptr;
TH2F* h35  = nullptr;

TH2F* h36 = nullptr;
TH2F* h37  = nullptr;
/*TH2F* h38  = nullptr;
TH2F* h39  = nullptr;
TH2F* h40  = nullptr;
TH2F* h41  = nullptr;
*/
TH2F* th36 = nullptr;
TH2F* th37 = nullptr;
TH2F* th38 = nullptr;
TH2F* th39 = nullptr;
TH2F* th40 = nullptr;
TH2F* th41 = nullptr;

TH1F* h42  = nullptr;
TH1F* h43  = nullptr;
TH1F* h44  = nullptr;

TH2F* h45  = nullptr;
TH2F* h46  = nullptr;
TH2F* h47  = nullptr;
TH2F* h48  = nullptr;
TH2F* h49  = nullptr;
TH2F* h50  = nullptr;
TH2F* h51  = nullptr;
TH2F* h52  = nullptr;
TH2F* h53  = nullptr;

TH2F* h54  = nullptr;
TH2F* h55  = nullptr;
TH2F* h56  = nullptr;
TH2F* h57  = nullptr;
TH2F* h58  = nullptr;
TH2F* h59  = nullptr;
TH2F* h60  = nullptr;
TH2F* h61  = nullptr;
TH2F* h62  = nullptr;
//! dca -> e,mu,pi for fakes,truth,rec tracks and for before and after kappa cut
TH1F* h63 = nullptr;
//TH1F* h64 = nullptr;
//TH1F* h65 = nullptr;
TH1F* h66  = nullptr;
TH1F* h67  = nullptr;
TH1F* h68  = nullptr;
TH1F* h69  = nullptr;
TH1F* h70  = nullptr;
TH1F* h71  = nullptr;
TH1F* h72  = nullptr;
//TH1F* h73 = nullptr;
//TH1F* h74 = nullptr;
TH1F* h75  = nullptr;
TH1F* h76  = nullptr;
TH1F* h77  = nullptr;
TH1F* h78  = nullptr;
TH1F* h79  = nullptr;
TH1F* h80  = nullptr;
//! dz2 -> e,mu,pi for fakes,truth,rec tracks and for before and after kappa cut
TH1F* h81  = nullptr;
//TH1F* h82 = nullptr;
//TH1F* h83 = nullptr;
TH1F* h84  = nullptr;
TH1F* h85  = nullptr;
TH1F* h86  = nullptr;
TH1F* h87  = nullptr;
TH1F* h88  = nullptr;
TH1F* h89  = nullptr;
TH1F* h90  = nullptr;
//TH1F* h91 = nullptr;
//TH1F* h92 = nullptr;
TH1F* h93  = nullptr;
TH1F* h94  = nullptr;
TH1F* h95  = nullptr;
TH1F* h96  = nullptr;
TH1F* h97  = nullptr;
TH1F* h98  = nullptr;
//! dkappa -> e,mu,pi for fakes,truth,rec tracks and for before and after kappa cut
TH1F* h99  = nullptr;
//TH1F* h100 = nullptr;
//TH1F* h101 = nullptr;
TH1F* h102 = nullptr;
TH1F* h103 = nullptr;
TH1F* h104 = nullptr;
TH1F* h105 = nullptr;
TH1F* h106 = nullptr;
TH1F* h107 = nullptr;
TH1F* h108 = nullptr;
//TH1F* h109 = nullptr;
//TH1F* h110 = nullptr;
TH1F* h111 = nullptr;
TH1F* h112 = nullptr;
TH1F* h113 = nullptr;
TH1F* h114 = nullptr;
TH1F* h115 = nullptr;
TH1F* h116 = nullptr;

TH1F* h117 = nullptr;
TH1F* h118 = nullptr;
TH1F* h119 = nullptr;
	              
TH2F* h120 = nullptr;
TH2F* h121 = nullptr;
TH2F* h122 = nullptr;
TH2F* h123 = nullptr;
TH2F* h124 = nullptr;
TH2F* h125 = nullptr;
TH2F* h126 = nullptr;
TH2F* h127 = nullptr;
TH2F* h128 = nullptr;
TH2F* h129 = nullptr;
TH2F* h130 = nullptr;
TH2F* h131 = nullptr;
	              
TH1F* h132 = nullptr;
TH1F* h133 = nullptr;
TH1F* h134 = nullptr;
TH1F* h135 = nullptr;
TH1F* h136 = nullptr;
TH1F* h137 = nullptr;
TH1F* h138 = nullptr;
TH1F* h139 = nullptr;
	              
TH2F* h140 = nullptr;
TH2F* h141 = nullptr;
TH2F* h142 = nullptr;
TH2F* h143 = nullptr;
TH2F* h144 = nullptr;
TH2F* h145 = nullptr;
TH2F* h146 = nullptr;
TH2F* h147 = nullptr;

TH1* h_num_vs_etaPU = nullptr;
TH1* h_den_vs_etaPU = nullptr;

TH1* h_num_vs_ptPU = nullptr;
TH1* h_den_vs_ptPU = nullptr;
		
TH1* h_num_vs_eta_ = nullptr;
TH1* h_den_vs_eta_ = nullptr;

TH1* h_num_vs_pt_ = nullptr;
TH1* h_den_vs_pt_ = nullptr;

TH1* h_num_vs_eta_l = nullptr;
TH1* h_den_vs_eta_l = nullptr;

TH1* h_num_vs_pt_l = nullptr;
TH1* h_den_vs_pt_l = nullptr;


TH1* h_num_vs_eta_m = nullptr;
TH1* h_den_vs_eta_m = nullptr;

TH1* h_num_vs_pt_m = nullptr;
TH1* h_den_vs_pt_m = nullptr;

TH1* h_num_vs_eta_t = nullptr;
TH1* h_den_vs_eta_t = nullptr;

TH1* h_num_vs_pt_t = nullptr;
TH1* h_den_vs_pt_t = nullptr;
