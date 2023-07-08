#pragma once
#include <iostream>
using namespace std;


#include "Ticket.h"
#include "TripInfo.h"
#include "Passenger.h"


class Passenger;
class Ticket;

class FirstClassTicket : public Ticket
{
	

public:
	FirstClassTicket(int cost, int gate, const Time& board, TripInfo* info, int seat, Flight& myFlight);
	FirstClassTicket(const FirstClassTicket& fct);
	FirstClassTicket(FirstClassTicket&& t) noexcept;
	~FirstClassTicket() {};


	Ticket* clone()const;

	const FirstClassTicket& operator =(FirstClassTicket&& p) noexcept;
	
	void print(ostream& out)const;

private:
	static const float ADDITIONAL_PRICE;
};

