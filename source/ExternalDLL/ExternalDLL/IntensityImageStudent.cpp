#include "IntensityImageStudent.h"

IntensityImageStudent::IntensityImageStudent() : IntensityImage() {
	//TODO: Nothing
	pixelList = new int[1];
	nPixels = 0;
}

IntensityImageStudent::IntensityImageStudent(const IntensityImageStudent &other) : IntensityImage(other.getWidth(), other.getHeight()) {
	//TODO: Create a copy from the other object
	this->set(other.getWidth(), other.getHeight() );
}

IntensityImageStudent::IntensityImageStudent(const int width, const int height) : IntensityImage(width, height) {
	//TODO: Initialize pixel storage
	this->set(width, height);
}

IntensityImageStudent::~IntensityImageStudent() {
	//TODO: delete allocated objects
	delete[] pixelList;
}

void IntensityImageStudent::set(const int width, const int height) {
	IntensityImage::set(width, height);
	//TODO: resize or create a new pixel storage (Don't forget to delete the old storage)
	delete[] pixelList;
	pixelList = new int[width * height];
	nPixels = width * height - 1;
}

void IntensityImageStudent::set(const IntensityImageStudent &other) {
	int tempWidth = other.getWidth();
	int tempHeight = other.getHeight();

	IntensityImage::set(tempWidth, tempHeight);
	//TODO: resize or create a new pixel storage and copy the object (Don't forget to delete the old storage)
	delete[] pixelList;
	pixelList = new int[tempWidth * tempHeight];
	nPixels = tempWidth * tempHeight - 1;
}

void IntensityImageStudent::setPixel(int x, int y, Intensity pixel) {
	//TODO: no comment needed :)
	setPixel(x + getWidth() * y, pixel);
}

void IntensityImageStudent::setPixel(int i, Intensity pixel) {
	/*
	* TODO: set pixel i in "Row-Major Order"
	*
	*
	* Original 2d image (values):
	* 9 1 2
	* 4 3 5
	* 8 7 8
	*
	* 1d representation (i, value):
	* i		value
	* 0		9
	* 1		1
	* 2		2
	* 3		4
	* 4		3
	* 5		5
	* 6		8
	* 7		7
	* 8		8
	*/

	if (i > nPixels) {
		return;
	}
	pixelList[i] = pixel;
}

Intensity IntensityImageStudent::getPixel(int x, int y) const {
	//TODO: no comment needed :)
	return getPixel(x + getWidth() * y);
}

Intensity IntensityImageStudent::getPixel(int i) const {
	//TODO: see setPixel(int i, RGB pixel)
	if (i > nPixels) {
		return -1;
	}
	return pixelList[i];
}