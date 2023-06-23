#include "Travel.h"

Travel::Travel(const char s[MAX_CHAR_CODE], const char d[MAX_CHAR_CODE]) {
    strcpy(source, s);
    source[MAX_CHAR_CODE - 1] = '\0';
    strcpy(destination, d);
    destination[MAX_CHAR_CODE - 1] = '\0';
}

bool Travel::setSource(const char s[MAX_CHAR_CODE]) {
    strcpy(source, s);
    return true;
}

bool Travel::setDest(const char d[MAX_CHAR_CODE]) {
    strcpy(destination, d);
    return true;
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
