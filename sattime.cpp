#include "sattime.h"
#include <math.h>

/// Return the Julian Date of the time object
double Time::jdate() {
    int a = (14.0 - months) / 12.0;
    int y = years + 4800.0 - a;
    int m = months + 12.0*a - 3.0;
    double jdate = days + (153*m + 2)/5 + 365*y + (y/4) - (y/100) + (y/400) - 32045;
    jdate += ((hours-12.0)/24.0) + (minutes/1440.0) + ((seconds+(microseconds/1000000.0))/86400.0);
    return jdate;
}

/// Takes the time since 00:00, Jan 1 1970 UTC in seconds and converts it to a Time object
/// Note this object will be relative to UTC (Greenwich)
Time::Time(time_t* time) {
    tm* t = gmtime(time);
    construct_help(t);
}

/// Takes a tm object from time.h and converts it to a Time object
Time::Time(tm* time) {
    construct_help(time);
}

/// Takes a timeval object from sys/time.h and converts it to a Time object
/// Note UTC
// TODO fix this, we don't want UTC here
Time::Time(timeval time) {
    tm* t = gmtime(&time.tv_sec);
    construct_help(t);
    microseconds = time.tv_usec;
}

unsigned Time::year() {
    return years;
}

unsigned Time::month() {
    return months;
}

unsigned Time::day() {
    return days;
}

unsigned Time::hour() {
    return hours;
}

unsigned Time::minute() {
    return minutes;
}

unsigned Time::second() {
    return seconds;
}

unsigned Time::microsecond() {
    return microseconds;
}

/// gmst in radians
double Time::gmst() {
    double ut;
    double intpart;
    double jd = jdate();
    ut = modf(jd+0.5, &intpart);
    jd -= ut;
    double tu = (jd - 2451545.0)/36525; //TODO wat are all these magic numbers
    double gmst = 24110.54841 + tu * (8640184.812866 + tu * (0.093104 - tu * 6.2e-6));
    gmst = (gmst + 86400.0*1.00273790934*ut);
    intpart = fmod(gmst, 86400.0);
    if (intpart < 0) {
        intpart += 86400.0;
    }
    gmst = intpart;
    gmst = 6.28318530718 * (gmst/86400.0);
    return gmst;
}

