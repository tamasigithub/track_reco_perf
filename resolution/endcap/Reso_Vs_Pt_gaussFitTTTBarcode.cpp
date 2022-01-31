///*** Resolution plots for the track parameters as a funtion of eta***///
/// Set save = true to save the plots in path/./plots/resolution_plots/
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
#include "TChain.h"
void ScaleAxis(TAxis *a, Double_t Scale)
{
  if (!a) return; // just a precaution
  if (a->GetXbins()->GetSize())
    {
      // an axis with variable bins
      // note: bins must remain in increasing order, hence the "Scale"
      // function must be strictly (monotonically) increasing
      TArrayD X(*(a->GetXbins()));
      for(Int_t i = 0; i < X.GetSize(); i++) X[i] = X[i]*Scale;
      a->Set((X.GetSize() - 1), X.GetArray()); // new Xbins
    }
  else
    {
      // an axis with fix bins
      // note: we modify Xmin and Xmax only, hence the "Scale" function
      // must be linear (and Xmax must remain greater than Xmin)
      a->Set( a->GetNbins(),
              a->GetXmin()*Scale, // new Xmin
              a->GetXmax()*Scale ); // new Xmax
    }
  return;
}
void ScaleXaxis(TH1 *h, Double_t Scale)
{
  if (!h) return; // just a precaution
  ScaleAxis(h->GetXaxis(), Scale);
  return;
}
//const char* out_path = "/media/tamasi/DriveT/tamasi/Desktop/PHD/talks_preps/ctd2k19/plots/resolution";
const char* out_path = "./plots";
//! Define Cut
TCut mu_cut = "abs(M_pdg)==13 && M_barcode > 0 && abs(M_Vz) < 100 && abs(M_Vx)<5 && abs(M_Vy)<5";
TCut pi_cut = "abs(M_pdg)==211 && M_barcode > 0 && abs(M_Vz) < 100 && abs(M_Vx)<5 && abs(M_Vy)<5";
TCut e_cut  = "abs(M_pdg)==11 && M_barcode > 0 && abs(M_Vz) < 100 && abs(M_Vx)<5 && abs(M_Vy)<5";
//! use this for TTT track resolution with barcode matching
TCut all_cut= "abs(station)==1 && Tid > 0 && abs(kappa_pull)<=5 && abs(M_pt)>2000 && abs(M_eta)>1.7 && abs(M_Vz) < 100 && abs(M_Vx) < 5 && abs(M_Vy) < 5 ";
//! path for input files
const char* path = "";
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
    	xmin_ = h->GetFunction("gaus")->GetParameter(1) - 2.3 * h->GetFunction("gaus")->GetParameter(2);
    	xmax_ = h->GetFunction("gaus")->GetParameter(1) + 2.3 * h->GetFunction("gaus")->GetParameter(2);
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
int resolution_plots_Vs_pt
(const char* output_file_name, /*const char* p_type = "muon",*/ bool save = false)
{
	TChain recTree("m_recTree");
	//! PU0 20mm
	//recTree.Add("/home/tamasi/repo_tamasi/rec_files/PU0hh4b_m260_recTree_200001_opt.root");
	//! PU1000 hh4b 30mm
	//recTree.Add("/media/tamasi/Z/PhD/FCC/Castellated/rec_files/PU1000*");
	//! PU0 hh4b 30mm
	//recTree.Add("/media/tamasi/Z/PhD/FCC/Castellated/rec_files/MB_recTree_3*");
	//recTree.Add("/media/tamasi/Z/PhD/FCC/Castellated/rec_files/PU1000*");
	//recTree.Add("/media/tamasi/Z/PhD/FCC/Castellated/rec_files/PU1K_hh4bm260_30mm_sig5/*.root");
        //recTree.Add("/home/tamasi/repo_tamasi/rec_files/rec_files/30mm/PU1k/ggFhh4b_SM/*.root");
        //recTree.Add("/home/tamasi/repo_tamasi/rec_files/rec_files/30mm/PU0/ggFhh4b_SM/*.root");
	recTree.Add("/user/tkar/work/data/rec/for_opt/Br30mmEC53mm/ggF1.0/*.root");
	
	std::cout<<"rec entries:"<<recTree.GetEntries()<<std::endl;
	TCut cut;
	//const char* type = p_type;
	const char* type = "all";
	//const char* type = "pion";
	if(type == "muon"){ cut = mu_cut;}
	else if(type == "pion") cut = pi_cut;
	else if(type == "electron") cut = e_cut;
	else if(type == "all") cut = all_cut;
	else{ std::cout <<"enter particle type"; return 0;} 
	
	//int ptbin = 12;
    	////double ptmin   = 1500, ptmax = 100500;
	//double bincenter[] = {2000, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
	//double binlow[] = {0, 2000, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
	//double binhigh[] = {0, 2000, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
	int ptbin = 9;
	double bincenter[] = {2000, 5000, 10000, 20000, 30000, 40000, 50000, 70000, 100000};
	double binlow[] = {0, 2000, 5000, 10000, 20000, 30000, 40000, 50000, 70000, 100000};
	double binhigh[] = {0, 2000, 5000, 10000,20000, 30000, 40000, 50000, 70000, 100000};
	//int ptbin = 7;
	//double bincenter[] = {2000, 5000, 10000, 15000, 30000, 50000, 80000};
	//double binlow[] = {0, 2000, 5000, 10000, 15000, 30000, 50000, 80000};
	//double binhigh[] = {0, 2000, 5000, 10000,15000, 30000, 50000, 80000};
	std::cout<<"size :" << sizeof(bincenter)/sizeof(double) <<std::endl;
	for (unsigned ik = 0; ik < sizeof(bincenter)/sizeof(double); ++ik)
	{
		float binwidth_low = 0;
		float binwidth_high = 0;
		if(ik == 0) 
		{	
			binwidth_low = 0.5*bincenter[ik];
			binhigh[ik] = binlow[ik] + binwidth_low;
		}
		else 
		{
			binwidth_low = 0.5*(bincenter[ik] - bincenter[ik-1]);
		}
		if (ik == ptbin-1)
		{
			binwidth_high = 1.1*bincenter[ik-1];
		}
		else
		{
			binwidth_high = 0.5*(bincenter[ik+1] - bincenter[ik]);
		}
		binlow[ik+1] = bincenter[ik] - binwidth_low;
		binhigh[ik+1] = bincenter[ik] + binwidth_high;
	//	std::cout<<"binlow[" <<ik <<"] : " << binlow[ik] << std::endl; 
	}
	for (unsigned ik = 0; ik <= sizeof(bincenter)/sizeof(double); ++ik)
	{
	
		std::cout<<"binlow[" <<ik <<"] : " << binlow[ik] << std::endl; 
		std::cout<<"binhigh[" <<ik <<"] : " << binhigh[ik] << std::endl; 
	}
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
	TH1D *h_sigmadp = new TH1D("h_sigmadp", "Relative Pt resolution Vs P_{t}",ptbin,binlow);
	h_sigmadp->SetLineColor(1);
  	h_sigmadp->SetLineWidth(2);
  	h_sigmadp->SetMarkerColor(1);
  	h_sigmadp->SetMarkerStyle(21);
  	h_sigmadp->GetXaxis()->SetTitle("P_{t_gen} [MeV/c]");
	h_sigmadp->GetYaxis()->SetTitleOffset(1.3);
  	h_sigmadp->GetYaxis()->SetTitle("#sigma_{#Delta(p_{t})/gen_p_{t}}");
	//! sigma invpt Vs eta//
	TH1D *h_sigma_invPt = new TH1D("h_sigma_invPt", "Inverse Pt resolution Vs P_{t}",ptbin,binlow);
	h_sigma_invPt->SetLineColor(1);
  	h_sigma_invPt->SetLineWidth(2);
  	h_sigma_invPt->SetMarkerColor(1);
  	h_sigma_invPt->SetMarkerStyle(21);
  	h_sigma_invPt->GetXaxis()->SetTitle("P_{t_gen} [MeV/c]");
	h_sigma_invPt->GetYaxis()->SetTitleOffset(1.3);
  	h_sigma_invPt->GetYaxis()->SetTitle("#sigma_{#Delta(1/p_{t})} [MeV^{-1}/c]");
	//! sigma phi Vs eta//
	TH1D *h_sigma_phi = new TH1D("h_sigma_phi", "Phi resolution Vs P_{t}",ptbin,binlow);
        h_sigma_phi->SetLineColor(1);
        h_sigma_phi->SetLineWidth(2);
        h_sigma_phi->SetMarkerColor(1);
        h_sigma_phi->SetMarkerStyle(21);
        h_sigma_phi->GetXaxis()->SetTitle("P_{t_gen} [MeV/c]");
        h_sigma_phi->GetYaxis()->SetTitleOffset(1.3);
        h_sigma_phi->GetYaxis()->SetTitle("#sigma_{#Delta(#phi)} [rad]");
	//! sigma theta Vs eta//
	TH1D *h_sigma_theta = new TH1D("h_sigma_theta", "Theta resolution Vs P_{t}",ptbin,binlow);
        h_sigma_theta->SetLineColor(1);
        h_sigma_theta->SetLineWidth(2);
        h_sigma_theta->SetMarkerColor(1);
        h_sigma_theta->SetMarkerStyle(21);
        h_sigma_theta->GetXaxis()->SetTitle("P_{t_gen} [MeV/c]");
        h_sigma_theta->GetYaxis()->SetTitleOffset(1.3);
        h_sigma_theta->GetYaxis()->SetTitle("#sigma_{#Delta(#theta)} [rad]");
	//! sigma eta Vs eta//
	TH1D *h_sigma_eta = new TH1D("h_sigma_eta", "Eta resolution Vs P_{t}",ptbin,binlow);
        h_sigma_eta->SetLineColor(1);
        h_sigma_eta->SetLineWidth(2);
        h_sigma_eta->SetMarkerColor(1);
        h_sigma_eta->SetMarkerStyle(21);
        h_sigma_eta->GetXaxis()->SetTitle("P_{t_gen} [MeV/c]");
        h_sigma_eta->GetYaxis()->SetTitleOffset(1.3);
        h_sigma_eta->GetYaxis()->SetTitle("#sigma_{#Delta(#eta)}");
	//! sigma z0 Vs eta//
	TH1D *h_sigma_z0 = new TH1D("h_sigma_z0", "Z0 resolution Vs P_{t}",ptbin,binlow);
        h_sigma_z0->SetLineColor(1);
        h_sigma_z0->SetLineWidth(2);
        h_sigma_z0->SetMarkerColor(1);
        h_sigma_z0->SetMarkerStyle(21);
        h_sigma_z0->GetXaxis()->SetTitle("P_{t_gen} [MeV/c]");
        h_sigma_z0->GetYaxis()->SetTitleOffset(1.3);
        h_sigma_z0->GetYaxis()->SetTitle("#sigma_{#Delta(z0)} [mm]");
	//! sigma dca Vs eta//
	TH1D *h_sigma_dca = new TH1D("h_sigma_dca", "Dca resolution Vs P_{t}",ptbin,binlow);
        h_sigma_dca->SetLineColor(1);
        h_sigma_dca->SetLineWidth(2);
        h_sigma_dca->SetMarkerColor(1);
        h_sigma_dca->SetMarkerStyle(21);
        h_sigma_dca->GetXaxis()->SetTitle("P_{t_gen} [MeV/c]");
        h_sigma_dca->GetYaxis()->SetTitleOffset(1.3);
        h_sigma_dca->GetYaxis()->SetTitle("#sigma_{dca} [mm]");
	
	h_sigmadp->SetDirectory(0);	
	h_sigma_invPt->SetDirectory(0);
	h_sigma_phi->SetDirectory(0);
	h_sigma_theta->SetDirectory(0);
	h_sigma_eta->SetDirectory(0);
	h_sigma_z0->SetDirectory(0);
	h_sigma_dca->SetDirectory(0);
	
	char out_file_root[1023];
	sprintf(out_file_root,"%s/%s.root",out_path,output_file_name);
	TFile* output_file = new TFile(out_file_root, "RECREATE");	
	//! divide eta into small bins and fill each bin with a histogram
	//! Next fit all these small histograms with gauss fit and optimise the fit about the mean
	for (int  k = 0; k < sizeof(bincenter)/sizeof(double); k++)
	{
		if(k < 2)
		{
			relptmin     	= -0.1, relptmax    = 0.1;
			inv_ptmin    	= -4.5e-5, inv_ptmax = 3e-5;
			phimin	    	= -0.01,phimax      = 0.01;
			zmin         	= -10.0,  zmax        = 10.0;
			thetamin     	= -0.01,thetamax   = 0.01;
			eta_min      	= -0.01,eta_max    = 0.01;
			dcamin	    	= -120,  dcamax       = 130;

		}
		else if(k >=2 && k < 4)
		{
			relptmin     	= -0.2, relptmax    = 0.2;
			inv_ptmin    	= -1.5e-5, inv_ptmax = 1.5e-5;
			phimin	    	= -0.003,phimax      = 0.003;
			zmin         	= -8.0,  zmax        = 8.0;
			thetamin     	= -0.003,thetamax   = 0.003;
			eta_min      	= -0.003,eta_max    = 0.003;
			dcamin	    	= -50,  dcamax       = 130;

		}		
		else if(k >= 4 && k<8)
		{
			relptmin     	= -0.4, relptmax    = 0.4;
			inv_ptmin    	= -1e-5, inv_ptmax = 1e-5;
			phimin	    	= -0.002,phimax      = 0.002;
			zmin         	= -6.0,  zmax        = 6.0;
			thetamin     	= -0.002,thetamax   = 0.002;
			eta_min      	= -0.002,eta_max    = 0.002;
			dcamin	    	= -50,  dcamax       = 130;

		}
		else if(k >=8 && k <12)
		{
			relptmin     	= -0.8, relptmax    = 0.8;
			inv_ptmin    	= -1e-5, inv_ptmax = 1e-5;
			phimin	    	= -0.002,phimax      = 0.002;
			zmin         	= -4.0,  zmax        = 4.0;
			thetamin     	= -0.002,thetamax   = 0.002;
			eta_min      	= -0.002,eta_max    = 0.002;
			dcamin	    	= -50,  dcamax       = 130;

		}
//		double eta = -1.2;
		TH1F *h1 = new TH1F("h1", "Relative pt", binNum,relptmin,relptmax);
		TH1F *h2 = new TH1F("h2", "Inverse pt", binNum,inv_ptmin,inv_ptmax);
		TH1F *h3 = new TH1F("h3", "Phi", binNum,phimin,phimax);
		TH1F *h4 = new TH1F("h4", "Theta", binNum,thetamin,thetamax);
		TH1F *h5 = new TH1F("h5", "Eta", binNum,eta_min,eta_max);
		TH1F *h6 = new TH1F("h6", "Z0", binNum,zmin,zmax);
		TH1F *h7 = new TH1F("h7", "dca", binNum,dcamin,dcamax);
		//h->SetDirectory(0);
		//! define pt range in which you want to fit a gauss function
		sprintf(buffer, "((M_pt > %f) && (M_pt < %f))", binlow[k+1], binhigh[k+1]);// corresponds to a binwidth of 1000MeV/c i.e. +- 500 MeV/c about the bincenter
		C1->Clear();
		h1->GetXaxis()->SetTitle("(pt_{rec} - pt_{gen})/pt_{gen} ");
		recTree.Draw("(Pt_n - M_pt)/M_pt>>h1",cut && TCut(buffer));
		fit_Gauss(h1);
		//h1->Fit("gaus","L");
		printf("pt = %.3f => mu = %.9f, sigma pt = %.9f, sigma err = %.9f\n", bincenter[k],h1->GetFunction("gaus")->GetParameter(1),h1->GetFunction("gaus")->GetParameter(2), h1->GetFunction("gaus")->GetParError(2));

		h_sigmadp->SetBinContent(h_sigmadp->FindBin(bincenter[k]), h1->GetFunction("gaus")->GetParameter(2));
    		h_sigmadp->SetBinError(h_sigmadp->FindBin(bincenter[k]), h1->GetFunction("gaus")->GetParError(2));
    		h_sigmadp->Draw("E1");
		//h1->Draw();
		C1->Update();
		//delete h1;
	
		C2->Clear();
		h2->GetXaxis()->SetTitle("pt_inv_{rec} - pt_inv_{gen} ");
                recTree.Draw("(1/Pt_n - 1/M_pt)>>h2",cut && TCut(buffer));
                fit_Gauss(h2);
		//h2->Fit("gaus","L");

		printf("pt = %.3f => mu = %.9f, sigma inv_pt= %.9f, sigma err = %.9f\n", bincenter[k],h2->GetFunction("gaus")->GetParameter(1),h2->GetFunction("gaus")->GetParameter(2), h2->GetFunction("gaus")->GetParError(2));

                h_sigma_invPt->SetBinContent(h_sigma_invPt->FindBin(bincenter[k]), h2->GetFunction("gaus")->GetParameter(2));
                h_sigma_invPt->SetBinError(h_sigma_invPt->FindBin(bincenter[k]), h2->GetFunction("gaus")->GetParError(2));
                h_sigma_invPt->Draw("E1");
		//h2->Draw();
		C2->Update();
                //delete h2;
		
		C3->Clear();
		h3->GetXaxis()->SetTitle("phi_{rec} - phi_{gen} ");
                recTree.Draw("Phi013 - M_phi>>h3",cut && TCut(buffer));
                fit_Gauss(h3);
                //h3->Fit("gaus","L");

               printf("pt = %.3f => mu = %.9f, sigma phi= %.9f, sigma err = %.9f\n", bincenter[k],h3->GetFunction("gaus")->GetParameter(1),h3->GetFunction("gaus")->GetParameter(2), h3->GetFunction("gaus")->GetParError(2));

                h_sigma_phi->SetBinContent(h_sigma_phi->FindBin(bincenter[k]), h3->GetFunction("gaus")->GetParameter(2));
                h_sigma_phi->SetBinError(h_sigma_phi->FindBin(bincenter[k]), h3->GetFunction("gaus")->GetParError(2));
                h_sigma_phi->Draw("E1");
                //h3->Draw();	
		C3->Update();
                //delete h3;
		
		C4->Clear();
		h4->GetXaxis()->SetTitle("theta_{rec} - theta_{gen} ");
                recTree.Draw("Theta13 - M_theta>>h4",cut && TCut(buffer));
                fit_Gauss(h4);
		//h4->Fit("gaus","L");

                printf("pt = %.3f => mu = %.9f, sigma theta= %.9f, sigma err = %.9f\n", bincenter[k],h4->GetFunction("gaus")->GetParameter(1),h4->GetFunction("gaus")->GetParameter(2), h4->GetFunction("gaus")->GetParError(2));

                h_sigma_theta->SetBinContent(h_sigma_theta->FindBin(bincenter[k]), h4->GetFunction("gaus")->GetParameter(2));
                h_sigma_theta->SetBinError(h_sigma_theta->FindBin(bincenter[k]), h4->GetFunction("gaus")->GetParError(2));
                h_sigma_theta->Draw("E1");
                //h4->Draw();
        	C4->Update();
                //delete h4;
        
		C5->Clear();
                h5->GetXaxis()->SetTitle("eta_{rec} - eta_{gen} ");
                recTree.Draw("Eta13 - M_eta>>h5",cut && TCut(buffer));
                fit_Gauss(h5);
                //h5->Fit("gaus","L");

                printf("pt = %.3f, etabin = %.6d => mu = %.9f, sigma eta= %.9f, sigma err = %.9f\n", bincenter[k],h_sigma_eta->FindBin(bincenter[k]),h5->GetFunction("gaus")->GetParameter(1),h5->GetFunction("gaus")->GetParameter(2), h5->GetFunction("gaus")->GetParError(2));

                h_sigma_eta->SetBinContent(h_sigma_eta->FindBin(bincenter[k]), h5->GetFunction("gaus")->GetParameter(2));
                h_sigma_eta->SetBinError(h_sigma_eta->FindBin(bincenter[k]), h5->GetFunction("gaus")->GetParError(2));
                h_sigma_eta->Draw("E1");
                //h5->Draw();
         	C5->Update();
                //delete h5;

		C6->Clear();
                h6->GetXaxis()->SetTitle("z0_{rec} - z0_{gen} ");
                recTree.Draw("Z013 - M_Vz>>h6",cut && TCut(buffer));
                fit_Gauss(h6);
                //h6->Fit("gaus","L");

                printf("pt = %.3f => mu = %.9f, sigma z0= %.9f, sigma err = %.9f\n", bincenter[k],h6->GetFunction("gaus")->GetParameter(1),h6->GetFunction("gaus")->GetParameter(2), h6->GetFunction("gaus")->GetParError(2));

                h_sigma_z0->SetBinContent(h_sigma_z0->FindBin(bincenter[k]), h6->GetFunction("gaus")->GetParameter(2));
                h_sigma_z0->SetBinError(h_sigma_z0->FindBin(bincenter[k]), h6->GetFunction("gaus")->GetParError(2));
                h_sigma_z0->Draw("E1");
                //h6->Draw();
          	C6->Update();
                //delete h6;
            	
		C7->Clear();  
                h7->GetXaxis()->SetTitle("dca_{rec}");
                //recTree.Draw("hypot(h-M_Vx,k-M_Vy) - abs(radius)>>h7",cut && TCut(buffer));
                recTree.Draw("dca-M_dca>>h7",cut && TCut(buffer));
                fit_Gauss(h7);
                //h7->Fit("gaus","L");

                printf("pt = %.3f => mu = %.9f, sigma = %.9f, sigma err = %.9f\n", bincenter[k],h7->GetFunction("gaus")->GetParameter(1),h7->GetFunction("gaus")->GetParameter(2), h7->GetFunction("gaus")->GetParError(2));
		
                h_sigma_dca->SetBinContent(h_sigma_dca->FindBin(bincenter[k]), h7->GetFunction("gaus")->GetParameter(2));
                h_sigma_dca->SetBinError(h_sigma_dca->FindBin(bincenter[k]), h7->GetFunction("gaus")->GetParError(2));
                h_sigma_dca->Draw("E1");
                //h7->Draw();
	      	C7->Update();
                //delete h7;
		
		if(save)
		{
			h1->Write();
			h2->Write();
			h3->Write();
			h4->Write();
			h5->Write();
			h6->Write();
			h7->Write();
		}
		delete h1;
		delete h2;
		delete h3;
		delete h4;
		delete h5;
		delete h6;
		delete h7;
	}
ScaleXaxis(h_sigmadp,1e-3);
h_sigmadp->GetXaxis()->SetTitle("p_{T} [GeV/c]");
h_sigmadp->Scale(1e2);// for %
h_sigmadp->GetYaxis()->SetTitle("#sigma_{#Delta(p_{T})/gen_p_{T}} [%]");
h_sigmadp->Write();

ScaleXaxis(h_sigma_invPt,1e-3);
h_sigma_invPt->GetXaxis()->SetTitle("p_{T} [GeV/c]");
h_sigma_invPt->Scale(1e3);// for GeV-1
h_sigma_invPt->GetYaxis()->SetTitle("#sigma_{#Delta(1/p_{T})} [GeV^{-1}/c]");
h_sigma_invPt->Write();

ScaleXaxis(h_sigma_phi,1e-3);
h_sigma_phi->GetXaxis()->SetTitle("p_{T} [GeV/c]");
h_sigma_phi->Write();

ScaleXaxis(h_sigma_theta,1e-3);
h_sigma_theta->GetXaxis()->SetTitle("p_{T} [GeV/c]");
h_sigma_theta->Write();

ScaleXaxis(h_sigma_eta,1e-3);
h_sigma_eta->GetXaxis()->SetTitle("p_{T} [GeV/c]");
h_sigma_eta->Write();

ScaleXaxis(h_sigma_z0,1e-3);
h_sigma_z0->GetXaxis()->SetTitle("p_{T} [GeV/c]");
h_sigma_z0->Write();

ScaleXaxis(h_sigma_dca,1e-3);
h_sigma_dca->GetXaxis()->SetTitle("p_{T} [GeV/c]");
h_sigma_dca->Write();	
output_file->Close();
	
return 0;
}
int plot_reso_vs_pt()
{
	resolution_plots_Vs_pt("ResoVspt_VxVy5_ggFhh4bPU1k_30mm_eta1.7_1",true);
	//resolution_plots_Vs_pt("ResoVspt_VxVy5_PU0_100030mm_1",true);
	//resolution_plots_Vs_pt("testResoVspt_all1.4_5GeV",true);
	return 0;
}

