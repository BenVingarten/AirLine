#include <typeinfo>
#include "Flight.h"
#include "Ticket.h"
#include "Passenger.h"
#include "FlightAttendet.h"



Flight::Flight(AirLine* myAirLine, char destination[MAX_CHAR_CODE], char source[MAX_CHAR_CODE], int durHour, int durMinute, int borHour, int borMinute,
				int day, int month, int year, Plane* plane, int ticketCost, int gate, char* meal)
	: airLine(myAirLine), flightNumber(flightNumberGen++), info(destination, source, durHour, durMinute, day, month, year),
		boardingTime(borHour, borMinute), currentPurchasedTickets(0), currentNumOfCrewMembers(0), pPlane(plane), ticketArr(nullptr),
		crewMembers(), numberOfDishes(0)
{
	if (plane != nullptr)
	{
		createTickets(ticketCost, gate);
		
	}
}

void Flight::createTickets(int ticketCost, int gate)
{

	FirstClassTicket tmp(ticketCost, gate, boardingTime, &info, 0, this);
	int numOfSeats = pPlane->getNumOfSeats();

	for (int i = 0; i < numOfSeats; i++)
	{
		if (i < PRECENTAGE_OF_FIRST_CLASS_TICKETS * numOfSeats) //30 precent from all tickets
			ticketArr[i] = new FirstClassTicket(tmp);
		else
			ticketArr[i] = new Ticket(tmp);
		
		ticketArr[i]->setSeat(i + 1);

	}
}

Flight::Flight(AirLine* myAirLine, const Travel& trav, const Date& d, const Time& time, Plane* plane = nullptr,
				int ticketCost = 20, int gate = 1, char* meal = nullptr)
	: airLine(myAirLine), flightNumber(flightNumberGen++), info(d, trav, time), currentPurchasedTickets(0), 
	currentNumOfCrewMembers(0), pPlane(plane), ticketArr(nullptr), crewMembers(), numberOfDishes(0)
{
	if (plane != nullptr)
	{
		createTickets(ticketCost, gate);
	}
}

Flight::Flight(AirLine* myAirLine, const TripInfo& t, Plane* plane = nullptr, int ticketCost = 20, int gate = 1, char* meal = nullptr)
	: airLine(myAirLine), flightNumber(flightNumberGen++), info(t), currentPurchasedTickets(0), 
	currentNumOfCrewMembers(0), pPlane(plane), ticketArr(nullptr), crewMembers(), numberOfDishes(0)
{
	if (plane != nullptr)
	{
		int numOfSeats = plane->getNumOfSeats();
		createTickets(ticketCost, gate);
	}
}

Flight::Flight(AirLine* myAirLine, ostream& out, istream& in)
	: airLine(myAirLine), info(out, in), currentPurchasedTickets(0), 
	currentNumOfCrewMembers(0), pPlane(nullptr), ticketArr(nullptr), crewMembers(), numberOfDishes(0)
{
	// Create Plane object
	setPlane(airLine->interactiveAddPlane(out, in));

	//create tickets 
	int ticketCost, gate;
	
	out << "Enter ticket cost: " << endl;
	in.ignore(); // Ignore the newline character
	in >> ticketCost;

	out << "Enter gate number: " << endl;
	in.ignore(); // Ignore the newline character
	in >> gate;

	createTickets(ticketCost, gate);

	//crew members
	assignCrew(out, in);
	
	//flight Numebr
	flightNumber = flightNumberGen++;
	

}

Flight::~Flight()
{
	//tickets are created for the flight so they will be deleted with the flight
	if (ticketArr != nullptr)
	{
		for (int i = 0; i < pPlane->getNumOfSeats(); i++)
		{
			delete ticketArr[i];
		}
		delete[] ticketArr;
	}
	
	//we save the workers in the airline database so we don't delete them when flight is deleted
	delete[] crewMembers; 
	
}

int Flight::getFlightNumber() const
{
	return flightNumber;
}

const Time& Flight::getDuration() const
{
	return info.getFlightDuration();
}

const TripInfo& Flight::getInfo() const
{
	return info;
}

Plane* Flight::getPlane() const
{
	return pPlane;
}

int Flight::getNumOfcurrentPurchasedTickets() const
{
	return currentPurchasedTickets;
}

int Flight::getNumOfTickets() const
{
	//number of tickets as number of seats 
	return pPlane->getNumOfSeats();
}

Ticket** Flight::getTicketArray() const
{
	return ticketArr;
}

