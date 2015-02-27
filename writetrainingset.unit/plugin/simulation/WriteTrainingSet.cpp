#include "WriteTrainingSet.h"

string WriteTrainingSet::trainingSetFileName = "D:\\RobviewFB\\tr.txt";
bool WriteTrainingSet::isInitialized = false;

using namespace std;

WriteTrainingSet::WriteTrainingSet (plugin::simulation::UnitDelegate& del)
: plugin::simulation::Unit(del, plugin::simulation::Deterministic)
{
}

void WriteTrainingSet::step (void)
{
	int nInputs = readInput("nInputs").toInt();
	int nOutputs = readInput("nOutputs").toInt();
	int nSets = readInput("nSets").toInt();
	bool canWrite = readInput("canWrite").toBool();
	if (!isInitialized)
	{
		initialize(nInputs, nOutputs, nSets);
	}
	rec::core::IntVector input = readInput("input").toIntVector();
	rec::core::IntVector output = readInput("output").toIntVector();
	
	if ((nWritten < nSets) && (canWrite))
	{
		writeRow(input);
		writeLinebreak();
		writeRow(output);
		writeLinebreak();
		nWritten++;
	}

}

void WriteTrainingSet::initialize(int nInputs, int nOutputs, int nSets)
{
	set.open(this->trainingSetFileName, ios::app);
	if (set.is_open())
	{
		set<<nSets<<" "<<nInputs<<" "<<nOutputs<<"\n";
		set.close();
	}
	nWritten = 0;
	isInitialized = true;
}

template <typename T>void WriteTrainingSet::writeRow(T v)
{
	set.open(trainingSetFileName, ios::app);
	if (set.is_open())
	{
		for (int i = 0; i < v.count(); i++)
		{
			if (i < v.count()-1) { set<<v[i]<<" "; }
			else{	set<<v[i]; }
		}
		set.close();
	}
}
void WriteTrainingSet::writeLinebreak()
{
	set.open(trainingSetFileName, ios::app);
	set<<"\n";
	set.close();
}


