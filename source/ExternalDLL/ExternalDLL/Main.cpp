/*
* Copyright (c) 2015 DottedEye Designs, Alexander Hustinx, NeoTech Software, Rolf Smit - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*/
#pragma warning(disable : 4996)
#include <iostream> //std::cout
#include "ImageIO.h" //Image load and save functionality
#include "HereBeDragons.h"
#include "ImageFactory.h"
#include "DLLExecution.h"

#include <chrono> //voor de timers
#include <ctime>   

#include <iomanip> //om de bestandsnamen te genereren
#include <fstream> //om de data op te slaan in een txt file




void drawFeatureDebugImage(IntensityImage &image, FeatureMap &features);
bool executeSteps(DLLExecution * executor);

float timePreProcessingStep1 = 0;

int main(int argc, char * argv[]) {
	auto startTotal = std::chrono::system_clock::now();//total time

	//ImageFactory::setImplementation(ImageFactory::DEFAULT);
	ImageFactory::setImplementation(ImageFactory::STUDENT);

	ImageIO::debugFolder = "../../../debug/FaceMinMin";
	ImageIO::isInDebugMode = false; //If set to false the ImageIO class will skip any image save function calls
	  
	std::ofstream myfile; //data opslaaan
	myfile.open("../../../meetrapporten/working/test1.txt");
	
	myfile << "filename" << ";" << "timePreProcessingStep1" << ";" << "elapsed_seconds_tests.count()\n"; //wat waar staat

	int aantalFotots = 30;
	for (int i = 1; i <= aantalFotots; i++) {
		auto startTests = std::chrono::system_clock::now();

		RGBImage* input = ImageFactory::newRGBImage();

		std::stringstream a_stream;
		a_stream << std::setfill('0') << std::setw(6) << i;
		std::string filename = a_stream.str();

		std::string imagePath = "../../../testsets/celebDataset/" + filename + ".jpg"; // Jelle
		//std::string imagePath = "../../../../../pictureDatabase/img_align_celeba/img_align_celeba/" + filename + ".jpg"; // Mart
		//std::string imagePath = "../../../testsets/Set A/TestSet Images/female-2.png"; // Testset

		std::cout << "filename: " << filename << "\n";

		if (!ImageIO::loadImage(imagePath, *input)) {
			std::cout << "Image could not be loaded!" << std::endl;
			system("pause");
			return 0;
		}

		ImageIO::saveRGBImage(*input, ImageIO::getDebugFileName("debug.png"));

		DLLExecution* executor = new DLLExecution(input);


		if (executeSteps(executor)) {
			std::cout << "Face recognition successful!" << std::endl;
			std::cout << "Facial parameters: " << std::endl;
			for (int i = 0; i < 16; i++) {
				std::cout << (i + 1) << ": " << executor->facialParameters[i] << std::endl;
			}
		}

		delete executor;


		auto endTests = std::chrono::system_clock::now();

		std::chrono::duration<double> elapsed_seconds_tests = endTests - startTests;
		std::time_t end_time = std::chrono::system_clock::to_time_t(endTests);

		std::cout << "===============" << timePreProcessingStep1 << std::endl;
		myfile << filename << ";" << timePreProcessingStep1 << ";" << elapsed_seconds_tests.count() << std::endl;
	}


	auto endTotal = std::chrono::system_clock::now(); //total time

	std::chrono::duration<double> elapsed_seconds_total = endTotal - startTotal; //total time
	std::time_t end_time = std::chrono::system_clock::to_time_t(endTotal); //total time

//	std::cout << "Elapsed time: " << elapsed_seconds_total.count() << "s\n";
	myfile << "total time in sec: " << elapsed_seconds_total.count();//data opslaan
	myfile.close();//data in file

	system("pause");
	return 1;
}


