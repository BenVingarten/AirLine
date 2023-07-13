#pragma once
#include <iostream>
using namespace std;

#include "Person.h"
#include "Worker.h"
#include "Passenger.h"
#include <vector>


class FlightAttendet: public Worker
{
private:
	const static string DEF_LANG;

	vector<string> languagesVec; 
	void print(ostream& out)const;

public:

	FlightAttendet(const string& n, int age, char gender, float salary, int seniority, const string& baseLang = "");
	FlightAttendet(const FlightAttendet& other);
	FlightAttendet(FlightAttendet&& w) noexcept;
	~FlightAttendet() {};
	
	//read and write from file
	FlightAttendet(ifstream& in);
	void saveToFile(ofstream& out)const;
	

	const vector<string> getLanguages()const;
	int getCurrentNumOfLanguages()const;
	bool addLanugage(const string& language);

	virtual void setRaise() override;	//+100 NIS per language she speaks
	virtual void prepareForFlight(ostream& out) override ;
	virtual void annualRefresh(ostream& out) override;
	virtual void takeoff(ostream& out)const override;
	virtual void landing(ostream& out)const override;
	Worker* clone()const { return new FlightAttendet(*this); }
	
};

