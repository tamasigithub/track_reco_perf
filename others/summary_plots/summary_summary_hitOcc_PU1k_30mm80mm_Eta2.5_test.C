void summary_summary_hitOcc_variousPU_30mm80mm_Eta2.5_test()
{
//=========Macro generated from canvas: c1/c1
//=========  (Fri Jan  6 19:55:00 2023) by ROOT version 6.22/06
   TCanvas *c1 = new TCanvas("c1", "c1",97,1194,800,800);
   gStyle->SetOptTitle(0);
   c1->Range(-16.63125,-1.694296,105.3312,2.238364);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetLogy();
   c1->SetGridx();
   c1->SetGridy();
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("Hit Occupancy as a function of layer radius");
   
   Double_t Graph_fx1001[11] = {
   2.5,
   6,
   10,
   15,
   27,
   40,
   52,
   75,
   82.7,
   85.7,
   88.7};
   Double_t Graph_fy1001[11] = {
   24.0801,
   14.5181,
   10.2012,
   6.97507,
   2.24695,
   1.28815,
   0.822437,
   0,
   0.311157,
   0.305194,
   0.262813};
   Double_t Graph_fex1001[11] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph_fey1001[11] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   TGraphErrors *gre = new TGraphErrors(11,Graph_fx1001,Graph_fy1001,Graph_fex1001,Graph_fey1001);
   gre->SetName("Graph");
   gre->SetTitle("<#mu> = 1000");
   gre->SetFillStyle(0);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph1001 = new TH1F("Graph_Graph1001","<#mu> = 1000",100,0,97.32);
   Graph_Graph1001->SetMinimum(0.05);
   Graph_Graph1001->SetMaximum(70);
   Graph_Graph1001->SetDirectory(0);
   Graph_Graph1001->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph1001->SetLineColor(ci);
   Graph_Graph1001->GetXaxis()->SetTitle("Layer Radius [cm]");
   Graph_Graph1001->GetXaxis()->SetRange(1,101);
   Graph_Graph1001->GetXaxis()->SetLabelFont(42);
   Graph_Graph1001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph1001->GetXaxis()->SetTitleFont(42);
   Graph_Graph1001->GetYaxis()->SetTitle("Hit occupancy [/event/cm^{2}]");
   Graph_Graph1001->GetYaxis()->SetLabelFont(42);
   Graph_Graph1001->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph1001->GetYaxis()->SetTitleFont(42);
   Graph_Graph1001->GetZaxis()->SetLabelFont(42);
   Graph_Graph1001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph1001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1001);
   
   multigraph->Add(gre,"");
   
   Double_t Graph_fx1002[11] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   53.05};
   Double_t Graph_fy1002[11] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   1.14719};
   Double_t Graph_fex1002[11] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   22.75};
   Double_t Graph_fey1002[11] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(11,Graph_fx1002,Graph_fy1002,Graph_fex1002,Graph_fey1002);
   gre->SetName("Graph");
   gre->SetTitle("");
   gre->SetFillStyle(0);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(2);
   
   TH1F *Graph_Graph1002 = new TH1F("Graph_Graph1002","",100,0,83.38);
   Graph_Graph1002->SetMinimum(0.05);
   Graph_Graph1002->SetMaximum(70);
   Graph_Graph1002->SetDirectory(0);
   Graph_Graph1002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1002->SetLineColor(ci);
   Graph_Graph1002->GetXaxis()->SetTitle("Layer Radius [cm]");
   Graph_Graph1002->GetXaxis()->SetRange(1,101);
   Graph_Graph1002->GetXaxis()->SetLabelFont(42);
   Graph_Graph1002->GetXaxis()->SetTitleOffset(1);
   Graph_Graph1002->GetXaxis()->SetTitleFont(42);
   Graph_Graph1002->GetYaxis()->SetTitle("Hit occupancy [/event/cm^{2}]");
   Graph_Graph1002->GetYaxis()->SetLabelFont(42);
   Graph_Graph1002->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph1002->GetYaxis()->SetTitleFont(42);
   Graph_Graph1002->GetZaxis()->SetLabelFont(42);
   Graph_Graph1002->GetZaxis()->SetTitleOffset(1);
   Graph_Graph1002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1002);
   
   multigraph->Add(gre,"");
   multigraph->Draw("APe1");
   multigraph->GetXaxis()->SetLimits(-4.435, 93.135);
   multigraph->GetXaxis()->SetTitle("Layer Radius [cm]");
   multigraph->GetXaxis()->CenterTitle(true);
   multigraph->GetXaxis()->SetLabelFont(42);
   multigraph->GetXaxis()->SetTitleSize(0.04);
   multigraph->GetXaxis()->SetTitleOffset(1);
   multigraph->GetXaxis()->SetTitleFont(42);
   multigraph->GetYaxis()->SetTitle("Cluster occupancy [/event/cm^{2}]");
   multigraph->GetYaxis()->CenterTitle(true);
   multigraph->GetYaxis()->SetLabelFont(42);
   multigraph->GetYaxis()->SetTitleSize(0.04);
   multigraph->GetYaxis()->SetTitleOffset(1.4);
   multigraph->GetYaxis()->SetTitleFont(42);
   
   TLegend *leg = new TLegend(0.2,0.89,0.89,0.97,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("NULL","#sqrt{s} = 100 TeV, HH #rightarrow b#bar{b}b#bar{b}(SM), B=4T","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.53,0.75,0.87,0.89,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("NULL","barrel  endcap   pileup","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry->SetTextSize(0.04);
   entry=leg->AddEntry("Graph","        ","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1.9);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph","    <#mu> = 1000","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(2);
   entry->SetTextFont(42);
   leg->Draw();
   TGaxis *gaxis = new TGaxis(93.135,0,93.135,70,2,2800,510,"+G");
   gaxis->SetLabelOffset(0.05);
   gaxis->SetLabelSize(0.04);
   gaxis->SetTickSize(0.03);
   gaxis->SetGridLength(0);
   gaxis->SetTitleOffset(1.08);
   gaxis->SetTitleSize(0.05);
   gaxis->SetTitleColor(1);
   gaxis->SetTitleFont(62);
   gaxis->SetTitle("rate [MHz/cm^{2}]");
   gaxis->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
