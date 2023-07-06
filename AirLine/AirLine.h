#pragma once
#include <iostream>
using namespace std;
#include "Passenger.h"
#include "Plane.h"
#include "Flight.h"
#include "Worker.h"

class AirLine
{
                                //TODO design PATTERN observer; 
private:
    static AirLine* theAirLine;

    char* name;
    char* country;
    
    int currentNumOfWorkers;
    int currentNumOfFlight;
    int currentNumOfPlanes;
    int currentNumOfPassengers;

    Worker** allWorkers;
    Plane** allPlanes;
    Flight** allFlights;
    Passenger** allPassengers;

    const int MAX_WORKERS = 50;
    const int MAX_PLANES = 10;
    const int MAX_FLIGHTS = 15;
    const int MAX_PASSENGERS = 50;

    float income;


    void boarding(); // Boarding function (for internal use)
    void takeoff(); // Takeoff function (for internal use)
    void landing(); // Landing function (for internal use)
    void checkReady(); // Check flight readiness (for internal use)

    AirLine(const char* name, const char* country); // Constructor in private because Singleton 
    AirLine(const AirLine* a) = delete;
    void operator = (const AirLine& a) = delete;

public:
    static AirLine& getInstance(const char* name, const char* countryCode);
    static void releaseInstance();
    
    ~AirLine(); // Destructor

    friend ostream& operator<<(ostream& out, const AirLine& al); // Print operator

    bool addWorker(const Worker& w); // Add worker
    bool addFlight(Flight& f); // Add flight
    bool addPlane(const Plane& p); // Add plane
    bool addPassenger(const Passenger* p); // Add passenger

    void printFlights()const; // Print all flights
    void printWorkers()const; // Print all workers
    void printPlanes()const; // Print all planes
    void printPassengers()const; // Print all passengers

    void removeWorker(); // Remove worker
    void removeFlight(); // Remove flight
    void removePlane(); // Remove plane
    void removePassenger(); // Remove passenger

    Plane* choosePlane()const;
    Worker* chooseWorker()const;
    Flight* chooseFlight()const;
    Passenger* choosePassenger()const;
    
    float executeFlight(Flight& f); // Execute flight
    bool buyTicket(); // Buy ticket
    void yearPassed(); // Add a year
 
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

