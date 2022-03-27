
////******* macro calculating the purity of the reconstructed tracks and contains all the relevant cuts *********//////
/// p = #reconstructed(cut + matched)/#reconstructed(cut)
/// here cut is applied on the reconstructed parameters both in the numerator and the denominator

#include "newcontrol_EC.h"
#include "newcontrol_EC_cuts.h"
#include "SetControlHisto_Props.cpp"
void bookHistograms()
{
	
	h1  = new TH2F("h1", "p_{T} Vs Phi_{13}; Phi_{13}; p_{T} [MeV/c]", nbins, phi_min, phi_max, nbins, pt_min, pt_max); 	
	h2  = new TH2F("h2", "p_{T} Vs Phi_{13}; Phi_{13}; p_{T} [MeV/c]", nbins, phi_min, phi_max, nbins, pt_min, pt_max); 	
	h4  = new TH2F("h4", "p_{T} Vs Phi_{13}; Phi_{13}; p_{T} [MeV/c]", nbins, phi_min, phi_max, nbins, pt_min, pt_max); 	
	h6  = new TH2F("h6", "p_{T} Vs Phi_{13}; Phi_{13}; p_{T} [MeV/c]", nbins, phi_min, phi_max, nbins, pt_min, pt_max); 	
	
	h7  = new TH2F("h7", "p_{Trec} Vs p_{T}; p_{T} [MeV/c]; p_{Trec}", nbins, pt_min,  pt_max,  nbins, pt_min, pt_max); 	
	h8  = new TH2F("h8", "p_{Trec} Vs p_{T}; p_{T} [MeV/c]; p_{Trec}", nbins, pt_min,  pt_max,  nbins, pt_min, pt_max); 	
	h9  = new TH2F("h9", "p_{Trec} Vs p_{T}; p_{T} [MeV/c]; p_{Trec}", nbins, pt_min,  pt_max,  nbins, pt_min, pt_max); 	
	h10 = new TH2F("h10","p_{Trec} Vs p_{T}; p_{T} [MeV/c]; p_{Trec}", nbins, pt_min,  pt_max,  nbins, pt_min, pt_max);
 
	h3  = new TH1F("h3", "#eta_{13}; #eta_{13}", nbins, deta2_min, deta2_max); 
	h11 = new TH2F("h11","p_{T} Vs #eta_{13}; #eta_{13}; p_{T} [MeV/c];", nbins, deta2_min, deta2_max, nbins, pt_min, pt_max); 		
	h5  = new TH1F("h5", "d#eta_{2}; d#eta_{2}", nbins, deta2_min, deta2_max); 
	h5a = new TH1F("h5a","d#eta_{2}; d#eta_{2}^{fakes}", nbins, deta2_min, deta2_max); 	
	
	h12 = new TH2F("h12","Z_{013} Vs dphi_{2}; dphi_{2}; Z_{013} [mm]", nbins, dphi2_min, dphi2_max, nbins, z0_min, z0_max); 	
	h13 = new TH2F("h13","Z_{013} Vs dphi_{2}; dphi_{2}; Z_{013} [mm]", nbins, dphi2_min, dphi2_max, nbins, z0_min, z0_max); 	
	h14 = new TH2F("h14","M_{vz}  Vs dphi_{2}; dphi_{2}; M_{Vz}  [mm]", nbins, dphi2_min, dphi2_max, nbins, z0_min, z0_max); 	
	h14a= new TH1F("h14a","dphi_{2}; dphi_{2}", nbins, dphi2_min, dphi2_max); 

	h15 = new TH2F("h15","Z_{013} Vs dr_{2}; dr_{2} [mm]; Z_{013} [mm]", nbins, dr2_min, dr2_max, nbins, z0_min, z0_max); 	
	h16 = new TH2F("h16","Z_{013} Vs dr_{2}; dr_{2} [mm]; Z_{013} [mm]", nbins, dr2_min, dr2_max, nbins, z0_min, z0_max); 	
	h17 = new TH2F("h17","M_{vz}  Vs dr_{2}; dr_{2} [mm]; M_{Vz}  [mm]", nbins, dr2_min, dr2_max, nbins, z0_min, z0_max); 
	h17a= new TH1F("h17a","dr_{2}; dr_{2} [mm]", nbins, dr2_min, dr2_max); 
	
	h18 = new TH2F("h18","dphi_{2} Vs Theta_{13}; Theta_{13}; dphi_{2}", nbins, theta_min, theta_max, nbins, dphi2_min, dphi2_max);
	h19 = new TH2F("h19","dphi_{2} Vs Theta_{13}; Theta_{13}; dphi_{2}", nbins, theta_min, theta_max, nbins, dphi2_min, dphi2_max); 	
	h20 = new TH2F("h20","dphi_{2} Vs M_{theta}; M_{theta};   dphi_{2}", nbins, theta_min, theta_max, nbins, dphi2_min, dphi2_max); 	
	
	h21 = new TH2F("h21","dr_{2} Vs Theta_{13};  Theta_{13};  dr_{2}",   nbins, theta_min, theta_max, nbins, dr2_min, dr2_max);
	h22 = new TH2F("h22","dr_{2} Vs Theta_{13};  Theta_{13};  dr_{2}",   nbins, theta_min, theta_max, nbins, dr2_min, dr2_max);
	h23 = new TH2F("h23","dr_{2} Vs M_{theta};   M_{theta};   dr_{2}",   nbins, theta_min, theta_max, nbins, dr2_min, dr2_max);

	th22 = new TH1F("th22","Theta_{13}; Theta_{13}", nbins, theta_min, theta_max);
	th23 = new TH1F("th23","M_{theta};  M_{theta}",   nbins, theta_min, theta_max);

	th24 = new TH2F("th24", "radial_gapsize vs d#kappa; d#kappa [mm^{-1}]; radial_gapsize [mm]", nbins, k013_min, k013_max, nbins, 5, 60 ); 	
	th25a= new TH2F("th25a","radial_gapsize vs d#kappa; d#kappa [mm^{-1}]; radial_gapsize [mm]", nbins, k013_min, k013_max, nbins, 5, 60 ); 	
	th25 = new TH2F("th25", "pixel_width vs d#kappa; d#kappa [mm^{-1}]; pixel_width [mm]", nbins, k013_min, k013_max, nbins, 0, 6e-2 ); 	
	th26 = new TH2F("th26", "pixel_width vs d#kappa; d#kappa [mm^{-1}]; pixel_width [mm]", nbins, k013_min, k013_max, nbins, 0, 6e-2 ); 	
	
	h27 = new TH1F("h27", "dphi_{2}, matched, loose pre-sel; dphi_{2}", nbins, dphi2_min, dphi2_max); 	
	h28a= new TH1F("h28a","dphi_{2}, matched, w/ sig kap= 5; dphi_{2}", nbins, dphi2_min*1e-1, dphi2_max*1e-1); 	
	h28 = new TH1F("h28", "deta_{2}, matched, loose pre-sel; deta_{2}", nbins, deta2_min, deta2_max); 	
	h29 = new TH1F("h29", "deta_{2}, matched, w/ sig kap= 5; deta_{2}", nbins, deta2_min*1e-1, deta2_max*1e-1);
	
	th27 = new TH1F("th27", "dphi_{2}, fakes, loose pre-sel; dphi_{2}", nbins, dphi2_min, dphi2_max); 	
	th28a= new TH1F("th28a","dphi_{2}, fakes, w/ sig kap= 5; dphi_{2}", nbins, dphi2_min, dphi2_max); 	
	th28 = new TH1F("th28", "deta_{2}, fakes, loose pre-sel; deta_{2}", nbins, deta2_min, deta2_max); 	
	th29 = new TH1F("th29", "deta_{2}, fakes, w/ sig kap= 5; deta_{2}", nbins, deta2_min, deta2_max);

	h24  = new TH2F("h24",  "abs(dphi_{2}) Vs sin(Theta_{13}); sin(Theta_{13}); abs(dphi_{2})", nbins, sinTheta_min, sinTheta_max, nbins, 0, dphi2_max); 	
	h25a = new TH2F("h25a", "abs(dphi_{2}) Vs sin(Theta_{13}); sin(Theta_{13}); abs(dphi_{2})", nbins, sinTheta_min, sinTheta_max, nbins, 0, dphi2_max); 	
	h25  = new TH2F("h25",  "abs(dphi_{2}) Vs sin(Theta_{13}); sin(Theta_{13}); abs(dphi_{2})", nbins, sinTheta_min, sinTheta_max, nbins, 0, dphi2_max); 	
	h26  = new TH2F("h26",  "abs(dphi_{2}) Vs sin(M_{theta});  sin(M_{theta});  abs(dphi_{2})", nbins, sinTheta_min, sinTheta_max, nbins, 0, dphi2_max); 	
	h_24 = new TH2F("h_24", "abs(dphi_{2}) Vs sin(Theta_{13}); sin(Theta_{13}); abs(dphi_{2})", nbins, sinTheta_min, sinTheta_max, nbins, 0, dphi2_max); 	
	h_25a= new TH2F("h_25a","abs(dphi_{2}) Vs sin(Theta_{13}); sin(Theta_{13}); abs(dphi_{2})", nbins, sinTheta_min, sinTheta_max, nbins, 0, dphi2_max); 	
	h_25 = new TH2F("h_25", "abs(dphi_{2}) Vs sin(Theta_{13}); sin(Theta_{13}); abs(dphi_{2})", nbins, sinTheta_min, sinTheta_max, nbins, 0, dphi2_max); 	
	h_26 = new TH2F("h_26", "abs(dphi_{2}) Vs sin(M_{theta});  sin(M_{theta});  abs(dphi_{2})", nbins, sinTheta_min, sinTheta_max, nbins, 0, dphi2_max); 	
	
	h_27 = new TH2F("h_27", "dr_{2} Vs sin(Theta_{13}); sin(Theta_{13}); dr_{2}", nbins, sinTheta_min, sinTheta_max, nbins, dr2_min, dr2_max); 	
	h_28a= new TH2F("h_28a","dr_{2} Vs sin(Theta_{13}); sin(Theta_{13}); dr_{2}", nbins, sinTheta_min, sinTheta_max, nbins, dr2_min, dr2_max); 	
	h_28 = new TH2F("h_28", "dr_{2} Vs sin(Theta_{13}); sin(Theta_{13}); dr_{2}", nbins, sinTheta_min, sinTheta_max, nbins, dr2_min, dr2_max); 	
	h_29 = new TH2F("h_29", "dr_{2} Vs sin(M_{theta});  sin(M_{theta});  dr_{2}", nbins, sinTheta_min, sinTheta_max, nbins, dr2_min, dr2_max);

	h30 = new TH2F("h30","#kappa_{013} Vs #kappa_{pull};d#kappa/#sigma_{#kappa};#kappa_{013} [mm^{-1}]", nbins, -10, 10, nbins, k013_min, k013_max); 	
	h31 = new TH2F("h31","#kappa_{013} Vs #kappa_{pull};d#kappa/#sigma_{#kappa};#kappa_{013} [mm^{-1}]", nbins, -10, 10, nbins, k013_min, k013_max); 	
	h32 = new TH2F("h32","#kappa_{013} Vs #kappa_{pull};d#kappa/#sigma_{#kappa};#kappa_{013} [mm^{-1}]", nbins, -10, 10, nbins, k013_min, k013_max); 
	h36 = new TH2F("h36","#kappa_{013} Vs #kappa_{pull};d#kappa/#sigma_{#kappa};#kappa_{013} [mm^{-1}]", nbins, -10, 10, nbins, k013_min, k013_max); 
	
	h33 = new TH2F("h33","|#eta_{013}| Vs #kappa_{pull};d#kappa/#sigma_{#kappa};|#eta_{013}|", nbins, -10, 10, nbins, theta_min, theta_max); 	
	h34 = new TH2F("h34","|#eta_{013}| Vs #kappa_{pull};d#kappa/#sigma_{#kappa};|#eta_{013}|", nbins, -10, 10, nbins, theta_min, theta_max); 	
	h35 = new TH2F("h35","|#eta_{013}| Vs #kappa_{pull};d#kappa/#sigma_{#kappa};|#eta_{013}|", nbins, -10, 10, nbins, theta_min, theta_max); 
	h37 = new TH2F("h37","|#eta_{013}| Vs #kappa_{pull};d#kappa/#sigma_{#kappa};|#eta_{013}|", nbins, -10, 10, nbins, theta_min, theta_max); 


/*	h36 = new TH2F("h36","kappa013^{2} Vs dkappa ;dkappa[mm^{-1}]; kap_{013}^{2}[mm^{-2}]", nbins,-0.7e-3,0.7e-3,nbins,0,2e-7);
	h37 = new TH2F("h37","kappa013^{2} Vs dkappa ;dkappa[mm^{-1}]; kap_{013}^{2}[mm^{-2}]", nbins,-0.7e-3,0.7e-3,nbins,0,2e-7);
	h38 = new TH2F("h38","kappa013^{2} Vs dkappa ;dkappa[mm^{-1}]; kap_{013}^{2}[mm^{-2}]", nbins,-0.7e-3,0.7e-3,nbins,0,2e-7);
	h39 = new TH2F("h39","kappa013^{2} Vs dkappa ;dkappa[mm^{-1}]; kap_{013}^{2}[mm^{-2}]", nbins,-0.7e-3,0.7e-3,nbins,0,2e-7);
	h40 = new TH2F("h40","kappa013^{2} Vs dkappa ;dkappa[mm^{-1}]; kap_{013}^{2}[mm^{-2}]", nbins,-0.7e-3,0.7e-3,nbins,0,2e-7);
	h41 = new TH2F("h41","kappa013^{2} Vs dkappa ;dkappa[mm^{-1}]; kap_{013}^{2}[mm^{-2}]", nbins,-0.7e-3,0.7e-3,nbins,0,2e-7);
*/
	th36 = new TH2F("th36","kappa013 Vs dkappa; dkappa[mm^{-1}]; kap_{013}[mm^{-1}]", nbins, k013_min, k013_max, nbins, k013_min, k013_max);
	th37 = new TH2F("th37","kappa013 Vs dkappa; dkappa[mm^{-1}]; kap_{013}[mm^{-1}]", nbins, k013_min, k013_max, nbins, k013_min, k013_max);
	th38 = new TH2F("th38","kappa013 Vs dkappa; dkappa[mm^{-1}]; kap_{013}[mm^{-1}]", nbins, k013_min, k013_max, nbins, k013_min, k013_max);
	th39 = new TH2F("th39","kappa013 Vs dkappa; dkappa[mm^{-1}]; kap_{013}[mm^{-1}]", nbins, k013_min, k013_max, nbins, k013_min, k013_max);
	th40 = new TH2F("th40","kappa013 Vs dkappa; dkappa[mm^{-1}]; kap_{013}[mm^{-1}]", nbins, k013_min, k013_max, nbins, k013_min, k013_max);
	th41 = new TH2F("th41","kappa013 Vs dkappa; dkappa[mm^{-1}]; kap_{013}[mm^{-1}]", nbins, k013_min, k013_max, nbins, k013_min, k013_max);
	
	h42 = new TH1F("h42","dca;dca [mm]", nbins, dca_min, dca_max);
	h43 = new TH1F("h43","dca;dca [mm]", nbins, dca_min, dca_max);
	h44 = new TH1F("h44","dca;dca [mm]", nbins, dca_min, dca_max);

	h45 = new TH2F("h45","p_{T} Vs dca; dca [mm]; p_{T} [MeV/c]", nbins, dca_min, dca_max, nbins, pt_min, pt_max);
	h46 = new TH2F("h46","p_{T} Vs dca; dca [mm]; p_{T} [MeV/c]", nbins, dca_min, dca_max, nbins, pt_min, pt_max);
	h47 = new TH2F("h47","p_{T} Vs dca; dca [mm]; p_{T} [MeV/c]", nbins, dca_min, dca_max, nbins, pt_min, pt_max);
	h48 = new TH2F("h48","p_{T} Vs dca; dca [mm]; p_{T} [MeV/c]", nbins, dca_min, dca_max, nbins, pt_min, pt_max);
	h49 = new TH2F("h49","p_{T} Vs dca; dca [mm]; p_{T} [MeV/c]", nbins, dca_min, dca_max, nbins, pt_min, pt_max);
	h50 = new TH2F("h50","p_{T} Vs dca; dca [mm]; p_{T} [MeV/c]", nbins, dca_min, dca_max, nbins, pt_min, pt_max);
	h51 = new TH2F("h51","p_{T} Vs dca; dca [mm]; p_{T} [MeV/c]", nbins, dca_min, dca_max, nbins, pt_min, pt_max);
	h52 = new TH2F("h52","p_{T} Vs dca; dca [mm]; p_{T} [MeV/c]", nbins, dca_min, dca_max, nbins, pt_min, pt_max);
	h53 = new TH2F("h53","p_{T} Vs dca; dca [mm]; p_{T} [MeV/c]", nbins, dca_min, dca_max, nbins, pt_min, pt_max);
	
	h54 = new TH2F("h54","Z_{0} Vs dca; dca [mm]; Z_{0} [mm]", nbins, dca_min, dca_max, nbins, z0_min, z0_max);
	h55 = new TH2F("h55","Z_{0} Vs dca; dca [mm]; Z_{0} [mm]", nbins, dca_min, dca_max, nbins, z0_min, z0_max);
	h56 = new TH2F("h56","Z_{0} Vs dca; dca [mm]; Z_{0} [mm]", nbins, dca_min, dca_max, nbins, z0_min, z0_max);
	h57 = new TH2F("h57","Z_{0} Vs dca; dca [mm]; Z_{0} [mm]", nbins, dca_min, dca_max, nbins, z0_min, z0_max);
	h58 = new TH2F("h58","Z_{0} Vs dca; dca [mm]; Z_{0} [mm]", nbins, dca_min, dca_max, nbins, z0_min, z0_max);
	h59 = new TH2F("h59","Z_{0} Vs dca; dca [mm]; Z_{0} [mm]", nbins, dca_min, dca_max, nbins, z0_min, z0_max);
	h60 = new TH2F("h60","Z_{0} Vs dca; dca [mm]; Z_{0} [mm]", nbins, dca_min, dca_max, nbins, z0_min, z0_max);
	h61 = new TH2F("h61","Z_{0} Vs dca; dca [mm]; Z_{0} [mm]", nbins, dca_min, dca_max, nbins, z0_min, z0_max);
	h62 = new TH2F("h62","Z_{0} Vs dca; dca [mm]; Z_{0} [mm]", nbins, dca_min, dca_max, nbins, z0_min, z0_max);
	//! dca -> e,mu,pi for fakes,truth,rec tracks and for before and after kappa cut
	h63 = new TH1F("h63","dca; dca [mm]", nbins, dca_min, dca_max);
//	h64 = new TH1F("h64","dca; dca [mm]", nbins,-200,850);
//	h65 = new TH1F("h65","dca; dca [mm]", nbins,-200,850);
	h66 = new TH1F("h66","dca; dca [mm]", nbins, dca_min, dca_max);
	h67 = new TH1F("h67","dca; dca [mm]", nbins, dca_min, dca_max);
	h68 = new TH1F("h68","dca; dca [mm]", nbins, dca_min, dca_max);
	h69 = new TH1F("h69","dca; dca [mm]", nbins, dca_min, dca_max);
	h70 = new TH1F("h70","dca; dca [mm]", nbins, dca_min, dca_max);
	h71 = new TH1F("h71","dca; dca [mm]", nbins, dca_min, dca_max);
	h72 = new TH1F("h72","dca; dca [mm]", nbins, dca_min, dca_max);
//	h73 = new TH1F("h73","dca; dca [mm]", nbins,-200,850);
//	h74 = new TH1F("h74","dca; dca [mm]", nbins,-200,850);
	h75 = new TH1F("h75","dca; dca [mm]", nbins, dca_min, dca_max);
	h76 = new TH1F("h76","dca; dca [mm]", nbins, dca_min, dca_max);
	h77 = new TH1F("h77","dca; dca [mm]", nbins, dca_min, dca_max);
	h78 = new TH1F("h78","dca; dca [mm]", nbins, dca_min, dca_max);
	h79 = new TH1F("h79","dca; dca [mm]", nbins, dca_min, dca_max);
	h80 = new TH1F("h80","dca; dca [mm]", nbins, dca_min, dca_max);
	//! dz2 -> e,mu,pi for fakes,truth,rec tracks and for before and after kappa cut
	h81 = new TH1F("h81","dz_{2}; dz_{2} [mm]", nbins, deta2_min, deta2_max);
//	h82 = new TH1F("h82","dz_{2}; dz_{2} [mm]", nbins, deta2_min, deta2_max);
//	h83 = new TH1F("h83","dz_{2}; dz_{2} [mm]", nbins, deta2_min, deta2_max);
	h84 = new TH1F("h84","dz_{2}; dz_{2} [mm]", nbins, deta2_min, deta2_max);
	h85 = new TH1F("h85","dz_{2}; dz_{2} [mm]", nbins, deta2_min, deta2_max);
	h86 = new TH1F("h86","dz_{2}; dz_{2} [mm]", nbins, deta2_min, deta2_max);
	h87 = new TH1F("h87","dz_{2}; dz_{2} [mm]", nbins, deta2_min, deta2_max);
	h88 = new TH1F("h88","dz_{2}; dz_{2} [mm]", nbins, deta2_min, deta2_max);
	h89 = new TH1F("h89","dz_{2}; dz_{2} [mm]", nbins, deta2_min, deta2_max);
	h90 = new TH1F("h90","dz_{2}; dz_{2} [mm]", nbins, deta2_min, deta2_max);
//	h91 = new TH1F("h91","dz_{2}; dz_{2} [mm]", nbins, deta2_min, deta2_max);
//	h92 = new TH1F("h92","dz_{2}; dz_{2} [mm]", nbins, deta2_min, deta2_max);
	h93 = new TH1F("h93","dz_{2}; dz_{2} [mm]", nbins, deta2_min, deta2_max);
	h94 = new TH1F("h94","dz_{2}; dz_{2} [mm]", nbins, deta2_min, deta2_max);
	h95 = new TH1F("h95","dz_{2}; dz_{2} [mm]", nbins, deta2_min, deta2_max);
	h96 = new TH1F("h96","dz_{2}; dz_{2} [mm]", nbins, deta2_min, deta2_max);
	h97 = new TH1F("h97","dz_{2}; dz_{2} [mm]", nbins, deta2_min, deta2_max);
	h98 = new TH1F("h98","dz_{2}; dz_{2} [mm]", nbins, deta2_min, deta2_max);
	//! dkappa -> e,mu,pi for fakes,truth,rec tracks and for before and after kappa cut
	h99 = new TH1F("h99", "d#kappa; d#kappa [mm^{-1}]", nbins,-9e-3,9e-3);
//	h100= new TH1F("h100","d#kappa; d#kappa [mm^{-1}]", nbins, k013_min, k013_max);
//	h101= new TH1F("h101","d#kappa; d#kappa [mm^{-1}]", nbins, k013_min, k013_max);
	h102= new TH1F("h102","d#kappa; d#kappa [mm^{-1}]", nbins, k013_min, k013_max);
	h103= new TH1F("h103","d#kappa; d#kappa [mm^{-1}]", nbins, k013_min, k013_max);
	h104= new TH1F("h104","d#kappa; d#kappa [mm^{-1}]", nbins, k013_min, k013_max);
	h105= new TH1F("h105","d#kappa; d#kappa [mm^{-1}]", nbins, k013_min, k013_max);
	h106= new TH1F("h106","d#kappa; d#kappa [mm^{-1}]", nbins, k013_min, k013_max);
	h107= new TH1F("h107","d#kappa; d#kappa [mm^{-1}]", nbins, k013_min, k013_max);
	h108= new TH1F("h108","d#kappa; d#kappa [mm^{-1}]", nbins, k013_min, k013_max);
//	h109= new TH1F("h109","d#kappa; d#kappa [mm^{-1}]", nbins, k013_min, k013_max);
//	h110= new TH1F("h110","d#kappa; d#kappa [mm^{-1}]", nbins, k013_min, k013_max);
	h111= new TH1F("h111","d#kappa; d#kappa [mm^{-1}]", nbins, k013_min, k013_max);
	h112= new TH1F("h112","d#kappa; d#kappa [mm^{-1}]", nbins, k013_min, k013_max);
	h113= new TH1F("h113","d#kappa; d#kappa [mm^{-1}]", nbins, k013_min, k013_max);
	h114= new TH1F("h114","d#kappa; d#kappa [mm^{-1}]", nbins, k013_min, k013_max);
	h115= new TH1F("h115","d#kappa; d#kappa [mm^{-1}]", nbins, k013_min, k013_max);
	h116= new TH1F("h116","d#kappa; d#kappa [mm^{-1}]", nbins, k013_min, k013_max);

	h117= new TH1F("h117","kappa truth; #kappa_{truth} [mm^{-1}]", nbins,-5e-3,5e-3);
	h118= new TH1F("h118","kappa rec with bml constraint; #kappa_{013} [mm^{-1}]", nbins,-5e-3,5e-3);
	h119= new TH1F("h119","kappa rec w/o bml constraint; #kappa_{123} [mm^{-1}]", nbins,-0.7e-2,0.7e-2);
                       
	h120= new TH2F("h120","#kappa_{013} Vs #kappa_{truth}; #kappa_{truth} [mm^{-1}]; #kappa_{013} [mm^{-1}]", nbins, kTru_min, kTru_max, nbins, k013_min, k013_max);
	h121= new TH2F("h121","#kappa_{013} Vs #kappa_{truth}; #kappa_{truth} [mm^{-1}]; #kappa_{013} [mm^{-1}]", nbins, kTru_min, kTru_max, nbins, k013_min, k013_max);
	h122= new TH2F("h122","#kappa_{013} Vs #kappa_{truth}; #kappa_{truth} [mm^{-1}]; #kappa_{013} [mm^{-1}]", nbins, kTru_min, kTru_max, nbins, k013_min, k013_max);
	h123= new TH2F("h123","#kappa_{013} Vs #kappa_{truth}; #kappa_{truth} [mm^{-1}]; #kappa_{013} [mm^{-1}]", nbins, kTru_min, kTru_max, nbins, k013_min, k013_max);
	h124= new TH2F("h124","#kappa_{123} Vs #kappa_{truth}; #kappa_{truth} [mm^{-1}]; #kappa_{123} [mm^{-1}]", nbins, kTru_min, kTru_max, nbins, k123_min, k123_max);
	h125= new TH2F("h125","#kappa_{123} Vs #kappa_{truth}; #kappa_{truth} [mm^{-1}]; #kappa_{123} [mm^{-1}]", nbins, kTru_min, kTru_max, nbins, k123_min, k123_max);
	h126= new TH2F("h126","#kappa_{123} Vs #kappa_{truth}; #kappa_{truth} [mm^{-1}]; #kappa_{123} [mm^{-1}]", nbins, kTru_min, kTru_max, nbins, k123_min, k123_max);
	h127= new TH2F("h127","#kappa_{123} Vs #kappa_{truth}; #kappa_{truth} [mm^{-1}]; #kappa_{123} [mm^{-1}]", nbins, kTru_min, kTru_max, nbins, k123_min, k123_max);
	
	h128= new TH2F("h128","#kappa_{013} Vs #kappa_{123}; #kappa_{123} [mm^{-1}]; #kappa_{013}", nbins, k123_min, k123_max, nbins, k013_min, k013_max);
	h129= new TH2F("h129","#kappa_{013} Vs #kappa_{123}; #kappa_{123} [mm^{-1}]; #kappa_{013}", nbins, k123_min, k123_max, nbins, k013_min, k013_max);
	h130= new TH2F("h130","#kappa_{013} Vs #kappa_{123}; #kappa_{123} [mm^{-1}]; #kappa_{013}", nbins, k123_min, k123_max, nbins, k013_min, k013_max);
	h131= new TH2F("h131","#kappa_{013} Vs #kappa_{123}; #kappa_{123} [mm^{-1}]; #kappa_{013}", nbins, k123_min, k123_max, nbins, k013_min, k013_max);
                       
	h132= new TH1F("h132","#kappa_{013}/#kappa_{truth}; #kappa_{013}/#kappa_{truth}", nbins, k013Ratio_min, k013Ratio_max);
	h133= new TH1F("h133","#kappa_{013}/#kappa_{truth}; #kappa_{013}/#kappa_{truth}", nbins, k013Ratio_min, k013Ratio_max);
	h134= new TH1F("h134","#kappa_{013}/#kappa_{truth}; #kappa_{013}/#kappa_{truth}", nbins, k013Ratio_min, k013Ratio_max);
	h135= new TH1F("h135","#kappa_{013}/#kappa_{truth}; #kappa_{013}/#kappa_{truth}", nbins, k013Ratio_min, k013Ratio_max);
	
	h136= new TH1F("h136","#kappa_{123}/#kappa_{truth}; #kappa_{123}/#kappa_{truth}", nbins, k123Ratio_min, k123Ratio_max);
	h137= new TH1F("h137","#kappa_{123}/#kappa_{truth}; #kappa_{123}/#kappa_{truth}", nbins, k123Ratio_min, k123Ratio_max);
	h138= new TH1F("h138","#kappa_{123}/#kappa_{truth}; #kappa_{123}/#kappa_{truth}", nbins, k123Ratio_min, k123Ratio_max);
	h139= new TH1F("h139","#kappa_{123}/#kappa_{truth}; #kappa_{123}/#kappa_{truth}", nbins, k123Ratio_min, k123Ratio_max);
                       
	h140= new TH2F("h140","d#kappa Vs r; r [mm]; d#kappa [mm^{-1}]", nbins,0,850, nbins, k013_min, k013_max);
	h141= new TH2F("h141","d#kappa Vs r; r [mm]; d#kappa [mm^{-1}]", nbins,0,850, nbins, k013_min, k013_max);
	h142= new TH2F("h142","d#kappa Vs r; r [mm]; d#kappa [mm^{-1}]", nbins,0,850, nbins, k013_min, k013_max);
	h143= new TH2F("h143","d#kappa Vs r; r [mm]; d#kappa [mm^{-1}]", nbins,0,850, nbins, k013_min, k013_max);
	
	h144= new TH2F("h144","#kappa_{013}/#kappa_{truth} Vs r; r [mm]; #kappa_{013}/#kappa_{truht}", nbins, r_min, r_max, nbins, k013Ratio_min, k013Ratio_max);
	h145= new TH2F("h145","#kappa_{013}/#kappa_{truth} Vs r; r [mm]; #kappa_{013}/#kappa_{truht}", nbins, r_min, r_max, nbins, k013Ratio_min, k013Ratio_max);
	h146= new TH2F("h146","#kappa_{013}/#kappa_{truth} Vs r; r [mm]; #kappa_{013}/#kappa_{truht}", nbins, r_min, r_max, nbins, k013Ratio_min, k013Ratio_max);
	h147= new TH2F("h147","#kappa_{013}/#kappa_{truth} Vs r; r [mm]; #kappa_{013}/#kappa_{truht}", nbins, r_min, r_max, nbins, k013Ratio_min, k013Ratio_max);
	return;
}
void newcontrol
(
	//const char* output_file_name = "control_PEC_mupt2_10GeV",//f-few
	const char* output_file_name = "control_ggF1.0_PU1k_EC67foropt_3",//f-few
	//const char* output_file_name = "control_MB_PU1k_EC67sel_3",//f-few
	const char* set = "C",
	const bool verbose = true
)
{
	//Open a list of root files and get reconstructed tree
	TChain rec("m_recTree");
	rec.Add("/user/tkar/work/data/rec/for_opt/Br30mmEC67mm/PU1k/ggF1.0/*.root");
	//rec.Add("/user/tkar/work/data/rec/opt/Br30mmEC106mm/ggF1.0/user.tkar_*.root");
	//rec.Add("/user/tkar/work/data/rec/sel/Br30mmEC67mm/PU1k/ggF1.0/user.tkar_*.root");
	TF1 *fdz2 = new TF1("fdz2", "[0]*(x)^[1]",0.16,1.05);
	fdz2->SetParameter(0,dz2_const);
	fdz2->SetParameter(1,dz2_exp);
	fdz2->SetLineColor(kBlack);
	TF1 *fdz2_ = new TF1("fdz2_", "[0]*(x)^[1]",0.16,1.05);
	fdz2_->SetParameter(0,-1*dz2_const);
	fdz2_->SetParameter(1,dz2_exp);
	fdz2_->SetLineColor(kBlack);


	//! number of points in the plots
	//int num_events = 250;//1e5;
	int num_events = rec.GetEntries();
	num_events = 200;

	int etabin = 31;
        double etamin =-2.6, etamax = 2.6;
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
	bookHistograms();
	SetControlHisto_Props();

	TH1* h_num_vs_etaPU = new TH1F("h_num_vs_etaPU", "Numerator Count vs #eta;#eta;Numerator Count"    , etabin, etamin, etamax);
        TH1* h_den_vs_etaPU = new TH1F("h_den_vs_etaPU", "Denominator Count vs #eta;#eta;Denominator Count", etabin, etamin, etamax);

	TH1* h_num_vs_ptPU = new TH1F("h_num_vs_ptPU", "Numerator Count vs p_{T};p_{T} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_ptPU = new TH1F("h_den_vs_ptPU", "Denominator Count vs p_{T};p_{T} [MeV/c];Denominator Count", ptbins, xbins);
			
	TH1* h_num_vs_eta_ = new TH1F("h_num_vs_eta_", "Numerator Count vs #eta;#eta;Numerator Count"    , etabin, etamin, etamax);
        TH1* h_den_vs_eta_ = new TH1F("h_den_vs_eta_", "Denominator Count vs #eta;#eta;Denominator Count", etabin, etamin, etamax);

	TH1* h_num_vs_pt_ = new TH1F("h_num_vs_pt_", "Numerator Count vs p_{T};p_{T} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_pt_ = new TH1F("h_den_vs_pt_", "Denominator Count vs p_{T};p_{T} [MeV/c];Denominator Count", ptbins, xbins);
	
	TH1* h_num_vs_eta_l = new TH1F("h_num_vs_eta_l", "Numerator Count vs #eta;#eta;Numerator Count"    , etabin, etamin, etamax);
        TH1* h_den_vs_eta_l = new TH1F("h_den_vs_eta_l", "Denominator Count vs #eta;#eta;Denominator Count", etabin, etamin, etamax);

	TH1* h_num_vs_pt_l = new TH1F("h_num_vs_pt_l", "Numerator Count vs p_{T};p_{T} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_pt_l = new TH1F("h_den_vs_pt_l", "Denominator Count vs p_{T};p_{T} [MeV/c];Denominator Count", ptbins, xbins);
	

	TH1* h_num_vs_eta_m = new TH1F("h_num_vs_eta_m", "Numerator Count vs #eta;#eta;Numerator Count"    , etabin, etamin, etamax);
        TH1* h_den_vs_eta_m = new TH1F("h_den_vs_eta_m", "Denominator Count vs #eta;#eta;Denominator Count", etabin, etamin, etamax);

	TH1* h_num_vs_pt_m = new TH1F("h_num_vs_pt_m", "Numerator Count vs p_{T};p_{T} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_pt_m = new TH1F("h_den_vs_pt_m", "Denominator Count vs p_{T};p_{T} [MeV/c];Denominator Count", ptbins, xbins);
	
	TH1* h_num_vs_eta_t = new TH1F("h_num_vs_eta_t", "Numerator Count vs #eta;#eta;Numerator Count"    , etabin, etamin, etamax);
        TH1* h_den_vs_eta_t = new TH1F("h_den_vs_eta_t", "Denominator Count vs #eta;#eta;Denominator Count", etabin, etamin, etamax);

	TH1* h_num_vs_pt_t = new TH1F("h_num_vs_pt_t", "Numerator Count vs p_{T};p_{T} [MeV/c];Numerator Count"    , ptbins, xbins);
	TH1* h_den_vs_pt_t = new TH1F("h_den_vs_pt_t", "Denominator Count vs p_{T};p_{T} [MeV/c];Denominator Count", ptbins, xbins);
	

	std::cout<<"num events : " <<num_events <<"\n";
	TCanvas *C =new TCanvas();
	
	//! page1
	//***
	// 1. truth pT vs phi13 (w/o phi13 cut)
	// 2. truth pT vs phi13 (w/ phi13 cut)
	// 3. rec and matched pT vs phi13
	// 4. rec and fake pT vs phi13
	rec.Draw("M_pt:Phi13>>h1",station && matched && truth_m,"",num_events);
	rec.Draw("M_pt:Phi13>>h2",station && matched && truth_m && phi13EC,"same",num_events);
	rec.Draw("Pt_n:Phi13>>h4",station && matched && recon_m,"same",num_events);
	rec.Draw("Pt_n:Phi13>>h6",station && fakes && recon_m,"same",num_events);
	
	//! compare truth and reconstructed Pt for matched tracks and for different particles
	//! ideally should be a straight line with slope 1
	//! disagreement seen in the low pt region -> explains multiple scattering
	//! page2
	//***
	// 1. rec pT vs truth pT : all particles
	// 2. rec pT vs truth pT : pions
	// 3. rec pT vs truth pT : electrons
	// 4. rec pT vs truth pT : muons
	rec.Draw("Pt_n:M_pt>>h7",station && matched && truth_m && recon_m,"",num_events);
        rec.Draw("Pt_n:M_pt>>h8",station && matched && truth_m && recon_m && pion,"same",num_events);
        rec.Draw("Pt_n:M_pt>>h9",station && matched && truth_m && recon_m && electron,"same",num_events);
        rec.Draw("Pt_n:M_pt>>h10",station && matched && truth_m && recon_m && muon,"same"/*,num_events*/);

	//! page3
	// 1. eta3 - eta1 dist. for matched tracks
	// 2. rec pT vs eta3 - eta1 for matched tracks
	// 3. d_eta2 distribution for matched tracks
	// 4. d_eta2 distribution for fake tracks
	rec.Draw("Eta3 - Eta1>>h3",station && matched && phi13EC,"",num_events);
	rec.Draw("Pt_n:Eta3 - Eta1>>h11",station && matched && phi13EC,"",num_events);
	rec.Draw("Eta2 - 0.5*(Eta3 + Eta1)>>h5", station && matched && phi13EC && eta13EC,"",num_events);
	rec.Draw("Eta2 - 0.5*(Eta3 + Eta1)>>h5a",station && fakes && phi13EC && eta13EC,"",num_events);

	//! page4
	// 1. rec z013 vs dphi2 : fakes
	// 2. rec z013 vs dphi2 : matched
	// 3. tru z0 vs dphi2
	// 4. dphi2 distibution : matched
	rec.Draw("Z013:dphi2>>h12",station &&  fakes && phi13EC && eta13EC && z0recmax,"",25);
	rec.Draw("Z013:dphi2>>h13",station && matched && phi13EC && eta13EC && z0recmax,"same",num_events);
	rec.Draw("M_Vz:dphi2>>h14",station && matched /*&& phi13EC && eta13EC*/ && z0truthmax,"same",num_events);
	rec.Draw("dphi2>>h14a",station && matched && phi13EC && eta13EC && z0recmax,"same",num_events);

	//! page5
	// 1. rec z013 vs dr2 :  fakes
	// 2. rec z013 vs dr2 :  matched
	// 3. truth z0 vs dr2
	// 4. dr2 distribution : matched
        rec.Draw("Z013:R02 - 0.5*(R01+R03)>>h15",station && fakes && phi13EC && eta13EC && z0recmax,"",25);
        rec.Draw("Z013:R02 - 0.5*(R01+R03)>>h16",station && matched && phi13EC && eta13EC && z0recmax,"same",num_events);
        rec.Draw("M_Vz:R02 - 0.5*(R01+R03)>>h17",station && matched /*&& phi13EC && eta13EC*/ && z0truthmax,"same",num_events);
	rec.Draw("R02 - 0.5*(R01+R03)>>h17a",station && matched && phi13EC && eta13EC && z0recmax,"same",num_events);

	//! page6
	// 1. dphi2 vs theta013 : fakes 
	// 2. dphi2 vs theta013 : matched
	// 3. dphi2 vs tru theta 
	// 4. deta2 dist : fakes (red) and matched (overlay)
        rec.Draw("dphi2:Theta13>>h18",station &&  fakes && minPt && phi13EC && eta13EC && z0recmax,"",num_events);
        rec.Draw("dphi2:Theta13>>h19",station && matched && minPt && phi13EC && eta13EC && z0recmax,"same",num_events);
        rec.Draw("dphi2:M_theta>>h20",station && matched && minPt_t /*&& phi13EC && eta13EC*/ && z0truthmax,"same",num_events);

	//! page7
	// 1. dr2 vs theta013 : fakes 
	// 2. dr2 vs theta013 : matched
	// 3. dr2 vs tru theta 
        rec.Draw("R02 - 0.5*(R01+R03):Theta13>>h21", station && fakes && minPt && phi13EC && eta13EC && z0recmax,"",num_events);
        rec.Draw("R02 - 0.5*(R01+R03):Theta13>>h22",station && matched && minPt && phi13EC && eta13EC && z0recmax,"same",num_events);
        rec.Draw("R02 - 0.5*(R01+R03):M_theta>>h23",station && matched && minPt_t /*&& phi13EC && eta13EC*/ && z0truthmax,"same",num_events);
        

	//! page8
	// 1. dphi2 vs sin(theta013) : fakes 
	// 2. dphi2 vs sin(theta013) : matched no electron
	// 3. dphi2 vs sin(theta013) : matched
	// 4. dphi2 vs tru sin(theta)
        rec.Draw("dphi2:sin(Theta13)>>h24",station &&  fakes && minPt && phi13EC && eta13EC && z0recmax,"",num_events);
        rec.Draw("dphi2:sin(Theta13)>>h25a",station && matched && minPt && phi13EC && eta13EC && z0recmax && noelectron,"same",num_events);
        rec.Draw("dphi2:sin(Theta13)>>h25",station && matched && minPt && phi13EC && eta13EC && z0recmax,"same",num_events);
        rec.Draw("dphi2:sin(M_theta)>>h26",station && matched && minPt_t /*&& phi13EC && eta13EC*/ && z0truthmax,"same",num_events);
	
	
	//! page9
	// 1. rec theta013 dist with l1l3 pre-selec. cuts
	// 2. tru theta dist.
	rec.Draw("Theta13>>th22",station && matched && minPt && phi13EC && eta13EC && z0recmax,"same",num_events);
        rec.Draw("M_theta>>th23",station && matched && minPt_t /*&& phi13EC && eta13EC*/ && z0truthmax,"same",num_events);
	
	//! page10
	// 1. radial_gapsize vs dkappa: truth cuts 
	// 2. pixel_width vs dkappa: truth cuts
	// 3. radial_gapsize vs dkappa: reco (loose pre-sel) cuts 
	// 4. pixel_width vs dkappa: reco (loose pre-sel) cuts
	rec.Draw("radial_gapsize:kappa-kap013>>th24", station && matched && minPt_t && z0truthmax,"same",num_events);
	rec.Draw("radial_gapsize:kappa-kap013>>th25a", station && matched && minPt && phi13EC && eta13EC && z0recmax,"same",num_events);
	rec.Draw("pixel_width:kappa-kap013>>th25", station && matched && minPt_t && z0truthmax,"same",num_events);
	rec.Draw("pixel_width:kappa-kap013>>th26", station && matched && minPt && phi13EC && eta13EC && z0recmax,"same",num_events);

	//!page11
	// 1. dphi2 : matched rec loose pre-selection
	// 2. dphi2 : matched rec w/ kappa cut w/o dphi2, deta2 cuts
	// 3. deta2 : matched rec loose pre-selection
	// 4. deta2 : matched rec w/ kappa cut w/o dphi2, deta2 cuts
	rec.Draw("dphi2>>h27", station && matched && minPt && phi13EC && eta13EC && z0recmax,"same",num_events);
	rec.Draw("dphi2>>h28a", station && matched && minPt && phi13EC && eta13EC && z0recmax && kapcut_l,"same",num_events);
	rec.Draw("Eta2 - 0.5*(Eta1+Eta3)>>h28", station && matched && minPt && phi13EC && eta13EC && z0recmax,"same",num_events);
	rec.Draw("Eta2 - 0.5*(Eta1+Eta3)>>h29", station && matched && minPt && phi13EC && eta13EC && z0recmax && kapcut_l,"same",num_events);
	//!page12
	// 1. dphi2 : fakes rec loose pre-selection
	// 2. dphi2 : fakes rec w/ kappa cut w/o dphi2, deta2 cuts
	// 3. deta2 : fakes rec loose pre-selection
	// 4. deta2 : fakes rec w/ kappa cut w/o dphi2, deta2 cuts
	rec.Draw("dphi2>>th27", station && fakes && minPt && phi13EC && eta13EC && z0recmax,"same",num_events);
	rec.Draw("dphi2>>th28a", station && fakes && minPt && phi13EC && eta13EC && z0recmax && kapcut_l,"same",num_events);
	rec.Draw("Eta2 - 0.5*(Eta1+Eta3)>>th28", station && fakes && minPt && phi13EC && eta13EC && z0recmax,"same",num_events);
	rec.Draw("Eta2 - 0.5*(Eta1+Eta3)>>th29", station && fakes && minPt && phi13EC && eta13EC && z0recmax && kapcut_l,"same",num_events);
	
	//! page13
	// 1. kappa013 vs kappa_pull : all truth cuts 
	// 2. kappa013 vs kappa_pull : all w/0 dphi2, deta2
	// 3. kappa013 vs kappa_pull : all with dphi2, deta2
	// 4. kappa013 vs kappa_pull : fakes with dphi2, deta2
	rec.Draw("kap013:kappa_pull>>h30",station && matched && minPt_t && z0truthmax,"same",num_events);
	rec.Draw("kap013:kappa_pull>>h31",station && matched && minPt && phi13EC && eta13EC && z0recmax,"same",num_events);
	rec.Draw("kap013:kappa_pull>>h32",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2,"same",num_events);
	rec.Draw("kap013:kappa_pull>>h36",station && fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2,"same",num_events);
	//! page14
	// 1. Eta013 vs Eta013 : all truth cuts 
	// 2. Eta013 vs Eta013 : all w/0 dphi2, deta2
	// 3. Eta013 vs Eta013 : all with dphi2, deta2
	// 4. Eta013 vs Eta013 : fakes with dphi2, deta2
	rec.Draw("Eta13:kappa_pull>>h33",station && matched && minPt_t && z0truthmax,"same",num_events);
	rec.Draw("Eta13:kappa_pull>>h34",station && matched && minPt && phi13EC && eta13EC && z0recmax,"same",num_events);
	rec.Draw("Eta13:kappa_pull>>h35",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2,"same",num_events);
	rec.Draw("Eta13:kappa_pull>>h37",station && fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2,"same",num_events);


	//rec.Draw("kap013^2:kappa-kap013>>h36",matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*dphi2max_l && dz2max_l*/,"",num_events);
	//rec.Draw("kap013^2:kappa-kap013>>h37",matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*dphi2max_l && dz2max_l*/ && pion,"same",num_events);
	//rec.Draw("kap013^2:kappa-kap013>>h38",matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*dphi2max_l && dz2max_l*/ && electron,"same",num_events);
	//rec.Draw("kap013^2:kappa-kap013>>h39",matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*dphi2max_l && dz2max_l*/ && noelectron,"same",num_events);
	//rec.Draw("kap013^2:kappa-kap013>>h40",matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*dphi2max_l && dz2max_l*/ && muon,"same"/*,num_events*/);
	//rec.Draw("kap013^2:kappa-kap013>>h41","Tid>0 && abs(M_Vz)<100 && abs(M_Vx)<15 && abs(M_Vy)<15 && abs(M_eta)<1.5 && abs(M_pt)>2e3","same",num_events);

	//! page15
	// 1. kappa013 vs dkappa :  truth
	// 2. kappa013 vs dkappa :  rec all
	// 3. kappa013 vs dkappa :  rec no electrons
	rec.Draw("kap013:kappa-kap013>>th36","station && Tid>0 && abs(M_Vz)<100 && abs(M_Vx)<10 && abs(M_Vy)<10 && abs(M_eta)<2.5 && abs(M_pt)>2e3","",num_events);
	rec.Draw("kap013:kappa-kap013>>th37",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*dphi2max_l && dz2max_l*/,"",num_events);
	rec.Draw("kap013:kappa-kap013>>th38",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*dphi2max_l && dz2max_l*/ && noelectron,"same",num_events);
	
	//! page16
	// 1. kappa013 vs dkappa :  rec loose
	// 2. kappa013 vs dkappa :  rec medium
	// 3. kappa013 vs dkappa :  rec tight
	// 4. kappa013 vs dkappa :  rec loose medium tight
	rec.Draw("kap013:kappa-kap013>>th39",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*dphi2max_l && dz2max_l*/ && kapcut_l,"same",num_events);
	rec.Draw("kap013:kappa-kap013>>th40",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*dphi2max_l && dz2max_l*/ && kapcut,"same",num_events);
	rec.Draw("kap013:kappa-kap013>>th41",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*dphi2max_l && dz2max_l*/ && kapcut_t,"same",num_events);

	//!dca distributions
	//! page17
	rec.Draw("dca>>h42",station && fakes && minPt && phi13EC && eta13EC && z0recmax,"", num_events);
	rec.Draw("dca>>h43",station && matched && minPt && phi13EC && eta13EC && z0recmax,"", num_events);
	rec.Draw("dca>>h44",station && matched && minPt_t && z0truthmax,"", num_events);

	//! pt vs dca
	//! page18
	rec.Draw("Pt_n:dca>>h45",station && fakes && minPt && recon_m && phi13EC && eta13EC && z0recmax,"", num_events);
	
	//! page19
	rec.Draw("Pt_n:dca>>h46",station && matched && minPt && recon_m && phi13EC && eta13EC && z0recmax,"", num_events);
	rec.Draw("Pt_n:dca>>h47",station && matched && minPt && recon_m && phi13EC && eta13EC && z0recmax && pion,"", num_events);
	rec.Draw("Pt_n:dca>>h48",station && matched && minPt && recon_m && phi13EC && eta13EC && z0recmax && electron,"", num_events);
	rec.Draw("Pt_n:dca>>h49",station && matched && minPt && recon_m && phi13EC && eta13EC && z0recmax && muon);
	
	//! page20
	rec.Draw("M_pt:dca>>h50",station && matched && minPt_t && truth_m && z0truthmax,"", num_events);
	rec.Draw("M_pt:dca>>h51",station && matched && minPt_t && truth_m && z0truthmax && pion,"", num_events);
	rec.Draw("M_pt:dca>>h52",station && matched && minPt_t && truth_m && z0truthmax && electron,"", num_events);
	rec.Draw("M_pt:dca>>h53",station && matched && minPt_t && truth_m && z0truthmax && muon);
	
	//! page21
	//! z0 vs dca
	rec.Draw("Z013:dca>>h54",station && fakes && minPt && recon_m && phi13EC && eta13EC && z0recmax,"", num_events);

	//! page22
	rec.Draw("Z013:dca>>h55",station && matched && minPt && recon_m && phi13EC && eta13EC && z0recmax,"", num_events);
	rec.Draw("Z013:dca>>h56",station && matched && minPt && recon_m && phi13EC && eta13EC && z0recmax && pion,"", num_events);
	rec.Draw("Z013:dca>>h57",station && matched && minPt && recon_m && phi13EC && eta13EC && z0recmax && electron,"", num_events);
	rec.Draw("Z013:dca>>h58",station && matched && minPt && recon_m && phi13EC && eta13EC && z0recmax && muon);
	//! page23
	rec.Draw("M_Vz:M_dca>>h59",station && matched && minPt_t && truth_m && z0truthmax,"", num_events);
	rec.Draw("M_Vz:M_dca>>h60",station && matched && minPt_t && truth_m && z0truthmax && pion,"", num_events);
	rec.Draw("M_Vz:M_dca>>h61",station && matched && minPt_t && truth_m && z0truthmax && electron,"", num_events);
	rec.Draw("M_Vz:M_dca>>h62",station && matched && minPt_t && truth_m && z0truthmax && muon);

	//! page24
	//!dca
	rec.Draw("dca>>h63",station && fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2,"",num_events);
	rec.Draw("dca>>h72",station && fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && kapcut_t,"",num_events);
	/*rec.Draw("dca>>h64",fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && electron,"",num_events);
	rec.Draw("dca>>h65",fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && muon);*/
	
	//! page25
	rec.Draw("M_dca>>h66",station && matched && minPt_t && phi13EC && eta13EC && z0truthmax &&  maxdphi2 && maxdeta2 && pion,"",num_events);
	rec.Draw("M_dca>>h67",station && matched && minPt_t && phi13EC && eta13EC && z0truthmax && maxdphi2 && maxdeta2 && electron,"",num_events);
	rec.Draw("M_dca>>h68",station && matched && minPt_t && phi13EC && eta13EC && z0truthmax && maxdphi2 && maxdeta2 && muon/*,"",num_events*/);

	//! page26
	rec.Draw("dca>>h69",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && pion,"",num_events);
	rec.Draw("dca>>h70",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && electron,"",num_events);
	rec.Draw("dca>>h71",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && muon/*,"",num_events*/);
	/*rec.Draw("dca>>h73",fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && kapcut_t && electron,"",num_events);
	rec.Draw("dca>>h74",fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && kapcut_t && muon);*/

	//! page27
	rec.Draw("M_dca>>h75",station && matched && minPt_t && phi13EC && eta13EC && z0truthmax &&  maxdphi2 && maxdeta2 && kapcut_t && pion,"",num_events);
	rec.Draw("M_dca>>h76",station && matched && minPt_t && phi13EC && eta13EC && z0truthmax && maxdphi2 && maxdeta2 && kapcut_t && electron,"",num_events);
	rec.Draw("M_dca>>h77",station && matched && minPt_t && phi13EC && eta13EC && z0truthmax && maxdphi2 && maxdeta2 && kapcut_t && muon/*,"",num_events*/);

	//! page28
	rec.Draw("dca>>h78",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && kapcut_t && pion,"",num_events);
	rec.Draw("dca>>h79",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && kapcut_t && electron,"",num_events);
	rec.Draw("dca>>h80",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && kapcut_t && muon/*,"",num_events*/);
	
	//!deta2
	rec.Draw("log(1/tan(0.5*atan2(sqrt(X2*X2+Y2*Y2),Z2)))-0.5*(log(1/tan(0.5*atan2(R03,Z3)))+log(1/tan(0.5*atan2(R01,Z1))))>>h81",station && fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2,"",num_events);
	rec.Draw("log(1/tan(0.5*atan2(sqrt(X2*X2+Y2*Y2),Z2)))-0.5*(log(1/tan(0.5*atan2(R03,Z3)))+log(1/tan(0.5*atan2(R01,Z1))))>>h90",station && fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && kapcut_t,"",num_events);
/*	rec.Draw("log(1/tan(0.5*atan2(sqrt(X2*X2+Y2*Y2),Z2)))-0.5*(log(1/tan(0.5*atan2(R03,Z3)))+log(1/tan(0.5*atan2(R01,Z1))))>>h82",fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && electron,"",num_events);
	rec.Draw("log(1/tan(0.5*atan2(sqrt(X2*X2+Y2*Y2),Z2)))-0.5*(log(1/tan(0.5*atan2(R03,Z3)))+log(1/tan(0.5*atan2(R01,Z1))))>>h83",fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && muon);*/
	rec.Draw("log(1/tan(0.5*atan2(sqrt(X2*X2+Y2*Y2),Z2)))-0.5*(log(1/tan(0.5*atan2(R03,Z3)))+log(1/tan(0.5*atan2(R01,Z1))))>>h84",station && matched && minPt_t && phi13EC && eta13EC && z0truthmax &&  maxdphi2 && maxdeta2 && pion,"",num_events);
	rec.Draw("log(1/tan(0.5*atan2(sqrt(X2*X2+Y2*Y2),Z2)))-0.5*(log(1/tan(0.5*atan2(R03,Z3)))+log(1/tan(0.5*atan2(R01,Z1))))>>h85",station && matched && minPt_t && phi13EC && eta13EC && z0truthmax && maxdphi2 && maxdeta2 && electron,"",num_events);
	rec.Draw("log(1/tan(0.5*atan2(sqrt(X2*X2+Y2*Y2),Z2)))-0.5*(log(1/tan(0.5*atan2(R03,Z3)))+log(1/tan(0.5*atan2(R01,Z1))))>>h86",station && matched && minPt_t && phi13EC && eta13EC && z0truthmax && maxdphi2 && maxdeta2 && muon/*,"",num_events*/);
	rec.Draw("log(1/tan(0.5*atan2(sqrt(X2*X2+Y2*Y2),Z2)))-0.5*(log(1/tan(0.5*atan2(R03,Z3)))+log(1/tan(0.5*atan2(R01,Z1))))>>h87",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && pion,"",num_events);
	rec.Draw("log(1/tan(0.5*atan2(sqrt(X2*X2+Y2*Y2),Z2)))-0.5*(log(1/tan(0.5*atan2(R03,Z3)))+log(1/tan(0.5*atan2(R01,Z1))))>>h88",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && electron,"",num_events);
	rec.Draw("log(1/tan(0.5*atan2(sqrt(X2*X2+Y2*Y2),Z2)))-0.5*(log(1/tan(0.5*atan2(R03,Z3)))+log(1/tan(0.5*atan2(R01,Z1))))>>h89",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && muon/*,"",num_events*/);
/*	rec.Draw("log(1/tan(0.5*atan2(sqrt(X2*X2+Y2*Y2),Z2)))-0.5*(log(1/tan(0.5*atan2(R03,Z3)))+log(1/tan(0.5*atan2(R01,Z1))))>>h91",fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && kapcut_t && electron,"",num_events);
	rec.Draw("log(1/tan(0.5*atan2(sqrt(X2*X2+Y2*Y2),Z2)))-0.5*(log(1/tan(0.5*atan2(R03,Z3)))+log(1/tan(0.5*atan2(R01,Z1))))>>h92",fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && kapcut_t && muon);*/
	rec.Draw("log(1/tan(0.5*atan2(sqrt(X2*X2+Y2*Y2),Z2)))-0.5*(log(1/tan(0.5*atan2(R03,Z3)))+log(1/tan(0.5*atan2(R01,Z1))))>>h93",station && matched && minPt_t && phi13EC && eta13EC && z0truthmax &&  maxdphi2 && maxdeta2 && kapcut_t && pion,"",num_events);
	rec.Draw("log(1/tan(0.5*atan2(sqrt(X2*X2+Y2*Y2),Z2)))-0.5*(log(1/tan(0.5*atan2(R03,Z3)))+log(1/tan(0.5*atan2(R01,Z1))))>>h94",station && matched && minPt_t && phi13EC && eta13EC && z0truthmax && maxdphi2 && maxdeta2 && kapcut_t && electron,"",num_events);
	rec.Draw("log(1/tan(0.5*atan2(sqrt(X2*X2+Y2*Y2),Z2)))-0.5*(log(1/tan(0.5*atan2(R03,Z3)))+log(1/tan(0.5*atan2(R01,Z1))))>>h95",station && matched && minPt_t && phi13EC && eta13EC && z0truthmax && maxdphi2 && maxdeta2 && kapcut_t && muon/*,"",num_events*/);
	rec.Draw("log(1/tan(0.5*atan2(sqrt(X2*X2+Y2*Y2),Z2)))-0.5*(log(1/tan(0.5*atan2(R03,Z3)))+log(1/tan(0.5*atan2(R01,Z1))))>>h96",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && kapcut_t && pion,"",num_events);
	rec.Draw("log(1/tan(0.5*atan2(sqrt(X2*X2+Y2*Y2),Z2)))-0.5*(log(1/tan(0.5*atan2(R03,Z3)))+log(1/tan(0.5*atan2(R01,Z1))))>>h97",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && kapcut_t && electron,"",num_events);
	rec.Draw("log(1/tan(0.5*atan2(sqrt(X2*X2+Y2*Y2),Z2)))-0.5*(log(1/tan(0.5*atan2(R03,Z3)))+log(1/tan(0.5*atan2(R01,Z1))))>>h98",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && kapcut_t && muon/*,"",num_events*/);
	
	//!dkappa
	rec.Draw("kappa-kap013>>h99",station && fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2,"",num_events);
/*	rec.Draw("kappa-kap013>>h100",fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && electron,"",num_events);
	rec.Draw("kappa-kap013>>h101",fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && muon);*/
	rec.Draw("kappa-kap013>>h102",station && matched && minPt_t && phi13EC && eta13EC && z0truthmax &&  maxdphi2 && maxdeta2 && pion,"",num_events);
	rec.Draw("kappa-kap013>>h103",station && matched && minPt_t && phi13EC && eta13EC && z0truthmax && maxdphi2 && maxdeta2 && electron,"",num_events);
	rec.Draw("kappa-kap013>>h104",station && matched && minPt_t && phi13EC && eta13EC && z0truthmax && maxdphi2 && maxdeta2 && muon/*,"",num_events*/);
	rec.Draw("kappa-kap013>>h105",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && pion,"",num_events);
	rec.Draw("kappa-kap013>>h106",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && electron,"",num_events);
	rec.Draw("kappa-kap013>>h107",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && muon/*,"",num_events*/);
	rec.Draw("kappa-kap013>>h108",station && fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && kapcut_t,"",num_events);
/*	rec.Draw("kappa-kap013>>h109",fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && kapcut_t && electron,"",num_events);
	rec.Draw("kappa-kap013>>h110",fakes && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && kapcut_t && muon);*/
	rec.Draw("kappa-kap013>>h111",station && matched && minPt_t && phi13EC && eta13EC && z0truthmax &&  maxdphi2 && maxdeta2 && kapcut_t && pion,"",num_events);
	rec.Draw("kappa-kap013>>h112",station && matched && minPt_t && phi13EC && eta13EC && z0truthmax && maxdphi2 && maxdeta2 && kapcut_t && electron,"",num_events);
	rec.Draw("kappa-kap013>>h113",station && matched && minPt_t && phi13EC && eta13EC && z0truthmax && maxdphi2 && maxdeta2 && kapcut_t && muon/*,"",num_events*/);
	rec.Draw("kappa-kap013>>h114",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && kapcut_t && pion,"",num_events);
	rec.Draw("kappa-kap013>>h115",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && kapcut_t && electron,"",num_events);
	rec.Draw("kappa-kap013>>h116",station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 && kapcut_t && muon/*,"",num_events*/);

	rec.Draw("M_kap>>h117",station && matched && minPt_t && phi13EC && eta13EC && z0truthmax,"",num_events);
	rec.Draw("kap013>>h118",station && matched && minPt && phi13EC && eta13EC && z0recmax,"",num_events);
	rec.Draw("kappa>>h119",station && matched && minPt && phi13EC && eta13EC && z0recmax,"",num_events);

	rec.Draw("kap013:M_kap>>h120",station && matched && minPt_t && minPt && phi13EC && eta13EC && z0recmax && z0truthmax,"",num_events);
	rec.Draw("kap013:M_kap>>h121",station && matched && minPt_t && minPt && phi13EC && eta13EC && z0recmax && z0truthmax && pion,"",num_events);
	rec.Draw("kap013:M_kap>>h122",station && matched && minPt_t && minPt && phi13EC && eta13EC && z0recmax && z0truthmax && electron,"",num_events);
	rec.Draw("kap013:M_kap>>h123",station && matched && minPt_t && minPt && phi13EC && eta13EC && z0recmax && z0truthmax && muon,"",num_events);
	rec.Draw("kappa:M_kap>>h124",station && matched && minPt_t && minPt && phi13EC && eta13EC && z0recmax && z0truthmax,"",num_events);
	rec.Draw("kappa:M_kap>>h125",station && matched && minPt_t && minPt && phi13EC && eta13EC && z0recmax && z0truthmax && pion,"",num_events);
	rec.Draw("kappa:M_kap>>h126",station && matched && minPt_t && minPt && phi13EC && eta13EC && z0recmax && z0truthmax && electron,"",num_events);
	rec.Draw("kappa:M_kap>>h127",station && matched && minPt_t && minPt && phi13EC && eta13EC && z0recmax && z0truthmax && muon,"",num_events);

	rec.Draw("kap013:kappa>>h128",station && matched && minPt && phi13EC && eta13EC && z0recmax,"",num_events);
	rec.Draw("kap013:kappa>>h129",station && matched && minPt && phi13EC && eta13EC && z0recmax && pion,"",num_events);
	rec.Draw("kap013:kappa>>h130",station && matched && minPt && phi13EC && eta13EC && z0recmax && electron,"",num_events);
	rec.Draw("kap013:kappa>>h131",station && matched && minPt && phi13EC && eta13EC && z0recmax && muon,"",num_events);

	rec.Draw("kap013/M_kap>>h132",station && matched && minPt && phi13EC && eta13EC && z0recmax,"",num_events);
	rec.Draw("kap013/M_kap>>h133",station && matched && minPt && phi13EC && eta13EC && z0recmax && pion,"",num_events);
	rec.Draw("kap013/M_kap>>h134",station && matched && minPt && phi13EC && eta13EC && z0recmax && electron,"",num_events);
	rec.Draw("kap013/M_kap>>h135",station && matched && minPt && phi13EC && eta13EC && z0recmax && muon,"",num_events);
	rec.Draw("kappa/M_kap>>h136",station && matched && minPt && phi13EC && eta13EC && z0recmax,"",num_events);
	rec.Draw("kappa/M_kap>>h137",station && matched && minPt && phi13EC && eta13EC && z0recmax && pion,"",num_events);
	rec.Draw("kappa/M_kap>>h138",station && matched && minPt && phi13EC && eta13EC && z0recmax && electron,"",num_events);
	rec.Draw("kappa/M_kap>>h139",station && matched && minPt && phi13EC && eta13EC && z0recmax && muon,"",num_events);

	rec.Draw("kap013-kappa:sqrt((M_Vx*M_Vx) + (M_Vy*M_Vy))>>h140",station && matched && minPt_t && minPt && phi13EC && eta13EC && z0recmax && z0truthmax,"",num_events);
	rec.Draw("kap013-kappa:sqrt((M_Vx*M_Vx) + (M_Vy*M_Vy))>>h141",station && matched && minPt_t && minPt && phi13EC && eta13EC && z0recmax && z0truthmax && pion,"",num_events);
	rec.Draw("kap013-kappa:sqrt((M_Vx*M_Vx) + (M_Vy*M_Vy))>>h142",station && matched && minPt_t && minPt && phi13EC && eta13EC && z0recmax && z0truthmax && electron,"",num_events);
	rec.Draw("kap013-kappa:sqrt((M_Vx*M_Vx) + (M_Vy*M_Vy))>>h143",station && matched && minPt_t && minPt && phi13EC && eta13EC && z0recmax && z0truthmax && muon,"",num_events);
	rec.Draw("kap013/M_kap:sqrt((M_Vx*M_Vx) + (M_Vy*M_Vy))>>h144",station && matched && minPt_t && minPt && phi13EC && eta13EC && z0recmax && z0truthmax,"",num_events);
	rec.Draw("kap013/M_kap:sqrt((M_Vx*M_Vx) + (M_Vy*M_Vy))>>h145",station && matched && minPt_t && minPt && phi13EC && eta13EC && z0recmax && z0truthmax && pion,"",num_events);
	rec.Draw("kap013/M_kap:sqrt((M_Vx*M_Vx) + (M_Vy*M_Vy))>>h146",station && matched && minPt_t && minPt && phi13EC && eta13EC && z0recmax && z0truthmax && electron,"",num_events);
	rec.Draw("kap013/M_kap:sqrt((M_Vx*M_Vx) + (M_Vy*M_Vy))>>h147",station && matched && minPt_t && minPt && phi13EC && eta13EC && z0recmax && z0truthmax && muon,"",num_events);

	//! dphi2 Vs sin(theta) w/o dphi2 and dz2 cut
        rec.Draw("dphi2:sin(Theta13)>>h_24",station &&  fakes && minPt && phi13EC && eta13EC && z0recmax && kapcut_l,"",num_events);
        rec.Draw("dphi2:sin(Theta13)>>h_25",station && matched && minPt && phi13EC && eta13EC && z0recmax && kapcut_l,"same",num_events);
        rec.Draw("dphi2:sin(Theta13)>>h_25a",station && matched && minPt && phi13EC && eta13EC && z0recmax && kapcut_l && noelectron,"same",num_events);
        rec.Draw("dphi2:sin(M_theta)>>h_26",station && matched && minPt_t /*&& phi13EC && eta13EC*/ && z0truthmax && kapcut_l,"same",num_events);

        //! deta2 Vs sin(theta) w/o deta2 cut and with kappa cut
        rec.Draw("dz2:sin(Theta13)>>h_27",station &&  fakes && minPt && phi13EC && eta13EC && z0recmax && kapcut_l,"",num_events);
        rec.Draw("dz2:sin(Theta13)>>h_28",station && matched && minPt && phi13EC && eta13EC && z0recmax && kapcut_l,"same",num_events);
        rec.Draw("dz2:sin(Theta13)>>h_28a",station && matched && minPt && phi13EC && eta13EC && z0recmax && kapcut_l && noelectron,"same",num_events);
        rec.Draw("dz2:sin(M_theta)>>h_29",station && matched && minPt_t /*&& phi13EC && eta13EC*/ && z0truthmax && kapcut_l,"same",num_events);
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
	h_pur_vs_ptPU->SetTitle("Purity vs p_{T};p_{T} [MeV/c];Purity");
	h_pur_vs_ptPU->Divide(h_num_vs_ptPU, h_den_vs_ptPU, 1.0, 1.0, "B");
	h_pur_vs_ptPU->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_pur_vs_ptPU->GetXaxis()->SetRangeUser(2000.,1000000.);
	h_pur_vs_ptPU->SetMarkerSize(0.95);
	h_pur_vs_ptPU->SetMarkerStyle(kOpenTriangleDown);
	h_pur_vs_ptPU->SetMarkerColor(kBlack);	
	
	rec.Draw("Eta13>>h_num_vs_eta_",   station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 , "goff"/*, num_events*/);

        rec.Draw("Eta13>>h_den_vs_eta_",   station && (fakes || matched) && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 , "goff"/*, num_events*/);
	TH1* h_pur_vs_eta_ = dynamic_cast<TH1*>(h_num_vs_eta_->Clone("h_pur_vs_eta_"));
        h_pur_vs_eta_->SetTitle("Purity vs #eta;#eta;Purity");
        h_pur_vs_eta_->Divide(h_num_vs_eta_, h_den_vs_eta_, 1.0, 1.0, "B");
        h_pur_vs_eta_->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_pur_vs_eta_->SetMarkerSize(0.95);
        h_pur_vs_eta_->SetMarkerStyle(kFullTriangleDown);
        h_pur_vs_eta_->SetMarkerColor(kBlack);

	rec.Draw("Pt_n>>h_num_vs_pt_",   station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2, "goff"/*, num_events*/);
	rec.Draw("Pt_n>>h_den_vs_pt_",   station && (fakes || matched) && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2, "goff"/*, num_events*/);
	TH1* h_pur_vs_pt_ = dynamic_cast<TH1*>(h_num_vs_pt_->Clone("h_pur_vs_pt_"));
	h_pur_vs_pt_->SetTitle("Purity vs p_{T};p_{T} [MeV/c];Purity");
	h_pur_vs_pt_->Divide(h_num_vs_pt_, h_den_vs_pt_, 1.0, 1.0, "B");
	h_pur_vs_pt_->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_pur_vs_pt_->GetXaxis()->SetRangeUser(2000.,1000000.);
	h_pur_vs_pt_->SetMarkerSize(0.95);
	h_pur_vs_pt_->SetMarkerStyle(kFullTriangleDown);
	h_pur_vs_pt_->SetMarkerColor(kBlack);	


	rec.Draw("Eta13>>h_num_vs_eta_l",   station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*&& dphi2max && dz2max*/ && kapcut_l, "goff"/*, num_events*/);

        rec.Draw("Eta13>>h_den_vs_eta_l",   station && (fakes || matched) && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*&& dphi2max && dz2max*/ && kapcut_l, "goff"/*, num_events*/);
	TH1* h_pur_vs_eta_l = dynamic_cast<TH1*>(h_num_vs_eta_l->Clone("h_pur_vs_eta_l"));
        h_pur_vs_eta_l->SetTitle("Purity vs #eta;#eta;Purity");
        h_pur_vs_eta_l->Divide(h_num_vs_eta_l, h_den_vs_eta_l, 1.0, 1.0, "B");
        h_pur_vs_eta_l->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_pur_vs_eta_l->SetMarkerSize(0.95);
        h_pur_vs_eta_l->SetMarkerStyle(kFullTriangleDown);
        h_pur_vs_eta_l->SetMarkerColor(kRed-9);

	rec.Draw("Pt_n>>h_num_vs_pt_l",   station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*&& dphi2max_l && dz2max_l*/ && kapcut_l, "goff"/*, num_events*/);
	rec.Draw("Pt_n>>h_den_vs_pt_l",   station && (fakes || matched) && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*&& dphi2max_l && dz2max_l*/ && kapcut_l, "goff"/*, num_events*/);
	TH1* h_pur_vs_pt_l = dynamic_cast<TH1*>(h_num_vs_pt_l->Clone("h_pur_vs_pt_l"));
	h_pur_vs_pt_l->SetTitle("Purity vs p_{T};p_{T} [MeV/c];Purity");
	h_pur_vs_pt_l->Divide(h_num_vs_pt_l, h_den_vs_pt_l, 1.0, 1.0, "B");
	h_pur_vs_pt_l->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_pur_vs_pt_l->GetXaxis()->SetRangeUser(2000.,1000000.);
	h_pur_vs_pt_l->SetMarkerSize(0.95);
	h_pur_vs_pt_l->SetMarkerStyle(kFullTriangleDown);
	h_pur_vs_pt_l->SetMarkerColor(kRed-9);	

rec.Draw("Eta13>>h_num_vs_eta_m",   station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*&& dphi2max && dz2max*/ && kapcut, "goff"/*, num_events*/);
        rec.Draw("Eta13>>h_den_vs_eta_m",   station && (fakes || matched) && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*&& dphi2max && dz2max*/ && kapcut, "goff"/*, num_events*/);
	TH1* h_pur_vs_eta_m = dynamic_cast<TH1*>(h_num_vs_eta_m->Clone("h_pur_vs_eta_m"));
        h_pur_vs_eta_m->SetTitle("Purity vs #eta;#eta;Purity");
        h_pur_vs_eta_m->Divide(h_num_vs_eta_m, h_den_vs_eta_m, 1.0, 1.0, "B");
        h_pur_vs_eta_m->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_pur_vs_eta_m->SetMarkerSize(0.95);
        h_pur_vs_eta_m->SetMarkerStyle(kFullTriangleDown);
        h_pur_vs_eta_m->SetMarkerColor(kRed);

	rec.Draw("Pt_n>>h_num_vs_pt_m",   station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*&& dphi2max && dz2max*/ && kapcut, "goff"/*, num_events*/);
	rec.Draw("Pt_n>>h_den_vs_pt_m",   station && (fakes || matched) && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*&& dphi2max && dz2max*/ && kapcut, "goff"/*, num_events*/);
	TH1* h_pur_vs_pt_m = dynamic_cast<TH1*>(h_num_vs_pt_m->Clone("h_pur_vs_pt_m"));
	h_pur_vs_pt_m->SetTitle("Purity vs p_{T};p_{T} [MeV/c];Purity");
	h_pur_vs_pt_m->Divide(h_num_vs_pt_m, h_den_vs_pt_m, 1.0, 1.0, "B");
	h_pur_vs_pt_m->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_pur_vs_pt_m->GetXaxis()->SetRangeUser(2000.,1000000.);
	h_pur_vs_pt_m->SetMarkerSize(0.95);
	h_pur_vs_pt_m->SetMarkerStyle(kFullTriangleDown);
	h_pur_vs_pt_m->SetMarkerColor(kRed);	

	rec.Draw("Eta13>>h_num_vs_eta_t",   station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*&& dphi2max_t && dz2max_t*/ && kapcut_t, "goff"/*, num_events*/);
        rec.Draw("Eta13>>h_den_vs_eta_t",   station && (fakes || matched) && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*&& dphi2max_t && dz2max_t*/ && kapcut_t, "goff"/*, num_events*/);
	TH1* h_pur_vs_eta_t = dynamic_cast<TH1*>(h_num_vs_eta_t->Clone("h_pur_vs_eta_t"));
        h_pur_vs_eta_t->SetTitle("Purity vs #eta;#eta;Purity");
        h_pur_vs_eta_t->Divide(h_num_vs_eta_t, h_den_vs_eta_t, 1.0, 1.0, "B");
        h_pur_vs_eta_t->GetYaxis()->SetRangeUser(0.1, 1.1);
        h_pur_vs_eta_t->SetMarkerSize(0.95);
        h_pur_vs_eta_t->SetMarkerStyle(kFullTriangleDown);
        h_pur_vs_eta_t->SetMarkerColor(kRed+2);

	rec.Draw("Pt_n>>h_num_vs_pt_t",   station && matched && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*&& dphi2max_t && dz2max_t*/ && kapcut_t, "goff"/*, num_events*/);
	rec.Draw("Pt_n>>h_den_vs_pt_t",   station && (fakes || matched) && minPt && phi13EC && eta13EC && z0recmax && maxdphi2 && maxdeta2 /*&& dphi2max_t && dz2max_t*/ && kapcut_t, "goff"/*, num_events*/);
	TH1* h_pur_vs_pt_t = dynamic_cast<TH1*>(h_num_vs_pt_t->Clone("h_pur_vs_pt_t"));
	h_pur_vs_pt_t->SetTitle("Purity vs p_{T};p_{T} [MeV/c];Purity");
	h_pur_vs_pt_t->Divide(h_num_vs_pt_t, h_den_vs_pt_t, 1.0, 1.0, "B");
	h_pur_vs_pt_t->GetYaxis()->SetRangeUser(0.1, 1.1);
	h_pur_vs_pt_t->GetXaxis()->SetRangeUser(2000.,1000000.);
	h_pur_vs_pt_t->SetMarkerSize(0.95);
	h_pur_vs_pt_t->SetMarkerStyle(kFullTriangleDown);
	h_pur_vs_pt_t->SetMarkerColor(kRed+2);	



	h1->Draw();
	h2->Draw();
	h3->Draw();
	h4->Draw();
	h5->Draw();
	h5a->Draw();
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
	h36->Draw();
        h37->Draw();
        /*h38->Draw();
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
	h3->Write();
	h4->Write();
	h5->Write();
	h5a->Write();
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
	h36->Write();
		      
	h33->Write();
	h34->Write();
	h35->Write();
	h37->Write();
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
/*
	//! page9
	// 1. dr2 vs sin(theta013) : fakes 
	// 2. dr2 vs sin(theta013) : matched no electron
	// 3. dr2 vs sin(theta013) : matched
	// 4. dr2 vs tru sin(theta)
        rec.Draw("R02 - 0.5*(R01+R03):sin(Theta13)>>h27",station &&  fakes && minPt && phi13EC && eta13EC && z0recmax,"",num_events);
        rec.Draw("R02 - 0.5*(R01+R03):sin(Theta13)>>h28a",station && matched && minPt && phi13EC && eta13EC && z0recmax && noelectron,"same",num_events);
        rec.Draw("R02 - 0.5*(R01+R03):sin(Theta13)>>h28",station && matched && minPt && phi13EC && eta13EC && z0recmax,"same",num_events);
        rec.Draw("R02 - 0.5*(R01+R03):sin(M_theta)>>h29",station && matched && minPt_t && z0truthmax,"same",num_events);
	//! page11
	// 1. dphi2 vs sin(theta013) * cos(theta013)^(-0.5): fakes 
	// 2. dphi2 vs sin(theta013) * cos(theta013)^(-0.5): matched no electron
	// 3. dphi2 vs sin(theta013) * cos(theta013)^(-0.5): matched
	// 4. dphi2 vs tru sin(theta)* cos(theta)^(-0.5)
        rec.Draw("dphi2:cos(Theta13)^(-0.5)*sin(Theta13)>>th24",station &&  fakes && minPt && phi13EC && eta13EC && z0recmax,"",num_events);
        rec.Draw("dphi2:cos(Theta13)^(-0.5)*sin(Theta13)>>th25a",station && matched && minPt && phi13EC && eta13EC && z0recmax && noelectron,"same",num_events);
        rec.Draw("dphi2:cos(Theta13)^(-0.5)*sin(Theta13)>>th25",station && matched && minPt && phi13EC && eta13EC && z0recmax,"same",num_events);
        rec.Draw("dphi2:cos(M_theta)^(-0.5)*sin(M_theta)>>th26",station && matched && minPt_t && z0truthmax,"same",num_events);

	//! page12
	// 1. dr2 vs sin(theta013) * cos(theta013)^(-2.5): fakes 
	// 2. dr2 vs sin(theta013) * cos(theta013)^(-2.5): matched no electron
	// 3. dr2 vs sin(theta013) * cos(theta013)^(-2.5): matched
	// 4. dr2 vs tru sin(theta)* cos(theta)^(-2.5)
        rec.Draw("R02 - 0.5*(R01+R03):cos(Theta13)^(-2.5)*sin(Theta13)>>th27",station &&  fakes && minPt && phi13EC && eta13EC && z0recmax,"",num_events);
        rec.Draw("R02 - 0.5*(R01+R03):cos(Theta13)^(-2.5)*sin(Theta13)>>th28a",station && matched && minPt && phi13EC && eta13EC && z0recmax && noelectron,"same",num_events);
        rec.Draw("R02 - 0.5*(R01+R03):cos(Theta13)^(-2.5)*sin(Theta13)>>th28",station && matched && minPt && phi13EC && eta13EC && z0recmax,"same",num_events);
        rec.Draw("R02 - 0.5*(R01+R03):cos(M_theta)^(-2.5)*sin(M_theta)>>th29",station && matched && minPt_t && z0truthmax,"same",num_events);
	
	//! page13
	// 1. rec pT vs dphi2 : fake 
	// 2. rec pT vs dphi2 : matched
	// 3. tru pT vs dphi2 :  
        rec.Draw("Pt_n:dphi2>>h30",station &&  fakes && minPt && recon_m && phi13EC && eta13EC && z0recmax,"",num_events);
        rec.Draw("Pt_n:dphi2>>h31",station && matched && minPt && recon_m && phi13EC && eta13EC && z0recmax,"same",num_events);
        rec.Draw("M_pt:dphi2>>h32",station && matched && minPt_t && truth_m && z0truthmax,"same",num_events);

	//! page14
	// 1. rec pT vs dr2 : fake 
	// 2. rec pT vs dr2 : matched
	// 3. tru pT vs dr2 :  
        rec.Draw("Pt_n:R02 - 0.5*(R01+R03)>>h33",station &&  fakes && minPt && recon_m && phi13EC && eta13EC && z0recmax,"",num_events);
        rec.Draw("Pt_n:R02 - 0.5*(R01+R03)>>h34",station && matched && minPt && recon_m && phi13EC && eta13EC && z0recmax,"same",num_events);
        rec.Draw("M_pt:R02 - 0.5*(R01+R03)>>h35",station && matched && minPt_t && truth_m && z0truthmax,"same",num_events);
	
*/
