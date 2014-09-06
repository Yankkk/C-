
CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : testimage 

testimage : testimage.o image.o rgbapixel.o png.o
	$(LD) testimage.o image.o rgbapixel.o png.o $(LDFLAGS) -o testimage



testimage.o : testimage.cpp image.h
	$(CXX) $(CXXFLAGS) testimage.cpp

image.o : image.cpp image.h
	$(CXX) $(CXXFLAGS) image.cpp

main.o : main.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) main.cpp

png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp


 
clean : 
	-rm -f *.o testimage

