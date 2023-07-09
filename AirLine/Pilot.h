#pragma once
#include <iostream>
using namespace std;
#include "Time.h"
#include "Worker.h"
#include "Flight.h"



class Pilot: public Worker
{
private:
	static const float RAISE_PRECENTAGE;

	Time flightHours;

	void print(ostream& out)const;

public:

	Pilot(const char* n, int age, char gender, float salary, int seniority, Time flightHours);
	Pilot(const Pilot& p);
	Pilot(Pilot&& p) noexcept;
	~Pilot() {};

	//read and write from file
	Pilot(ifstream& in);
	void saveToFile(ofstream& out)const;
	
	
	Time getflightHours()const;
	Pilot& operator +=(const Time& hours); //add to flight hours

	virtual void setRaise()override; //70% of his flightHours from current year
	virtual void prepareForFlight(ostream& out) override;
	virtual void annualRefresh(ostream& out) override;
	virtual void takeoff(ostream& out) const override;
	virtual void landing(ostream& out) const override;

};

