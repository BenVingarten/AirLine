#include "Time.h"

Time::Time(int hours, int minutes) : hours(hours), minutes(minutes) {}

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
    out << hours << ":" << minutes << ":" << seconds;
}

Time& Time::operator+=(const Time& other)
{
    hours += other.hours;
    
    int m = other.minutes + minutes;
    if (m >= 60)
    {
        hours++;
        m -= 60;
    }
    minutes = m;

   

}

ostream& operator<<(ostream& out, const Time& t) {
    t.print(out);
    return out;
}
