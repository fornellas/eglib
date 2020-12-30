#!/bin/sh -ex
cd "$(dirname "$0")"
gnulib-tool --copy-file build-aux/git-version-gen
autoreconf --verbose --force --install --warnings=error
