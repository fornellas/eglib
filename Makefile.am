SUBDIRS = fonts font_generator src examples tests sphinx
dist_doc_DATA = README.md LICENSE.md

EXTRA_DIST = $(top_srcdir)/.version
BUILT_SOURCES = $(top_srcdir)/.version
$(top_srcdir)/.version:
	echo $(VERSION) > $@-t && mv $@-t $@
dist-hook:
	echo $(VERSION) > $(distdir)/.tarball-version

.PHONY:
update-html:
	$(MAKE) $(AM_MAKEFLAGS) -C sphinx update-html