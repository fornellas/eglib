#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(
	[eglib-font_generator],
	m4_esyscmd([build-aux/git-version-gen .tarball-version]),
	[https://github.com/fornellas/eglib/issues],
	[eglib],
	[https://fornellas.github.io/eglib/])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_SILENT_RULES([yes])
AC_CONFIG_SRCDIR([font_generator.c])
AC_CONFIG_MACRO_DIR([/usr/share/aclocal])

# Checks for programs.
: ${CFLAGS="-g -O3"}
AM_CFLAGS="-Wall -Wextra -Wimplicit-function-declaration -Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wshadow -Werror -Wfatal-errors"
AC_SUBST([AM_CFLAGS])
AC_PROG_CC
AC_PROG_AWK
AC_PROG_MAKE_SET
PKG_PROG_PKG_CONFIG

# Checks for libraries.
PKG_CHECK_MODULES([FREETYPE2], [freetype2 >= 2.10.1])

# Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
if test x$ac_cv_header_stdbool_h != xyes
then
	echo "stdbool.h not found!"
	exit 1
fi
AC_TYPE_INT16_T
AC_TYPE_UINT16_T
AC_TYPE_UINT8_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
