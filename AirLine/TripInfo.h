#pragma once
#include <iostream>
using namespace std;
#include "Date.h"
#include "Time.h"
#include "Travel.h"

class TripInfo: public Date, public Travel
{
private:
	Time flightDuration;

protected:
	virtual void print(ostream& out)const;



public:
	TripInfo(const char src[3], const char des[3], int d, int m, int y, int hour, int minute);
	TripInfo(const Date& d, const Travel& trav, const Time& time);
	TripInfo(ostream& out, istream& in);


	void setTime(int hour, int minute);
	const Time& getFlightDuration()const;
	
	//we must implement operator << because two of our parents has the same operator
	friend ostream& operator << (ostream& out, const TripInfo& t);

};

