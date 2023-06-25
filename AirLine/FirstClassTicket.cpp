#include "FirstClassTicket.h"
#include "Passenger.h"

FirstClassTicket::FirstClassTicket(int cost, int gate, const Time& board, TripInfo* info, int seat,
	Flight* myFlight = nullptr)
	: Ticket(cost, gate, board, info, seat, p, myFlight) {}


FirstClassTicket::FirstClassTicket(const FirstClassTicket& fct)
	: Ticket(fct) { }

FirstClassTicket::FirstClassTicket(FirstClassTicket&& t) noexcept
	: Ticket(std::move(t))
{

}

FirstClassTicket::~FirstClassTicket()
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

void FirstClassTicket::showMenu(ostream& out) const
{
	flight->showMenu();
}

ostream& operator<<(ostream& out, const FirstClassTicket& fct)
{
	fct.print(out);
	return out;
}
