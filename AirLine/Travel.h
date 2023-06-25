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
	Travel() = default; //so we can create TripInfo(ostrem, istream)
	Travel(const char s[MAX_CHAR_CODE], const char d[MAX_CHAR_CODE]);
	bool setSource(const char s[MAX_CHAR_CODE]);
	bool setDest(const char d[MAX_CHAR_CODE]);
	virtual ~Travel() {};

	friend ostream& operator << (ostream& out, const Travel& t);
	const char* getSource()const;
	const char* getDestenation()const;
};

