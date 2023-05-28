#pragma once
#include <iostream>
using namespace std;
#include "Worker.h"
#include "Time.h"
#include "Flight.h"

class Pilot: public Worker
{
private:

	Time flightHours;

	void checkFlightDetails(const Flight& f);

public:

	Pilot(const char* n, int age, char gender, float salary, int seniority, Time flightHours);
	Pilot(const Worker& w, Time flightHours);
	Pilot(const Pilot& p) = delete;
	Pilot(Pilot&& p);

	friend ostream& operator <<(ostream& out, const Pilot& p);
	
	Time getflightHours()const;
	Person& operator +=(Time hours); //add to flight hours

	virtual void setRaise()override;
	virtual void PrepareForFlight()override;
	virtual void AnnualRefresh()override;

};

