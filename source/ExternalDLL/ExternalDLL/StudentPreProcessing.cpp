#include "StudentPreProcessing.h"
#include "ImageFactory.h"

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &RGB_image) const {
	//return nullptr;

    IntensityImage* intensity_image = ImageFactory::newIntensityImage();
    intensity_image->set(RGB_image.getWidth(), RGB_image.getHeight());
    int nPixels = RGB_image.getWidth() * RGB_image.getHeight();
    for (int i = 0; i < nPixels; i++) {
        intensity_image->setPixel(i, (RGB_image.getPixel(i).r + RGB_image.getPixel(i).g + RGB_image.getPixel(i).b) / 3);
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