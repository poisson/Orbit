#ifndef __SATTIME_H__
#define __SATTIME_H__

#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <stdint.h>

class Time {
    unsigned int years;
    unsigned int months;
    unsigned int days;
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;
    unsigned int microseconds;

    public:
    double jdate();
    Time(unsigned yr = 0, unsigned mo = 0, unsigned d = 0, unsigned hr = 0, unsigned min = 0, unsigned sec = 0, unsigned micro = 0) : years(yr), months(mo), days(d), hours(hr), minutes(min), seconds(sec), microseconds(micro) {};
    Time(time_t* time);
    Time(tm* time);
    Time(timeval time);
    unsigned year();
    unsigned month();
    unsigned day();
    unsigned hour();
    unsigned minute();
    unsigned second();
    unsigned microsecond();
    double gmst();
    
    private:
    inline void construct_help(tm* time) {
        if (time == NULL) {
            years = 0;
            months = 0;
            days = 0;
            hours = 0;
            minutes = 0;
            seconds = 0;
            microseconds = 0;
            return;
        }
        years = time->tm_year + 1900;
        months = time->tm_mon + 1;
        days = time->tm_mday;
        hours = time->tm_hour;
        minutes = time->tm_min;
        seconds = time->tm_sec;
        return;
    }

};


#endif
