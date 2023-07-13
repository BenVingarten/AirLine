#pragma once
#include <iostream>
#include "Save.h"

using namespace std;


class Time: public Save
{
private:
    static const int DEF_H = 0;
    static const int DEF_M = 0;
    static const int HOURS_LIMIT_FOR_CLOCK = 24;
    static const int MINUTES_LIMIT = 60;

    int hours;
    int minutes;

public:

    Time(int hours = DEF_H, int minutes = DEF_M);

    //read and save to file
    Time(ifstream& in);
    void saveToFile(ofstream& out) const;

    virtual ~Time();

    bool setHours(int hours);
    bool setMinutes(int minutes);

    int getHours() const;
    int getMinutes() const;

    virtual void print(ostream& out) const;

    friend ostream& operator<<(ostream& out, const Time& t);
    Time& operator+=(const Time& other);
};
