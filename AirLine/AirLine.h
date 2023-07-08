#pragma once
#include <iostream>
using namespace std;
#include <fstream>

#include "Worker.h"
#include "Passenger.h"
#include "Plane.h"
#include "Flight.h"


#include "Pilot.h"
#include "WorkerPassenger.h"
#include "Technician.h"
#include "FlightAttendet.h"


class Passenger;
class Worker;
class Plane;




class AirLine
{
private:
    static const char* DEFAULT_COUNTRY;
    static const char* DEFAULT_NAME; 


    static AirLine* theAirLine; //Singleton

    static const int PILOT = 0;
    static const int FLIGHT_ATTENDENT = 1;
    static const int TECHNICHIAN = 2;
    static const int PASSENGER = 2;
    static const int WORKER_PASSENGER = 2;


    char* name;
    char* country;
    
    int currentNumOfWorkers;
    int currentNumOfFlights;
    int currentNumOfPlanes;
    int currentNumOfPassengers;

    Worker** allWorkers;
    Plane** allPlanes;
    Flight** allFlights;
    Passenger** allPassengers;

    int sizeOfWorkers; //size of Workers array
    int sizeOfFlights; //size of Flights array
    int sizeOfPlanes; //size of Planes  array
    int sizeOfPassengers; //size of Passengers array

    const int MAX_WORKERS = 50;
    const int MAX_PLANES = 10;
    const int MAX_FLIGHTS = 15;
    const int MAX_PASSENGERS = 50;

    float income;

    bool checkReady(Flight& f, ostream& out); // Check flight readiness (for internal use)

    AirLine(const char* pName, const char* pCountry); // Constructor in private because Singleton 
    AirLine(const AirLine* a) = delete;
    void operator = (const AirLine& a) = delete;

public:
    static AirLine& getInstance(const char* name = DEFAULT_NAME, const char* countryCode = DEFAULT_COUNTRY); // we initiallize airLine 
    static void releaseInstance();
    
    ~AirLine(); // Destructor

    friend ostream& operator<<(ostream& out, const AirLine& al); // Print operator

    bool addWorker(Worker& w); // Add worker
    bool addFlight(Flight& f); // Add flight
    bool addPlane(Plane& p); // Add plane
    bool addPassenger(Passenger* p); // Add passenger
    

    void printFlights(ostream& out)const; // Print all flights
    void printWorkers(ostream& out)const; // Print all workers
    void printPlanes(ostream& out)const; // Print all planes
    void printPassengers(ostream& out)const; // Print all passengers

    void removeWorker(Worker& w); // Remove worker
    void removeFlight(Flight& f); // Remove flight
    void removePlane(Plane& p); // Remove plane
    void removePassenger(Passenger& p); // Remove passenger

    Plane* choosePlane(ostream& out, istream& in)const;
    Worker* chooseWorker(ostream& out, istream& in)const;
    Flight* chooseFlight(ostream& out, istream& in)const;
    Passenger* choosePassenger(ostream& out, istream& in)const;

    int isWorkerExist(const Worker& w)const;
    int isFlightExist(const Flight& f)const;
    int isPlaneExist(const Plane& p)const;
    int isPassengerExist(const Passenger& p)const;
    
    void executeFlight(Flight& f, ostream& out); // Execute flight
    bool buyTicket(Passenger& p, Flight& f, ostream& out); // Buy ticket
    void yearPassed(ostream& out); // Add a year
 
    //read and save to file
    void readPassengersFromFile(ifstream& in);
    void readWorkersFromFile(ifstream& in);
    void readFlightsFromFile(ifstream& in);
    void readPlanesFromFile(ifstream& in);

    void savePassengersFromFile(ofstream& out);
    void saveWorkersFromFile(ofstream& out);
    void saveFlightsFromFile(ofstream& out);
    void savePlanesFromFile(ofstream& out);
    
};

