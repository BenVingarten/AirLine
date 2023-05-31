#pragma once
#include <iostream>
using namespace std;
#include "Person.h"

class Ticket;
class Passenger
{
private:
	Ticket* ticket;
	static int passPortGen; // will be initiallize to 1111 in main
	int passPort;
	int luggageWeight;
	char airPortCode[3];

	void print(ostream& out)const;

public:
	Passenger(const char* n, int age, char gender, int luggageWeight, char code[3]);
	Passenger(const Person& p, int luggageWeight, char code[3]);
	Passenger(const Passenger& p) = delete;
	Passenger(Passenger&& p) noexcept;
	

	
	char* getAirPortCode()const;
	int getLuggageWeight()const;
	int getPassportNum()const;

	void setLuggageWeight(int weight);
	bool setTicket(Ticket* ticket);
};