bool executeSteps(DLLExecution * executor) {

	//Execute the four Pre-processing steps

	auto startPreProcessingStep1 = std::chrono::system_clock::now();//PreProcessingStep1 time
	if (!executor->executePreProcessingStep1(false)) {
		std::cout << "Pre-processing step 1 failed!" << std::endl;
		return false;
	}
	auto endPreProcessingStep1 = std::chrono::system_clock::now(); //PreProcessingStep1 time

	std::chrono::duration<double> elapsed_seconds_PreProcessingStep1 = endPreProcessingStep1 - startPreProcessingStep1; //PreProcessingStep1 time
	std::time_t end_time = std::chrono::system_clock::to_time_t(endPreProcessingStep1); //PreProcessingStep1 time
	timePreProcessingStep1 = elapsed_seconds_PreProcessingStep1.count();

	if (!executor->executePreProcessingStep2(false)) {
		std::cout << "Pre-processing step 2 failed!" << std::endl;
		return false;
	}
	ImageIO::saveIntensityImage(*executor->resultPreProcessingStep2, ImageIO::getDebugFileName("Pre-processing-2.png"));

	if (!executor->executePreProcessingStep3(false)) {
		std::cout << "Pre-processing step 3 failed!" << std::endl;
		return false;
	}
	ImageIO::saveIntensityImage(*executor->resultPreProcessingStep3, ImageIO::getDebugFileName("Pre-processing-3.png"));

	if (!executor->executePreProcessingStep4(false)) {
		std::cout << "Pre-processing step 4 failed!" << std::endl;
		return false;
	}
	ImageIO::saveIntensityImage(*executor->resultPreProcessingStep4, ImageIO::getDebugFileName("Pre-processing-4.png"));


	//Execute the localization steps
	if (!executor->prepareLocalization()) {
		std::cout << "Localization preparation failed!" << std::endl;
		return false;
	}

	if (!executor->executeLocalizationStep1(false)) {
		std::cout << "Localization step 1 failed!" << std::endl;
		return false;
	}

	if (!executor->executeLocalizationStep2(false)) {
		std::cout << "Localization step 2 failed!" << std::endl;
		return false;
	}

	if (!executor->executeLocalizationStep3(false)) {
		std::cout << "Localization step 3 failed!" << std::endl;
		return false;
	}

	if (!executor->executeLocalizationStep4(false)) {
		std::cout << "Localization step 4 failed!" << std::endl;
		return false;
	}

	if (!executor->executeLocalizationStep5(false)) {
		std::cout << "Localization step 5 failed!" << std::endl;
		return false;
	}


	//Execute the extraction steps
	if (!executor->prepareExtraction()) {
		std::cout << "Extraction preparation failed!" << std::endl;
		return false;
	}

	if (!executor->executeExtractionStep1(false)) {
		std::cout << "Extraction step 1 failed!" << std::endl;
		return false;
	}

	if (!executor->executeExtractionStep2(false)) {
		std::cout << "Extraction step 2 failed!" << std::endl;
		return false;
	}

	if (!executor->executeExtractionStep3(false)) {
		std::cout << "Extraction step 3 failed!" << std::endl;
		return false;
	}


	//Post processing and representation
	if (!executor->executePostProcessing()) {
		std::cout << "Post-processing failed!" << std::endl;
		return false;
	}

	drawFeatureDebugImage(*executor->resultPreProcessingStep1, executor->featuresScaled);

	if (!executor->executeRepresentation()) {
		std::cout << "Representation failed!" << std::endl;
		return false;
	}
	return true;
}

