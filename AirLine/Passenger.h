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


public:
	Passenger(const char* n, int age, char gender, int luggageWeight, char code[3]);
	Passenger(const Person& p, int luggageWeight, char code[3]);
	Passenger(const Passenger& p) = delete;
	Passenger(Passenger&& p);
	~Passenger();

	friend ostream& operator <<(ostream& out, const Passenger& p);
	bool setTicket(Ticket* ticket);
	int getLuggageWeight();
	int getPassportNum();
	void setLuggageWeight(int weight);
};

