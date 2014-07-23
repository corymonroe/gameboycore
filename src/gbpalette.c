

#include "gbpalette.h"

//		{ 255, 255, 255, 255 },
//		{ 192, 192, 192, 255 },
//		{  96,  96,  96, 255 },
//		{   0,   0,   0, 255 }

void paletteInitDefault(GBPalette* p)
{
	GBColor c0 = { 255, 255, 255, 255 };
	GBColor c1 = { 192, 192, 192, 255 };
	GBColor c2 = {  96,  96,  96, 255 };
	GBColor c3 = {   0,   0,   0, 255 };

	p->colors[0] = c0;
	p->colors[1] = c1;
	p->colors[2] = c2;
	p->colors[3] = c3;
}
