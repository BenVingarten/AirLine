#pragma once
#include <iostream>
using namespace std;

#define MIN_SEATS 10
#define MAX_SEATS 250
#define MIN_WEIGHT 3000 //avarage 150 passengers * 20 kg/pas
#define MAX_WEIGHT_PLANE 9000
#define MIN_SPEED 800 //km per hour
#define MAX_SPEED 1000 

#include "Technician.h"

class Plane
{
	const static int refuelAfter = 2; //every 2 flights
	static int planeNumberGen; //initialized outside the class to 3333

	int planeNumber;
	float	maxSpeed;
	int		maxLuggageWeight;
	int		currentWeight;
	int		numOfSeats;
	bool	isAvailable;
	int		flightsCounter;
	bool	needToRefuel;

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

	bool operator += (int weight); //add weight
	void operator ++ (); //add flight 
	friend ostream& operator << (ostream& out, const Plane& p);



	bool isNumOfSeatsValid(int numOfSeats)const;
	bool isMaxLuggageWeightValid(int weight)const;
	bool isMaxSpeedValid(float speed)const;

	bool isPlaneAvailable() const;
	bool isPlaneFuled()const;
	bool isReadyToFly()const ;

	void setNeedToRefuelFalse();
	
};

int Plane::planeNumberGen = 3333;
