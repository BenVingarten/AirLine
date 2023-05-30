#pragma once
#include <iostream>
using namespace std;
class Travel
{
private:
	char source[3];
	char destination[3];

public:
	Travel(char s[3], char d[3]);
	bool setSource(char s[3]);
	bool setDest(char d[3]);

	friend ostream& operator << (ostream& out, const Travel& t);
	char* getSource()const;
	char* getDestenation()const;
};

