void summary_rms_pT_Vs_purity()
{
//=========Macro generated from canvas: c1/c1
//=========  (Fri Feb 17 18:00:23 2023) by ROOT version 6.22/06
   TCanvas *c1 = new TCanvas("c1", "c1",129,165,800,800);
   c1->Range(0.812987,-0.1625,1.020779,1.4625);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetLeftMargin(0.13);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1001[5] = {
   0.932076,
   0.927725,
   0.915471,
   0.88269,
   0.848006};
   Double_t Graph0_fy1001[5] = {
   0.952045,
   0.783257,
   0.708941,
   0.653471,
   0.620935};
   Double_t Graph0_fex1001[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1001[5] = {
   0.000142589,
   0.000105025,
   9.75091e-05,
   9.82524e-05,
   8.67109e-05};
   TGraphErrors *gre = new TGraphErrors(5,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
   gre->SetName("Graph0");
   gre->SetTitle("Relative p_{T} resolution Vs track purity for various gap sizes of the TTT");
   gre->SetFillStyle(0);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","Relative p_{T} resolution Vs track purity for various gap sizes of the TTT",100,0.84,1);
   Graph_Graph01001->SetMinimum(0);
   Graph_Graph01001->SetMaximum(1.3);
   Graph_Graph01001->SetDirectory(0);
   Graph_Graph01001->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph01001->SetLineColor(ci);
   Graph_Graph01001->GetXaxis()->SetTitle("Average track purity, p_{T} #in (10, 100) GeV/c");
   Graph_Graph01001->GetXaxis()->CenterTitle(true);
   Graph_Graph01001->GetXaxis()->SetLabelFont(42);
   Graph_Graph01001->GetXaxis()->SetTitleSize(0.04);
   Graph_Graph01001->GetXaxis()->SetTitleOffset(1.2);
   Graph_Graph01001->GetXaxis()->SetTitleFont(42);
   Graph_Graph01001->GetYaxis()->SetTitle("#sigma_{#delta p_{T}/p_{T, gen}} [%], at p_{T} = 10 GeV/c");
   Graph_Graph01001->GetYaxis()->CenterTitle(true);
   Graph_Graph01001->GetYaxis()->SetLabelFont(42);
   Graph_Graph01001->GetYaxis()->SetTitleSize(0.04);
   Graph_Graph01001->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph01001->GetYaxis()->SetTitleFont(42);
   Graph_Graph01001->GetZaxis()->SetLabelFont(42);
   Graph_Graph01001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01001);
   
   gre->Draw("alpe1");
   
   //Double_t Graph1_fx1002[5] = {
   //0.958705,
   //0.965413,
   //0.96878,
   //0.969307,
   //0.965768};
   //Double_t Graph1_fy1002[5] = {
   //0.952045,
   //0.783257,
   //0.708941,
   //0.653471,
   //0.620935};
   //Double_t Graph1_fex1002[5] = {
   //0,
   //0,
   //0,
   //0,
   //0};
   //Double_t Graph1_fey1002[5] = {
   //0.000142589,
   //0.000105025,
   //9.75091e-05,
   //9.82524e-05,
   //8.67109e-05};
   //gre = new TGraphErrors(5,Graph1_fx1002,Graph1_fy1002,Graph1_fex1002,Graph1_fey1002);
   //gre->SetName("Graph1");
   //gre->SetTitle("Relative p_{T} resolution Vs track purity for various gap sizes of the TTT");
   //gre->SetFillStyle(0);
   //gre->SetMarkerStyle(22);
   //
   //TH1F *Graph_Graph11002 = new TH1F("Graph_Graph11002","Relative p_{T} resolution Vs track purity for various gap sizes of the TTT",100,0.84,1);
   //Graph_Graph11002->SetMinimum(0);
   //Graph_Graph11002->SetMaximum(1.3);
   //Graph_Graph11002->SetDirectory(0);
   //Graph_Graph11002->SetStats(0);

   //ci = TColor::GetColor("#000099");
   //Graph_Graph11002->SetLineColor(ci);
   //Graph_Graph11002->GetXaxis()->SetTitle("Average track purity, p_{T} #in (10, 100) GeV/c");
   //Graph_Graph11002->GetXaxis()->CenterTitle(true);
   //Graph_Graph11002->GetXaxis()->SetLabelFont(42);
   //Graph_Graph11002->GetXaxis()->SetTitleSize(0.04);
   //Graph_Graph11002->GetXaxis()->SetTitleOffset(1.2);
   //Graph_Graph11002->GetXaxis()->SetTitleFont(42);
   //Graph_Graph11002->GetYaxis()->SetTitle("#sigma_{#delta p_{T}/p_{T, gen}} [%], at p_{T} = 10 GeV/c");
   //Graph_Graph11002->GetYaxis()->CenterTitle(true);
   //Graph_Graph11002->GetYaxis()->SetLabelFont(42);
   //Graph_Graph11002->GetYaxis()->SetTitleSize(0.04);
   //Graph_Graph11002->GetYaxis()->SetTitleOffset(1.2);
   //Graph_Graph11002->GetYaxis()->SetTitleFont(42);
   //Graph_Graph11002->GetZaxis()->SetLabelFont(42);
   //Graph_Graph11002->GetZaxis()->SetTitleOffset(1);
   //Graph_Graph11002->GetZaxis()->SetTitleFont(42);
   //gre->SetHistogram(Graph_Graph11002);
   //
   //gre->Draw("lpe1");
   //
   //Double_t Graph2_fx1003[5] = {
   //0.971871,
   //0.9704,
   //0.974285,
   //0.976774,
   //0.970408};
   //Double_t Graph2_fy1003[5] = {
   //0.952045,
   //0.783257,
   //0.708941,
   //0.653471,
   //0.620935};
   //Double_t Graph2_fex1003[5] = {
   //0,
   //0,
   //0,
   //0,
   //0};
   //Double_t Graph2_fey1003[5] = {
   //0.000142589,
   //0.000105025,
   //9.75091e-05,
   //9.82524e-05,
   //8.67109e-05};
   //gre = new TGraphErrors(5,Graph2_fx1003,Graph2_fy1003,Graph2_fex1003,Graph2_fey1003);
   //gre->SetName("Graph2");
   //gre->SetTitle("Relative p_{T} resolution Vs track purity for various gap sizes of the TTT");
   //gre->SetFillStyle(0);
   //gre->SetMarkerStyle(21);
   //
   //TH1F *Graph_Graph21003 = new TH1F("Graph_Graph21003","Relative p_{T} resolution Vs track purity for various gap sizes of the TTT",100,0.84,1);
   //Graph_Graph21003->SetMinimum(0);
   //Graph_Graph21003->SetMaximum(1.3);
   //Graph_Graph21003->SetDirectory(0);
   //Graph_Graph21003->SetStats(0);

   //ci = TColor::GetColor("#000099");
   //Graph_Graph21003->SetLineColor(ci);
   //Graph_Graph21003->GetXaxis()->SetTitle("Average track purity, p_{T} #in (10, 100) GeV/c");
   //Graph_Graph21003->GetXaxis()->CenterTitle(true);
   //Graph_Graph21003->GetXaxis()->SetLabelFont(42);
   //Graph_Graph21003->GetXaxis()->SetTitleSize(0.04);
   //Graph_Graph21003->GetXaxis()->SetTitleOffset(1.2);
   //Graph_Graph21003->GetXaxis()->SetTitleFont(42);
   //Graph_Graph21003->GetYaxis()->SetTitle("#sigma_{#delta p_{T}/p_{T, gen}} [%], at p_{T} = 10 GeV/c");
   //Graph_Graph21003->GetYaxis()->CenterTitle(true);
   //Graph_Graph21003->GetYaxis()->SetLabelFont(42);
   //Graph_Graph21003->GetYaxis()->SetTitleSize(0.04);
   //Graph_Graph21003->GetYaxis()->SetTitleOffset(1.2);
   //Graph_Graph21003->GetYaxis()->SetTitleFont(42);
   //Graph_Graph21003->GetZaxis()->SetLabelFont(42);
   //Graph_Graph21003->GetZaxis()->SetTitleOffset(1);
   //Graph_Graph21003->GetZaxis()->SetTitleFont(42);
   //gre->SetHistogram(Graph_Graph21003);
   
   gre->Draw("lpe1");
   TMarker *marker = new TMarker(0.932076,0.952045,20);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   //marker = new TMarker(0.958705,0.952045,22);
   //marker->SetMarkerStyle(22);
   //marker->SetMarkerSize(2);
   //marker->Draw();
   //marker = new TMarker(0.971871,0.952045,21);
   //marker->SetMarkerStyle(21);
   //marker->SetMarkerSize(2);
   //marker->Draw();
   marker = new TMarker(0.927725,0.783257,20);
   marker->SetMarkerColor(2);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   //marker = new TMarker(0.965413,0.783257,22);
   //marker->SetMarkerColor(2);
   //marker->SetMarkerStyle(22);
   //marker->SetMarkerSize(2);
   //marker->Draw();
   //marker = new TMarker(0.9704,0.783257,21);
   //marker->SetMarkerColor(2);
   //marker->SetMarkerStyle(21);
   //marker->SetMarkerSize(2);
   //marker->Draw();
   marker = new TMarker(0.915471,0.708941,20);
   marker->SetMarkerColor(3);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   //marker = new TMarker(0.96878,0.708941,22);
   //marker->SetMarkerColor(3);
   //marker->SetMarkerStyle(22);
   //marker->SetMarkerSize(2);
   //marker->Draw();
   //marker = new TMarker(0.974285,0.708941,21);
   //marker->SetMarkerColor(3);
   //marker->SetMarkerStyle(21);
   //marker->SetMarkerSize(2);
   //marker->Draw();
   marker = new TMarker(0.88269,0.653471,20);
   marker->SetMarkerColor(4);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   //marker = new TMarker(0.969307,0.653471,22);
   //marker->SetMarkerColor(4);
   //marker->SetMarkerStyle(22);
   //marker->SetMarkerSize(2);
   //marker->Draw();
   //marker = new TMarker(0.976774,0.653471,21);
   //marker->SetMarkerColor(4);
   //marker->SetMarkerStyle(21);
   //marker->SetMarkerSize(2);
   //marker->Draw();
   marker = new TMarker(0.848006,0.620935,20);
   marker->SetMarkerColor(5);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   //marker = new TMarker(0.965768,0.620935,22);
   //marker->SetMarkerColor(5);
   //marker->SetMarkerStyle(22);
   //marker->SetMarkerSize(2);
   //marker->Draw();
   //marker = new TMarker(0.970408,0.620935,21);
   //marker->SetMarkerColor(5);
   //marker->SetMarkerStyle(21);
   //marker->SetMarkerSize(2);
   //marker->Draw();
   
   TLegend *leg = new TLegend(0.14,0.31,0.44,0.38,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("NULL","      <#mu>         gap size","h");
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
   entry=leg->AddEntry("TMarker","   20mm","lpf");
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
   entry=leg->AddEntry("TMarker","   25mm","lpf");
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
   entry=leg->AddEntry("TMarker","   30mm","lpf");
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
   entry=leg->AddEntry("TMarker","   35mm","lpf");
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
   entry=leg->AddEntry("TMarker","   40mm","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(5);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.15,0.916134,0.85,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("Relative p_{T} resolution Vs track purity for various gap sizes of the TTT");
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
