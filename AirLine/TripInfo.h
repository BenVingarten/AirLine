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

	void print(ostream& out)const;

public:
	TripInfo(char src[3], char des[3], int d, int m, int y, int hour, int minute);
	TripInfo(const Date& d, const Travel& trav, const Time& time);

	void setTime(int hour, int minute);
	Time getFlightDuration()const;
};

