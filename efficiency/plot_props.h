Float_t LINE_WIDTH = 2.5;
Float_t TITLE_SIZE = 0.04;
Float_t MARKER_SIZE = 1.2;
Float_t AXISTITLE_OFFSET = 0.8;
Float_t YAXISTITLE_OFFSET = 1.2;
Float_t max_range;
Float_t min_range;
Float_t ENTRY_SEP = 0.05;
Float_t FILL_STYLE = 0;
Float_t BORDER_SIZE = 0;
Float_t TEXT_ALIGN = 32;
Float_t TEXT_ALIGN_1 = 12;
Float_t TEXT_FONT = 62;
Float_t TEXT_SIZE = 0.04;
Float_t Xl1 = 0.16, Yu1 = 0.9, Xl2 = 0.36, Yu2 = 0.95;
Float_t Xr1 = 0.45, Ym1 = 0.5, Xr2 = 0.899, Ym2 = 0.76;
Float_t LEFT_MARGIN = 0.15;
Float_t MARKER_STYLE = 6;

TLegend *leg1 = nullptr;
TLegend *leg2 = nullptr;
TLegend *leg3 = nullptr;
TLegend *leg4 = nullptr;
TLegend *leg5 = nullptr;

void Legends()
{
	leg1 = new TLegend(Xr1, Yu1, Xr2, Yu2);
	//leg1->AddEntry((TObject*)0, "#sqrt{s} = 100 TeV, B = 4T", "");
	//leg1->AddEntry((TObject*)0, "HH #rightarrow b#bar{b}b#bar{b}, <#mu> = 0", "");
	leg1->AddEntry((TObject*)0, "HH #rightarrow b#bar{b}b#bar{b}, #langle #mu #rangle = 1k", "");
	leg1->SetFillStyle(FILL_STYLE);
	leg1->SetBorderSize(BORDER_SIZE);
	leg1->SetTextSize(TEXT_SIZE);
	leg1->SetTextAlign(kHAlignRight+kVAlignCenter);

	leg2 = new TLegend(Xl2, Yu1-0.05, Xr2, Yu1-0.001);
	//leg2->AddEntry((TObject*)0, "final selection cuts", "");
	leg2->AddEntry((TObject*)0, "p_{T} > 2 GeV/c, |#eta| < 2.5, |z_{vtx}| < 10 cm", "");
	//leg2->AddEntry((TObject*)0, "p_{T} > 2 GeV/c, |#eta| < 1.7, |z_{vtx}| < 10 cm", "");
	leg2->SetFillStyle(FILL_STYLE);
	leg2->SetBorderSize(BORDER_SIZE);
	leg2->SetTextSize(TEXT_SIZE);
	leg2->SetTextAlign(kHAlignRight+kVAlignCenter);
	
	leg3 = new TLegend(Xr1+0.22, Yu1-0.11, Xr2,Yu1-0.05);
	//leg3->AddEntry((TObject*)0, "final selection cuts", "");
	leg3->AddEntry((TObject*)0,  "#phi_{13, cut}, z_{13, cut}","");
	//leg3->SetFillStyle(FILL_STYLE);
	leg3->SetBorderSize(BORDER_SIZE);
	leg3->SetTextSize(TEXT_SIZE);
	leg3->SetTextAlign(kHAlignRight+kVAlignCenter);
	
	leg4 = new TLegend(Xr1+0.22, Yu1-0.16, Xr2,Yu1-0.1);
	//leg4->AddEntry((TObject*)0, "final selection cuts", "");
	leg4->AddEntry((TObject*)0,  "d#phi_{2, cut}, dz_{2, cut}","");
	//leg4->SetFillStyle(FILL_STYLE);
	leg4->SetBorderSize(BORDER_SIZE);
	leg4->SetTextSize(TEXT_SIZE);
	leg4->SetTextAlign(kHAlignRight+kVAlignCenter);

	leg5 = new TLegend(0.1, Yu1, Xl1, Yu2);
	//leg5->AddEntry((TObject*)0, "gap-size = 30 mm", "");
	leg5->AddEntry((TObject*)0, "#sqrt{s} = 100 TeV, B = 4T", "");
	//leg5->AddEntry((TObject*)0, " ", "");
	leg5->SetFillStyle(FILL_STYLE);
	leg5->SetBorderSize(BORDER_SIZE);
	leg5->SetTextSize(TEXT_SIZE);
	leg5->SetTextAlign(kHAlignLeft+kVAlignCenter);
	//leg5->SetTextAlign(kHAlignLeft+kVAlignBottom);
	return;
}
