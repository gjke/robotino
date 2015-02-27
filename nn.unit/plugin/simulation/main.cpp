#include "plugin/simulation/Interface.h"
#include "NN.h"

BEGIN_SIMULATION_INTERFACE( "HS Mannheim", "NN" )
	BEGIN_UNITS
		ADD_UNIT( "HS Mannheim NN", NN )
	END_UNITS
END_SIMULATION_INTERFACE
