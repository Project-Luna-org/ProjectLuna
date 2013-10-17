


#include <SDL.h>
#include <math.h>
#include "../utils/SDLgraph.h"
#include "shared.h"


typedef union
{
	Uint32 PIXEL;
	struct 
	{
        Uint8 nz, ny, nx, m;
	};
} NORMAL_PIXEL;


void gfxRawToNMap( Uint32* inputMap, NORMAL_PIXEL* outputMap, Uint32 width, Uint32 height )
{
    float scale = 1.0f;
    float sqlen, reciplen, nx, ny, nz;
    float c, cx, cy, dcx, dcy;
    const float oneOver255 = 1.0f/255.0f;

    for (Uint32 i=0; i<height; ++i)
    {
        for (Uint32 j=0; j<width; ++j) 
        {
            Uint32 src;

            src = inputMap[ i*width + j ];
            c = ((src>>8)&0xFF) * oneOver255;

            src = inputMap[ i*width + (j+1)%width];
            cx = ((src>>8)&0xFF) * oneOver255;

            src = inputMap[((i+1)%height)*width + j];
            cy = ((src>>8)&0xFF) * oneOver255;

            dcx = scale * (c - cx);
            dcy = scale * (c - cy);

            sqlen = dcx*dcx + dcy*dcy + 1;
            reciplen = 1.0f/sqrtf(sqlen);

            nx = dcy*reciplen;
            ny = -dcx*reciplen;
            nz = reciplen;

            outputMap[i*width+j].nx = (Uint8)(128 + 127*nx);
            outputMap[i*width+j].ny = (Uint8)(128 + 127*ny);
            outputMap[i*width+j].nz = (Uint8)(128 + 127*nz);
            outputMap[i*width+j].m  = 255;
        }
    }
}



SDL_Surface* calculateNormalMap(SDL_Surface* image)
{

    image=SDL_ConvertSurfaceFormat(image,SDL_PIXELFORMAT_ARGB8888,0);
	
	SDL_Surface* img = SDL_CreateRGBSurface(0, image->w, image->h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	NORMAL_PIXEL* normalMapRAW = new NORMAL_PIXEL[image->w*image->h];


	gfxRawToNMap((Uint32*)image->pixels,normalMapRAW,image->w,image->h);

	for (int y=0;y<image->h;y++)
		for (int x=0;x<image->w;x++)
		{
			Uint32 color = normalMapRAW[y*image->w+x].PIXEL;

			putpixel32(img,x,y,color);
		}


	delete [] normalMapRAW;

	return img;
}