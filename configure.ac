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
AC_CONFIG_AUX_DIR([build-aux])
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_SILENT_RULES([yes])
AC_CONFIG_SRCDIR([src/eglib.c])
AC_CONFIG_MACRO_DIR([/usr/share/aclocal])
AC_CONFIG_FILES([
	font_generator/Makefile
	Makefile
	src/Makefile
	tests/display/Makefile
	tests/drawing/Makefile
	tests/fonts/adobe/Makefile
	tests/fonts/liberation/Makefile
	tests/fonts/Makefile
	tests/frame_buffer/Makefile
	tests/Makefile
])
AC_REQUIRE_AUX_FILE([tap-driver.sh])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

# Checks for programs.
AX_VALGRIND_DFLT([helgrind],[off])
AX_VALGRIND_DFLT([drd],[off])
AX_VALGRIND_DFLT([sgcheck],[off])
AX_VALGRIND_DFLT([memcheck],[on])
AX_VALGRIND_CHECK
AM_CFLAGS="-O3 -Wall -Wextra -Wimplicit-function-declaration -Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wshadow -Werror -Wfatal-errors"
AC_SUBST([AM_CFLAGS])
AC_PROG_CC
AC_PROG_RANLIB
AM_PROG_AR
PKG_PROG_PKG_CONFIG
AC_PROG_AWK
AC_CHECK_PROG([IMAGE_MAGICK_COMPARE], [compare], [yes], [no])
if test x$IMAGE_MAGICK_COMPARE = xno
then
	echo "ImageMagick's \`compare' command not found!"
	exit 1
fi
AC_CHECK_PROG([IMAGE_MAGICK_CONVERT], [convert], [yes], [no])
if test x$IMAGE_MAGICK_COMPARE = xno
then
	echo "ImageMagick's \`convert' command not found!"
	exit 1
fi

# Checks for libraries.
PKG_CHECK_MODULES([FREETYPE2], [freetype2 >= 2.10.1])
PKG_CHECK_MODULES([CHECK], [check >= 0.10.0])

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

AC_OUTPUT