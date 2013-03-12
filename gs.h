#ifndef __GS_H__
#define __GS_H__

#include "util.h"

class GroundStation {
    // Geographic coordinates
    double latitude; // in decimal degrees
    double longitude; // in decimal degrees

    public:
    GroundStation(int lat_deg, int lat_min, double lat_sec, int long_deg, int long_min, double long_sec);
    GroundStation(double lat, double lon) : latitude(lat), longitude(lon) {};
    double lat();
    double lon();
};

#endif

