// kX Driver / kX Driver Interface / kX Driver Effects Library
// Copyright (c) Max Mikhailov and Eugene Gavrilov, 2001-2005.
// All rights reserved

/*
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

// 10kX microcode
// Patch name: 'delay_b'

const char *delay_a_copyright="(c) Max Mikhailov, 2003-2005";
const char *delay_a_engine="";
const char *delay_a_comment="stereo->stereo panning delay";
const char *delay_a_created="";
const char *delay_a_guid="80100006-0999-11D6-BFBC-D4F706E10C52";

const char *delay_a_name="Delay A";
int delay_a_itramsize=0,delay_a_xtramsize=64004;

dsp_register_info delay_a_info[]={
	{ "in1",0x4000,0x7,0xffff,0x0 },
	{ "in2",0x4001,0x7,0xffff,0x0 },
	{ "out1",0x8000,0x8,0xffff,0x0 },
	{ "out2",0x8001,0x8,0xffff,0x0 },
	{ "dry",0x8002,0x4,0xffff,0x7fffffff },
	{ "wet",0x8003,0x4,0xffff,0x547ae147 },
	{ "feedback",0x8004,0x4,0xffff,0x3fffffff },
	{ "time1",0x8005,0x4,0xffff,0x5fffffff },
	{ "time2",0x8006,0x4,0xffff,0x4ccccccc },
	{ "xfeed",0x8007,0x4,0xffff,0x5fffffff },
	{ "maxdlysize",0x8008,0x1,0xffff,0x3e80000 },
	{ "w",0x8009,0x3,0xffff,0x0 },
	{ "v",0x800a,0x3,0xffff,0x0 },
	{ "d1",0x800b,0x4a,0xffff,0x0 },
	{ "&d1",0x800c,0xb,0xffff,0x0 },
	{ "d1r",0x800d,0x2a,0xffff,0x7d00 },
	{ "&d1r",0x800e,0xb,0xffff,0x7d00 },
	{ "d2",0x800f,0x4a,0xffff,0x7d02 },
	{ "&d2",0x8010,0xb,0xffff,0x7d02 },
	{ "d2r",0x8011,0x2a,0xffff,0xfa02 },
	{ "&d2r",0x8012,0xb,0xffff,0xfa02 },
};

dsp_code delay_a_code[]={
	{ 0x0,0x8009,0x4000,0x800d,0x8004 },
	{ 0x0,0x800a,0x4001,0x8011,0x8004 },
	{ 0xe,0x800b,0x8009,0x8007,0x800a },
	{ 0xe,0x800f,0x800a,0x8007,0x8009 },
	{ 0x0,0x2040,0x2040,0x800d,0x8003 },
	{ 0x0,0x8000,0x2056,0x4000,0x8002 },
	{ 0x0,0x2040,0x2040,0x8011,0x8003 },
	{ 0x0,0x8001,0x2056,0x4001,0x8002 },
	{ 0x0,0x800e,0x800c,0x8008,0x8005 },
	{ 0x0,0x8012,0x8010,0x8008,0x8006 },
};

