#pragma once
#include <iostream>
using namespace std;
#include "Worker.h"
#include "Plane.h"


class Technician : public Worker
{
private:

	enum class eTechnicianType {Avionics,
		                        Navigation,
		                        Communication,
		                        Engines,
		                        General 
								};

	eTechnicianType type;
	int numOfPlanesPrepared;

	void testSystems(Plane& p);
	void fillFuel(Plane& plane);

	void print(ostream& out)const;

public:

	Technician(const char* n, int age, char gender, float salary, int seniority, eTechnicianType type);
	Technician(const Worker& w);
	Technician(const Technician& other) = delete;
	Technician(Technician&& t) noexcept;

	eTechnicianType getType() const;
	int getNumOfPlanesPrepared()const;


	bool operator ==(const Worker& worker)const;
	virtual void setRaise() override;
	virtual void PrepareForFlight() override;
	virtual void AnnualRefresh()override;

	Worker& operator ++ ();
};

