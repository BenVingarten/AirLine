#pragma once
#include <iostream>
using namespace std;

#define MAX_CHAR_CODE 4

class Travel
{
private:
	char source[MAX_CHAR_CODE];
	char destination[MAX_CHAR_CODE];

protected:

	virtual void print(ostream& out) const;

public:
	static const char* DEFAULT_SOURCE_CODE; //public because used in passenger 
	static const char* DEFAULT_DEST_CODE;

	Travel() = default; //so we can create TripInfo(ostrem, istream)
	Travel(const char* s, const char* d);

	//read and save to file
	Travel(ifstream& in);
	void saveToFile(ofstream& out)const;

	
	void setSource(const char* s);
	void setDest(const char* d);
	virtual ~Travel() {};

	friend ostream& operator << (ostream& out, const Travel& t);
	const char* getSource()const;
	const char* getDestenation()const;

	static bool airportCodeValid(const char* code); //We use this method also in Passenger ->static
};

