CLEANFILES=protracer.iss

edit = sed \
	-e 's|@PKGVERSION[@]|$(VERSION)|g'

all: protracer.iss

protracer.iss: protracer.iss.in Makefile
	$(edit) $< >$@

EXTRA_DIST=protracer.iss.in website.url logo.png