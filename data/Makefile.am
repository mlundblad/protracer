examplesdir = $(pkgdatadir)/examples
examples_DATA = example1.pov example2.pov example3.pov example4.pov\
	example5.pov example6.pov example7.pov example8.pov sky.ppm

CLEANFILES=example1.pov example2.pov example3.pov example4.pov example5.pov\
	example6.pov example7.pov example8.pov
DISTCLEANFILES=example1.pov example2.pov example3.pov example4.pov example5.pov\
	example6.pov example7.pov example8.pov

edit = sed \
	-e 's|@EXAMPLESDIR[@]|$(examplesdir)|g'

example1.pov: example1.pov.in Makefile
	$(edit) $< >$@

example2.pov: example2.pov.in Makefile
	$(edit) $< >$@

example3.pov: example3.pov.in Makefile
	$(edit) $< >$@

example4.pov: example4.pov.in Makefile
	$(edit) $< >$@

example5.pov: example5.pov.in Makefile
	$(edit) $< >$@

example6.pov: example6.pov.in Makefile
	$(edit) $< >$@

example7.pov: example7.pov.in Makefile
	$(edit) $< >$@

example8.pov: example8.pov.in Makefile
	$(edit) $< >$@

EXTRA_DIST = example1.pov.in example2.pov.in example3.pov.in example4.pov.in \
	example5.pov.in example6.pov.in example7.pov.in sky.ppm
