TESTS = test-desttype-round.sh

TESTS_ENVIRONMENT = top_builddir=$(top_builddir) GS=$(GS)

check_PROGRAMS = dummy
dummy_SOURCES = dummy.cc
dummy_DEPENDENCIES = desttype.pdf destonly.pdf nodest.pdf \
	pdfdocencoding.pdf utf16.pdf utf8.pdf binary.pdf \
	namedict.pdf

PDFTEX = pdftex
GS = gs

namedict.pdf: nodest.pdf addnamedict.ps
	$(GS) -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -sOutputFile=$@ \
		-dCompatibilityLevel=1.1 $^

SUFFIXES = .tex .pdf

.tex.pdf:
	$(PDFTEX) $<
