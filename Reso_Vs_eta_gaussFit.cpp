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
#include <fstream>
#include <string>
#include <math.h>
//! Define Cut
TCut mu_cut = "abs(M_pdg)==13 && M_barcode > 0 && abs(InDetTZ0) < 200 && abs(M_Vx)<10 && abs(M_Vy)<10";
TCut pi_cut = "abs(M_pdg)==211 && M_barcode > 0 && abs(InDetTZ0) < 200 && abs(M_Vx)<10 && abs(M_Vy)<10";
TCut e_cut  = "abs(M_pdg)==11 && M_barcode > 0 && abs(InDetTZ0) < 200 && abs(M_Vx)<10 && abs(M_Vy)<10";
TCut all_cut= "InDetTBarcode > 0 && abs(InDetTPt)>2000 && abs(InDetTEta)<1.4 && abs(InDetpt)>2000 && abs(InDeteta)<1.5";
//! path for input files
const char* path = "/afs/cern.ch/work/t/tkar/testarea/20.20.10.1/WorkArea/run/rec_outputs/SingleParticles_Sept272k18";
char buf[4096];
//! User defined Gauss fit function to optimise the fit 
void fit_Gauss(TH1F* h)
{
	h->SetLineWidth(2);
	float xmin = h->GetXaxis()->GetXmin(), xmin_ = xmin;
	float xmax = h->GetXaxis()->GetXmax(), xmax_ = xmax;
	//! repeat the fit thrice 
	for(int i = 0; i < 3; i++) 
	{
    	h->Fit("gaus", "QLL", "", xmin_, xmax_);
    	xmin_ = h->GetFunction("gaus")->GetParameter(1) - 2.0 * h->GetFunction("gaus")->GetParameter(2);
    	xmax_ = h->GetFunction("gaus")->GetParameter(1) + 2.0 * h->GetFunction("gaus")->GetParameter(2);
  	}

	h->GetFunction("gaus")->SetLineColor(2);
  	h->GetFunction("gaus")->SetLineWidth(2);

	h->GetYaxis()->SetRangeUser(0, 1.1 * h->GetMaximum());
	float ymin = 0;
	float ymax = 1.1 * h->GetMaximum();

	TLatex lat;
	sprintf(buf, "#mu = %.2f", h->GetFunction("gaus")->GetParameter(1));
	lat.DrawLatex(xmin + 0.6 * (xmax - xmin), 0.80 * ymax, buf);
	sprintf(buf, "#sigma = %.2f", h->GetFunction("gaus")->GetParameter(2));
	lat.DrawLatex(xmin + 0.6 * (xmax - xmin), 0.75 * ymax, buf);
}

