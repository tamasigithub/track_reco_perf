void summary_rms_z_Vs_purity()
{
//=========Macro generated from canvas: c1/c1
//=========  (Sun Feb 19 16:53:00 2023) by ROOT version 6.22/06
   TCanvas *c1 = new TCanvas("c1", "c1",85,1182,800,800);
   c1->Range(0.812987,0.21875,1.020779,0.53125);
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
   0.437574,
   0.370972,
   0.333283,
   0.31114,
   0.288277};
   Double_t Graph0_fex1001[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1001[5] = {
   0.00579646,
   0.00581036,
   0.00446726,
   0.00489669,
   0.0040704};
   TGraphErrors *gre = new TGraphErrors(5,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
   gre->SetName("Graph0");
   gre->SetTitle("z_{0} resolution Vs track purity for various gap sizes of the TTT");
   gre->SetFillStyle(0);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","z_{0} resolution Vs track purity for various gap sizes of the TTT",100,0.84,1);
   Graph_Graph01001->SetMinimum(0.25);
   Graph_Graph01001->SetMaximum(0.5);
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
   Graph_Graph01001->GetYaxis()->SetTitle("#sigma_{#delta z }[mm], at p_{T} = 10 GeV/c");
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
   TMarker *marker = new TMarker(0.932076,0.437574,20);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.927725,0.370972,20);
   marker->SetMarkerColor(2);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.915471,0.333283,20);
   marker->SetMarkerColor(3);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.88269,0.31114,20);
   marker->SetMarkerColor(4);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   marker = new TMarker(0.848006,0.288277,20);
   marker->SetMarkerColor(5);
   marker->SetMarkerStyle(20);
   marker->SetMarkerSize(2);
   marker->Draw();
   
   TLegend *leg = new TLegend(0.69,0.59,0.89,0.79,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("NULL","~~~~ gap size","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry->SetTextSize(0.04);
   entry=leg->AddEntry("TMarker","   20mm","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   25mm","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   30mm","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(3);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   35mm","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("TMarker","   40mm","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(5);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2);
   entry->SetTextFont(62);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.15,0.9285052,0.85,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("z_{0} resolution Vs track purity for various gap sizes of the TTT");
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
   entry=leg->AddEntry("NULL","HH #rightarrow b#bar{b}b#bar{b}, <#mu>=1k","");
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
