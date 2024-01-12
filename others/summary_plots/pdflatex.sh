file_name="summary_summary_hitOcc_PU1k_30mm80mm_Eta2.5_test.tex"
sed -i -e 's/Cluster occupancy.*/\\text\{Cluster occupancy\[\/bunch crossing\/\}\\text\{cm\}\^\{2\}\]\$\};/g' $file_name
#sed -i -e 's/B=4T/B=4\\,\\text\{T\}/g' $file_name
#sed -i -e 's/rate \[MHz/\\text\{Rate \[MHz\}/g' $file_name
#sed -i -e 's/endcap/\\,endcap/g' $file_name
#sed -i -e 's/<\\mu>/~~\\langle\\mu\\rangle/g' $file_name
sed -i -e 's/Layer Radius.*/Layer Radius\\,\[\\text\{cm\}\]\};/g' $file_name
