#include <cstdint>

#include "rgbapixel.h"

//constructor
RGBAPixel::RGBAPixel(){
	alpha = 255;
	red = 255;
	green = 255;
	blue = 255;
}
RGBAPixel::RGBAPixel(uint8_t r, uint8_t g, uint8_t b){
	red = r;
	green = g;
	blue = b;
	alpha = 255;

}
