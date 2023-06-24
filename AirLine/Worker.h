#pragma once
#include <iostream>
using namespace std;
#include "Person.h"

#define MINIMUM_WAGE 1000

class Flight;
class Worker : public Person
{

private:
	 static int workerCardNumberGenerator; //initiallized outside of the class to 2222 (only once!)
	 int cardNumber;
	 float salary;
	 int seniority;
	 Flight* currentFlight;
	 bool isWorkerAvailable;
	
	 Worker(const Worker& w) = default;

protected:
	 void print(ostream& out)const;

/*
* only the one's inheritance from worker will use these functions
* we can't create worker in the main
*/

	Worker(const char* pName, int theAge, char gen, float  salary, int seniority);
	Worker(const Person& p, float salary, int seniority);
	Worker(Worker&& w) noexcept;
	Worker(ostream& out, istream& in);
	virtual ~Worker() {};

	
	int getWorkerId()const;
	float getSalary()const;
	int getSeniority()const;
	bool isAvailable()const;

	bool isSalaryValid(float salary)const;
	void readAndsetSalary(ostream& out, istream& in);
	void readAndsetSeniority(ostream& out, istream& in);
	bool setFlight(Flight* flight);

	Worker& operator ++(); // add 1 year seniority
	
	virtual bool operator ==(const Worker& worker)const;
	virtual void setRaise() = 0;
	virtual void PrepareForFlight() = 0; 
	virtual void AnnualRefresh() = 0;

	
	
	/*	set Raise: We check if a particular worker deserves a raise, every 3 years a worker should get one.
			for the pilot its 70% of his flightHours
			for the flight attendet its 100 NIS per language she speaks
			for the Technician its the number of tickets he sold times 5 */

};

int Worker::workerCardNumberGenerator = 2222;

