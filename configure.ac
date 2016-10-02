#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Extract PDFmark], [0.01], , extractpdfname,
[https://github.com/trueroad/extractpdfmark/])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_HEADERS([config.h])

PACKAGE_COPYRIGHT="Copyright (C) 2016 Masamichi Hosoda"
PACKAGE_LICENSE="License: GPL3+"

AC_SUBST(PACKAGE_COPYRIGHT)
AC_SUBST(PACKAGE_LICENSE)
AC_DEFINE_UNQUOTED(PACKAGE_COPYRIGHT, "$PACKAGE_COPYRIGHT",
[Define to the copyright of this package.])
AC_DEFINE_UNQUOTED(PACKAGE_LICENSE, "$PACKAGE_LICENSE",
[Define to the license of this package.])

# Checks for programs.
AC_PROG_CXX
AC_PROG_RANLIB

# Checks for libraries.
PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES(POPPLER,poppler >= 0.13.3)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

# Checks for library functions.

AC_CONFIG_FILES(Makefile src/Makefile src/poppler-core/Makefile)
AC_OUTPUT
