/*************************************************************************\
|  File: Finish.c                                                         |
|                                                                         |
|  Implements an abstract datatype for finish used by bison parser        |
|                                                                         |
\*************************************************************************/

#include "Finish.h"
#include "Scalar.h"

Finish Finish_create( scalar diffuse, scalar reflection )
{
    Finish f;

    f.diffuse = diffuse;
    f.reflection = reflection;

    return f;
}

scalar Finish_diffuse( Finish fi )
{
    return fi.diffuse;
}

scalar Finish_reflection( Finish fi )
{
    return fi.reflection;
}

