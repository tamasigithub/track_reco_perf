////******* macro calculating the purity of the reconstructed tracks and contains all the relevant cuts *********//////
/// p = #reconstructed(cut + matched)/#reconstructed(cut)
/// here cut is applied on the reconstructed parameters both in the numerator and the denominator

#include <iostream>
#include "TROOT.h"
#include "TFile.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TPostScript.h"
#include "TCut.h"
#include "TMath.h"
#include "TChain.h"
#include "TH1.h"
#include "TLegend.h"
#include <fstream>
#include <string>
#include <math.h>
//! kappa cut based on hit uncertainty and MS formula
//http://tkar.web.cern.ch/tkar/TTT/cuts_2.pdf
//FCC setup 
// 20mm
// hit_c:5e-09
// MS_c:0.00642222
// 30mm
//hit_c:9.87654e-10
//MS_c:0.00285432
// 40mm
// hit_c:3.125e-10
// MS_c:0.00160556
// 50mm
// hit_c:1.28e-10
// MS_c:0.00102756
//ATLAS setup
//hit_c:7.8125e-09
//MS_c:0.0192667

//const char* out_path = "/media/tamasi/DriveT1/tamasi/Desktop/PHD/work/rec_data/Mar102k19/minBias/plots/optimisation";
const char* out_path = "/media/tamasi/DriveT1/tamasi/Desktop/PHD/talks_preps/ctd2k19/plots/optimisation";
//! DEFINE CUTS for numerator and denominator
//! 20mm
/*TCut num_select    = "Tid>0  && Pt_n > 2000  && abs(Z013) < 100 && abs(Eta13) < 1.6 && abs(Phi13)<0.014 && abs(Z13)<120";
TCut den_select    = "Tid>-2 && Pt_n > 2000  && abs(Z013) < 100 && abs(Eta13) < 1.6 && abs(Phi13)<0.014 && abs(Z13)<120";
//! 
TCut phiBarrel	= "abs(Phi13)< 0.014";
TCut zBarrel	= "abs(Z13)<120";
TCut maxdphi2	= "abs(dphi2)<1.0e-4";
TCut maxdz2	= "abs(dz2)<0.17*(sin(Theta13)^(-1.1))";
const float dz2_exp   = -1.1;
const float dz2_const = 0.17;
//! 
TCut kapcut_l =  "abs(kappa-kap013)/sqrt(5e-9 + 0.00642222 * (1/sin(Theta13)) * kap013^2 ) < 5 ";
TCut kapcut   =  "abs(kappa-kap013)/sqrt(5e-9 + 0.00642222 * (1/sin(Theta13)) * kap013^2 ) < 4 ";
TCut kapcut_t =  "abs(kappa-kap013)/sqrt(5e-9 + 0.00642222 * (1/sin(Theta13)) * kap013^2 ) < 3 ";
*/
//! 30mm
/*TCut num_select    = "Tid>0  && Pt_n > 2000  && abs(Z013) < 100 && abs(Eta13) < 1.6 && abs(Phi13)<0.02 && abs(Z13)<160";
TCut den_select    = "Tid>-2 && Pt_n > 2000  && abs(Z013) < 100 && abs(Eta13) < 1.6 && abs(Phi13)<0.02 && abs(Z13)<160";
//! 
TCut phiBarrel	= "abs(Phi13)< 0.02";
TCut zBarrel	= "abs(Z13)<160";
TCut maxdphi2	= "abs(dphi2)<1.6e-4";
TCut maxdz2	= "abs(dz2)<0.17*(sin(Theta13)^(-1.25))";
const float dz2_exp   = -1.25;
const float dz2_const = 0.17;
//! 
TCut kapcut_l =  "abs(kappa-kap013)/sqrt(9.87654e-10 + 0.00285432 * (1/sin(Theta13)) * kap013^2 ) < 5 ";
TCut kapcut   =  "abs(kappa-kap013)/sqrt(9.87654e-10 + 0.00285432 * (1/sin(Theta13)) * kap013^2 ) < 4 ";
TCut kapcut_t =  "abs(kappa-kap013)/sqrt(9.87654e-10 + 0.00285432 * (1/sin(Theta13)) * kap013^2 ) < 3 ";*/
//! 40mm
/*TCut num_select    = "Tid>0  && Pt_n > 2000  && abs(Z013) < 100 && abs(Eta13) < 1.6 && abs(Phi13)<0.026 && abs(Z13)<210";
TCut den_select    = "Tid>-2 && Pt_n > 2000  && abs(Z013) < 100 && abs(Eta13) < 1.6 && abs(Phi13)<0.026 && abs(Z13)<210";
//! 
TCut phiBarrel	= "abs(Phi13)< 0.026";
TCut zBarrel	= "abs(Z13)<210";
TCut maxdphi2	= "abs(dphi2)<2.0e-4";
TCut maxdz2	= "abs(dz2)<0.17*(sin(Theta13)^(-1.35))";
const float dz2_exp   = -1.35;
const float dz2_const = 0.17;
//! 
TCut kapcut_l =  "abs(kappa-kap013)/sqrt(3.125e-10 + 0.00160556 * (1/sin(Theta13)) * kap013^2 ) < 5 ";
TCut kapcut   =  "abs(kappa-kap013)/sqrt(3.125e-10 + 0.00160556 * (1/sin(Theta13)) * kap013^2 ) < 4 ";
TCut kapcut_t =  "abs(kappa-kap013)/sqrt(3.125e-10 + 0.00160556 * (1/sin(Theta13)) * kap013^2 ) < 3 ";*/
//! 50mm
TCut num_select    = "Tid>0  && Pt_n > 2000  && abs(Z013) < 100 && abs(Eta13) < 1.6 && abs(Phi13)<0.032 && abs(Z13)<260";
TCut den_select    = "Tid>-2 && Pt_n > 2000  && abs(Z013) < 100 && abs(Eta13) < 1.6 && abs(Phi13)<0.032 && abs(Z13)<260";
//! 
TCut phiBarrel	= "abs(Phi13)< 0.032";
TCut zBarrel	= "abs(Z13)< 260";
TCut maxdphi2	= "abs(dphi2)<2.2e-4";
TCut maxdz2	= "abs(dz2)<0.17*(sin(Theta13)^(-1.5))";
const float dz2_exp   = -1.5;
const float dz2_const = 0.17;
//! 
TCut kapcut_l =  "abs(kappa-kap013)/sqrt(1.28e-10 + 0.00102756 * (1/sin(Theta13)) * kap013^2 ) < 5 ";
TCut kapcut   =  "abs(kappa-kap013)/sqrt(1.28e-10 + 0.00102756 * (1/sin(Theta13)) * kap013^2 ) < 4 ";
TCut kapcut_t =  "abs(kappa-kap013)/sqrt(1.28e-10 + 0.00102756 * (1/sin(Theta13)) * kap013^2 ) < 3 ";


