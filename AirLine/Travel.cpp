#define _CRT_SECURE_NO_WARNINGS

#include "Travel.h"
#include <fstream>

const char* Travel::DEFAULT_SOURCE_CODE = "TLV";
const char* Travel::DEFAULT_DEST_CODE = "ATH";

Travel::Travel(const char* s, const char* d) 
{
    if (airportCodeValid(s))
        setSource(s);
    else
        setSource(DEFAULT_SOURCE_CODE);

    if (airportCodeValid(d))
        setDest(d);
    else
        setDest(DEFAULT_DEST_CODE);

}

Travel::Travel(ifstream& in)
{
    in >> source;
    in >> destination;
    in.ignore();
}

void Travel::saveTravel(ofstream& out) const
{
    out << source << endl << destination << endl;
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

bool Travel::airportCodeValid(const char* code) {
    
    return strlen(code) >= (MAX_CHAR_CODE - 1);
}

