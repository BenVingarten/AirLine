#include "Plane.h"

Plane::Plane(int numOfSeats, int maxLuggageWeight, float maxSpeed)
    : numOfSeats(numOfSeats), maxLuggageWeight(maxLuggageWeight), 
        maxSpeed(maxSpeed), currentWeight(0), isAvailable(true), 
        flightsCounter(0), needToRefuel(false)
{
    planeNumber = planeNumberGen++;
}

Plane::Plane(ostream& out, istream& in)
    :currentWeight(0), isAvailable(true), flightsCounter(0), 
        needToRefuel(false)
{
    readAndsetNumOfSeats(out, in);
    readAndsetLuggageWeight(out, in);
    readAndsetMaxSpeed(out, in);
    planeNumber = planeNumberGen++;
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

void Plane::operator++()
{

    flightsCounter++;
    if (flightsCounter % 2 == 0)
        needToRefuel = true;
}

ostream& operator<<(ostream& out, const Plane& p) {
    out << "Plane Number "<< p.planeNumber << " Details: " << endl;
    out << "Number of Seats: " << p.numOfSeats << endl;
    out << "Current Weight: " << p.currentWeight << endl;
    out << "Maximum Weight: " << p.maxLuggageWeight << endl;
    out << "Maximum Speed: " << p.maxSpeed << endl;
    out << "Number of flight: " << p.flightsCounter << endl;
    
    if(p.isAvailable)
        out << "Plane is available " << endl;
    else 
        out << "Plane is not available " << endl;

    if (p.isReadyToFly())
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
        cout << "Enter maximum luggage weight between " << MIN_WEIGHT << " and " << MAX_WEIGHT_PLANE << ": ";
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
    return (weight < MIN_WEIGHT || weight > MAX_WEIGHT_PLANE);
}

bool Plane::isMaxSpeedValid(float speed)const
{
    return(speed < MIN_SPEED || speed > MAX_SPEED);
}

bool Plane::isPlaneAvailable() const {
    return isAvailable;
}

bool Plane::isPlaneFuled() const {
   
    return !needToRefuel;
}

bool Plane::isReadyToFly() const
{
    if (!needToRefuel && isAvailable)
        return true;
    else
        return false;

}

void Plane::setNeedToRefuelFalse()
{
    needToRefuel = false;
}



