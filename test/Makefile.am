TESTS = test-desttype-round.sh

TESTS_ENVIRONMENT = top_builddir=$(top_builddir) GS=$(GS)

check_PROGRAMS = dummy
dummy_SOURCES = dummy.cc
dummy_DEPENDENCIES = desttype.pdf destonly.pdf nodest.pdf \
	pdfdocencoding.pdf utf16.pdf utf8.pdf binary.pdf \
	namedict.pdf

EXTRA_DIST = test-desttype-round.sh \
	desttype.tex desttype.pdf destonly.tex destonly.pdf \
	nodest.tex nodest.pdf pdfdocencoding.tex pdfdocencoding.pdf \
	utf16.tex utf16.pdf utf8.tex utf8.pdf binary.tex binary.pdf \
	addnamedict.ps namedict.pdf

PDFTEX = pdftex
GS = gs

namedict.pdf: nodest.pdf addnamedict.ps
	$(GS) -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -sOutputFile=$@ \
		-dCompatibilityLevel=1.1 $^

SUFFIXES = .tex .pdf

.tex.pdf:
	$(PDFTEX) $<
