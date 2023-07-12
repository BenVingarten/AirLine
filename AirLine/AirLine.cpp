#define _CRT_SECURE_NO_WARNINGS
#include "AirLine.h"
#include "Ticket.h"
#include <algorithm>


AirLine* AirLine::theAirLine = nullptr;
const char* AirLine::DEFAULT_COUNTRY = "Israel";
const char* AirLine::DEFAULT_NAME = "EL-AL";


//Privates


bool AirLine::checkReady(Flight& f, ostream& out)
{
	if (f.checkIfFlightReady(out))
	{
		out << "The plane is available and fuled!" << endl;
		out << "Enough tickets have been purchased" << endl;
		out << "crew members are in position, and prepared the plane" << endl;
		return true;
	}

	return false;


}

AirLine::AirLine(const char* pName, const char* pCountry) : 
	
	 planeList(), income(0)
	
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
	
	return *theAirLine;
	
}

void AirLine::releaseInstance()
{
	delete theAirLine;
	theAirLine = nullptr;
}

AirLine::~AirLine()
{
	for (int i = 0; i < flightVec.size(); i++)
		delete flightVec[i];
	
	planeList.clear();

	for (int i = 0; i < workerVec.size(); i++)
		delete workerVec[i];
	
	for (int i = 0; i < passengerVec.size(); i++)
		delete passengerVec[i];

	delete[] name; 
	delete[] country;


}



bool AirLine::addWorker(const Worker& w)
{
	// Check if the worker already exists in the workers vector
	if (isWorkerExist(w))
		return false;

	workerVec.push_back(w.clone());
	return true;
}

bool AirLine::addFlight(const Flight& f)
{
	// Check if the flight already exists in the flights array
	if (isFlightExist(f))
		return false;

	flightVec.push_back(new Flight(f));
	return true;
	
}

bool AirLine::addPlane(const Plane& p)
{
	// Check if the plane already exists in the planes array
	if (isPlaneExist(p))
		return false;

	planeList.add(new Plane(p));
	return true;
}

bool AirLine::addPassenger(const Passenger& p)
{
	// Check if the passenger already exists in the passengers array
	if (isPassengerExist(p))
		return false;

	passengerVec.push_back(p.cloneP());
	return true;
}



void AirLine::printFlights(ostream& out) const
{
	out << "Flights:" << endl;

	for (int i = 0; i < flightVec.size(); ++i)
	{
		out << (i + 1) << ")" << *flightVec[i] << endl;
	}
}

void AirLine::printWorkers(ostream& out) const
{
	out << "Workers:" << endl;

	for (int i = 0; i < workerVec.size(); ++i)
	{
		out << (i+1) << ")" << *workerVec[i] << endl;
	}
}

void AirLine::printPlanes(ostream& out) const
{
	out << "Planes:" << endl;
	planeList.print(out);

}

void AirLine::printPassengers(ostream& out) const
{
	out << "Passengers:" << endl;

	for (int i = 0; i < passengerVec.size(); ++i)
	{
		out << (i + 1) << ")" << *passengerVec[i] << endl;
	}
}



bool AirLine::removeWorker(const Worker& w)
{
	// Check if the worker exists in the workers array
	if (!isWorkerExist(w))
		return false;


	auto it = std::find(workerVec.begin(), workerVec.end(), &w);
	if (it != workerVec.end())
		workerVec.erase(it);
		
	return true;
}

bool AirLine::removeFlight(const Flight& f)
{
	// Check if the flight exists in the flights array
		if (!isFlightExist(f))
			return false;

		auto it = std::find(flightVec.begin(), flightVec.end(), &f);
		if (it != flightVec.end())
			flightVec.erase(it);

		return true;
}

bool AirLine::removePlane(const Plane& p)
{

	if (!isPlaneExist(p))
		return false;
	
	planeList.remove(const_cast<Plane*>(&p));
	return true;


}

bool AirLine::removePassenger(const Passenger& p)
{
	// Check if the passenger exists in the passengers array
	if (!isPassengerExist(p))
		return false;

	auto it = std::find(passengerVec.begin(), passengerVec.end(), &p);
	if (it != passengerVec.end())
		passengerVec.erase(it);
	
	return true;
}



Plane* AirLine::choosePlane(ostream& out, istream& in) const
{
	// Print all planes
	printPlanes(out);

	int choice;
	out << "Enter the number of the plane you want: ";
	in >> choice;

	// Validate the input
	if (choice < 1 || choice > planeList.getSize())
	{
		out << "Invalid choice. Please try again." << endl;
		return nullptr;
	}

	// Return the selected plane
	return getPlaneAtIndex(choice - 1);
}

