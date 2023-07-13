#pragma once
#include <fstream>
using namespace std;

class Save
{

public:
	virtual void saveToFile(ofstream& out)const = 0;
};
