//summary and comparison of pt and z vertext resolution of 3 different triplets as track triggers
//summary of RMS of inverse pt resolution wrt pt ranging from 1GeV/c to 100GeV/c
#include <iostream>
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
#include <fstream>
#include <string>
#include<math.h>


TCanvas *c1 = new TCanvas();

const char * runNumber = 0;
const char * mc_p = 0;
//clears the txt file
void deleteText(const char* pix_size, const char* trigger_position) {
    const char* txt_path = "/home/tamasi/repo_tamasi/mu3e/run/my_macros";
    char txt_file[1023];
    sprintf(txt_file,"%s/summary_layerON_%s_%s.txt",txt_path,pix_size,trigger_position);
    std::ofstream ofs;
    ofs.open(txt_file, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void deleteAll()
{
    deleteText("40","");
    deleteText("40","M");
    deleteText("40","In");

}

//writes the runno,p,rms and error in a txt file
void write_file(const char* pix_size, const char* trigger_position, double rms, double error)
{
    const char* txt_path = "/home/tamasi/repo_tamasi/mu3e/run/my_macros";
    char txt_file[1023];
    sprintf(txt_file,"%s/summary_layerON_%s_%s.txt",txt_path,pix_size, trigger_position);
    std::ofstream ofs;
    ofs.open (txt_file, std::ofstream::out | std::ofstream::app);
    ofs<<runNumber<<" "<<mc_p<<" "<<rms*pow(10,3)<<" "<<error*pow(10,3)<<"\n";
    ofs.close();

}

void draw(const char *pt, const char* pix_size, const char* trigger_position)
{
    double binNum = 100;
    double ptmin = -0.7, ptmax = 0.00001;
    c1->Clear();
    char histo_title[1023];
    sprintf(histo_title,"Inverse momentum Resolution for %s x %s with p=%sGeV",pix_size,pix_size,pt);
    TH1F* h_p = new TH1F("h_p","histo_title",binNum,ptmin,ptmax);
    if (trigger_position == "In") segs_t1->Draw("(1/pt_exact)-(1/mc_pt)>>h_p","mc_pid==-13");
    else if (trigger_position == "M") segs_t2->Draw("(1/pt_exact)-(1/mc_pt)>>h_p","mc_pid==-13");
    else segs_t9->Draw("(1/pt_exact)-(1/mc_pt)>>h_p","mc_pid==-13");
    h_p->SetXTitle("delta p [MeV/c]");
    h_p->SetTitle(histo_title);
    h_p->Draw();
    c1->Update();

    double pRMS = h_p->GetRMS();
    double PRMS_err = h_p->GetRMSError();
    write_file(pix_size,trigger_position, pRMS, PRMS_err);
}


//opens the reconstructed root file with run# = "run_no" and momentum "p"(1-10 GeV/c)
//hence calls the draw funtion. This function draws the resolution plots and fetches the rms and errors from this and hence calls the write function.
//the write function creates a txt file and prints in that
//the run_no, the momentum p, rms, and error..
void rms(const char *run_no, const char *p, const char *pixel_size, const char* trig_position = "")
{
runNumber = run_no;
mc_p = p;
const char *file_path = "/home/tamasi/repo_tamasi/mu3e/run/my_macros";
char rec_file_name[1023];
sprintf(rec_file_name, "%s/trial%s_%s%s.root",file_path,run_no,trig_position,pixel_size);
TFile *f = TFile::Open(rec_file_name);
draw(p,pixel_size,trig_position);
}


summary_40_layersON_out()
{
    rms("400","1","40");
    rms("401","2","40");
    rms("402","3","40");
    rms("403","4","40");
    rms("404","5","40");
    rms("405","10","40");
//    rms("406","15","40");
    rms("407","20","40");
//    rms("408","25","40");
    rms("409","30","40");
//    rms("410","35","40");
    rms("411","40","40");
//    rms("412","45","40");
    rms("413","50","40");
//    rms("414","55","40");
    rms("415","60","40");
//    rms("416","65","40");
    rms("417","70","40");
//    rms("418","75","40");
    rms("419","80","40");
//    rms("420","85","40");
    rms("421","90","40");
//    rms("422","95","40");
    rms("423","100","40");

}
summary_40_layersON_mid()
{
    rms("400","1","40", "M");
    rms("401","2","40", "M");
    rms("402","3","40", "M");
    rms("403","4","40", "M");
    rms("404","5","40", "M");
    rms("405","10","40", "M");
//    rms("406","15","40", "M");
    rms("407","20","40", "M");
//    rms("408","25","40", "M");
    rms("409","30","40", "M");
//    rms("410","35","40", "M");
    rms("411","40","40", "M");
//    rms("412","45","40", "M");
    rms("413","50","40", "M");
//    rms("414","55","40", "M");
    rms("415","60","40", "M");
//    rms("416","65","40", "M");
    rms("417","70","40", "M");
//    rms("418","75","40", "M");
    rms("419","80","40", "M");
//    rms("420","85","40", "M");
    rms("421","90","40", "M");
//    rms("422","95","40", "M");
    rms("423","100","40", "M");

}
summary_40_layersON_in()
{
    rms("400","1","40", "In");
    rms("401","2","40", "In");
    rms("402","3","40", "In");
    rms("403","4","40", "In");
    rms("404","5","40", "In");
    rms("405","10","40", "In");
//    rms("406","15","40", "In");
    rms("407","20","40", "In");
//    rms("408","25","40", "In");
    rms("409","30","40", "In");
//    rms("410","35","40", "In");
    rms("411","40","40", "In");
//    rms("412","45","40", "In");
    rms("413","50","40", "In");
//    rms("414","55","40", "In");
    rms("415","60","40", "In");
//    rms("416","65","40", "In");
    rms("417","70","40", "In");
//    rms("418","75","40", "In");
    rms("419","80","40", "In");
//    rms("420","85","40", "In");
    rms("421","90","40", "In");
//    rms("422","95","40", "In");
    rms("423","100","40", "In");

}

void summary_all()
{
   summary_40_layersON_out();
   summary_40_layersON_mid();
   summary_40_layersON_in();

}

                    ///***** Draw Summary Plots*****///
///*the code above helps create text file that contains rms and errors of each of the plots above*///
///*this text file is then read and plotted here in the code below*///
void SaveCanvas(TCanvas *C, char *name)
{
    const char *path = "/home/tamasi/repo_tamasi/mu3e/run/my_macros/new_plots/summary_pt";
    char full_name[1023];
    sprintf(full_name,"%s/summary_%s.root", path, name);
    C->SaveAs(full_name);
    sprintf(full_name,"%s/summary_%s.pdf", path, name);
    C->SaveAs(full_name);
    sprintf(full_name,"%s/summary_%s.png", path, name);
    C->SaveAs(full_name);
    sprintf(full_name,"%s/summary_%s.C", path, name);
    C->SaveAs(full_name);

}
//Multi Graph
void draw_together(const char* dim1 = "40",const char* dim2 = "40")
{
    c1->Clear();
    const char* txt_path = "/home/tamasi/repo_tamasi/mu3e/run/my_macros";
    char txt_file1[1023];//40 out blue
    char txt_file2[1023];//m red
    char txt_file3[1023];//in green

    char plot_title[1023];
    sprintf(txt_file1,"%s/summary_layerON_%s_.txt",txt_path,dim1);
    sprintf(txt_file2,"%s/summary_layerON_%s_M.txt",txt_path,dim2);
    sprintf(txt_file3,"%s/summary_layerON_%s_In.txt",txt_path,dim1);

    sprintf(plot_title,"Inverse Momentum Resolution for triplet trigger at different radii as a fuction of p ");

    TTree *t1 = new TTree ("t1", "t1");
    t1->ReadFile(txt_file1,"run_Num:pt:rms:err");
    t1->Draw("pt:rms:err","","goff");
//    TGraphErrors *g1 = new TGraphErrors(24,t1->GetV1(),t1->GetV2(),0,t1->GetV3());

    TGraphErrors *g1 = new TGraphErrors(15,t1->GetV1(),t1->GetV2(),0,t1->GetV3());
    g1->SetMarkerColor(kBlue);
    g1->SetLineColor(kBlue);
    g1->SetLineWidth(2);
    g1->SetMarkerStyle(3);
    g1->SetFillStyle(0);
//    g1->SetFillColor(0);
    g1->SetTitle("Outer triplet ~ 100cm");


    TTree *t2 = new TTree ("t2", "t2");
    t2->ReadFile(txt_file2,"run_Num:pt:rms:err");
    t2->Draw("pt:rms:err","","goff");
//    TGraphErrors *g2 = new TGraphErrors(24,t2->GetV1(),t2->GetV2(),0,t2->GetV3());

    TGraphErrors *g2 = new TGraphErrors(15,t2->GetV1(),t2->GetV2(),0,t2->GetV3());
    g2->SetMarkerColor(kRed);
    g2->SetLineColor(kRed);
    g2->SetLineWidth(2);
    g2->SetMarkerStyle(3);
    g2->SetFillStyle(0);
    g2->SetTitle("Middle Triplet ~ 53cm");


        TTree *t3 = new TTree ("t3", "t3");
        t3->ReadFile(txt_file3,"run_Num:pt:rms:err");
        t3->Draw("pt:rms:err","","goff");
    //    TGraphErrors *g3 = new TGraphErrors(24,t3->GetV1(),t3->GetV2(),0,t3->GetV3());

        TGraphErrors *g3 = new TGraphErrors(15,t3->GetV1(),t3->GetV2(),0,t3->GetV3());
        g3->SetMarkerColor(kGreen);
        g3->SetLineColor(kGreen);
        g3->SetLineWidth(2);
        g3->SetMarkerStyle(3);
        g3->SetFillStyle(0);
        g3->SetTitle("Inner Triplet ~ 7cm");

Double_t x1= 0.6,y1= 0.7, x2 = 0.88, y2 = 0.88;
    TMultiGraph *g = new TMultiGraph();
    g->Add(g1);
    g->Add(g2);
    g->Add(g3);
    g->Draw("ALP");
    g->SetTitle(plot_title);
    g->GetXaxis()->SetTitle("Momentum p [GeV/c]");
    g->GetXaxis()->SetRangeUser(0,100);
    g->GetYaxis()->SetTitleOffset(1.5);
    g->GetYaxis()->SetTitle("#sigma (1/pt_{rec} - 1/p_{gen}) GeV ^{-1}");
    g->GetYaxis()->SetRangeUser(0,0.04);
    c1->BuildLegend(x1,y1,x2,y2,"Triplet Trigger Position");
    c1->Update();
    SaveCanvas(c1,"Track trigger at different radii for 40 #mum X 40 #mum pixels");

}
void drawSummary_plot(const char *pixel_dimenssions, const char* trig_pos)
{
    c1->Clear();
    const char* txt_path = "/home/tamasi/repo_tamasi/mu3e/run/my_macros";
    char txt_file[1023];
    char plot_title[1023];
    sprintf(txt_file,"%s/summary_layerON_%s_%s.txt",txt_path,pixel_dimenssions,trig_pos);
    sprintf(plot_title,"Inverse Momentum Resolution as a fuction of p for %s  #mum x %s #mum",pixel_dimenssions,pixel_dimenssions);

    TTree *t = new TTree ("t", "t");
    t->ReadFile(txt_file,"run_Num:pt:rms:err");
    t->Draw("pt:rms:err","","goff");
    TGraphErrors *g = new TGraphErrors(24,t->GetV1(),t->GetV2(),0,t->GetV3());
    g->SetMarkerColor(kBlue);
    g->SetTitle(plot_title);
    g->GetXaxis()->SetTitle("Momentum p [GeV/c]");
    g->GetXaxis()->SetRangeUser(0,100);
    g->GetYaxis()->SetTitleOffset(1.3);
    g->GetYaxis()->SetTitle("#sigma (1/pt_{rec} - 1/p_{gen}) GeV ^{-1}");
    g->GetYaxis()->SetRangeUser(0,0.04);
    g->Draw("alp");
    c1->Update();

    SaveCanvas(c1,pixel_dimenssions);
}
