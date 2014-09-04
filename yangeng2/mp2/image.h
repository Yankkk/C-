#ifndef IMAGE_H
#define IMAGE_H

#include "png.h"

class Image : public PNG
{
    public:

	//Image const & operator =(Image const & other);

        void flipleft();

        void adjustbrightness(int r, int g, int b);

	void invertcolors();

};
#endif
