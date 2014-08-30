
#include <iostream>

#include "rgbapixel.h"
#include "png.h"

using namespace std;

/**
 * This function rotate the input PNG object by 180 degrees.
 *
 *
 *
 */
int main() {

	PNG input("in.png");
	size_t x = input.width();
	size_t y = input.height();
	
	PNG output(x,y);

	for(size_t xi = 0; xi<x; xi++){
		for(size_t yi = 0; yi<y; yi++){
			output(x-1-xi, y-yi-1) ->red = (input(xi,yi) ->red);
			output(x-1-xi, y-yi-1) ->green = (input(xi,yi) ->green);
			output(x-1-xi, y-yi-1) ->blue = (input(xi,yi) ->blue);
			output(x-1-xi, y-yi-1) ->alpha = (input(xi,yi) ->alpha);
		}
	}

	output.writeToFile("out.png");

	

}

