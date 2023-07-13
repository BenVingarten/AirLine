#pragma once
#include <iostream>
using namespace std;

#include "Person.h"
#include "Worker.h"
#include "Flight.h"

class Person;
class Plane;
class Worker;


class Technician : public Worker
{

public:

	enum class eTechnicianType {STRUCTURE,
		                        NAVIGATIONS,
		                        COMMUNICATION,
		                        ENGINES,
		                        GENERAL
								};

	Technician(const string&, int age, char gender, float salary, int seniority, eTechnicianType type = eTechnicianType::GENERAL);
	Technician(const Technician& other);
	Technician(Technician&& t) noexcept;
	~Technician() {};

	//read and write from file
	Technician(ifstream& in);
	void saveToFile(ofstream& out)const;
	

	eTechnicianType getType() const;
	string getStringType()const;
	int getNumOfPlanesPrepared()const;

	
	virtual void setRaise() ; //the number of planes prepared times 5 
	virtual void prepareForFlight(ostream& out) ;
	virtual void annualRefresh(ostream& out) ;
	virtual void takeoff(ostream& out)const ;
	virtual void landing(ostream& out)const ;
	Worker* clone()const { return new Technician(*this); }


private:


	eTechnicianType type;
	int planesPreparedThisYear; 

	void testSystems(ostream& out)const;
	void fillFuel(Plane* plane, ostream& out);
	void fixProblem(ostream& out)const;
	void print(ostream& out)const;

};
