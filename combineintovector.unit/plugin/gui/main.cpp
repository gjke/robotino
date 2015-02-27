#include "plugin/gui/Interface.h"
#include "CombineIntoVector.h"

BEGIN_GUI_INTERFACE( "HS Mannheim", "Combine Into Vector" )
	BEGIN_UNITWIDGETS
		ADD_UNITWIDGET_NARGS2( "HS Mannheim Combine Into Vector", "dialog", 
								plugin::gui::VariableInputDialog,
								QStringList() << "in1" << "in2" << "in3" << "in4" << "in5" << "in6" << "in7" << "in8" << "in9" << "in10",
												2)
	END_UNITWIDGETS
END_GUI_INTERFACE
