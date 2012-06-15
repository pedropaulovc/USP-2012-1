document : document.tex
	pdflatex document.tex
	bibtex document.aux
	pdflatex document.tex
	pdflatex document.tex

clean : 
	rm -f document.aux document.bbl document.log document.out document.blg
