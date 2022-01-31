#!/usr/bin/env bash
CURRENT_DIR=$PWD
echo ${CURRENT_DIR}
sed -i -e 's/EC106/EC53/g' ./newcontrol_EC.cpp
sed -i -e 's/abs(Eta3 - Eta1)<0.009/abs(Eta3 - Eta1)<0.005/g' ./newcontrol_EC_cuts.h
sed -i -e 's/abs(Phi13)<0.028/abs(Phi13)<0.014/g' ./newcontrol_EC_cuts.h
root -b -l newcontrol_EC.cpp -e 'newcontrol();'<<EOF
EOF
echo 'Done Br30mmEC53mm'
#
sed -i -e 's/EC53/EC67/g' ./newcontrol_EC.cpp
sed -i -e 's/abs(Eta3 - Eta1)<0.005/abs(Eta3 - Eta1)<0.006/g' ./newcontrol_EC_cuts.h
sed -i -e 's/abs(Phi13)<0.014/abs(Phi13)<0.018/g' ./newcontrol_EC_cuts.h
root -b -l newcontrol_EC.cpp -e 'newcontrol();'<<EOF
EOF
echo 'Done Br30mmEC67mm'
#
sed -i -e 's/EC67/EC80/g' ./newcontrol_EC.cpp
sed -i -e 's/abs(Eta3 - Eta1)<0.006/abs(Eta3 - Eta1)<0.007/g' ./newcontrol_EC_cuts.h
sed -i -e 's/abs(Phi13)<0.018/abs(Phi13)<0.021/g' ./newcontrol_EC_cuts.h
root -b -l newcontrol_EC.cpp -e 'newcontrol();'<<EOF
EOF
echo 'Done Br30mmEC80mm'
#
sed -i -e 's/EC80/EC93/g' ./newcontrol_EC.cpp
sed -i -e 's/abs(Eta3 - Eta1)<0.007/abs(Eta3 - Eta1)<0.008/g' ./newcontrol_EC_cuts.h
sed -i -e 's/abs(Phi13)<0.021/abs(Phi13)<0.025/g' ./newcontrol_EC_cuts.h
root -b -l newcontrol_EC.cpp -e 'newcontrol();'<<EOF
EOF
echo 'Done Br30mmEC93mm'
#
sed -i -e 's/EC93/EC106/g' ./newcontrol_EC.cpp
sed -i -e 's/abs(Eta3 - Eta1)<0.008/abs(Eta3 - Eta1)<0.009/g' ./newcontrol_EC_cuts.h
sed -i -e 's/abs(Phi13)<0.025/abs(Phi13)<0.028/g' ./newcontrol_EC_cuts.h
root -b -l newcontrol_EC.cpp -e 'newcontrol();'<<EOF
EOF
echo 'Done Br30mmEC106mm'
#######
#######
sed -i -e 's/EC106/EC53/g' ./control_to_pdf_EC.cpp
root -b -l control_to_pdf_EC.cpp -e 'write_to_pdf();'<<EOF
EOF
echo 'Done pdf Br30mmEC53mm'
#
sed -i -e 's/EC53/EC67/g' ./control_to_pdf_EC.cpp
root -b -l control_to_pdf_EC.cpp -e 'write_to_pdf();'<<EOF
EOF
echo 'Done pdf Br30mmEC67mm'
#
sed -i -e 's/EC67/EC80/g' ./control_to_pdf_EC.cpp
root -b -l control_to_pdf_EC.cpp -e 'write_to_pdf();'<<EOF
EOF
echo 'Done pdf Br30mmEC80mm'
#
sed -i -e 's/EC80/EC93/g' ./control_to_pdf_EC.cpp
root -b -l control_to_pdf_EC.cpp -e 'write_to_pdf();'<<EOF
EOF
echo 'Done pdf Br30mmEC93mm'
#
sed -i -e 's/EC93/EC106/g' ./control_to_pdf_EC.cpp
root -b -l control_to_pdf_EC.cpp -e 'write_to_pdf();'<<EOF
EOF
echo 'Done pdf Br30mmEC106mm'
#
