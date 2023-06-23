#pragma once
#include <iostream>
using namespace std;

class Date
{
public:
	static const int MIN_DAY = 1;
	static const int MIN_MONTH = 1;
	static const int MAX_MONTH = 12;

	static const int DEF_YEAR = 2023;


	//We Assume that Feb always has 29 days (simple)
	static const int DAY_MONTH_LIMIT[MAX_MONTH];

	Date(int d, int m, int y);

	friend ostream& operator << (ostream& out, const Date& date);


	void	setDay(int d);
	void	setMonth(int m);
	void	setYear(int y);

	int		getDay() const { return day; }
	int		getMonth() const { return month; }
	int		getYear()const { return year; }

	Date operator+ (int days) const;
	const Date& operator++ ();		//prefix
	Date operator++ (int);		//postfix

	virtual ~Date() {};

protected:
	void print(ostream& out) const;

private:

	int day;
	int month;
	int year;

	void	addOneDay();
	void setDate(int d, int m, int y);
};

Date operator+(int days, const Date& date);
