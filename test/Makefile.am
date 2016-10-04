TESTS = test-desttype-round.sh $(TESTMARKS)

TEST_EXTENSIONS = .sh .mark

SH_LOG_COMPILER = sh
MARK_LOG_COMPILER = $(srcdir)/test-expected-pdfmark.sh

TESTS_ENVIRONMENT = top_builddir=$(top_builddir) \
	srcdir=$(srcdir) \
	GREP=$(GREP) \
	DIFF=$(DIFF) \
	GS=$(GS)

check_PROGRAMS = dummy
dummy_SOURCES = dummy.cc
dummy_DEPENDENCIES = $(TESTPDFS) $(TESTMARKS)

TESTTEXS = binary.tex destonly.tex desttype.tex nodest.tex \
	pdfdocencoding.tex utf16.tex utf8.tex
TESTPDFS = $(TESTTEXS:.tex=.pdf) namedict.pdf
TESTMARKS = $(TESTPDFS:.pdf=.mark)

EXTRA_DIST = test-desttype-round.sh test-expected-pdfmark.sh addnamedict.ps \
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
