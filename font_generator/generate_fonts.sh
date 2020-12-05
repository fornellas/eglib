#!/bin/bash -e

LIBERATION_PATH="/usr/share/fonts/truetype/liberation"
EGLIB_ROOT="$(dirname $(realpath "$0"))"/../src
SCALABLE_FONT_SIZES="6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 32 33 34 35 38 39 41 42 46 48 49 50 53 54 56 57 58 61 62 63 64 78 92"
FONT_HEADERS=""

##
## Cleanup
##

mkdir -p "$EGLIB_ROOT"/eglib/drawing/fonts/

##
## Liberation fonts
##

echo "Liberation"

FONT_HEADERS="$FONT_HEADERS fonts/liberation.h"

cat << EOF > "$EGLIB_ROOT"/eglib/drawing/fonts/liberation.h
#ifndef EGLIB_DRAWING_FONTS_LIBERATION_H
#define EGLIB_DRAWING_FONTS_LIBERATION_H

#include "../../drawing.h"

/**
 * Liberation
 * ==========
 *
 * The Liberation Fonts is font collection which aims to provide document layout compatibility as usage of Times New Roman, Arial, Courier New.
 *
 * :Source: https://github.com/liberationfonts/liberation-fonts.
 * :License: SIL Open Font License, Version 1.1
 */

EOF

for FONT_PATH in $(ls -1 "$LIBERATION_PATH"/*.ttf | sort)
do
	NAME="$(basename "${FONT_PATH%*.ttf}" | tr "-" "_" )"
	FONT_TITLE="$(echo ${NAME#Liberation*} | tr _ \ )"
	echo "  $FONT_TITLE"

	cat << EOF >> "$EGLIB_ROOT"/eglib/drawing/fonts/liberation.h
/**
 * $FONT_TITLE
 * $(echo "$FONT_TITLE" | tr "[a-zA-z_ ]" -)
 */

EOF

	for PIXEL_SIZE in $SCALABLE_FONT_SIZES
	do
		NAME_SIZE="$NAME"_"${PIXEL_SIZE}px"
		./font_generator "$FONT_PATH" "$NAME_SIZE" 0 "$PIXEL_SIZE" 32 255 > "$EGLIB_ROOT"/eglib/drawing/fonts/font_"$NAME_SIZE".c
		cat << EOF >> "$EGLIB_ROOT"/eglib/drawing/fonts/liberation.h
/**
 * $FONT_TITLE
 *
 * .. image:: ../../../tests/fonts/test_$NAME_SIZE.png
 */
extern struct font_t font_$NAME_SIZE;

EOF
		touch ../tests/fonts/test_$NAME_SIZE.png
	done
done

echo "#endif" >> "$EGLIB_ROOT"/eglib/drawing/fonts/liberation.h

##
## Header
##

echo "eglib/drawing/fonts.h"

cat << EOF > "$EGLIB_ROOT"/eglib/drawing/fonts.h-
#ifndef EGLIB_DRAWING_FONTS_H
#define EGLIB_DRAWING_FONTS_H

#include "../drawing.h"

EOF

for FONT_HEADER in $FONT_HEADERS
do
	cat << EOF >> "$EGLIB_ROOT"/eglib/drawing/fonts.h-
#include "$FONT_HEADER"

EOF
done

echo "#endif" >> "$EGLIB_ROOT"/eglib/drawing/fonts.h-

mv "$EGLIB_ROOT"/eglib/drawing/fonts.h- "$EGLIB_ROOT"/eglib/drawing/fonts.h