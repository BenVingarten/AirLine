#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "AirLine.h"
#include "Pilot.h"
#include "FlightAttendet.h"
#include "Technician.h"
#include "WorkerPassenger.h"

//#define READ_FROM_FILE


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


    


#else


    // Create passengers
    Passenger passenger1("John", 25, 'M', 20, Travel::DEFAULT_SOURCE_CODE);
    Passenger passenger2("Alice", 30, 'F', 15, Travel::DEFAULT_DEST_CODE);
    Passenger passenger3 = Passenger("Emma", 25, 'F', 20, Travel::DEFAULT_SOURCE_CODE);
    Passenger passenger4 = Passenger("David", 35, 'M', 15, Travel::DEFAULT_SOURCE_CODE);
    WorkerPassenger workerPassenger("Amy", 33, 'F', 3500, 6, 10, "TLV", 0.2);

    //add passengers
    airline.addPassenger(passenger1);
    airline.addPassenger(passenger2);
    airline.addPassenger(passenger3);
    airline.addPassenger(passenger4);
    airline.addPassenger(workerPassenger); // Treat worker passenger as a passenger




    // Create workers

    Pilot pilot("Mike", 35, 'M', 5000, 5, Time(100, 0));
    Pilot pilot1("John", 40, 'M', 10000, 5, Time(300, 0));
    Pilot pilot2("Alice", 35, 'F', 9500, 3, Time(200, 0));
    FlightAttendet flightAttendant("Emily", 28, 'F', 3000, 3, "Hebrew");
    FlightAttendet flightAttendant1("Michael", 30, 'M', 5500, 4, "Hebrew");
    FlightAttendet flightAttendant2("Emily", 28, 'F', 5000, 2, "English");
    Technician technician("David", 40, 'M', 4000, 8);
    Technician technician1("David", 45, 'M', 6000, 6, Technician::eTechnicianType::STRUCTURE);
    Technician technician2("Sophia", 32, 'F', 5500, 3, Technician::eTechnicianType::NAVIGATIONS);
    Technician technician3("William", 50, 'M', 6500, 8, Technician::eTechnicianType::ENGINES);
    Technician technician4("Olivia", 27, 'F', 5000, 2, Technician::eTechnicianType::COMMUNICATION);
    Technician technician5("Daniel", 35, 'M', 5500, 4, Technician::eTechnicianType::GENERAL);
    Technician technician6("Mia", 32, 'F', 5500, 3, Technician::eTechnicianType::GENERAL);
    Technician technician7("James", 45, 'M', 6000, 6, Technician::eTechnicianType::GENERAL);
    Technician technician8("Emma", 30, 'F', 5500, 4, Technician::eTechnicianType::GENERAL);

    flightAttendant.addLanugage("English");

    // Add workers to the airline
    airline.addWorker(flightAttendant);
    airline.addWorker(pilot);
    airline.addWorker(technician);

    airline.addWorker(pilot1);
    airline.addWorker(pilot2);
    airline.addWorker(flightAttendant1);
    airline.addWorker(flightAttendant2);
    airline.addWorker(technician1);
    airline.addWorker(technician2);
    airline.addWorker(technician3);
    airline.addWorker(technician4);
    airline.addWorker(technician5);
    airline.addWorker(technician6);
    airline.addWorker(technician7);
    airline.addWorker(technician8);




    // Create flights and planes...
    Plane plane1 = Plane(150, 8000, 900);
    Plane plane2 = Plane(200, 10000, 950);
    Plane plane3 = Plane(250, 9000, 980);

    airline.addPlane(plane1);
    airline.addPlane(plane2);
    airline.addPlane(plane3);

    // Add flights to the airline...
  
    Flight flight1 = Flight(Travel("NYC", "LND"), Date(1, 1, 24), Time(7, 15), Time(7, 30), &plane1, 30, 2, "Steak");
    Flight flight2 = Flight(Travel("FRN", "JPN"), Date(14, 3, 23), Time(20, 30), Time(6, 20), &plane2, 100, 3, "Sushi");
    Flight flight3 = Flight(Travel("TLV", "LAX"), Date(14, 8, 23), Time(15, 45), Time(6, 20), &plane3, 80, 4, "Falafel");

    flight2.addDishToMenu("Eggroll");


    airline.addFlight(flight1);
    airline.addFlight(flight2);
    airline.addFlight(flight3);

   

  


