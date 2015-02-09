#include "plugin/simulation/Interface.h"
#include "Obstaclesprofile.h"

BEGIN_SIMULATION_INTERFACE( "HS Mannheim", "Obstacles profile" )
	BEGIN_UNITS
		ADD_UNIT( "HS Mannheim Obstacles profile", Obstaclesprofile )
	END_UNITS
END_SIMULATION_INTERFACE
