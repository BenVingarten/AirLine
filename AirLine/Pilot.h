#pragma once
#include <iostream>
using namespace std;
#include "Worker.h"
#include "Time.h"
#include "Flight.h"

#define RAISE_PRECENTAGE 0.7

class Pilot: public Worker
{
private:

	Time flightHours;

	void print(ostream& out)const;

public:

	Pilot(const char* n, int age, char gender, float salary, int seniority, Time flightHours);
	Pilot(const Pilot& p) = delete;
	Pilot(Pilot&& p) noexcept;
	~Pilot() {};

	//read and write from file
	Pilot(ifstream& in);
	void saveToFile(ofstream& out)const;
	
	
	Time getflightHours()const;
	Pilot& operator +=(const Time& hours); //add to flight hours

	virtual void setRaise()override; //70% of his flightHours from current year
	virtual void prepareForFlight(ostream& out)override;
	virtual void annualRefresh(ostream& out)override;

};

