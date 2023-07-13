#pragma once
#include <iostream>
using namespace std;
#include "Date.h"
#include "Travel.h"
//#include "Worker.h"
//#include "FirstClassTicket.h"
//#include "Plane.h"
#include "Passenger.h"
#include "Time.h"
#include "TripInfo.h"
#include "AirLine.h"
#include "Save.h"



#define MAX_CREW_MEMBERS 10 //(limit array) 2 pilot 4 flightAttendets and 4 technicians
#define MAX_DISHES 10 //limit array of dishes


class Plane;
class Ticket;
class Worker;
class AirLine;


class Flight: public Save
{
private:
	static const int DEFAULT_COST = 60;
	static const int DEFAULT_GATE = 1;


	static int workersOfType[3]; //workers of type [pilot], [flightAttendent], [Technichian]
	static int flightNumberGen; //initialized outside of the class to 4444

	/*
	  every static attribute will set the number of prints each type pf worker will do.
    */
	static int maxPilotPrintsInTakeoffAndLandingOrPreparingPlane;
	static int maxTechnicianPrintsInTakeOffOrLanding;
	static int maxFlightAttendetPrintsInTakeOffOrLanding;
	static int maxFlightAttendetsPreparingPlane;
	static int maxTechnicianPreparingPlane;
	

	static const float PRECENTAGE_OF_FIRST_CLASS_TICKETS;
	static const float FIRST_CLASS_COST_PRECENT;
	static const string DEFAULT_FLIGHT_MEAL;

	static const int MIN_PILOTS = 1;
	static const int MIN_TECHNICHIAN = 2;
	static const int MIN_FLIGHT_ATTENDENT = 2;
	static const int MIN_TICKETS = 2;

	AirLine& airLine; 
	
	int flightNumber;
	TripInfo info;
	Time boardingTime;
	
	Plane* pPlane;

	int currentPurchasedTickets;
	Ticket** ticketArr;
	
	Worker* crewMembers[MAX_CREW_MEMBERS];
	int currentNumOfCrewMembers;
	
	vector<string> firstClassMenuVec;
	string meal;
	
	bool addCrewMember(Worker* w);
	void createTickets(int ticketCost = DEFAULT_COST, int gate = DEFAULT_GATE);

public:

	/*Flight(char* destination, char* source, 
		int durHour, int durMinute, int borHour, int borMinute, 
		int day, int month, int year, Plane* plane = nullptr,
		int ticketCost = 20, int gate = 1, const char* meal = nullptr);*/

	Flight(const Travel & trav, const Date& d, 
			const Time& durTime, const Time& borTime, Plane* plane = nullptr,
		int ticketCost = 20, int gate = 1, const string& meal = "");

	Flight(const Flight& f);

	~Flight();

	//read and save to file
	Flight(ifstream& in); 
	void saveToFile(ofstream& out)const;

	int				getFlightNumber()const;
	const Time&		getDuration()const;
	const TripInfo& getInfo()const;
	Plane*			getPlane()const;
	int				getNumOfcurrentPurchasedTickets()const;
	int             getCurrentNumOfCrewMembers()const;
	int				getNumOfTickets()const; //number of seats in plane

	Ticket**		getTicketArray()const;
	Worker**        getCrew()const;
	void			showFirstClassMenu(ostream& out)const;
	void			showMainMeal(ostream& out)const;

	bool operator ==(const Flight& f)const;
	bool operator = (const Flight& f);
	friend ostream& operator <<(ostream& out, const Flight& f);
	
	bool setPlane(Plane* pl);
	bool setDuration(const Time& t);
	Ticket* setTicketToPassenger(Passenger* p, ostream& out);
	void setMeal(const string& pMeal);
	void assignCrew(vector<Worker*> workers);
	bool checkIfFlightReady(ostream& out) const;
	bool addDishToMenu(const string& dish);
	bool isMealInMenu(const string& pMeal) const;
	bool areThereEnoughPurchasedTickets()const;
	bool setMainMealToFlight(const string& pMeal);
	int numOfavaiableTickets()const;
	bool checkCrewTypes()const;
	bool checkAddCrewMember(Worker* w);
	bool isPassengerInFlight(const Passenger* p) const;

	void crewPreparations(ostream& out);
	void boarding(ostream& out);
	void takeoff(ostream& out);
	void landing(ostream& out);
	
	void resetPrints();
	



};



