#include "grlib.h"

static const unsigned char pixel_CURSOR_DOWN1BPP_UNCOMP[] =
{
0x0e, 0x00, 
0x0e, 0x00, 
0x0e, 0x00, 
0x0e, 0x00, 
0x0e, 0x00, 
0xe0, 0xe0, 
0x7f, 0xc0, 
0x3f, 0x80, 
0x1f, 0x00, 
0x0e, 0x00, 
0x04, 0x04
};

static const unsigned long palette_CURSOR_DOWN1BPP_UNCOMP[]=
{
	0x000000, 	0xffffff
};

const tImage  CURSOR_DOWN1BPP_UNCOMP=
{
	IMAGE_FMT_1BPP_UNCOMP,
	11,
	11,
	2,
	palette_CURSOR_DOWN1BPP_UNCOMP,
	pixel_CURSOR_DOWN1BPP_UNCOMP,
};

