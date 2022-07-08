#!/usr/bin/env bash
CURRENT_DIR=$PWD
echo ${CURRENT_DIR}

#PU0
sed -i -e 's/nbins = .*/nbins = 100;/g' ./occ_max.h
sed -i -e 's/max_cnt = .*/max_cnt = 100.;/g' ./occ_max.h
sed -i -e 's/file_path = ".*/file_path = "\/user\/tkar\/work\/data\/sim\/user.tkar.ggF1.0hh4b_SIMPU0_30mmEC80mm_selected_0_output.root";/g' ./occ_max.h
sed -i -e 's/file_names = ".*/file_names = "user.tkar.28081261._0000*.output";/g' ./occ_max.h
sed -i -e 's/out_file_name = ".*/out_file_name = "occ_max_ggF1_PU0";/g' ./occ_max.h
root -l occ_max.cpp -e 'occ_max();'<<EOF
EOF
sed -i -e 's/bins = .*/bins = 100;/g' ./hitloss.h
sed -i -e 's/max_bin = .*/max_bin = 100.;/g' ./hitloss.h
sed -i -e 's/in_file_name = ".*/in_file_name = "occ_max_ggF1_PU0";/g' ./hitloss.h
sed -i -e 's/out_file_name = ".*/out_file_name = "occ_summ_ggF1_PU0";/g' ./hitloss.h
root -l hitloss.cpp -e 'loss();'<<EOF
EOF

#MBPU0
sed -i -e 's/nbins = .*/nbins = 100;/g' ./occ_max.h
sed -i -e 's/max_cnt = .*/max_cnt = 100.;/g' ./occ_max.h
sed -i -e 's/file_path = ".*/file_path = "\/user\/tkar\/work\/data\/sim\/user.tkar.minbias_low_SIMPU0_30mmEC80mm_3_output.root";/g' ./occ_max.h
sed -i -e 's/file_names = ".*/file_names = "user.tkar.24586470._00000*.output";/g' ./occ_max.h
sed -i -e 's/out_file_name = ".*/out_file_name = "occ_max_MBL_PU0";/g' ./occ_max.h
root -l occ_max.cpp -e 'occ_max();'<<EOF
EOF
sed -i -e 's/bins = .*/bins = 100;/g' ./hitloss.h
sed -i -e 's/max_bin = .*/max_bin = 100.;/g' ./hitloss.h
sed -i -e 's/in_file_name = ".*/in_file_name = "occ_max_MBL_PU0";/g' ./hitloss.h
sed -i -e 's/out_file_name = ".*/out_file_name = "occ_summ_MBL_PU0";/g' ./hitloss.h
root -l hitloss.cpp -e 'loss();'<<EOF
EOF

#MBHU0
sed -i -e 's/nbins = .*/nbins = 100;/g' ./occ_max.h
sed -i -e 's/max_cnt = .*/max_cnt = 100.;/g' ./occ_max.h
sed -i -e 's/file_path = ".*/file_path = "\/user\/tkar\/work\/data\/sim\/user.tkar.minbias_high_SIMPU0_30mmEC80mm_2_output.root";/g' ./occ_max.h
sed -i -e 's/file_names = ".*/file_names = "user.tkar.24800306._00000*.output";/g' ./occ_max.h
sed -i -e 's/out_file_name = ".*/out_file_name = "occ_max_MBH_PU0";/g' ./occ_max.h
root -l occ_max.cpp -e 'occ_max();'<<EOF
EOF
sed -i -e 's/bins = .*/bins = 100;/g' ./hitloss.h
sed -i -e 's/max_bin = .*/max_bin = 100.;/g' ./hitloss.h
sed -i -e 's/in_file_name = ".*/in_file_name = "occ_max_MBH_PU0";/g' ./hitloss.h
sed -i -e 's/out_file_name = ".*/out_file_name = "occ_summ_MBH_PU0";/g' ./hitloss.h
root -l hitloss.cpp -e 'loss();'<<EOF
EOF

