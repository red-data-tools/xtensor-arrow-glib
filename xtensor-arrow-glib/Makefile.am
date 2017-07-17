# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

CLEANFILES =

EXTRA_DIST =

AM_CPPFLAGS =					\
	-I$(top_builddir)			\
	-I$(top_srcdir)

AM_CFLAGS =					\
	$(GLIB_CFLAGS)				\
	$(XTENSOR_CFLAGS)			\
	$(ARROW_GLIB_CFLAGS)			\
	$(XTENSOR_ARROW_GLIB_CFLAGS)

lib_LTLIBRARIES =				\
	libxtensor-arrow-glib.la

libxtensor_arrow_glib_la_CXXFLAGS =		\
	$(GLIB_CFLAGS)				\
	$(XTENSOR_CFLAGS)			\
	$(ARROW_GLIB_CFLAGS)			\
	$(XTENSOR_ARROW_GLIB_CXXFLAGS)

libxtensor_arrow_glib_la_LDFLAGS =		\
	-version-info $(LT_VERSION_INFO)	\
	-no-undefined

libxtensor_arrow_glib_la_LIBADD =		\
	$(GLIB_LIBS)				\
	$(XTENSOR_LIBS)				\
	$(ARROW_GLIB_LIBS)

libxtensor_arrow_glib_la_headers =		\
	double-array.h				\
	xtensor-arrow-glib.h

libxtensor_arrow_glib_la_sources =		\
	double-array.cpp			\
	$(libxtensor_arrow_glib_la_headers)

libxtensor_arrow_glib_la_cpp_headers =		\
	double-array.hpp			\
	xtensor-arrow-glib.hpp

libxtensor_arrow_glib_la_SOURCES =			\
	$(libxtensor_arrow_glib_la_sources)		\
	$(libxtensor_arrow_glib_la_cpp_headers)

xtensor_arrow_glib_includedir = $(includedir)/xtensor-arrow-glib
xtensor_arrow_glib_include_HEADERS =			\
	$(libxtensor_arrow_glib_la_headers)		\
	$(libxtensor_arrow_glib_la_cpp_headers)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA =				\
	xtensor-arrow-glib.pc

# GObject Introspection
-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS =
INTROSPECTION_COMPILER_ARGS =

if HAVE_INTROSPECTION
XtensorArrow-1.0.gir: libxtensor-arrow-glib.la
XtensorArrow_1_0_gir_PACKAGES =			\
	arrow-glib
XtensorArrow_1_0_gir_EXPORT_PACKAGES = XtensorArrow
XtensorArrow_1_0_gir_INCLUDES =			\
	Arrow-1.0
XtensorArrow_1_0_gir_CFLAGS =			\
	$(AM_CPPFLAGS)
XtensorArrow_1_0_gir_LIBS = libxtensor-arrow-glib.la
XtensorArrow_1_0_gir_FILES = $(libxtensor_arrow_glib_la_sources)
XtensorArrow_1_0_gir_SCANNERFLAGS =		\
	--warn-all				\
	--identifier-prefix=GXtArrow		\
	--symbol-prefix=gxt_arrow
INTROSPECTION_GIRS += XtensorArrow-1.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES +=					\
	$(gir_DATA)				\
	$(typelib_DATA)
endif
