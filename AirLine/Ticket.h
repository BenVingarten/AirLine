#pragma once
#include <iostream>
using namespace std;
#include "Time.h"
#include "Flight.h"

class TripInfo;
class Passenger;

#define MAX_WEIGHT 24.0;
class Ticket
{
protected:
	int price;
	int gate;
	Time boarding;
	TripInfo* pInfo;  
	int seat; // accroding to the index in the tickets array (in flight class)
	Passenger* pPassenger;
	Flight& flight;	
	virtual void print(ostream& out)const;

public:

	Ticket(int cost, int gate, const Time& board, TripInfo* info, int seat,
			Flight& myFlight);
	Ticket(const Ticket& other);
	Ticket(Ticket&& ticket) noexcept;
	virtual ~Ticket() {};

	virtual Ticket* clone()const;
	void setSeat(int s);

	const Ticket& operator =(Ticket&& t) noexcept;

	friend ostream& operator <<(ostream& out, const Ticket& t);

	int getPrice()const;
	int getGateNumber()const;
	const Time& getTime()const;
};

