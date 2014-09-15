#include <iostream>
#include "scene.h"
#include "rgbapixel.h"
#include "png.h"
#include "image.h"

using namespace std;

/**
* Constructor create a Image array of max images
*/

Scene::Scene(int max)
{
    num = max;
    xx = new int[max];
    yy = new int[max];
    myImage = new Image*[max];
    for(int i = 0; i < max; i++)
    {
	myImage[i] = NULL;
    }
    
}

/**
* This function copy the given scene
*/

void Scene::clean()
{
    delete [] xx;
    delete [] yy;

    if(myImage != NULL){
	for(int i = 0; i < num; i ++){
	    delete myImage[i];
        }
    }
    delete [] myImage;
}

/**
* This function clean the Scene
*/
Scene::~Scene()
{
    clean();

}

/**
* Copy source
*/
void Scene::copy(const Scene & source)
{
    num = source.num;
    myImage = new Image * [num];
    xx = new int[num];
    yy = new int[num];

    for(int i = 0; i < num; i ++){
	
    
        if(source.myImage[i] != NULL){
	    myImage[i] = new Image(* (source.myImage[i]));
	    xx[i] = source.xx[i];
            yy[i] = source.yy[i];
	}
        else{
	    myImage[i] = NULL;
	}
    }
}

/**
* Constructor that create Scene same as source
*/
Scene::Scene(const Scene & source)
{
    copy(source);
}

/**
* Scene operator
*/
const Scene & Scene::operator= (const Scene & source)
{
    if(this != &source){
	clean();
	copy(source);
    }

    return *this;

}

/**
* Modify the size of the array of Image pointers without changing their indices
*/
void Scene::changemaxlayers(int newmax)
{
    
    if(num > newmax){
	for(int j = newmax; j < num; j++){
	    if(myImage[j] != NULL){
		cout<< "invalid newmax" << endl;
		return;
	    }
	}
    }
    Image ** n = new Image * [newmax];
    int * newxx = new int[newmax];
    int * newyy = new int[newmax];

    if(num >= newmax){
	for(int i = 0; i < newmax; i ++){
                if(myImage[i] != NULL){
	            n[i] = myImage[i];
		    newxx[i] = xx[i];
		    newyy[i] = yy[i];
	        }
		else{
		    n[i] = NULL;
		}
        }
    }
    else if(num < newmax){
	for(int i = 0; i < num; i++){
	    if(myImage[i] != NULL){
	        n[i]=myImage[i];
	        newxx[i] = xx[i];
	        newyy[i] = yy[i];
	    }
	    else{
		    n[i] = NULL;
		}
	}
	for(int j = num; j < newmax; j++){
	    n[j] = NULL;
	   
	}
    }

    num = newmax;
    delete [] myImage;
    myImage = n;
    delete [] xx;
    delete [] yy;
    xx = newxx;
    yy = newyy;


}

/**
* This function add a picture to the Scene, and places the picture in the given index
*/
void Scene::addpicture(const char * FileName, int index, int x, int y)
{
    if(index >= num || index < 0){
	cout << "index out of bounds" << endl;
	return;
    }
    if(myImage[index] != NULL){
	delete myImage[index];
    }
    xx[index] = x;
    yy[index] = y;
    
    myImage[index] = new Image();
    myImage[index] -> readFromFile(FileName);

}

/**
* This function moves an Image from one layer to another
*/
void Scene::changelayer(int index, int newindex)
{
    if(index == newindex)
    {
	return;
    }
    if(index < 0 || index >= num || newindex < 0 || newindex >= num){
	cout << "invalid index" << endl;
	return;
    }
    if(myImage[newindex] != NULL){
	delete myImage[newindex];
    }
    myImage[newindex] = myImage[index];
    xx[newindex] = xx[index];
    yy[newindex] = yy[index];
    myImage[index] = NULL;
}

/**
* This function change the x and y coordinates of the Image in the specified layer
*/
void Scene::translate(int index, int xcoord, int ycoord)
{
    if(index < 0 || index >= num ){
	cout << "invalid index" << endl;
	return;
    }
    if(myImage[index] == NULL){
	cout << "invalid index" << endl;
	return;
    }

    xx[index] = xcoord;
    yy[index] = ycoord;
}

/**
* This function delete the Image at the given index
*/
void Scene::deletepicture(int index)
{
    if(index < 0 || index >= num){
	cout << "invalid index" << endl;
	return;
    }
    if(myImage[index] == NULL){
	cout << "invalid index" << endl;
	return;
    }

    delete myImage[index];
    myImage[index] = NULL;
}

/**
* This function return a pointer to the Image at the specified index
*/
Image * Scene::getpicture(int index) const
{
    if(index < 0 || index >= num){
	cout << "invalid index" << endl;
	return NULL;
    }
    Image * p = myImage[index];
    return p;

}

/**
* This function draws the whole scene on one Image and returns that Image by value
*/
Image Scene::drawscene() const
{
    size_t w = 0;
    size_t h = 0;
    
//Calculate the width and height of the new image
    for(int i = 0 ; i < num; i++){
	if(myImage[i] != NULL){
	    size_t wid = myImage[i] -> width();
	    size_t hei = myImage[i] -> height();
	    if(wid + xx[i] > w){
		w = wid + xx[i];
	    }
	    if(hei + yy[i] > h){
		h = hei + yy[i];
	    }
	}
    }

//change the size of image to w,h
    Image image;
    image.resize(w, h);

//put the images into one Image with given position
    for(int j = 0; j < num; j++){
	if(myImage[j] != NULL){
	for(size_t k = 0; k < myImage[j] -> width(); k++){
	    for(size_t i = 0; i < myImage[j] -> height(); i++){
		RGBAPixel * r = (*myImage[j])(k, i);
		*image(k + xx[j], i + yy[j]) = *r;
	    }
	}
	}

    }


    return image;
}


