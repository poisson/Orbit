#include "gs.h"
#include <iostream>

GroundStation::GroundStation(int lat_deg, int lat_min, double lat_sec, int long_deg, int long_min, double long_sec) {
    latitude = dms_to_dd(lat_deg, lat_min, lat_sec);
    longitude = dms_to_dd(long_deg, long_min, long_sec);
}

double GroundStation::lat() {
    return latitude;
}

double GroundStation::lon() {
    return longitude;
}