char buffer[1024];
int resolution_plots_Vs_eta
(const char* output_file_name, const char* p_type = "all", bool save = false)
{
	TChain recTree("m_collectionTree");
	recTree.Add("/media/tamasi/DriveT/tamasi/Desktop/PHD/work/mere_plots/athena/Analysis/user.tkar.hh4bsig5PU0_2_ntuples1_MYSTREAM/*.root");
	TCut cut;
	const char* type = p_type;
	if(type == "muon"){ cut = mu_cut;}
	else if(type == "pion") cut = pi_cut;
	else if(type == "electron") cut = e_cut;
	else if(type == "all") cut = all_cut;
	else{ std::cout <<"enter particle type"; return 0;} 
	
	int etabin = 13;
    	double etamin   = -1.3, etamax = 1.3;
	int binNum	    = 200;
	double relptmin, relptmax;    
	double inv_ptmin, inv_ptmax;    
	double phimin, phimax;	    
	double zmin, zmax;
	double thetamin, thetamax;
	double eta_min, eta_max;
	double dcamin, dcamax;
		
	TCanvas *C1 = new TCanvas("C1","");
	TCanvas *C2 = new TCanvas("C2","");
	TCanvas *C3 = new TCanvas("C3","");
	TCanvas *C4 = new TCanvas("C4","");
	TCanvas *C5 = new TCanvas("C5","");
	TCanvas *C6 = new TCanvas("C6","");
	TCanvas *C7 = new TCanvas("C7","");

        TH1::SetDefaultSumw2(true);
	//! Final histograms showing the resolution as a funtion of eta
	//! sigma relpt Vs eta //
	TH1D *h_sigmadp = new TH1D("h_sigmadp", "Relative Pt resolution Vs #eta",etabin,etamin,etamax);
	h_sigmadp->SetLineColor(1);
  	h_sigmadp->SetLineWidth(2);
  	h_sigmadp->SetMarkerColor(1);
  	h_sigmadp->SetMarkerStyle(21);
  	h_sigmadp->GetXaxis()->SetTitle("#eta_{gen}");
	h_sigmadp->GetYaxis()->SetTitleOffset(1.3);
  	h_sigmadp->GetYaxis()->SetTitle("#sigma_{#Delta(p_{t})/gen_p_{t}}");
	//! sigma invpt Vs eta//
	TH1D *h_sigma_invPt = new TH1D("h_sigma_invPt", "Inverse Pt resolution Vs #eta",etabin,etamin,etamax);
	h_sigma_invPt->SetLineColor(1);
  	h_sigma_invPt->SetLineWidth(2);
  	h_sigma_invPt->SetMarkerColor(1);
  	h_sigma_invPt->SetMarkerStyle(21);
  	h_sigma_invPt->GetXaxis()->SetTitle("#eta_{gen}");
	h_sigma_invPt->GetYaxis()->SetTitleOffset(1.3);
  	h_sigma_invPt->GetYaxis()->SetTitle("#sigma_{#Delta(1/p_{t})} MeV^{-1}/c");
	//! sigma phi Vs eta//
	TH1D *h_sigma_phi = new TH1D("h_sigma_phi", "Phi resolution Vs #eta",etabin,etamin,etamax);
        h_sigma_phi->SetLineColor(1);
        h_sigma_phi->SetLineWidth(2);
        h_sigma_phi->SetMarkerColor(1);
        h_sigma_phi->SetMarkerStyle(21);
        h_sigma_phi->GetXaxis()->SetTitle("#eta_{gen}");
        h_sigma_phi->GetYaxis()->SetTitleOffset(1.3);
        h_sigma_phi->GetYaxis()->SetTitle("#sigma_{#Delta(#phi)} rad");
	//! sigma theta Vs eta//
	TH1D *h_sigma_theta = new TH1D("h_sigma_theta", "Theta resolution Vs #eta",etabin,etamin,etamax);
        h_sigma_theta->SetLineColor(1);
        h_sigma_theta->SetLineWidth(2);
        h_sigma_theta->SetMarkerColor(1);
        h_sigma_theta->SetMarkerStyle(21);
        h_sigma_theta->GetXaxis()->SetTitle("#eta_{gen}");
        h_sigma_theta->GetYaxis()->SetTitleOffset(1.3);
        h_sigma_theta->GetYaxis()->SetTitle("#sigma_{#Delta(#theta)} rad");
	//! sigma eta Vs eta//
	TH1D *h_sigma_eta = new TH1D("h_sigma_eta", "Eta resolution Vs #eta",etabin,etamin,etamax);
        h_sigma_eta->SetLineColor(1);
        h_sigma_eta->SetLineWidth(2);
        h_sigma_eta->SetMarkerColor(1);
        h_sigma_eta->SetMarkerStyle(21);
        h_sigma_eta->GetXaxis()->SetTitle("#eta_{gen}");
        h_sigma_eta->GetYaxis()->SetTitleOffset(1.3);
        h_sigma_eta->GetYaxis()->SetTitle("#sigma_{#Delta(#eta)}");
	//! sigma z0 Vs eta//
	TH1D *h_sigma_z0 = new TH1D("h_sigma_z0", "Z0 resolution Vs #eta",etabin,etamin,etamax);
        h_sigma_z0->SetLineColor(1);
        h_sigma_z0->SetLineWidth(2);
        h_sigma_z0->SetMarkerColor(1);
        h_sigma_z0->SetMarkerStyle(21);
        h_sigma_z0->GetXaxis()->SetTitle("#eta_{gen}");
        h_sigma_z0->GetYaxis()->SetTitleOffset(1.3);
        h_sigma_z0->GetYaxis()->SetTitle("#sigma_{#Delta(z0)} mm");
	//! sigma dca Vs eta//
	TH1D *h_sigma_dca = new TH1D("h_sigma_dca", "Dca resolution Vs #eta",etabin,etamin,etamax);
        h_sigma_dca->SetLineColor(1);
        h_sigma_dca->SetLineWidth(2);
        h_sigma_dca->SetMarkerColor(1);
        h_sigma_dca->SetMarkerStyle(21);
        h_sigma_dca->GetXaxis()->SetTitle("#eta_{gen}");
        h_sigma_dca->GetYaxis()->SetTitleOffset(1.3);
        h_sigma_dca->GetYaxis()->SetTitle("#sigma_{dca} mm");
	
	h_sigmadp->SetDirectory(0);	
	h_sigma_invPt->SetDirectory(0);
	h_sigma_phi->SetDirectory(0);
	h_sigma_theta->SetDirectory(0);
	h_sigma_eta->SetDirectory(0);
	h_sigma_z0->SetDirectory(0);
	h_sigma_dca->SetDirectory(0);
	
	const char* out_path = "./plots/reso_plots";
	char out_file_root[1023];
	sprintf(out_file_root,"%s/%s.root",out_path,output_file_name);
	TFile* output_file = new TFile(out_file_root, "RECREATE");	
	// for 2 anf 5 GeV Mu
	double bincenter[] = {2000, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
	for (int  k = 0; k < 12; k++)
	{
		//if(Pt<5.0 && Pt>1.0)
		if(k<2){
			std::cout<<"bincenter[" << k <<"] = " << bincenter[k] <<" \n";
			relptmin     	= -0.10, relptmax    	= 0.15;
			inv_ptmin    	= -8e-5, inv_ptmax 	= 4e-5;//4e-5
			phimin		= -0.015, phimax     	= 0.015;
			zmin         	= -12, 	 zmax         	= 12;//10
			thetamin     	= -0.01, thetamax  	= 0.01;
			eta_min      	= -0.015,eta_max   	= 0.015;//0.01
			dcamin	    	= -150, dcamax		= 150;
		}
		//if(Pt<10.0 && Pt>4.9)
		else if(k >=2 && k < 4)
		{
			std::cout<<"bincenter[" << k <<"] = " << bincenter[k] <<" \n";
			relptmin     	= -0.10, relptmax    	= 0.15;
			inv_ptmin    	= -4e-5, inv_ptmax 	= 4e-5;//4e-5
			phimin		= -0.01, phimax     	= 0.01;
			zmin         	= -7, 	 zmax         	= 7;//10
			thetamin     	= -0.006, thetamax  	= 0.006;
			eta_min      	= -0.006,eta_max   	= 0.006;//0.01
			dcamin	    	= -150, dcamax		= 150;
		}
		//for 10 GeV
		//if(Pt<20.0 && Pt >9.9)
		else if(k >= 4 && k<8)
		{
			std::cout<<"bincenter[" << k <<"] = " << bincenter[k] <<" \n";
			relptmin	= -0.25, relptmax    = 0.25;
			inv_ptmin    	= -2e-5, inv_ptmax   = 2e-5;
			phimin	    	= -0.005,phimax      = 0.005;
			zmin         	= -6.0,  zmax        = 6.0;
			thetamin     	= -0.004,thetamax    = 0.004;
			eta_min      	= -0.004,eta_max     = 0.004;
			dcamin	    	= -40,   dcamax      = 150;
		}
		// for 20 to 100 GeV
		//if(Pt < 101.0 && Pt >19.9)
		else if(k >=8 && k <12)
		{
			std::cout<<"bincenter[" << k <<"] = " << bincenter[k] <<" \n";
			relptmin     	= -0.60, relptmax    = 1.1;
			inv_ptmin    	= -1.2e-5, inv_ptmax = 1.2e-5;
			phimin	    	= -0.003,phimax      = 0.003;
			zmin         	= -4.0,  zmax        = 4.0;
			thetamin     	= -0.0025,thetamax   = 0.0025;
			eta_min      	= -0.0025,eta_max    = 0.0025;
			dcamin	    	= -40,  dcamax       = 150;
		}


		//! divide eta into small bins and fill each bin with a histogram
		//! Next fit all these small histograms with gauss fit and optimise the fit about the mean
		for (double eta = -1.2; eta < 1.3; eta+=0.2)
		{
	//		double eta = -1.2;
			TH1F *h1 = new TH1F("h1", "Relative pt", binNum,relptmin,relptmax);
			TH1F *h2 = new TH1F("h2", "Inverse pt", binNum,inv_ptmin,inv_ptmax);
			TH1F *h3 = new TH1F("h3", "Phi", binNum,phimin,phimax);
			TH1F *h4 = new TH1F("h4", "Theta", binNum,thetamin,thetamax);
			TH1F *h5 = new TH1F("h5", "Eta", binNum,eta_min,eta_max);
			TH1F *h6 = new TH1F("h6", "Z0", binNum,zmin,zmax);
			//TH1F *h7 = new TH1F("h7", "dca", binNum,dcamin,dcamax);
			//h->SetDirectory(0);
			sprintf(buffer, "abs(InDetTEta-%f)<0.1 && abs(InDetTPt - %f)<300", eta, bincenter[k]);
			C1->Clear();
			h1->GetXaxis()->SetTitle("(pt_{rec} - pt_{gen})/pt_{gen} ");
			recTree.Draw("(InDetpt - InDetTPt)/InDetTPt>>h1",cut && TCut(buffer));
			fit_Gauss(h1);
			//h1->Fit("gaus","L");
			printf("eta = %.3f => mu = %.9f, sigma rel pt = %.9f, sigma err = %.9f\n", eta,h1->GetFunction("gaus")->GetParameter(1),h1->GetFunction("gaus")->GetParameter(2), h1->GetFunction("gaus")->GetParError(2));

			h_sigmadp->SetBinContent(h_sigmadp->FindBin(eta), h1->GetFunction("gaus")->GetParameter(2));
			h_sigmadp->SetBinError(h_sigmadp->FindBin(eta), h1->GetFunction("gaus")->GetParError(2));
			h_sigmadp->Draw("E1");
			//h1->Draw();
			C1->Update();
			//delete h1;
		
			C2->Clear();
			h2->GetXaxis()->SetTitle("pt_inv_{rec} - pt_inv_{gen} ");
			recTree.Draw("(1/InDetpt - 1/InDetTPt)>>h2",cut && TCut(buffer));
			fit_Gauss(h2);
			//h2->Fit("gaus","L");

			printf("eta = %.3f => mu = %.9f, sigma inv pt= %.9f, sigma err = %.9f\n", eta,h2->GetFunction("gaus")->GetParameter(1),h2->GetFunction("gaus")->GetParameter(2), h2->GetFunction("gaus")->GetParError(2));

			h_sigma_invPt->SetBinContent(h_sigma_invPt->FindBin(eta), h2->GetFunction("gaus")->GetParameter(2));
			h_sigma_invPt->SetBinError(h_sigma_invPt->FindBin(eta), h2->GetFunction("gaus")->GetParError(2));
			h_sigma_invPt->Draw("E1");
			//h2->Draw();
			C2->Update();
			//delete h2;
			
			C3->Clear();
			h3->GetXaxis()->SetTitle("phi_{rec} - phi_{gen} ");
			recTree.Draw("InDetphi0 - InDetTPhi>>h3",cut && TCut(buffer));
			fit_Gauss(h3);
			//h3->Fit("gaus","L");

		       printf("eta = %.3f => mu = %.9f, sigma phi = %.9f, sigma err = %.9f\n", eta,h3->GetFunction("gaus")->GetParameter(1),h3->GetFunction("gaus")->GetParameter(2), h3->GetFunction("gaus")->GetParError(2));

			h_sigma_phi->SetBinContent(h_sigma_phi->FindBin(eta), h3->GetFunction("gaus")->GetParameter(2));
			h_sigma_phi->SetBinError(h_sigma_phi->FindBin(eta), h3->GetFunction("gaus")->GetParError(2));
			h_sigma_phi->Draw("E1");
			//h3->Draw();	
			C3->Update();
			//delete h3;
			
			C4->Clear();
			h4->GetXaxis()->SetTitle("theta_{rec} - theta_{gen} ");
			recTree.Draw("InDettheta - InDetTTheta>>h4",cut && TCut(buffer));
			fit_Gauss(h4);
			//h4->Fit("gaus","L");

			printf("eta = %.3f => mu = %.9f, sigma theta = %.9f, sigma err = %.9f\n", eta,h4->GetFunction("gaus")->GetParameter(1),h4->GetFunction("gaus")->GetParameter(2), h4->GetFunction("gaus")->GetParError(2));

			h_sigma_theta->SetBinContent(h_sigma_theta->FindBin(eta), h4->GetFunction("gaus")->GetParameter(2));
			h_sigma_theta->SetBinError(h_sigma_theta->FindBin(eta), h4->GetFunction("gaus")->GetParError(2));
			h_sigma_theta->Draw("E1");
			//h4->Draw();
			C4->Update();
			//delete h4;
		
			C5->Clear();
			h5->GetXaxis()->SetTitle("eta_{rec} - eta_{gen} ");
			recTree.Draw("InDeteta - InDetTEta>>h5",cut && TCut(buffer));
			fit_Gauss(h5);
			//h5->Fit("gaus","L");

			printf("eta = %.3f, etabin = %.6d => mu = %.9f, sigma eta = %.9f, sigma err = %.9f\n", eta,h_sigma_eta->FindBin(eta),h5->GetFunction("gaus")->GetParameter(1),h5->GetFunction("gaus")->GetParameter(2), h5->GetFunction("gaus")->GetParError(2));

			h_sigma_eta->SetBinContent(h_sigma_eta->FindBin(eta), h5->GetFunction("gaus")->GetParameter(2));
			h_sigma_eta->SetBinError(h_sigma_eta->FindBin(eta), h5->GetFunction("gaus")->GetParError(2));
			h_sigma_eta->Draw("E1");
			//h5->Draw();
			C5->Update();
			//delete h5;

			C6->Clear();
			h6->GetXaxis()->SetTitle("z0_{rec} - z0_{gen} ");
			recTree.Draw("InDetz0 - InDetTZ0>>h6",cut && TCut(buffer));
			fit_Gauss(h6);
			//h6->Fit("gaus","L");

			printf("eta = %.3f => mu = %.9f, sigma z0 = %.9f, sigma err = %.9f\n", eta,h6->GetFunction("gaus")->GetParameter(1),h6->GetFunction("gaus")->GetParameter(2), h6->GetFunction("gaus")->GetParError(2));

			h_sigma_z0->SetBinContent(h_sigma_z0->FindBin(eta), h6->GetFunction("gaus")->GetParameter(2));
			h_sigma_z0->SetBinError(h_sigma_z0->FindBin(eta), h6->GetFunction("gaus")->GetParError(2));
			h_sigma_z0->Draw("E1");
			//h6->Draw();
			C6->Update();
			//delete h6;
			
		/*	C7->Clear();  
			h7->GetXaxis()->SetTitle("dca_{rec}");
			recTree.Draw("hypot(h-M_Vx,k-M_Vy) - abs(radius)>>h7",cut && TCut(buffer));
			fit_Gauss(h7);
			//h7->Fit("gaus","L");

			printf("eta = %.3f => mu = %.9f, sigma = %.9f, sigma err = %.9f\n", eta,h7->GetFunction("gaus")->GetParameter(1),h7->GetFunction("gaus")->GetParameter(2), h7->GetFunction("gaus")->GetParError(2));
			
			h_sigma_dca->SetBinContent(h_sigma_dca->FindBin(eta), h7->GetFunction("gaus")->GetParameter(2));
			h_sigma_dca->SetBinError(h_sigma_dca->FindBin(eta), h7->GetFunction("gaus")->GetParError(2));
			h_sigma_dca->Draw("E1");
			//h7->Draw();
			C7->Update();
			//delete h7;
		*/	
			if(save)
			{
				h1->Write();
				h2->Write();
				h3->Write();
				h4->Write();
				h5->Write();
				h6->Write();
			}
			delete h1;
			delete h2;
			delete h3;
			delete h4;
			delete h5;
			delete h6;
		}//! end of loop over eta bins
	}//! end of for loop over pt bins
h_sigmadp->Write();
h_sigma_invPt->Write();
h_sigma_phi->Write();
h_sigma_theta->Write();
h_sigma_eta->Write();
h_sigma_z0->Write();
//h_sigma_dca->Write();	
output_file->Close();
	
return 0;
}

int plot_all_muon()
{
/*resolution_plots_Vs_eta("June18RecTree2GeVSinglemu.root","July12Reso2GeVmu","muon",2.0,true);
resolution_plots_Vs_eta("June18RecTree5GeVSinglemu.root","July12Reso5GeVmu","muon",5.0,true);
resolution_plots_Vs_eta("June18RecTree10GeVSinglemu.root","July12Reso10GeVmu","muon",10.0,true);
resolution_plots_Vs_eta("June18RecTree20GeVSinglemu.root","July12Reso20GeVmu","muon",20.0,true);
resolution_plots_Vs_eta("June18RecTree30GeVSinglemu.root","July12Reso30GeVmu","muon",30.0,true);
resolution_plots_Vs_eta("June18RecTree40GeVSinglemu.root","July12Reso40GeVmu","muon",40.0,true);
resolution_plots_Vs_eta("June18RecTree50GeVSinglemu.root","July12Reso50GeVmu","muon",50.0,true);
resolution_plots_Vs_eta("June18RecTree60GeVSinglemu.root","July12Reso60GeVmu","muon",60.0,true);
resolution_plots_Vs_eta("June18RecTree70GeVSinglemu.root","July12Reso70GeVmu","muon",70.0,true);
resolution_plots_Vs_eta("June18RecTree80GeVSinglemu.root","July12Reso80GeVmu","muon",80.0,true);
resolution_plots_Vs_eta("June18RecTree90GeVSinglemu.root","July12Reso90GeVmu","muon",90.0,true);
resolution_plots_Vs_eta("June18RecTree100GeVSinglemu.root","July12Reso100GeVmu","muon",100.0,true);
*/
resolution_plots_Vs_eta("Sept27RecTree2GeVSinglemu.root","Sept27Reso2GeVmu","muon",2.0,true);
resolution_plots_Vs_eta("Sept27RecTree5GeVSinglemu.root","Sept27Reso5GeVmu","muon",5.0,true);
resolution_plots_Vs_eta("Sept27RecTree10GeVSinglemu.root","Sept27Reso10GeVmu","muon",10.0,true);
resolution_plots_Vs_eta("Sept27RecTree20GeVSinglemu.root","Sept27Reso20GeVmu","muon",20.0,true);
resolution_plots_Vs_eta("Sept27RecTree30GeVSinglemu.root","Sept27Reso30GeVmu","muon",30.0,true);
resolution_plots_Vs_eta("Sept27RecTree40GeVSinglemu.root","Sept27Reso40GeVmu","muon",40.0,true);
resolution_plots_Vs_eta("Sept27RecTree50GeVSinglemu.root","Sept27Reso50GeVmu","muon",50.0,true);
resolution_plots_Vs_eta("Sept27RecTree60GeVSinglemu.root","Sept27Reso60GeVmu","muon",60.0,true);
resolution_plots_Vs_eta("Sept27RecTree70GeVSinglemu.root","Sept27Reso70GeVmu","muon",70.0,true);
resolution_plots_Vs_eta("Sept27RecTree80GeVSinglemu.root","Sept27Reso80GeVmu","muon",80.0,true);
resolution_plots_Vs_eta("Sept27RecTree90GeVSinglemu.root","Sept27Reso90GeVmu","muon",90.0,true);
resolution_plots_Vs_eta("Sept27RecTree100GeVSinglemu.root","Sept27Reso100GeVmu","muon",100.0,true);
return 0;
}
int plot_all_pion()
{
/*resolution_plots_Vs_eta("June18RecTree2GeVSinglepi.root","July12Reso2GeVpi","pion",2.0,true);
resolution_plots_Vs_eta("June18RecTree5GeVSinglepi.root","July12Reso5GeVpi","pion",5.0,true);
resolution_plots_Vs_eta("June18RecTree10GeVSinglepi.root","July12Reso10GeVpi","pion",10.0,true);
resolution_plots_Vs_eta("June18RecTree20GeVSinglepi.root","July12Reso20GeVpi","pion",20.0,true);
resolution_plots_Vs_eta("June18RecTree30GeVSinglepi.root","July12Reso30GeVpi","pion",30.0,true);
resolution_plots_Vs_eta("June18RecTree40GeVSinglepi.root","July12Reso40GeVpi","pion",40.0,true);
resolution_plots_Vs_eta("June18RecTree50GeVSinglepi.root","July12Reso50GeVpi","pion",50.0,true);
resolution_plots_Vs_eta("June18RecTree60GeVSinglepi.root","July12Reso60GeVpi","pion",60.0,true);
resolution_plots_Vs_eta("June18RecTree70GeVSinglepi.root","July12Reso70GeVpi","pion",70.0,true);
resolution_plots_Vs_eta("June18RecTree80GeVSinglepi.root","July12Reso80GeVpi","pion",80.0,true);
resolution_plots_Vs_eta("June18RecTree90GeVSinglepi.root","July12Reso90GeVpi","pion",90.0,true);
resolution_plots_Vs_eta("June18RecTree100GeVSinglepi.root","July12Reso100GeVpi","pion",100.0,true);
*/
resolution_plots_Vs_eta("Sept27RecTree2GeVSinglepi.root","Sept27Reso2GeVpi","pion",2.0,true);
resolution_plots_Vs_eta("Sept27RecTree5GeVSinglepi.root","Sept27Reso5GeVpi","pion",5.0,true);
resolution_plots_Vs_eta("Sept27RecTree10GeVSinglepi.root","Sept27Reso10GeVpi","pion",10.0,true);
resolution_plots_Vs_eta("Sept27RecTree20GeVSinglepi.root","Sept27Reso20GeVpi","pion",20.0,true);
resolution_plots_Vs_eta("Sept27RecTree30GeVSinglepi.root","Sept27Reso30GeVpi","pion",30.0,true);
resolution_plots_Vs_eta("Sept27RecTree40GeVSinglepi.root","Sept27Reso40GeVpi","pion",40.0,true);
resolution_plots_Vs_eta("Sept27RecTree50GeVSinglepi.root","Sept27Reso50GeVpi","pion",50.0,true);
resolution_plots_Vs_eta("Sept27RecTree60GeVSinglepi.root","Sept27Reso60GeVpi","pion",60.0,true);
resolution_plots_Vs_eta("Sept27RecTree70GeVSinglepi.root","Sept27Reso70GeVpi","pion",70.0,true);
resolution_plots_Vs_eta("Sept27RecTree80GeVSinglepi.root","Sept27Reso80GeVpi","pion",80.0,true);
resolution_plots_Vs_eta("Sept27RecTree90GeVSinglepi.root","Sept27Reso90GeVpi","pion",90.0,true);
resolution_plots_Vs_eta("Sept27RecTree100GeVSinglepi.root","Sept27Reso100GeVpi","pion",100.0,true);

return 0;
}

int plot_one()
{
resolution_plots_Vs_eta("testResoVsEtaInDet_all","all",true);
return 0;
}
