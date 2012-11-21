bin_PROGRAMS=protracer

AM_CPPFLAGS=$(PROTRACER_CFLAGS)
protracer_LDADD=$(PROTRACER_LIBS)

protracer_SOURCES=bitmap.cc \
	bitmap.h \
	bitmap_pigment.cc \
	bitmap_pigment.h \
	box.cc \
	box.h \
	camera.cc \
	camera.h \
	color.h \
	color_pigment.h \
	composed_transformation.cc \
	composed_transformation.h \
	constants.h \
	declaration.cc \
	declaration.h \
	disc.h \
	disc.cc \
	exception.h \
	finish.cc \
	finish.h \
	finish_modification.cc \
	finish_modification.h \
	hit_calculation.h \
	item.h \
	lexer.ll \
	light.cc \
	light.h \
	main.cc \
	object.cc \
	object.h \
	object_modification.h \
	parameters.cc \
	parameters.h \
	parser.yy \
	pigment.h \
	pigment_modification.cc \
	pigment_modification.h \
	plane.cc \
	plane.h \
	planar_object.cc \
	planar_object.h \
	ppm_file.cc \
	ppm_file.h \
	ray.h \
	rotation.cc \
	rotation.h \
	scene.h \
	scene.cc \
	sphere.cc \
	sphere.h \
	transformation.h \
	translation.cc \
	translation.h \
	triangle.cc \
	triangle.h \
	union.cc \
	union.h \
	util.cc \
	util.h \
	vector.cc \
	vector.h

BUILT_SOURCES=parser.h parser.cc lexer.cc

CLEANFILES=parser.cc parser.h lexer.cc
DISTCLEANFILES=parser.cc parser.h lexer.cc

AM_YFLAGS=-d