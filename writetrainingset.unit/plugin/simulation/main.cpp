#include "plugin/simulation/Interface.h"
#include "WriteTrainingSet.h"

BEGIN_SIMULATION_INTERFACE( "HS Mannheim", "Write Training Set" )
	BEGIN_UNITS
		ADD_UNIT( "HS Mannheim Write Training Set", WriteTrainingSet )
	END_UNITS
END_SIMULATION_INTERFACE
