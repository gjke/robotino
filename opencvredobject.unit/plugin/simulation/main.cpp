#include "plugin/simulation/Interface.h"
#include "OpenCVredobject.h"

BEGIN_SIMULATION_INTERFACE( "HS Mannheim", "openCV red object" )
	BEGIN_UNITS
		ADD_UNIT( "HS Mannheim openCV red object", OpenCVredobject )
	END_UNITS
END_SIMULATION_INTERFACE
