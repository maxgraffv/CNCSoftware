#ifndef COORDINATE_SYSTEM_H
#define COORDINATE_SYSTEM_H

struct CoordinateSystem
{
    double Id;

    double offsetX;
    double offsetY;
    double offsetZ;

    CoordinateSystem(double Id, double offsetX, double offsetY, double offsetZ);

    bool operator<( const CoordinateSystem& other ) const;


};

#endif