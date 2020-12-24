#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
m4_define(
	[eglib_VERSION],
	[0.0.0])
	# m4_esyscmd([build-aux/git-version-gen .tarball-version]))
AC_INIT(
	[eglib],
	m4_defn([eglib_VERSION]),
	[https://github.com/fornellas/eglib/issues],
	[eglib],
	[https://fornellas.github.io/eglib/])
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_SILENT_RULES([yes])
AC_CONFIG_SRCDIR([src/eglib.c])
AC_CONFIG_FILES([
	Makefile
	font_generator/Makefile
	src/Makefile
])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

# Checks for programs.
CFLAGS="$CFLAGS -MD -O3 -Wall -Wextra -Wimplicit-function-declaration -Wredundant-decls -Wmissing-prototypes -Wundef -Wshadow -Werror -Wfatal-errors"
AC_PROG_CC
AC_PROG_RANLIB
AM_PROG_AR

# Checks for libraries.
PKG_CHECK_MODULES([FREETYPE2], [freetype2 >= 2.10.1])

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdint.h stdlib.h wchar.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.

CFLAGS="$CFLAGS -Wstrict-prototypes"
AC_OUTPUT