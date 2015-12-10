TEX = xelatex

all: $(TARGET)

$(TARGET):
	xelatex $(TARGET).tex
	mv $(TARGET).pdf $(PDFNAME).pdf

.PHONY: removetemporaryfiles
removetemporaryfiles:
	rm -f *.fls *.aux *.out *.log *.fdb_latexmk *.ilg *.idx *.synctex.gz *.toc *.ind *.bcf *.run.xml *.blg
	
.PHONY: clean
clean: removetemporaryfiles