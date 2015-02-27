#include "NN.h"

NN::NN (plugin::simulation::UnitDelegate& del)
: plugin::simulation::Unit(del, plugin::simulation::Deterministic)
{
}
struct fann* ann;
bool init = false;
void initNN();

using namespace rec::core;
using namespace std;

fann_type* in; 
fann_type* out;
fann_type* out_past;

void NN::step (void)
{
	if (!init)
	{
		initNN();
		init = true;
	}

		float deflection = readInput("deflection").toFloat();
		float area = readInput("area").toFloat();
		IntVector profile = readInput("profile").toIntVector();

		
		in[0] = deflection;
		in[1] = area;
		for (int i = 0; i < profile.count(); i++)
		{in[i+2] = profile[i];}

		/* Extension: past values of dy/dt 
		in[profile.count()+2] = out_past[1];
		in[profile.count()+3] = out_past[2];
		in[profile.count()+4] = out_past[3];
		extension end */

		
		fann_scale_input(ann, in);
		out = fann_run(ann, in);
		fann_descale_output(ann, out);

		/* Extension: past values of dy/dt 
		out_past[3] = out_past[2];
		out_past[2] = out_past[1];
		out_past[1] = out_past[0];
		out_past[0] = out[1];
		extension end */

		writeOutput("xdot", out[0]);
		writeOutput("ydot", out[1]);
		writeOutput("phidot", out[2]);
		
		profile.clear();
	/*
		catch( exception& e )
	{
		// handle the exeption
		FILE *f = fopen("D:\\RobviewFB\\nn\\nnlog.txt", "w");
		fprintf(f, "%s\n", e.what());
		fclose(f);
	}
	*/

}


void initNN()
{
	ann = fann_create_from_file("D:\\RobviewFB\\nn\\without8-0025.net");
	in = (fann_type*) malloc(10*sizeof(fann_type));
	out = (fann_type*) malloc(3*sizeof(fann_type));

	/*
	out_past = (fann_type*)malloc(4*sizeof(fann_type));
	out_past[0] = 0;
	out_past[1] = 0;
	out_past[2] = 0;
	out_past[3] = 0;
	*/
}
