#ifndef __SATELLITE_H__
#define __SATELLITE_H__

class Satellite {
    // ECI coordinates (time changing!)
    double xs;
    double ys;
    double zs;

    public: 
    Satellite(double xs, double ys, double zs) : xs(xs), ys(ys), zs(zs) {};
    double x();
    double y();
    double z();
};

#endif
