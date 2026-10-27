#
#   This file is part of the MLV Library.
#
#   Copyright (C) 2010 Adrien Boussicault, Marc Zipstein
#
#
#    This library is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this Library.  If not, see <http://www.gnu.org/licenses/>.
#

lt_ECHO = @lt_ECHO@
SED = /usr/bin/sed
top_srcdir=../..
top_builddir=../..
SHELL = /bin/bash
LIBTOOL = $(SHELL) $(top_builddir)/libtool
CC= $(LIBTOOL) --tag=CC --mode=link gcc
CXX= $(LIBTOOL) --tag=CXX --mode=link g++
CPPFLAGS=-I${top_srcdir}
CFLAGS= -g -O2 -Wall -Werror
CXXFLAGS= -g -O2 -Wall -Werror
LDLIBS=${top_builddir}/MLV/libMLV.la

all:
	$(SED) -e "s# # #" ./README

clean:
	if test "" != "`find ./ -name "*.libs"`"; then for d in `find ./ -name "*.libs"`; do for i in `ls "$$d"`; do if test -a $$d/$$i; then j=`$(lt_ECHO) "$$d/$$i" | $(SED) -e "s#\.libs/##"`; rm -f -- $$j; fi; done; rm -rf $$d; done; fi

.phony: all clean
