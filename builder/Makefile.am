# libguestfs virt-builder tool
# Copyright (C) 2013-2015 Red Hat Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

include $(top_srcdir)/subdir-rules.mk

AM_YFLAGS = -d

EXTRA_DIST = \
	$(SOURCES_MLI) $(SOURCES_ML) $(SOURCES_C) \
	libguestfs.gpg \
	test-index \
	test-virt-builder.sh \
	test-virt-builder-list.sh \
	test-virt-builder-planner.sh \
	test-virt-index-validate.sh \
	test-virt-index-validate-bad-1 \
	test-virt-index-validate-good-1 \
	test-virt-index-validate-good-2 \
	virt-builder.pod \
	virt-index-validate.pod

CLEANFILES = *~ *.annot *.cmi *.cmo *.cmx *.cmxa *.o virt-builder

SOURCES_MLI = \
	cache.mli \
	downloader.mli \
	get_kernel.mli \
	index_parser.mli \
	ini_reader.mli \
	languages.mli \
	list_entries.mli \
	pxzcat.mli \
	setlocale.mli \
	sigchecker.mli \
	sources.mli \
	uname.mli

SOURCES_ML = \
	utils.ml \
	pxzcat.ml \
	setlocale.ml \
	uname.ml \
	architecture.ml \
	ini_reader.ml \
	paths.ml \
	languages.ml \
	get_kernel.ml \
	cache.ml \
	sources.ml \
	downloader.ml \
	sigchecker.ml \
	index_parser.ml \
	list_entries.ml \
	cmdline.ml \
	builder.ml

SOURCES_C = \
	$(top_srcdir)/mllib/fsync-c.c \
	$(top_srcdir)/mllib/uri-c.c \
	$(top_srcdir)/mllib/mkdtemp-c.c \
	$(top_srcdir)/customize/perl_edit-c.c \
	$(top_srcdir)/customize/crypt-c.c \
	$(top_srcdir)/fish/uri.c \
	$(top_srcdir)/fish/file-edit.c \
	index-scan.c \
	index-struct.c \
	index-parse.c \
	index-parser-c.c \
	pxzcat-c.c \
	setlocale-c.c \
	uname-c.c

man_MANS =
noinst_DATA =
bin_PROGRAMS =

if HAVE_OCAML

bin_PROGRAMS += virt-builder

virt_builder_SOURCES = $(SOURCES_C)
virt_builder_CPPFLAGS = \
	-I. \
	-I$(top_builddir) \
	-I$(top_srcdir)/gnulib/lib -I$(top_builddir)/gnulib/lib \
	-I$(shell $(OCAMLC) -where) \
	-I$(top_srcdir)/gnulib/lib \
	-I$(top_srcdir)/src \
	-I$(top_srcdir)/fish
virt_builder_CFLAGS = \
	-pthread \
	$(WARN_CFLAGS) $(WERROR_CFLAGS) \
	-Wno-unused-macros \
	$(LIBLZMA_CFLAGS) \
	$(LIBTINFO_CFLAGS) \
	$(LIBXML2_CFLAGS)

BOBJECTS = \
	$(top_builddir)/mllib/libdir.cmo \
	$(top_builddir)/mllib/config.cmo \
	$(top_builddir)/mllib/common_gettext.cmo \
	$(top_builddir)/mllib/common_utils.cmo \
	$(top_builddir)/mllib/fsync.cmo \
	$(top_builddir)/mllib/planner.cmo \
	$(top_builddir)/mllib/regedit.cmo \
	$(top_builddir)/mllib/JSON.cmo \
	$(top_builddir)/mllib/uRI.cmo \
	$(top_builddir)/mllib/mkdtemp.cmo \
	$(top_builddir)/customize/customize_utils.cmo \
	$(top_builddir)/customize/urandom.cmo \
	$(top_builddir)/customize/random_seed.cmo \
	$(top_builddir)/customize/hostname.cmo \
	$(top_builddir)/customize/timezone.cmo \
	$(top_builddir)/customize/firstboot.cmo \
	$(top_builddir)/customize/perl_edit.cmo \
	$(top_builddir)/customize/crypt.cmo \
	$(top_builddir)/customize/password.cmo \
	$(top_builddir)/customize/ssh_key.cmo \
	$(top_builddir)/customize/customize_cmdline.cmo \
	$(top_builddir)/customize/customize_run.cmo \
	$(SOURCES_ML:.ml=.cmo)
