sed -i -e 's/4T/\\SI{4}{\\tesla}/g' ./*.tex
echo 'pdfLatex leg.tex'
pdfLatex ./leg.tex
echo 'pdfLatex reso_dpt.tex'
pdfLatex ./reso_dpt.tex
echo 'pdfLatex reso_eta.tex'
pdfLatex ./reso_eta.tex
echo 'pdfLatex reso_invpt.tex'
pdfLatex ./reso_invpt.tex
echo 'pdfLatex reso_phi.tex'
pdfLatex ./reso_phi.tex
echo 'pdfLatex reso_theta.tex'
pdfLatex ./reso_theta.tex
echo 'pdfLatex reso_z0.tex'
pdfLatex ./reso_z0.tex
rm ./*.log
rm ./*.aux
mv *.pdf ./pdf
