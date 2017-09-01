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
	pdfdocencoding.tex utf16.tex utf8.tex special-chars.tex \
	pagemode-usenone.tex pagemode-thumbs.tex pagemode-fullscreen.tex
# Test PDFs
TESTPDFS = $(TESTTEXS:.tex=.pdf) namedict.pdf
# Expected PDFmark for expected pdf test
TESTMARKS = $(TESTPDFS:.pdf=-expected.pdfmark) \
	destonly-expected-literal-escape.pdfmark \
	destonly-expected-hex.pdfmark \
	destonly-expected-name.pdfmark \
	destonly-expected-name-escape.pdfmark \
	utf8-expected-literal-escape.pdfmark \
	utf8-expected-hex.pdfmark \
	utf8-expected-name.pdfmark \
	utf8-expected-name-escape.pdfmark \
	special-chars-expected-literal-escape.pdfmark \
	special-chars-expected-hex.pdfmark \
	special-chars-expected-name.pdfmark \
	special-chars-expected-name-escape.pdfmark
# Extracted PDFmark for round test
TESTROUNDS = $(TESTPDFS:.pdf=-round.ps) \
	destonly-round-literal-escape.ps \
	destonly-round-hex.ps \
	destonly-round-name.ps \
	utf8-round-literal-escape.ps \
	utf8-round-hex.ps \
	special-chars-round-literal-escape.ps \
	special-chars-round-hex.ps

# TESTROUNDS should not be contained.
EXTRA_DIST = test-round.sh test-expected-pdfmark.sh addnamedict.ps \
	$(TESTTEXS) $(TESTPDFS) $(TESTMARKS)

# For `make clean'
CLEANFILES = $(TESTMARKS:-expected.pdfmark=-expected-test.pdfmark) \
	$(TESTMARKS:-expected-literal-escape.pdfmark=-expected-literal-escape-test.pdfmark) \
	$(TESTMARKS:-expected-hex.pdfmark=-expected-hex-test.pdfmark) \
	$(TESTMARKS:-expected-name.pdfmark=-expected-name-test.pdfmark) \
	$(TESTMARKS:-expected-name-escape.pdfmark=-expected-name-escape-test.pdfmark) \
	$(TESTROUNDS:-round.ps=-round-test.pdf) \
	$(TESTROUNDS:-round.ps=-round-test.ps) \
	$(TESTROUNDS:-round-literal-escape.ps=-round-literal-escape-test.pdf) \
	$(TESTROUNDS:-round-literal-escape.ps=-round-literal-escape-test.ps) \
	$(TESTROUNDS:-round-hex.ps=-round-hex-test.pdf) \
	$(TESTROUNDS:-round-hex.ps=-round-hex-test.ps) \
	$(TESTROUNDS:-round-name.ps=-round-name-test.pdf) \
	$(TESTROUNDS:-round-name.ps=-round-name-test.ps) \
	$(TESTROUNDS:-round-name-escape.ps=-round-name-escape-test.pdf) \
	$(TESTROUNDS:-round-name-escape.ps=-round-name-escape-test.ps)

if HAVE_GHOSTSCRIPT
# For name object (PDF 1.1) handling test
# PDF 1.2+ uses name tree instead of name object.
# So most PDFs use name tree for named destination.
namedict.pdf: nodest.pdf addnamedict.ps
	$(GHOSTSCRIPT) -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -sOutputFile=$@ \
		-dCompatibilityLevel=1.1 $^
else
namedict.pdf:
	touch $@
endif

# Generate test PDFs
# Tarball contains them for convenience.
%.pdf: %.tex
	$(PDFTEX) $<

# Generate expected PDFmark
# Tarball should contain them for checking outputs.
%-expected.pdfmark: %.pdf
	$(top_builddir)/src/extractpdfmark $< | \
		$(GREP) -v "^%\|^$$" > $@

# Generate expected PDFmark with hexadecimal style
# Tarball should contain them for checking outputs.
%-expected-hex.pdfmark: %.pdf
	$(top_builddir)/src/extractpdfmark --style=hex $< | \
		$(GREP) -v "^%\|^$$" > $@

# Generate expected PDFmark with literal style full escaped
# Tarball should contain them for checking outputs.
%-expected-literal-escape.pdfmark: %.pdf
	$(top_builddir)/src/extractpdfmark --style=literal --escape $< | \
		$(GREP) -v "^%\|^$$" > $@

# Generate expected PDFmark with name style
# Tarball should contain them for checking outputs.
%-expected-name.pdfmark: %.pdf
	$(top_builddir)/src/extractpdfmark --style=name $< | \
		$(GREP) -v "^%\|^$$" > $@

# Generate expected PDFmark with name style full escaped
# Tarball should contain them for checking outputs.
%-expected-name-escape.pdfmark: %.pdf
	$(top_builddir)/src/extractpdfmark --style=name --escape $< | \
		$(GREP) -v "^%\|^$$" > $@

# Generate extracted PDFmark
# Tarball should not contain them for checking building environment.
%-round.ps: %.pdf
	$(top_builddir)/src/extractpdfmark -o $@ $<

# Generate extracted PDFmark with hexadecimal style
# Tarball should not contain them for checking building environment.
%-round-hex.ps: %.pdf
	$(top_builddir)/src/extractpdfmark --style=hex -o $@ $<

# Generate extracted PDFmark with literal style full escaped
# Tarball should not contain them for checking building environment.
%-round-literal-escape.ps: %.pdf
	$(top_builddir)/src/extractpdfmark --style=literal --escape  -o $@ $<

# Generate extracted PDFmark with name style
# Tarball should not contain them for checking building environment.
%-round-name.ps: %.pdf
	$(top_builddir)/src/extractpdfmark --style=name -o $@ $<

# Generate extracted PDFmark with name style full escaped
# Tarball should not contain them for checking building environment.
%-round-name-escape.ps: %.pdf
	$(top_builddir)/src/extractpdfmark --style=name --escape  -o $@ $<
