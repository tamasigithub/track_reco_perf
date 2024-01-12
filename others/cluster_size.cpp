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
void cluster_size()
{
	TChain c("cluster");
	c.Add("/user/tkar/work/data/rec/sel/Br30mmEC80mm/PU1k/ggF_clstrocc/*.root");
	std::cout<<"Total number of events: " <<c.GetEntries() << std::endl;
	
	//! Hist for cluster size
	TH1F *h10 = new TH1F("h10","cluster size layer 10;cluster size;number of clusters", 50,0,50);
	c.Draw("cluster_size>>h10","cluster_layerid==10");
	unsigned long tot_clusters_l10 = h10->Integral();
	std::cout<<"total number of clusters excluding single hits pre-clusterization: " << tot_clusters_l10 << std::endl;
	h10->Draw();

	TH1F *h10Sid = new TH1F("h10Sid","sensor ids of the hits in layer 10;sensor id;number of hits post clusterization",1000 ,2600e3,2700e3);
	c.Draw("hit_sensorid>>h10Sid","layerid==10");
	//! Hist for cluster size
	TH1F *h9 = new TH1F("h9","cluster size layer 9;cluster size;number of clusters", 50,0,50);
	c.Draw("cluster_size>>h9","cluster_layerid==9");
	unsigned long tot_clusters_l9 = h9->Integral();
	std::cout<<"total number of clusters excluding single hits pre-clusterization: " << tot_clusters_l9 << std::endl;
	h9->Draw();

	TH1F *h9Sid = new TH1F("h9Sid","sensor ids of the hits in layer 9;sensor id;number of hits post clusterization",1000 ,2340e3,2440e3);
	c.Draw("hit_sensorid>>h9Sid","layerid==9");
	//! Hist for cluster size
	TH1F *h8 = new TH1F("h8","cluster size layer 8;cluster size;number of clusters", 50,0,50);
	c.Draw("cluster_size>>h8","cluster_layerid==8");
	unsigned long tot_clusters_l8 = h8->Integral();
	std::cout<<"total number of clusters excluding single hits pre-clusterization: " << tot_clusters_l8 << std::endl;
	h8->Draw();

	TH1F *h8Sid = new TH1F("h8Sid","sensor ids of the hits in layer 8;sensor id;number of hits post clusterization",1000 ,2080e3,2180e3);
	c.Draw("hit_sensorid>>h8Sid","layerid==8");
	//hSid->Draw();

	//std::vector<unsigned int> *hitSenid;
	//c.SetBranchAddress("hit_sensorid",&hitSenid);
	
	//c.GetEntries();

	auto tot_hits_l10 = h10Sid->Integral();
	auto tot_hits_l9 = h9Sid->Integral();
	auto tot_hits_l8 = h8Sid->Integral();
	std::cout<<"total number of hits post clusterisation in layer 10: " << tot_hits_l10 <<std::endl;
	std::cout<<"total number of hits post clusterisation in layer 9: " << tot_hits_l9 <<std::endl;
	std::cout<<"total number of hits post clusterisation in layer 8: " << tot_hits_l8 <<std::endl;

	unsigned long tot_single_hits_l10 = tot_hits_l10 - tot_clusters_l10;
	unsigned long tot_single_hits_l9 = tot_hits_l9 - tot_clusters_l9;
	unsigned long tot_single_hits_l8 = tot_hits_l8 - tot_clusters_l8;
	std::cout<<"total number of single hits in layers 10 = " << tot_single_hits_l10 << std::endl;
	std::cout<<"total number of single hits in layers 9 = " << tot_single_hits_l9 << std::endl;
	std::cout<<"total number of single hits in layers 8 = " << tot_single_hits_l8 << std::endl;

	float h10_mean = h10->GetMean();
	h10->SetBinContent(2, tot_single_hits_l10);
	float corrected_mean_l10 = h10->GetMean();
	float h9_mean = h9->GetMean();
	h9->SetBinContent(2, tot_single_hits_l9);
	float corrected_mean_l9 = h9->GetMean();
	float h8_mean = h8->GetMean();
	h8->SetBinContent(2, tot_single_hits_l8);
	float corrected_mean_l8 = h8->GetMean();

	std::cout<<"Mean clustersize excluding single hits: " << h10_mean << std::endl;
	std::cout<<"Mean clustersize including single hits: " << corrected_mean_l10 << std::endl;
	std::cout<<"Mean clustersize excluding single hits: " << h9_mean << std::endl;
	std::cout<<"Mean clustersize including single hits: " << corrected_mean_l9 << std::endl;
	std::cout<<"Mean clustersize excluding single hits: " << h8_mean << std::endl;
	std::cout<<"Mean clustersize including single hits: " << corrected_mean_l8 << std::endl;
	
	return 0;
}
