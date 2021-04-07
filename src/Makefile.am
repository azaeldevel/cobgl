

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = gl

gl_SOURCES = main.cc core.cc shader.cpp
gl_CXXFLAGS = $(GL_CFLAGS)
gl_LDADD = $(GL_LIBS)


