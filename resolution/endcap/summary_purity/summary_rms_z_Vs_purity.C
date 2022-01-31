void summary_rms_z_Vs_purity()
{
//=========Macro generated from canvas: c1/c1
//=========  (Mon Jul 19 15:12:04 2021) by ROOT version 6.18/00
   TCanvas *c1 = new TCanvas("c1", "c1",49,65,800,800);
   c1->Range(0.7662338,-0.25,1.025974,2.25);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetLeftMargin(0.13);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1004[5] = {
   0.951371,
   0.926636,
   0.899495,
   0.870479,
   0.836101};
   Double_t Graph0_fy1004[5] = {
   1.46533,
   1.22585,
   1.10176,
   1.00527,
   0.916447};
   Double_t Graph0_fex1004[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1004[5] = {
   0.00856832,
   0.00818306,
   0.00653635,
   0.00568808,
   0.00536193};
   TGraphErrors *gre = new TGraphErrors(5,Graph0_fx1004,Graph0_fy1004,Graph0_fex1004,Graph0_fey1004);
   gre->SetName("Graph0");
   gre->SetTitle("z_{0} resolution Vs track purity for various gap sizes of the TTT");
   gre->SetFillStyle(0);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph01004 = new TH1F("Graph_Graph01004","z_{0} resolution Vs track purity for various gap sizes of the TTT",100,0.8,1);
   Graph_Graph01004->SetMinimum(0);
   Graph_Graph01004->SetMaximum(2);
   Graph_Graph01004->SetDirectory(0);
   Graph_Graph01004->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph01004->SetLineColor(ci);
   Graph_Graph01004->GetXaxis()->SetTitle("Average track purity, p_{T} #in (10, 100) GeV/c");
   Graph_Graph01004->GetXaxis()->CenterTitle(true);
   Graph_Graph01004->GetXaxis()->SetLabelFont(42);
   Graph_Graph01004->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph01004->GetXaxis()->SetTitleOffset(1.2);
   Graph_Graph01004->GetXaxis()->SetTitleFont(42);
   Graph_Graph01004->GetYaxis()->SetTitle("#sigma_{#delta z }[mm], at p_{T} = 10 GeV/c");
   Graph_Graph01004->GetYaxis()->CenterTitle(true);
   Graph_Graph01004->GetYaxis()->SetLabelFont(42);
   Graph_Graph01004->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph01004->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph01004->GetYaxis()->SetTitleFont(42);
   Graph_Graph01004->GetZaxis()->SetLabelFont(42);
   Graph_Graph01004->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01004->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01004->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01004);
   
   gre->Draw("alpe1");
   
   Double_t Graph1_fx1005[5] = {
   0.986945,
   0.979701,
   0.977588,
   0.97742,
   0.96973};
   Double_t Graph1_fy1005[5] = {
   1.46533,
   1.22585,
   1.10176,
   1.00527,
   0.916447};
   Double_t Graph1_fex1005[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1005[5] = {
   0.00856832,
   0.00818306,
   0.00653635,
   0.00568807,
   0.00536193};
   gre = new TGraphErrors(5,Graph1_fx1005,Graph1_fy1005,Graph1_fex1005,Graph1_fey1005);
   gre->SetName("Graph1");
   gre->SetTitle("z_{0} resolution Vs track purity for various gap sizes of the TTT");
   gre->SetFillStyle(0);
   gre->SetMarkerStyle(22);
   
   TH1F *Graph_Graph11005 = new TH1F("Graph_Graph11005","z_{0} resolution Vs track purity for various gap sizes of the TTT",100,0.8,1);
   Graph_Graph11005->SetMinimum(0);
   Graph_Graph11005->SetMaximum(2);
   Graph_Graph11005->SetDirectory(0);
   Graph_Graph11005->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11005->SetLineColor(ci);
   Graph_Graph11005->GetXaxis()->SetTitle("Average track purity, p_{T} #in (10, 100) GeV/c");
   Graph_Graph11005->GetXaxis()->CenterTitle(true);
   Graph_Graph11005->GetXaxis()->SetLabelFont(42);
   Graph_Graph11005->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph11005->GetXaxis()->SetTitleOffset(1.2);
   Graph_Graph11005->GetXaxis()->SetTitleFont(42);
   Graph_Graph11005->GetYaxis()->SetTitle("#sigma_{#delta z}[mm], at p_{T} = 10 GeV/c");
   Graph_Graph11005->GetYaxis()->CenterTitle(true);
   Graph_Graph11005->GetYaxis()->SetLabelFont(42);
   Graph_Graph11005->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph11005->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph11005->GetYaxis()->SetTitleFont(42);
   Graph_Graph11005->GetZaxis()->SetLabelFont(42);
   Graph_Graph11005->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph11005->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph11005->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11005->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11005);
   
   gre->Draw("lpe1");
   
   Double_t Graph2_fx1006[5] = {
   0.991405,
   0.990518,
   0.989731,
   0.990939,
   0.991117};
   Double_t Graph2_fy1006[5] = {
   1.46533,
   1.22585,
   1.10176,
   1.00527,
   0.916447};
   Double_t Graph2_fex1006[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1006[5] = {
   0.00856832,
   0.00818306,
   0.00653635,
   0.00568808,
   0.00536193};
   gre = new TGraphErrors(5,Graph2_fx1006,Graph2_fy1006,Graph2_fex1006,Graph2_fey1006);
   gre->SetName("Graph2");
   gre->SetTitle("z_{0} resolution Vs track purity for various gap sizes of the TTT");
   gre->SetFillStyle(0);
   gre->SetMarkerStyle(22);
   
   TH1F *Graph_Graph21006 = new TH1F("Graph_Graph21006","z_{0} resolution Vs track purity for various gap sizes of the TTT",100,0.8,1);
   Graph_Graph21006->SetMinimum(0);
   Graph_Graph21006->SetMaximum(2);
   Graph_Graph21006->SetDirectory(0);
   Graph_Graph21006->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21006->SetLineColor(ci);
   Graph_Graph21006->GetXaxis()->SetTitle("Average track purity, p_{T} #in (10, 100) GeV/c");
   Graph_Graph21006->GetXaxis()->CenterTitle(true);
   Graph_Graph21006->GetXaxis()->SetLabelFont(42);
   Graph_Graph21006->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph21006->GetXaxis()->SetTitleOffset(1.2);
   Graph_Graph21006->GetXaxis()->SetTitleFont(42);
   Graph_Graph21006->GetYaxis()->SetTitle("#sigma_{#delta z}[mm], at p_{T} = 10 GeV/c");
   Graph_Graph21006->GetYaxis()->CenterTitle(true);
   Graph_Graph21006->GetYaxis()->SetLabelFont(42);
   Graph_Graph21006->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph21006->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph21006->GetYaxis()->SetTitleFont(42);
   Graph_Graph21006->GetZaxis()->SetLabelFont(42);
   Graph_Graph21006->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph21006->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph21006->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21006->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21006);
   
   gre->Draw("lpe1");
   TMarker *marker = new TMarker(0.951371,1.46533,20);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.986945,1.46533,22);
   marker->SetMarkerStyle(22);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.991405,1.46533,21);
   marker->SetMarkerStyle(21);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.926636,1.22585,20);
   marker->SetMarkerColor(2);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.979701,1.22585,22);
   marker->SetMarkerColor(2);
   marker->SetMarkerStyle(22);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.990518,1.22585,21);
   marker->SetMarkerColor(2);
   marker->SetMarkerStyle(21);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.899495,1.10176,20);
   marker->SetMarkerColor(3);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.977588,1.10176,22);
   marker->SetMarkerColor(3);
   marker->SetMarkerStyle(22);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.989731,1.10176,21);
   marker->SetMarkerColor(3);
   marker->SetMarkerStyle(21);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.870479,1.00527,20);
   marker->SetMarkerColor(4);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.97742,1.00527,22);
   marker->SetMarkerColor(4);
   marker->SetMarkerStyle(22);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.990939,1.00527,21);
   marker->SetMarkerColor(4);
   marker->SetMarkerStyle(21);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.836101,0.916447,20);
   marker->SetMarkerColor(5);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.96973,0.916447,22);
   marker->SetMarkerColor(5);
   marker->SetMarkerStyle(22);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.991117,0.916447,21);
   marker->SetMarkerColor(5);
   marker->SetMarkerStyle(21);
   marker->SetMarkerSize(2);
   marker->Draw();
   
   TLegend *leg = new TLegend(0.14,0.31,0.44,0.38,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("NULL","      <#mu>      gap size","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry->SetTextSize(0.04);
   leg->Draw();
   
   leg = new TLegend(0.15,0.11,0.45,0.31,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("NULL","1k 200   0","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry->SetTextSize(0.04);
   entry=leg->AddEntry("TMarker","   ","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   ","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   53mm","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   ","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   ","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   67mm","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   ","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(3);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   ","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(3);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   80mm","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(3);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   ","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   ","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   93mm","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   ","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(5);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   ","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(5);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","  106mm","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(5);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.15,0.9283333,0.85,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("z_{0} resolution Vs track purity for various gap sizes of the TTT");
   pt->Draw();
   
   leg = new TLegend(0.55,0.79,0.9,0.92,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("NULL","#sqrt{s} = 100 TeV","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.58,0.72,0.9,0.92,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("NULL","HH #rightarrow b#bar{b}b#bar{b}","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
