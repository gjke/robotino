#include "NN.h"

using namespace rec::core;
using namespace std;

NN::NN (plugin::simulation::UnitDelegate& del)
: plugin::simulation::Unit(del, plugin::simulation::Deterministic)
{
	ann = fann_create_from_file("D:\\RobviewFB\\nn\\without8zero.net");
	in = (fann_type*) malloc(10*sizeof(fann_type));
	out = (fann_type*) malloc(3*sizeof(fann_type));
}

void NN::step (void)
{
	float deflection = readInput("deflection").toFloat();
	float area = readInput("area").toFloat();
	IntVector profile = readInput("profile").toIntVector();

	in[0] = deflection;
	in[1] = area;
	for (int i = 0; i < profile.count(); i++)
	{
		in[i+2] = profile[i];
	}	
		
	fann_scale_input(ann, in);
	out = fann_run(ann, in);
	fann_descale_output(ann, out);

	writeOutput("xdot", out[0]);
	writeOutput("ydot", out[1]);
	writeOutput("phidot", out[2]);
		
	profile.clear();
}

