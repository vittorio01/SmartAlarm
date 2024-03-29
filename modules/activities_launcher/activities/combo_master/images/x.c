/* Copyright (c) 2012, Texas Instruments Incorporated
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

*  Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

*  Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

*  Neither the name of Texas Instruments Incorporated nor the names of
   its contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/


#include "grlib.h"

static const unsigned char pixel_x1BPP_UNCOMP[] =
{
0x00, 0x00, 0x00, 
0x38, 0x00, 0x1c, 
0x7c, 0x00, 0x3e, 
0x7e, 0x00, 0x7e, 
0x7f, 0x00, 0xfe, 
0x3f, 0x81, 0xfc, 
0x1f, 0xc3, 0xf8, 
0x0f, 0xe7, 0xf0, 
0x07, 0xff, 0xe0, 
0x03, 0xff, 0xc0, 
0x01, 0xff, 0x80, 
0x00, 0xff, 0x00, 
0x00, 0xff, 0x00, 
0x01, 0xff, 0x80, 
0x03, 0xff, 0xc0, 
0x07, 0xff, 0xe0, 
0x0f, 0xe7, 0xf0, 
0x1f, 0xc3, 0xf8, 
0x3f, 0x81, 0xfc, 
0x7f, 0x00, 0xfe, 
0x7e, 0x00, 0x7e, 
0x7c, 0x00, 0x3e, 
0x38, 0x00, 0x1c, 
0x00, 0x00, 0x00
};

static const unsigned long palette_x1BPP_UNCOMP[]=
{
	0x000000, 	0xffffff
};

const tImage  x1BPP_UNCOMP=
{
	IMAGE_FMT_1BPP_UNCOMP,
	24,
	24,
	2,
	palette_x1BPP_UNCOMP,
	pixel_x1BPP_UNCOMP,
};

