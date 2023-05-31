#pragma once
#include <iostream>
using namespace std;
#include "Worker.h"

class FlightAttendet: public Worker
{
private:
	const static int MAX_LANGUAGES = 10;
	char* allLanguages[MAX_LANGUAGES];
	int currentNumOfLanguages;

	void print(ostream& out)const;

public:

	FlightAttendet(const char* n, int age, char gender, float salary, int seniority, const char* baseLang);
	FlightAttendet(const Worker& w, const char* baseLang);
	FlightAttendet(const FlightAttendet& other) = delete;
	FlightAttendet(FlightAttendet&& w) noexcept;
	~FlightAttendet();
	

	char** getLanguages()const;
	int getCurrentNumOfLanguages()const;
	bool addLanugage(char* language);

	bool operator ==(const Worker& worker)const;
	virtual void  setRaise() override;
	virtual void PrepareForFlight() override;
	virtual void AnnualRefresh() override;

	
};

