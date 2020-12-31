#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(
	[eglib],
	m4_esyscmd([build-aux/git-version-gen .tarball-version]),
	[https://github.com/fornellas/eglib/issues],
	[eglib],
	[https://fornellas.github.io/eglib/])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_SILENT_RULES([yes])
AC_CONFIG_SRCDIR([src/eglib.c])
AC_CONFIG_MACRO_DIR([/usr/share/aclocal])
AC_REQUIRE_AUX_FILE([tap-driver.sh])

# Canonical
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AM_CONDITIONAL([NOT_CROSS_COMPILE], [test x$build = x$host])

# Checks for programs.
: ${CFLAGS="-g -O3"}
AM_CFLAGS="-Wall -Wextra -Wimplicit-function-declaration -Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wshadow -Werror -Wfatal-errors"
AC_SUBST([AM_CFLAGS])
AC_PROG_CC
AM_PROG_AR
AC_PROG_RANLIB
AX_VALGRIND_DFLT([helgrind],[off])
AX_VALGRIND_DFLT([drd],[off])
AX_VALGRIND_DFLT([sgcheck],[off])
AX_VALGRIND_DFLT([memcheck],[on])
AX_VALGRIND_CHECK
if test "x$build" = "x$host"
then
	AC_CHECK_PROG([IMAGE_MAGICK_COMPARE], [compare], [yes], [no])
	if test "x$IMAGE_MAGICK_COMPARE" = xno
	then
		echo "ImageMagick's \`compare' command not found!"
		exit 1
	fi
	AC_CHECK_PROG([IMAGE_MAGICK_CONVERT], [convert], [yes], [no])
	if test "x$IMAGE_MAGICK_COMPARE" = xno
	then
		echo "ImageMagick's \`convert' command not found!"
		exit 1
	fi
fi

# Checks for libraries.
if test "x$build" = "x$host"
then
	PKG_CHECK_MODULES([CHECK], [check >= 0.10.0])
fi

# Checks for header files.
AC_CHECK_HEADERS([stddef.h], [], [echo "stddef.h not found!" ; exit 1])
AC_CHECK_HEADERS([stdint.h], [], [echo "stdint.h not found!" ; exit 1])
AC_CHECK_HEADERS([stdlib.h], [], [echo "stdlib.h not found!" ; exit 1])
AC_CHECK_HEADERS([wchar.h], [], [echo "wchar.h not found!" ; exit 1])
if test "x$build" = "x$host"
then
	AC_CHECK_HEADERS([fcntl.h], [], [echo "fcntl.h not found!" ; exit 1])
	AC_CHECK_HEADERS([string.h], [], [echo "string.h not found!" ; exit 1])
	AC_CHECK_HEADERS([unistd.h], [], [echo "unistd.h not found!" ; exit 1])
fi

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
if ! test "x$ac_cv_header_stdbool_h" = xyes
then
	echo "stdbool.h not found!"
	exit 1
fi
AC_C_INLINE
if test "x$inline" != x
then
	echo "C does not support inline keyword!"
	exit 1
fi
AC_TYPE_INT16_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T
if test "x$build" = "x$host"
then
	AC_TYPE_SSIZE_T
fi

# Checks for library functions.
if test "x$build" = "x$host"
then
	AC_CHECK_FUNCS([munmap], [], [echo "Function munmap not found!" ; exit 1])
	AC_CHECK_FUNCS([strerror], [], [echo "Function strerror not found!" ; exit 1])
	AC_FUNC_MMAP
	if ! test "x$ac_cv_func_mmap_fixed_mapped" = xyes
	then
		echo "Function mmap not found!"
		exit 1
	fi
fi

AC_CONFIG_FILES([
	Makefile
	fonts/Makefile
	src/Makefile
	sphinx/Makefile
	tests/display/Makefile
	tests/drawing/Makefile
	tests/fonts/adobe/Makefile
	tests/fonts/liberation/Makefile
	tests/fonts/Makefile
	tests/frame_buffer/Makefile
	tests/Makefile])

# Subdirectory packages
ORIGINAL_CC="$CC"
unset CC
ORIGINAL_CFLAGS="$CFLAGS"
unset CFLAGS
AX_SUBDIRS_CONFIGURE([font_generator], [], [], [[--build="$build"], [--host="$build"]], [[CC=.*], [CFLAGS=.*]])
CC="$ORIGINAL_CC"
CFLAGS="$ORIGINAL_CFLAGS"

AC_OUTPUT