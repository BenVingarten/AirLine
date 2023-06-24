#include "Passenger.h"

Passenger::Passenger(const char* n, int age, char gender, int luggageWeight, char code[MAX_CHAR_CODE])
    : Person(n, age, gender), luggageWeight(luggageWeight), ticket(nullptr)
{
    passport = passportGen++;
    if (airportCodeValid(code))
        strcpy(airportCode, code);
}

Passenger::Passenger(const Person& p, int luggageWeight, char code[MAX_CHAR_CODE])
    : Person(p), luggageWeight(luggageWeight)
{
    passport = passportGen++;
    if (airportCodeValid(code))
        strcpy(airportCode, code);
}

Passenger::Passenger(ostream& out, istream& in)
    : Person(out, in)
{
    cout << "Enter Passenger details:" << endl;
   
    cout << "Luggage Weight: ";
    int weight;
    in >> weight;
    in.ignore();
    luggageWeight = weight;

    char code[MAX_CHAR_CODE];
    do {
        cout << "Airport Code: ";
        in.getline(code, MAX_CHAR_CODE);

    } while (!airportCodeValid(code));
    strcpy_s(airportCode, MAX_CHAR_CODE, code);


    passport = passportGen++;
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

void Passenger::print(ostream& out) const {
    
    Person::print(out);

    out << "Passport Number: " << passport;
    out << ", Luggage Weight: " << luggageWeight << " kg";
    out << ", Airport Code: " << airportCode << endl;

    if (ticket)
        out << ticket << endl;
}

bool Passenger::airportCodeValid(char* code) const {
    if (strlen(code) == MAX_CHAR_CODE - 1) {
        code[MAX_CHAR_CODE - 1] = '\0';
        return true;
    }
    return false;
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
