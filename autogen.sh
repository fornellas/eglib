#!/bin/sh -ex
for dir in "$(dirname "$0")" "$(dirname "$0")/font_generator"
do
	cd "$dir"
	gnulib-tool --copy-file build-aux/git-version-gen
	autoreconf --verbose --force --install --warnings=error
	cd -
done