#include <iostream>
#include <iomanip>
#include "util.h"
#include "gs.h"
#include "satellite.h"
#include "sattime.h"

/// WGS84/EGM84 Ellipsoid
//static const double GPS_A = 6378137.0;
//const double GPS_F = 1/298.257223563;
//const double GPS_B = GPS_A * (1.0 - GPS_F);

// WGS74 for debugging
const double GPS_A = 6378.135;
const double GPS_F = 1/298.26;
const double GPS_B = GPS_A * (1.0 - GPS_F);
const double PI = 3.1415926536;

struct look_angle {
    double azimuth;
    double elevation;
    double range;
};

look_angle eci_look_angle(GroundStation gs, Satellite sat, Time time);

/// Uses WGS84 ellipsoid
// TODO figure out which ECI coordinate system this is
look_angle eci_look_angle(GroundStation gs, Satellite sat, Time time) {
    double lst = time.gmst() + ((gs.lon() / 180) * PI);
    std::cout << std::setprecision(32) << "Local sidereal time:" << (lst * 180) / PI << std::endl;
    double psi = (gs.lat() / 180) * PI; // correct at least to this line
    std::cout << std::setprecision(32) << "Latitude in radians:" << psi << std::endl;
    double C = 1 / sqrt(1 + (GPS_F * (GPS_F - 2) * sin(psi)));
    std::cout << std::setprecision(32) << "C:" << C << std::endl;
    double S = (1-GPS_F)*(1-GPS_F)*C;
    std::cout << std::setprecision(32) << "S :" << S << std::endl;
    // calculate ground station ECI coords
    double gs_x = GPS_A * C * cos(psi) * cos(lst);
    std::cout << std::setprecision(32) << "gs_x :" << gs_x << std::endl;
    double gs_y = GPS_A * C * cos(psi) * sin(lst);
    std::cout << std::setprecision(32) << "gs_y :" << gs_y << std::endl;
    double gs_z = GPS_A * S * sin(psi);
    std::cout << std::setprecision(32) << "gs_z :" << gs_z << std::endl;
    // calculate range vector
    double range_x = sat.x() - gs_x;
    std::cout << std::setprecision(32) << "range_X :" << range_x << std::endl;
    double range_y = sat.y() - gs_y;
    std::cout << std::setprecision(32) << "range_y :" << range_y << std::endl;
    double range_z = sat.z() - gs_z;
    std::cout << std::setprecision(32) << "range_z :" << range_z << std::endl;
    // transform to topocentric-horizon system
    double range_south = sin(psi) * cos(lst) * range_x + sin(psi) * sin(lst) * range_y - cos(psi) * range_z;
    std::cout << std::setprecision(32) << "range_south :" << range_south << std::endl;
    double range_east = -sin(lst) * range_x + cos(lst) * range_y;
    std::cout << std::setprecision(32) << "range_east :" << range_east << std::endl;
    double range_zenith = cos(psi) * cos(lst) * range_x + cos(psi) * sin(lst) * range_y + sin(psi) * range_z;
    std::cout << std::setprecision(32) << "range_zenith :" << range_zenith << std::endl;
    // calculate azimuth/elevation/range
    look_angle result;
    result.range = sqrt(range_south*range_south + range_east*range_east + range_zenith*range_zenith);
    result.elevation = asin(range_zenith / result.range);
    result.azimuth = atan(-range_east/range_south);
    if (range_south > 0) 
        result.azimuth = result.azimuth + PI;
    if (result.azimuth < 0)
        result.azimuth = result.azimuth + 2 * PI;
    // and return it!
    return result;
}

int main() {
    Time ex_t(1995, 11, 18, 12, 46, 0, 0);
    std::cout << std::setprecision(32) << "JD: " << ex_t.jdate() << std::endl;
    std::cout << "GMST: " << (ex_t.gmst() * 180) / PI << std::endl;
    GroundStation gs(45, 0, 0.0, -93, 0, 0.0);
    std::cout << "GS latitude: " << gs.lat() << std::endl;
    std::cout << "GS longitude: " << gs.lon() << std::endl;
    Satellite mir(-4400.594, 1932.870, 4760.712);
    look_angle answer = eci_look_angle(gs, mir, ex_t);
    std::cout << "Azimuth: " << (answer.azimuth * 180) / PI << std::endl << "Elevation: " << (answer.elevation*180) / PI << std::endl << "Range: " << answer.range << std::endl;
}

