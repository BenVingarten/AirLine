#pragma once
class Time
{
private:
	int hours;
	int minutes;

public:
	Time(int hour, int minutes);
	bool setHour(int hour);
	bool setMinutes(int m); 

	int getHours()const;
	int getMinutes()const;

	friend ostream& operator <<(ostream& out, const Time& t);
};

