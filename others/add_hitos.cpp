
#include <iostream>
#include <fstream>
#include <string>
#include<math.h>

#include "TROOT.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TPostScript.h"

#include "TAxis.h"
#include "TGaxis.h"
#include "TF1.h"

TH1F *h1 = nullptr;
TH1F *h2 = nullptr;
TH1F *h3 = nullptr;
TH1F *h4 = nullptr;
TH1F *h5 = nullptr;
TH1F *h6 = nullptr;
TH1F *h7 = nullptr;
TH1F *h8 = nullptr;
TH1F *h9 = nullptr;
TH1F *h10 =nullptr;
TH1F *h11 =nullptr;
TH1F *h_1 = nullptr;
TH1F *h_2 = nullptr;
TH1F *h_3 = nullptr;
TH1F *h_4 = nullptr;
TH1F *h_5 = nullptr;
TH1F *h_6 = nullptr;
TH1F *h_7 = nullptr;
TH1F *h_8 = nullptr;
TH1F *h_9 = nullptr;
TH1F *h_10 =nullptr;
TH1F *h_11 =nullptr;
TH1F *h_12 =nullptr;
TH1F *h_13 =nullptr;
TH1F *h_14 =nullptr;
TH1F *h_15 =nullptr;
TH1F *h_16 =nullptr;
TH1F *h_17 =nullptr;

int h_add()
{
	TFile *f1 = new TFile("filename.root", "READ");
	h1 = (TH1F*)f1->Get("hitL1");
	h2 = (TH1F*)f1->Get("hitL2");
	h3 = (TH1F*)f1->Get("hitL3");
	h4 = (TH1F*)f1->Get("hitL4");
	h5 = (TH1F*)f1->Get("hitL5");
	h6 = (TH1F*)f1->Get("hitL6");
	h7 = (TH1F*)f1->Get("hitL7");
	h8 = (TH1F*)f1->Get("hitL8");
	h9 = (TH1F*)f1->Get("hitL9");
	h10 = (TH1F*)f1->Get("hitL10");
	h11 = (TH1F*)f1->Get("hitL11");
	h12 = (TH1F*)f1->Get("hitL12");
	h13 = (TH1F*)f1->Get("hitL13");
	h14 = (TH1F*)f1->Get("hitL14");
	h15 = (TH1F*)f1->Get("hitL15");
	h16 = (TH1F*)f1->Get("hitL16");
	h17 = (TH1F*)f1->Get("hitL17");

	h_1->Add(h1);
	h_2->Add(h2);
	h_3->Add(h3);
	h_4->Add(h4);
	h_5->Add(h5);
	h_6->Add(h6);
	h_7->Add(h7);
	h_8->Add(h8);
	h_9->Add(h9);
	h_10->Add(h10);
	h_11->Add(h11);
	h_12->Add(h12);
	h_13->Add(h13);
	h_14->Add(h14);
	h_15->Add(h15);
	h_16->Add(h16);
	h_17->Add(h17);

	h1->delete;
	h2->delete;
	h3->delete;
	h4->delete;
	h5->delete;
	h6->delete;
	h7->delete;
	h8->delete;
	h9->delete;
	h10->delete;
	h11->delete;
	h12->delete;
	h13->delete;
	h14->delete;
	h15->delete;
	h16->delete;
	h17->delete;
	
	
return 0;
}
