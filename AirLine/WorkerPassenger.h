#pragma once
#include "Worker.h"
#include "Passenger.h"


class WorkerPassenger : public Passenger, public Worker
{
private:

    static const float MAX_DISCOUNT;

    float discount;


    void print(ostream& out)const;
public:
    WorkerPassenger(const string& pName, int theAge, char gen, float salary,
                        int seniority, int luggageWeight, const char* code, float disc);
    WorkerPassenger(const WorkerPassenger& wp);
    WorkerPassenger(WorkerPassenger&& wp) noexcept;
    virtual ~WorkerPassenger() {};

    // read and write from file
    WorkerPassenger(ifstream& in);
    virtual void saveToFile(ofstream& out)const;

    void setRaise() ;
    void prepareForFlight(ostream& out) ;
    void annualRefresh(ostream& out) ;
    void takeoff(ostream& out)const ;
    void landing(ostream& out)const ;
    Worker* Worker::clone() const{ return new WorkerPassenger(*this); }
    Passenger* cloneP() const{ return new WorkerPassenger(*this); }
};


