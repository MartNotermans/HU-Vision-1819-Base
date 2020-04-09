#include "RGBImageStudent.h"

RGBImageStudent::RGBImageStudent() : RGBImage() {
	// Initialize.
	pixelList = new RGB[1];
	nPixels = 0;
}

RGBImageStudent::RGBImageStudent(const RGBImageStudent &other) : RGBImage(other.getWidth(), other.getHeight()) {
	// Create a copy from the other object.
	this->set(other.getWidth(), other.getHeight());
}


RGBImageStudent::RGBImageStudent(const int width, const int height) : RGBImage(width, height) {
	// Initialize pixel (width, height) storage.
	this->set(width, height);
}

RGBImageStudent::~RGBImageStudent() {
	// Delete allocated objects
	delete[] pixelList;
}

void RGBImageStudent::set(const int width, const int height) {
	// Create a new pixel storage and deleting the old storage.
	RGBImage::set(width, height);
	delete[] pixelList;
	pixelList = new RGB[width * height];
	nPixels = width * height - 1;
}

void RGBImageStudent::set(const RGBImageStudent &other) {
	// Create a new pixel storage, copy the object, and deleting the old storage.
	int tempWidth = other.getWidth();
	int tempHeight = other.getHeight();

	RGBImage::set(other.getWidth(), other.getHeight());
	delete[] pixelList;
	pixelList = new RGB[tempWidth * tempHeight];
	nPixels = tempWidth * tempHeight - 1;
}

void RGBImageStudent::setPixel(int x, int y, RGB pixel) {
	// Set pixel
	setPixel(x + getWidth() * y, pixel);
}

void RGBImageStudent::setPixel(int i, RGB pixel) {
	/* Set pixel i in "Row-Major Order"
	* See explanation below:
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
	// Return 2 dimensional image pixel
	return getPixel(x + getWidth() * y);
}

RGB RGBImageStudent::getPixel(int i) const {
	// Return 1 dimensional image pixel
	if (i > nPixels) {
		return -1;
	}
	return pixelList[i];
}