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

AC_PREREQ(2.65)

AC_INIT([xtensor-arrow-glib], [1.0.0])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_SRCDIR([xtensor-arrow-glib/xtensor-arrow-glib.h])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.13 foreign])
AM_SILENT_RULES([yes])

AC_PROG_CC
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11([ext], [mandatory])
LT_INIT

LT_CURRENT=1
LT_REVISION=0
LT_AGE=0
LT_VERSION_INFO="\$(LT_CURRENT):\$(LT_REVISION):\$(LT_AGE)"
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)
AC_SUBST(LT_VERSION_INFO)

XTENSOR_ARROW_GLIB_CFLAGS="-Wall"
XTENSOR_ARROW_GLIB_CXXFLAGS="-Wall"
AC_ARG_ENABLE(debug,
  [AS_HELP_STRING([--enable-debug],
                  [Use debug flags (default=no)])],
  [XTENSOR_ARROW_GLIB_DEBUG="$enableval"],
  [XTENSOR_ARROW_GLIB_DEBUG="no"])
if test "x$XTENSOR_ARROW_GLIB_DEBUG" != "xno"; then
  XTENSOR_ARROW_GLIB_DEBUG="yes"
  if test "$CLANG" = "yes"; then
    CFLAGS="$CFLAGS -O0 -g"
    CXXFLAGS="$CXXFLAGS -O0 -g"
  elif test "$GCC" = "yes"; then
    CFLAGS="$CFLAGS -O0 -g3"
    CXXFLAGS="$CXXFLAGS -O0 -g3"
  fi
fi
AC_SUBST(XTENSOR_ARROW_GLIB_CFLAGS)
AC_SUBST(XTENSOR_ARROW_GLIB_CXXFLAGS)

AM_PATH_GLIB_2_0([2.32.4], [], [], [gobject])

GOBJECT_INTROSPECTION_REQUIRE([1.32.1])
GTK_DOC_CHECK([1.18-2])

PKG_CHECK_MODULES([XTENSOR], [xtensor])
PKG_CHECK_MODULES([ARROW_GLIB], [arrow-glib])

AC_CONFIG_FILES([
  Makefile
  xtensor-arrow-glib/Makefile
  xtensor-arrow-glib/xtensor-arrow-glib.pc
  doc/Makefile
  doc/reference/Makefile
])

AC_OUTPUT
