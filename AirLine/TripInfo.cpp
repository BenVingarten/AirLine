#include "TripInfo.h"

TripInfo::TripInfo(const char src[3], const char des[3], int d, int m, int y, int hour, int minute)
    : Date(d, m, y), Travel(src, des), flightDuration(hour, minute)
{
}

TripInfo::TripInfo(const Date& d, const Travel& trav, const Time& time)
    : Date(d), Travel(trav), flightDuration(time)
{
}

TripInfo::TripInfo(ostream& out, istream& in)
{
	out << "Enter flight information:" << endl;
	in.ignore(); // Ignore the newline character

	// Read destination and source
	char destination[MAX_CHAR_CODE];
	char source[MAX_CHAR_CODE];
	out << "Destination: ";
	in.getline(destination, MAX_CHAR_CODE);
	out << "Source: ";
	in.getline(source, MAX_CHAR_CODE);

	// Read date and time
	int dHour, dMinute, day, month, year;
	out << "Duration Time:" << endl;
	out << "Hour: ";
	in >> dHour;
	out << "Minute: ";
	in >> dMinute;
	out << "Date:" << endl;
	out << "Day: ";
	in >> day;
	out << "Month: ";
	in >> month;
	out << "Year: ";
	in >> year;
}


void TripInfo::print(ostream& out) const {
    
    out << " Trip Info: \n";
    Date::print(out);
    out << " \n";
    Travel::print(out);
    
    out << " \nFlight Duration: " << flightDuration<< endl;
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