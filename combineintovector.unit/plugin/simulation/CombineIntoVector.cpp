#include "CombineIntoVector.h"
#include "rec/core/variant/Converter.h"

using namespace std;

const char* CombineIntoVector::_inputNames[4] = { "in1", "in2", "in3", "in4"};
CombineIntoVector::CombineIntoVector (plugin::simulation::UnitDelegate& del)
: plugin::simulation::Unit(del, plugin::simulation::Deterministic)
{
}

void CombineIntoVector::step (void)
{
	rec::core::IntVector vec;
	for ( int i = 0; i < 4; i++)
	{
		rec::core::Variant v = readInput(_inputNames[i]);
		if (i == 2)
		{
			rec::core::IntVector subvec = rec::core::variant::Converter::singleton().convert<rec::core::IntVector>( v );
			for( int j=0; j<subvec.size(); ++j )
			{
				vec.append( subvec[j] );
			}
		}
		else
		{
				int a = v.toInt();
				vec.append(a); 
		}
	}
	writeOutput("vector", vec);
}

