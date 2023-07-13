#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;
#include <fstream>

#include "Date.h"


const int Date::DAY_MONTH_LIMIT[MAX_MONTH] = { 31,29,31,30,31,30,31,31,30,31,30,31 };

Date::Date(int d, int m, int y)
{
	setDate(d, m, y); //This function check the input
}

Date::Date(ifstream& in)
{
	char tmp;
	in >> day >> tmp >> month >> tmp >> year;
}

void Date::saveToFile(ofstream& out) const
{
	out << day << DEL << month << DEL << year << endl;
}



ostream& operator << (ostream& out, const Date& date)
{
	date.print(out);
	return out;
}

void Date::print(ostream& out) const
{
	out << "Date: " << day << R"(\)" << month << R"(\)" << year;

}

Date Date::operator+ (int days) const
{
	Date temp(*this);
	for (int i = 0; i < days; i++)
		temp.addOneDay();
	return temp;
}

const Date& Date::operator++ ()		//prefix
{
	addOneDay();
	return *this;
}

Date Date::operator++ (int)		//postfix
{
	Date temp(*this);
	addOneDay();
	return temp;
}


Date operator+(int days, const Date& date)
{
	return date + days;
}

void Date::addOneDay()
{
	//Are we at the same month?
	if (day < DAY_MONTH_LIMIT[month - 1])
	{
		day++;
		return;
	}
	//Need to move one month ahead.
	if (month < MAX_MONTH)
	{
		month++;
		day = 1;
		return;
	}

	//Need to move a year
	year++;
	month = 1;
	day = 1;
}

void	 Date::setDay(int d)
{
	if ((d < MIN_DAY) || (d > DAY_MONTH_LIMIT[month - 1]))
		day = 0;
	else
		day = d;
}

void	 Date::setMonth(int m)
{
	if ((m < MIN_MONTH) || (m > MAX_MONTH))
		month = 0;
	else
		month = m;

}

void	 Date::setYear(int y)
{
	if (y > 0)
		year = y;
	else
		year = 0;

}

void Date::setDate(int d, int m, int y)
{
	if ((y < 0) || (m < MIN_MONTH) || (m > MAX_MONTH) ||
		(d < MIN_DAY) || (d > DAY_MONTH_LIMIT[m - 1]))
	{
		cout << "error in parameters" << endl;
		return;
	}

	year = y;
	month = m;
	day = d;
}