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



class OpenCVredobject : public plugin::simulation::Unit
{
public:
	OpenCVredobject (plugin::simulation::UnitDelegate& del);

	void step (void);

private:
};

#endif // _OpenCVTest_H_
