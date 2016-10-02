SUBDIRS = poppler-core

bin_PROGRAMS = extractpdfmark
extractpdfmark_SOURCES = main.cc output-pdfmark.hh \
	encodename.cc encodename.hh \
	utf16.cc utf16.hh \
	utf8.cc utf8.hh

extractpdfmark_LDADD = -lextractpdfmark-poppler-core $(POPPLER_LIBS)
extractpdfmark_LDFLAGS = -L./poppler-core
extractpdfmark_DEPENDENCIES = ./poppler-core/libextractpdfmark-poppler-core.a
