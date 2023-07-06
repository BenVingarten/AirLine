#include "AirLine.h"


//Privates

void AirLine::boarding()
{
}

void AirLine::takeoff()
{
}

void AirLine::landing()
{
}

void AirLine::checkReady()
{
}

AirLine::AirLine(const char* name, const char* country) : 
	currentNumOfFlight(0), currentNumOfPassengers(0), currentNumOfPlanes(0), currentNumOfWorkers(0),
	allWorkers(nullptr), allFlights(nullptr), allPlanes(nullptr), allPassengers(nullptr), 
	income(0)
{
	name = _strdup(name);
	country = _strdup(country);
}



//Publics

AirLine& AirLine::getInstance(const char* name, const char* country)
{
	if (theAirLine == nullptr)
		theAirLine = new AirLine(name, country);

}

void AirLine::releaseInstance()
{
	delete theAirLine;
	theAirLine = nullptr;
}

AirLine::~AirLine()
{
	for (int i = 0; i < currentNumOfFlight; ++i)
		delete allFlights[i];
	delete[] allFlights;

	for (int i = 0; i < currentNumOfWorkers; ++i)
		delete allWorkers[i];
	delete[] allWorkers;
	
	for (int i = 0; i < currentNumOfPassengers; ++i)
		delete allPassengers[i];
	delete[] allPassengers;

	for (int i = 0; i < currentNumOfPlanes; ++i)
		delete allPlanes[i];
	delete[] allPlanes;

	delete[] name; 
	delete[] country;


}

bool AirLine::addWorker(Worker& w)
{
	// Check if the worker already exists in the workers vector
	if (isWorkerExist(w))
		return false;

	// Add the worker to the workers array
	allWorkers[currentNumOfWorkers++] = &w;
	

	return true;
}

bool AirLine::addFlight(Flight& f)
{
	return false;
}

bool AirLine::addPlane(Plane& p)
{
	return false;
}

bool AirLine::addPassenger(Passenger* p)
{
	return false;
}

void AirLine::printFlights() const
{
}

void AirLine::printWorkers() const
{
}

void AirLine::printPlanes() const
{
}

void AirLine::printPassengers() const
{
}

void AirLine::removeWorker()
{
}

void AirLine::removeFlight()
{
}

void AirLine::removePlane()
{
}

void AirLine::removePassenger()
{
}

Plane* AirLine::choosePlane() const
{
	return nullptr;
}

Worker* AirLine::chooseWorker() const
{
	return nullptr;
}

Flight* AirLine::chooseFlight() const
{
	return nullptr;
}

Passenger* AirLine::choosePassenger() const
{
	return nullptr;
}

bool AirLine::isWorkerExist(const Worker& w) const
{
	for (int i = 0; i < currentNumOfWorkers; ++i)
	{
		if (*allWorkers[i] == w)
		{
			// Worker with the same ID already exists
			return true;
		}
	}
	return false;
}

bool AirLine::isFlightExist(const Flight& f) const
{
	for (int i = 0; i < currentNumOfFlight; ++i)
	{
		if (*allFlights[i] == f)			//TODO   CREATE == in flight by flight ID 
		{
			// Flight with the same flight number already exists
			return true;
		}
	}
	return false;
}

bool AirLine::isPlaneExist(const Plane& p) const
{
	return false;
}

bool AirLine::isPassengerExist(const Passenger& p) const
{
	return false;
}

float AirLine::executeFlight(Flight& f)
{
	return 0.0f;
}

bool AirLine::buyTicket()
{
	return false;
}

void AirLine::yearPassed()
{
}

void AirLine::readPassengersFromFile(ifstream& in)
{
}

void AirLine::readWorkersFromFile(ifstream& in)
{
}

void AirLine::readFlightsFromFile(ifstream& in)
{
}

void AirLine::readPlanesFromFile(ifstream& in)
{
}

void AirLine::savePassengersFromFile(ofstream& out)
{
}

void AirLine::saveWorkersFromFile(ofstream& out)
{
}

void AirLine::saveFlightsFromFile(ofstream& out)
{
}

void AirLine::savePlanesFromFile(ofstream& out)
{
}

ostream& operator<<(ostream& out, const AirLine& al)
{
	// TODO: insert return statement here
}
