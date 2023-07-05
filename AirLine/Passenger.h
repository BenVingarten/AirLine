#pragma once
#include <iostream>
using namespace std;
#include "Person.h"
#include "Travel.h"

class Ticket;
class Passenger : virtual public Person
{
protected:
	static int passportGen; // initiallize to 1111 outside the class (only once)

	Ticket* ticket;
	int passport;
	int luggageWeight;
	char airportCode[MAX_CHAR_CODE];

	void print(ostream& out)const;

public:
	//Passenger can't have Ticket as he initialized because he needs to buy a ticket
	Passenger(const char* n, int age, char gender, int luggageWeight, const char* code);
	Passenger(const Passenger& p) = delete;
	Passenger(Passenger&& p) noexcept;
	
	//read and write from file
	Passenger(ifstream& in);
	void saveToFile(ofstream& out)const;
	
	const char* getAirPortCode()const;
	int getLuggageWeight()const;
	int getPassportNum()const;

	void setLuggageWeight(int weight);
	bool setTicket(Ticket* ticket);
};


int Passenger::passportGen = 1111;
