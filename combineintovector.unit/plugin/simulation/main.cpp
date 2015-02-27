#include "plugin/simulation/Interface.h"
#include "CombineIntoVector.h"

BEGIN_SIMULATION_INTERFACE( "HS Mannheim", "Combine Into Vector" )
	BEGIN_UNITS
		ADD_UNIT( "HS Mannheim Combine Into Vector", CombineIntoVector )
	END_UNITS
END_SIMULATION_INTERFACE
