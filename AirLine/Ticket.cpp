#include "Ticket.h"
#include "TripInfo.h"
#include "Passenger.h"

const float Ticket::MAX_WEIGHT = 24.0;

Ticket::Ticket(int cost, int gate, const Time& board, TripInfo* info, int seat,
			Flight& myFlight)
	: price(cost), gate(gate), boarding(board), pInfo(info), seat(seat), flight(myFlight)
{
}

Ticket::Ticket(const Ticket& other)
	: price(other.price), gate(other.gate), boarding(other.boarding), pInfo(other.pInfo),
	seat(other.seat), pPassenger(other.pPassenger), flight(other.flight) {}

Ticket::Ticket(Ticket&& ticket) noexcept
	: price(ticket.price), gate(ticket.gate), boarding(ticket.boarding), pInfo(ticket.pInfo),
	seat(ticket.seat), pPassenger(ticket.pPassenger), flight(ticket.flight)
{
	ticket.pInfo = nullptr;
	ticket.pPassenger = nullptr;
}


Ticket* Ticket::clone() const
{
	return new Ticket(*this);
}

void Ticket::setSeat(int s)
{
	seat = s;
}

const Ticket& Ticket::operator=(Ticket&& t) noexcept
{
	if (this != &t)
	{
		price = t.price;
		gate = t.gate;
		boarding = t.boarding;
		pInfo = t.pInfo;
		seat = t.seat;
		pPassenger = t.pPassenger;
		flight = t.flight;
		

		t.pInfo = nullptr;
		t.pPassenger = nullptr;
		
	}
	return *this;
}

void Ticket::print(ostream& out) const
{
	out << "Ticket Information:" << endl;
	out << "Flight number: " << flight.getFlightNumber();
	out << ", Price: " << price;
	out << ", Gate: " << gate;
	out << ", Boarding Time: " << boarding;
	out << ", Seat: " << seat << endl;
	out << "Trip Information: ";
	out << *pInfo << endl;
	out << "Passenger Information: " << endl;
	
}

ostream& operator<<(ostream& out, const Ticket& t)
{
	t.print(out);
	return out;
}

int Ticket::getPrice() const
{
	return price;
}

int Ticket::getGateNumber() const
{
	return gate;
}

Passenger* Ticket::getPassenger() const
{
	return pPassenger;
}

TripInfo* Ticket::getTicketInfo() const
{
	return pInfo;
}

const Time& Ticket::getTime() const
{
	return boarding;
}


