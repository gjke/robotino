#include "CombineIntoVector.h"


CombineIntoVector::CombineIntoVector (plugin::gui::UnitDelegate& del, const QStringList& inputNames, int minInputs ) 
	: plugin::gui::VariableInputDialog (del, inputNames, minInputs)
{
}


void CombineIntoVector::update (const plugin::gui::UnitHistoryBundle& buf)
{
}

void CombineIntoVector::translate (void)
{
}

void  CombineIntoVector::on_numInputs_valueChanged(int n)
{
	/*
	this->updateNumInputs();
	QStringList qsl = QStringList();
	for (int i=0; i<n; i++)
	{
		qsl<<inputNames[i];
	}
	this->setInputNames(qsl, 2, this->del);
	*/

}

