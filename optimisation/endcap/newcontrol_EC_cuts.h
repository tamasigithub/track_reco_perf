#include "TCut.h"

//! DEFINE CUTS for numerator and denominator
//! z3-z1 = 80mm
TCut num_select    = "abs(station) == 1 && Tid>0  && Pt_n > 2000  && abs(Z013) < 100 && abs(Eta13) < 2.5 && abs(Eta13) > 1.7 && abs(Phi13)<0.028 && abs(Eta3 - Eta1)<0.009";
TCut den_select    = "abs(station) == 1 && Tid>-2 && Pt_n > 2000  && abs(Z013) < 100 && abs(Eta13) < 2.5 && abs(Eta13) > 1.7 && abs(Phi13)<0.028 && abs(Eta3 - Eta1)<0.009";
//! 
TCut phi13EC	= "abs(Phi13)<0.028";
//TCut etaBarrel	= "abs(log(1/tan(0.5*atan2(R03,Z3))) - log(1/tan(0.5*atan2(R01,Z1))))< 0.01";
TCut eta13EC	= "abs(Eta3 - Eta1)<0.009";
TCut maxdphi2	= "abs(dphi2)<1.0e-3";
//TCut maxdz2	= "abs(dz2)<0.15*(sin(Theta13)^(-1.1))";
TCut maxdeta2   = "abs(Eta2-0.5*(Eta1+Eta3))<1e-3";
const float dz2_exp   = -1.1;
const float dz2_const = 0.15;
//! 
TCut kapcut_l =  "abs(kappa_pull) < 5 ";
TCut kapcut   =  "abs(kappa_pull) < 4 ";
TCut kapcut_t =  "abs(kappa_pull) < 3 ";

TCut station    = "abs(station) == 1";
TCut matched	= "Tid>0";
TCut fakes	= "Tid ==-1";
TCut minPt	= "Pt_n > 2e3 && abs(Eta13)<2.5";
TCut minPt_t	= "M_pt > 2e3 && abs(M_eta)<2.5";
TCut truth_m	= "M_pt < 20e3";
TCut recon_m	= "Pt_n < 20e3";
TCut pion	= "abs(M_pdg) == 211";
TCut muon	= "abs(M_pdg) == 13";
TCut electron	= "abs(M_pdg) == 11";
TCut noelectron = "abs(M_pdg) != 11";
TCut z0truthmax	= "abs(M_Vz)<100 && abs(M_Vx)<10 && abs(M_Vy)<10";//! depends on the luminous region along z
TCut z0recmax	= "abs(Z013)<100";
