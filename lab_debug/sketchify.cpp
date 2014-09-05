#include <cstdlib>
#include "png.h"

//
// sets up the output image
PNG * setupOutput(int w, int h)
{
	PNG * image = new PNG(w, h);
	return image;
}


// Returns my favorite color
RGBAPixel * myFavoriteColor(int intensity)
{
	RGBAPixel color;
	color.red   = 0;
	color.green = intensity/2;
	color.blue  = intensity;
	RGBAPixel * c = new RGBAPixel(color);
	return c;
}


void sketchify()
{
	// Load in.png
	PNG * original;

	//std::cout << "Reached line 28" << endl;	
	original = new PNG();
	original->readFromFile("in.png");
	int width  = original->width();
	int height = original->height();
	//std::cout << "Reached line 32" << endl;

	// Create out.png
	PNG * output = setupOutput(width, height);	

	// Loud our favorite color to color the outline
	RGBAPixel * myPixel = myFavoriteColor(192);

	// Go over the whole image, and if a pixel differs from that to its upper
	// left, color it my favorite color in the output
	for (int y = 1; y < height; y++)
	{
		//std::cout << "begin" << endl;
		for (int x = 1; x < width; x++)
		{
			// Calculate the pixel difference
			RGBAPixel * prev = (*original)(x-1, y-1);
			RGBAPixel * curr = (*original)(x  , y  );
			int diff = abs(curr->red   - prev->red  ) +
					   abs(curr->green - prev->green) +
					   abs(curr->blue  - prev->blue );

			// If the pixel is an edge pixel,
			// color the output pixel with my favorite color
			RGBAPixel * currOutPixel =(*output)(x,y);

			if (diff > 100)
				*currOutPixel = *myPixel;
				//*(*output)(x,y) = *myPixel;
			
		}
		//std::cout << "end" << endl;
	}
	
	// Save the output file
	//std::cout << "begin" << endl;
	output->writeToFile("out.png");
	//std::cout << "end" << endl;

	// Clean up memory
	delete myPixel;
	//std::cout << "check1" << endl;
	delete output;
	delete original;
	//std::cout << "check2" << endl;
}
