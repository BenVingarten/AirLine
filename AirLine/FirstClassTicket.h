#pragma once
#include <iostream>
using namespace std;
#include "Ticket.h"
#include "Date.h"

class Passenger;

class FirstClassTicket: public Ticket
{
private:
	const static int MAX_DISHES = 10;
	char* menu[MAX_DISHES];
	int numOfDishes;

	bool addDishToMenu();

	void print(ostream& out)const;

public:
	FirstClassTicket(int cost, int gate, const Time& t, const Date& d, int seat, Passenger* p);
	FirstClassTicket(const Ticket& t); // c'tor with ticket reference
	FirstClassTicket(const FirstClassTicket& fct);
	FirstClassTicket(Ticket&& t) noexcept;
	~FirstClassTicket();


	//FirstClassTicket& operator =(const FirstClassTicket& p);  // operator =
	virtual Ticket& clone()const;

	const FirstClassTicket& operator =(FirstClassTicket&& p) noexcept;
	bool setMenu();
	void showMenu()const;

	
};

