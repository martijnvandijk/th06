# TARGET  = ReqArch
PDFNAME = ../PDF/Requirements\ Architecture
DOCROOT = ../../

# DOCUMENTS = agenda_18-11-2015 agenda_2-12-2015 agenda_09-12-2015 
DOCUMENTS = $(shell ls Notulen*.tex | sed 's/\(.*\)\..*/\1/')

agendas:
	$(foreach var,$(DOCUMENTS),xelatex $(var).tex;)

include $(DOCROOT)/Makefile.inc