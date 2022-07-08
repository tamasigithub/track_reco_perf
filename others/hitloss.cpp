#include "hitloss.h"

void init_histos()
{
   h0 = (TH1F*)f->Get("h0");
   h1 = (TH1F*)f->Get("h1");
   h2 = (TH1F*)f->Get("h2");
   h3 = (TH1F*)f->Get("h3");
   h4 = (TH1F*)f->Get("h4");
   h5 = (TH1F*)f->Get("h5");
   h6 = (TH1F*)f->Get("h6");
   h8 = (TH1F*)f->Get("h8");
   h9 = (TH1F*)f->Get("h9");
   h10 = (TH1F*)f->Get("h10");
   h11 = (TH1F*)f->Get("h11");
   h12 = (TH1F*)f->Get("h12");
   h13 = (TH1F*)f->Get("h13");
   h14 = (TH1F*)f->Get("h14");
   h15 = (TH1F*)f->Get("h15");
   h16 = (TH1F*)f->Get("h16");

   h_count8 = new TH1F("h_count8" ,"occupancy per sensor for layer 8 ", bins, 0., max_bin);
   h_count9 = new TH1F("h_count9" ,"occupancy per sensor for layer 9 ", bins, 0., max_bin);
   h_count10= new TH1F("h_count10","occupancy per sensor for layer 10", bins, 0., max_bin);

   ht_count8 = new TH1F("ht_count8" ,"weighted occupancy per sensor for layer 8 ", bins, 0., max_bin);
   ht_count9 = new TH1F("ht_count9" ,"weighted occupancy per sensor for layer 9 ", bins, 0., max_bin);
   ht_count10= new TH1F("ht_count10","weighted occupancy per sensor for layer 10", bins, 0., max_bin);
   
   he_8 = new TH1F("he_8" ,"hit efficiency for layer 8 ", bins, 0., max_bin);
   he_9 = new TH1F("he_9" ,"hit efficiency for layer 9 ", bins, 0., max_bin);
   he_10= new TH1F("he_10","hit efficiency for layer 10", bins, 0., max_bin);
   
   hl_8 = new TH1F("hl_8" ,"hit loss for layer 8 ", bins, 0., max_bin);
   hl_9 = new TH1F("hl_9" ,"hit loss for layer 9 ", bins, 0., max_bin);
   hl_10= new TH1F("hl_10","hit loss for layer 10", bins, 0., max_bin);
   
   return;
}
void writeAll()
{
   ht_count8->Write();
   he_8->Write();
   hl_8->Write();
   
   ht_count9->Write();
   he_9->Write();
   hl_9->Write();
   
   ht_count10->Write();
   he_10->Write();
   hl_10->Write();
   return;
}
void loss(bool debug=false)
{
   sprintf(in_file,"%s/%s.root",in_path,in_file_name);
   f = new TFile(in_file,"READ");
   t = (TTree*)f->Get("occupancy");

   init_histos();

   t->Draw("counts_8>>h_count8");
   t->Draw("counts_9>>h_count9");
   t->Draw("counts_10>>h_count10");

   //! create an output file and a tree
   sprintf(out_file, "%s/%s.root",out_path,out_file_name);
   fout =  new TFile(out_file, "RECREATE");
   std::cout<<"Output File " << out_file << " created!" <<std::endl;

   for(int i = 1; i < bins+1; i++)
   {
      float bin_content = i*h_count8->GetBinContent(i);
      ht_count8->Fill(i, bin_content);
      if(debug) printf("bin num = %d, old content = %f, new content = %f \n", i, h_count8->GetBinContent(i), bin_content);
      
      bin_content = i*h_count9->GetBinContent(i);
      ht_count9->Fill(i, bin_content);
      if(debug) printf("bin num = %d, old content = %f, new content = %f \n", i, h_count9->GetBinContent(i), bin_content);
      
      bin_content = i*h_count10->GetBinContent(i);
      ht_count10->Fill(i, bin_content);
      if(debug) printf("bin num = %d, old content = %f, new content = %f \n \n \n", i, h_count10->GetBinContent(i), bin_content);
   }

   normalization[0] = ht_count8->Integral();
   normalization[1] = ht_count9->Integral();
   normalization[2] = ht_count10->Integral();
   
   for(int i = 1; i < bins+1; i++)
   {
      integral8[i-1] = ht_count8->Integral(0,i);
      integral9[i-1] = ht_count9->Integral(0,i);
      integral10[i-1] = ht_count10->Integral(0,i);
      
      epcilon8[i-1]  = integral8[i-1]/normalization[0];
      epcilon9[i-1]  = integral9[i-1]/normalization[1];
      epcilon10[i-1]  = integral10[i-1]/normalization[2];
    
      he_8->Fill(i, epcilon8[i-1]);
      hl_8->Fill(i, 1-epcilon8[i-1]);
      
      he_9->Fill(i, epcilon9[i-1]);
      hl_9->Fill(i, 1-epcilon9[i-1]);
      
      he_10->Fill(i, epcilon10[i-1]);
      hl_10->Fill(i, 1-epcilon10[i-1]);

   }
   
   //! Write to pdf
   char out_file_open[1023];
   sprintf(out_file_open,"%s/%s.pdf(",out_path,out_file_name);
   char out_file_[1023];
   sprintf(out_file_,"%s/%s.pdf",out_path,out_file_name);
   char out_file_close[1023];
   sprintf(out_file_close,"%s/%s.pdf)",out_path,out_file_name);
   
   TCanvas *C = new TCanvas("C","C",800,800);
   //gStyle->SetOptStat(0);
   //gStyle->SetOptTitle(0);
   
   C->Divide(2,3);
   C->cd(1);
   h0->Draw();
   C->cd(2);
   h1->Draw();
   C->cd(3);
   h2->Draw();
   C->cd(4);
   h3->Draw();
   C->cd(5);
   h4->Draw();
   C->cd(6);
   h5->Draw();
   C->Print(out_file_open,"pdf");
   
   C->Clear();
   C->Divide(3,3);
   C->cd(1);
   h8->Draw();
   C->cd(2);
   h9->Draw();
   C->cd(3);
   h10->Draw();
   C->cd(4);
   h11->Draw();
   C->cd(5);
   h12->Draw();
   C->cd(6);
   h13->Draw();
   C->cd(7);
   h14->Draw();
   C->cd(8);
   h15->Draw();
   C->cd(9);
   h16->Draw();
   C->Print(out_file_open,"pdf");

   C->Clear();
   C->Divide(2,2);
   C->cd(1);
   h_count8->Draw("hist");
   C->cd(2);
   h_count9->Draw("hist");
   C->cd(3);
   h_count10->Draw("hist");
   C->cd(4);
   h_count10->Draw("hist");
   h_count8->Draw("hist same");
   h_count9->Draw("hist same");
   C->Print(out_file_,"pdf");
   
   C->cd(1);
   ht_count8->Draw("hist");
   C->cd(2);
   ht_count9->Draw("hist");
   C->cd(3);
   ht_count10->Draw("hist");
   C->cd(4);
   ht_count8->Draw("hist");
   ht_count9->Draw("hist same");
   ht_count10->Draw("hist same");
   C->Print(out_file_,"pdf");
   
   C->cd(1);
   he_8->Draw("hist");
   C->cd(2);
   he_9->Draw("hist");
   C->cd(3);
   he_10->Draw("hist");
   C->cd(4);
   he_8->SetTitle("");
   he_8->Draw("hist");
   he_9->Draw("hist same");
   he_10->Draw("hist same");
   C->Print(out_file_,"pdf");
  
   C->cd(1);
   hl_8->Draw("hist");
   C->cd(2);
   hl_9->Draw("hist");
   C->cd(3);
   hl_10->Draw("hist");
   C->cd(4);
   hl_8->Draw("hist");
   hl_9->Draw("hist same");
   hl_10->Draw("hist same");
   C->Print(out_file_,"pdf");
   
   TPad *p1 = (TPad*)(C->cd(1));
   p1->SetLogy();
   p1->SetLogx();
   hl_8->Draw("hist");
   TPad *p2 = (TPad*)(C->cd(2));
   p2->SetLogy();
   p2->SetLogx();
   hl_9->Draw("hist");
   TPad *p3 = (TPad*)(C->cd(3));
   p3->SetLogy();
   p3->SetLogx();
   hl_10->Draw("hist");
   TPad *p4 = (TPad*)(C->cd(4));
   p4->SetLogy();
   p4->SetLogx();
   p4->SetGridy();
   p4->SetGridx();
   p4->SetTitle("");
   hl_8->Draw("hist");
   hl_9->Draw("hist same");
   hl_10->Draw("hist same");
   C->Print(out_file_close,"pdf");


   writeAll();
   fout->Close();
   return;
}