#pp4bPU0
sed -i -e 's/nbins = .*/nbins = 100;/g' ./occ_max.h
sed -i -e 's/max_cnt = .*/max_cnt = 100.;/g' ./occ_max.h
sed -i -e 's/file_path = ".*/file_path = "\/user\/tkar\/work\/data\/sim\/user.tkar.pp_4bQCD_SIMPU0_30mmEC80mm_selected_0_output.root";/g' ./occ_max.h
sed -i -e 's/file_names = ".*/file_names = "user.tkar.28081276._00000*.output";/g' ./occ_max.h
sed -i -e 's/out_file_name = ".*/out_file_name = "occ_max_pp4b_PU0";/g' ./occ_max.h
root -l occ_max.cpp -e 'occ_max();'<<EOF
EOF
sed -i -e 's/bins = .*/bins = 100;/g' ./hitloss.h
sed -i -e 's/max_bin = .*/max_bin = 100.;/g' ./hitloss.h
sed -i -e 's/in_file_name = ".*/in_file_name = "occ_max_pp4b_PU0";/g' ./hitloss.h
sed -i -e 's/out_file_name = ".*/out_file_name = "occ_summ_pp4b_PU0";/g' ./hitloss.h
root -l hitloss.cpp -e 'loss();'<<EOF
EOF

#PU1000
sed -i -e 's/nbins = .*/nbins = 1000;/g' ./occ_max.h
sed -i -e 's/max_cnt = .*/max_cnt = 1000.;/g' ./occ_max.h
sed -i -e 's/file_path = ".*/file_path = "\/user\/tkar\/work\/data\/merge\/user.tkar.ggF1.0hh4b_SIMPU1k_Br30mmEC80mm_selected";/g' ./occ_max.h
sed -i -e 's/file_names = ".*/file_names = "user.tkar.28081261._0000*.output.merged";/g' ./occ_max.h
sed -i -e 's/out_file_name = ".*/out_file_name = "occ_max_ggF1_PU1k";/g' ./occ_max.h
root -l occ_max.cpp -e 'occ_max();'<<EOF
EOF
sed -i -e 's/bins = .*/bins = 200;/g' ./hitloss.h
sed -i -e 's/max_bin = .*/max_bin = 200.;/g' ./hitloss.h
sed -i -e 's/in_file_name = ".*/in_file_name = "occ_max_ggF1_PU1k";/g' ./hitloss.h
sed -i -e 's/out_file_name = ".*/out_file_name = "occ_summ_ggF1_PU1k";/g' ./hitloss.h
root -l hitloss.cpp -e 'loss();'<<EOF
EOF

#PU200
sed -i -e 's/nbins = .*/nbins = 500;/g' ./occ_max.h
sed -i -e 's/max_cnt = .*/max_cnt = 500.;/g' ./occ_max.h
sed -i -e 's/file_path = ".*/file_path = "\/user\/tkar\/work\/data\/merge\/user.tkar.ggF1.0hh4b_SIMPU200_Br30mmEC80mm";/g' ./occ_max.h
sed -i -e 's/file_names = ".*/file_names = "user.tkar.24726593._0000*.output.merged";/g' ./occ_max.h
sed -i -e 's/out_file_name = ".*/out_file_name = "occ_max_ggF1_PU200";/g' ./occ_max.h
root -l occ_max.cpp -e 'occ_max();'<<EOF
EOF
sed -i -e 's/bins = .*/bins = 150;/g' ./hitloss.h
sed -i -e 's/max_bin = .*/max_bin = 150.;/g' ./hitloss.h
sed -i -e 's/in_file_name = ".*/in_file_name = "occ_max_ggF1_PU200";/g' ./hitloss.h
sed -i -e 's/out_file_name = ".*/out_file_name = "occ_summ_ggF1_PU200";/g' ./hitloss.h
root -l hitloss.cpp -e 'loss();'<<EOF
EOF
