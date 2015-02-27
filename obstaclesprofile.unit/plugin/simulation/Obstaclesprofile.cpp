#include "Obstaclesprofile.h"
#include <sstream>

using namespace rec::core;
using namespace rec::core::image;
using namespace cv;
using namespace std;

/// Function header
bool comparePoints(Point2i a, Point2i b);

Obstaclesprofile::Obstaclesprofile (plugin::simulation::UnitDelegate& del)
: plugin::simulation::Unit(del, plugin::simulation::Deterministic)
{
	thresh = 35;
}

void Obstaclesprofile::step (void)
{
	//read the input image
	rec::core::image::Image inputImage = readInput("image").toImage();

	//read the discretisation level
	nSamples = readInput("descretisationLevel").toInt();

	puckY = readInput("puckY").toInt();

	//check if there is an image
	if (!inputImage.isNull())
	{
			src = Mat(inputImage.info().height, inputImage.info().width, CV_8UC3, inputImage.data());
			im_width = src.cols;
			dSamples = (int) im_width/nSamples;
			bilateralFilter(src, dst, 20, 40, 10);
			cvtColor( dst, src_gray, CV_RGB2GRAY );
			findContours();
			processContours();
			fillIntVector();
	}

	writeOutput("profile", profile);

}
void Obstaclesprofile::findContours()
{
    vector<Vec4i> hierarchy;
    
    /// Detect edges using canny
    Canny( src_gray, canny_output, thresh, thresh*2, 3 );
    /// Find contours
    cv::findContours( canny_output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point2i(0, 0) );
    
}

void Obstaclesprofile::processContours()
{
    vector <Point2i> contoursProcessed;
    vector <Point2i> contourFinal;
    for (int i = 0; i < contours.size(); i++)
    {
        contoursProcessed.reserve(contours[i].size() + contoursProcessed.size());
        contoursProcessed.insert(contoursProcessed.end(), contours[i].begin(), contours[i].end());
    }
    sort(contoursProcessed.begin(), contoursProcessed.end(), comparePoints);
    
    //fill from the left
    for (int i = 0; i < contoursProcessed[0].x; i++)
    {
        contourFinal.push_back(Point2i(i, contoursProcessed[0].y));
    }
    for (int i = 0; i < contoursProcessed.size()-1; i++)
    {
        if (contoursProcessed[i].x != contoursProcessed[i+1].x)
        {
            contourFinal.push_back(contoursProcessed[i]);
        }   
    }
    contourFinal.push_back(contoursProcessed[contoursProcessed.size()-1]);
    //fill from the right
    for (int i = contoursProcessed[contoursProcessed.size()-1].x + 1; i < im_width; i++)
    {
        contourFinal.push_back(Point2i(i, contoursProcessed[contoursProcessed.size()-1].y));
    }
    
	descrete.clear();
    int s = 0;
    int j = 1;
    for (int i = 0; i < contourFinal.size(); i++)
    {
        if (contourFinal[i].x > dSamples*j)
        {
           if (s > puckY)
			{
				descrete.push_back(s);
			}
			else
			{
				descrete.push_back(0);
			}
            s = 0;
            j++;
        }
        s =( s>contourFinal[i].y ) ? s : contourFinal[i].y;
    }
    if (s > puckY)
	{
		descrete.push_back(s);
	}
	else
	{
		descrete.push_back(0);
	}
    
}
void Obstaclesprofile::fillIntVector()
{
	//descrete to profile
	profile = profile.fromStdVector(descrete);
}

bool comparePoints(Point2i a, Point2i b)
{
    return ((a.x < b.x) || ((a.x == b.x) && (a.y < b.y)));
}

