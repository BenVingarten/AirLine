#pragma once
class Plane
{
	int numOfSeats;
	const static int  MAX_WEIGHT = 1000; //KG
	int currentWeight;
	float maxSpeed;
	bool IsAvailable;
	int flightsCounter;
	bool needToRefuel;
	const static int refuelAfter = 2; //every 2 flights
	bool readyToFly;

public:
	Plane(int numofSeats, int maxLuggageWeight, float maxSpeed);

	int getNumOfSeats()const;
	int getCurrentWeight()const;
	int getMaxWeight()const;
	float getMaxSpeed()const;

	Plane& operator += (int weight);
	friend ostream& operator << (ostream& out, const Plane& p);

	void PlaneFuelRefill(Technician& tech);
	bool isPlaneAvailable() const;
	bool isAllSystemsWork() const;
	bool isPlaneFuled()const;
	void preparePlane(Worker** workers);
	void planeAnnualCare(Worker** workers);
};

