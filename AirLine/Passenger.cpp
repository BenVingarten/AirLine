#define _CRT_SECURE_NO_WARNINGS

#include "Passenger.h"
#include <fstream>

Passenger::Passenger(const char* n, int age, char gender, int luggageWeight, const char* code)
    : Person(n, age, gender), luggageWeight(luggageWeight), ticket(nullptr)
{
    passport = passportGen++;
    if (Travel::airportCodeValid(code))
        strcpy(airportCode, code);
    else
        strcpy(airportCode, DEFAULT_SOURCE_CODE);
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
    in >> passport >> luggageWeight;
    in.getline(airportCode, MAX_CHAR_CODE);
}

void Passenger::saveToFile(ofstream& out) const
{
    Person::saveToFile(out);
    out << passport << luggageWeight << airportCode << endl;


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

void Passenger::setLuggageWeight(int weight) {
    luggageWeight = weight;
}

bool Passenger::setTicket(Ticket* otherTicket) {
    if (otherTicket != nullptr) {
        ticket = otherTicket;
        return true;
    }
    return false;
}
