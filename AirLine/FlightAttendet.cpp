#define _CRT_SECURE_NO_WARNINGS

#include "FlightAttendet.h"
#include <fstream>
#include <string>

const string FlightAttendet::DEF_LANG = "Hebrew";

FlightAttendet::FlightAttendet(const string& n, int age, char gender, float salary, int seniority, const string& baseLang)
    : Person(n, age, gender), Worker(n, age, gender, salary, seniority)
{
    if (baseLang == "")
        addLanugage(DEF_LANG);
    else
        addLanugage(baseLang);
}

FlightAttendet::FlightAttendet(const FlightAttendet& other) :
    Person(other), Worker(other), languagesVec(other.languagesVec)
{
}

FlightAttendet::FlightAttendet(FlightAttendet&& w) noexcept
    : Person(std::move(w)), Worker(std::move(w))
{
    languagesVec = std::move(w.languagesVec);
}



FlightAttendet::FlightAttendet(ifstream& in) : Person(in), Worker(in)
{
    int numOfLanugages;
    in >> numOfLanugages;
    in.ignore();

    for (int i = 0; i < numOfLanugages; i++)
    {
        string s;
        std::getline(in, s);
        languagesVec.push_back(s);
    }
}

void FlightAttendet::saveToFile(ofstream& out) const
{
    Worker::saveToFile(out);
    out << languagesVec.size() << endl;
    for (int i = 0; i < languagesVec.size(); i++)
        out << languagesVec[i] << endl;
}



const vector<string> FlightAttendet::getLanguages() const
{
    return languagesVec;
}

int FlightAttendet::getCurrentNumOfLanguages() const
{
    return languagesVec.size();
}

bool FlightAttendet::addLanugage(const string& language)
{
    if (language == "")
        return false;
    languagesVec.push_back(language);
    return true;
}

void FlightAttendet::print(ostream& out) const
{
    out << "Flight attendet: ";
    Worker::print(out);
    out << "Languages: {";
    for (int i = 0; i < languagesVec.size(); ++i)
        out << languagesVec[i] << ((i == languagesVec.size() - 1)? "" : ", ");
    out << "}" << endl;
}

void FlightAttendet::setRaise()
{
    salary += 100 * languagesVec.size();
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
    
    unsigned int  rnd = (unsigned int)(rand() % languagesVec.size());


    out << "I am " << name << " the flight attendent and I went to " << languagesVec[rnd] << " language refreshment" << endl;
}

void FlightAttendet::takeoff(ostream& out)const
{
    out << "this is " << name << " Flight attendet " << getWorkerId() <<
        " asking for your attention\nwe are about to takeoff, so please fasten your seat belt and stay seated" << endl;
}