TCut matched	= "Tid>0";
TCut fakes	= "Tid ==-1";
TCut minPt	= "Pt_n > 2e3 && abs(Eta13)<1.6";
TCut minPt_t	= "M_pt > 2e3 && abs(M_eta)<1.6";
TCut truth_m	= "M_pt < 20e3";
TCut recon_m	= "Pt_n < 20e3";
TCut pion	= "abs(M_pdg) == 211";
TCut muon	= "abs(M_pdg) == 13";
TCut electron	= "abs(M_pdg) == 11";
TCut noelectron = "abs(M_pdg) != 11";
TCut z0truthmax	= "abs(M_Vz)<100";//! depends on the luminous region along z
TCut z0recmax	= "abs(Z013)<100";
void newcontrol
(
	const char* output_file_name = "control_hh4b_PU1000_2_50mm",//f-few
	//const char* output_file_name = "control_hh4b_final2",//f-few
	const char* set = "C",
	const bool verbose = true
)
{
	//Open a list of root files and get reconstructed tree
	TChain rec("m_recTree");
	//! minbias
	//rec.Add("/media/tamasi/DriveT1/tamasi/Desktop/PHD/work/rec_data/Mar102k19/minBias/*000010_1.root");
	//rec.Add("/media/tamasi/DriveT1/tamasi/Desktop/PHD/work/rec_data/Mar102k19/minBias/*000011_1.root");
	TF1 *fdz2 = new TF1("fdz2", "[0]*(x)^[1]",0.4,1.05);
	fdz2->SetParameter(0,dz2_const);
	fdz2->SetParameter(1,dz2_exp);
	fdz2->SetLineColor(kBlack);
	TF1 *fdz2_ = new TF1("fdz2_", "[0]*(x)^[1]",0.4,1.05);
	fdz2_->SetParameter(0,-1*dz2_const);
	fdz2_->SetParameter(1,dz2_exp);
	fdz2_->SetLineColor(kBlack);
	//! 20mm
	//rec.Add("/media/tamasi/DriveT1/tamasi/Desktop/PHD/talks_preps/ctd2k19/data_files/hh4b/pileup_samples/rec-files/PU200*rec__002*_.root");
	//! 30mm
	//rec.Add("/media/tamasi/DriveT1/tamasi/Desktop/PHD/talks_preps/ctd2k19/data_files/hh4b/pileup_samples/rec-files/PU200*rec__003*_.root");
	//! 40mm
	//rec.Add("/media/tamasi/DriveT1/tamasi/Desktop/PHD/talks_preps/ctd2k19/data_files/hh4b/pileup_samples/rec-files/PU200*rec__004*_.root");
	//! 50mm
	//rec.Add("/media/tamasi/DriveT1/tamasi/Desktop/PHD/talks_preps/ctd2k19/data_files/hh4b/pileup_samples/rec-files/PU200hh4b_rec__005*_.root");

	//PU1000
	//! 20mm
	//rec.Add("/media/tamasi/DriveT1/tamasi/Desktop/PHD/talks_preps/ctd2k19/data_files/hh4b/pileup_samples/rec-files/PU1000hh4b_recOPTsig5_002*.root");
	//! 30mm
	//rec.Add("/media/tamasi/DriveT1/tamasi/Desktop/PHD/talks_preps/ctd2k19/data_files/hh4b/pileup_samples/rec-files/PU1000hh4b_recOPTsig5_003*.root");
	//! 40mm
	//rec.Add("/media/tamasi/DriveT1/tamasi/Desktop/PHD/talks_preps/ctd2k19/data_files/hh4b/pileup_samples/rec-files/PU1000hh4b_recOPTsig5_004*.root");
	//! 50mm
	rec.Add("/media/tamasi/DriveT1/tamasi/Desktop/PHD/talks_preps/ctd2k19/data_files/hh4b/pileup_samples/rec-files/PU1000hh4b_recOPTsig5_005*.root");


	//! number of points in the plots
	//int num_events = 225;//1e5;
	int num_events = rec.GetEntries();

	int etabin = 29;
        double etamin =-1.7, etamax = 1.7;
	std::cout<<"rec tree opened with " << rec.GetEntries() <<"entries\n";
	/// LOG BINS
	/// Variable bin width
	const int ptbins = 40;//no. of bins
	Double_t xbins[ptbins+1];//elements of this array are
	double dx = 5./ptbins;//5 -> implies max until 10^5
	double l10 = TMath::Log(10);
	for (int i = 0; i<=ptbins; i++)
	{
	//        std::cout<<"i,dx : " <<i << ", "<<dx <<std::endl;
	xbins[i] = TMath::Exp(l10*i*dx);
	//        std::cout<<"xbin[i] : " <<xbins[i] <<std::endl;
	}
	
	
	//! Books histograms
        TH1::SetDefaultSumw2(true);

	TH2F* h1 = new TH2F("h1","P_{t} Vs Phi_{13};Phi_{13};P_{t} [MeV/c]", 300,-0.04,0.04,300,1000,25e3); 	
	TH2F* h2 = new TH2F("h2","P_{t} Vs Phi_{13};Phi_{13};P_{t} [MeV/c]", 300,-0.04,0.04,300,1000,25e3); 	
	TH2F* h4 = new TH2F("h4","P_{t} Vs Phi_{13};Phi_{13};P_{t} [MeV/c]", 300,-0.04,0.04,300,1000,25e3); 	
	TH2F* h6 = new TH2F("h6","P_{t} Vs Phi_{13};Phi_{13};P_{t} [MeV/c]", 300,-0.04,0.04,300,1000,25e3); 	
	TH2F* h7 = new TH2F("h7","P_{trec} Vs P_{t};P_{t} [MeV/c];P_{trec}", 300,1000,25e3,300,1000,25e3); 	
	TH2F* h8 = new TH2F("h8","P_{trec} Vs P_{t};P_{t} [MeV/c];P_{trec}", 300,1000,25e3,300,1000,25e3); 	
	TH2F* h9 = new TH2F("h9","P_{trec} Vs P_{t};P_{t} [MeV/c];P_{trec}", 300,1000,25e3,300,1000,25e3); 	
	TH2F* h10 = new TH2F("h10","P_{trec} Vs P_{t};P_{t} [MeV/c];P_{trec}", 300,1000,25e3,300,1000,25e3);
 	
	TH2F* h11 = new TH2F("h11","P_{t} Vs Z_{13};Z_{13};P_{t} [MeV/c];", 300,-300,300,300,1000,25e3); 		
	
	TH2F* h12 = new TH2F("h12","Z_{013} Vs dphi_{2};dphi_{2};Z_{013} [mm]", 300,-0.001,0.001,300,-125,125); 	
	TH2F* h13 = new TH2F("h13","Z_{013} Vs dphi_{2};dphi_{2};Z_{013} [mm]", 300,-0.001,0.001,300,-125,125); 	
	TH2F* h14 = new TH2F("h14","M_{vz}  Vs dphi_{2};dphi_{2};M_{Vz}  [mm]", 300,-0.001,0.001,300,-125,125); 	
	TH1F* h14a= new TH1F("h14a","dphi_{2};dphi_{2}", 300,-5e-4,5e-4); 	
	TH2F* h15 = new TH2F("h15","Z_{013} Vs dz_{2};dz_{2} [mm];Z_{013} [mm]", 300,-2,2,300,-125,125); 	
	TH2F* h16 = new TH2F("h16","Z_{013} Vs dz_{2};dz_{2} [mm];Z_{013} [mm]", 300,-1,1,300,-125,125); 	
	TH2F* h17 = new TH2F("h17","M_{vz}  Vs dz_{2};dz_{2} [mm];M_{Vz}  [mm]", 300,-1,1,300,-125,125); 
	TH1F* h17a= new TH1F("h17a","dz_{2};dz_{2} [mm]", 300,-0.5,0.5); 
	 
	TH2F* h18 = new TH2F("h18","dphi_{2} Vs Theta_{13};Theta_{13};dphi_{2}", 300,0,3,300,-0.001,0.001);
	TH2F* h19 = new TH2F("h19","dphi_{2} Vs Theta_{13};Theta_{13};dphi_{2}", 300,0,3,300,-0.001,0.001); 	
	TH2F* h20 = new TH2F("h20","dphi_{2} Vs M_{theta};M_{theta};dphi_{2}", 300,0,3,300,-0.001,0.001); 	
	TH2F* h21 = new TH2F("h21","dz_{2} Vs Theta_{13};Theta_{13};dz_{2}", 300,0,3.0,300,-1,1);
	TH2F* h22 = new TH2F("h22","dz_{2} Vs Theta_{13};Theta_{13};dz_{2}", 300,0,3.0,300,-1,1);
	TH2F* h23 = new TH2F("h23","dz_{2} Vs M_{theta};M_{theta};dz_{2}", 300,0,3.0,300,-1,1);

	TH1F* th22 = new TH1F("th22","Theta_{13};Theta_{13}", 300,0,3.0);
	TH1F* th23 = new TH1F("th23","M_{theta};M_{theta}", 300,0,3.0);

	TH2F* th24 = new TH2F("th24","abs(dphi_{2}) Vs cos(Theta_{13});cos(Theta_{13});abs(dphi_{2})", 300,-1,1,300,0,6e-4); 	
	TH2F* th25a= new TH2F("th25a","abs(dphi_{2}) Vs cos(Theta_{13});cos(Theta_{13});abs(dphi_{2})", 300,-1,1,300,0,6e-4); 	
	TH2F* th25 = new TH2F("th25","abs(dphi_{2}) Vs cos(Theta_{13});cos(Theta_{13});abs(dphi_{2})", 300,-1,1,300,0,6e-4); 	
	TH2F* th26 = new TH2F("th26","abs(dphi_{2}) Vs cos(M_{theta});cos(M_{theta});abs(dphi_{2})", 300,-1,1,300,0,6e-4); 	
	TH2F* th27 = new TH2F("th27","dz_{2} Vs cos(Theta_{13});cos(Theta_{13});dz_{2}", 300,-1,1,300,-1,1); 	
	TH2F* th28a= new TH2F("th28a","dz_{2} Vs cos(Theta_{13});cos(Theta_{13});dz_{2}", 300,-1,1,300,-1,1); 	
	TH2F* th28 = new TH2F("th28","dz_{2} Vs cos(Theta_{13});cos(Theta_{13});dz_{2}", 300,-1,1,300,-1,1); 	
	TH2F* th29 = new TH2F("th29","dz_{2} Vs cos(M_{theta});cos(M_{theta});dz_{2}", 300,-1,1,300,-1,1);

	TH2F* h24 = new TH2F("h24","abs(dphi_{2}) Vs sin(Theta_{13});sin(Theta_{13});abs(dphi_{2})", 300,0.5,1.1,300,0,0.0006); 	
	TH2F* h25a= new TH2F("h25a","abs(dphi_{2}) Vs sin(Theta_{13});sin(Theta_{13});abs(dphi_{2})", 300,0.5,1.1,300,0,0.0006); 	
	TH2F* h25 = new TH2F("h25","abs(dphi_{2}) Vs sin(Theta_{13});sin(Theta_{13});abs(dphi_{2})", 300,0.5,1.1,300,0,0.0006); 	
	TH2F* h26 = new TH2F("h26","abs(dphi_{2}) Vs sin(M_{theta});sin(M_{theta});abs(dphi_{2})", 300,0.5,1.1,300,0,0.0006); 	
	TH2F* h_24 = new TH2F("h_24","abs(dphi_{2}) Vs sin(Theta_{13});sin(Theta_{13});abs(dphi_{2})", 300,0.5,1.1,300,0,0.0006); 	
	TH2F* h_25a= new TH2F("h_25a","abs(dphi_{2}) Vs sin(Theta_{13});sin(Theta_{13});abs(dphi_{2})", 300,0.5,1.1,300,0,0.0006); 	
	TH2F* h_25 = new TH2F("h_25","abs(dphi_{2}) Vs sin(Theta_{13});sin(Theta_{13});abs(dphi_{2})", 300,0.5,1.1,300,0,0.0006); 	
	TH2F* h_26 = new TH2F("h_26","abs(dphi_{2}) Vs sin(M_{theta});sin(M_{theta});abs(dphi_{2})", 300,0.5,1.1,300,0,0.0006); 	
	TH2F* h27 = new TH2F("h27","dz_{2} Vs sin(Theta_{13});sin(Theta_{13});dz_{2}", 300,0,1.1,300,-1,1); 	
	TH2F* h28a= new TH2F("h28a","dz_{2} Vs sin(Theta_{13});sin(Theta_{13});dz_{2}", 300,0,1.1,300,-1,1); 	
	TH2F* h28 = new TH2F("h28","dz_{2} Vs sin(Theta_{13});sin(Theta_{13});dz_{2}", 300,0,1.1,300,-1,1); 	
	TH2F* h29 = new TH2F("h29","dz_{2} Vs sin(M_{theta});sin(M_{theta});dz_{2}", 300,0,1.1,300,-1,1);
	TH2F* h_27 = new TH2F("h_27","dz_{2} Vs sin(Theta_{13});sin(Theta_{13});dz_{2}", 300,0,1.1,300,-1,1); 	
	TH2F* h_28a= new TH2F("h_28a","dz_{2} Vs sin(Theta_{13});sin(Theta_{13});dz_{2}", 300,0,1.1,300,-1,1); 	
	TH2F* h_28 = new TH2F("h_28","dz_{2} Vs sin(Theta_{13});sin(Theta_{13});dz_{2}", 300,0,1.1,300,-1,1); 	
	TH2F* h_29 = new TH2F("h_29","dz_{2} Vs sin(M_{theta});sin(M_{theta});dz_{2}", 300,0,1.1,300,-1,1);

	TH2F* h30 = new TH2F("h30","P_{t} Vs dphi_{2};dphi_{2};P_{t} [MeV/c]", 300,-6e-4,6e-4,300,1000,25e3); 	
	TH2F* h31 = new TH2F("h31","P_{t} Vs dphi_{2};dphi_{2};P_{t} [MeV/c]", 300,-6e-4,6e-4,300,1000,25e3); 	
	TH2F* h32 = new TH2F("h32","P_{t} Vs dphi_{2};dphi_{2};P_{t} [MeV/c]", 300,-6e-4,6e-4,300,1000,25e3); 	
	TH2F* h33 = new TH2F("h33","P_{t} Vs dz_{2};dz_{2};P_{t} [MeV/c]", 300,-1,1,300,1000,25e3); 	
	TH2F* h34 = new TH2F("h34","P_{t} Vs dz_{2};dz_{2};P_{t} [MeV/c]", 300,-1,1,300,1000,25e3); 	
	TH2F* h35 = new TH2F("h35","P_{t} Vs dz_{2};dz_{2};P_{t} [MeV/c]", 300,-1,1,300,1000,25e3);

	/*TH2F* h36 = new TH2F("h36","kappa013^{2} Vs dkappa;dkappa[mm^{-1}];kap_{013}^{2}[mm^{-2}]", 300,-0.7e-3,0.7e-3,300,0,2e-7);
	TH2F* h37 = new TH2F("h37","kappa013^{2} Vs dkappa;dkappa[mm^{-1}];kap_{013}^{2}[mm^{-2}]", 300,-0.7e-3,0.7e-3,300,0,2e-7);
	TH2F* h38 = new TH2F("h38","kappa013^{2} Vs dkappa;dkappa[mm^{-1}];kap_{013}^{2}[mm^{-2}]", 300,-0.7e-3,0.7e-3,300,0,2e-7);
	TH2F* h39 = new TH2F("h39","kappa013^{2} Vs dkappa;dkappa[mm^{-1}];kap_{013}^{2}[mm^{-2}]", 300,-0.7e-3,0.7e-3,300,0,2e-7);
	TH2F* h40 = new TH2F("h40","kappa013^{2} Vs dkappa;dkappa[mm^{-1}];kap_{013}^{2}[mm^{-2}]", 300,-0.7e-3,0.7e-3,300,0,2e-7);
	TH2F* h41 = new TH2F("h41","kappa013^{2} Vs dkappa;dkappa[mm^{-1}];kap_{013}^{2}[mm^{-2}]", 300,-0.7e-3,0.7e-3,300,0,2e-7);
	*/
	TH2F* th36 = new TH2F("th36","kappa013 Vs dkappa;dkappa[mm^{-1}];kap_{013}[mm^{-1}]", 300,-0.7e-3,0.7e-3,300,-8e-4,8e-4);
	TH2F* th37 = new TH2F("th37","kappa013 Vs dkappa;dkappa[mm^{-1}];kap_{013}[mm^{-1}]", 300,-0.7e-3,0.7e-3,300,-8e-4,8e-4);
	TH2F* th38 = new TH2F("th38","kappa013 Vs dkappa;dkappa[mm^{-1}];kap_{013}[mm^{-1}]", 300,-0.7e-3,0.7e-3,300,-8e-4,8e-4);
	TH2F* th39 = new TH2F("th39","kappa013 Vs dkappa;dkappa[mm^{-1}];kap_{013}[mm^{-1}]", 300,-0.7e-3,0.7e-3,300,-8e-4,8e-4);
	TH2F* th40 = new TH2F("th40","kappa013 Vs dkappa;dkappa[mm^{-1}];kap_{013}[mm^{-1}]", 300,-0.7e-3,0.7e-3,300,-8e-4,8e-4);
	TH2F* th41 = new TH2F("th41","kappa013 Vs dkappa;dkappa[mm^{-1}];kap_{013}[mm^{-1}]", 300,-0.7e-3,0.7e-3,300,-8e-4,8e-4);
	
	TH1F* h42 = new TH1F("h42","dca;dca [mm]", 300,-850,850);
	TH1F* h43 = new TH1F("h43","dca;dca [mm]", 300,-850,850);
	TH1F* h44 = new TH1F("h44","dca;dca [mm]", 300,-850,850);

	TH2F* h45 = new TH2F("h45","P_{t} Vs dca;dca [mm];P_{t} [MeV/c]", 300,-850,850,300,1000,25e3);
	TH2F* h46 = new TH2F("h46","P_{t} Vs dca;dca [mm];P_{t} [MeV/c]", 300,-850,850,300,1000,25e3);
	TH2F* h47 = new TH2F("h47","P_{t} Vs dca;dca [mm];P_{t} [MeV/c]", 300,-850,850,300,1000,25e3);
	TH2F* h48 = new TH2F("h48","P_{t} Vs dca;dca [mm];P_{t} [MeV/c]", 300,-850,850,300,1000,25e3);
	TH2F* h49 = new TH2F("h49","P_{t} Vs dca;dca [mm];P_{t} [MeV/c]", 300,-850,850,300,1000,25e3);
	TH2F* h50 = new TH2F("h50","P_{t} Vs dca;dca [mm];P_{t} [MeV/c]", 300,-850,850,300,1000,25e3);
	TH2F* h51 = new TH2F("h51","P_{t} Vs dca;dca [mm];P_{t} [MeV/c]", 300,-850,850,300,1000,25e3);
	TH2F* h52 = new TH2F("h52","P_{t} Vs dca;dca [mm];P_{t} [MeV/c]", 300,-850,850,300,1000,25e3);
	TH2F* h53 = new TH2F("h53","P_{t} Vs dca;dca [mm];P_{t} [MeV/c]", 300,-850,850,300,1000,25e3);
	
	TH2F* h54 = new TH2F("h54","Z_{0} Vs dca;dca [mm];Z_{0} [mm]", 300,-850,850,300,-100,100);
	TH2F* h55 = new TH2F("h55","Z_{0} Vs dca;dca [mm];Z_{0} [mm]", 300,-850,850,300,-100,100);
	TH2F* h56 = new TH2F("h56","Z_{0} Vs dca;dca [mm];Z_{0} [mm]", 300,-850,850,300,-100,100);
	TH2F* h57 = new TH2F("h57","Z_{0} Vs dca;dca [mm];Z_{0} [mm]", 300,-850,850,300,-100,100);
	TH2F* h58 = new TH2F("h58","Z_{0} Vs dca;dca [mm];Z_{0} [mm]", 300,-850,850,300,-100,100);
	TH2F* h59 = new TH2F("h59","Z_{0} Vs dca;dca [mm];Z_{0} [mm]", 300,-850,850,300,-100,100);
	TH2F* h60 = new TH2F("h60","Z_{0} Vs dca;dca [mm];Z_{0} [mm]", 300,-850,850,300,-100,100);
	TH2F* h61 = new TH2F("h61","Z_{0} Vs dca;dca [mm];Z_{0} [mm]", 300,-850,850,300,-100,100);
	TH2F* h62 = new TH2F("h62","Z_{0} Vs dca;dca [mm];Z_{0} [mm]", 300,-850,850,300,-100,100);
	//! dca -> e,mu,pi for fakes,truth,rec tracks and for before and after kappa cut
	TH1F* h63 = new TH1F("h63","dca;dca [mm]", 300,-850,850);
	//TH1F* h64 = new TH1F("h64","dca;dca [mm]", 300,-200,850);
	//TH1F* h65 = new TH1F("h65","dca;dca [mm]", 300,-200,850);
	TH1F* h66 = new TH1F("h66","dca;dca [mm]", 300,-850,850);
	TH1F* h67 = new TH1F("h67","dca;dca [mm]", 300,-850,850);
	TH1F* h68 = new TH1F("h68","dca;dca [mm]", 300,-850,850);
	TH1F* h69 = new TH1F("h69","dca;dca [mm]", 300,-850,850);
	TH1F* h70 = new TH1F("h70","dca;dca [mm]", 300,-850,850);
	TH1F* h71 = new TH1F("h71","dca;dca [mm]", 300,-850,850);
	TH1F* h72 = new TH1F("h72","dca;dca [mm]", 300,-850,850);
	//TH1F* h73 = new TH1F("h73","dca;dca [mm]", 300,-200,850);
	//TH1F* h74 = new TH1F("h74","dca;dca [mm]", 300,-200,850);
	TH1F* h75 = new TH1F("h75","dca;dca [mm]", 300,-850,850);
	TH1F* h76 = new TH1F("h76","dca;dca [mm]", 300,-850,850);
	TH1F* h77 = new TH1F("h77","dca;dca [mm]", 300,-850,850);
	TH1F* h78 = new TH1F("h78","dca;dca [mm]", 300,-850,850);
	TH1F* h79 = new TH1F("h79","dca;dca [mm]", 300,-850,850);
	TH1F* h80 = new TH1F("h80","dca;dca [mm]", 300,-850,850);
	//! dz2 -> e,mu,pi for fakes,truth,rec tracks and for before and after kappa cut
	TH1F* h81 = new TH1F("h81","dz_{2};dz_{2} [mm]", 300,-0.5,0.5);
	//TH1F* h82 = new TH1F("h82","dz_{2};dz_{2} [mm]", 300,-0.5,0.5);
	//TH1F* h83 = new TH1F("h83","dz_{2};dz_{2} [mm]", 300,-0.5,0.5);
	TH1F* h84 = new TH1F("h84","dz_{2};dz_{2} [mm]", 300,-0.5,0.5);
	TH1F* h85 = new TH1F("h85","dz_{2};dz_{2} [mm]", 300,-0.5,0.5);
	TH1F* h86 = new TH1F("h86","dz_{2};dz_{2} [mm]", 300,-0.5,0.5);
	TH1F* h87 = new TH1F("h87","dz_{2};dz_{2} [mm]", 300,-0.5,0.5);
	TH1F* h88 = new TH1F("h88","dz_{2};dz_{2} [mm]", 300,-0.5,0.5);
	TH1F* h89 = new TH1F("h89","dz_{2};dz_{2} [mm]", 300,-0.5,0.5);
	TH1F* h90 = new TH1F("h90","dz_{2};dz_{2} [mm]", 300,-0.5,0.5);
	//TH1F* h91 = new TH1F("h91","dz_{2};dz_{2} [mm]", 300,-0.5,0.5);
	//TH1F* h92 = new TH1F("h92","dz_{2};dz_{2} [mm]", 300,-0.5,0.5);
	TH1F* h93 = new TH1F("h93","dz_{2};dz_{2} [mm]", 300,-0.5,0.5);
	TH1F* h94 = new TH1F("h94","dz_{2};dz_{2} [mm]", 300,-0.5,0.5);
	TH1F* h95 = new TH1F("h95","dz_{2};dz_{2} [mm]", 300,-0.5,0.5);
	TH1F* h96 = new TH1F("h96","dz_{2};dz_{2} [mm]", 300,-0.5,0.5);
	TH1F* h97 = new TH1F("h97","dz_{2};dz_{2} [mm]", 300,-0.5,0.5);
	TH1F* h98 = new TH1F("h98","dz_{2};dz_{2} [mm]", 300,-0.5,0.5);
	//! dkappa -> e,mu,pi for fakes,truth,rec tracks and for before and after kappa cut
	TH1F* h99 = new TH1F("h99","d#kappa;d#kappa [mm^{-1}]", 300,-9e-3,9e-3);
	//TH1F* h100= new TH1F("h100","d#kappa;d#kappa [mm^{-1}]", 300,-0.7e-3,0.7e-3);
	//TH1F* h101= new TH1F("h101","d#kappa;d#kappa [mm^{-1}]", 300,-0.7e-3,0.7e-3);
	TH1F* h102= new TH1F("h102","d#kappa;d#kappa [mm^{-1}]", 300,-0.7e-3,0.7e-3);
	TH1F* h103= new TH1F("h103","d#kappa;d#kappa [mm^{-1}]", 300,-0.7e-3,0.7e-3);
	TH1F* h104= new TH1F("h104","d#kappa;d#kappa [mm^{-1}]", 300,-0.7e-3,0.7e-3);
	TH1F* h105= new TH1F("h105","d#kappa;d#kappa [mm^{-1}]", 300,-0.7e-3,0.7e-3);
	TH1F* h106= new TH1F("h106","d#kappa;d#kappa [mm^{-1}]", 300,-0.7e-3,0.7e-3);
	TH1F* h107= new TH1F("h107","d#kappa;d#kappa [mm^{-1}]", 300,-0.7e-3,0.7e-3);
	TH1F* h108= new TH1F("h108","d#kappa;d#kappa [mm^{-1}]", 300,-0.7e-3,0.7e-3);
	//TH1F* h109= new TH1F("h109","d#kappa;d#kappa [mm^{-1}]", 300,-0.7e-3,0.7e-3);
	//TH1F* h110= new TH1F("h110","d#kappa;d#kappa [mm^{-1}]", 300,-0.7e-3,0.7e-3);
	TH1F* h111= new TH1F("h111","d#kappa;d#kappa [mm^{-1}]", 300,-0.7e-3,0.7e-3);
	TH1F* h112= new TH1F("h112","d#kappa;d#kappa [mm^{-1}]", 300,-0.7e-3,0.7e-3);
	TH1F* h113= new TH1F("h113","d#kappa;d#kappa [mm^{-1}]", 300,-0.7e-3,0.7e-3);
	TH1F* h114= new TH1F("h114","d#kappa;d#kappa [mm^{-1}]", 300,-0.7e-3,0.7e-3);
	TH1F* h115= new TH1F("h115","d#kappa;d#kappa [mm^{-1}]", 300,-0.7e-3,0.7e-3);
	TH1F* h116= new TH1F("h116","d#kappa;d#kappa [mm^{-1}]", 300,-0.7e-3,0.7e-3);

	TH1F* h117= new TH1F("h117","kappa truth; #kappa_{truth} [mm^{-1}]", 300,-5e-3,5e-3);
	TH1F* h118= new TH1F("h118","kappa rec with bml constraint; #kappa_{013} [mm^{-1}]", 300,-5e-3,5e-3);
	TH1F* h119= new TH1F("h119","kappa rec w/o bml constraint; #kappa_{123} [mm^{-1}]", 300,-0.7e-2,0.7e-2);
                             
	TH2F* h120= new TH2F("h120","#kappa_{013} Vs #kappa_{truth}; #kappa_{truth} [mm^{-1}]; #kappa_{013} [mm^{-1}]", 300,-0.8e-3,0.8e-3, 300,-0.8e-3,0.8e-3);
	TH2F* h121= new TH2F("h121","#kappa_{013} Vs #kappa_{truth}; #kappa_{truth} [mm^{-1}]; #kappa_{013} [mm^{-1}]", 300,-0.8e-3,0.8e-3, 300,-0.8e-3,0.8e-3);
	TH2F* h122= new TH2F("h122","#kappa_{013} Vs #kappa_{truth}; #kappa_{truth} [mm^{-1}]; #kappa_{013} [mm^{-1}]", 300,-0.8e-3,0.8e-3, 300,-0.8e-3,0.8e-3);
	TH2F* h123= new TH2F("h123","#kappa_{013} Vs #kappa_{truth}; #kappa_{truth} [mm^{-1}]; #kappa_{013} [mm^{-1}]", 300,-0.8e-3,0.8e-3, 300,-0.8e-3,0.8e-3);
	TH2F* h124= new TH2F("h124","#kappa_{123} Vs #kappa_{truth}; #kappa_{truth} [mm^{-1}]; #kappa_{123} [mm^{-1}]", 300,-0.8e-3,0.8e-3, 300,-0.01,0.01);
	TH2F* h125= new TH2F("h125","#kappa_{123} Vs #kappa_{truth}; #kappa_{truth} [mm^{-1}]; #kappa_{123} [mm^{-1}]", 300,-0.8e-3,0.8e-3, 300,-0.01,0.01);
	TH2F* h126= new TH2F("h126","#kappa_{123} Vs #kappa_{truth}; #kappa_{truth} [mm^{-1}]; #kappa_{123} [mm^{-1}]", 300,-0.8e-3,0.8e-3, 300,-0.01,0.01);
	TH2F* h127= new TH2F("h127","#kappa_{123} Vs #kappa_{truth}; #kappa_{truth} [mm^{-1}]; #kappa_{123} [mm^{-1}]", 300,-0.8e-3,0.8e-3, 300,-0.01,0.01);
	TH2F* h128= new TH2F("h128","#kappa_{013} Vs #kappa_{123}; #kappa_{123} [mm^{-1}]; #kappa_{013}", 300,-0.01,0.01, 300,-0.8e-3,0.8e-3);
	TH2F* h129= new TH2F("h129","#kappa_{013} Vs #kappa_{123}; #kappa_{123} [mm^{-1}]; #kappa_{013}", 300,-0.01,0.01, 300,-0.8e-3,0.8e-3);
	TH2F* h130= new TH2F("h130","#kappa_{013} Vs #kappa_{123}; #kappa_{123} [mm^{-1}]; #kappa_{013}", 300,-0.01,0.01, 300,-0.8e-3,0.8e-3);
	TH2F* h131= new TH2F("h131","#kappa_{013} Vs #kappa_{123}; #kappa_{123} [mm^{-1}]; #kappa_{013}", 300,-0.01,0.01, 300,-0.8e-3,0.8e-3);
                             
	TH1F* h132= new TH1F("h132","#kappa_{013}/#kappa_{truth}; #kappa_{013}/#kappa_{truth}", 300,-0.5,1.5);
	TH1F* h133= new TH1F("h133","#kappa_{013}/#kappa_{truth}; #kappa_{013}/#kappa_{truth}", 300,-0.5,1.5);
	TH1F* h134= new TH1F("h134","#kappa_{013}/#kappa_{truth}; #kappa_{013}/#kappa_{truth}", 300,-0.5,1.5);
	TH1F* h135= new TH1F("h135","#kappa_{013}/#kappa_{truth}; #kappa_{013}/#kappa_{truth}", 300,-0.5,1.5);
	TH1F* h136= new TH1F("h136","#kappa_{123}/#kappa_{truth}; #kappa_{123}/#kappa_{truht}", 300,-20,20);
	TH1F* h137= new TH1F("h137","#kappa_{123}/#kappa_{truth}; #kappa_{123}/#kappa_{truht}", 300,-20,20);
	TH1F* h138= new TH1F("h138","#kappa_{123}/#kappa_{truth}; #kappa_{123}/#kappa_{truht}", 300,-20,20);
	TH1F* h139= new TH1F("h139","#kappa_{123}/#kappa_{truth}; #kappa_{123}/#kappa_{truht}", 300,-20,20);
                             
	TH2F* h140= new TH2F("h140","d#kappa Vs r; r [mm]; d#kappa [mm^{-1}]", 300,0,850, 300,-0.5e-3,0.5e-3);
	TH2F* h141= new TH2F("h141","d#kappa Vs r; r [mm]; d#kappa [mm^{-1}]", 300,0,850, 300,-0.5e-3,0.5e-3);
	TH2F* h142= new TH2F("h142","d#kappa Vs r; r [mm]; d#kappa [mm^{-1}]", 300,0,850, 300,-0.5e-3,0.5e-3);
	TH2F* h143= new TH2F("h143","d#kappa Vs r; r [mm]; d#kappa [mm^{-1}]", 300,0,850, 300,-0.5e-3,0.5e-3);
	TH2F* h144= new TH2F("h144","#kappa_{013}/#kappa_{truth} Vs r; r [mm]; #kappa_{013}/#kappa_{truht}", 300,0,850, 300,-0.5,1.5);
	TH2F* h145= new TH2F("h145","#kappa_{013}/#kappa_{truth} Vs r; r [mm]; #kappa_{013}/#kappa_{truht}", 300,0,850, 300,-0.5,1.5);
	TH2F* h146= new TH2F("h146","#kappa_{013}/#kappa_{truth} Vs r; r [mm]; #kappa_{013}/#kappa_{truht}", 300,0,850, 300,-0.5,1.5);
	TH2F* h147= new TH2F("h147","#kappa_{013}/#kappa_{truth} Vs r; r [mm]; #kappa_{013}/#kappa_{truht}", 300,0,850, 300,-0.5,1.5);

	TH1* h_num_vs_etaPU = new TH1F("h_num_vs_etaPU", "Numerator Count vs #eta;#eta;Numerator Count"    , etabin, etamin, etamax);
        TH1* h_den_vs_etaPU = new TH1F("h_den_vs_etaPU", "Denominator Count vs #eta;#eta;Denominator Count", etabin, etamin, etamax);

	TH1* h_num_vs_ptPU = new TH1F("h_num_vs_ptPU", "Numerator Count vs P_{t};P_{t} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_ptPU = new TH1F("h_den_vs_ptPU", "Denominator Count vs P_{t};P_{t} [MeV/c];Denominator Count", ptbins, xbins);
			
	TH1* h_num_vs_eta_ = new TH1F("h_num_vs_eta_", "Numerator Count vs #eta;#eta;Numerator Count"    , etabin, etamin, etamax);
        TH1* h_den_vs_eta_ = new TH1F("h_den_vs_eta_", "Denominator Count vs #eta;#eta;Denominator Count", etabin, etamin, etamax);

	TH1* h_num_vs_pt_ = new TH1F("h_num_vs_pt_", "Numerator Count vs P_{t};P_{t} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_pt_ = new TH1F("h_den_vs_pt_", "Denominator Count vs P_{t};P_{t} [MeV/c];Denominator Count", ptbins, xbins);
	
	TH1* h_num_vs_eta_l = new TH1F("h_num_vs_eta_l", "Numerator Count vs #eta;#eta;Numerator Count"    , etabin, etamin, etamax);
        TH1* h_den_vs_eta_l = new TH1F("h_den_vs_eta_l", "Denominator Count vs #eta;#eta;Denominator Count", etabin, etamin, etamax);

	TH1* h_num_vs_pt_l = new TH1F("h_num_vs_pt_l", "Numerator Count vs P_{t};P_{t} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_pt_l = new TH1F("h_den_vs_pt_l", "Denominator Count vs P_{t};P_{t} [MeV/c];Denominator Count", ptbins, xbins);
	

	TH1* h_num_vs_eta_m = new TH1F("h_num_vs_eta_m", "Numerator Count vs #eta;#eta;Numerator Count"    , etabin, etamin, etamax);
        TH1* h_den_vs_eta_m = new TH1F("h_den_vs_eta_m", "Denominator Count vs #eta;#eta;Denominator Count", etabin, etamin, etamax);

	TH1* h_num_vs_pt_m = new TH1F("h_num_vs_pt_m", "Numerator Count vs P_{t};P_{t} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_pt_m = new TH1F("h_den_vs_pt_m", "Denominator Count vs P_{t};P_{t} [MeV/c];Denominator Count", ptbins, xbins);
	
	TH1* h_num_vs_eta_t = new TH1F("h_num_vs_eta_t", "Numerator Count vs #eta;#eta;Numerator Count"    , etabin, etamin, etamax);
        TH1* h_den_vs_eta_t = new TH1F("h_den_vs_eta_t", "Denominator Count vs #eta;#eta;Denominator Count", etabin, etamin, etamax);

	TH1* h_num_vs_pt_t = new TH1F("h_num_vs_pt_t", "Numerator Count vs P_{t};P_{t} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_pt_t = new TH1F("h_den_vs_pt_t", "Denominator Count vs P_{t};P_{t} [MeV/c];Denominator Count", ptbins, xbins);
	


	h1->SetMarkerColor(kGreen);
	h2->SetMarkerColor(kBlack);
	h4->SetMarkerColor(kBlue);
	h6->SetMarkerColor(kRed);
	
	h7->SetMarkerColor(kBlack);
	h8->SetMarkerColor(kGreen);
	h9->SetMarkerColor(kBlue);
	h10->SetMarkerColor(kRed);

	h12->SetMarkerColor(kRed);
	h13->SetMarkerColor(kBlue);
	h14->SetMarkerColor(kGreen);

	h15->SetMarkerColor(kRed);
        h16->SetMarkerColor(kBlue);
        h17->SetMarkerColor(kGreen);

	h18->SetMarkerColor(kRed);
        h19->SetMarkerColor(kBlue);
        h20->SetMarkerColor(kGreen);

	h21->SetMarkerColor(kRed);
        h22->SetMarkerColor(kBlue);
        h23->SetMarkerColor(kGreen);
 		
	h24->SetMarkerColor(kRed);
        h25->SetMarkerColor(kBlue);
        h25a->SetMarkerColor(kCyan);
        h26->SetMarkerColor(kGreen);

	h27->SetMarkerColor(kRed);
        h28->SetMarkerColor(kBlue);
        h28a->SetMarkerColor(kCyan);
        h29->SetMarkerColor(kGreen);

	h_24->SetMarkerColor(kRed);
        h_25->SetMarkerColor(kBlue);
        h_25a->SetMarkerColor(kCyan);
        h_26->SetMarkerColor(kGreen);

	h_27->SetMarkerColor(kRed);
        h_28->SetMarkerColor(kBlue);
        h_28a->SetMarkerColor(kCyan);
        h_29->SetMarkerColor(kGreen);

        th22->SetMarkerColor(kBlue);
        th23->SetMarkerColor(kGreen);
	
	th24->SetMarkerColor(kRed);
        th25->SetMarkerColor(kBlue);
        th25a->SetMarkerColor(kCyan);
        th26->SetMarkerColor(kGreen);

	th27->SetMarkerColor(kRed);
        th28->SetMarkerColor(kBlue);
        th28a->SetMarkerColor(kCyan);
        th29->SetMarkerColor(kGreen);

	h30->SetMarkerColor(kRed);
        h31->SetMarkerColor(kBlue);
        h32->SetMarkerColor(kGreen);	

	h33->SetMarkerColor(kRed);
        h34->SetMarkerColor(kBlue);
        h35->SetMarkerColor(kGreen);

	/*h36->SetMarkerColor(kBlack);
        h37->SetMarkerColor(kGreen);
        h38->SetMarkerColor(kBlue);
	h39->SetMarkerColor(kCyan);
	h40->SetMarkerColor(kRed);
	h41->SetMarkerColor(kGreen+3);
       */
	th36->SetMarkerColor(kGreen+3);
        th37->SetMarkerColor(kBlack);
        th38->SetMarkerColor(kCyan);
	th39->SetMarkerColor(kRed-9);
	th40->SetMarkerColor(kRed);
	th41->SetMarkerColor(kRed+2);
	
	h42->SetMarkerColor(kRed);
	h43->SetMarkerColor(kBlue);
	h44->SetMarkerColor(kGreen+3);

	h45->SetMarkerColor(kRed);
	h46->SetMarkerColor(kBlack);
	h47->SetMarkerColor(kGreen);
	h48->SetMarkerColor(kBlue);
	h49->SetMarkerColor(kRed);
	h50->SetMarkerColor(kGreen+3);
	h51->SetMarkerColor(kGreen);
	h52->SetMarkerColor(kBlue);
	h53->SetMarkerColor(kRed);

	h54->SetMarkerColor(kRed);
	h55->SetMarkerColor(kBlack);
	h56->SetMarkerColor(kGreen);
	h57->SetMarkerColor(kBlue);
	h58->SetMarkerColor(kRed);
	h59->SetMarkerColor(kGreen+3);
	h60->SetMarkerColor(kGreen);
	h61->SetMarkerColor(kBlue);
	h62->SetMarkerColor(kRed);

	h63->SetMarkerColor(kRed);
	//h64->SetMarkerColor(kBlue);
	//h65->SetMarkerColor(kRed);
	h66->SetMarkerColor(kGreen);
	h67->SetMarkerColor(kBlue);
	h68->SetMarkerColor(kRed);
	h69->SetMarkerColor(kGreen);
	h70->SetMarkerColor(kBlue);
	h71->SetMarkerColor(kRed);
	h72->SetMarkerColor(kRed+2);
	//h73->SetMarkerColor(kBlue);
	//h74->SetMarkerColor(kRed);
	h75->SetMarkerColor(kGreen);
	h76->SetMarkerColor(kBlue);
	h77->SetMarkerColor(kRed);
	h78->SetMarkerColor(kGreen);
	h79->SetMarkerColor(kBlue);
	h80->SetMarkerColor(kRed);
	h81->SetMarkerColor(kRed);
	//h82->SetMarkerColor(kBlue);
	//h83->SetMarkerColor(kRed);
	h84->SetMarkerColor(kGreen);
	h85->SetMarkerColor(kBlue);
	h86->SetMarkerColor(kRed);
	h87->SetMarkerColor(kGreen);
	h88->SetMarkerColor(kBlue);
	h89->SetMarkerColor(kRed);
	h90->SetMarkerColor(kRed+2);
	//h91->SetMarkerColor(kBlue);
	//h92->SetMarkerColor(kRed);
	h93->SetMarkerColor(kGreen);
	h94->SetMarkerColor(kBlue);
	h95->SetMarkerColor(kRed);
	h96->SetMarkerColor(kGreen);
	h97->SetMarkerColor(kBlue);
	h98->SetMarkerColor(kRed);
	h99->SetMarkerColor(kRed);
	//h100->SetMarkerColor(kBlue);
	//h101->SetMarkerColor(kRed);
	h102->SetMarkerColor(kGreen);
	h103->SetMarkerColor(kBlue);
	h104->SetMarkerColor(kRed);
	h105->SetMarkerColor(kGreen);
	h106->SetMarkerColor(kBlue);
	h107->SetMarkerColor(kRed);
	h108->SetMarkerColor(kRed+2);
	//h109->SetMarkerColor(kBlue);
	//h110->SetMarkerColor(kRed);
	h111->SetMarkerColor(kGreen);
	h112->SetMarkerColor(kBlue);
	h113->SetMarkerColor(kRed);
	h114->SetMarkerColor(kGreen);
	h115->SetMarkerColor(kBlue);
	h116->SetMarkerColor(kRed);
	
	h120->SetMarkerColor(kBlack);
	h121->SetMarkerColor(kGreen);
	h122->SetMarkerColor(kBlue);
	h123->SetMarkerColor(kRed);
	h124->SetMarkerColor(kBlack);
	h125->SetMarkerColor(kGreen);
	h126->SetMarkerColor(kBlue);
	h127->SetMarkerColor(kRed);
	h128->SetMarkerColor(kBlack);
	h129->SetMarkerColor(kGreen);
	h130->SetMarkerColor(kBlue);
	h131->SetMarkerColor(kRed);
	h132->SetMarkerColor(kBlack);
	h133->SetMarkerColor(kGreen);
	h134->SetMarkerColor(kBlue);
	h135->SetMarkerColor(kRed);
	h136->SetMarkerColor(kBlack);
	h137->SetMarkerColor(kGreen);
	h138->SetMarkerColor(kBlue);
	h139->SetMarkerColor(kRed);
	h140->SetMarkerColor(kBlack);
	h141->SetMarkerColor(kGreen);
	h142->SetMarkerColor(kBlue);
	h143->SetMarkerColor(kRed);
	h144->SetMarkerColor(kBlack);
	h145->SetMarkerColor(kGreen);
	h146->SetMarkerColor(kBlue);
	h147->SetMarkerColor(kRed);
	
	h1->SetLineColor(kGreen);
	h2->SetLineColor(kBlack);
	h4->SetLineColor(kBlue);
	h6->SetLineColor(kRed);
	
	h7->SetLineColor(kBlack);
	h8->SetLineColor(kGreen);
	h9->SetLineColor(kBlue);
	h10->SetLineColor(kRed);

	h12->SetLineColor(kRed);
	h13->SetLineColor(kBlue);
	h14->SetLineColor(kGreen);

	h15->SetLineColor(kRed);
        h16->SetLineColor(kBlue);
        h17->SetLineColor(kGreen);

	h18->SetLineColor(kRed);
        h19->SetLineColor(kBlue);
        h20->SetLineColor(kGreen);

	h21->SetLineColor(kRed);
        h22->SetLineColor(kBlue);
        h23->SetLineColor(kGreen);
	
	h24->SetLineColor(kRed);
        h25->SetLineColor(kBlue);
        h25a->SetLineColor(kCyan);
        h26->SetLineColor(kGreen);

	h27->SetLineColor(kRed);
        h28->SetLineColor(kBlue);
        h28a->SetLineColor(kCyan);
        h29->SetLineColor(kGreen);
	
	h_24->SetLineColor(kRed);
        h_25->SetLineColor(kBlue);
        h_25a->SetLineColor(kCyan);
        h_26->SetLineColor(kGreen);

	h_27->SetLineColor(kRed);
        h_28->SetLineColor(kBlue);
        h_28a->SetLineColor(kCyan);
        h_29->SetLineColor(kGreen);

        th22->SetLineColor(kBlue);
        th23->SetLineColor(kGreen);
	
	th24->SetLineColor(kRed);
        th25->SetLineColor(kBlue);
        th25a->SetLineColor(kCyan);
        th26->SetLineColor(kGreen);

	th27->SetLineColor(kRed);
        th28->SetLineColor(kBlue);
        th28a->SetLineColor(kCyan);
        th29->SetLineColor(kGreen);
	
	h30->SetLineColor(kRed);
        h31->SetLineColor(kBlue);
        h32->SetLineColor(kGreen);	

	h33->SetLineColor(kRed);
        h34->SetLineColor(kBlue);
        h35->SetLineColor(kGreen);

	/*h36->SetLineColor(kBlack);
        h37->SetLineColor(kGreen);
        h38->SetLineColor(kBlue);
	h39->SetLineColor(kCyan);
	h40->SetLineColor(kRed);
	h41->SetLineColor(kGreen+3);
       */
	th36->SetLineColor(kGreen+3);
        th37->SetLineColor(kBlack);
        th38->SetLineColor(kCyan);
	th39->SetLineColor(kRed-9);
	th40->SetLineColor(kRed);
	th41->SetLineColor(kRed+2);

	h42->SetLineColor(kRed);
	h43->SetLineColor(kBlue);
	h44->SetLineColor(kGreen+3);

	h45->SetLineColor(kRed);
	h46->SetLineColor(kBlack);
	h47->SetLineColor(kGreen);
	h48->SetLineColor(kBlue);
	h49->SetLineColor(kRed);
	h50->SetLineColor(kGreen+3);
	h51->SetLineColor(kGreen);
	h52->SetLineColor(kBlue);
	h53->SetLineColor(kRed);

	h54->SetLineColor(kRed);
	h55->SetLineColor(kBlack);
	h56->SetLineColor(kGreen);
	h57->SetLineColor(kBlue);
	h58->SetLineColor(kRed);
	h59->SetLineColor(kGreen+3);
	h60->SetLineColor(kGreen);
	h61->SetLineColor(kBlue);
	h62->SetLineColor(kRed); 

	h63->SetLineColor(kRed);
	//h64->SetLineColor(kBlue);
	//h65->SetLineColor(kRed);
	h66->SetLineColor(kGreen);
	h67->SetLineColor(kBlue);
	h68->SetLineColor(kRed);
	h69->SetLineColor(kGreen);
	h70->SetLineColor(kBlue);
	h71->SetLineColor(kRed);
	h72->SetLineColor(kRed+2);
	//h73->SetLineColor(kBlue);
	//h74->SetLineColor(kRed);
	h75->SetLineColor(kGreen);
	h76->SetLineColor(kBlue);
	h77->SetLineColor(kRed);
	h78->SetLineColor(kGreen);
	h79->SetLineColor(kBlue);
	h80->SetLineColor(kRed);
	h81->SetLineColor(kRed);
	//h82->SetLineColor(kBlue);
	//h83->SetLineColor(kRed);
	h84->SetLineColor(kGreen);
	h85->SetLineColor(kBlue);
	h86->SetLineColor(kRed);
	h87->SetLineColor(kGreen);
	h88->SetLineColor(kBlue);
	h89->SetLineColor(kRed);
	h90->SetLineColor(kRed+2);
	//h91->SetLineColor(kBlue);
	//h92->SetLineColor(kRed);
	h93->SetLineColor(kGreen);
	h94->SetLineColor(kBlue);
	h95->SetLineColor(kRed);
	h96->SetLineColor(kGreen);
	h97->SetLineColor(kBlue);
	h98->SetLineColor(kRed);
	h99->SetLineColor(kRed);
	//h100->SetLineColor(kBlue);
	//h101->SetLineColor(kRed);
	h102->SetLineColor(kGreen);
	h103->SetLineColor(kBlue);
	h104->SetLineColor(kRed);
	h105->SetLineColor(kGreen);
	h106->SetLineColor(kBlue);
	h107->SetLineColor(kRed);
	h108->SetLineColor(kRed+2);
	//h109->SetLineColor(kBlue);
	//h110->SetLineColor(kRed);
	h111->SetLineColor(kGreen);
	h112->SetLineColor(kBlue);
	h113->SetLineColor(kRed);
	h114->SetLineColor(kGreen);
	h115->SetLineColor(kBlue);
	h116->SetLineColor(kRed);

	h120->SetLineColor(kBlack);
	h121->SetLineColor(kGreen);
	h122->SetLineColor(kBlue);
	h123->SetLineColor(kRed);
	h124->SetLineColor(kBlack);
	h125->SetLineColor(kGreen);
	h126->SetLineColor(kBlue);
	h127->SetLineColor(kRed);
	h128->SetLineColor(kBlack);
	h129->SetLineColor(kGreen);
	h130->SetLineColor(kBlue);
	h131->SetLineColor(kRed);
	h132->SetLineColor(kBlack);
	h133->SetLineColor(kGreen);
	h134->SetLineColor(kBlue);
	h135->SetLineColor(kRed);
	h136->SetLineColor(kBlack);
	h137->SetLineColor(kGreen);
	h138->SetLineColor(kBlue);
	h139->SetLineColor(kRed);
	h140->SetLineColor(kBlack);
	h141->SetLineColor(kGreen);
	h142->SetLineColor(kBlue);
	h143->SetLineColor(kRed);
	h144->SetLineColor(kBlack);
	h145->SetLineColor(kGreen);
	h146->SetLineColor(kBlue);
	h147->SetLineColor(kRed);

	std::cout<<"num events : " <<num_events <<"\n";
	TCanvas *C =new TCanvas();
	//! See effect of Phi barrel cut
	rec.Draw("M_pt:Phi13>>h1",matched && truth_m,"",num_events);
	rec.Draw("M_pt:Phi13>>h2",matched && truth_m && phiBarrel,"same",num_events);

	//! compare truth and reconstructed Pt as a function of Phi13 for matched tracks
	rec.Draw("Pt_n:Phi13>>h4",matched && recon_m,"same",num_events);

	//! compare reconstructed truth and fakes plot
	rec.Draw("Pt_n:Phi13>>h6",fakes && recon_m,"same",num_events);

	//! compare truth and reconstructed Pt for matched tracks and for different particles
	//! ideally should be a straight line with slope 1
	//! disagreement seen in the low pt region -> explains multiple scattering
	rec.Draw("Pt_n:M_pt>>h7",matched && truth_m && recon_m,"",num_events);//all
        rec.Draw("Pt_n:M_pt>>h8",matched && truth_m && recon_m && pion,"same",num_events);//pion
        rec.Draw("Pt_n:M_pt>>h9",matched && truth_m && recon_m && electron,"same",num_events);//electron -> majority of the lowpt e's are wrongly reconstructed as high pt e's
        rec.Draw("Pt_n:M_pt>>h10",matched && truth_m && recon_m && muon,"same"/*,num_events*/);//muon

	//! determine zBarrel cut
	rec.Draw("M_pt:Z13>>h11",matched && truth_m && phiBarrel && z0truthmax,"",num_events);

	//! Zvtx Vs dphi2
	rec.Draw("Z013:dphi2>>h12", fakes && phiBarrel && zBarrel && z0recmax,"",num_events);
	rec.Draw("Z013:dphi2>>h13",matched && phiBarrel && zBarrel && z0recmax,"same",num_events);
	rec.Draw("M_Vz:dphi2>>h14",matched /*&& phiBarrel && zBarrel*/ && z0truthmax,"same",num_events);
	rec.Draw("dphi2>>h14a",matched && phiBarrel && zBarrel && z0recmax,"same",num_events);

	//! Zvtx Vs dz2
        rec.Draw("Z013:dz2>>h15",fakes && phiBarrel && zBarrel && z0recmax,"",num_events);
        rec.Draw("Z013:dz2>>h16",matched && phiBarrel && zBarrel && z0recmax,"same",num_events);
        rec.Draw("M_Vz:dz2>>h17",matched /*&& phiBarrel && zBarrel*/ && z0truthmax,"same",num_events);
	rec.Draw("dz2>>h17a",matched && phiBarrel && zBarrel && z0recmax,"same",num_events);

	//! theta Vs dphi2
        rec.Draw("dphi2:Theta13>>h18", fakes && minPt && phiBarrel && zBarrel && z0recmax,"",num_events);
        rec.Draw("dphi2:Theta13>>h19",matched && minPt && phiBarrel && zBarrel && z0recmax,"same",num_events);
        rec.Draw("dphi2:M_theta>>h20",matched && minPt_t /*&& phiBarrel && zBarrel*/ && z0truthmax,"same",num_events);

	//! theta Vs dz2
        rec.Draw("dz2:Theta13>>h21", fakes && minPt && phiBarrel && zBarrel && z0recmax,"",num_events);
        rec.Draw("dz2:Theta13>>h22",matched && minPt && phiBarrel && zBarrel && z0recmax,"same",num_events);
        rec.Draw("dz2:M_theta>>h23",matched && minPt_t /*&& phiBarrel && zBarrel*/ && z0truthmax,"same",num_events);
        
	//!theta distribution
	rec.Draw("Theta13>>th22",matched && minPt && phiBarrel && zBarrel && z0recmax,"same",num_events);
        rec.Draw("M_theta>>th23",matched && minPt_t /*&& phiBarrel && zBarrel*/ && z0truthmax,"same",num_events);

	//! sin(theta) vs dphi2
        rec.Draw("dphi2:sin(Theta13)>>h24", fakes && minPt && phiBarrel && zBarrel && z0recmax,"",num_events);
        rec.Draw("dphi2:sin(Theta13)>>h25",matched && minPt && phiBarrel && zBarrel && z0recmax,"same",num_events);
        rec.Draw("dphi2:sin(Theta13)>>h25a",matched && minPt && phiBarrel && zBarrel && z0recmax && noelectron,"same",num_events);
        rec.Draw("dphi2:sin(M_theta)>>h26",matched && minPt_t /*&& phiBarrel && zBarrel*/ && z0truthmax,"same",num_events);
	//! dphi2 Vs sin(theta) w/o dphi2 and dz2 cut
        rec.Draw("dphi2:sin(Theta13)>>h_24", fakes && minPt && phiBarrel && zBarrel && z0recmax && kapcut_l,"",num_events);
        rec.Draw("dphi2:sin(Theta13)>>h_25",matched && minPt && phiBarrel && zBarrel && z0recmax && kapcut_l,"same",num_events);
        rec.Draw("dphi2:sin(Theta13)>>h_25a",matched && minPt && phiBarrel && zBarrel && z0recmax && kapcut_l && noelectron,"same",num_events);
        rec.Draw("dphi2:sin(M_theta)>>h_26",matched && minPt_t /*&& phiBarrel && zBarrel*/ && z0truthmax && kapcut_l,"same",num_events);

        //! sin(theta) Vs dz2
        rec.Draw("dz2:sin(Theta13)>>h27", fakes && minPt && phiBarrel && zBarrel && z0recmax,"",num_events);
        rec.Draw("dz2:sin(Theta13)>>h28",matched && minPt && phiBarrel && zBarrel && z0recmax,"same",num_events);
        rec.Draw("dz2:sin(Theta13)>>h28a",matched && minPt && phiBarrel && zBarrel && z0recmax && noelectron,"same",num_events);
        rec.Draw("dz2:sin(M_theta)>>h29",matched && minPt_t /*&& phiBarrel && zBarrel*/ && z0truthmax,"same",num_events);
        //! dz2 Vs sin(theta) w/o dz2 cut and with kappa cut
        rec.Draw("dz2:sin(Theta13)>>h_27", fakes && minPt && phiBarrel && zBarrel && z0recmax && kapcut_l,"",num_events);
        rec.Draw("dz2:sin(Theta13)>>h_28",matched && minPt && phiBarrel && zBarrel && z0recmax && kapcut_l,"same",num_events);
        rec.Draw("dz2:sin(Theta13)>>h_28a",matched && minPt && phiBarrel && zBarrel && z0recmax && kapcut_l && noelectron,"same",num_events);
        rec.Draw("dz2:sin(M_theta)>>h_29",matched && minPt_t /*&& phiBarrel && zBarrel*/ && z0truthmax && kapcut_l,"same",num_events);

	//! cos(theta) vs dphi2
        rec.Draw("dphi2:cos(Theta13)>>th24", fakes && minPt && phiBarrel && zBarrel && z0recmax,"",num_events);
        rec.Draw("dphi2:cos(Theta13)>>th25",matched && minPt && phiBarrel && zBarrel && z0recmax,"same",num_events);
        rec.Draw("dphi2:cos(Theta13)>>th25a",matched && minPt && phiBarrel && zBarrel && z0recmax && noelectron,"same",num_events);
        rec.Draw("dphi2:cos(M_theta)>>th26",matched && minPt_t /*&& phiBarrel && zBarrel*/ && z0truthmax,"same",num_events);

        //! cos(theta) Vs dz2
        rec.Draw("dz2:cos(Theta13)>>th27", fakes && minPt && phiBarrel && zBarrel && z0recmax,"",num_events);
        rec.Draw("dz2:cos(Theta13)>>th28",matched && minPt && phiBarrel && zBarrel && z0recmax,"same",num_events);
        rec.Draw("dz2:cos(Theta13)>>th28a",matched && minPt && phiBarrel && zBarrel && z0recmax && noelectron,"same",num_events);
        rec.Draw("dz2:cos(M_theta)>>th29",matched && minPt_t /*&& phiBarrel && zBarrel*/ && z0truthmax,"same",num_events);
	
	//! pt vs dphi2
        rec.Draw("Pt_n:dphi2>>h30", fakes && minPt && recon_m && phiBarrel && zBarrel && z0recmax,"",num_events);
        rec.Draw("Pt_n:dphi2>>h31",matched && minPt && recon_m && phiBarrel && zBarrel && z0recmax,"same",num_events);
        rec.Draw("M_pt:dphi2>>h32",matched && minPt_t && truth_m /*&& phiBarrel && zBarrel*/ && z0truthmax,"same",num_events);

	//! pt vs dz2
        rec.Draw("Pt_n:dz2>>h33", fakes && minPt && recon_m && phiBarrel && zBarrel && z0recmax,"",num_events);
        rec.Draw("Pt_n:dz2>>h34",matched && minPt && recon_m && phiBarrel && zBarrel && z0recmax,"same",num_events);
        rec.Draw("M_pt:dz2>>h35",matched && minPt_t && truth_m /*&& phiBarrel && zBarrel*/ && z0truthmax,"same",num_events);	

	//rec.Draw("kap013^2:kappa-kap013>>h36",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*dphi2max_l && dz2max_l*/,"",num_events);
	//rec.Draw("kap013^2:kappa-kap013>>h37",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*dphi2max_l && dz2max_l*/ && pion,"same",num_events);
	//rec.Draw("kap013^2:kappa-kap013>>h38",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*dphi2max_l && dz2max_l*/ && electron,"same",num_events);
	//rec.Draw("kap013^2:kappa-kap013>>h39",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*dphi2max_l && dz2max_l*/ && noelectron,"same",num_events);
	//rec.Draw("kap013^2:kappa-kap013>>h40",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*dphi2max_l && dz2max_l*/ && muon,"same"/*,num_events*/);
	//rec.Draw("kap013^2:kappa-kap013>>h41","Tid>0 && abs(M_Vz)<100 && abs(M_Vx)<15 && abs(M_Vy)<15 && abs(M_eta)<1.5 && abs(M_pt)>2e3","same",num_events);

	rec.Draw("kap013:kappa-kap013>>th36","Tid>0 && abs(M_Vz)<100 && abs(M_Vx)<2 && abs(M_Vy)<2 && abs(M_eta)<1.6 && abs(M_pt)>2e3","",num_events);
	rec.Draw("kap013:kappa-kap013>>th37",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*dphi2max_l && dz2max_l*/,"",num_events);
	rec.Draw("kap013:kappa-kap013>>th38",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*dphi2max_l && dz2max_l*/ && noelectron,"same",num_events);
	rec.Draw("kap013:kappa-kap013>>th39",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*dphi2max_l && dz2max_l*/ && kapcut_l,"same",num_events);
	rec.Draw("kap013:kappa-kap013>>th40",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*dphi2max_l && dz2max_l*/ && kapcut,"same",num_events);
	rec.Draw("kap013:kappa-kap013>>th41",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*dphi2max_l && dz2max_l*/ && kapcut_t,"same",num_events);

//!dca distributions
	rec.Draw("dca>>h42",fakes && minPt && phiBarrel && zBarrel && z0recmax,"", num_events);
	rec.Draw("dca>>h43",matched && minPt && phiBarrel && zBarrel && z0recmax,"", num_events);
	rec.Draw("dca>>h44",matched && minPt_t && z0truthmax,"", num_events);

	//! pt vs dca
	rec.Draw("Pt_n:dca>>h45",fakes && minPt && recon_m && phiBarrel && zBarrel && z0recmax,"", num_events);
	rec.Draw("Pt_n:dca>>h46",matched && minPt && recon_m && phiBarrel && zBarrel && z0recmax,"", num_events);
	rec.Draw("Pt_n:dca>>h47",matched && minPt && recon_m && phiBarrel && zBarrel && z0recmax && pion,"", num_events);
	rec.Draw("Pt_n:dca>>h48",matched && minPt && recon_m && phiBarrel && zBarrel && z0recmax && electron,"", num_events);
	rec.Draw("Pt_n:dca>>h49",matched && minPt && recon_m && phiBarrel && zBarrel && z0recmax && muon);
	rec.Draw("M_pt:dca>>h50",matched && minPt_t && truth_m && z0truthmax,"", num_events);
	rec.Draw("M_pt:dca>>h51",matched && minPt_t && truth_m && z0truthmax && pion,"", num_events);
	rec.Draw("M_pt:dca>>h52",matched && minPt_t && truth_m && z0truthmax && electron,"", num_events);
	rec.Draw("M_pt:dca>>h53",matched && minPt_t && truth_m && z0truthmax && muon);
	
	//! z0 vs dca
	rec.Draw("Z013:dca>>h54",fakes && minPt && recon_m && phiBarrel && zBarrel && z0recmax,"", num_events);
	rec.Draw("Z013:dca>>h55",matched && minPt && recon_m && phiBarrel && zBarrel && z0recmax,"", num_events);
	rec.Draw("Z013:dca>>h56",matched && minPt && recon_m && phiBarrel && zBarrel && z0recmax && pion,"", num_events);
	rec.Draw("Z013:dca>>h57",matched && minPt && recon_m && phiBarrel && zBarrel && z0recmax && electron,"", num_events);
	rec.Draw("Z013:dca>>h58",matched && minPt && recon_m && phiBarrel && zBarrel && z0recmax && muon);
	rec.Draw("M_Vz:M_dca>>h59",matched && minPt_t && truth_m && z0truthmax,"", num_events);
	rec.Draw("M_Vz:M_dca>>h60",matched && minPt_t && truth_m && z0truthmax && pion,"", num_events);
	rec.Draw("M_Vz:M_dca>>h61",matched && minPt_t && truth_m && z0truthmax && electron,"", num_events);
	rec.Draw("M_Vz:M_dca>>h62",matched && minPt_t && truth_m && z0truthmax && muon);
	//!dca
	rec.Draw("dca>>h63",fakes && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2,"",num_events);
	/*rec.Draw("dca>>h64",fakes && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && electron,"",num_events);
	rec.Draw("dca>>h65",fakes && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && muon);*/
	rec.Draw("M_dca>>h66",matched && minPt_t && phiBarrel && zBarrel && z0truthmax &&  maxdphi2 && maxdz2 && pion,"",num_events);
	rec.Draw("M_dca>>h67",matched && minPt_t && phiBarrel && zBarrel && z0truthmax && maxdphi2 && maxdz2 && electron,"",num_events);
	rec.Draw("M_dca>>h68",matched && minPt_t && phiBarrel && zBarrel && z0truthmax && maxdphi2 && maxdz2 && muon/*,"",num_events*/);
	rec.Draw("dca>>h69",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && pion,"",num_events);
	rec.Draw("dca>>h70",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && electron,"",num_events);
	rec.Draw("dca>>h71",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && muon/*,"",num_events*/);
	rec.Draw("dca>>h72",fakes && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && kapcut_t,"",num_events);
	/*rec.Draw("dca>>h73",fakes && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && kapcut_t && electron,"",num_events);
	rec.Draw("dca>>h74",fakes && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && kapcut_t && muon);*/
	rec.Draw("M_dca>>h75",matched && minPt_t && phiBarrel && zBarrel && z0truthmax &&  maxdphi2 && maxdz2 && kapcut_t && pion,"",num_events);
	rec.Draw("M_dca>>h76",matched && minPt_t && phiBarrel && zBarrel && z0truthmax && maxdphi2 && maxdz2 && kapcut_t && electron,"",num_events);
	rec.Draw("M_dca>>h77",matched && minPt_t && phiBarrel && zBarrel && z0truthmax && maxdphi2 && maxdz2 && kapcut_t && muon/*,"",num_events*/);
	rec.Draw("dca>>h78",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && kapcut_t && pion,"",num_events);
	rec.Draw("dca>>h79",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && kapcut_t && electron,"",num_events);
	rec.Draw("dca>>h80",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && kapcut_t && muon/*,"",num_events*/);
	//!dz2
	rec.Draw("dz2>>h81",fakes && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2,"",num_events);
	/*rec.Draw("dz2>>h82",fakes && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && electron,"",num_events);
	rec.Draw("dz2>>h83",fakes && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && muon);*/
	rec.Draw("dz2>>h84",matched && minPt_t && phiBarrel && zBarrel && z0truthmax &&  maxdphi2 && maxdz2 && pion,"",num_events);
	rec.Draw("dz2>>h85",matched && minPt_t && phiBarrel && zBarrel && z0truthmax && maxdphi2 && maxdz2 && electron,"",num_events);
	rec.Draw("dz2>>h86",matched && minPt_t && phiBarrel && zBarrel && z0truthmax && maxdphi2 && maxdz2 && muon/*,"",num_events*/);
	rec.Draw("dz2>>h87",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && pion,"",num_events);
	rec.Draw("dz2>>h88",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && electron,"",num_events);
	rec.Draw("dz2>>h89",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && muon/*,"",num_events*/);
	rec.Draw("dz2>>h90",fakes && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && kapcut_t,"",num_events);
	/*rec.Draw("dz2>>h91",fakes && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && kapcut_t && electron,"",num_events);
	rec.Draw("dz2>>h92",fakes && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && kapcut_t && muon);*/
	rec.Draw("dz2>>h93",matched && minPt_t && phiBarrel && zBarrel && z0truthmax &&  maxdphi2 && maxdz2 && kapcut_t && pion,"",num_events);
	rec.Draw("dz2>>h94",matched && minPt_t && phiBarrel && zBarrel && z0truthmax && maxdphi2 && maxdz2 && kapcut_t && electron,"",num_events);
	rec.Draw("dz2>>h95",matched && minPt_t && phiBarrel && zBarrel && z0truthmax && maxdphi2 && maxdz2 && kapcut_t && muon/*,"",num_events*/);
	rec.Draw("dz2>>h96",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && kapcut_t && pion,"",num_events);
	rec.Draw("dz2>>h97",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && kapcut_t && electron,"",num_events);
	rec.Draw("dz2>>h98",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && kapcut_t && muon/*,"",num_events*/);
	//!dkappa
	rec.Draw("kappa-kap013>>h99",fakes && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2,"",num_events);
	/*rec.Draw("kappa-kap013>>h100",fakes && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && electron,"",num_events);
	rec.Draw("kappa-kap013>>h101",fakes && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && muon);*/
	rec.Draw("kappa-kap013>>h102",matched && minPt_t && phiBarrel && zBarrel && z0truthmax &&  maxdphi2 && maxdz2 && pion,"",num_events);
	rec.Draw("kappa-kap013>>h103",matched && minPt_t && phiBarrel && zBarrel && z0truthmax && maxdphi2 && maxdz2 && electron,"",num_events);
	rec.Draw("kappa-kap013>>h104",matched && minPt_t && phiBarrel && zBarrel && z0truthmax && maxdphi2 && maxdz2 && muon/*,"",num_events*/);
	rec.Draw("kappa-kap013>>h105",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && pion,"",num_events);
	rec.Draw("kappa-kap013>>h106",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && electron,"",num_events);
	rec.Draw("kappa-kap013>>h107",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && muon/*,"",num_events*/);
	rec.Draw("kappa-kap013>>h108",fakes && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && kapcut_t,"",num_events);
	/*rec.Draw("kappa-kap013>>h109",fakes && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && kapcut_t && electron,"",num_events);
	rec.Draw("kappa-kap013>>h110",fakes && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && kapcut_t && muon);*/
	rec.Draw("kappa-kap013>>h111",matched && minPt_t && phiBarrel && zBarrel && z0truthmax &&  maxdphi2 && maxdz2 && kapcut_t && pion,"",num_events);
	rec.Draw("kappa-kap013>>h112",matched && minPt_t && phiBarrel && zBarrel && z0truthmax && maxdphi2 && maxdz2 && kapcut_t && electron,"",num_events);
	rec.Draw("kappa-kap013>>h113",matched && minPt_t && phiBarrel && zBarrel && z0truthmax && maxdphi2 && maxdz2 && kapcut_t && muon/*,"",num_events*/);
	rec.Draw("kappa-kap013>>h114",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && kapcut_t && pion,"",num_events);
	rec.Draw("kappa-kap013>>h115",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && kapcut_t && electron,"",num_events);
	rec.Draw("kappa-kap013>>h116",matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 && kapcut_t && muon/*,"",num_events*/);

	rec.Draw("M_kap>>h117",matched && minPt_t && phiBarrel && zBarrel && z0truthmax,"",num_events);
	rec.Draw("kap013>>h118",matched && minPt && phiBarrel && zBarrel && z0recmax,"",num_events);
	rec.Draw("kappa>>h119",matched && minPt && phiBarrel && zBarrel && z0recmax,"",num_events);

	rec.Draw("kap013:M_kap>>h120",matched && minPt_t && minPt && phiBarrel && zBarrel && z0recmax && z0truthmax,"",num_events);
	rec.Draw("kap013:M_kap>>h121",matched && minPt_t && minPt && phiBarrel && zBarrel && z0recmax && z0truthmax && pion,"",num_events);
	rec.Draw("kap013:M_kap>>h122",matched && minPt_t && minPt && phiBarrel && zBarrel && z0recmax && z0truthmax && electron,"",num_events);
	rec.Draw("kap013:M_kap>>h123",matched && minPt_t && minPt && phiBarrel && zBarrel && z0recmax && z0truthmax && muon,"",num_events);
	rec.Draw("kappa:M_kap>>h124",matched && minPt_t && minPt && phiBarrel && zBarrel && z0recmax && z0truthmax,"",num_events);
	rec.Draw("kappa:M_kap>>h125",matched && minPt_t && minPt && phiBarrel && zBarrel && z0recmax && z0truthmax && pion,"",num_events);
	rec.Draw("kappa:M_kap>>h126",matched && minPt_t && minPt && phiBarrel && zBarrel && z0recmax && z0truthmax && electron,"",num_events);
	rec.Draw("kappa:M_kap>>h127",matched && minPt_t && minPt && phiBarrel && zBarrel && z0recmax && z0truthmax && muon,"",num_events);

	rec.Draw("kap013:kappa>>h128",matched && minPt && phiBarrel && zBarrel && z0recmax,"",num_events);
	rec.Draw("kap013:kappa>>h129",matched && minPt && phiBarrel && zBarrel && z0recmax && pion,"",num_events);
	rec.Draw("kap013:kappa>>h130",matched && minPt && phiBarrel && zBarrel && z0recmax && electron,"",num_events);
	rec.Draw("kap013:kappa>>h131",matched && minPt && phiBarrel && zBarrel && z0recmax && muon,"",num_events);

	rec.Draw("kap013/M_kap>>h132",matched && minPt && phiBarrel && zBarrel && z0recmax,"",num_events);
	rec.Draw("kap013/M_kap>>h133",matched && minPt && phiBarrel && zBarrel && z0recmax && pion,"",num_events);
	rec.Draw("kap013/M_kap>>h134",matched && minPt && phiBarrel && zBarrel && z0recmax && electron,"",num_events);
	rec.Draw("kap013/M_kap>>h135",matched && minPt && phiBarrel && zBarrel && z0recmax && muon,"",num_events);
	rec.Draw("kappa/M_kap>>h136",matched && minPt && phiBarrel && zBarrel && z0recmax,"",num_events);
	rec.Draw("kappa/M_kap>>h137",matched && minPt && phiBarrel && zBarrel && z0recmax && pion,"",num_events);
	rec.Draw("kappa/M_kap>>h138",matched && minPt && phiBarrel && zBarrel && z0recmax && electron,"",num_events);
	rec.Draw("kappa/M_kap>>h139",matched && minPt && phiBarrel && zBarrel && z0recmax && muon,"",num_events);

	rec.Draw("kap013-kappa:sqrt((M_Vx*M_Vx) + (M_Vy*M_Vy))>>h140",matched && minPt_t && minPt && phiBarrel && zBarrel && z0recmax && z0truthmax,"",num_events);
	rec.Draw("kap013-kappa:sqrt((M_Vx*M_Vx) + (M_Vy*M_Vy))>>h141",matched && minPt_t && minPt && phiBarrel && zBarrel && z0recmax && z0truthmax && pion,"",num_events);
	rec.Draw("kap013-kappa:sqrt((M_Vx*M_Vx) + (M_Vy*M_Vy))>>h142",matched && minPt_t && minPt && phiBarrel && zBarrel && z0recmax && z0truthmax && electron,"",num_events);
	rec.Draw("kap013-kappa:sqrt((M_Vx*M_Vx) + (M_Vy*M_Vy))>>h143",matched && minPt_t && minPt && phiBarrel && zBarrel && z0recmax && z0truthmax && muon,"",num_events);
	rec.Draw("kap013/M_kap:sqrt((M_Vx*M_Vx) + (M_Vy*M_Vy))>>h144",matched && minPt_t && minPt && phiBarrel && zBarrel && z0recmax && z0truthmax,"",num_events);
	rec.Draw("kap013/M_kap:sqrt((M_Vx*M_Vx) + (M_Vy*M_Vy))>>h145",matched && minPt_t && minPt && phiBarrel && zBarrel && z0recmax && z0truthmax && pion,"",num_events);
	rec.Draw("kap013/M_kap:sqrt((M_Vx*M_Vx) + (M_Vy*M_Vy))>>h146",matched && minPt_t && minPt && phiBarrel && zBarrel && z0recmax && z0truthmax && electron,"",num_events);
	rec.Draw("kap013/M_kap:sqrt((M_Vx*M_Vx) + (M_Vy*M_Vy))>>h147",matched && minPt_t && minPt && phiBarrel && zBarrel && z0recmax && z0truthmax && muon,"",num_events);

	rec.Draw("Eta13>>h_num_vs_etaPU",   num_select, "goff"/*, num_events*/);
        rec.Draw("Eta13>>h_den_vs_etaPU",   den_select, "goff"/*, num_events*/);
	TH1* h_pur_vs_etaPU = dynamic_cast<TH1*>(h_num_vs_etaPU->Clone("h_pur_vs_etaPU"));
        h_pur_vs_etaPU->SetTitle("Purity vs #eta;#eta;Purity");
        h_pur_vs_etaPU->Divide(h_num_vs_etaPU, h_den_vs_etaPU, 1.0, 1.0, "B");
        h_pur_vs_etaPU->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_pur_vs_etaPU->SetMarkerSize(0.95);
        h_pur_vs_etaPU->SetMarkerStyle(kOpenTriangleDown);
        h_pur_vs_etaPU->SetMarkerColor(kBlack);

	rec.Draw("Pt_n>>h_num_vs_ptPU",   num_select, "goff"/*, num_events*/);
	rec.Draw("Pt_n>>h_den_vs_ptPU",   den_select, "goff"/*, num_events*/);
	TH1* h_pur_vs_ptPU = dynamic_cast<TH1*>(h_num_vs_ptPU->Clone("h_pur_vs_ptPU"));
	h_pur_vs_ptPU->SetTitle("Purity vs P_{t};P_{t} [MeV/c];Purity");
	h_pur_vs_ptPU->Divide(h_num_vs_ptPU, h_den_vs_ptPU, 1.0, 1.0, "B");
	h_pur_vs_ptPU->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_pur_vs_ptPU->GetXaxis()->SetRangeUser(2000.,1000000.);
	h_pur_vs_ptPU->SetMarkerSize(0.95);
	h_pur_vs_ptPU->SetMarkerStyle(kOpenTriangleDown);
	h_pur_vs_ptPU->SetMarkerColor(kBlack);	
	
	rec.Draw("Eta13>>h_num_vs_eta_",   matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 , "goff"/*, num_events*/);

        rec.Draw("Eta13>>h_den_vs_eta_",   (fakes || matched) && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 , "goff"/*, num_events*/);
	TH1* h_pur_vs_eta_ = dynamic_cast<TH1*>(h_num_vs_eta_->Clone("h_pur_vs_eta_"));
        h_pur_vs_eta_->SetTitle("Purity vs #eta;#eta;Purity");
        h_pur_vs_eta_->Divide(h_num_vs_eta_, h_den_vs_eta_, 1.0, 1.0, "B");
        h_pur_vs_eta_->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_pur_vs_eta_->SetMarkerSize(0.95);
        h_pur_vs_eta_->SetMarkerStyle(kFullTriangleDown);
        h_pur_vs_eta_->SetMarkerColor(kBlack);

	rec.Draw("Pt_n>>h_num_vs_pt_",   matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2, "goff"/*, num_events*/);
	rec.Draw("Pt_n>>h_den_vs_pt_",   (fakes || matched) && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2, "goff"/*, num_events*/);
	TH1* h_pur_vs_pt_ = dynamic_cast<TH1*>(h_num_vs_pt_->Clone("h_pur_vs_pt_"));
	h_pur_vs_pt_->SetTitle("Purity vs P_{t};P_{t} [MeV/c];Purity");
	h_pur_vs_pt_->Divide(h_num_vs_pt_, h_den_vs_pt_, 1.0, 1.0, "B");
	h_pur_vs_pt_->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_pur_vs_pt_->GetXaxis()->SetRangeUser(2000.,1000000.);
	h_pur_vs_pt_->SetMarkerSize(0.95);
	h_pur_vs_pt_->SetMarkerStyle(kFullTriangleDown);
	h_pur_vs_pt_->SetMarkerColor(kBlack);	


	rec.Draw("Eta13>>h_num_vs_eta_l",   matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*&& dphi2max && dz2max*/ && kapcut_l, "goff"/*, num_events*/);

        rec.Draw("Eta13>>h_den_vs_eta_l",   (fakes || matched) && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*&& dphi2max && dz2max*/ && kapcut_l, "goff"/*, num_events*/);
	TH1* h_pur_vs_eta_l = dynamic_cast<TH1*>(h_num_vs_eta_l->Clone("h_pur_vs_eta_l"));
        h_pur_vs_eta_l->SetTitle("Purity vs #eta;#eta;Purity");
        h_pur_vs_eta_l->Divide(h_num_vs_eta_l, h_den_vs_eta_l, 1.0, 1.0, "B");
        h_pur_vs_eta_l->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_pur_vs_eta_l->SetMarkerSize(0.95);
        h_pur_vs_eta_l->SetMarkerStyle(kFullTriangleDown);
        h_pur_vs_eta_l->SetMarkerColor(kRed-9);

	rec.Draw("Pt_n>>h_num_vs_pt_l",   matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*&& dphi2max_l && dz2max_l*/ && kapcut_l, "goff"/*, num_events*/);
	rec.Draw("Pt_n>>h_den_vs_pt_l",   (fakes || matched) && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*&& dphi2max_l && dz2max_l*/ && kapcut_l, "goff"/*, num_events*/);
	TH1* h_pur_vs_pt_l = dynamic_cast<TH1*>(h_num_vs_pt_l->Clone("h_pur_vs_pt_l"));
	h_pur_vs_pt_l->SetTitle("Purity vs P_{t};P_{t} [MeV/c];Purity");
	h_pur_vs_pt_l->Divide(h_num_vs_pt_l, h_den_vs_pt_l, 1.0, 1.0, "B");
	h_pur_vs_pt_l->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_pur_vs_pt_l->GetXaxis()->SetRangeUser(2000.,1000000.);
	h_pur_vs_pt_l->SetMarkerSize(0.95);
	h_pur_vs_pt_l->SetMarkerStyle(kFullTriangleDown);
	h_pur_vs_pt_l->SetMarkerColor(kRed-9);	

rec.Draw("Eta13>>h_num_vs_eta_m",   matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*&& dphi2max && dz2max*/ && kapcut, "goff"/*, num_events*/);
        rec.Draw("Eta13>>h_den_vs_eta_m",   (fakes || matched) && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*&& dphi2max && dz2max*/ && kapcut, "goff"/*, num_events*/);
	TH1* h_pur_vs_eta_m = dynamic_cast<TH1*>(h_num_vs_eta_m->Clone("h_pur_vs_eta_m"));
        h_pur_vs_eta_m->SetTitle("Purity vs #eta;#eta;Purity");
        h_pur_vs_eta_m->Divide(h_num_vs_eta_m, h_den_vs_eta_m, 1.0, 1.0, "B");
        h_pur_vs_eta_m->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_pur_vs_eta_m->SetMarkerSize(0.95);
        h_pur_vs_eta_m->SetMarkerStyle(kFullTriangleDown);
        h_pur_vs_eta_m->SetMarkerColor(kRed);

	rec.Draw("Pt_n>>h_num_vs_pt_m",   matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*&& dphi2max && dz2max*/ && kapcut, "goff"/*, num_events*/);
	rec.Draw("Pt_n>>h_den_vs_pt_m",   (fakes || matched) && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*&& dphi2max && dz2max*/ && kapcut, "goff"/*, num_events*/);
	TH1* h_pur_vs_pt_m = dynamic_cast<TH1*>(h_num_vs_pt_m->Clone("h_pur_vs_pt_m"));
	h_pur_vs_pt_m->SetTitle("Purity vs P_{t};P_{t} [MeV/c];Purity");
	h_pur_vs_pt_m->Divide(h_num_vs_pt_m, h_den_vs_pt_m, 1.0, 1.0, "B");
	h_pur_vs_pt_m->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_pur_vs_pt_m->GetXaxis()->SetRangeUser(2000.,1000000.);
	h_pur_vs_pt_m->SetMarkerSize(0.95);
	h_pur_vs_pt_m->SetMarkerStyle(kFullTriangleDown);
	h_pur_vs_pt_m->SetMarkerColor(kRed);	

	rec.Draw("Eta13>>h_num_vs_eta_t",   matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*&& dphi2max_t && dz2max_t*/ && kapcut_t, "goff"/*, num_events*/);
        rec.Draw("Eta13>>h_den_vs_eta_t",   (fakes || matched) && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*&& dphi2max_t && dz2max_t*/ && kapcut_t, "goff"/*, num_events*/);
	TH1* h_pur_vs_eta_t = dynamic_cast<TH1*>(h_num_vs_eta_t->Clone("h_pur_vs_eta_t"));
        h_pur_vs_eta_t->SetTitle("Purity vs #eta;#eta;Purity");
        h_pur_vs_eta_t->Divide(h_num_vs_eta_t, h_den_vs_eta_t, 1.0, 1.0, "B");
        h_pur_vs_eta_t->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_pur_vs_eta_t->SetMarkerSize(0.95);
        h_pur_vs_eta_t->SetMarkerStyle(kFullTriangleDown);
        h_pur_vs_eta_t->SetMarkerColor(kRed+2);

	rec.Draw("Pt_n>>h_num_vs_pt_t",   matched && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*&& dphi2max_t && dz2max_t*/ && kapcut_t, "goff"/*, num_events*/);
	rec.Draw("Pt_n>>h_den_vs_pt_t",   (fakes || matched) && minPt && phiBarrel && zBarrel && z0recmax && maxdphi2 && maxdz2 /*&& dphi2max_t && dz2max_t*/ && kapcut_t, "goff"/*, num_events*/);
	TH1* h_pur_vs_pt_t = dynamic_cast<TH1*>(h_num_vs_pt_t->Clone("h_pur_vs_pt_t"));
	h_pur_vs_pt_t->SetTitle("Purity vs P_{t};P_{t} [MeV/c];Purity");
	h_pur_vs_pt_t->Divide(h_num_vs_pt_t, h_den_vs_pt_t, 1.0, 1.0, "B");
	h_pur_vs_pt_t->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_pur_vs_pt_t->GetXaxis()->SetRangeUser(2000.,1000000.);
	h_pur_vs_pt_t->SetMarkerSize(0.95);
	h_pur_vs_pt_t->SetMarkerStyle(kFullTriangleDown);
	h_pur_vs_pt_t->SetMarkerColor(kRed+2);	



	h1->Draw();
	h2->Draw();
	h4->Draw();
	h6->Draw();
	h7->Draw();
	h8->Draw();
	h9->Draw();
	h10->Draw();
	h11->Draw();		      
	h12->Draw();
	h13->Draw();
	h14->Draw();		      
	h14a->Draw();		      
	h15->Draw();
	h16->Draw();
	h17->Draw();		      
	h17a->Draw();		      
	h18->Draw();
	h19->Draw();
	h20->Draw();		      
	h21->Draw();
	h22->Draw();
	h23->Draw();
	h24->Draw();
	h25->Draw();
	h25a->Draw();
	h26->Draw();
	h27->Draw();
	h28->Draw();
	h28a->Draw();
	h29->Draw();
	h_24->Draw();
	h_25->Draw();
	h_25a->Draw();
	h_26->Draw();
	h_27->Draw();
	h_28->Draw();
	h_28a->Draw();
	h_29->Draw();
	th22->Draw();
	th23->Draw();
	th24->Draw();
	th25->Draw();
	th25a->Draw();
	th26->Draw();
	th27->Draw();
	th28->Draw();
	th28a->Draw();
	th29->Draw();
	h30->Draw();
	h31->Draw();
	h32->Draw();		      
	h33->Draw();
	h34->Draw();
	h35->Draw();
	/*h36->Draw();
        h37->Draw();
        h38->Draw();
	h39->Draw();
	h40->Draw();
	h41->Draw();
	*/th36->Draw();
        th37->Draw();
        th38->Draw();
	th39->Draw();
	th40->Draw();
	th41->Draw();
	h42->Draw();
        h43->Draw();
        h44->Draw();
        h45->Draw();
        h46->Draw();
        h47->Draw();
        h48->Draw();
        h49->Draw();
        h50->Draw();
        h51->Draw();
        h52->Draw();
        h53->Draw();
        h54->Draw();
        h55->Draw();
        h56->Draw();
        h57->Draw();
        h58->Draw();
        h59->Draw();
        h60->Draw();
        h61->Draw();
        h62->Draw();

	h63->Draw();
	//h64->Draw();
	//h65->Draw();
	h66->Draw();
	h67->Draw();
	h68->Draw();
	h69->Draw();
	h70->Draw();
	h71->Draw();
	h72->Draw();
	//h73->Draw();
	//h74->Draw();
	h75->Draw();
	h76->Draw();
	h77->Draw();
	h78->Draw();
	h79->Draw();
	h80->Draw();
	h81->Draw();
	//h82->Draw();
	//h83->Draw();
	h84->Draw();
	h85->Draw();
	h86->Draw();
	h87->Draw();
	h88->Draw();
	h89->Draw();
	h90->Draw();
	//h91->Draw();
	//h92->Draw();
	h93->Draw();
	h94->Draw();
	h95->Draw();
	h96->Draw();
	h97->Draw();
	h98->Draw();
	h99->Draw();
	//h100->Draw();
	//h101->Draw();
	h102->Draw();
	h103->Draw();
	h104->Draw();
	h105->Draw();
	h106->Draw();
	h107->Draw();
	h108->Draw();
	//h109->Draw();
	//h110->Draw();
	h111->Draw();
	h112->Draw();
	h113->Draw();
	h114->Draw();
	h115->Draw();
	h116->Draw();
	
	h117->Draw();
	h118->Draw();
	h119->Draw();
		 
	h120->Draw();
	h121->Draw();
	h122->Draw();
	h123->Draw();
	h124->Draw();
	h125->Draw();
	h126->Draw();
	h127->Draw();
	h128->Draw();
	h129->Draw();
	h130->Draw();
	h131->Draw();
		 
	h132->Draw();
	h133->Draw();
	h134->Draw();
	h135->Draw();
	h136->Draw();
	h137->Draw();
	h138->Draw();
	h139->Draw();
		 
	h140->Draw();
	h141->Draw();
	h142->Draw();
	h143->Draw();
	h144->Draw();
	h145->Draw();
	h146->Draw();
	h147->Draw();






/*	TCanvas* a1 = new TCanvas();
	h25->Draw();
	fdphi2_l->Draw("same");
	fdphi2_m->Draw("same");
	fdphi2_t->Draw("same");
	a1->Update();
		
	TCanvas* a2 = new TCanvas();
	h28->Draw();
	fdz2_l->Draw("same");
	fdz2_m->Draw("same");
	fdz2_t->Draw("same");
	a2->Update();
	
	TCanvas* a3 = new TCanvas();
	h36->Draw();
	fkap_l->Draw("same");
        fkap_m->Draw("same");
        fkap_t->Draw("same");
	a3->Update();
        	
	TCanvas* a4 = new TCanvas();
	h39->Draw();
	fkap_l->Draw("same");
        fkap_m->Draw("same");
        fkap_t->Draw("same");
	a4->Update();
        
*/
	char out_file_root[1023];
        sprintf(out_file_root,"%s/%s.root",out_path,output_file_name);
        TFile* output_file = new TFile(out_file_root, "RECREATE");
	
	
	h1->Write();
	h2->Write();
	h4->Write();
	h6->Write();

	h7->Write();
	h8->Write();
	h9->Write();
	h10->Write();

	h11->Write();
		      
	h12->Write();
	h13->Write();
	h14->Write();
	h14a->Write();
		      
	h15->Write();
	h16->Write();
	h17->Write();
	h17a->Write();
		      
	h18->Write();
	h19->Write();
	h20->Write();
		      
	h21->Write();
	h22->Write();
	h23->Write();
	
	th22->Write();
	th23->Write();

	h24->Write();
	h25->Write();
	h25a->Write();
	h26->Write();
	h_24->Write();
	h_25->Write();
	h_25a->Write();
	h_26->Write();
	
	/*fdphi2_l->Write();
	fdphi2_m->Write();
	fdphi2_t->Write();
*/
	th24->Write();
	th25->Write();
	th25a->Write();
	th26->Write();
	      
	h27->Write();
	h28->Write();
	h28a->Write();
	h29->Write();
	h_27->Write();
	h_28->Write();
	h_28a->Write();
	h_29->Write();
	fdz2->Write();	
	fdz2_->Write();	
	/*fdz2_l->Write();
	fdz2_m->Write();
	fdz2_t->Write();
*/
	th27->Write();
	th28->Write();
	th28a->Write();
	th29->Write();
	      
	h30->Write();
	h31->Write();
	h32->Write();
		      
	h33->Write();
	h34->Write();
	h35->Write();
	/*h36->Write();
	h37->Write();
	h38->Write();
	h39->Write();
	h40->Write();
	h41->Write();
	*/th36->Write();
	th37->Write();
	th38->Write();
	th39->Write();
	th40->Write();
	th41->Write();
	h42->Write();
        h43->Write();
        h44->Write();
        h45->Write();
        h46->Write();
        h47->Write();
        h48->Write();
        h49->Write();
        h50->Write();
        h51->Write();
        h52->Write();
        h53->Write();
        h54->Write();
        h55->Write();
        h56->Write();
        h57->Write();
        h58->Write();
        h59->Write();
        h60->Write();
        h61->Write();
        h62->Write();

	h63->Write();
	//h64->Write();
	//h65->Write();
	h66->Write();
	h67->Write();
	h68->Write();
	h69->Write();
	h70->Write();
	h71->Write();
	h72->Write();
	//h73->Write();
	//h74->Write();
	h75->Write();
	h76->Write();
	h77->Write();
	h78->Write();
	h79->Write();
	h80->Write();
	h81->Write();
	//h82->Write();
	//h83->Write();
	h84->Write();
	h85->Write();
	h86->Write();
	h87->Write();
	h88->Write();
	h89->Write();
	h90->Write();
	//h91->Write();
	//h92->Write();
	h93->Write();
	h94->Write();
	h95->Write();
	h96->Write();
	h97->Write();
	h98->Write();
	h99->Write();
	//h100->Write();
	//h101->Write();
	h102->Write();
	h103->Write();
	h104->Write();
	h105->Write();
	h106->Write();
	h107->Write();
	h108->Write();
	//h109->Write();
	//h110->Write();
	h111->Write();
	h112->Write();
	h113->Write();
	h114->Write();
	h115->Write();
	h116->Write();
	/*fkap_l->Write("kappa_l");
	fkap_m->Write("kappa_m");
	fkap_t->Write("kappa_t");
*/
	h117->Write();
	h118->Write();
	h119->Write();
		 
	h120->Write();
	h121->Write();
	h122->Write();
	h123->Write();
	h124->Write();
	h125->Write();
	h126->Write();
	h127->Write();
	h128->Write();
	h129->Write();
	h130->Write();
	h131->Write();
		 
	h132->Write();
	h133->Write();
	h134->Write();
	h135->Write();
	h136->Write();
	h137->Write();
	h138->Write();
	h139->Write();
		 
	h140->Write();
	h141->Write();
	h142->Write();
	h143->Write();
	h144->Write();
	h145->Write();
	h146->Write();
	h147->Write();

	h_pur_vs_etaPU->Write();
	h_pur_vs_eta_->Write();
	h_pur_vs_eta_l->Write();
	h_pur_vs_eta_m->Write();
	h_pur_vs_eta_t->Write();
	h_pur_vs_ptPU->Write();
	h_pur_vs_pt_->Write();
	h_pur_vs_pt_l->Write();
	h_pur_vs_pt_m->Write();
	h_pur_vs_pt_t->Write();

	//a1->Write();
	//a2->Write();
	//a3->Write();
	output_file->Close();
	
	std::cout<<"histograms written to output file! \n";
}
int plot_all(){
std::cout<<"plot all called \n";
/*
newcontrol( "control_minBiasA_f", "A");
std::cout<<"SetA done! \n";
newcontrol( "control_minBiasB_f", "B");
std::cout<<"SetB done! \n";
newcontrol( "control_minBiasC_f", "C");
std::cout<<"SetC done! \n";
*/
newcontrol( "control_minBiaskA_f", "A");
std::cout<<"SetA done! \n";
newcontrol( "control_minBiaskB_f", "B");
std::cout<<"SetB done! \n";
newcontrol( "control_minBiaskC_f", "C");
std::cout<<"SetC done! \n";
return 0;
}

