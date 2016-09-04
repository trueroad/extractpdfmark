bin_PROGRAMS = extractpdfmark
extractpdfmark_SOURCES = main.cc output-pdfmark.hh \
	poppler-core.cc pagemode.cc destname.cc encodename.cc \
	pagemode.hh destname.hh destname-private.hh encodename.hh
extractpdfmark_LDADD = $(POPPLER_LIBS)
extractpdfmark_CPPFLAGS = $(POPPLER_CFLAGS)
