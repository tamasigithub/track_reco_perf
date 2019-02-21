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
#include <vector>
#include <algorithm> 
#include <functional>
#include <fstream>
#include <string>
#include <math.h>

int Njeteff_calo(const char* output_file_name = "test", bool debug = true)
{
	
	//! selections
	int Njet_max = 5;
	float eta_max = 1.5;
	//! load input files
	TChain tree("m_collectionTree");
	tree.Add("./../test_ntuple.root");
	if(debug) std::cout<<"m_collectionTree opened with " << tree.GetEntries() << " entries" <<std::endl;

	const float pt_min = 50e3, pt_max = 500e3; //! in MeV
	const float ptcut = 60e3; 
	
	//! book histograms
	TH1::SetDefaultSumw2(true);
	TH1* h_tJeff1 = new TH1F("h_tJeff1"," Track Jet efficiency", nbins, pt_min, pt_max );
	TH1* h_tJeff2 = new TH1F("h_tJeff2"," Track Jet efficiency", nbins, pt_min, pt_max );
	TH1* h_tJeff3 = new TH1F("h_tJeff3"," Track Jet efficiency", nbins, pt_min, pt_max );
	TH1* h_tJeff4 = new TH1F("h_tJeff4"," Track Jet efficiency", nbins, pt_min, pt_max );
	TH1* h_tJeff5 = new TH1F("h_tJeff5"," Track Jet efficiency", nbins, pt_min, pt_max );

	tree.Draw("truthPt >> ")

	

return 0;
}
