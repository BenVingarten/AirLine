#pragma once
#include <iostream>
using namespace std;
#include "Worker.h"
#include "Time.h"
#include "Date.h"
#include "TripInfo.h"
#include "Travel.h"
#include "Plane.h"
#include "Pilot.h"
#include "FirstClassTicket.h"
#include "Ticket.h"
#include "AirLine.h"


#define MAX_CREW_MEMBERS 10 // 2 pilot 4 flightAttendets and 4 technicians
#define PRECENTAGE_OF_FIRST_CLASS_TICKETS 0.3
#define FIRST_CLASS_COST_PRECENT 1.5
#define MAX_DISHES 10

#define MIN_PILOTS 1
#define MIN_TECHNICHIAN 2
#define MIN_FLIGHT_ATTENDENT 2

#define MIN_TICKETS 2

class Flight
{
private:
	static int workersOfType[3]; //workers of type [pilot], [flightAttendent], [Technichian]
	static int flightNumberGen; //initialized outside of the class to 4444

	AirLine* airLine;
	int flightNumber;
	TripInfo info;
	int currentPurchasedTickets;
	int currentNumOfCrewMembers;
	Time boardingTime;
	Plane* pPlane;
	Ticket** ticketArr;
	Worker* crewMembers[MAX_CREW_MEMBERS];
	char* meal;
	char* firstClassMenu[MAX_DISHES];
	int numberOfDishes;
	

	bool addCrewMember(Worker* w);
	void createTickets(int ticketCost, int gate);

public:

	Flight(AirLine* myAirLine, char destination[MAX_CHAR_CODE], char source[MAX_CHAR_CODE], 
		int durHour, int durMinute, int borHour, int borMinute, int day, int month, int year, Plane* plane = nullptr,
		int ticketCost = 20, int gate = 1, char* meal = nullptr);
	Flight(AirLine* myAirLine, const Travel & trav, const Date& d, const Time& time, Plane* plane = nullptr, int ticketCost = 20, int gate = 1, char* meal = nullptr);
	Flight(AirLine* myAirLine, const TripInfo& t, Plane* plane = nullptr, int ticketCost = 20, int gate = 1, char* meal = nullptr);
	Flight(AirLine* myAirLine, ostream& out, istream& in);
	~Flight();


	int getFlightNumber()const;
	const Time& getDuration()const;
	const TripInfo& getInfo()const;
	Plane* getPlane()const;
	int getNumOfcurrentPurchasedTickets()const;
	int getNumOfTickets()const; //number of seats in plane
	Ticket** getTicketArray()const;
	void showMenu()const;
	void showDish()const;

	bool operator = (const Flight& f);
	friend ostream& operator <<(ostream& out, const Flight& f);
	
	bool setPlane(Plane* pl);
	bool setDuration(const Time& t);
	void assignCrew(ostream& out, istream& in);
	void assignCrew(Worker** workers, int workersSize);
	bool checkIfFlightReady();
	bool addDishToMenu(const char* dish);
	
	void interactiveSetPlane(ostream& out, istream& in);
	bool checkCrewTypes();
	bool checkAddCrewMember(Worker* w);
	



};


int Flight::flightNumberGen = 4444;
int Flight::workersOfType[3] = { 0, 0, 0 };
