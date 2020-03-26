#include "RGBImageStudent.h"

RGBImageStudent::RGBImageStudent() : RGBImage() {
	//TODO: Nothing
	pixelList = new RGB[1];
	nPixels = 0;
}

RGBImageStudent::RGBImageStudent(const RGBImageStudent &other) : RGBImage(other.getWidth(), other.getHeight()) {
	//TODO: Create a copy from the other object
	this->set(other.getWidth(), other.getHeight());
}


RGBImageStudent::RGBImageStudent(const int width, const int height) : RGBImage(width, height) {
	//TODO: Initialize pixel storage
	this->set(width, height);
}

RGBImageStudent::~RGBImageStudent() {
	//TODO: delete allocated objects
	delete[] pixelList;
}

void RGBImageStudent::set(const int width, const int height) {
	RGBImage::set(width, height);
	//TODO: resize or create a new pixel storage (Don't forget to delete the old storage)
	delete[] pixelList;
	pixelList = new RGB[width * height];
	nPixels = width * height - 1;
}

void RGBImageStudent::set(const RGBImageStudent &other) {
	int tempWidth = other.getWidth();
	int tempHeight = other.getHeight();

	RGBImage::set(other.getWidth(), other.getHeight());
	//TODO: resize or create a new pixel storage and copy the object (Don't forget to delete the old storage)
	delete[] pixelList;
	pixelList = new RGB[tempWidth * tempHeight];
	nPixels = tempWidth * tempHeight - 1;
}

void RGBImageStudent::setPixel(int x, int y, RGB pixel) {
	//TODO: no comment needed :)
	setPixel(x + getWidth() * y, pixel);
}

void RGBImageStudent::setPixel(int i, RGB pixel) {
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

RGB RGBImageStudent::getPixel(int x, int y) const {
	//TODO: no comment needed :)
	return getPixel(x + getWidth() * y);
}

RGB RGBImageStudent::getPixel(int i) const {
	//TODO: see setPixel(int i, RGB pixel)
	if (i > nPixels) {
		return -1;
	}
	return pixelList[i];
}