Worker* AirLine::chooseWorker(ostream& out, istream& in) const
{
	// Print all workers
	printWorkers(out);

	int choice;
	out << "Enter the number of the worker you want: ";
	in >> choice;

	// Validate the input
	if (choice < 1 || choice > workerVec.size())
	{
		out << "Invalid choice. Please try again." << endl;
		return nullptr;
	}

	// Return the selected worker
	return workerVec[choice - 1];
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
	if (choice < 1 || choice > flightVec.size())
	{
		out << "Invalid choice. Please try again." << endl;
		return nullptr;
	}

	// Return the selected flight
	return flightVec[choice - 1];
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
	if (choice < 1 || choice > passengerVec.size())
	{
		out << "Invalid choice. Please try again." << endl;
		return nullptr;
	}

	// Return the selected passenger
	return passengerVec[choice - 1];
}



bool AirLine::isWorkerExist(const Worker& w) const
{
	if (workerVec.empty())
		return false;

	for(int i = 0; i < workerVec.size(); i++)
	{
		if (*workerVec[i] == w)
		{
			// Worker with the same ID already exists
			return true;
		}
	}
	return false;
}

bool AirLine::isFlightExist(const Flight& f) const
{


	if (flightVec.empty())
		return false;

	for (int i = 0; i < flightVec.size(); i++)
	{
		if (*flightVec[i] == f)
		{
			// Flight with the same flight number already exists
			return true;
		}
	}
	return false;
	
}

bool AirLine::isPlaneExist(const Plane& p) const
{
	return planeList.isInList(const_cast<Plane*>(&p));
}

bool AirLine::isPassengerExist(const Passenger& p) const
{

	if (passengerVec.empty())
		return false;

	for (int i = 0; i < passengerVec.size(); i++)
	{
		if (*passengerVec[i] == p)
		{
			// Passenger with the same Passport already exists
			return true;
		}
	}
	return false;
}



void AirLine::executeFlight(Flight& f, ostream& out)
{
	out << "Prepare the flight...\n" << endl;
	f.crewPreparations(out);
	f.resetPrints(); 

	out << "Checking last  requirments...\n" << endl;
	if (checkReady(f, out) && isFlightExist(f) > -1)
		out << "Flight Is Ready!" << endl;
	else
	{
		out << "flight is not ready.... " << endl;
		return;
	}

	out << "Executing Flight: " << f.getFlightNumber() << " from " << f.getInfo().getSource() << " to " << f.getInfo().getDestenation() << "\n\n" << endl;

	out << "Boarding \n " << endl;
	f.boarding(out);
	out << "ready for takeoff" << endl;

	out << "Take Off \n " << endl;
	f.takeoff(out);
	f.resetPrints();

	out << " we have reached max speed of " << (int)f.getPlane()->getMaxSpeed() << endl;
	out << " we have decreasing to  minimum speed of " << f.getPlane()->getMinSpeed() << endl;

	out << "Landing \n " << endl;
	f.landing(out); 
	f.resetPrints();

	removeFlight(f);
}

bool AirLine::buyTicket(Passenger& p, Flight& f, ostream& out)
{
	Ticket* t = f.setTicketToPassenger(&p, out);
	if (t == nullptr)
		return false;

	income += t->getPrice();
	return true;
}

void AirLine::yearPassed(ostream& out)
{
	for (int i = 0; i < passengerVec.size(); i++)
		++(*passengerVec[i]);

	for (int i = 0; i < workerVec.size(); i++)
	{
		++(*workerVec[i]); //seniority + set raise
		workerVec[i]->annualRefresh(out);
	}
}


int AirLine::getNumOfWorkers() const {
	return workerVec.size();
}

int AirLine::getNumOfFlights() const {
	return flightVec.size();
}

int AirLine::getNumOfPassengers() const {
	return passengerVec.size();
}

int AirLine::getNumOfPlanes() const {
	return planeList.getSize();
}


Worker* AirLine::getWorkerAtIndex(int index) const {
	if (index >= 0 && index < workerVec.size()) {
		return workerVec[index];
	}
	return nullptr; // Index out of bounds or empty array
}

Flight* AirLine::getFlightAtIndex(int index) const {
	if (index >= 0 && index < flightVec.size()) {
		return flightVec[index];
	}
	return nullptr; // Index out of bounds or empty array
}

