#include "Time.h"

Time::Time(int hours, int minutes, int seconds) : hours(hours), minutes(minutes), seconds(seconds) {}

Time::~Time() {}

bool Time::setHours(int hours) {
    if (hours >= 0 && hours < HOURS_LIMIT) {
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

bool Time::setSeconds(int seconds) {
    if (seconds >= 0 && seconds < SECONDS_LIMIT) {
        this->seconds = seconds;
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

int Time::getSeconds() const {
    return seconds;
}

void Time::print(ostream& out) const {
    out << hours << ":" << minutes << ":" << seconds;
}

ostream& operator<<(ostream& out, const Time& t) {
    t.print(out);
    return out;
}
