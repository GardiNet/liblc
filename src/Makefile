#---------------------------------------------------------------------------
# Author: Cedric Adjih, Hana Baccouch
#---------------------------------------------------------------------------
# Copyright 2015-2017 Inria
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
# LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#---------------------------------------------------------------------------

-include Makefile.local

CONFIG_FILE=config-default.h

#--------------------------------------------------

CFLAGS += -Wall -g3 -fPIC -DCONFIG_FILE=${CONFIG_FILE}

#------------------------------

SRCS =  general.c linear-code.c coded-packet.c packet-set.c

HEADERS = $(SRCS:.c=.h)

OBJS = $(SRCS:.c=.o)

#------------------------------

#---------------------------------------------------------------------------
# Main targets
#---------------------------------------------------------------------------

all: liblc.a

#---------------------------------------------------------------------------
# Dependencies
# http://stackoverflow.com/questions/97338/gcc-dependency-generation-for-a-different-output-directory
#---------------------------------------------------------------------------

DEPS = $(SRCS:.c=.d)

-include $(DEPS)

%.d : %.c %.h
	$(CC) $(CCFLAGS) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(<:.c=.o)" "$<"

#---------------------------------------------------------------------------
# Library
#---------------------------------------------------------------------------

liblc.a: ${OBJS}
	${AR} cru $@ ${OBJS}

#---------------------------------------------------------------------------
# Testing
#---------------------------------------------------------------------------

test-coded-packet: test-coded-packet.o liblc.a
	${CC} ${CFLAGS} -o $@ $< -llc -L.

#---------------------------------------------------------------------------
# Documentation
#---------------------------------------------------------------------------

doc:
	doxygen Doxyfile

#---------------------------------------------------------------------------
# Cleaning
#---------------------------------------------------------------------------

clean:
	rm -f *.a *.so *.o *.d *~
	rm -f test-coded-packet

really-clean: clean

#---------------------------------------------------------------------------
