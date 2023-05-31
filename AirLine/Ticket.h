#pragma once
#include <iostream>
using namespace std;
#include "Time.h"


class TripInfo;
class Passenger;
class Ticket
{
private:
	int price;
	int gate;
	Time boarding;
	TripInfo* pInfo;
	int seat; // accroding to the index in the tickets array (in flight class)
	Passenger* pPassenger;
	char* meal;
	float maxLuggageWeightAllowed;

protected:
	virtual void print(ostream& out)const;

public:

	Ticket(int cost, int gate, const Time& board, TripInfo* info, int seat, Passenger* p);
	Ticket(const Ticket& other);
	Ticket(Ticket&& ticket) noexcept;
	virtual ~Ticket();

	//bool operator = (const Ticket& t1);
	virtual Ticket& clone()const;

	const Ticket& operator =(Ticket&& t) noexcept;

	friend ostream& operator <<(ostream& out, const Ticket& t);
};

