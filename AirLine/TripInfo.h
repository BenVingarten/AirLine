#pragma once
#include <iostream>
using namespace std;
#include "Travel.h"
#include "Date.h"
#include "Time.h"


class TripInfo: public Travel
{
private:		

	Time flightDuration;
	Date date;

protected:
	virtual void print(ostream& out)const;



public:
	TripInfo(const char* src, const char* des, int d, int m, int y, int hour, int minute);
	TripInfo(const Date& d, const Travel& trav, const Time& time);
	
	//read and write to file
	TripInfo(ifstream& in);
	void saveToFile(ofstream& out) const;


	void setDuration(int hour, int minute);
	const Time& getFlightDuration()const;
	
	//we must implement operator << because two of our parents has the same operator
	friend ostream& operator << (ostream& out, const TripInfo& t);

};