Passenger* AirLine::getPassengerAtIndex(int index) const {
	if (index >= 0 && index < passengerVec.size()) {
		return passengerVec[index];
	}
	return nullptr; // Index out of bounds or empty array
}

Plane* AirLine::getPlaneAtIndex(int index) const {
	if (index >= 0 && index < planeList.getSize()) {
		return planeList.getData(index);
	}
	return nullptr; // Index out of bounds or empty array
}


vector<Worker*> AirLine::getAllWorkers() const {
	return workerVec;
}

vector<Flight*> AirLine::getAllFlights() const {
	return flightVec;
}

vector<Passenger*> AirLine::getAllPassengers() const {
	return passengerVec;
}

LinkedList<Plane*> AirLine::getAllPlanes() const {
	return planeList;
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
		in.ignore();

		// Check the type of the worker and create a corresponding object
		if (passengerType == WORKER_PASSENGER)
			addPassenger(WorkerPassenger(in));
		
		else if (passengerType == PASSENGER)
			addPassenger(Passenger(in));
			
		

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
		in.ignore();
		
		// Check the type of the worker and create a corresponding object
		if (workerType == FLIGHT_ATTENDENT) 
			addWorker(FlightAttendet(in));
		
		else if (workerType == PILOT)
		
			addWorker(Pilot(in));
		
		else if (workerType == TECHNICHIAN)
			addWorker(Technician(in));
		
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
		addFlight(Flight(in));
	
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
		addPlane(Plane(in));
		
	
}


void AirLine::savePassengersFromFile(ofstream& out)
{
	if (!out)
	{
		cout << "Failed to open file." << endl;
		return;
	}

	// Write the number of passengers to the file
	out << passengerVec.size() << endl;

	// Write passenger data to the file
	for (int i = 0; i < passengerVec.size(); ++i)
	{
		if (typeid(*passengerVec[i]) == typeid(WorkerPassenger))
			out << WORKER_PASSENGER << endl;
		else
			out << PASSENGER << endl;
		
		passengerVec[i]->saveToFile(out);
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
	out << workerVec.size() << endl;

	// Write worker data to the file
	for (int i = 0; i < workerVec.size(); ++i)
	{
		if (typeid(*workerVec[i]) == typeid(Pilot))
			out << PILOT << endl;
		else if (typeid(*workerVec[i]) == typeid(FlightAttendet))
			out << FLIGHT_ATTENDENT << endl;
		else 
			out << TECHNICHIAN << endl;


		workerVec[i]->saveToFile(out);
		// Check the type of the worker and call the corresponding saveToFile function
		//if (typeid(*workerVec[i]) == typeid(FlightAttendet))
		//{
		//	out << FLIGHT_ATTENDENT << endl; // Write worker type
		//	FlightAttendet* flightAttendant = (FlightAttendet*)(allWorkers[i]);
		//	flightAttendant->saveToFile(out);
		//}
		//else if (typeid(*allWorkers[i]) == typeid(Pilot))
		//{
		//	out << PILOT << endl; // Write worker type
		//	Pilot* pilot = (Pilot*)(allWorkers[i]);
		//	pilot->saveToFile(out);
		//}
		//else if (typeid(*allWorkers[i]) == typeid(Technician))
		//{
		//	out << TECHNICHIAN << endl; // Write worker type
		//	Technician* technician = (Technician*)(allWorkers[i]);
		//	technician->saveToFile(out);
		//}
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
	out << flightVec.size() << endl;

	// Write flight data to the file
	for (int i = 0; i < flightVec.size(); ++i)
	{
		flightVec[i]->saveToFile(out);
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
	out << planeList.getSize() << endl;

	// Write plane data to the file
	
	LinkedList<Plane*>::Node* currentNode = planeList.getHead();
	while (currentNode != nullptr)
	{
		currentNode->value->saveToFile(out);
		currentNode = currentNode->next;
	}
	
}

ostream& operator<<(ostream& out, const AirLine& al)
{
	out << "Airline Name: " << al.name << endl;
	out << "Country: " << al.country << endl;
	out << "Number of Workers: " << al.workerVec.size() << endl;
	out << "Number of Flights: " << al.flightVec.size() << endl;
	out << "Number of Planes: " << al.planeList.getSize() << endl;
	out << "Number of Passengers: " << al.passengerVec.size() << endl;
	out << "Income: " << al.income << endl;

	return out;
}
