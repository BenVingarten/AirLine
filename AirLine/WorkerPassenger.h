#pragma once
#include "Worker.h"
#include "Passenger.h"

class WorkerPassenger : public Worker, public Passenger
{
private:

    static const float MAX_DISCOUNT;

    float discount;


    void print(ostream& out)const;
public:
    WorkerPassenger(const char* pName, int theAge, char gen, float salary,
                        int seniority, int luggageWeight, const char* code, float disc);
    WorkerPassenger(const WorkerPassenger& wp) = delete;
    WorkerPassenger(WorkerPassenger&& wp) noexcept;
    virtual ~WorkerPassenger() {};

    // read and write from file
    WorkerPassenger(ifstream& in);
    void saveToFile(ofstream& out) const override;

    virtual void setRaise() override;
    virtual void prepareForFlight(ostream& out) override;
    virtual void annualRefresh(ostream& out) override;
    virtual void takeoff(ostream& out)const override;
    virtual void landing(ostream& out)const override;
};


