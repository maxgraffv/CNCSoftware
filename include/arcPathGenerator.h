#ifndef ARC_PATH_GENERATOR_H
#define ARC_PATH_GENERATOR_H

#include <vector>
#include "motionPlaneEnum.h"
#include "arcDistanceMode.h"
#include "distanceMode.h"

class ArcPath
{

    public:
    struct Point
    {
        double x;
        double y;
        double z;
    };

    static std::vector<Point> generate( 
        double start_x, double start_y, double start_z,
        double end_x, double end_y, double end_z,
        double i, double j, double k,
        MotionPlane plane, bool clockwise,
        ArcDistanceMode arcDistanceMode, DistanceMode distanceMode
    );

};


#endif