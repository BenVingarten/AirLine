#define _CRT_SECURE_NO_WARNINGS

#include "Travel.h"
#include <fstream>

Travel::Travel(const char* s, const char* d) 
{
    if (airportCodeValid(s))
        setSource(s);

    if (airportCodeValid(d))
        setDest(d);

}

Travel::Travel(ifstream& in)
{
    char tmp;
    in >> source >> tmp >> destination;
}

void Travel::saveTravel(ofstream& out) const
{
    out << source << DEL << destination << endl;
}



void Travel::setSource(const char* s) {
    strcpy(source, s);
    source[MAX_CHAR_CODE-1] = '\0';
}

void Travel::setDest(const char* d) {
    strcpy(destination, d);
    destination[MAX_CHAR_CODE - 1] = '\0';
}


void Travel::print(ostream& out) const {
    out << "Travel: Source: " << source << ", Destination: " << destination;
}

ostream& operator<<(ostream& out, const Travel& t) {
    t.print(out);
    return out;
}

const char* Travel::getSource() const {
    return source;
}

const char* Travel::getDestenation() const {
    return destination;
}

bool Travel::airportCodeValid(const char* code) const {
    
    return strlen(code) == (MAX_CHAR_CODE - 1);
}

