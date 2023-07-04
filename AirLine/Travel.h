#pragma once
#include <iostream>
using namespace std;

#define MAX_CHAR_CODE 4
#define DEFAULT_SOURCE_CODE "TLV"
#define DEFAULT_DEST_CODE "ATH" //Athens


class Travel
{
private:
	static const char DEL = '|';

	char source[MAX_CHAR_CODE];
	char destination[MAX_CHAR_CODE];

protected:

	virtual void print(ostream& out) const;

public:
	Travel() = default; //so we can create TripInfo(ostrem, istream)
	Travel(const char* s, const char* d);

	//read and save to file
	Travel(ifstream& in);
	void saveTravel(ofstream& out)const;

	
	void setSource(const char* s);
	void setDest(const char* d);
	virtual ~Travel() {};

	friend ostream& operator << (ostream& out, const Travel& t);
	const char* getSource()const;
	const char* getDestenation()const;

	bool airportCodeValid(const char* code) const;
};

