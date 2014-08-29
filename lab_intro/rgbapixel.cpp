#include <cstdint>

#include "rgbapixel.h"
//constructor
RGBAPixel::RGBAPixel(){
	alpha = 255;
	red = 255;
	green = 255;
	blue = 255;

}
RGBAPixel::RGBAPixel(uint8_t red, uint8_t green, uint8_t blue){
	red = red;
	green = green;
	blue = blue;
	alpha = 255;

}
