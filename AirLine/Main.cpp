#include <iostream>
#include <fstream>
#include "Travel.h"
#include "Date.h"
#include "TripInfo.h"

int main()
{

        // Create a TripInfo object
        TripInfo trip("Source", "Destination", 10, 7, 2023, 2, 30);
        cout << trip << endl;

        // Open a file for writing
        ofstream outFile("trip.txt");
        if (!outFile) {
            cout << "Failed to open the file." << endl;
            return 1;
        }

        // Call the saveToFile method
        trip.saveToFile(outFile);

        // Close the file
        outFile.close();

        cout << "Data saved to file successfully." << endl;
        ifstream inFile("trip.txt");
        if (!inFile) {
            cout << "Failed to open the file." << endl;
            return 1;
        }

        TripInfo t1(inFile);
        cout << t1 << endl;

        return 0;


}
