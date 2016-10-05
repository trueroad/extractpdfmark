TESTS = $(TESTMARKS) $(TESTROUNDS)

TEST_EXTENSIONS = .pdfmark .ps

PDFMARK_LOG_COMPILER = $(srcdir)/test-expected-pdfmark.sh
PS_LOG_COMPILER = $(srcdir)/test-round.sh

TESTS_ENVIRONMENT = top_builddir=$(top_builddir) \
	srcdir=$(srcdir) \
	GREP=$(GREP) \
	DIFF=$(DIFF) \
	GHOSTSCRIPT=$(GHOSTSCRIPT)

# Source files for test PDFs
TESTTEXS = binary.tex destonly.tex desttype.tex nodest.tex \
	pdfdocencoding.tex utf16.tex utf8.tex
# Test PDFs
TESTPDFS = $(TESTTEXS:.tex=.pdf) namedict.pdf
# Expected PDFmark for expected pdf test
TESTMARKS = $(TESTPDFS:.pdf=-expected.pdfmark)
# Extracted PDFmark for round test
TESTROUNDS = $(TESTPDFS:.pdf=-round.ps)

# TESTROUNDS should not be contained.
EXTRA_DIST = test-round.sh test-expected-pdfmark.sh addnamedict.ps \
	$(TESTTEXS) $(TESTPDFS) $(TESTMARKS)

# For name object (PDF 1.1) handling test
# PDF 1.2+ uses name tree intead of name object.
# So most PDFs use name tree for named destination.
namedict.pdf: nodest.pdf addnamedict.ps
	$(GHOSTSCRIPT) -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -sOutputFile=$@ \
		-dCompatibilityLevel=1.1 $^

# Generate test PDFs
# Tarball contains them for convenience.
%.pdf: %.tex
	$(PDFTEX) $<

# Generate expected PDFmark
# Tarball should contain them for checking outputs.
%-expected.pdfmark: %.pdf
	$(top_builddir)/src/extractpdfmark $< | \
		$(GREP) -v "^%\|^$$" > $@

# Generate extracted PDFmark
# Tarball should not contain them for checking building environment.
%-round.ps: %.pdf
	$(top_builddir)/src/extractpdfmark -o $@ $<
