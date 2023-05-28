#pragma once
#include <iostream>
using namespace std;
#include "Person.h"

class Worker : public Person
{

private:
	 static int WorkerIdGenerator; // will be initiallized to 1000 in main
	 int id;
	 float salary;
	 int seniority;
	 bool isWorkerAvailable;
	 bool isWorkerGotARaise;
	 Worker(const Worker& w) = default;

public:

	Worker(const char* pName, int theAge, char gen, float  salary, int seniority);
	Worker(const Person& p, float salary, int seniority);
	Worker(Worker&& w);

	bool updateSalary(float sal);
	int getWorkerId()const;
	float getSalary()const;
	int getSeniority()const;
	Worker& operator ++(); // add 1 year seniority
	friend ostream& operator <<(ostream& out, const Worker& w);

	virtual void setRaise() = 0;
	virtual void PrepareForFlight() = 0; 
	virtual void AnnualRefresh() = 0;

	
	 // set Raise:we check if a particular worker deserves a raise, every 3 years a worked should get one.
	                //for the pilot its 70% of his flightHours
					//for the flight attendet its 100 NIS per language she speaks
					// for the Technician its the number of tickets he sold times 5













};

