#include "IntensityImageStudent.h"

IntensityImageStudent::IntensityImageStudent() : IntensityImage() {
	// Initialize.
	pixelList = new int[1];
	nPixels = 0;
}

IntensityImageStudent::IntensityImageStudent(const IntensityImageStudent &other) : IntensityImage(other.getWidth(), other.getHeight()) {
	// Create a copy from the other object.
	this->set(other.getWidth(), other.getHeight() );
}

IntensityImageStudent::IntensityImageStudent(const int width, const int height) : IntensityImage(width, height) {
	// Initialize pixel (width, height) storage.
	this->set(width, height);
}

IntensityImageStudent::~IntensityImageStudent() {
	// Delete allocated objects
	delete[] pixelList;
}

void IntensityImageStudent::set(const int width, const int height) {
	// Create a new pixel storage and deleting the old storage.
	IntensityImage::set(width, height);
	delete[] pixelList;
	pixelList = new int[width * height];
	nPixels = width * height - 1;
}

void IntensityImageStudent::set(const IntensityImageStudent &other) {
	// Create a new pixel storage, copy the object, and deleting the old storage.
	int tempWidth = other.getWidth();
	int tempHeight = other.getHeight();

	IntensityImage::set(tempWidth, tempHeight);
	delete[] pixelList;
	pixelList = new int[tempWidth * tempHeight];
	nPixels = tempWidth * tempHeight - 1;
}

void IntensityImageStudent::setPixel(int x, int y, Intensity pixel) {
	// Set pixel
	setPixel(x + getWidth() * y, pixel);
}

void IntensityImageStudent::setPixel(int i, Intensity pixel) {
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

Intensity IntensityImageStudent::getPixel(int x, int y) const {
	// Return 2 dimensional image pixel
	return getPixel(x + getWidth() * y);
}

Intensity IntensityImageStudent::getPixel(int i) const {
	// Return 1 dimensional image pixel
	if (i > nPixels) {
		return -1;
	}
	return pixelList[i];
}