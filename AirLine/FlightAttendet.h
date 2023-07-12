#pragma once
#include <iostream>
using namespace std;

#include "Person.h"
#include "Worker.h"
#include "Passenger.h"

#define MAX_LANGUAGES  10	//define because its limiter for array

class FlightAttendet: public Worker
{
private:
	static const char* DEF_LANG;

	char* allLanguages[MAX_LANGUAGES]; //char ** all_languages 
	int currentNumOfLanguages;

	void print(ostream& out)const;

public:

	FlightAttendet(const char* n, int age, char gender, float salary, int seniority, const char* baseLang);
	FlightAttendet(const FlightAttendet& other);
	FlightAttendet(FlightAttendet&& w) noexcept;
	~FlightAttendet();
	
	//read and write from file
	FlightAttendet(ifstream& in);
	void saveToFile(ofstream& out)const;
	

	const char** getLanguages()const;
	int getCurrentNumOfLanguages()const;
	bool addLanugage(const char* language);

	virtual void setRaise() override;	//+100 NIS per language she speaks
	virtual void prepareForFlight(ostream& out) override ;
	virtual void annualRefresh(ostream& out) override;
	virtual void takeoff(ostream& out)const override;
	virtual void landing(ostream& out)const override;
	Worker* clone()const { return new FlightAttendet(*this); }
	
};

