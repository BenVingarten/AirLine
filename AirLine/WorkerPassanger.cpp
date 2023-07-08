#define _CRT_SECURE_NO_WARNINGS
#include "WorkerPassenger.h"
#include <fstream>

const float WorkerPassenger::MAX_DISCOUNT = 0.5;

void WorkerPassenger::print(ostream& out) const
{
    Worker::print(out);
    
    //cannot print Passenger because its going to Person so print individually 
    out << "Passport Number: " << passport;
    out << ", Luggage Weight: " << luggageWeight << " kg";
    out << ", Airport Code: " << airportCode;
    out << ", Worker Discount: " << discount << endl;

    if (ticket)
        out << ticket << endl;

}

WorkerPassenger::WorkerPassenger(const char* pName, int theAge, char gen,
                    float salary, int seniority, int luggageWeight, 
                    const char* code, float disc)
    : Person(pName, theAge, gen),
        Worker(pName, theAge, gen, salary, seniority), 
        Passenger(pName, theAge, gen, luggageWeight, code), discount(disc)
{

}


WorkerPassenger::WorkerPassenger(WorkerPassenger&& wp) noexcept
    : Person(std::move(wp)), Worker(std::move(wp)), Passenger(std::move(wp)), discount(wp.discount)
{
}


WorkerPassenger::WorkerPassenger(ifstream& in)
    :  Person(in), Passenger(in), Worker(in)
{
    in >> discount;
    in.ignore();
}

void WorkerPassenger::saveToFile(std::ofstream& out) const
{
    Passenger::saveToFile(out);
    
    out << cardNumber << endl << salary << endl << seniority << endl 
                    << isWorkerAvailable << endl << discount << endl;

}


void WorkerPassenger::setRaise()
{
    Worker::setRaise();

    discount += 0.1f; // Increase discount by 10%
    if (discount > MAX_DISCOUNT)
        discount = MAX_DISCOUNT;
}

void WorkerPassenger::prepareForFlight(ostream& out)
{
    out << "My name is " << Person::name << " and I am on a vacation, I don't neet to prepare!" << endl;
    
}

void WorkerPassenger::annualRefresh(ostream& out)
{
    
    out << "I will complete the course when I get back from vacation..." << std::endl;
    
}

void WorkerPassenger::takeoff(ostream& out) const
{
    out << "this is " << name << " WorkerPassenger " << getWorkerId() <<
        " with passPortNum " << passport << "hope the crew is doing well, while i'm gone" << endl;
}
void WorkerPassenger::landing(ostream& out) const
{
    out << "this is " << name << " WorkerPassenger " << getWorkerId() <<
        " with passPortNum " << passport << "Yes! lets start this vacation" << endl;

}
