#pragma once
#include <iostream>
using namespace std;
#include "Worker.h"
#include "Time.h"
#include "Date.h"
#include "TripInfo.h"
#include "Travel.h"

class Ticket;
class Plane;
class Flight
{
private:
	int flightId;
	static int flightIdGenerator;
	TripInfo info;
	Plane* pPlane;
	Ticket** ticketArr;
	int currentPurchasedTickets;
	Worker** crewMembers;
	int currentNumOfCrewMembers;
	const int MAX_CREW_MEMBERS = 10; // 2 pilot 4-5 flightAttendets and 3-4 technicians
	

	bool addCrewMember(const Worker* w);


public:

	Flight(char destination[3], char source[3], Pilot* pi, int hour, int minute, int day, int month, int year);
	Flight(const Travel & t, Pilot* pi, const Time& t, const Date& d);
	Flight(const TripInfo& t, Pilot* pi);
	Flight(const Travel& t, const Time& duartion, const Date& d);
	~Flight()

	bool setPlane(const Plane& pl);
	bool setDuration(const Time& t)
	Time getDuration()const;

	bool operator = (const Flight& f);
	friend ostream& operator <<(ostream& out, const Flight& f);
	
	bool assignCrew(ostream& out, istream& in);
	bool checkIfFlightReady();
	TripInfo getInfo()const;
	
};

