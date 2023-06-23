#include "Travel.h"

Travel::Travel(char s[3], char d[3]) {
    strcpy(source, s);
    strcpy(destination, d);
}

bool Travel::setSource(char s[3]) {
    strcpy(source, s);
    return true;
}

bool Travel::setDest(char d[3]) {
    strcpy(destination, d);
    return true;
}

Travel::~Travel() {}

void Travel::print(ostream& out) const {
    out << "Source: " << source << ", Destination: " << destination;
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
