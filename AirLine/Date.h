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

protected:

     virtual void print(ostream& out)const;

public:
	Date(int day, int month, int year);
	virtual ~Date();


	bool setDay(int day);
	bool setMonth(int month);
	bool setYear(int year);

	int getDay()const;
	int getMonth()const;
	int getYear()const;

	friend ostream& operator <<(ostream& out, const Time& t);
};

