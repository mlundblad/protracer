examplesdir = $(pkgdatadir)/examples
examples_DATA = example1.pov example2.pov sky.ppm

CLEANFILES=$(examples_DATA)
DISTCLEANFILES=$(examples_DATA)

edit = sed \
	-e 's|@EXAMPLESDIR[@]|$(examplesdir)|g'

example1.pov: example1.pov.in Makefile
	$(edit) $< >$@

example2.pov: example2.pov.in Makefile
	$(edit) $< >$@

EXTRA_DIST = example1.pov.in example2.pov.in sky.ppm
