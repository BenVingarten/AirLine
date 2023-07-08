#pragma once
#include <iostream>
using namespace std;

#include "Date.h"

class Passenger;
class Ticket;
class FirstClassTicket : public Ticket
{
	

public:
	FirstClassTicket(int cost, int gate, const Time& board, TripInfo* info, int seat, Flight& myFlight);
	FirstClassTicket(const FirstClassTicket& fct);
	FirstClassTicket(FirstClassTicket&& t) noexcept;
	~FirstClassTicket() {};


	Ticket* clone()const override;

	const FirstClassTicket& operator =(FirstClassTicket&& p) noexcept;
	
	void print(ostream& out)const override;

private:
	static const float ADDITIONAL_PRICE;
};

