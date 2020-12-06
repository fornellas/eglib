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

for FONT_PATH in $(ls -1 "$LIBERATION_PATH"/*.ttf | LANG=C sort)
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
		C_NAME="Liberation_$(echo "${NAME#Liberation*}" | tr -d _\ )_${PIXEL_SIZE}px"
		./font_generator "$FONT_PATH" "$C_NAME" 0 "$PIXEL_SIZE" "${UNICODE_BLOCKS[@]}" > "$EGLIB_ROOT"/eglib/drawing/fonts/font_"$C_NAME".c
		cat << EOF >> "$EGLIB_ROOT"/eglib/drawing/fonts/liberation.h

/**
 * ${PIXEL_SIZE} pixels
 * ====================
 */

/**
 * .. image:: ../../../tests/fonts/test_font_${C_NAME}.png
 */
extern struct font_t font_$C_NAME;

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
 * $UNICODE_BLOCK_NAME unicode block for :c:data:\`font_$C_NAME\`.
 */
extern struct glyph_unicode_block_t unicode_block_${C_NAME}_${UNICODE_BLOCK_NAME};
EOF
		done
		touch ../tests/fonts/test_font_${C_NAME}.png
	done
done

echo "#endif" >> "$EGLIB_ROOT"/eglib/drawing/fonts/liberation.h

##
## Adobe
##

# https://en.wikipedia.org/wiki/Unicode_block
UNICODE_BLOCKS=(
	# https://en.wikipedia.org/wiki/Basic_Latin_(Unicode_block)
	"BasicLatin" "32" "126"
	# https://en.wikipedia.org/wiki/Latin-1_Supplement_(Unicode_block)
	"Latin1Supplement" "161" "255"
	# https://en.wikipedia.org/wiki/Latin_Extended-A
	"LatinExtendedA" "256" "383"
)

echo "Adobe"

FONT_HEADERS="$FONT_HEADERS fonts/adobe.h"

cat << EOF > "$EGLIB_ROOT"/eglib/drawing/fonts/adobe.h
#ifndef EGLIB_DRAWING_FONTS_ADOBE_H
#define EGLIB_DRAWING_FONTS_ADOBE_H

#include "../../drawing.h"

/**
 * Adobe
 * #####
 *
 * These fonts by Adobe are covered by the following license:
 *
 * .. code-block::
 *
 *   Copyright 1984-1989, 1994 Adobe Systems Incorporated.
 *   Copyright 1988, 1994 Digital Equipment Corporation.
 *   
 *   Adobe is a trademark of Adobe Systems Incorporated which may be
 *   registered in certain jurisdictions.
 *   Permission to use these trademarks is hereby granted only in
 *   association with the images described in this file.
 *   
 *   Permission to use, copy, modify, distribute and sell this software
 *   and its documentation for any purpose and without fee is hereby
 *   granted, provided that the above copyright notices appear in all
 *   copies and that both those copyright notices and this permission
 *   notice appear in supporting documentation, and that the names of
 *   Adobe Systems and Digital Equipment Corporation not be used in
 *   advertising or publicity pertaining to distribution of the software
 *   without specific, written prior permission.  Adobe Systems and
 *   Digital Equipment Corporation make no representations about the
 *   suitability of this software for any purpose.  It is provided "as
 *   is" without express or implied warranty.
 *
 * :Source: https://xorg.freedesktop.org/releases/individual/font/
 */
EOF

declare -A ADOBE_FONT_PATHS
declare -A ADOBE_FONT_PIXEL_SIZES

for DPI in 75 100
do
	for FONT_PATH in $(find adobe/${DPI}dpi -name \*.bdf)
	do
		NAME="$(gawk 'BEGIN{FS="\""}/^FULL_NAME /{print $2}' < $FONT_PATH)"
		PIXEL_SIZE="$(gawk '/^PIXEL_SIZE /{print $2}' < $FONT_PATH)"
		ADOBE_FONT_PATHS["$PIXEL_SIZE $NAME"]="$FONT_PATH"
		ADOBE_FONT_PIXEL_SIZES["$NAME"]="${ADOBE_FONT_PIXEL_SIZES["$NAME"]} $PIXEL_SIZE"
	done
done

for NAME in "${!ADOBE_FONT_PIXEL_SIZES[@]}" ; do echo "$NAME" ; done | LANG=C sort | while read NAME
do
	if [ "$NAME" == "Symbol" ]
	then
		continue
	fi
	echo "  $NAME"
	cat << EOF >> "$EGLIB_ROOT"/eglib/drawing/fonts/adobe.h

/**
 * $NAME
 * $(echo "$NAME" | tr "[a-zA-z_ ]" "*")
 */
EOF

	for PIXEL_SIZE in ${ADOBE_FONT_PIXEL_SIZES["$NAME"]} ; do echo "$PIXEL_SIZE" ; done | LANG=C sort -k +1n -u | while read PIXEL_SIZE
	do
		echo "    $PIXEL_SIZE"
		C_NAME="Adobe_$(echo "$NAME" | tr -d \ )_${PIXEL_SIZE}px"
		FONT_PATH="${ADOBE_FONT_PATHS["$PIXEL_SIZE $NAME"]}"
		./font_generator "$FONT_PATH" "$C_NAME" 0 "$PIXEL_SIZE" "${UNICODE_BLOCKS[@]}" > "$EGLIB_ROOT"/eglib/drawing/fonts/font_"$C_NAME".c
		cat << EOF >> "$EGLIB_ROOT"/eglib/drawing/fonts/adobe.h

/**
 * ${PIXEL_SIZE} pixels
 * $(echo "$PIXEL_SIZE" | tr "[0-9]" "=")=======
 */

/**
 * .. image:: ../../../tests/fonts/test_font_${C_NAME}.png
 */
extern struct font_t font_$C_NAME;

/**
 * Unicode blocks
 * --------------
 */
EOF
		for ((i=0 ; i < "${#UNICODE_BLOCKS[@]}" ; i+=3))
		do
			UNICODE_BLOCK_NAME="${UNICODE_BLOCKS[$i]}"
			cat << EOF >> "$EGLIB_ROOT"/eglib/drawing/fonts/adobe.h

/**
 * $UNICODE_BLOCK_NAME unicode block for :c:data:\`font_$C_NAME\`.
 */
extern struct glyph_unicode_block_t unicode_block_${C_NAME}_${UNICODE_BLOCK_NAME};
EOF
		done
		touch ../tests/fonts/test_font_${C_NAME}.png
	done
done

echo "#endif" >> "$EGLIB_ROOT"/eglib/drawing/fonts/adobe.h

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