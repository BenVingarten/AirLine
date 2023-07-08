#define _CRT_SECURE_NO_WARNINGS
#include "AirLine.h"
#include <fstream>

#include "FlightAttendet.h"
#include "Pilot.h"
#include "Technician.h"
#include "WorkerPassenger.h"



//Privates


bool AirLine::checkReady(Flight& f, ostream& out)
{
	if (f.checkIfFlightReady(out))
	{
		out << "The plane is available and fuled!" << endl;
		out << "Enough tickets have been purchased" << endl;
		out << "crew members are in position, and prepared the plane" << endl;
	}
	else
		return false;
}

AirLine::AirLine(const char* pName, const char* pCountry) : 
	currentNumOfFlights(0), currentNumOfPassengers(0), currentNumOfPlanes(0), currentNumOfWorkers(0),
	allWorkers(nullptr), allFlights(nullptr), allPlanes(nullptr), allPassengers(nullptr), 
	income(0)
{
	name = new char[strlen(pName) + 1];
	strcpy(name, pName);

	country = new char[strlen(pCountry) + 1];
	strcpy(country, pCountry);

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
	for (int i = 0; i < currentNumOfFlights; ++i)
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
	// Check if the worker already exists in the workers array
	if (isWorkerExist(w) != -1)
		return false;

	// If reached maximum Workers
	if (currentNumOfWorkers == MAX_WORKERS)
		return false;

	// Check if there is space at the end of the array
	int arrSize = sizeof(allWorkers) / sizeof(Worker*);
	
	if (currentNumOfWorkers < arrSize)
	{
		allWorkers[currentNumOfWorkers++] = &w;
		return true;
	}

	// Extend the array by creating a new array with double the capacity
	int newCapacity = 2 * currentNumOfWorkers;
	if (newCapacity > MAX_WORKERS)
		newCapacity = MAX_WORKERS;

	Worker** newWorkers = new Worker* [newCapacity];

	// Copy the existing workers into the new array
	for (int i = 0; i < currentNumOfWorkers; ++i)
	{
		newWorkers[i] = allWorkers[i];
	}

	// Add the new worker to the extended array
	newWorkers[currentNumOfWorkers] = &w;

	// Delete the old workers array and update the pointer to the new array
	delete[] allWorkers;
	allWorkers = newWorkers;
	currentNumOfWorkers = newCapacity;

	return true;
}

bool AirLine::addFlight(Flight& f)
{
	// Check if the flight already exists in the flights array
	if (isFlightExist(f) != -1)
		return false;

	// Check if there is space at the end of the array
	int arrSize = sizeof(allFlights) / sizeof(Flight*);
	if (currentNumOfFlights < arrSize)
	{
		allFlights[currentNumOfFlights++] = &f;
		return true;
	}

	// If reached the maximum number of flights
	if (currentNumOfFlights == MAX_FLIGHTS)
		return false;

	// Extend the array by creating a new array with double the capacity
	int newCapacity = 2 * currentNumOfFlights;
	if (newCapacity > MAX_FLIGHTS)
		newCapacity = MAX_FLIGHTS;

	Flight** newFlights = new Flight * [newCapacity];

	// Copy the existing flights into the new array
	for (int i = 0; i < currentNumOfFlights; ++i)
	{
		newFlights[i] = allFlights[i];
	}

	// Add the new flight to the extended array
	newFlights[currentNumOfFlights] = &f;

	// Delete the old flights array and update the pointer to the new array
	delete[] allFlights;
	allFlights = newFlights;
	currentNumOfFlights = newCapacity;
	return true;
}

