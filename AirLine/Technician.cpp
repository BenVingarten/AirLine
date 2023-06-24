#include "Technician.h"
#include "Plane.h"
using namespace std;

Technician::Technician(const char* n, int age, char gender, float salary, int seniority, eTechnicianType type)
    : Worker(n, age, gender, salary, seniority), type(type), numOfPlanesPrepared(0)
{
}

Technician::Technician(const Worker& w, eTechnicianType type)
    : Worker(w), type(type), numOfPlanesPrepared(0)
{
}

Technician::Technician(Technician&& t) noexcept
    : Worker(move(t)), type(t.type), numOfPlanesPrepared(t.numOfPlanesPrepared)
{
    t.numOfPlanesPrepared = 0;
}

Technician::Technician(ostream& out, istream& in)
    : Worker(out, in), type(eTechnicianType::GENERAL), numOfPlanesPrepared(0)
{
    
    int typeVal;
    do {
        cout << "Enter technician type (0 - Avionics, 1 - Navigations, 2 - Communication, 3 - Engines, 4 - General): ";
        in >> typeVal;
        in.ignore(); // Ignore the newline character
    } while (typeVal < 0 || typeVal > 4);

    type = static_cast<eTechnicianType>(typeVal);
}

Technician::eTechnicianType Technician::getType() const {
    return type;
}

int Technician::getNumOfPlanesPrepared() const {
    return numOfPlanesPrepared;
}

void Technician::setRaise() {
     salary += numOfPlanesPrepared * 5;
}

void Technician::PrepareForFlight(Plane& plane, ostream& out) 
{
    testSystems(out);
    if (!plane.isPlaneFuled())
        fillFuel(plane, out);

    ++numOfPlanesPrepared;
}

void Technician::AnnualRefresh(ostream& out) {

    //TODO--------------------------------------

    numOfPlanesPrepared = 0;
}

void Technician::testSystems(ostream& out) {
    // Implementation for testing plane systems

    srand(time(nullptr)); // use current time as seed for random generator
    int rnd = rand() % 8;
    if (rnd == 7)
        fixProblem(out);

    switch (type) {
    case eTechnicianType::STRUCTURE:
        out << "Checking all plane components .... Checked! ";
        break;
    case eTechnicianType::NAVIGATIONS:
        out << "Checking all radars and maps .... Checked! ";
        break;
    case eTechnicianType::COMMUNICATION:
        out << "Checking all radio and screens .... Checked! ";
        break;
    case eTechnicianType::ENGINES:
        out << "Checking for problems in engines .... Checked! ";
        break;
    case eTechnicianType::GENERAL:
        out << "Checking fuel and oil .... Checked! ";
        break;
    }
    out << endl;
}

void Technician::fillFuel(Plane& plane, ostream& out) {
    // Implementation for filling plane fuel

    out << "Refueling the plane " << endl;
    plane.setNeedToRefuelFalse();

}

void Technician::fixProblem(ostream& out)
{
    switch (type) {
    case eTechnicianType::STRUCTURE:
        out << "found problem in wings! \nProblem fixed, checking again  ";
        break;
    case eTechnicianType::NAVIGATIONS:
        out << "found maps not updated! \nI updated the maps, checking again  ";
        break;
    case eTechnicianType::COMMUNICATION:
        out << "No connection to the air-traffic tower! \nI reconnected the connection, checking again  ";
        break;
    case eTechnicianType::ENGINES:
        out << "found an oil leak! \nI shut the leak, checking again   ";
        break;
    case eTechnicianType::GENERAL:
        out << "Oil is too old! \nI changed the oil, checking again  ";
        break;
    }
    out << endl;
    
}

void Technician::print(ostream& out) const {
    Worker::print(out);
    out << "Technician Type: ";
    switch (type) {
    case eTechnicianType::STRUCTURE:
        out << "Structure";
        break;
    case eTechnicianType::NAVIGATIONS:
        out << "Navigations";
        break;
    case eTechnicianType::COMMUNICATION:
        out << "Communication";
        break;
    case eTechnicianType::ENGINES:
        out << "Engines";
        break;
    case eTechnicianType::GENERAL:
        out << "General";
        break;
    }
    out << " and I prepared " << numOfPlanesPrepared << " flights" << endl;
}


