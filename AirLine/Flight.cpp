#include "Flight.h"
#include "Ticket.h"
#include "Passenger.h"


Flight::Flight(AirLine* myAirLine, char destination[MAX_CHAR_CODE], char source[MAX_CHAR_CODE], int durHour, int durMinute, int borHour, int borMinute,
				int day, int month, int year, Plane* plane, int ticketCost, int gate, char* meal)
	: airLine(myAirLine), flightNumber(flightNumberGen++), info(destination, source, durHour, durMinute, day, month, year),
		boardingTime(borHour, borMinute), currentPurchasedTickets(0), currentNumOfCrewMembers(0), pPlane(plane), ticketArr(nullptr),
		crewMembers(nullptr)
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
	currentNumOfCrewMembers(0), pPlane(plane), ticketArr(nullptr), crewMembers(nullptr)
{
	if (plane != nullptr)
	{
		createTickets(ticketCost, gate);
	}
}

Flight::Flight(AirLine* myAirLine, const TripInfo& t, Plane* plane = nullptr, int ticketCost = 20, int gate = 1, char* meal = nullptr)
	: airLine(myAirLine), flightNumber(flightNumberGen++), info(t), currentPurchasedTickets(0), 
	currentNumOfCrewMembers(0), pPlane(plane), ticketArr(nullptr), crewMembers(nullptr)
{
	if (plane != nullptr)
	{
		int numOfSeats = plane->getNumOfSeats();
		createTickets(ticketCost, gate);
	}
}

Flight::Flight(AirLine* myAirLine, ostream& out, istream& in)
	: airLine(myAirLine), info(out, in), currentPurchasedTickets(0), 
	currentNumOfCrewMembers(0), pPlane(nullptr), ticketArr(nullptr), crewMembers()
{
	// Create Plane object
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
		setPlane(airLine->choosePlane();
	}

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
	return pPlane->getNumOfSeats();
}

Ticket** Flight::getTicketArray() const
{
	return ticketArr;
}

bool Flight::operator=(const Flight& f)
{
	if (this == &f)
		return false;

	flightNumber = f.flightNumber;
	info = f.info;

	//in the copied flight the tickets are not taken!!!
	currentPurchasedTickets = 0;

	if (pPlane != nullptr)
		delete pPlane;

	pPlane = f.pPlane;

	if (ticketArr != nullptr)
	{
		for (int i = 0; i < pPlane->getNumOfSeats(); i++)
		{
			delete ticketArr[i];
		}
		delete[] ticketArr;
	}

	if (f.ticketArr != nullptr)
	{
		ticketArr = new Ticket * [pPlane->getNumOfSeats()];
		createTickets( ticketArr[0]->getPrice(), ticketArr[0]->getGateNumber() );
	}

	if (crewMembers != nullptr) //not deleting the members but not disconnecting them 
		for (int i = 0; i < currentNumOfCrewMembers; i++)
			crewMembers[i] = nullptr;
		
	currentNumOfCrewMembers = f.currentNumOfCrewMembers;
	
	for (int i = 0; i < currentNumOfCrewMembers; i++) //assigning pointer = pointer
		crewMembers[i] = f.crewMembers[i];


	return true;
}

ostream& operator<<(ostream& out, const Flight& f)
{
	out << "Flight Number: " << f.flightNumber << endl;
	out << f.info;
	out << "Current Purchased Tickets: " << f.currentPurchasedTickets << endl;
	out << "Current Number of Crew Members: " << f.currentNumOfCrewMembers << endl;

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
	info.setDuration(t);
	return true;
}

bool Flight::addCrewMember(Worker* w)
{
	if (currentNumOfCrewMembers >= MAX_CREW_MEMBERS)
		return false;

	crewMembers[currentNumOfCrewMembers] = w->clone();
	currentNumOfCrewMembers++;

	return true;
}



bool Flight::assignCrew(ostream& out, istream& in)
{
	int choose;
	do 
	{
		out << "Please choose: \nadd crew member - 0";
		out << "\ndon't add crew member right now - 1" << endl;
		in.ignore(); // Ignore the newline character
		in >> choose;
		if (choose == 0)
		{
			crewMembers[currentNumOfCrewMembers] = airLine->chooseWorker();
			currentNumOfCrewMembers++;
		}

	}while(choose == 0)
}

bool Flight::assignCrew(Worker** workers, int workersSize)
{
	if (currentNumOfCrewMembers + workersSize > MAX_CREW_MEMBERS)
	{
		cout << "Maximum number of crew members reached." << endl;
		return false;
	}

	for (int i = 0; i < workersSize; i++)
	{
		crewMembers[currentNumOfCrewMembers] = workers[i]->clone();
		currentNumOfCrewMembers++;
	}

	return true;
}

bool Flight::checkIfFlightReady()
{
	if (currentNumOfCrewMembers < 2)
		return false;

	if (currentPurchasedTickets == 0)
		return false;

	return true;
}
