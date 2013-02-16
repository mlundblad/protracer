#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.59])
AC_INIT([protracer], [3.3], [ml@update.uu.se])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.10 dist-bzip2 no-dist-gzip])

m4_include([m4/ax_cxx_compile_stdcxx_11.m4])

# Checks for programs.
AC_PROG_YACC
AC_PROG_CXX
AC_PROG_LEX
AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11

# check for thread support
AC_ARG_ENABLE([threads],
    AS_HELP_STRING([--disable-threads], [Disable threads (default: enabled)]),
    ,
    enable_threads=yes)

AS_IF([test "x$enable_threads" != "xno"], [
  AC_CHECK_LIB([pthread], [pthread_create],
	       [AC_SUBST(AM_CXXFLAGS,-pthread)
		AC_DEFINE(USE_THREADS, 1, [Use multithreading])],
		[enable_threads=no])
])

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lfl':
AC_CHECK_LIB([fl], [main])
# FIXME: Replace `main' with a function in `-lm':
AC_CHECK_LIB([m], [main])

# check for Magick++
PKG_CHECK_MODULES(PROTRACER, Magick++)

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for library functions.
AC_CHECK_FUNCS([sqrt strdup strtol])

AC_CONFIG_FILES([Makefile
		data/Makefile
		src/Makefile
		win32/Makefile])
AC_OUTPUT

echo "

Configuration:
	Thread support: $enable_threads
"
