#!/bin/bash -e

LIBERATION_PATH="/usr/share/fonts/truetype/liberation"
EGLIB_ROOT="$(dirname $(realpath "$0"))"/../src
SCALABLE_FONT_SIZES=(7 8 9 10 11 12 13 14 15 16 18 20 22 24 26 28 32 36 40 44 48 54 60 66 72 80 83 88 96)
FONT_HEADERS=""

# https://en.wikipedia.org/wiki/Unicode_block
UNICODE_BLOCKS=(
	# https://en.wikipedia.org/wiki/Basic_Latin_(Unicode_block)
	"BasicLatin" "32" "126"
	# https://en.wikipedia.org/wiki/Latin-1_Supplement_(Unicode_block)
	"Latin1Supplement" "161" "255"
	# https://en.wikipedia.org/wiki/Latin_Extended-A
	"LatinExtendedA" "256" "383"
	# https://en.wikipedia.org/wiki/Latin_Extended-B
	"LatinExtendedB" "384" "591"
)

##
## Cleanup
##

rm -f "$EGLIB_ROOT"/eglib/drawing/fonts/*.h
rm -f "$EGLIB_ROOT"/eglib/drawing/fonts/*.c
rm -f "$EGLIB_ROOT"/eglib/drawing/fonts.h
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
 * ##########
 *
 * The Liberation Fonts is font collection which aims to provide document layout compatibility as usage of Times New Roman, Arial, Courier New.
 *
 * :Source: https://github.com/liberationfonts/liberation-fonts.
 * :License: SIL Open Font License, Version 1.1
 */
EOF

ls -1 "$LIBERATION_PATH"/*.ttf | sort

for FONT_PATH in $(ls -1 "$LIBERATION_PATH"/*.ttf | sort)
do
	NAME="$(basename "${FONT_PATH%*.ttf}" | tr "-" "_" )"
	FONT_TITLE="$(echo ${NAME#Liberation*} | tr _ \ )"
	echo "  $FONT_TITLE"

	cat << EOF >> "$EGLIB_ROOT"/eglib/drawing/fonts/liberation.h

/**
 * $FONT_TITLE
 * $(echo "$FONT_TITLE" | tr "[a-zA-z_ ]" "*")
 */
EOF

	for PIXEL_SIZE in "${SCALABLE_FONT_SIZES[@]}"
	do
		NAME_SIZE="$NAME"_"${PIXEL_SIZE}px"
		./font_generator "$FONT_PATH" "$NAME_SIZE" 0 "$PIXEL_SIZE" "${UNICODE_BLOCKS[@]}" > "$EGLIB_ROOT"/eglib/drawing/fonts/font_"$NAME_SIZE".c
		cat << EOF >> "$EGLIB_ROOT"/eglib/drawing/fonts/liberation.h

/**
 * ${PIXEL_SIZE} pixels
 * ====================
 */

/**
 * .. image:: ../../../tests/fonts/test_font_${NAME_SIZE}.png
 */
extern struct font_t font_$NAME_SIZE;

/**
 * Unicode blocks
 * --------------
 */
EOF
		for ((i=0 ; i < "${#UNICODE_BLOCKS[@]}" ; i+=3))
		do
			UNICODE_BLOCK_NAME="${UNICODE_BLOCKS[$i]}"
			cat << EOF >> "$EGLIB_ROOT"/eglib/drawing/fonts/liberation.h

/**
 * $UNICODE_BLOCK_NAME unicode block for :c:data:\`font_$NAME_SIZE\`.
 */
extern struct glyph_unicode_block_t unicode_block_${NAME_SIZE}_${UNICODE_BLOCK_NAME};
EOF
		done
		touch ../tests/fonts/test_font_${NAME_SIZE}.png
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