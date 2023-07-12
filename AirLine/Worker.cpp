#define _CRT_SECURE_NO_WARNINGS
#include "Worker.h"
#include <fstream>

int Worker::workerCardNumberGenerator = 2222;



Worker::Worker(const char* pName, int theAge, char gen, float salary, int seniority)
    : Person(pName, theAge, gen), salary(salary), seniority(seniority),
        isWorkerAvailable(true), currentFlight(nullptr)
{
    cardNumber = workerCardNumberGenerator++;
}

Worker::Worker(const Worker& w) : 
    Person(w), seniority(w.seniority), salary(w.salary), 
    cardNumber(w.cardNumber), currentFlight(w.currentFlight), isWorkerAvailable(w.isWorkerAvailable)
{
}

Worker::Worker(Worker&& w) noexcept
    : Person(std::move(w)), cardNumber(w.cardNumber), salary(w.salary), seniority(w.seniority),
    currentFlight(w.currentFlight), isWorkerAvailable(w.isWorkerAvailable)
{
    w.cardNumber = 0;
    w.salary = 0.0f;
    w.seniority = 0;
    w.currentFlight = nullptr;
    w.isWorkerAvailable = false;
}


Worker::Worker(ifstream& in) : Person(in), currentFlight(nullptr), isWorkerAvailable(true)
{
    //when we read from file we read from data base to create worker
    // the pointers won't be saved or wrtitten (Flight*)
    in >> cardNumber;
    in >> salary;
    in >> seniority;
    in.ignore();
}

void Worker::saveToFile(ofstream& out) const
{
    Person::saveToFile(out);
    out << cardNumber << endl << salary << endl <<
        seniority << endl;
}


bool Worker::isSalaryValid(float salary)const 
{
    return salary < MINIMUM_WAGE;
}

void Worker::readAndsetSalary(ostream& out, istream& in)
{
    do
    {
        out << "Enter worker's salary (at least " << MINIMUM_WAGE << ") : ";
        in >> salary;
        in.ignore(); // Ignore the newline character
    } while(isSalaryValid(salary));
}

void Worker::readAndsetSeniority(ostream& out, istream& in)
{
    int s;
    cout << "Enter worker's seniority: ";
    in >> s;
    in.ignore(); // Ignore the newline character
    if (s < 0)
        seniority = 0;
    else
        seniority = s;
}

void Worker::print(ostream& out) const {
    
    Person::print(out);

    out << "Worker ID: " << cardNumber;
    out << ", Salary: $" << salary;
    out << ", Seniority: " << seniority << " years" << endl;
}


int Worker::getWorkerId() const {
    return cardNumber;
}

float Worker::getSalary() const {
    return salary;
}

int Worker::getSeniority() const {
    return seniority;
}

bool Worker::isAvailable() const {
    return isWorkerAvailable;
}


bool Worker::setFlight(Flight* flight) {
    if (flight != nullptr) {
        currentFlight = flight;
        return true;
    }
    return false;
}

void Worker::removeFlight()
{
    currentFlight = nullptr;
}

void Worker::changeAvailability()
{
    isWorkerAvailable = !isWorkerAvailable;
}

Worker& Worker::operator++() {
    ++seniority;
    setRaise();
    
    return *this;
}

bool Worker::operator==(const Worker& worker) const {
    return (cardNumber == worker.cardNumber); //card number is unique for each worker 
}
