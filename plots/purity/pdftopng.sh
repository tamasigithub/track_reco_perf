for i in *.pdf; do
   pdftoppm -png -rx 300 -ry 300 $i ${i%.pdf*}
done