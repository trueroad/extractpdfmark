SUBDIRS =

bin_PROGRAMS = extractpdfmark
extractpdfmark_SOURCES = main.cc output-pdfmark.hh cmdlineparse.hh \
	encodename.cc \
	utf16.cc utf16.hh \
	utf8.cc utf8.hh

extractpdfmark_LDADD =
extractpdfmark_LDFLAGS =
extractpdfmark_DEPENDENCIES =

if USE_POPPLER_CORE
SUBDIRS += poppler-core
extractpdfmark_LDADD += -lextractpdfmark-poppler-core $(POPPLER_LIBS)
extractpdfmark_LDFLAGS += -L./poppler-core
extractpdfmark_DEPENDENCIES += ./poppler-core/libextractpdfmark-poppler-core.a
endif
