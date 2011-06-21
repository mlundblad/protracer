examplesdir = $(pkgdatadir)/examples
examples_DATA = examples/example1.pov examples/example2.pov

CLEANFILES=$(examples_DATA)
DISTCLEANFILES=$(examples_DATA)

edit = sed \
	-e 's|@EXAMPLESDIR[@]|$(examplesdir)|g'

examples/example1.pov: examples/example1.pov.in Makefile
	$(edit) $< >$@

examples/example2.pov: examples/example2.pov.in Makefile
	$(edit) $< >$@