void drawFeatureDebugImage(IntensityImage &image, FeatureMap &features) {
	RGB colorRed(244, 67, 54);
	RGBImage * debug = ImageFactory::newRGBImage(image.getWidth(), image.getHeight());
	ImageIO::intensityToRGB(image, *debug);

	//Nose
	Point2D<double> noseLeft = features.getFeature(Feature::FEATURE_NOSE_END_LEFT)[0];
	Point2D<double> noseRight = features.getFeature(Feature::FEATURE_NOSE_END_RIGHT)[0];
	Point2D<double> nostrilLeft = features.getFeature(Feature::FEATURE_NOSTRIL_LEFT)[0];
	Point2D<double> nostrilRight = features.getFeature(Feature::FEATURE_NOSTRIL_RIGHT)[0];
	Point2D<double> noseBottom = features.getFeature(Feature::FEATURE_NOSE_BOTTOM)[0];


	//These (weird) methods can be used to draw debug points
	HereBeDragons::TriumphInLoveFleshStaysNoFatherReason(*debug, noseLeft, colorRed);
	HereBeDragons::TriumphInLoveFleshStaysNoFatherReason(*debug, noseRight, colorRed);
	HereBeDragons::TriumphInLoveFleshStaysNoFatherReason(*debug, nostrilLeft, colorRed);
	HereBeDragons::TriumphInLoveFleshStaysNoFatherReason(*debug, nostrilRight, colorRed);
	HereBeDragons::TriumphInLoveFleshStaysNoFatherReason(*debug, noseBottom, colorRed);

	//Chin
	std::vector<Point2D<double>> points = features.getFeature(Feature::FEATURE_CHIN_CONTOUR).getPoints();
	for (size_t i = 0; i < points.size(); i++) {
		HereBeDragons::TriumphInLoveFleshStaysNoFatherReason(*debug, points[i], colorRed);
	}

	//Eye
	Feature leftEye = features.getFeature(Feature::FEATURE_EYE_LEFT_RECT);
	Feature rightEye = features.getFeature(Feature::FEATURE_EYE_RIGHT_RECT);


	//These (weird) methods can be used to draw debug rects
	HereBeDragons::AsHisTriumphantPrizeProudOfThisPride(*debug, leftEye[0], leftEye[1], colorRed);
	HereBeDragons::AsHisTriumphantPrizeProudOfThisPride(*debug, rightEye[0], rightEye[1], colorRed);


	//Head
	Feature headTop = features.getFeature(Feature::FEATURE_HEAD_TOP);
	Feature headLeftNoseMiddle = features.getFeature(Feature::FEATURE_HEAD_LEFT_NOSE_MIDDLE);
	Feature headLeftNoseBottom = features.getFeature(Feature::FEATURE_HEAD_LEFT_NOSE_BOTTOM);
	Feature headRightNoseMiddle = features.getFeature(Feature::FEATURE_HEAD_RIGHT_NOSE_MIDDLE);
	Feature headRightNoseBottom = features.getFeature(Feature::FEATURE_HEAD_RIGHT_NOSE_BOTTOM);
	HereBeDragons::TriumphInLoveFleshStaysNoFatherReason(*debug, headTop[0], colorRed);
	HereBeDragons::TriumphInLoveFleshStaysNoFatherReason(*debug, headLeftNoseMiddle[0], colorRed);
	HereBeDragons::TriumphInLoveFleshStaysNoFatherReason(*debug, headLeftNoseBottom[0], colorRed);
	HereBeDragons::TriumphInLoveFleshStaysNoFatherReason(*debug, headRightNoseMiddle[0], colorRed);
	HereBeDragons::TriumphInLoveFleshStaysNoFatherReason(*debug, headRightNoseBottom[0], colorRed);

	//Mouth
	Point2D<double> mouthTop = features.getFeature(Feature::FEATURE_MOUTH_TOP)[0];
	Point2D<double> mouthBottom = features.getFeature(Feature::FEATURE_MOUTH_BOTTOM)[0];
	Point2D<double> mouthLeft = features.getFeature(Feature::FEATURE_MOUTH_CORNER_LEFT)[0];
	Point2D<double> mouthRight = features.getFeature(Feature::FEATURE_MOUTH_CORNER_RIGHT)[0];

	//This (weird) method can be used to draw a debug line
	HereBeDragons::ButRisingAtThyNameDothPointOutThee(*debug, mouthLeft, mouthRight, colorRed);

	HereBeDragons::TriumphInLoveFleshStaysNoFatherReason(*debug, mouthTop, colorRed);
	HereBeDragons::TriumphInLoveFleshStaysNoFatherReason(*debug, mouthBottom, colorRed);
	HereBeDragons::TriumphInLoveFleshStaysNoFatherReason(*debug, mouthLeft, colorRed);
	HereBeDragons::TriumphInLoveFleshStaysNoFatherReason(*debug, mouthRight, colorRed);

	ImageIO::saveRGBImage(*debug, ImageIO::getDebugFileName("feature-points-debug.png"));
	delete debug;
}