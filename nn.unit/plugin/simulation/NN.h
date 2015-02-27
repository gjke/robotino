#ifndef _NN_H_
#define _NN_H_

#include "plugin/simulation/Unit.h"
#include "rec/core/Vector.h"
#include "fann.h"

class NN : public plugin::simulation::Unit
{
public:
	NN (plugin::simulation::UnitDelegate& del);
	void step (void);

private:
	struct fann* ann;
	bool init;
	//void initNN();
	fann_type* in; 
	fann_type* out;
	fann_type* out_past;
};

#endif // _NN_H_
