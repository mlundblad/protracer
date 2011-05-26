# Makefile
# for tracer project

LEX	= flex
YACC	= bison
CC	= gcc

CFLAGS	= -Wall -O3

# Caution, these files will be deleted upon clean!!!
GENFILES	= Baseparse.c Baselex.c
# Caution

default:	tracer

tracer:	Baselex.o Tracer.o Baseparse.o Bitmap.o PPMFile.o Camera.o Triangle.o Sphere.o Plane.o Error.o ObjectList.o LightList.o Finish.o ObjectMods.o SphereOptions.o Object.o ObjectArray.o LightArray.o Parameters.o Pigment.o World.o
	${CC} -o $@ $^ -lfl -lm

archive:
	rm -f tracer.tar.gz   # don't want the archive in the archive :-)
	tar -cf tracer.tar *.c *.h Makefile
	gzip tracer.tar

Baseparse.c Baseparse.h:	Baseparse.y
	${YACC} -d -o Baseparse.c Baseparse.y

Tracer.o:	Tracer.c

Baselex.c:	Baselex.l

Baseparse.o:	Baseparse.c Vector.h

Baselex.o:	Baselex.c Baseparse.h

Vector.o:	Vector.c Vector.h

Camera.o:	Camera.c Camera.h

Color.o:	Color.c Color.h

Triangle.o:	Triangle.c Triangle.h

Sphere.o:	Sphere.c Sphere.h

Plane.o:	Plane.c Plane.h

#Timer.o:	Timer.c Timer.h

ObjectList.o: 	ObjectList.c ObjectList.h

LightList.o:    LightList.c LightList.h

Finish.o:	Finish.c Finish.h

ObjectMods.o:	ObjectMods.c ObjectMods.h

SphereOptions.o:	SphereOptions.c SphereOptions.h

Object.o:	Object.c Object.h

ObjectArray.o:	ObjectArray.c ObjectArray.h

LightArray.o:   LightArray.c LightArray.h

Parameters.o:	Parameters.c Parameters.h

Pigment.o:	Pigment.c Pigment.h

Light.o:	Light.c Light.h

World.o:	World.c World.h

Ray.o:		Ray.c Ray.h

clean:
	rm -f ${GENFILES} tracer *.o *~
