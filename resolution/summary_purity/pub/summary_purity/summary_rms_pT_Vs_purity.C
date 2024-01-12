void summary_rms_pT_Vs_purity()
{
//=========Macro generated from canvas: c1/c1
//=========  (Sun Feb 19 17:42:27 2023) by ROOT version 6.22/06
   TCanvas *c1 = new TCanvas("c1", "c1",49,90,800,800);
   c1->Range(0.8012987,1.2625,1.022078,2.6375);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetLeftMargin(0.13);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1002[5] = {
   0.951371,
   0.926636,
   0.899495,
   0.870479,
   0.836101};
   Double_t Graph0_fy1002[5] = {
   2.12445,
   1.83345,
   1.65654,
   1.53964,
   1.46911};
   Double_t Graph0_fex1002[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1002[5] = {
   0.000122649,
   0.000121606,
   9.64337e-05,
   8.83907e-05,
   8.59685e-05};
   TGraphErrors *gre = new TGraphErrors(5,Graph0_fx1002,Graph0_fy1002,Graph0_fex1002,Graph0_fey1002);
   gre->SetName("Graph0");
   gre->SetTitle("Relative p_{T} resolution Vs track purity for various gap sizes of the TTT");
   gre->SetFillStyle(0);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph01002 = new TH1F("Graph_Graph01002","Relative p_{T} resolution Vs track purity for various gap sizes of the TTT",100,0.83,1);
   Graph_Graph01002->SetMinimum(1.4);
   Graph_Graph01002->SetMaximum(2.5);
   Graph_Graph01002->SetDirectory(0);
   Graph_Graph01002->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph01002->SetLineColor(ci);
   Graph_Graph01002->GetXaxis()->SetTitle("purity, p_{T} #in (10, 100) GeV/c");
   Graph_Graph01002->GetXaxis()->CenterTitle(true);
   Graph_Graph01002->GetXaxis()->SetLabelFont(42);
   Graph_Graph01002->GetXaxis()->SetTitleSize(0.04);
   Graph_Graph01002->GetXaxis()->SetTitleOffset(1.2);
   Graph_Graph01002->GetXaxis()->SetTitleFont(42);
   Graph_Graph01002->GetYaxis()->SetTitle("#sigma_{#delta p_{T}/p_{T, gen}} [%], at p_{T} #sim 10 GeV/c");
   Graph_Graph01002->GetYaxis()->CenterTitle(true);
   Graph_Graph01002->GetYaxis()->SetLabelFont(42);
   Graph_Graph01002->GetYaxis()->SetTitleSize(0.04);
   Graph_Graph01002->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph01002->GetYaxis()->SetTitleFont(42);
   Graph_Graph01002->GetZaxis()->SetLabelFont(42);
   Graph_Graph01002->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01002);
   
   gre->Draw("alpe1");
   TMarker *marker = new TMarker(0.951371,2.12445,20);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.926636,1.83345,20);
   marker->SetMarkerColor(2);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.899495,1.65654,20);
   marker->SetMarkerColor(3);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.870479,1.53964,20);
   marker->SetMarkerColor(4);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.836101,1.46911,20);
   marker->SetMarkerColor(5);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   
   TLegend *leg = new TLegend(0.71,0.6,0.89,0.79,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("NULL","~~ gap size","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry->SetTextSize(0.04);
   entry=leg->AddEntry("TMarker","   53mm","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   67mm","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   80mm","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(3);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   93mm","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","  106mm","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(5);
   entry->SetMarkerStyle(20);
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
   
   leg = new TLegend(0.55,0.85,0.9,0.9,NULL,"brNDC");
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
   
   leg = new TLegend(0.5,0.75,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("NULL","HH #rightarrow b#bar{b}b#bar{b} <#mu> = 1k","");
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
