#pragma once
#include <iostream>
using namespace std;
#include "Time.h"

class Date
{
private:
	int day;
	int month;
	int year;

public:
	Date(int day, int month, int year);
	bool setDay(int day);
	bool setMonth(int month);
	bool setYear(int year);
	int getDay()const;
	int getMonth()const;
	int getYear()const;

	friend ostream& operator <<(ostream& out, const Time& t);
};

