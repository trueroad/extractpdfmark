TESTS = $(TESTMARKS) $(TESTROUNDS)

TEST_EXTENSIONS = .pdfmark .ps

PDFMARK_LOG_COMPILER = $(srcdir)/test-expected-pdfmark.sh
PS_LOG_COMPILER = $(srcdir)/test-round.sh

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
TESTMARKS = $(TESTPDFS:.pdf=-expected.pdfmark)
TESTROUNDS = $(TESTPDFS:.pdf=-round.ps)

# TESTROUNDS should not be contained.
EXTRA_DIST = test-round.sh test-expected-pdfmark.sh addnamedict.ps \
	$(TESTTEXS) $(TESTPDFS) $(TESTMARKS)

PDFTEX = pdftex
GS = gs

namedict.pdf: nodest.pdf addnamedict.ps
	$(GS) -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -sOutputFile=$@ \
		-dCompatibilityLevel=1.1 $^

%.pdf: %.tex
	$(PDFTEX) $<

%-expected.pdfmark: %.pdf
	$(top_builddir)/src/extractpdfmark $< | \
		$(GREP) -v "^%\|^$$" > $@

%-round.ps: %.pdf
	$(top_builddir)/src/extractpdfmark -o $@ $<
