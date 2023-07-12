#define _CRT_SECURE_NO_WARNINGS

#include "FlightAttendet.h"
#include <fstream>

const char* FlightAttendet::DEF_LANG = "Hebrew";

FlightAttendet::FlightAttendet(const char* n, int age, char gender, float salary, int seniority, const char* baseLang)
    : Person(n, age, gender), Worker(n, age, gender, salary, seniority), currentNumOfLanguages(0)
{
    for (int i = 0; i < MAX_LANGUAGES; ++i)
        allLanguages[i] = nullptr;

    if (baseLang != nullptr)
        addLanugage(baseLang);
    else
        addLanugage(DEF_LANG);
}

FlightAttendet::FlightAttendet(const FlightAttendet& other) :
    Person(other), Worker(other), currentNumOfLanguages(0)
{
    for (int i = 0; i < MAX_LANGUAGES; ++i)
        allLanguages[i] = nullptr;
    
    int i = 0;
    while (i < other.currentNumOfLanguages)
        addLanugage(other.allLanguages[i++]);

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
    char tmpLang[MAX_NAME_LEN];
    for (int i = 0; i < currentNumOfLanguages; i++)
    {
        in.getline(tmpLang, MAX_NAME_LEN);


        allLanguages[i] = new char[strlen(tmpLang) + 1];
        strcpy(allLanguages[i], tmpLang);
    }

    if (currentNumOfLanguages == 0)
        addLanugage(DEF_LANG);

}

void FlightAttendet::saveToFile(ofstream& out) const
{
    Worker::saveToFile(out);
    out << currentNumOfLanguages << endl;
    for (int i = 0; i < currentNumOfLanguages; i++)
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

void FlightAttendet::landing(ostream& out) const
{
    out << "this is " << name << " Flight attendet " << getWorkerId() <<
        " asking for your attention\nwe are about to land, so please fasten your seat and remove headphones" << endl;
    out << "dont forget any of your belongings in the plane" << endl;
}


void FlightAttendet::prepareForFlight(ostream& out)
{
    srand((unsigned int)time(NULL)); // use current time as seed for random generator
    unsigned int rnd = (unsigned int)(rand() % 4);
    
    out << "I'm " << name << " flight Attendet " << getWorkerId() << " preparing for flight" << endl;
    switch(rnd)
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
        out << " and I prepared and ensured proper catering and supplies" << endl;
        break;

    }
    out << endl;
}

void FlightAttendet::annualRefresh(ostream& out)
{
    srand((unsigned int)time(NULL)); // use current time as seed for random generator
    
    unsigned int  rnd = (unsigned int)(rand() % currentNumOfLanguages);


    out << "I am " << name << " the flight attendent and I went to " << allLanguages[rnd] << " language refreshment" << endl;
}

void FlightAttendet::takeoff(ostream& out)const
{
    out << "this is " << name << " Flight attendet " << getWorkerId() <<
        " asking for your attention\nwe are about to takeoff, so please fasten your seat belt and stay seated" << endl;
}
