#include <iostream>
#include "Travel.h"
#include "Date.h"
#include "TripInfo.h"

int main() {
    // Create a Travel object
    Travel travel("NYC", "LAX");
    cout << "----------TRAVEL--------------" << endl;
    cout << "Travel: " << travel << endl;

    // Set the source and destination
    travel.setSource("JFK");
    travel.setDest("LAX");

    // Output the Travel object
    cout << "Travel: " << travel << endl;

    // Create a Date object
    Date date(10, 6, 2023);

    // Output the Date object
    cout << "----------DATE--------------" << endl;
    cout << "Date: " << date.getDay() << "/" << date.getMonth() << "/" << date.getYear() << endl;
    
    
    // Create a TripInfo object
    cout << "---------TRIP---------------" << endl;
    TripInfo trip("JFK", "LAX", 10, 6, 2023, 2, 30);
    // Output the TripInfo object
    cout << "Trip Info:" << trip << endl;
    //trip.print(cout);

    cout << "-----------------------" << endl;
    // Set the flight duration
    trip.setTime(3, 15);
    cout << "Trip Info:" << trip << endl;


    cout << "----------TIME-------------" << endl;
    // Get the flight duration
    Time flightDuration = trip.getFlightDuration();
    cout << "Updated Flight Duration: " << flightDuration.getHours() << " hours " << flightDuration.getMinutes() << " minutes" << endl;

    return 0;
}