#endif // READ_FROM_FILE


    //---------------------------------------------------------------------------------
    // Print all Passenger, flights, workers and planese before any flight 
    cout << "Print all Passenger, Flights, Workers and Planese BEFORE any flight ------------------------\n\n" << endl;
    airline.printPassengers(cout);
    cout << endl;

    // Print all flights and workers in the airline
    cout << "\n**************************" << endl;
    airline.printFlights(cout);
    cout << endl;

    cout << "\n**************************" << endl;
    airline.printWorkers(cout);
    cout << endl;

    cout << "\n**************************" << endl;
    airline.printPlanes(cout);
    cout << endl;


    cout << "Try to execute 2 flight, for the first one add what needed ------------------------\n\n" << endl;






    /* 
    *                   Execute a flight1 or the first flight available
    * if we have one flight, we will fill it with the crew members.
    *     � inside of assignCrew we check for how many worker of each type
    *       we have and add them as needed. so we will add the first workers
    *       available and won't add only pilots/only Technichian/...
    *
    *     � we add the first plane if there is one and it is available (only if  we don't have one on flight alraedy)
    *
    *     � we make at most 3 passangers (or as many as there are id less than 3)
    *       buying tickets to the flight ,if they are able to (checked in function).
    *
    *       at the end we Exectute the flight
    */
    cout << "\nEXECUTE FLIGHT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
    if (airline.getNumOfFlights() > 0) //there is at least one flight
    {
        Flight* f = airline.getFlightAtIndex(0);

        //assign crew members
        f->assignCrew(airline.getAllWorkers());

        //set plane
        if (airline.getNumOfPlanes() > 0 && f->getPlane() == nullptr)
            f->setPlane(airline.getPlaneAtIndex(0));

        //buy tickets 
        for (int i = 0; i < airline.getNumOfPassengers() && i < 3; ++i)
        {
            airline.buyTicket(*airline.getPassengerAtIndex(i), *f, cout);
        }

        //execute
        airline.executeFlight(*f, cout);

    }

    //Try to Execute the second flight 
    cout << "\nEXECUTE FLIGHT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
    if (airline.getNumOfFlights() > 0) //there is at least one flight
    {
        airline.executeFlight(*airline.getFlightAtIndex(0), cout);
    }
    




    // Print all Passenger, flights, workers and planese before any flight -----------------------------------------------------------------
    cout << "Print all Passenger, flights, workers and planese AFTER any flight ------------------------\n\n" << endl;
    airline.printPassengers(cout);
    cout << endl;

    cout << "\n**************************" << endl;
    airline.printFlights(cout);
    cout << endl;

    cout << "\n**************************" << endl;
    airline.printWorkers(cout);
    cout << endl;

    cout << "\n**************************" << endl;
    airline.printPlanes(cout);
    cout << endl;




    // do Year Passed on the company --------------------------------------------------------------------------------------------------------
    cout << "Make Year Passed------------------------\n\n" << endl;
    airline.yearPassed(cout);





    // Print all Passenger, workers and planese before any flight  -----------------------------------------------------------------
    cout << "Print all Passenger, flights, workers and planese AFTER any flight ------------------------\n\n" << endl;
    airline.printPassengers(cout);
    cout << endl;

    cout << "\n**************************" << endl;
    airline.printWorkers(cout);
    cout << endl;

    cout << "\n**************************" << endl;
    airline.printPlanes(cout);
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

