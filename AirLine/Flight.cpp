#include <typeinfo>
#include <fstream>
#include "Flight.h"
#include "Ticket.h"
#include "Passenger.h"
#include "FlightAttendet.h"

//Initializing
int Flight::flightNumberGen = 4444;
int Flight::workersOfType[3] = { 0, 0, 0 };

const float Flight::PRECENTAGE_OF_FIRST_CLASS_TICKETS = 0.3;
const float Flight::FIRST_CLASS_COST_PRECENT = 1.5;
const char* Flight::DEFAULT_FLIGHT_MEAL = "Chicken";


Flight::Flight(AirLine& myAirLine, char* destination, char* source,
	int durHour, int durMinute, int borHour, int borMinute,
	int day, int month, int year, Plane* plane,
	int ticketCost, int gate, const char* meal)
	: airLine(myAirLine), flightNumber(flightNumberGen++), 
		info(destination, source, durHour, durMinute, day, month, year),
		boardingTime(borHour, borMinute), currentPurchasedTickets(0), 
		currentNumOfCrewMembers(0), pPlane(plane), ticketArr(nullptr),
		numberOfDishesInMenu(0)
{
	if (plane != nullptr)
		createTickets(ticketCost, gate);

	
	if (meal != nullptr)
		setMainMealToFlight(meal);
	else
		setMainMealToFlight(DEFAULT_FLIGHT_MEAL);

}



Flight::Flight(AirLine& myAirLine, const Travel& trav, const Date& d,
	const Time& durTime, const Time& borTime, Plane* plane, int ticketCost,
	int gate, const char* meal)
	: airLine(myAirLine), flightNumber(flightNumberGen++), info(d, trav, durTime), boardingTime(borTime),
		currentPurchasedTickets(0), currentNumOfCrewMembers(0), pPlane(plane), 
		ticketArr(nullptr), numberOfDishesInMenu(0)
{
	if (plane != nullptr)
		createTickets(ticketCost, gate);


	if (meal != nullptr)
		setMainMealToFlight(meal);
	else
		setMainMealToFlight(DEFAULT_FLIGHT_MEAL);
}


Flight::Flight(AirLine& myAirLine, ifstream& in)
	: airLine(myAirLine), info(in), boardingTime(in)
{
	
	in >> flightNumber;
	
	char tmp[MAX_NAME_LEN];
	
	in.getline(tmp, MAX_NAME_LEN);
	meal = new char[strlen(tmp) + 1];
	strcpy(meal, tmp);

	in >> numberOfDishesInMenu;
	for (int i = 0; i < numberOfDishesInMenu; ++i)
	{
		in.getline(tmp, MAX_NAME_LEN);
		firstClassMenu[i] = new char[strlen(tmp) + 1];
		strcpy(firstClassMenu[i], tmp);
		
	}
	
}

void Flight::saveToFile(ofstream& out) const 
{
	info.saveToFile(out);
	boardingTime.saveToFile(out);
	out << flightNumber << endl;

	out << meal << endl;
	out << numberOfDishesInMenu << endl;
	for (int i = 0; i < numberOfDishesInMenu; ++i)
	{
		out << firstClassMenu[i] << endl;
	}

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
	// also the array is allocated on the stack, so we dont need to delete it as well
	
}


//Get and Show

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

void Flight::showMainMeal(ostream& out) const
{
	out << "Plane Main Meal is: " << meal << endl;
}

void Flight::showFirstClassMenu(ostream& out) const
{
	out << "First Class Menu: " << endl;
	for (int i = 0; i < numberOfDishesInMenu; ++i)
		out << (i + 1) << ") " << firstClassMenu[i] << endl;
	if (numberOfDishesInMenu == 0)
		out << "No extra dishes for first class on this flight." << endl;
}


//Operators, Set and Check

bool Flight::operator==(const Flight& f)const
{
	return flightNumber == f.flightNumberGen;
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
	info = f.info;
	boardingTime = f.boardingTime;
	
	//Deep copy meal
	setMeal(f.meal);
	

	//Deep copy menu
	numberOfDishesInMenu = f.numberOfDishesInMenu;
	for (int i = 0; i < numberOfDishesInMenu; i++)
	{
		firstClassMenu[i] = new char[strlen(f.firstClassMenu[i]) + 1];
		strcpy(firstClassMenu[i], f.firstClassMenu[i]);
	}

	f.airLine.addFlight(*this); // cannot do myReference = other.Reference therefore we add the AirlineRef from Airline
	//TODO: To check if working ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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

	f.showFirstClassMenu(out);
	return out;
}

bool Flight::setPlane(Plane* pl)
{
	if (pl == nullptr)
		return false;

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

bool Flight::setMeal(const char* pMeal)
{
	if (pMeal == nullptr)
		return false;

	if (meal != nullptr)
		delete meal;
	
	meal = new char[strlen(pMeal) + 1];
	strcpy(meal, pMeal);
	return true;
}

bool Flight::addCrewMember(Worker* w)
{
	if (currentNumOfCrewMembers >= MAX_CREW_MEMBERS)
		return false;

	

	if (w->isAvailable() && checkAddCrewMember(w))
		// no need to check if the worker is already in crew,
		// because if he does, then he is no loger available.
	{
		crewMembers[currentNumOfCrewMembers] = w;
		currentNumOfCrewMembers++;
		w->setFlight(this); // if this is technicain will also increase number of planes prepeard because: setFlight is virtual
		w->changeAvailability();

		return true;
	}

	return false;
}

bool Flight::addDishToMenu(const char* dish)
{
	if(numberOfDishesInMenu >= MAX_DISHES)
		return false;

	if (isMealInMenu(dish))
		return false;

	firstClassMenu[numberOfDishesInMenu] = new char[strlen(dish) + 1];
	strcpy(firstClassMenu[numberOfDishesInMenu], dish);
	numberOfDishesInMenu++;
	return true;
	
	
}

bool Flight::isMealInMenu(const char* pMeal) const
{
	if (firstClassMenu == nullptr)
		return false;

	for (int i = 0; i < numberOfDishesInMenu; i++)
		if (strcmp(firstClassMenu[i], pMeal) == 0)
			return true;

	return false;
}

bool Flight::checkIfFlightReady()
{
	return (
		checkCrewTypes() && //check crew members 
		currentPurchasedTickets >= MIN_TICKETS && //check tickets purchased 
		pPlane->isReadyToFly() //check plane is ready 
		);
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

bool Flight::setMainMealToFlight(const char* pMeal)
{
	if (strcmp(pMeal,meal) == 0 )
		return false;

	if (pMeal == nullptr)
		setMeal(DEFAULT_FLIGHT_MEAL);

	else
		setMeal(pMeal);

	return true;
}

void Flight::assignCrew(Worker** workers, int workersSize)
{
	for (int i = 0; i < workersSize; ++i)
		addCrewMember(workers[i]);
}

void Flight::createTickets(int ticketCost, int gate)
{

	FirstClassTicket tmp = FirstClassTicket(ticketCost, gate, boardingTime, &info, 0, *this);

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