bool AirLine::addPlane(Plane& p)
{
	// Check if the plane already exists in the planes array
	if (isPlaneExist(p) != -1)
		return false;

	// Check if there is space at the end of the array
	int arrSize = sizeof(allPlanes) / sizeof(Plane*);
	if (currentNumOfPlanes < arrSize)
	{
		allPlanes[currentNumOfPlanes++] = &p;
		return true;
	}

	// If reached the maximum number of planes
	if (currentNumOfPlanes == MAX_PLANES)
		return false;

	// Extend the array by creating a new array with double the capacity
	int newCapacity = 2 * currentNumOfPlanes;
	if (newCapacity > MAX_PLANES)
		newCapacity = MAX_PLANES;

	Plane** newPlanes = new Plane * [newCapacity];

	// Copy the existing planes into the new array
	for (int i = 0; i < currentNumOfPlanes; ++i)
	{
		newPlanes[i] = allPlanes[i];
	}

	// Add the new plane to the extended array
	newPlanes[currentNumOfPlanes] = &p;

	// Delete the old planes array and update the pointer to the new array
	delete[] allPlanes;
	allPlanes = newPlanes;
	currentNumOfPlanes = newCapacity;

	return true;
}

bool AirLine::addPassenger(Passenger* p)
{
	// Check if the passenger already exists in the passengers array
	if (isPassengerExist(*p) != -1)
		return false;

	// Check if there is space at the end of the array
	int arrSize = sizeof(allPassengers) / sizeof(Passenger*);
	if (currentNumOfPassengers < arrSize)
	{
		allPassengers[currentNumOfPassengers++] = p;
		return true;
	}

	// If reached the maximum number of passengers
	if (currentNumOfPassengers == MAX_PASSENGERS)
		return false;

	// Extend the array by creating a new array with double the capacity
	int newCapacity = 2 * currentNumOfPassengers;
	if (newCapacity > MAX_PASSENGERS)
		newCapacity = MAX_PASSENGERS;

	Passenger** newPassengers = new Passenger* [newCapacity];

	// Copy the existing passengers into the new array
	for (int i = 0; i < currentNumOfPassengers; ++i)
	{
		newPassengers[i] = allPassengers[i];
	}

	// Add the new passenger to the extended array
	newPassengers[currentNumOfPassengers] = p;

	// Delete the old passengers array and update the pointer to the new array
	delete[] allPassengers;
	allPassengers = newPassengers;
	currentNumOfPassengers = newCapacity;
	return true;
}



void AirLine::printFlights(ostream& out) const
{
	out << "Flights:" << endl;

	for (int i = 0; i < currentNumOfFlights; ++i)
	{
		out << (i + 1) << ")" << *allFlights[i] << endl;
	}
}

void AirLine::printWorkers(ostream& out) const
{
	out << "Workers:" << endl;

	for (int i = 0; i < currentNumOfWorkers; ++i)
	{
		out << (i+1) << ")" << *allWorkers[i] << endl;
	}
}

void AirLine::printPlanes(ostream& out) const
{
	out << "Planes:" << endl;

	for (int i = 0; i < currentNumOfPlanes; ++i)
	{
		out << (i + 1) << ")" << *allPlanes[i] << endl;
	}
}

void AirLine::printPassengers(ostream& out) const
{
	out << "Passengers:" << endl;

	for (int i = 0; i < currentNumOfPassengers; ++i)
	{
		out << (i + 1) << ")" << *allPassengers[i] << endl;
	}
}



void AirLine::removeWorker(Worker& w)
{
	// Check if the worker exists in the workers array
	int index = isWorkerExist(w);
	if (index == -1)
		return;

	delete allWorkers[index];

	// If the worker to be removed is not the last worker, replace it with the last worker
	if (index != currentNumOfWorkers - 1)
	{
		allWorkers[index] = allWorkers[currentNumOfWorkers - 1];
	}

	// Delete the removed worker
	delete allWorkers[currentNumOfWorkers - 1];
	allWorkers[currentNumOfWorkers - 1] = nullptr;

	// Decrement the current number of workers
	--currentNumOfWorkers;
}