XOBJECTS = $(BOBJECTS:.cmo=.cmx)

# -I $(top_builddir)/src/.libs is a hack which forces corresponding -L
# option to be passed to gcc, so we don't try linking against an
# installed copy of libguestfs.
OCAMLPACKAGES = \
	-package str,unix \
	-I $(top_builddir)/src/.libs \
	-I $(top_builddir)/gnulib/lib/.libs \
	-I $(top_builddir)/ocaml \
	-I $(top_builddir)/mllib \
	-I $(top_builddir)/customize
if HAVE_OCAML_PKG_GETTEXT
OCAMLPACKAGES += -package gettext-stub
endif

OCAMLFLAGS = $(OCAML_FLAGS) $(OCAML_WARN_ERROR)

if !HAVE_OCAMLOPT
OBJECTS = $(BOBJECTS)
BEST    = c
OCAMLLINKFLAGS = mlguestfs.cma -custom
else
OBJECTS = $(XOBJECTS)
BEST    = opt
OCAMLLINKFLAGS = mlguestfs.cmxa
endif

virt_builder_DEPENDENCIES = $(OBJECTS)
virt_builder_LINK = \
	./link.sh \
	  $(OCAMLFIND) $(BEST) $(OCAMLFLAGS) $(OCAMLPACKAGES) $(OCAMLLINKFLAGS) \
	  $(OBJECTS) -o $@

.mli.cmi:
	$(OCAMLFIND) ocamlc $(OCAMLFLAGS) $(OCAMLPACKAGES) -c $< -o $@
.ml.cmo:
	$(OCAMLFIND) ocamlc $(OCAMLFLAGS) $(OCAMLPACKAGES) -c $< -o $@
if HAVE_OCAMLOPT
.ml.cmx:
	$(OCAMLFIND) ocamlopt $(OCAMLFLAGS) $(OCAMLPACKAGES) -c $< -o $@
endif

# Manual pages and HTML files for the website.

man_MANS += virt-builder.1
noinst_DATA += $(top_builddir)/html/virt-builder.1.html

virt-builder.1 $(top_builddir)/html/virt-builder.1.html: stamp-virt-builder.pod

stamp-virt-builder.pod: virt-builder.pod $(top_srcdir)/customize/customize-synopsis.pod $(top_srcdir)/customize/customize-options.pod
	$(PODWRAPPER) \
	  --man virt-builder.1 \
	  --html $(top_builddir)/html/virt-builder.1.html \
	  --insert $(top_srcdir)/customize/customize-synopsis.pod:__CUSTOMIZE_SYNOPSIS__ \
	  --insert $(top_srcdir)/customize/customize-options.pod:__CUSTOMIZE_OPTIONS__ \
	  --license GPLv2+ \
	  $<
	touch $@

CLEANFILES += stamp-virt-builder.pod

# Tests.

TESTS_ENVIRONMENT = $(top_builddir)/run --test

disk_images := \
	$(shell for f in debian fedora ubuntu windows; do if [ -s "../tests/guests/$$f.img" ]; then echo $$f.xz; fi; done) \
	$(shell if [ -s "../tests/guests/fedora.img" ]; then echo fedora.qcow2 fedora.qcow2.xz; fi)

CLEANFILES += *.qcow2 *.xz

check_DATA = $(disk_images)

