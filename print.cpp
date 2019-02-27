
#include<iostream.h>
#include<math.h>
int print()
{
	for (double eta = -3.2; eta < 3.4; eta+=0.4)
	{
		std::cout<<"eta  = " << eta <<std::endl;
	}
	
	double bincenter[] = {2000, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
	double binlow[] = {0, 2000, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
	double binhigh[] = {0, 2000, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
	std::cout<<"size :" << sizeof(bincenter)/sizeof(double) <<std::endl;
	for (unsigned ik = 0; ik < sizeof(bincenter)/sizeof(double); ++ik)
	{
		float binwidth_low = 0;
		float binwidth_high = 0;
		if(ik == 0) 
		{	
			binwidth_low = 0.5*bincenter[ik];
			binhigh[ik] = binlow[ik] + binwidth_low;
		}
		else 
		{
			binwidth_low = 0.5*(bincenter[ik] - bincenter[ik-1]);
		}
		if (ik == 11)
		{
			binwidth_high = 10.*bincenter[ik-1];
		}
		else
		{
			binwidth_high = 0.5*(bincenter[ik+1] - bincenter[ik]);
		}
		binlow[ik+1] = bincenter[ik] - binwidth_low;
		binhigh[ik+1] = bincenter[ik] + binwidth_high;
	//	std::cout<<"binlow[" <<ik <<"] : " << binlow[ik] << std::endl; 
	}
	for (unsigned ik = 0; ik <= sizeof(bincenter)/sizeof(double); ++ik)
	{
	
		std::cout<<"binlow[" <<ik <<"] : " << binlow[ik] << std::endl; 
		std::cout<<"binhigh[" <<ik <<"] : " << binhigh[ik] << std::endl; 
	}
	/// LOG BINS
	/// Variable bin width
	const int ptbins = 40;//no. of bins
	Double_t xbins[ptbins+1];//elements of this array are
	double dx = 5./ptbins;//5 -> implies max until 10^5
	double l10 = TMath::Log(10);
	for (int i = 0; i<=ptbins; i++)
	{
	        //std::cout<<"i,dx : " <<i << ", "<<dx <<std::endl;
		xbins[i] = TMath::Exp(l10*i*dx);
	        std::cout<<"xbin["<<i<<"] : " <<xbins[i] <<std::endl;
	}

return 0;
}
