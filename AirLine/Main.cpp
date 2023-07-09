#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "AirLine.h"
#include "Pilot.h"
#include "FlightAttendet.h"
#include "Technician.h"
#include "WorkerPassenger.h"

#define READ_FROM_FILE


int main() {
    AirLine& airline = AirLine::getInstance(); // Get the instance of the AirLine

#ifdef READ_FROM_FILE


    // Check if there are files to read from
    ifstream workersFileRead("workers.txt");
    ifstream flightsFileRead("flights.txt");
    ifstream passengersFileRead("passengers.txt");
    ifstream planesFileRead("planes.txt");

    // Read workers from file if it exists
    if (workersFileRead) {
        airline.readWorkersFromFile(workersFileRead);
        workersFileRead.close();
    }

    // Read flights from file if it exists
    if (flightsFileRead) {
        airline.readFlightsFromFile(flightsFileRead);
        flightsFileRead.close();
    }

    // Read passengers from file if it exists
    if (passengersFileRead) {
        airline.readPassengersFromFile(passengersFileRead);
        passengersFileRead.close();
    }

    // Read planes from file if it exists
    if (planesFileRead) {
        airline.readPlanesFromFile(planesFileRead);
        planesFileRead.close();
    }

    //airline.


#else


    // Create passengers
    Passenger passenger1("John", 25, 'M', 20, Travel::DEFAULT_SOURCE_CODE);
    Passenger passenger2("Alice", 30, 'F', 15, Travel::DEFAULT_DEST_CODE);

    // Create workers
    Pilot pilot("Mike", 35, 'M', 5000, 5, Time(100, 0));
    FlightAttendet flightAttendant("Emily", 28, 'F', 3000, 3);
    Technician technician("David", 40, 'M', 4000, 8);
    WorkerPassenger workerPassenger("Amy", 33, 'F', 3500, 6, 10, "TLV", 0.2);

    // Add passengers and workers to the airline
    airline.addPassenger(&passenger1);
    airline.addPassenger(&passenger2);
    airline.addPassenger(&workerPassenger); // Treat worker passenger as a passenger
    airline.addWorker(pilot);
    airline.addWorker(flightAttendant);
    airline.addWorker(technician);

    // Create flights and planes...
    Plane* plane1 = new Plane(150, 8000, 900);
    Plane* plane2 = new Plane(200, 10000, 950);

    airline.addPlane(*plane1);
    airline.addPlane(*plane2);

    // Add flights to the airline...
    Flight* flight1 = new Flight(Travel("New York", "London"), Date(1, 1, 24), Time(7, 15), Time(7, 30), plane1, 30, 2, "Steak");
    Flight* flight2 = new Flight(Travel("Paris", "Tokyo"), Date(14, 3, 23), Time(20, 30), Time(6, 20), plane2, 100, 3, "Sushi");

    airline.addFlight(*flight1);
    airline.addFlight(*flight2);

    // Assign workers to the flight...
    Worker* pilot1 = new Pilot("John", 40, 'M', 10000, 5, Time(300, 0));
    Worker* pilot2 = new Pilot("Alice", 35, 'F', 9500, 3, Time(200, 0));
    Worker* flightAttendant1 = new FlightAttendet("Emily", 28, 'F', 5000, 2);
    Worker* flightAttendant2 = new FlightAttendet("Michael", 30, 'M', 5500, 4);
    Worker* technician1 = new Technician("David", 45, 'M', 6000, 6, Technician::eTechnicianType::STRUCTURE);
    Worker* technician2 = new Technician("Sophia", 32, 'F', 5500, 3, Technician::eTechnicianType::NAVIGATIONS);
    Worker* technician3 = new Technician("William", 50, 'M', 6500, 8, Technician::eTechnicianType::ENGINES);
    Worker* technician4 = new Technician("Olivia", 27, 'F', 5000, 2, Technician::eTechnicianType::COMMUNICATION);
    Worker* technician5 = new Technician("Daniel", 35, 'M', 5500, 4, Technician::eTechnicianType::GENERAL);
    Worker* technician6 = new Technician("Mia", 32, 'F', 5500, 3, Technician::eTechnicianType::GENERAL);
    Worker* technician7 = new Technician("James", 45, 'M', 6000, 6, Technician::eTechnicianType::GENERAL);
    Worker* technician8 = new Technician("Emma", 30, 'F', 5500, 4, Technician::eTechnicianType::GENERAL);

    airline.addWorker(*pilot1);
    airline.addWorker(*pilot2);
    airline.addWorker(*flightAttendant1);
    airline.addWorker(*flightAttendant2);
    airline.addWorker(*technician1);
    airline.addWorker(*technician2);
    airline.addWorker(*technician3);
    airline.addWorker(*technician4);
    airline.addWorker(*technician5);
    airline.addWorker(*technician6);
    airline.addWorker(*technician7);
    airline.addWorker(*technician8);

    flight1->assignCrew(new Worker * [5] { pilot1, flightAttendant1, flightAttendant2, technician1, technician2 }, 5);
    flight2->assignCrew(new Worker * [3] { pilot2, flightAttendant1, technician5 }, 3);


    // Create passengers and buy tickets for flight1
    Passenger* passenger3 = new Passenger("Emma", 25, 'F', 20, Travel::DEFAULT_SOURCE_CODE);
    Passenger* passenger4 = new Passenger("David", 35, 'M', 15, Travel::DEFAULT_SOURCE_CODE);

    airline.addPassenger(passenger3);
    airline.addPassenger(passenger4);

    airline.buyTicket(*passenger3, *flight1, cout);
    airline.buyTicket(*passenger4, *flight1, cout);

#endif // READ_FROM_FILE


    //---------------------------------------------------------------------------------
    // Print all Passenger 
    cout << "Passengers in the airline:" << endl;
    airline.printPassengers(cout);
    cout << endl;

    // Print all flights and workers in the airline
    cout << "Flights in the airline:" << endl;
    airline.printFlights(cout);
    cout << endl;

    cout << "Workers in the airline:" << endl;
    airline.printWorkers(cout);
    cout << endl;

    // Execute a flight1
    cout << "Executing flight 1..." << endl;
    airline.executeFlight(*flight1, cout);
    cout << endl;

    // Execute a flight2        -- suppose to FAIL
    cout << "Executing flight 2..." << endl;
    airline.executeFlight(*flight1, cout);
    cout << endl;
    

    // Print all flights and workers after executing the flight
    cout << "Flights in the airline:" << endl;
    airline.printFlights(cout);                     //why fail +++++++++++++++++++++++
    cout << endl;

    cout << "Workers in the airline:" << endl;
    airline.printWorkers(cout);
    cout << endl;

    // Create and open files for saving airline objects
    ofstream workersFileWrite("workers.txt");
    ofstream flightsFileWrite("flights.txt");
    ofstream passengersFileWrite("passengers.txt");
    ofstream planesFileWrite("planes.txt");

    // Save the airline objects to file
    airline.saveWorkersFromFile(workersFileWrite);
    airline.saveFlightsFromFile(flightsFileWrite);
    airline.savePassengersFromFile(passengersFileWrite);
    airline.savePlanesFromFile(planesFileWrite);

    // Close the files
    workersFileWrite.close();
    flightsFileWrite.close();
    passengersFileWrite.close();
    planesFileWrite.close();

    // Release the instance of the AirLine
    AirLine::releaseInstance();

    return 0;
}

