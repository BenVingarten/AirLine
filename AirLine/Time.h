#pragma once
#include <iostream>

using namespace std;


class Time
{
private:
    int hours;
    int minutes;

public:
    static const int HOURS_LIMIT_FOR_CLOCK = 24;
    static const int MINUTES_LIMIT = 60;

    Time(int hours = 0, int minutes = 0);
    virtual ~Time();

    bool setHours(int hours);
    bool setMinutes(int minutes);

    int getHours() const;
    int getMinutes() const;

    virtual void print(ostream& out) const;

    friend ostream& operator<<(ostream& out, const Time& t);
    Time& operator+=(const Time& other);
};
