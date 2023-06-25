#pragma once
#include <iostream>
using namespace std;
#include "Ticket.h"
#include "Date.h"

class Passenger;


class FirstClassTicket: public Ticket
{

public:
	FirstClassTicket(int cost, int gate, const Time& board, TripInfo* info, int seat, Flight* myFlight = nullptr);
	FirstClassTicket(const FirstClassTicket& fct);
	FirstClassTicket(FirstClassTicket&& t) noexcept;
	~FirstClassTicket() {};


	//FirstClassTicket& operator =(const FirstClassTicket& p);  // operator =
	Ticket* clone()const override;

	const FirstClassTicket& operator =(FirstClassTicket&& p) noexcept;
	void showMenu(ostream& out)const;
	void print(ostream& out)const override;

	
};

