TESTS = test-desttype-round.sh

TESTS_ENVIRONMENT = top_builddir=$(top_builddir) GS=$(GS)

check_PROGRAMS = dummy
dummy_SOURCES = dummy.cc
dummy_DEPENDENCIES = desttype.pdf

PDFTEX = pdftex
GS = gs

SUFFIXES = .tex .pdf

.tex.pdf:
	$(PDFTEX) $<
