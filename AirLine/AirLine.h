#pragma once
#include <iostream>
using namespace std;
#include <fstream>
#include <vector>
#include "Worker.h"
#include "Passenger.h"
#include "Plane.h"
#include "Flight.h"


#include "Pilot.h"
#include "WorkerPassenger.h"
#include "Technician.h"
#include "FlightAttendet.h"
#include "LinkedList.h"



class Passenger;
class Worker;
class Plane;





class AirLine
{
private:
    static const string DEFAULT_COUNTRY;
    static const string DEFAULT_NAME;


    static AirLine* theAirLine; //Singleton

    static const int PILOT = 0;
    static const int FLIGHT_ATTENDENT = 1;
    static const int TECHNICHIAN = 2;
    static const int PASSENGER = 3;
    static const int WORKER_PASSENGER = 4;


    string name;
    string country;
    
 
    vector<Worker*> workerVec;
    LinkedList<Plane*> planeList;
    vector<Flight*> flightVec;
    vector<Passenger*> passengerVec;


    float income;

    bool checkReady(Flight& f, ostream& out); // Check flight readiness (for internal use)

    AirLine(const string& pName, const string& pCountry); // Constructor in private because Singleton 
    AirLine(const AirLine* a) = delete;
    void operator = (const AirLine& a) = delete;

public:
    static AirLine& getInstance(const string& name = DEFAULT_NAME, const string& countryCode = DEFAULT_COUNTRY); // we initiallize airLine 
    static void releaseInstance();
    
    ~AirLine(); // Destructor

    friend ostream& operator<<(ostream& out, const AirLine& al); // Print operator

    bool addWorker(const Worker& w); // Add worker
    bool addFlight(const Flight& f); // Add flight
    bool addPlane(const Plane& p); // Add plane
    bool addPassenger(const Passenger& p); // Add passenger
    

    void printFlights(ostream& out)const; // Print all flights
    void printWorkers(ostream& out)const; // Print all workers
    void printPlanes(ostream& out)const; // Print all planes
    void printPassengers(ostream& out)const; // Print all passengers

    bool removeWorker(const Worker& w); // Remove worker
    bool removeFlight(const Flight& f); // Remove flight
    bool removePlane(const Plane& p); // Remove plane
    bool removePassenger(const Passenger& p); // Remove passenger

    Plane* choosePlane(ostream& out, istream& in)const;
    Worker* chooseWorker(ostream& out, istream& in)const;
    Flight* chooseFlight(ostream& out, istream& in)const;
    Passenger* choosePassenger(ostream& out, istream& in)const;

    bool isWorkerExist(const Worker& w)const;
    bool isFlightExist(const Flight& f)const;
    bool isPlaneExist(const Plane& p)const;
    bool isPassengerExist(const Passenger& p)const;
    
    void executeFlight(Flight& f, ostream& out); // Execute flight
    bool buyTicket(Passenger& p, Flight& f, ostream& out); // Buy ticket
    void yearPassed(ostream& out); // Add a year
 
    int getNumOfWorkers() const;
    int getNumOfFlights() const;
    int getNumOfPassengers() const;
    int getNumOfPlanes() const;
    
    // Function to get a object pointer from the array based on the index
    Worker* getWorkerAtIndex(int index) const;
    Flight* getFlightAtIndex(int index) const;
    Passenger* getPassengerAtIndex(int index) const;
    Plane* getPlaneAtIndex(int index) const;

    // Function to return the array of Objects
    vector<Worker*> getAllWorkers() const;
    vector<Flight*> getAllFlights() const;
    vector<Passenger*> getAllPassengers() const;
    LinkedList<Plane*> getAllPlanes() const;

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

