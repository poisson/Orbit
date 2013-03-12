#include "util.h"

double dms_to_dd(int deg, int min, double sec) {
    return deg + min/60.0 + sec/3600.0;
}

