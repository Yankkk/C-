#include <cstdint>
#include "image.h"

using namespace std;

/**
* This function flip the image.
*/
void Image::flipleft()
{
    for(size_t i = 0; i < width()/2; i ++)
    {
	for(size_t j = 0; j < height(); j++)
	{
	    RGBAPixel* x = PNG::operator()(i, j);
	    RGBAPixel* y = PNG::operator()(width()-1-i, j);
	    RGBAPixel temp = *x;
	    *x = *y;
	    *y = temp;
	    
	}
    }
}

/**
* This function change the brightness by given amount.
*/
void Image::adjustbrightness(int r, int g, int b)
{
    for(size_t i = 0; i < width(); i++ )
    {
	for(size_t j = 0; j < height(); j++)
	{
	    RGBAPixel* x = PNG::operator()(i, j);
	    int r2 = x ->red;
	    int g2 = x ->green; 
	    int b2 = x ->blue;

	    r2 = r2+r;
	    g2 = g2+g;
	    b2 = b2+b;

	    if(r2>255){
		r2 = 255;
	    }
	  
	    if(g2>255){
		g2 = 255;
	    }

	    if(b2>255){
		b2 = 255;
	    }

	    if(r2<0){
		r2 = 0;
	    }

	    if(g2<0){
		g2 = 0;
	    }

	    if(b2<0){
		b2 = 0;
	    }
	    
	    x->red = r2;
	    x->green = g2;
	    x->blue = b2;

	}
    }
}

/**
* This function invert the colors of image.
*/
void Image::invertcolors()
{
    for(size_t i = 0; i < width(); i++)
    {
	for(size_t j = 0; j < height(); j++)
	{
	    RGBAPixel* x = PNG::operator()(i, j);
	    x -> red = 255 - x-> red;
	    x -> green = 255 - x-> green;
	    x -> blue = 255 - x -> blue;

	}
    }

}
