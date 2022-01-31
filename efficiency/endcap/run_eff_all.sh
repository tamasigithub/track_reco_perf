#!/usr/bin/env bash
CURRENT_DIR=$PWD
#echo ${CURRENT_DIR}
#sed -i -e 's/30mmEC106mm/30mmEC53mm/g' ./reco_efficiency.cpp
#root -b -l reco_efficiency.cpp -e 'eff_Vs_etaphipt_dR_barcode();'<<EOF
#EOF
#echo 'Done Br30mmEC53mm'
##
#sed -i -e 's/30mmEC53mm/30mmEC67mm/g' ./reco_efficiency.cpp
#root -b -l reco_efficiency.cpp -e 'eff_Vs_etaphipt_dR_barcode();'<<EOF
#EOF
#echo 'Done Br30mmEC67mm'
##
#sed -i -e 's/30mmEC67mm/30mmEC80mm/g' ./reco_efficiency.cpp
#root -b -l reco_efficiency.cpp -e 'eff_Vs_etaphipt_dR_barcode();'<<EOF
#EOF
#echo 'Done Br30mmEC80mm'
##
#sed -i -e 's/30mmEC80mm/30mmEC93mm/g' ./reco_efficiency.cpp
#root -b -l reco_efficiency.cpp -e 'eff_Vs_etaphipt_dR_barcode();'<<EOF
#EOF
#echo 'Done Br30mmEC93mm'
##
#sed -i -e 's/30mmEC93mm/30mmEC106mm/g' ./reco_efficiency.cpp
#root -b -l reco_efficiency.cpp -e 'eff_Vs_etaphipt_dR_barcode();'<<EOF
#EOF
#echo 'Done Br30mmEC106mm'
##
echo 'runnign write to pdf now!'
#
sed -i -e 's/30mmEC106mm/30mmEC53mm/g' ./write_efficiencyAllpcles.cpp
root -b -l write_efficiencyAllpcles.cpp -e 'write_topdf();'<<EOF
EOF
echo 'Done Br30mmEC53mm'
#
sed -i -e 's/30mmEC53mm/30mmEC67mm/g' ./write_efficiencyAllpcles.cpp
root -b -l write_efficiencyAllpcles.cpp -e 'write_topdf();'<<EOF
EOF
echo 'Done Br30mmEC67mm'
#
sed -i -e 's/30mmEC67mm/30mmEC80mm/g' ./write_efficiencyAllpcles.cpp
root -b -l write_efficiencyAllpcles.cpp -e 'write_topdf();'<<EOF
EOF
echo 'Done Br30mmEC80mm'
#
sed -i -e 's/30mmEC80mm/30mmEC93mm/g' ./write_efficiencyAllpcles.cpp
root -b -l write_efficiencyAllpcles.cpp -e 'write_topdf();'<<EOF
EOF
echo 'Done Br30mmEC93mm'
#
sed -i -e 's/30mmEC93mm/30mmEC106mm/g' ./write_efficiencyAllpcles.cpp
root -b -l write_efficiencyAllpcles.cpp -e 'write_topdf();'<<EOF
EOF
echo 'Done Br30mmEC106mm'

