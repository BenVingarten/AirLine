#pragma once
#include <iostream>
using namespace std;
#include "Worker.h"
#include "Plane.h"


class Technician : public Worker
{

public:

	enum class eTechnicianType {STRUCTURE,
		                        NAVIGATIONS,
		                        COMMUNICATION,
		                        ENGINES,
		                        GENERAL
								};

	Technician(const char* n, int age, char gender, float salary, int seniority, eTechnicianType type = eTechnicianType::GENERAL);
	Technician(const Technician& other) = delete;
	Technician(Technician&& t) noexcept;
	~Technician() {};

	//read and write from file
	Technician(ifstream& in);
	void saveToFile(ofstream& out)const;

	eTechnicianType getType() const;
	const char* getStringType()const;
	int getNumOfPlanesPrepared()const;

	
	virtual void setRaise() override; //the number of planes prepared times 5 
	virtual void prepareForFlight(ostream& out)override;
	virtual void annualRefresh(ostream& out)override;
	virtual void takeoff(ostream& out)override;


private:


	eTechnicianType type;
	int planesPreparedThisYear; 

	void testSystems(ostream& out);
	void fillFuel(Plane* plane, ostream& out);
	void fixProblem(ostream& out);
	void print(ostream& out)const;

};

