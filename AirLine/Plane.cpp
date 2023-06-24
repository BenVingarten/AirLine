#include "Plane.h"

Plane::Plane(int numOfSeats, int maxLuggageWeight, float maxSpeed)
    : numOfSeats(numOfSeats), maxLuggageWeight(maxLuggageWeight), 
        maxSpeed(maxSpeed), currentWeight(0), IsAvailable(true), 
        flightsCounter(0), needToRefuel(false),AreSystemsWork(true), readyToFly(true)
{
}

Plane::Plane(ostream& out, istream& in)
    :currentWeight(0), IsAvailable(true), flightsCounter(0), 
        needToRefuel(false), readyToFly(true)
{
    readAndsetNumOfSeats(out, in);
    readAndsetLuggageWeight(out, in);
    readAndsetMaxSpeed(out, in);

}

int Plane::getNumOfSeats() const {
    return numOfSeats;
}

int Plane::getCurrentWeight() const {
    return currentWeight;
}

int Plane::getMaxWeight() const {
    return maxLuggageWeight;
}

float Plane::getMaxSpeed() const {
    return maxSpeed;
}

bool Plane::operator+=(int weight) {
    if (currentWeight + weight <= maxLuggageWeight)
    {
        currentWeight += weight;
        return true;
    }
    return false;
}

ostream& operator<<(ostream& out, const Plane& p) {
    out << "Plane Details: " << endl;
    out << "Number of Seats: " << p.numOfSeats << endl;
    out << "Current Weight: " << p.currentWeight << endl;
    out << "Maximum Weight: " << p.maxLuggageWeight << endl;
    out << "Maximum Speed: " << p.maxSpeed << endl;
    out << "Number of flight: " << p.flightsCounter << endl;
    
    if(p.IsAvailable)
        out << "Plane is available " << endl;
    else 
        out << "Plane is not available " << endl;

    if (p.readyToFly)
        out << "Plane is ready to fly" << endl;
    else
        out << "Plane is not ready to fly" << endl;


    return out;
}


void Plane::readAndsetNumOfSeats(ostream& out, istream& in)
{
    do {
        out << "Enter number of seats between " << MIN_SEATS << " and " << MAX_SEATS << ": ";
        in >> numOfSeats;
        in.ignore(); // Ignore the newline character
    } while (!isNumOfSeatsValid(numOfSeats));
}

void Plane::readAndsetLuggageWeight(ostream& out, istream& in)
{
    do {
        cout << "Enter maximum luggage weight between " << MIN_WEIGHT << " and " << MAX_WEIGHT << ": ";
        in >> maxLuggageWeight;
        in.ignore(); // Ignore the newline character

    } while (!isMaxLuggageWeightValid(maxLuggageWeight));
}

void Plane::readAndsetMaxSpeed(ostream& out, istream& in)
{
    do {
        cout << "Enter maximum speed between " << MIN_SPEED << " and " << MAX_SPEED << ": ";
        in >> maxSpeed;
        in.ignore(); // Ignore the newline character

    } while (!isMaxSpeedValid(maxSpeed));
}

bool Plane::isNumOfSeatsValid(int numOfSeats)const
{
    return(numOfSeats < MIN_SEATS || numOfSeats > MAX_SEATS);
}

bool Plane::isMaxLuggageWeightValid(int weight)const
{
    return (weight < MIN_WEIGHT || weight > MAX_WEIGHT);
}

bool Plane::isMaxSpeedValid(float speed)const
{
    return(speed < MIN_SPEED || speed > MAX_SPEED);
}

bool Plane::isPlaneAvailable() const {
    return IsAvailable;
}

bool Plane::areAllSystemsWork() const 
{
    return AreSystemsWork;
}

bool Plane::isPlaneFuled() const {
    if(flightsCounter % 2 == 0) // meaning we done at least 2 flights
    return !needToRefuel;
}

void Plane::PlaneFuelRefill(Technician& tech) {
    tech.refillPlaneFuel(*this);
    needToRefuel = false;
}

void Plane::preparePlane(Worker** workers) {
    if (workers != nullptr) {
        // Perform necessary preparation tasks
        // Assuming implementation details here
        readyToFly = true;
    }
}

void Plane::planeAnnualCare(Worker** workers) {
    if (workers != nullptr) {
        // Perform annual care tasks
        // Assuming implementation details here
    }
}
