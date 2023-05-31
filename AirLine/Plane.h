#pragma once
class Plane
{
	int numOfSeats;
	const float  MAX_WEIGHT = 1000; //KG
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

	bool isPlaneAvailable() const;
	bool isAllSystemsWork() const;
	bool isPlaneFuled()const;

	void PlaneFuelRefill(Technician& tech);
	void preparePlane(Worker** workers);
	void planeAnnualCare(Worker** workers);
};

