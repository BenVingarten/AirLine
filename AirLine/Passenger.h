#pragma once
#include <iostream>
using namespace std;
#include "Person.h"
#include "Travel.h"

class Ticket;
class Passenger : public Person
{
private:
	static int passportGen; // initiallize to 1111 outside the class (only once)

	Ticket* ticket;
	int passport;
	int luggageWeight;
	char airportCode[MAX_CHAR_CODE];

	void print(ostream& out)const;
	bool airportCodeValid(char* code) const; //the code has only 3 charss and adds '\0'


public:
	//Passenger can't have Ticket as he initialized because he needs to buy a ticket
	Passenger(const char* n, int age, char gender, int luggageWeight, char code[MAX_CHAR_CODE]);
	Passenger(const Person& p, int luggageWeight, char code[MAX_CHAR_CODE]);
	Passenger(const Passenger& p) = delete;
	Passenger(ostream& out, istream& in); //c'tor create with user (talks with the user)
	Passenger(Passenger&& p) noexcept;
	

	
	const char* getAirPortCode()const;
	int getLuggageWeight()const;
	int getPassportNum()const;

	void setLuggageWeight(int weight);
	bool setTicket(Ticket* ticket);
};


int Passenger::passportGen = 1111;
