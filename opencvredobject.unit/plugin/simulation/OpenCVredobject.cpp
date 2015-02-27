#include "OpenCVredobject.h"

using namespace rec::core;
using namespace rec::core::image;
using namespace cv;
using namespace std;


struct ObjectInformation
{
	int deflection;
	int area;
	int y;
	bool ifFound;
	rec::core::image::Image im;
} oi;


OpenCVredobject::OpenCVredobject (plugin::simulation::UnitDelegate& del)
: plugin::simulation::Unit(del, plugin::simulation::Deterministic)
{
	lastDeflection = 0;
	maxDeflection = 160;
}

void OpenCVredobject::step (void)
{
	//read the input image
	inputImage = readInput("image").toImage();

	//check if there is an image
	if (!inputImage.isNull())
	{
		try
		{
			img = Mat(inputImage.info().height, inputImage.info().width, CV_8UC3, inputImage.data());
			cvtColor(img, img, CV_RGB2BGR);
			//imwrite("C:\\Users\\1130386.FFE\\opencvtest\\ii.jpg", img);
			getOI();
			writeOutput("deflection", oi.deflection);
			writeOutput("area", oi.area);
			writeOutput("y", oi.y);
			writeOutput("ifFound", oi.ifFound);
			writeOutput("imageWithoutObject", oi.im);
		}
		catch( cv::Exception& e )
		{
			/* handle the exeption*/
		}
	}
}

void OpenCVredobject::getOI()
{
	// Load source image and convert it to gray
	Mat red, red1, red2, hsv_src;
	float deflection;
    //convert to HSV
    cvtColor(img, hsv_src, CV_BGR2HSV);
    inRange(hsv_src, Scalar(0, 135, 135), Scalar(20, 255, 255), red1);
	inRange(hsv_src, Scalar(159, 135, 135), Scalar(179, 255, 255), red2);
	add(red1, red2, red);
    
	vector<vector<Point2i> > contours;
    vector<Vec4i> hierarchy;
    findContours( red, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point2i(0, 0) );
	if (contours.size() > 0)
	{
		vector <Point2i> puckContour;
		int a = 0;
		for (int i = 0; i < contours.size(); i++)
		{
			if (contourArea(contours[i]) > a)
			{
				a = contourArea(contours[i]);
				puckContour = contours[i];
			}
		}

		//get the moment
		Moments mu = moments(puckContour, false);

		//get the mass center
		Point2f mc = Point2f(mu.m10/mu.m00, mu.m01/mu.m00);

		//printf("center of the puck (%.2f; %.2f)", mc.x, mc.y);
		oi.deflection =  (int) mc.x - red.cols/2;
		oi.y = (int) mc.y;
		oi.area = contourArea(puckContour) > 2400 ? 2400 : (int)contourArea(puckContour);
		oi.ifFound = true;
		oi.im = removeObject(&puckContour, oi.area);
	}
	else
	{
		oi.deflection = 0;
		lastDeflection = 0;
		oi.area = 0;
		oi.y = 0;
		oi.ifFound = false;
		oi.im = inputImage;
	}
}

rec::core::image::Image OpenCVredobject::removeObject(vector<Point2i>* contour, int area)
{
	Rect boundRect = boundingRect(Mat(*contour));
	int shift = (int) area / 3;
	boundRect = boundRect - Point2i(10, 5);
	boundRect = boundRect + Size2i(15, 20);

	Mat drawing = Mat::zeros(img.size(), CV_8UC1);
	rectangle(drawing, boundRect, Scalar(100), CV_FILLED, 8, 0);
	inpaint(img, drawing, img, 5, CV_INPAINT_TELEA);

	//rectangle(img, boundRect, Scalar(100), 1, 8, 0);

	//cvtColor(img, img, CV_BGR2RGB);


	rec::core::image::ImageInfo(img.size().width, img.size().height, img.channels(), (int) img.elemSize(),rec::core::image::Format_BGR);
	rec::core::image::Image outputImage = rec::core::image::Image(rec::core::image::ImageInfo(img.size().width, img.size().height, img.channels(), (int) img.elemSize(), rec::core::image::Format_BGR),
																	img.step, 
																	img.data);
	return outputImage;

}
