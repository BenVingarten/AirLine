#pragma once
#include <iostream>
using namespace std;
#include "Person.h"

class Worker : public Person
{

private:
	 static int WorkerIdGenerator; // will be initiallized to 1000
	 int id;
	 float salary;
	 int seniority;
	 bool isWorkerAvailable;
	 bool isWorkerGotARaise;


public:

	Worker(const char* pName, int theAge, char gen, float salary, int seniority);   // c'tor with all params
	Worker(const Person& p, float salary, int seniority);                           // c'tor with Person object
	Worker(Person&& p, float salary, int seniority);							    // move c'tor with person object
	
	friend ostream& operator <<(ostream& out, const Worker& w);						// operaor <<
	Worker& operator ++();															// operator ++ for seniority (each year)

	float getSalary()const;
	int getSeniority()const;
	bool getIsAvailable() const;

	bool updateSalary(float newSalary);
	void changeAvailabilty(); // we just do  isWorkerAvailable = !isWorkerAvailable

	
	void setRaise(); // we check if a particular worker deserves a raise, every 3 years a worked should get one.
	                //for the pilot its 70% of his flightHours
					//for the flight attendet its 100 NIS per language she speaks
					// for the TravelAgent its the number of tickets he sold times 5













};

