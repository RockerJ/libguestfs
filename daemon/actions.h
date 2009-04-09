/* libguestfs generated file
 * WARNING: THIS FILE IS GENERATED BY 'src/generator.ml'.
 * ANY CHANGES YOU MAKE TO THIS FILE WILL BE LOST.
 *
 * Copyright (C) 2009 Red Hat Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "../src/guestfs_protocol.h"

extern int do_mount (const char *device, const char *mountpoint);
extern int do_sync (void);
extern int do_touch (const char *path);
extern char *do_cat (const char *path);
extern char *do_ll (const char *directory);
extern char **do_ls (const char *directory);
extern char **do_list_devices (void);
extern char **do_list_partitions (void);
extern char **do_pvs (void);
extern char **do_vgs (void);
extern char **do_lvs (void);
extern guestfs_lvm_int_pv_list *do_pvs_full (void);
extern guestfs_lvm_int_vg_list *do_vgs_full (void);
extern guestfs_lvm_int_lv_list *do_lvs_full (void);
extern char **do_read_lines (const char *path);
extern int do_aug_init (const char *root, int flags);
extern int do_aug_close (void);
extern int do_aug_defvar (const char *name, const char *expr);
extern guestfs_aug_defnode_ret *do_aug_defnode (const char *name, const char *expr, const char *val);
extern char *do_aug_get (const char *path);
extern int do_aug_set (const char *path, const char *val);
extern int do_aug_insert (const char *path, const char *label, int before);
extern int do_aug_rm (const char *path);
extern int do_aug_mv (const char *src, const char *dest);
extern char **do_aug_match (const char *path);
extern int do_aug_save (void);
extern int do_aug_load (void);
extern char **do_aug_ls (const char *path);
