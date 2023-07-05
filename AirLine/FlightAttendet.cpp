#define _CRT_SECURE_NO_WARNINGS

#include "FlightAttendet.h"
#include <fstream>

FlightAttendet::FlightAttendet(const char* n, int age, char gender, float salary, int seniority, const char* baseLang)
    : Person(n, age, gender), Worker(n, age, gender, salary, seniority), currentNumOfLanguages(0)
{
    if (baseLang != nullptr)
        addLanugage(baseLang);
}

FlightAttendet::FlightAttendet(FlightAttendet&& w) noexcept
    : Person(std::move(w)), Worker(std::move(w)), currentNumOfLanguages(w.currentNumOfLanguages)
{
    for (int i = 0; i < currentNumOfLanguages; ++i)
    {
        allLanguages[i] = w.allLanguages[i];
        w.allLanguages[i] = nullptr;
    }

    w.currentNumOfLanguages = 0;
}

FlightAttendet::~FlightAttendet()
{
    for (int i = 0; i < currentNumOfLanguages; ++i)
        delete[] allLanguages[i];
}

FlightAttendet::FlightAttendet(ifstream& in): Person(in), Worker(in)
{
    in >> currentNumOfLanguages;
    in.ignore();
    char temp[100];
    for (int i = 0; i < currentNumOfLanguages; ++i)
    {
        in.getline(temp, 100);
        allLanguages[i] = new char[strlen(temp) + 1];
        strcpy(allLanguages[i], temp);
    }
}

void FlightAttendet::saveToFile(ofstream& out) const
{
    Worker::saveToFile(out);
    out << currentNumOfLanguages;
    for (int i = 0; i < currentNumOfLanguages; ++i)
        out << allLanguages[i] << endl;
}

const char** FlightAttendet::getLanguages() const
{
    return const_cast<const char**>(allLanguages); 
}

int FlightAttendet::getCurrentNumOfLanguages() const
{
    return currentNumOfLanguages;
}

bool FlightAttendet::addLanugage(const char* language)
{
    if (currentNumOfLanguages >= MAX_LANGUAGES || language == nullptr)
        return false;

    
    allLanguages[currentNumOfLanguages] = new char[strlen(language) + 1];
    strcpy(allLanguages[currentNumOfLanguages], language);
    currentNumOfLanguages++;
    return true;
}

void FlightAttendet::print(ostream& out) const
{
    out << "Flight attendet: ";
    Worker::print(out);
    out << "Languages: {";
    for (int i = 0; i < currentNumOfLanguages; ++i)
        out << allLanguages[i] << ((i == currentNumOfLanguages - 1)? "" : ", ");
    out << "}" << endl;
}

void FlightAttendet::setRaise()
{
    salary += 100 * currentNumOfLanguages;
}

void FlightAttendet::prepareForFlight(ostream& out)
{
    srand(time(nullptr)); // use current time as seed for random generator
    int rnd = rand() % 4;
    
    out << "I am fligh attendet " << name;
    switch (rnd)
    {
    case 0:
        out << " and I prepared emergency equipment" << endl;
        break;

    case 1:
        out << " and I prepared and reviewed safety procedures" << endl;
        break;

    case 2:
        out << " and I prepared and inspected cabin cleanliness" << endl;
        break;

    case 3:
        out << " and I prepared and ensure proper catering and supplies" << endl;
        break;

    }
    out << endl;
}

void FlightAttendet::annualRefresh(ostream& out)
{
    srand(time(nullptr)); // use current time as seed for random generator
    int rnd = rand() % currentNumOfLanguages;


    out << "I am " << name << " the flight attendent and I went to " << allLanguages[rnd] << " language refreshment" << endl;
}
