#ifndef _OpenCVredobject_H_
#define _OpenCVredobject_H_

#define HAVE_OPENCV

#include "plugin/simulation/Unit.h"
#include "rec/core/Image.h"
#include <opencv2/core/core.hpp>
#include <opencv2/core/core_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/photo/photo.hpp>
#include <rec/core/image/OpenCV.h>

#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;



class OpenCVredobject : public plugin::simulation::Unit
{
public:
	OpenCVredobject (plugin::simulation::UnitDelegate& del);
	void step (void);
	void getOI(void);
	rec::core::image::Image removeObject(vector<Point2i>*, int area);
private:
	int lastDeflection;
	int maxDeflection;
	cv::Mat img;
	rec::core::image::Image inputImage;
};

#endif // _OpenCVTest_H_
