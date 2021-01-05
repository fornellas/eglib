SUBDIRS = fonts font_generator src $(subdirs_extra) tests sphinx
dist_doc_DATA = README.md LICENSE.md

EXTRA_DIST = $(top_srcdir)/.version
BUILT_SOURCES = $(top_srcdir)/.version
$(top_srcdir)/.version:
	echo $(VERSION) > $@-t && mv $@-t $@
dist-hook:
	echo $(VERSION) > $(distdir)/.tarball-version