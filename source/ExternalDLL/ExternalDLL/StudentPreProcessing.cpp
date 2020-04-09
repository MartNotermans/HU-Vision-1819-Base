#include "StudentPreProcessing.h"
#include "ImageFactory.h"
#include <math.h>

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &RGB_image) const {
    // Apply the 'student' code to the images selected in 'main.cpp'. 
    // Get an image and count all pixels in this image.
    // Apply the chosen method (Intenisty, Luminance, Luma) to every pixel.
    IntensityImage* intensity_image = ImageFactory::newIntensityImage();
    intensity_image->set(RGB_image.getWidth(), RGB_image.getHeight());
    int nPixels = RGB_image.getWidth() * RGB_image.getHeight();
    for (int i = 0; i < nPixels; i++) {
        intensity_image->setPixel(i, (RGB_image.getPixel(i).r + RGB_image.getPixel(i).g + RGB_image.getPixel(i).b) / 3); // Intensity
        //intensity_image->setPixel(i, (0.3 * RGB_image.getPixel(i).r) + (0.59 * RGB_image.getPixel(i).g) + (0.11 * RGB_image.getPixel(i).b)); // Luminance
        //intensity_image->setPixel(i, (0.2126 * pow(RGB_image.getPixel(i).r, 1 / 2.2)) + (0.7152 * pow(RGB_image.getPixel(i).g, 1 / 2.2)) + (0.0722 * pow(RGB_image.getPixel(i).b, 1 / 2.2))); // Luma
    }
    return intensity_image;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}