#define _CRT_SECURE_NO_WARNINGS
#include "Pilot.h"
#include <fstream>

const float Pilot::RAISE_PRECENTAGE = 0.7f;

Pilot::Pilot(const string& n, int age, char gender, float salary, int seniority, Time flightHours)
    : Person(n, age, gender), Worker(n, age, gender, salary, seniority), flightHours(flightHours)
{
}

Pilot::Pilot(const Pilot& p) :
    Person::Person(p), Worker(p), flightHours(p.flightHours)
{}

Pilot::Pilot(Pilot&& p) noexcept
    : Person(std::move(p)), Worker(std::move(p)), flightHours(std::move(p.flightHours))
{
}

Pilot::Pilot(ifstream& in) :Person(in), Worker(in), flightHours(in)
{
}

void Pilot::saveToFile(ofstream& out) const
{
    Worker::saveToFile(out);
    flightHours.saveToFile(out);
}

Time Pilot::getflightHours() const
{
    return flightHours;
}

Pilot& Pilot::operator+=(const Time& time)
{
    flightHours += time;
    return *this;
}

void Pilot::setRaise()
{

    salary += RAISE_PRECENTAGE * flightHours.getHours();
    
}

void Pilot::prepareForFlight(ostream& out)
{
    out << "I'm " << name <<", pilot " << getWorkerId() << " Perform pre - flight inspection for flight " << endl;
}

void Pilot::annualRefresh(ostream& out)
{
    srand((unsigned int)time(NULL)); // use current time as seed for random generator
    unsigned int rnd = rand() % 4;

    out << "Pilot " << name;
    switch (rnd)
    {
    case 0:
        out << " going through complete medical examination" << endl;
        break;

    case 1:
        out << " reviewign emergency procedures" << endl;
        break;

    case 2:
        out << " participating in simulator training" << endl;
        break;

    case 3:
        out << " attending refresher courses" << endl;
        break;

    }
    
}

void Pilot::takeoff(ostream& out)const
{
    out << "this is your pilot " << name << " for flight " << currentFlight->getFlightNumber() << " from " << currentFlight->getInfo().getSource() <<
        " to " << currentFlight->getInfo().getDestenation() << endl;
    out << "the duration of the flight is " << currentFlight->getInfo().getFlightDuration().getHours() << " hours and " <<
        currentFlight->getInfo().getFlightDuration().getMinutes() << " minutes" << endl;
    out << "Get ready for takeoff, and have a wonderful flight" << endl;
}

void Pilot::landing(ostream& out)const
{
    out << "this is your pilot " << name << " for flight " << currentFlight->getFlightNumber() <<
     " get ready for takeoff, we are about to land in " << currentFlight->getInfo().getDestenation() << endl;

}

void Pilot::print(ostream& out) const
{
    out << "Pilot ";
    Worker::print(out);
    out << "Flight Hours: " << flightHours << endl;
}
