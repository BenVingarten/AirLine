#pragma once
#include <iostream>
using namespace std;
#include "Worker.h"
#include "Passenger.h"

#define MAX_LANGUAGES  10

class FlightAttendet: public Worker
{
private:
	
	char* allLanguages[MAX_LANGUAGES]; //char ** all_languages 
	int currentNumOfLanguages;

	void print(ostream& out)const;

public:

	FlightAttendet(const char* n, int age, char gender, float salary, int seniority, char* baseLang = nullptr);
	FlightAttendet(const Worker& w, char* baseLang = nullptr);
	FlightAttendet(const FlightAttendet& other) = delete;
	FlightAttendet(FlightAttendet&& w) noexcept;
	FlightAttendet(ostream& out, istream& in);
	~FlightAttendet();
	

	const char** getLanguages()const;
	int getCurrentNumOfLanguages()const;
	bool addLanugage(char* language);

	virtual void setRaise() override;	//+100 NIS per language she speaks
	virtual void prepareForFlight(ostream& out) override ;
	virtual void annualRefresh(ostream& out) override;

	
};