fedora.qcow2: ../tests/guests/fedora.img
	rm -f $@ $@-t
	qemu-img convert -f raw -O qcow2 $< $@-t
	mv $@-t $@

fedora.qcow2.xz: fedora.qcow2
	rm -f $@ $@-t
	xz --best -c $< > $@-t
	mv $@-t $@

%.xz: ../tests/guests/%.img
	rm -f $@ $@-t
	xz --best -c $< > $@-t
	mv $@-t $@

TESTS = \
	test-virt-builder-list.sh \
	test-virt-index-validate.sh

if ENABLE_APPLIANCE
TESTS += test-virt-builder.sh
endif ENABLE_APPLIANCE

check-valgrind:
	$(MAKE) VG="$(top_builddir)/run @VG@" check

check-slow:
	$(MAKE) TESTS="test-virt-builder-planner.sh" check

# Dependencies.
depend: .depend

.depend: $(wildcard $(abs_srcdir)/*.mli) $(wildcard $(abs_srcdir)/*.ml)
	rm -f $@ $@-t
	$(OCAMLFIND) ocamldep -I ../ocaml -I $(abs_srcdir) -I $(abs_top_builddir)/mllib -I $(abs_top_builddir)/customize $^ | \
	  $(SED) 's/ *$$//' | \
	  $(SED) -e :a -e '/ *\\$$/N; s/ *\\\n */ /; ta' | \
	  $(SED) -e 's,$(abs_srcdir)/,$(builddir)/,g' | \
	  sort > $@-t
	mv $@-t $@

-include .depend

endif

DISTCLEANFILES = .depend

.PHONY: depend docs

# virt-builder's default repository

repoconfdir = $(sysconfdir)/xdg/virt-builder/repos.d
repoconf_DATA = libguestfs.conf libguestfs.gpg

install-exec-hook:
	$(LN_S) xdg/virt-builder $(DESTDIR)$(sysconfdir)/virt-builder

# Build a small C index validator program.
bin_PROGRAMS += virt-index-validate

virt_index_validate_SOURCES = \
	index-parse.y \
	index-scan.l \
	index-struct.h \
	index-struct.c \
	index-validate.c

virt_index_validate_CPPFLAGS = \
	-DLOCALEBASEDIR=\""$(datadir)/locale"\" \
	-I. \
	-I$(top_builddir) \
	-I$(top_srcdir)/gnulib/lib -I$(top_builddir)/gnulib/lib \
	-I$(top_srcdir)/src
virt_index_validate_CFLAGS = \
	$(WARN_CFLAGS) $(WERROR_CFLAGS) \
	-Wno-unused-macros
virt_index_validate_LDADD = \
	$(LTLIBINTL) \
	../gnulib/lib/libgnu.la

man_MANS += virt-index-validate.1
noinst_DATA += $(top_builddir)/html/virt-index-validate.1.html

virt-index-validate.1 $(top_builddir)/html/virt-index-validate.1.html: stamp-virt-index-validate.pod

stamp-virt-index-validate.pod: virt-index-validate.pod
	$(PODWRAPPER) \
	  --man virt-index-validate.1 \
	  --html $(top_builddir)/html/virt-index-validate.1.html \
	  --license GPLv2+ \
	  $<
	touch $@

CLEANFILES += \
	index-parse.c \
	index-parse.h \
	index-scan.c \
	stamp-virt-index-validate.pod

if HAVE_OCAML
# Automake-generated makefile has a rule ".y.c" but lacks a rule ".y.h".
index-parse.h: index-parse.y
	touch $(srcdir)/index-parse.y
	$(MAKE) index-parse.c
# Also it doesn't generate dependencies for the C files that include
# index-parse.h.
index-parser-c.c index-scan.c index-validate.c: index-parse.h
endif

# Apparently there's no clean way with Automake to not have them
# in the distribution, so just remove them from the distdir.
dist-hook:
	rm -f $(distdir)/index-parse.c $(distdir)/index-parse.h $(distdir)/index-scan.c