bool Flight::operator=(const Flight& f)
{
	/*
	* We copy the dry details of flight
	* Copied: airLine, info, boarding time, meal, first class menu, number of dishes
	* Not Copied: flight number, current purchased tickets, crew members, plane, tickets 
	*/

	if (this == &f)
		return false;

	flightNumber = flightNumberGen++;
	
	airLine = f.airLine;
	info = f.info;
	boardingTime = f.boardingTime;
	meal = _strdup(f.meal);
	
	numberOfDishes = f.numberOfDishes;
	for (int i = 0; i < numberOfDishes; i++)
	{
		firstClassMenu[i] = _strdup(f.firstClassMenu[i]);
	}


	return true;
}

ostream& operator<<(ostream& out, const Flight& f)
{
	out << "Flight Number: " << f.flightNumber << endl;
	out << f.info;
	out << "Boarding Time: " << f.boardingTime << endl;
	out << "Current Purchased Tickets: " << f.currentPurchasedTickets << endl;
	out << "Current Number of Crew Members: " << f.currentNumOfCrewMembers << endl;
	if(f.meal != nullptr)
		out << "Standart meal: " << f.meal << endl;
	if(f.numberOfDishes == 0)
		out << "No dishes in first class menu " << endl;
	else
	{
		out << "First Class Menu: " << endl;
		for (int i = 0; i < f.numberOfDishes; ++i)
			out << (i+1) <<") " << f.currentPurchasedTickets << endl;
		
	}

	return out;
}

bool Flight::setPlane(Plane* pl)
{
	if (pPlane != nullptr)
		delete pPlane;

	pPlane = pl;

	return true;
}

bool Flight::setDuration(const Time& t)
{
	info.setDuration(t.getHours(), t.getMinutes());
	return true;
}

bool Flight::addCrewMember(Worker* w)
{
	if (currentNumOfCrewMembers >= MAX_CREW_MEMBERS)
		return false;

	

	if (w->isAvailable() && checkAddCrewMember(w))
	{
		crewMembers[currentNumOfCrewMembers] = w;
		currentNumOfCrewMembers++;
		return true;
	}

	return false;
}



void Flight::assignCrew(ostream& out, istream& in)
{
	int choose;
	Worker* w;
	do 
	{
		out << "Please choose: \nadd crew member - 0";
		out << "\nadd new crew member - 1" << endl;
		out << "\ndon't add crew member right now - 2" << endl;
		in.ignore(); // Ignore the newline character
		in >> choose;
		if (choose == 0)
			w = airLine->chooseWorker();
		else if (choose == 1)
			w = airLine->interactiveAddWorker(out, in);

		addCrewMember(w);

	} while (choose != 2);


}



bool Flight::checkIfFlightReady()
{
	return (
			checkCrewTypes() && //check crew members 
			currentPurchasedTickets >= MIN_TICKETS && //check tickets purchased 
			pPlane->isReadyToFly() //check plane is ready 
			);
}


//moving to the AirLine
void Flight::interactiveSetPlane(ostream& out, istream& in)
{
	

	out << "Please choose: New plane - 0 | Existing plane - 1" << endl;
	in.ignore(); // Ignore the newline character
	int choose;
	in >> choose;
	if (choose == 0)
	{
		pPlane = new Plane(out, in);
		airLine->addPlane(*pPlane);
	}
	else
	{
		setPlane(airLine->choosePlane());
	}
}



bool Flight::checkCrewTypes()
{
	return (
			workersOfType[0] >= MIN_PILOTS &&
			workersOfType[1] >= MIN_TECHNICHIAN &&
			workersOfType[0] >= MIN_FLIGHT_ATTENDENT
			);
}

bool Flight::checkAddCrewMember(Worker* w)
{
	if (strcmp(typeid(*w).name(), typeid(Pilot).name()) == 0)
	{
		if (workersOfType[0] < 2)
		{
			workersOfType[0]++;
			return true;
		}
		return false;


	}

	else if (strcmp(typeid(*w).name(), typeid(Technician).name()) == 0)
	{
		if (workersOfType[1] < 4)
		{
			workersOfType[1]++;
			return true;
		}
		return false;
	}

	else // flight attendent
	{
		if (workersOfType[2] < 4)
		{
			workersOfType[2]++;
			return true;
		}
		return false;
	}
}

void Flight::assignCrew(Worker** workers, int workersSize)
{
	for (int i = 0; i < workersSize; ++i)
		addCrewMember(workers[i]);
}


