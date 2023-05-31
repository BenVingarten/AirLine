#pragma once
#include <iostream>
using namespace std;
#include "Person.h"

class Flight;
class Worker : public Person
{

private:
	 static int WorkerIdGenerator; // will be initiallized to 1000 in main
	 int id;
	 float salary;
	 int seniority;
	 Flight* currentFlight;
	 bool isWorkerAvailable;
	
	 Worker(const Worker& w) = default;

protected:
	 void print(ostream& out)const;

public:

	Worker(const char* pName, int theAge, char gen, float  salary, int seniority);
	Worker(const Person& p, float salary, int seniority);
	Worker(Worker&& w) noexcept;
	virtual ~Worker();

	
	int getWorkerId()const;
	float getSalary()const;
	int getSeniority()const;
	bool isAvailable()const;


	bool updateSalary(float sal);
	bool setFlight(Flight* flight);

	Worker& operator ++(); // add 1 year seniority
	
	virtual bool operator ==(const Worker& worker)const;
	virtual void setRaise() = 0;
	virtual void PrepareForFlight() = 0; 
	virtual void AnnualRefresh() = 0;

	
	 // set Raise:we check if a particular worker deserves a raise, every 3 years a worker should get one.
	                //for the pilot its 70% of his flightHours
					//for the flight attendet its 100 NIS per language she speaks
					// for the Technician its the number of tickets he sold times 5













};