void AirLine::removeFlight(Flight& f)
{
	// Check if the flight exists in the flights array
	int index = isFlightExist(f);
	if (index == -1)
		return;

	delete allFlights[index];

	// If the flight to be removed is not the last flight, replace it with the last flight
	if (index != currentNumOfFlights - 1)
	{
		allFlights[index] = allFlights[currentNumOfFlights - 1];
	}

	// Delete the removed flight
	delete allFlights[currentNumOfFlights - 1];
	allFlights[currentNumOfFlights - 1] = nullptr;

	// Decrement the current number of flights
	--currentNumOfFlights;
}

void AirLine::removePlane(Plane& p)
{
	// Check if the plane exists in the planes array
	int index = isPlaneExist(p);
	if (index == -1)
		return;

	delete allPlanes[index];

	// If the plane to be removed is not the last plane, replace it with the last plane
	if (index != currentNumOfPlanes - 1)
	{
		allPlanes[index] = allPlanes[currentNumOfPlanes - 1];
	}

	// Delete the removed plane
	delete allPlanes[currentNumOfPlanes - 1];
	allPlanes[currentNumOfPlanes - 1] = nullptr;

	// Decrement the current number of planes
	--currentNumOfPlanes;
}

void AirLine::removePassenger(Passenger& p)
{
	// Check if the passenger exists in the passengers array
	int index = isPassengerExist(p);
	if (index == -1)
		return;

	delete allPassengers[index];

	// If the passenger to be removed is not the last passenger, replace it with the last passenger
	if (index != currentNumOfPassengers - 1)
	{
		allPassengers[index] = allPassengers[currentNumOfPassengers - 1];
	}

	// Delete the removed passenger
	delete allPassengers[currentNumOfPassengers - 1];
	allPassengers[currentNumOfPassengers - 1] = nullptr;

	// Decrement the current number of passengers
	--currentNumOfPassengers;
}



Plane* AirLine::choosePlane(ostream& out, istream& in) const
{
	// Print all planes
	printPlanes(out);

	int choice;
	out << "Enter the number of the plane you want: ";
	in >> choice;

	// Validate the input
	if (choice < 1 || choice > currentNumOfPlanes)
	{
		out << "Invalid choice. Please try again." << endl;
		return nullptr;
	}

	// Return the selected plane
	return allPlanes[choice - 1];
}

Worker* AirLine::chooseWorker(ostream& out, istream& in) const
{
	// Print all workers
	printWorkers(out);

	int choice;
	out << "Enter the number of the worker you want: ";
	in >> choice;

	// Validate the input
	if (choice < 1 || choice > currentNumOfWorkers)
	{
		out << "Invalid choice. Please try again." << endl;
		return nullptr;
	}

	// Return the selected worker
	return allWorkers[choice - 1];
}

Flight* AirLine::chooseFlight(ostream& out, istream& in) const
{
	// Print all flights
	out << "Available Flights:" << endl;
	printFlights(out);

	int choice;
	out << "Enter the number of the flight you want: ";
	in >> choice;

	// Validate the input
	if (choice < 1 || choice > currentNumOfFlights)
	{
		out << "Invalid choice. Please try again." << endl;
		return nullptr;
	}

	// Return the selected flight
	return allFlights[choice - 1];
}

Passenger* AirLine::choosePassenger(ostream& out, istream& in) const
{
	// Print all passengers
	out << "Available Passengers:" << endl;
	printPassengers(out);

	int choice;
	out << "Enter the number of the passenger you want: ";
	in >> choice;

	// Validate the input
	if (choice < 1 || choice > currentNumOfPassengers)
	{
		out << "Invalid choice. Please try again." << endl;
		return nullptr;
	}

	// Return the selected passenger
	return allPassengers[choice - 1];
}



int AirLine::isWorkerExist(const Worker& w) const
{
	for (int i = 0; i < currentNumOfWorkers; ++i)
	{
		if (*allWorkers[i] == w)
		{
			// Worker with the same ID already exists
			return i;
		}
	}
	return -1;
}

