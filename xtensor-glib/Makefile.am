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
	$(GXTENSOR_CFLAGS)

lib_LTLIBRARIES =				\
	libxtensor-glib.la

libxtensor_glib_la_CXXFLAGS =			\
	$(GLIB_CFLAGS)				\
	$(XTENSOR_CFLAGS)			\
	$(GXTENSOR_CXXFLAGS)

libxtensor_glib_la_LDFLAGS =			\
	-version-info $(LT_VERSION_INFO)	\
	-no-undefined

libxtensor_glib_la_LIBADD =			\
	$(GLIB_LIBS)				\
	$(XTENSOR_LIBS)				\
	$(GARROW_LIBS)

libxtensor_glib_la_headers =			\
	double-array.h				\
	xtensor-glib.h

libxtensor_glib_la_sources =			\
	double-array.cpp			\
	$(libxtensor_glib_la_headers)

libxtensor_glib_la_cpp_headers =		\
	double-array.hpp			\
	xtensor-glib.hpp

libxtensor_glib_la_SOURCES =			\
	$(libxtensor_glib_la_sources)		\
	$(libxtensor_glib_la_cpp_headers)

xtensor_glib_includedir = $(includedir)/xtensor-glib
xtensor_glib_include_HEADERS =			\
	$(libxtensor_glib_la_headers)		\
	$(libxtensor_glib_la_cpp_headers)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA =				\
	xtensor-glib.pc

# GObject Introspection
-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS =
INTROSPECTION_COMPILER_ARGS =

if HAVE_INTROSPECTION
xtensor-1.0.gir: libxtensor-glib.la
xtensor_1_0_gir_PACKAGES =			\
	gobject-2.0
xtensor_1_0_gir_EXPORT_PACKAGES = xtensor
xtensor_1_0_gir_INCLUDES =			\
	GObject-2.0
xtensor_1_0_gir_CFLAGS =			\
	$(AM_CPPFLAGS)
xtensor_1_0_gir_LIBS = libxtensor-glib.la
xtensor_1_0_gir_FILES = $(libxtensor_glib_la_sources)
xtensor_1_0_gir_SCANNERFLAGS =			\
	--warn-all				\
	--identifier-prefix=GXt			\
	--symbol-prefix=gxt
INTROSPECTION_GIRS += xtensor-1.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES +=					\
	$(gir_DATA)				\
	$(typelib_DATA)
endif
