#pragma once
#include <iostream>

using namespace std;

class Time
{
private:
    int hours;
    int minutes;
    int seconds;

public:
    static const int HOURS_LIMIT = 24;
    static const int MINUTES_LIMIT = 60;
    static const int SECONDS_LIMIT = 60;

    Time(int hours = 0, int minutes = 0, int seconds = 0);
    virtual ~Time();

    bool setHours(int hours);
    bool setMinutes(int minutes);
    bool setSeconds(int seconds);

    int getHours() const;
    int getMinutes() const;
    int getSeconds() const;

    virtual void print(ostream& out) const;

    friend ostream& operator<<(ostream& out, const Time& t);
};
