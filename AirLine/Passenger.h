#pragma once
#include <iostream>
using namespace std;
#include "Person.h"
#include "Travel.h"
//#include "Ticket.h"

class Ticket;

class Passenger : virtual public Person
{
protected:
	static int passportGen; // initiallize to 1111 outside the class (only once)
	
	static const int MAX_WEIGHT = 24;
	static const int MIN_WEIGHT = 5;


	Ticket* ticket;
	int passport;
	int luggageWeight;
	char airportCode[MAX_CHAR_CODE];

	virtual void print(ostream& out)const;

public:
	//Passenger can't have Ticket as he initialized because he needs to buy a ticket
	Passenger(const string& n, int age, char gender, int luggageWeight, const char* code);
	//Passenger(const Passenger& p);
	//Passenger(Passenger&& p) noexcept;
	
	//read and write from file
	Passenger(ifstream& in);
	virtual void saveToFile(ofstream& out)const;
	
	const char* getAirPortCode()const;
	int getLuggageWeight()const;
	int getPassportNum()const;
	Ticket* getTicket()const;

	void setLuggageWeight(int weight);
	bool setTicket(Ticket* ticket);
	void removeTicket();
	void setAirPortCode(const char* newCode);

	virtual Passenger* cloneP()const { return new Passenger(*this); }
	

	bool operator ==(const Passenger& p)const;

};


