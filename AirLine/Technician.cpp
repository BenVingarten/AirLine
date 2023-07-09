#define _CRT_SECURE_NO_WARNINGS

#include "Technician.h"
#include "Plane.h"
#include <fstream>
using namespace std;

Technician::Technician(const char* n, int age, char gender, float salary, int seniority, eTechnicianType type)
    :Person(n, age, gender), Worker(n, age, gender, salary, seniority), type(type), planesPreparedThisYear(0)
{
}

Technician::Technician(const Technician& other) :
    Person(other), Worker(other), planesPreparedThisYear(other.planesPreparedThisYear), type(other.type)
{
}

Technician::Technician(Technician&& t) noexcept
    : Person(std::move(t)), Worker(move(t)), type(t.type), planesPreparedThisYear(t.planesPreparedThisYear)
{
    t.planesPreparedThisYear = 0;
}

Technician::Technician(ifstream& in): Person(in), Worker(in)
{
    int typeVal;
    in >> planesPreparedThisYear;
    in >> typeVal;
    type = static_cast<eTechnicianType>(typeVal);
    in.ignore();
}

void Technician::saveToFile(ofstream& out) const
{
    Worker::saveToFile(out);
    out << planesPreparedThisYear << endl << static_cast<int>(type) << endl;
}

Technician::eTechnicianType Technician::getType() const {
    return type;
}

const char* Technician::getStringType()const
{
    switch (type) {
    case eTechnicianType::STRUCTURE:
        return "Structure";

    case eTechnicianType::NAVIGATIONS:
        return "Navigations";
        
    case eTechnicianType::COMMUNICATION:
        return "Communication";
       
    case eTechnicianType::ENGINES:
        return "Engines";

    default:
        return "General";
 
    }
}

int Technician::getNumOfPlanesPrepared() const {
    return planesPreparedThisYear;
}

void Technician::setRaise() {
     salary += planesPreparedThisYear * 5;
}


void Technician::prepareForFlight(ostream& out)
{
    out << "I'm " << name << " technician " << getWorkerId() << " in field: " << getStringType() << " preparing for flight" << endl;
    testSystems(out);
    if (!currentFlight->getPlane()->isPlaneFuled())
        fillFuel(currentFlight->getPlane(), out);

    ++planesPreparedThisYear;
}

void Technician::annualRefresh(ostream& out) {

    switch (type) {
    case eTechnicianType::STRUCTURE:
        out << "I am structure technician, I went to physics & matirials course refreshment.  ";
        break;
    case eTechnicianType::NAVIGATIONS:
        out << "I am navigation technician, I went to navigation systems course refreshment.  ";
        break;
    case eTechnicianType::COMMUNICATION:
        out << "I am communication technician, I went to communication systems course refreshment.  ";
        break;
    case eTechnicianType::ENGINES:
        out << "I am engines technician, I went to engines course refreshment.  ";
        break;
    case eTechnicianType::GENERAL:
        out << "I am general technician, I went to safety course refreshment.  ";
        break;
    }
    out << endl;

    planesPreparedThisYear = 0;
}

void Technician::takeoff(ostream& out)const
{
    out << "This is " << name << " technician " << getWorkerId() << " keeping alert for any unwanted malfunction system during takeoff" << endl;
}

void Technician::landing(ostream& out) const
{
    out << "this is " << name << " technician " << getWorkerId() << " making sure there all communication systesm with tower are woring" << endl;
}


void Technician::testSystems(ostream& out)const {
    // Implementation for testing plane systems

    srand((unsigned int)time(NULL)); // use current time as seed for random generator

    unsigned int  rnd = rand() % 8;
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

void Technician::fillFuel(Plane* plane, ostream& out) {
    // Implementation for filling plane fuel

    out << "Refueling the plane " << endl;
    plane->setNeedToRefuelFalse();

}

void Technician::fixProblem(ostream& out)const
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
    out << "Technician: ";
    Worker::print(out);
    out << "Type: ";
    out << getStringType();
    out << " and I prepared " << planesPreparedThisYear << " flights" << endl;
}


