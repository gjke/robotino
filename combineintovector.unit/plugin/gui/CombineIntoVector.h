#ifndef _CombineIntoVector_H_
#define _CombineIntoVector_H_

#include "plugin/gui/VariableInputDialog.h"

class CombineIntoVector : public plugin::gui::VariableInputDialog
{
	Q_OBJECT

public:
	CombineIntoVector (plugin::gui::UnitDelegate& del, const QStringList& inputNames, int minInputs);

	void update (const plugin::gui::UnitHistoryBundle& buf);
	void translate (void);

private:
	void on_numInputs_valueChanged(int);
	plugin::gui::UnitDelegate& del;
};

#endif // _CombineIntoVector_H_
