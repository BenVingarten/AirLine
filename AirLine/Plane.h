#pragma once
#include <iostream>
using namespace std;


#include "Technician.h"

class Plane
{
	const static int refuelAfter = 2; //every 2 flights
	static int planeNumberGen; //initialized outside the class to 3333

	static const int MIN_SEATS = 10;
	static const int MAX_SEATS = 250;
	static const int MAX_WEIGHT_PLANE = 9000;
	static const int MIN_SPEED_PLANE = 800;
	static const int MAX_SPEED_PLANE = 1000;

	int		planeNumber;
	float	maxSpeed;
	int		maxLuggageWeight;
	int		currentWeight;
	int		numOfSeats;
	bool	isAvailable;
	int		flightsCounter;
	bool	needToRefuel;

public:
	Plane(int numOfSeats, int maxLuggageWeight, float speed);
	
	//read and save to file
	Plane(ifstream& in);
	void saveToFile(ofstream& out)const;


	int getNumOfSeats()const;
	int getCurrentWeight()const;
	int getMaxWeight()const;
	float getMaxSpeed()const;
	int getMinSpeed()const;

	

	bool operator ==(const Plane& p)const;
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
	void setAvailability();
	
};


