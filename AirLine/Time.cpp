#define _CRT_SECURE_NO_WARNINGS

#include "Time.h"
#include <fstream>

Time::Time(int hours, int minutes) : hours(hours), minutes(minutes) {}

Time::Time(ifstream& in)
{
    char tmp;
    in >> hours >> tmp >> minutes;
}

void Time::saveTime(ofstream& out) const
{
    out << hours << DEL << minutes << endl;
}

Time::~Time() {}

bool Time::setHours(int hours) {
    if (hours >= 0) {
        this->hours = hours;
        return true;
    }
    return false;
}

bool Time::setMinutes(int minutes) {
    if (minutes >= 0 && minutes < MINUTES_LIMIT) {
        this->minutes = minutes;
        return true;
    }
    return false;
}

int Time::getHours() const {
    return hours;
}

int Time::getMinutes() const {
    return minutes;
}

void Time::print(ostream& out) const {
    out << hours << ":" << minutes << endl;
}

Time& Time::operator+=(const Time& other)
{
    hours += other.hours;
    
    int m = other.minutes + minutes;
    if (m >= MINUTES_LIMIT)
    {
        hours++;
        m -= MINUTES_LIMIT;
    }
    minutes = m;

    return *this;

}

ostream& operator<<(ostream& out, const Time& t) {
    t.print(out);
    return out;
}
