#define _CRT_SECURE_NO_WARNINGS
#include "FirstClassTicket.h"
//#include "Passenger.h"

const float FirstClassTicket::ADDITIONAL_PRICE = 1.5;

FirstClassTicket::FirstClassTicket(int cost, int gate, const Time& boardingT, TripInfo* info, 
	int seat, Flight& myFlight)
	: Ticket((int)(cost * ADDITIONAL_PRICE), gate, boardingT, info, seat, myFlight) {}


FirstClassTicket::FirstClassTicket(const FirstClassTicket& fct)
	: Ticket(fct) { }

FirstClassTicket::FirstClassTicket(FirstClassTicket&& t) noexcept
	: Ticket(std::move(t))
{

}


Ticket* FirstClassTicket::clone() const
{
	return new FirstClassTicket(*this);
}

const FirstClassTicket& FirstClassTicket::operator=(FirstClassTicket&& p) noexcept
{
	if (this != &p)
	{
		Ticket::operator=(std::move(p));
	}
	return *this;
}

void FirstClassTicket::print(ostream& out) const
{
	Ticket::print(out);
	
}


ostream& operator<<(ostream& out, const FirstClassTicket& fct)
{
	fct.print(out);
	return out;
}
