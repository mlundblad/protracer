examplesdir = $(pkgdatadir)/examples
examples_DATA = example1.pov example2.pov sky.ppm

CLEANFILES=$(example1.pov example2.pov)
DISTCLEANFILES=$(example1.pov example2.pov)

edit = sed \
	-e 's|@EXAMPLESDIR[@]|$(examplesdir)|g'

example1.pov: example1.pov.in Makefile
	$(edit) $< >$@

example2.pov: example2.pov.in Makefile
	$(edit) $< >$@

EXTRA_DIST = example1.pov.in example2.pov.in sky.ppm
