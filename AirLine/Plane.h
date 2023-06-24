#pragma once
#include <iostream>
using namespace std;

#define MIN_SEATS 10
#define MAX_SEATS 250
#define MIN_WEIGHT 3000 //avarage 150 passengers * 20 kg/pas
#define MAX_WEIGHT 9000
#define MIN_SPEED 800 //km per hour
#define MAX_SPEED 1000 

#include "Technician.h"

class Plane
{
	const static int refuelAfter = 2; //every 2 flights
	
	float	maxSpeed;
	int		maxLuggageWeight;
	int		currentWeight;
	int		numOfSeats;
	bool	IsAvailable;
	int		flightsCounter;
	bool	needToRefuel;
	bool    AreSystemsWork;
	bool	readyToFly;

public:
	Plane(int numOfSeats, int maxLuggageWeight, float maxSpeed);
	Plane(ostream& out, istream& in);


	int getNumOfSeats()const;
	int getCurrentWeight()const;
	int getMaxWeight()const;
	float getMaxSpeed()const;

	void readAndsetNumOfSeats(ostream& out, istream& in);
	void readAndsetLuggageWeight(ostream& out, istream& in);
	void readAndsetMaxSpeed(ostream& out, istream& in);

	bool operator += (int weight);
	friend ostream& operator << (ostream& out, const Plane& p);


	bool isNumOfSeatsValid(int numOfSeats)const;
	bool isMaxLuggageWeightValid(int weight)const;
	bool isMaxSpeedValid(float speed)const;

	bool isPlaneAvailable() const;
	bool areAllSystemsWork() const;
	void checkSystems(Technician& t);
	bool isPlaneFuled()const;

	void PlaneFuelRefill(Technician& tech);
	void preparePlane(Worker** workers);
	void planeAnnualCare(Worker** workers);
};

