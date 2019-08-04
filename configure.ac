AC_INIT([drumkit], [0.1], [jonadev95@posteo.org])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_PROG_CXXCPP
AC_PROG_CXX

AC_LANG([C++])
AC_TYPE_SIZE_T

PKG_CHECK_MODULES([PORTAUDIO_DEP], [portaudio-2.0])

AC_PROG_CC
AC_CONFIG_FILES([
 Makefile
 src/Makefile
])
AX_CXX_COMPILE_STDCXX_11(noext,mandatory)
AC_OUTPUT
