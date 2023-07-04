#define _CRT_SECURE_NO_WARNINGS

#include "TripInfo.h"
#include <fstream>

TripInfo::TripInfo(const char* src, const char* des, int d, int m, int y, int hour, int minute)
    : Travel(src, des), date(d, m, y), flightDuration(hour, minute)
{
}

TripInfo::TripInfo(const Date& d, const Travel& trav, const Time& time)
    : Travel(trav), date(d), flightDuration(time)
{
}

TripInfo::TripInfo(ifstream& in) : Travel(in)
{
    in.ignore();
    date = Date(in);
    in.ignore();
    flightDuration = Time(in);
}

void TripInfo::saveToFile(ofstream& out)
{
    Travel::saveTravel(out);
    date.saveDate(out);
    flightDuration.saveTime(out);
}


void TripInfo::print(ostream& out) const {
    
    out << " Trip Info: " ;
    Travel::print(out);
    out <<", " << date << ", Duration: " << flightDuration << endl;
}

void TripInfo::setDuration(int hour, int minute) {
    flightDuration.setHours(hour);
    flightDuration.setMinutes(minute);
}

const Time& TripInfo::getFlightDuration() const {
    return flightDuration;
}


ostream& operator<<(ostream& out, const TripInfo& t) {
    t.print(out);
    return out;
}