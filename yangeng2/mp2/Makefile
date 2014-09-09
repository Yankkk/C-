
CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : testimage testscene

testimage : testimage.o image.o rgbapixel.o png.o
	$(LD) testimage.o image.o rgbapixel.o png.o $(LDFLAGS) -o testimage

testscene : testscene.o scene.o image.o rgbapixel.o png.o
	$(LD) testscene.o scene.o image.o rgbapixel.o png.o $(LDFLAGS) -o testscene

testscene.o : testscene.cpp scene.h image.h
	$(CXX) $(CXXFLAGS) testscene.cpp

scene.o : scene.cpp scene.h
	$(CXX) $(CXXFLAGS) scene.cpp

testimage.o : testimage.cpp image.h
	$(CXX) $(CXXFLAGS) testimage.cpp

image.o : image.cpp image.h
	$(CXX) $(CXXFLAGS) image.cpp

png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp


 
clean : 
	-rm -f *.o testimage testscene

