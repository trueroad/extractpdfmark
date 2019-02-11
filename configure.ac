#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Extract PDFmark], [1.0.3], , [extractpdfmark],
        [https://github.com/trueroad/extractpdfmark])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_HEADERS([config.h])

PACKAGE_COPYRIGHT="Copyright (C) 2016-2019 Masamichi Hosoda"
PACKAGE_LICENSE="License: GPL3+"

AC_SUBST([PACKAGE_COPYRIGHT])
AC_SUBST([PACKAGE_LICENSE])
AC_DEFINE_UNQUOTED([PACKAGE_COPYRIGHT], ["$PACKAGE_COPYRIGHT"],
                   [Define to the copyright of this package.])
AC_DEFINE_UNQUOTED([PACKAGE_LICENSE], ["$PACKAGE_LICENSE"],
                   [Define to the license of this package.])

# Checks for programs.
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])
AC_PROG_RANLIB
AC_PROG_GREP

AC_PATH_PROG([DIFF], [diff])
AS_IF([test "x$DIFF" = x],
      [AC_MSG_WARN([diff isn't found. `make check' will skip tests.])])
AC_SUBST([DIFF])

AC_PATH_PROG([GHOSTSCRIPT], [gs])
AS_IF([test ! "x$GHOSTSCRIPT" = x],
      [AC_MSG_CHECKING([for gs version ( >= 9.14 )])
       gs_ver=`$GHOSTSCRIPT --version`
       AX_COMPARE_VERSION([$gs_ver], [ge], [9.14],
           [AC_MSG_RESULT([yes])],
           [AC_MSG_RESULT([no])
            GHOSTSCRIPT=])])
AM_CONDITIONAL([HAVE_GHOSTSCRIPT], [test ! "x$GHOSTSCRIPT" = x])
AM_COND_IF([HAVE_GHOSTSCRIPT],
           ,
           [AC_MSG_WARN(
                [Ghostscript isn't found. `make check' will skip some tests.])])
AC_SUBST([GHOSTSCRIPT])

