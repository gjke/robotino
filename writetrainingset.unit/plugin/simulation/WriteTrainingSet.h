#ifndef _WriteTrainingSet_H_
#define _WriteTrainingSet_H_

#include "plugin/simulation/Unit.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class WriteTrainingSet : public plugin::simulation::Unit
{
public:
	WriteTrainingSet (plugin::simulation::UnitDelegate& del);

	void step (void);

private:
	static string trainingSetFileName;
	static bool isInitialized;
	ofstream set;
	template <typename T>void writeRow (T);
	void initialize(int, int, int);
	void writeLinebreak();
	int nWritten;
};

#endif // _WriteTrainingSet_H_
