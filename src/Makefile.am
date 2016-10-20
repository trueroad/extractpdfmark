SUBDIRS =

bin_PROGRAMS = extractpdfmark
extractpdfmark_SOURCES = main.cc cmdlineparse.hh \
	output-pdfmark.cc output-pdfmark.hh \
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

if USE_POPPLER_GLIB
SUBDIRS += poppler-glib
extractpdfmark_LDADD += -lextractpdfmark-poppler-glib $(POPPLER_GLIB_LIBS)
extractpdfmark_LDFLAGS += -L./poppler-glib
extractpdfmark_DEPENDENCIES += ./poppler-glib/libextractpdfmark-poppler-glib.a
endif

if USE_ICONV
extractpdfmark_SOURCES += iconv_wrapper.hh
extractpdfmark_LDADD += $(LIBICONV)
endif
