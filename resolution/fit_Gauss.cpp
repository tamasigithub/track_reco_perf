char buf[4096];
int n_repeat = 3;
float fit_sigma = 2.1;//
//! User defined Gauss fit function to optimise the fit 
void fit_Gauss(TH1F* h)
{
	h->SetLineWidth(2);
	float xmin = h->GetXaxis()->GetXmin(), xmin_ = xmin;
	float xmax = h->GetXaxis()->GetXmax(), xmax_ = xmax;
	//! repeat the fit thrice 
	for(int i = 0; i < n_repeat; i++) 
	{
		h->Fit("gaus", "QLL", "", xmin_, xmax_);
		xmin_ = h->GetFunction("gaus")->GetParameter(1) - fit_sigma * h->GetFunction("gaus")->GetParameter(2);
		xmax_ = h->GetFunction("gaus")->GetParameter(1) + fit_sigma * h->GetFunction("gaus")->GetParameter(2);
  	}

	h->GetFunction("gaus")->SetLineColor(2);
  	h->GetFunction("gaus")->SetLineWidth(2);

	h->GetYaxis()->SetRangeUser(0, 1.1 * h->GetMaximum());
	float ymin = 0;
	float ymax = 1.1 * h->GetMaximum();

	TLatex lat;
	sprintf(buf, "#mu = %.2f", h->GetFunction("gaus")->GetParameter(1));
	lat.DrawLatex(xmin + 0.6 * (xmax - xmin), 0.80 * ymax, buf);
	sprintf(buf, "#sigma = %.2f", h->GetFunction("gaus")->GetParameter(2));
	lat.DrawLatex(xmin + 0.6 * (xmax - xmin), 0.75 * ymax, buf);
}
