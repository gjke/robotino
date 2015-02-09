#ifndef _Obstaclesprofile_H_
#define _Obstaclesprofile_H_

#include "plugin/simulation/Unit.h"
#include "rec/core/Image.h"
#include "rec/core/Vector.h"
#include <opencv2/core/core.hpp>
#include <opencv2/core/core_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/photo/photo.hpp>


class Obstaclesprofile : public plugin::simulation::Unit
{
public:
	Obstaclesprofile (plugin::simulation::UnitDelegate& del);

	void step (void);

private:
};

#endif // _Obstaclesprofile_H_