int AirLine::isFlightExist(const Flight& f) const
{
	for (int i = 0; i < currentNumOfFlights; ++i)
	{
		if (*allFlights[i] == f)
		{
			// Flight with the same flight number already exists
			return i;
		}
	}
	return -1;
}

int AirLine::isPlaneExist(const Plane& p) const
{
	for (int i = 0; i < currentNumOfPlanes; ++i)
	{
		if (*allPlanes[i] == p)
		{
			// Plane with the same plane number already exists
			return i;
		}
	}
	return -1;
}

int AirLine::isPassengerExist(const Passenger& p) const
{
	for (int i = 0; i < currentNumOfPassengers; ++i)
	{
		if (*allPassengers[i] == p)
		{
			// Passenger with the same Passport already exists
			return i;
		}
	}
	return -1;
}



void AirLine::executeFlight(Flight& f, ostream& out)
{
	out << "Checking last  requirments..." << endl;
	if (checkReady(f, out))
		out << "Flight Is Ready!" << endl;
	else
	{
		out << "flight is not ready.... " << endl;
		return;
	}

	out << "Executing Flight: " << f.getFlightNumber() << " from " << f.getInfo().getSource() << " to " << f.getInfo().getDestenation() << endl;
	f.crewPreparations(out);
	f.resetPrints(); 

	f.boarding(out);
	out << "ready for takeoff" << endl;

	f.takeoff(out);
	f.resetPrints();

	out << " we have reached max speed of " << f.getPlane()->getMaxSpeed() << endl;
	out << " we have decreasing to  minimum speed of " << f.getPlane()->getMinSpeed() << endl;

	f.landing(out); 
	f.resetPrints();

	delete &f;
}

bool AirLine::buyTicket(Passenger& p, Flight& f, ostream& out)
{
	Ticket* t = f.setTicketToPassenger(p, out);
	if (t == nullptr)
		return false;

	income += t->getPrice();
	return true;
}

void AirLine::yearPassed(ostream& out)
{
	for (int i = 0; i < currentNumOfPassengers; i++)
		allPassengers[i]++;

	for (int i = 0; i < currentNumOfWorkers; i++)
	{
		allWorkers[i]++;
		allWorkers[i]->setRaise();
		allWorkers[i]->annualRefresh(out);
	}
}



void AirLine::readPassengersFromFile(ifstream& in)
{
	if (!in)
	{
		cout << "Failed to open file." << endl;
		return;
	}

	// Read the number of passengers from the file
	int numPassengers;
	in >> numPassengers;

	// Read passenger data and add them to the array
	for (int i = 0; i < numPassengers; ++i)
	{
		int passengerType;
		in >> passengerType;
		

		// Check the type of the worker and create a corresponding object
		Passenger* p = nullptr;
		if (passengerType == WORKER_PASSENGER)
			 p = new WorkerPassenger(in);
			
		
		else if (passengerType == PASSENGER)
			 p = new Passenger(in);
			
		addPassenger(p);

	}
}

void AirLine::readWorkersFromFile(ifstream& in)
{
	if (!in)
	{
		cout << "Failed to open file." << endl;
		return;
	}

	// Read the number of workers from the file
	int numWorkers;
	in >> numWorkers;
	in.ignore(); // Ignore the newline character

	// Read worker data from the file
	for (int i = 0; i < numWorkers; ++i)
	{
		int workerType;
		in >> workerType;

		// Check the type of the worker and create a corresponding object
		if (workerType == FLIGHT_ATTENDENT)
		{
			FlightAttendet* flightAttendant = new FlightAttendet(in);
			addWorker(*flightAttendant);
		}
		else if (workerType == PILOT)
		{
			Pilot* pilot = new Pilot(in);
			addWorker(*pilot);
		}
		else if (workerType == TECHNICHIAN)
		{
			Technician* technician = new Technician(in);
			addWorker(*technician);
		}
	}
}

