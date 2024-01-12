#include "occ_max.h"
//union {
//    uint64_t id;
//    struct {
//        unsigned int row     : 16;
//        unsigned int col     : 16;
//        unsigned int chip    : 10;//10;
//        unsigned int ladder  : 8;//8;
//        unsigned int layer   : 5;//5;// four bits to store layer no. from 0010 to 1010 in our case(max 0-15)
//    } in, out;// here in and out corresponds to inner and outer layer
//} pixel;
void clearAll()
{
   sid->clear();
   unique_sids.clear();
   count_unique_sids.clear();
   for(int l = 0; l < tot_layers; l++)
   {
      array_unique_sids[l].clear();
      array_count_sids[l].clear();
   }
  //pxid->clear();
  return;
}
void init_histos()
{
   h = new TH1F*[tot_layers];
   for(int li = 0; li < tot_layers; li++)
   {
      if(li == missing_layer) continue;
      h[li] = new TH1F(TString::Format("h%d", li), TString::Format("max occupancy per sensor for Layer %d",li), nbins, 0., max_cnt);
   }
   return;
}
void write_histos()
{
   for(int li = 0; li < tot_layers; li++)
   {
      if(li == missing_layer) continue;
      h[li]->Write();
   }
   return;
}
void occ_max(bool debug = false)
{

   sprintf(input_file_names, "%s/%s.root",file_path,file_names);
   std::cout<<"input file name: " << input_file_names <<std::endl;
   //f_in = new TFile(input_file_names, "READ");
   //t_in = (TTree*)f_in->Get("mu3e");
   //int num_events = t_in->GetEntries();
   //TChain t_chain("mu3e");
   TChain t_chain("cluster");
   t_chain.Add(input_file_names);
   int num_events = t_chain.GetEntries();
   // ------------ FIX ME ------------//
   //num_events = 1;
   
   std::cout<<"number of events used: " << num_events <<std::endl;

   t_chain.SetBranchAddress("hit_sensorid",&sid);
   //t_in->SetBranchAddress("hit_pixelid",&pxid);
   
   //! create an output file and a tree
   sprintf(out_file, "%s/%s.root",out_path,out_file_name);
   f_out =  new TFile(out_file, "RECREATE");
   std::cout<<"Output File " << out_file << " created!" <<std::endl;

   //! Initialise histograms
   init_histos();
   t_out = new TTree("occupancy","tree for occupancy studies");
   t_out->Branch("unique_sids", &unique_sids);
   t_out->Branch("count_unique_sids", &count_unique_sids);
   for(int l = 0; l < tot_layers; l++)
   {
      if(l==missing_layer) continue;
      array_unique_sids[l].clear();
      array_count_sids[l].clear();
      t_out->Branch(TString::Format("sids_%d",l), &array_unique_sids[l]);
      t_out->Branch(TString::Format("counts_%d",l), &array_count_sids[l]);

      if(debug) 
      {
         std::cout<<"size of unique_sid_"<<l<< " = " << array_unique_sids[l].size() <<std::endl;
         std::cout<<"size of count_sid_"<<l<< " = " << array_count_sids[l].size() <<std::endl;
      }
   }
   //t_out->Branch("sid",&cpy_sid);

   for (int i = 0; i < num_events; i++)
   {
      clearAll();
      t_chain.GetEntry(i);
      
      //! sort the sids for a given event
      std::sort(sid->begin(), sid->end());
      //! make a copy of the sorted sids
      //cpy_sid = sid;

      size_t sid_size = sid->size();
      int x = -1; //represents iterator of unique_sids and count_unique_sids
      int y = -1; //represents iterator of unique_sids and count_unique_sids

      for(int j = 0; j < sid_size; j++)
      {
         if(debug) std::cout<< "j = "<< j <<std::endl;
	 //if(j==0)
	 //{
	 //   x = j;
	 //   unique_sids.push_back((*sid)[j]);
	 //   count_unique_sids.push_back(1);
	 //}
	 //else
	 //{
	 //   if((*sid)[j] == unique_sids[x])
	 //   {
	 //      count_unique_sids[x] += 1;
	 //   }
	 //   else
	 //   {
	 //      x += 1;
	 //      unique_sids.push_back((*sid)[j]);
	 //      count_unique_sids.push_back(1);
	 //   }
	 //   if(debug)
	 //   {
	 //      std::cout<<"jth sid = " <<(*sid)[j]<<std::endl;
	 //      std::cout<<"x, unique_sid, count = " << x << ", " << unique_sids[x] <<", " << count_unique_sids[x] <<std::endl;
	 //   }
	 //}
	 //////////////////////////////////////////////////////////// 
	 //int othermethod_layer = (*sid)[j]>>18;
         //pixel.id = (uint64_t)(*sid)[j] << 32;
         //static_assert(sizeof(pixel.out) == sizeof(pixel.id), "");
	 //current_layer = pixel.out.layer;
         //if(current_layer!=othermethod_layer)std::cout <<"current layer is different: " << current_layer << ", and with bitwise right 18 " << othermethod_layer <<std::endl;
	 //std::cout<< "layer,ladder, chip: " <<current_layer << ",  " << pixel.out.ladder << ",  " <<pixel.out.chip <<std::endl <<std::endl;
	 /////////////////////////////////////////////////////////////
	 current_layer = (*sid)[j]>>18;
	 if(array_unique_sids[current_layer].size()==0)
	 {
	    y = 0;
	    array_unique_sids[current_layer].push_back((*sid)[j]);
	    array_count_sids[current_layer].push_back(1);
	 }
	 else
	 {
	    if((*sid)[j] == array_unique_sids[current_layer][y])
	    {
	       array_count_sids[current_layer][y] += 1;
	    }
	    else
	    {
	       y += 1;
	       array_unique_sids[current_layer].push_back((*sid)[j]);
	       array_count_sids[current_layer].push_back(1);
	    }
	 }

	 
      }// loop over all the sids for an event i

      //if(debug) std::cout<<"Now looping over all unique_sids" <<std::endl;
      //int prev_layer = -1;

      ////! Determine the max count/occupancy per sensor for a given layer
      //for(int k = 0; k < unique_sids.size(); k++)
      //{
      //   current_layer = unique_sids[k]>>18;
      //   array_unique_sids[current_layer].push_back(unique_sids[k]);
      //   array_count_sids[current_layer].push_back(count_unique_sids[k]);

      //   if(debug) std::cout<< "Previous layer, current layer: " << prev_layer << ", " << current_layer << std::endl;

      //   if(current_layer != prev_layer)
      //   {
      //      vec_max_count[current_layer] =  count_unique_sids[k];
      //      prev_layer = current_layer;
      //   }
      //   else
      //   {
      //      if(vec_max_count[current_layer] < count_unique_sids[k])
      //      {
      //         vec_max_count[current_layer] = count_unique_sids[k];
      //      }
      //      else continue;
      //   }

      //   if(debug)
      //   {
      //      std::cout<<"layer, count[k], max_count[layer]: " << current_layer << ", " << count_unique_sids[k] << ", " << vec_max_count[current_layer]<<std::endl;
      //   }

      //}// loop over unique sids

      for(int l = 0; l < tot_layers; l++)
      {
         if(l == missing_layer) continue;
	 //h[l]->Fill(vec_max_count[l]);
	 h[l]->Fill(*std::max_element(array_count_sids[l].begin(), array_count_sids[l].end()));
	 //if(i==0) h[l]->GetXaxis()->SetRangeUser(vec_max_count[l]/3,vec_max_count[l]*3);
      }// loop over N layers
	   
      t_out->Fill();

   }// loop over all events
   t_out->Write();
   write_histos();
   f_out->Close();

   //TODO: delete pointers
   return;
}

