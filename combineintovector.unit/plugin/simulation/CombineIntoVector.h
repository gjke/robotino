#ifndef _CombineIntoVector_H_
#define _CombineIntoVector_H_

#include "plugin/simulation/Unit.h"
#include "rec/core/Vector.h"

class CombineIntoVector : public plugin::simulation::Unit
{
public:
	CombineIntoVector (plugin::simulation::UnitDelegate& del);

	void step (void);

private:
	static const char* _inputNames[4];
};

#endif // _CombineIntoVector_H_
