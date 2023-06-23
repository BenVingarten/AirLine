#include "TripInfo.h"

TripInfo::TripInfo(const char src[3], const char des[3], int d, int m, int y, int hour, int minute)
    : Date(d, m, y), Travel(src, des), flightDuration(hour, minute)
{
}

TripInfo::TripInfo(const Date& d, const Travel& trav, const Time& time)
    : Date(d), Travel(trav), flightDuration(time)
{
}

void TripInfo::print(ostream& out) const {
    
    out << " Trip Info: \n";
    Date::print(out);
    out << " \n";
    Travel::print(out);
    
    out << " \nFlight Duration: " << flightDuration<< endl;
}

void TripInfo::setTime(int hour, int minute) {
    flightDuration.setHours(hour);
    flightDuration.setMinutes(minute);
}

Time TripInfo::getFlightDuration() const {
    return flightDuration;
}


ostream& operator<<(ostream& out, const TripInfo& t) {
    t.print(out);
    return out;
}