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
	Technician(const Worker& w, eTechnicianType type);
	Technician(const Technician& other) = delete;
	Technician(Technician&& t) noexcept;
	Technician(ostream& out, istream& in);
	~Technician() {};

	eTechnicianType getType() const;
	int getNumOfPlanesPrepared()const;

	
	virtual void setRaise() override; //the number of planes prepared times 5 
	virtual void PrepareForFlight(Plane& plane, ostream& out) override;
	virtual void AnnualRefresh(ostream& out)override;


private:


	eTechnicianType type;
	int numOfPlanesPrepared;

	void testSystems(ostream& out);
	void fillFuel(Plane& plane, ostream& out);
	void fixProblem(ostream& out);
	void print(ostream& out)const;

};

