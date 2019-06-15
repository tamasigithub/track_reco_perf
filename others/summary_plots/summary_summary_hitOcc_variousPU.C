void summary_summary_hitOcc_variousPU()
{
//=========Macro generated from canvas: c1/c1
//=========  (Sat Jun 15 02:42:28 2019) by ROOT version 6.12/06
   TCanvas *c1 = new TCanvas("c1", "c1",67,57,700,500);
   c1->Range(-13.6625,-3.92603,104.8625,2.32397);
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
   8.81287,
   5.57563,
   4.00876,
   2.94079,
   1.29244,
   0.815011,
   0.551599,
   0.261728,
   0.217324,
   0.200313,
   0.179064};
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
   gre->SetTitle("<#mu> = 960");
   gre->SetFillStyle(0);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph1001 = new TH1F("Graph_Graph1001","<#mu> = 960",100,0,97.32);
   Graph_Graph1001->SetMinimum(0.0005);
   Graph_Graph1001->SetMaximum(50);
   Graph_Graph1001->SetDirectory(0);
   Graph_Graph1001->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph1001->SetLineColor(ci);
   Graph_Graph1001->GetXaxis()->SetTitle("Layer Radius [cm]");
   Graph_Graph1001->GetXaxis()->SetRange(1,101);
   Graph_Graph1001->GetXaxis()->SetLabelFont(42);
   Graph_Graph1001->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1001->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1001->GetXaxis()->SetTitleFont(42);
   Graph_Graph1001->GetYaxis()->SetTitle("hit occupancy [/event/cm^{2}]");
   Graph_Graph1001->GetYaxis()->SetLabelFont(42);
   Graph_Graph1001->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1001->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1001->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph1001->GetYaxis()->SetTitleFont(42);
   Graph_Graph1001->GetZaxis()->SetLabelFont(42);
   Graph_Graph1001->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1001->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1001);
   
   multigraph->Add(gre,"");
   
   Double_t Graph_fx1002[11] = {
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
   Double_t Graph_fy1002[11] = {
   7.82156,
   3.48745,
   2.13285,
   1.37376,
   0.487132,
   0.268062,
   0.164356,
   0.0712588,
   0.0546446,
   0.0526688,
   0.0471218};
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
   0};
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
   gre->SetTitle("<#mu> = 160");
   gre->SetFillStyle(0);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(1.9);
   
   TH1F *Graph_Graph1002 = new TH1F("Graph_Graph1002","<#mu> = 160",100,0,97.32);
   Graph_Graph1002->SetMinimum(0.0005);
   Graph_Graph1002->SetMaximum(50);
   Graph_Graph1002->SetDirectory(0);
   Graph_Graph1002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1002->SetLineColor(ci);
   Graph_Graph1002->GetXaxis()->SetTitle("Layer Radius [cm]");
   Graph_Graph1002->GetXaxis()->SetRange(1,101);
   Graph_Graph1002->GetXaxis()->SetLabelFont(42);
   Graph_Graph1002->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1002->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1002->GetXaxis()->SetTitleFont(42);
   Graph_Graph1002->GetYaxis()->SetTitle("hit occupancy [/event/cm^{2}]");
   Graph_Graph1002->GetYaxis()->SetLabelFont(42);
   Graph_Graph1002->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1002->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1002->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph1002->GetYaxis()->SetTitleFont(42);
   Graph_Graph1002->GetZaxis()->SetLabelFont(42);
   Graph_Graph1002->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1002->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1002);
   
   multigraph->Add(gre,"");
   
   Double_t Graph_fx1003[11] = {
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
   Double_t Graph_fy1003[11] = {
   0.0316451,
   0.0186628,
   0.0131075,
   0.00942186,
   0.00407749,
   0.00273405,
   0.00198344,
   0.00110194,
   0.00096586,
   0.000913367,
   0.000830853};
   Double_t Graph_fex1003[11] = {
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
   Double_t Graph_fey1003[11] = {
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
   gre = new TGraphErrors(11,Graph_fx1003,Graph_fy1003,Graph_fex1003,Graph_fey1003);
   gre->SetName("Graph");
   gre->SetTitle("<#mu> = 0");
   gre->SetFillStyle(0);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(2.5);
   
   TH1F *Graph_Graph1003 = new TH1F("Graph_Graph1003","<#mu> = 0",100,0,97.32);
   Graph_Graph1003->SetMinimum(0.0005);
   Graph_Graph1003->SetMaximum(50);
   Graph_Graph1003->SetDirectory(0);
   Graph_Graph1003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1003->SetLineColor(ci);
   Graph_Graph1003->GetXaxis()->SetTitle("Layer Radius [cm]");
   Graph_Graph1003->GetXaxis()->SetRange(1,101);
   Graph_Graph1003->GetXaxis()->SetLabelFont(42);
   Graph_Graph1003->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1003->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1003->GetXaxis()->SetTitleFont(42);
   Graph_Graph1003->GetYaxis()->SetTitle("hit occupancy [/event/cm^{2}]");
   Graph_Graph1003->GetYaxis()->SetLabelFont(42);
   Graph_Graph1003->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1003->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1003->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph1003->GetYaxis()->SetTitleFont(42);
   Graph_Graph1003->GetZaxis()->SetLabelFont(42);
   Graph_Graph1003->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1003->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1003);
   
   multigraph->Add(gre,"");
   multigraph->Draw("AP");
   multigraph->GetXaxis()->SetTitle("Layer Radius [cm]");
   multigraph->GetXaxis()->SetLabelFont(42);
   multigraph->GetXaxis()->SetLabelSize(0.035);
   multigraph->GetXaxis()->SetTitleFont(42);
   multigraph->GetYaxis()->SetTitle("hit occupancy [/event/cm^{2}]");
   multigraph->GetYaxis()->SetLabelFont(42);
   multigraph->GetYaxis()->SetLabelSize(0.035);
   multigraph->GetYaxis()->SetTitleOffset(0);
   multigraph->GetYaxis()->SetTitleFont(42);
   
   TPaveText *pt = new TPaveText(0.15,0.9344958,0.85,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("Hit Occupancy as a function of layer radius");
   pt->Draw();
   
   TLegend *leg = new TLegend(0.7,0.7,0.89,0.89,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","pileup","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph","<#mu> = 960","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1.9);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph","<#mu> = 160","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1.9);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph","<#mu> = 0","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(2.5);
   entry->SetTextFont(42);
   leg->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