AC_MSG_CHECKING([for pre-generated test PDFs])
AS_IF([test ! -e ${srcdir}/test/desttype.pdf],
      [AC_MSG_RESULT([no])
       AC_PATH_PROG([PDFTEX], [pdftex])
       AS_IF([test "x$PDFTEX" = x],
             [AC_MSG_WARN(
                  [pdftex isn't found. Test PDFs cannot be generated.])
              AC_MSG_WARN(
                  [You cannot use `make check'.])],
             [AM_COND_IF([HAVE_GHOSTSCRIPT],
                         [AC_MSG_NOTICE(
                             [pdftex is found. Test PDFs will be generated.])],
                         [AC_MSG_WARN(
                             [pdftex is found but ghostscript isn't found.])
                          AC_MSG_WARN(
                             [You cannot use `make check'.])])])],
      [AC_MSG_RESULT([yes])])
AC_SUBST([PDFTEX])

AC_MSG_CHECKING([for pre-generated expected PDFmark files])
AS_IF([test ! -e ${srcdir}/test/desttype-expected.pdfmark],
      [AC_MSG_RESULT([no])
       AC_MSG_WARN(
           [PDFmark files will be generated.])
       AC_MSG_WARN(
           [`make check' cannot compare with the correct expected results.])],
      [AC_MSG_RESULT([yes])])

# Checks for libraries.
PKG_PROG_PKG_CONFIG

AC_ARG_WITH([poppler],
             AS_HELP_STRING([--with-poppler=@<:@auto|cpp|glib|core|core-private@:>@],
                            [Poppler I/F (default: auto)]),
                            ,
                            [with_poppler=auto])
AS_CASE(["$with_poppler"],
        ["cpp"],
            [AC_MSG_NOTICE([--with-poppler=cpp requires poppler >= 0.74.0])
             PKG_CHECK_MODULES([POPPLER_CPP], [poppler-cpp >= 0.74.0])],
        ["glib"],
            [AC_MSG_NOTICE([--with-poppler=glib requires poppler >= 0.74.0])
             PKG_CHECK_MODULES([POPPLER_GLIB], [poppler-glib >= 0.74.0])],
        ["core"],
            [AC_MSG_NOTICE([--with-poppler=core requires poppler >= 0.48.0])
             PKG_CHECK_MODULES([POPPLER], [poppler >= 0.48.0])],
        ["core-private"],
            [AC_MSG_NOTICE(
                 [--with-poppler=core-private requires poppler >= 0.13.3])
             PKG_CHECK_MODULES([POPPLER], [poppler >= 0.13.3])],
        ["auto"],
            [AC_MSG_NOTICE([selecting for --with-poppler=auto])
             AC_MSG_NOTICE([ trying for cpp (poppler-cpp >= 0.74.0)])
             PKG_CHECK_MODULES(
                 [POPPLER_CPP], [poppler-cpp >= 0.74.0],
                 [with_poppler="cpp"],
                 [AC_MSG_NOTICE([ trying for core (poppler >= 0.48.0)])
                  PKG_CHECK_MODULES(
                      [POPPLER], [poppler >= 0.48.0],
                      [with_poppler="core"],
                      [AC_MSG_NOTICE(
                           [ trying for core-private (poppler >= 0.24.4)])
                       PKG_CHECK_MODULES([POPPLER], [poppler >= 0.24.4],
                           [with_poppler="core-private"])])])]
             AC_MSG_NOTICE([use --with-poppler=$with_poppler]),
        [AC_MSG_ERROR([unrecognized --with-poppler argument: $with_poppler])])
AS_CASE(["$with_poppler"],
        ["cpp"],
            [POPPLER_IF="poppler-cpp"
             use_library="cpp"],
        ["glib"],
            [POPPLER_IF="poppler-glib"
             use_library="glib"],
        ["core"],
            [POPPLER_IF="poppler-core"
             use_library="core"
             AC_DEFINE([HAVE_POPPLER_CORE_IF], [1],
                       [Define if poppler-core is selected])],
        ["core-private"],
            [POPPLER_IF="poppler-core private"
             use_library="core"],
        [AC_MSG_ERROR([programming error])])
AM_CONDITIONAL([USE_POPPLER_CORE], [test $use_library = core])
AM_CONDITIONAL([USE_POPPLER_GLIB], [test $use_library = glib])
AM_CONDITIONAL([USE_POPPLER_CPP], [test $use_library = cpp])
AC_DEFINE_UNQUOTED([PACKAGE_STRING], ["$PACKAGE_STRING (with $POPPLER_IF)"],
    [Define to the full name and version, method of this package.])

# Checks for header files.
AM_COND_IF([USE_POPPLER_CORE],
           [AC_LANG_PUSH([C++])
            TEMP_CPPFLAGS=$CPPFLAGS
            CPPFLAGS="$CPPFLAGS $POPPLER_CFLAGS"
            AC_CHECK_HEADERS([Link.h PDFDoc.h PDFDocFactory.h],
                ,
                [AC_MSG_ERROR([poppler xpdf headers are not found.])])
            CPPFLAGS=$TMP_CPPFLAGS
            AC_LANG_POP])

AC_ARG_ENABLE([codecvt],
              [AS_HELP_STRING(
                  [--enable-codecvt],
                  [enable codecvt for UTF-8 checking (default is disable)])],
              ,
              [enable_codecvt=no])
AS_IF([test "x$enable_codecvt" != xno],
      [AC_LANG_PUSH([C++])
       AC_CHECK_HEADERS([codecvt])
       AC_LANG_POP])
AS_IF([test "x$ac_cv_header_codecvt" == xyes],
      [AC_DEFINE([USE_CODECVT], [1], [Define if codecvt is enabled.])])

AC_ARG_ENABLE([iconv],
              [AS_HELP_STRING(
                  [--disable-iconv],
                  [disable iconv for UTF-8 checking (default is enable)])],
              ,
              [enable_iconv=yes])
# AM_ICONV does not seem to be able to put in IF block.
AM_ICONV
AM_CONDITIONAL([USE_ICONV],
    [test "x$enable_iconv" = xyes && \
     test "x$am_cv_func_iconv" = xyes && \
     test "x$ac_cv_header_codecvt" != xyes])
AM_COND_IF([USE_ICONV],
    [AC_DEFINE([USE_ICONV], [1], [Define if iconv is enabled.])],
    [AS_IF([test "x$ac_cv_header_codecvt" != xyes],
        [AC_MSG_WARN(
[Some `make check' will fail since both codecvt and iconv are disabled.])])])

# Checks for typedefs, structures, and compiler characteristics.
AM_COND_IF([USE_POPPLER_CORE],
           [AC_LANG_PUSH([C++])
            TEMP_CPPFLAGS=$CPPFLAGS
            CPPFLAGS="$CPPFLAGS $POPPLER_CFLAGS"
            AC_MSG_CHECKING([for poppler's GooString::c_str ()])
            AC_COMPILE_IFELSE(
                [AC_LANG_PROGRAM(
                     [[ #include <Link.h> ]],
                     [[ GooString goo; const char *dummy = goo.c_str (); ]])],
                [AC_MSG_RESULT([yes])
                 AC_DEFINE([HAS_GOOSTRING_C_STR], [1],
                     [Define if poppler's GooString::c_str () exists])],
                [AC_MSG_RESULT([no])])
            CPPFLAGS=$TMP_CPPFLAGS
            AC_LANG_POP])

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/poppler-core/Makefile
                 src/poppler-glib/Makefile
                 src/poppler-cpp/Makefile
                 man/Makefile
                 test/Makefile])
AC_OUTPUT
