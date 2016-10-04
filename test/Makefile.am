TESTS = test-desttype-round.sh

TESTS_ENVIRONMENT = top_builddir=$(top_builddir) \
	srcdir=$(srcdir) \
	GS=$(GS)

check_PROGRAMS = dummy
dummy_SOURCES = dummy.cc
dummy_DEPENDENCIES = $(TESTPDFS) $(TESTMARKS)

TESTTEXS = $(notdir $(wildcard $(srcdir)/*.tex))
TESTPDFS = $(TESTTEXS:.tex=.pdf) namedict.pdf
TESTMARKS = $(TESTPDFS:.pdf=.mark)

EXTRA_DIST = test-desttype-round.sh addnamedict.ps \
	$(TESTTEXS) $(TESTPDFS) $(TESTMARKS)

PDFTEX = pdftex
GS = gs

namedict.pdf: nodest.pdf addnamedict.ps
	$(GS) -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -sOutputFile=$@ \
		-dCompatibilityLevel=1.1 $^

SUFFIXES = .tex .pdf .mark

.tex.pdf:
	$(PDFTEX) $<

.pdf.mark:
	$(top_builddir)/src/extractpdfmark $< | \
		$(GREP) -v "^%\|^$$" > $@
