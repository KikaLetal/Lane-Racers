#include "Utils.h"

string to_string_with_precision(const float a_value, const int n) {
    ostringstream out;
    out << fixed << setprecision(n) << a_value;
    return out.str();
}