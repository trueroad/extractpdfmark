#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Extract PDFmark], [0.01], , [extractpdfname],
[https://github.com/trueroad/extractpdfmark/])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_HEADERS([config.h])

PACKAGE_COPYRIGHT="Copyright (C) 2016 Masamichi Hosoda"
PACKAGE_LICENSE="License: GPL3+"

AC_SUBST([PACKAGE_COPYRIGHT])
AC_SUBST([PACKAGE_LICENSE])
AC_DEFINE_UNQUOTED([PACKAGE_COPYRIGHT], ["$PACKAGE_COPYRIGHT"],
[Define to the copyright of this package.])
AC_DEFINE_UNQUOTED([PACKAGE_LICENSE], ["$PACKAGE_LICENSE"],
[Define to the license of this package.])

# Checks for programs.
AC_PROG_CXX
AC_PROG_RANLIB
AC_PROG_GREP

AC_PATH_PROG([DIFF], [diff])
if test x"$DIFF" = x; then
   AC_MSG_WARN([diff isn't found. `make check' will skip tests.])
fi
AC_SUBST([DIFF])

AC_PATH_PROG([GHOSTSCRIPT], [gs])
if test x"$GHOSTSCRIPT" = x; then
   AC_MSG_WARN([Ghostscript isn't found. `make check' will skip some tests.])
fi
AC_SUBST([GHOSTSCRIPT])

AC_MSG_CHECKING([for pre-generated test PDFs])
if test ! -e ${srcdir}/test/desttype.pdf ; then
   AC_MSG_RESULT([no])
   AC_PATH_PROG([PDFTEX], [pdftex])
   if test x"$PDFTEX" = x; then
      AC_MSG_WARN([pdftex isn't found. Test PDFs cannot be generated.])
      AC_MSG_WARN([You cannot use `make check'.])
   else
      AC_MSG_NOTICE([pdftex is found. Test PDFs will be generated.])
   fi
else
   AC_MSG_RESULT([yes])
fi
AC_SUBST([PDFTEX])

AC_MSG_CHECKING([for pre-generated expected PDFmark files])
if test ! -e ${srcdir}/test/desttype-expected.pdfmark ; then
   AC_MSG_RESULT([no])
   AC_MSG_WARN([PDFmark files will be generated.])
   AC_MSG_WARN([`make check' cannot compare with the correct expected results.])
else
   AC_MSG_RESULT([yes])
fi

# Checks for libraries.
PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([POPPLER], [poppler >= 0.13.3])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

# Checks for library functions.

AC_CONFIG_FILES([Makefile
	src/Makefile
	src/poppler-core/Makefile
	test/Makefile])
AC_OUTPUT