void AirLine::readFlightsFromFile(ifstream& in)
{
	if (!in)
	{
		cout << "Failed to open file." << endl;
		return;
	}

	// Read the number of flights from the file
	int numFlights;
	in >> numFlights;

	// Read flight data and add them to the array
	for (int i = 0; i < numFlights; ++i)
	{
		Flight* flight = new Flight(*this, in);
		addFlight(*flight);
	}
}

void AirLine::readPlanesFromFile(ifstream& in)
{
	if (!in)
	{
		cout << "Failed to open file." << endl;
		return;
	}

	// Read the number of planes from the file
	int numPlanes;
	in >> numPlanes;

	// Read plane data and add them to the array
	for (int i = 0; i < numPlanes; ++i)
	{
		Plane* plane = new Plane(in);
		addPlane(*plane);
	}
}



void AirLine::savePassengersFromFile(ofstream& out)
{
	if (!out)
	{
		cout << "Failed to open file." << endl;
		return;
	}

	// Write the number of passengers to the file
	out << currentNumOfPassengers << endl;

	// Write passenger data to the file
	for (int i = 0; i < currentNumOfPassengers; ++i)
	{
		if (typeid(*allPassengers[i]) == typeid(WorkerPassenger))
			out << WORKER_PASSENGER << endl;
		else
			out << PASSENGER << endl;
		
		allPassengers[i]->saveToFile(out);
	}
}

void AirLine::saveWorkersFromFile(ofstream& out)
{
	if (!out)
	{
		cout << "Failed to open file." << endl;
		return;
	}

	// Write the number of workers to the file
	out << currentNumOfWorkers << endl;

	// Write worker data to the file
	for (int i = 0; i < currentNumOfWorkers; ++i)
	{

		// Check the type of the worker and call the corresponding saveToFile function
		if (typeid(*allWorkers[i]) == typeid(FlightAttendet))
		{
			out << FLIGHT_ATTENDENT << endl; // Write worker type
			FlightAttendet* flightAttendant = (FlightAttendet*)(allWorkers[i]);
			flightAttendant->saveToFile(out);
		}
		else if (typeid(*allWorkers[i]) == typeid(Pilot))
		{
			out << PILOT << endl; // Write worker type
			Pilot* pilot = (Pilot*)(allWorkers[i]);
			pilot->saveToFile(out);
		}
		else if (typeid(*allWorkers[i]) == typeid(Technician))
		{
			out << TECHNICHIAN << endl; // Write worker type
			Technician* technician = (Technician*)(allWorkers[i]);
			technician->saveToFile(out);
		}
		
	}
}

void AirLine::saveFlightsFromFile(ofstream& out)
{
	if (!out)
	{
		cout << "Failed to open file." << endl;
		return;
	}

	// Write the number of flights to the file
	out << currentNumOfFlights << endl;

	// Write flight data to the file
	for (int i = 0; i < currentNumOfFlights; ++i)
	{
		allFlights[i]->saveToFile(out);
	}
}

void AirLine::savePlanesFromFile(ofstream& out)
{
	if (!out)
	{
		cout << "Failed to open file." << endl;
		return;
	}

	// Write the number of planes to the file
	out << currentNumOfPlanes << endl;

	// Write plane data to the file
	for (int i = 0; i < currentNumOfPlanes; ++i)
	{
		allPlanes[i]->saveToFile(out);
	}
}

ostream& operator<<(ostream& out, const AirLine& al)
{
	out << "Airline Name: " << al.name << endl;
	out << "Country: " << al.country << endl;
	out << "Number of Workers: " << al.currentNumOfWorkers << endl;
	out << "Number of Flights: " << al.currentNumOfFlights << endl;
	out << "Number of Planes: " << al.currentNumOfPlanes << endl;
	out << "Number of Passengers: " << al.currentNumOfPassengers << endl;
	out << "Income: " << al.income << endl;
}
