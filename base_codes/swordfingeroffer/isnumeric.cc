#include <string>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

bool isNumeric(std::string& s) {
    if (s.length() == 0)  return false;
    int index = 0;
    bool isnumeric = scanInteger(s, index);
    if (index < s.length() && s[index] == '.') {
        index++;
        isnumeric = scanUnsignedInteger(s, index) || isnumeric;
    }
    if (index < s.length() && (s[index] == 'e' || s[index] == 'E')) {
        index++;
        isnumeric = isnumeric && scanInteger(s, index);
    }
    return isnumeric;
}

bool scanInteger(std::string& s, int& index) {
    if (s[index] == '+' || s[index] == '-') {
        index++;
    }
    return scanUnsignedInteger(s, index);
}

bool scanUnsignedInteger(std::string& s, int& index) {
    while (index < s.length() && s[index] >= '0' && s[index] <= '9') {
        index++;
    }
    if (s.length() == index || (s[index] == '.'  && index > 0)|| ((s[index] == 'e' || s[index] == 'E') && index>0)) return true;
    return false;
}


} // namespace sword_finger_offer
