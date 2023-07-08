#define _CRT_SECURE_NO_WARNINGS

#include "Passenger.h"
#include <fstream>

int Passenger::passportGen = 1111;


Passenger::Passenger(const char* n, int age, char gender, int luggageWeight, const char* code)
    : Person(n, age, gender), ticket(nullptr)
{
    setLuggageWeight(luggageWeight);

    passport = passportGen++;
    if (Travel::airportCodeValid(code))
        strcpy(airportCode, code);
    else
        strcpy(airportCode, Travel::DEFAULT_SOURCE_CODE);
}

Passenger::Passenger(Passenger&& p) noexcept
    : Person(std::move(p)), luggageWeight(p.luggageWeight), passport(p.passport)
{
    strcpy(airportCode,p.airportCode);
    ticket = p.ticket;

    strcpy(p.airportCode, "");
    p.luggageWeight = 0;
    p.passport = 0;
    p.ticket = nullptr;

}

Passenger::Passenger(ifstream& in): Person(in), ticket(nullptr)
{
    in >> passport;
    in >> luggageWeight;
    in >> airportCode;
    in.ignore();
}

void Passenger::saveToFile(ofstream& out) const
{
    Person::saveToFile(out);
    out << passport << endl <<
        luggageWeight << endl << airportCode << endl;

}

void Passenger::print(ostream& out) const {
    
    Person::print(out);

    out << "Passport Number: " << passport;
    out << ", Luggage Weight: " << luggageWeight << " kg";
    out << ", Airport Code: " << airportCode << endl;

    if (ticket)
        out << ticket << endl;
}


const char* Passenger::getAirPortCode() const {
    return airportCode;
}

int Passenger::getLuggageWeight() const {
    return luggageWeight;
}

int Passenger::getPassportNum() const {
    return passport;
}

Ticket* Passenger::getTicket() const
{
    return ticket;
}

void Passenger::setLuggageWeight(int weight) {

    if (weight < MIN_WEIGHT)
        luggageWeight = MIN_WEIGHT;

    else if (weight > MAX_WEIGHT)
        luggageWeight = MAX_WEIGHT;
    else
        luggageWeight = weight;

}

bool Passenger::setTicket(Ticket* otherTicket) {
    if (otherTicket != nullptr) {
        ticket = otherTicket;
        return true;
    }
    return false;
}

void Passenger::removeTicket()
{
    ticket = nullptr;
}

void Passenger::setAirPortCode(const char* newCode)
{
    if (strcmp(airportCode, newCode) == 0)
        return;
    if(Travel::airportCodeValid(newCode))
       strcpy(airportCode, newCode);
}
bool Passenger::operator==(const Passenger& p) const
{
    return passport == p.passport;
}
