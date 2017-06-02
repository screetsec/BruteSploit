#   Copyright
#
#	Copyright (C) 2009-2013 Jason aka bofh28 <bofh28@gmail.com>
#
#   License
#	This program is free software; you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation; version 2.
# 
#	This program is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with this program; if not, write to the Free Software
#	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-13, USA
#	or see <http://www.gnu.org/licenses/gpl-2.0.html>.
#
#   Description
#
#	For standard FHS directory structure install, use command:
#	make PREFIX=/usr INSTALL_OPTIONS=geninstall

# detect Darwin = OS X enviro
UNAME_LOOKUP = $(shell uname -s)

# General variables
PACKAGE	    = crunch
VERSION	    = 3.6
PREFIX	    = /usr
DISTDIR	    = $(PACKAGE)-$(VERSION)
DISTFILES   = crunch.c crunch.1 charset.lst
BINDIR	    = $(PREFIX)/bin
LIBDIR	    = $(PREFIX)/lib/$(PACKAGE)
SHAREDIR    = $(PREFIX)/share/$(PACKAGE)
DOCDIR	    = $(PREFIX)/share/doc/$(PACKAGE)
MANDIR	    = $(PREFIX)/share/man/man1

INSTALL	    = sudo $(shell which install)
CC	    = $(shell which gcc)
LIBFLAGS    = -lm
THREADFLAGS = -pthread
OPTFLAGS    = -g -o0
LINTFLAGS   = -Wall -pedantic
CFLAGS_STD  = $(THREADFLAGS) $(LINTFLAGS) -std=c99
VCFLAGS	    = $(CFLAGS_STD) $(OPTFLAGS)
LFS	    = $(shell getconf POSIX_V6_ILP32_OFFBIG_CFLAGS)

ifeq ($(UNAME_LOOKUP),Darwin)
#Darwin = OS X, and os x does not use root root as stated in email
  INSTALL_OPTIONS = -g wheel -o root
# changing the CC flag from gcc is optional but Apple recommneds using LLVM clang compiler instad of gcc so it's a good practice to do so in an OS X enviro, alas not compulsory 
  CC = $(shell which cc)
#LFS flag HAS TO BE reset or it's a no-go :(
 LFS=""  
else
#non-mac as you were 
  INSTALL_OPTIONS = -g root -o root
endif

# Default target
all: build

build: crunch

val:	crunch.c
	@echo "Building valgrind compatible binary..."
	$(CC) $(CPPFLAGS) $(VCFLAGS) $(CFLAGS) $(LFS) $? $(LIBFLAGS) $(LDFLAGS) -o $(PACKAGE)
	@echo "valgrind --leak-check=yes crunch ..."
	@echo ""

crunch: crunch.c
	@echo "Building binary..."
	$(CC) $(CPPFLAGS) $(CFLAGS_STD) $(CFLAGS) $(LFS) $? $(LIBFLAGS) $(LDFLAGS) -o $@
	@echo ""

# Clean target
clean:
	@echo "Cleaning sources..."
	rm -f *.o $(PACKAGE) *~ START
	@echo ""

# Install generic target
install: build
	@echo "Creating directories..."
	$(INSTALL) -d $(INSTALL_OPTIONS) \
		$(DESTDIR)$(BINDIR) \
		$(DESTDIR)$(MANDIR) \
		$(DESTDIR)$(SHAREDIR) \
		$(DESTDIR)$(DOCDIR)
	@echo "Copying binary..."
	$(INSTALL) crunch $(DESTDIR)$(BINDIR)
	@echo "Copying charset.lst..."
	$(INSTALL) charset.lst $(DESTDIR)$(SHAREDIR)
	@echo "Copying COPYING..."
	$(INSTALL) COPYING $(DESTDIR)$(DOCDIR)
	@echo "Installing man page..."
	$(INSTALL) crunch.1 $(DESTDIR)$(MANDIR)
	@echo ""

# Uninstall target
uninstall:
	@echo "Deleting binary and manpages..."
	rm -rf $(BTBINDIR)/
	rm -rf $(BINDIR)/$(PACKAGE)
	rm -f $(MANDIR)/crunch.1
	@echo ""

zip: clean
	cd .. ;\
	zip -r $(DISTDIR).zip $(DISTDIR)

tarball: clean
	cd .. ;\
	tar -czf $(DISTDIR).tgz $(DISTDIR)

bzip: clean
	cd .. ;\
	tar -cjf $(DISTDIR).tar.bz2 $(DISTDIR)
