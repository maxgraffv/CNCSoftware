#include "arcPathGenerator.h"
#include <vector>
#include "motionPlaneEnum.h"
#include "arcDistanceMode.h"
#include "distanceMode.h"
#include <cmath>


std::vector<ArcPath::Point> ArcPath::generate(  double start_x, double start_y, double start_z,
        double end_x, double end_y, double end_z,
        double i, double j, double k,
        MotionPlane plane, bool clockwise,
        ArcDistanceMode arcDistanceMode, DistanceMode distanceMode
)
{

    std::vector<Point> path;
    const double PI = 3.14159265358979323846;

    switch( distanceMode )
    {
        case DistanceMode::absoluteDistance :
            end_x = end_x;
            end_y = end_y;
            end_z = end_z;
            break;

        case DistanceMode::incrementalDistance :
            end_x += start_x;
            end_y += start_y;
            end_z += start_z;
            break;
    }

    double center_x = 0;
    double center_y = 0;
    double center_z = 0;

    switch( arcDistanceMode )
    {
        case ArcDistanceMode::absolute :
            center_x = i;
            center_y = j;
            center_z = k;
            break;
        
        case ArcDistanceMode::incremental :
            center_x = start_x + i;
            center_y = start_y + j;
            center_z = start_z + k;
            break;
    }

    double radius = std::sqrt( i*i + j*j + k*k );
    double startAngle = 0;
    double endAngle = 0;

    switch (plane)
    {
        case MotionPlane::XY :
            startAngle = std::atan2( start_y - center_y, start_x - center_x );
            endAngle = std::atan2( end_y - center_y, end_x - center_x );
            break;

        case MotionPlane::XZ :
            startAngle = std::atan2( start_z - center_z, start_x - center_x );
            endAngle = std::atan2( end_z - center_z, end_x - center_x );
            break;    

        case MotionPlane::YZ :
            startAngle = std::atan2( start_z - center_z, start_y - center_y );
            endAngle = std::atan2( end_z - center_z, end_y - center_y );
            break;
    
        default:
            break;
    }

    if(clockwise)
        if( startAngle < endAngle )
            startAngle += 2*PI;
    else
        if( startAngle > endAngle )
            startAngle -= 2*PI;


    double angle = abs( endAngle - startAngle );
    double partOfCircle = angle/(2*PI);
    double pathLength = (2*PI*radius)*partOfCircle;
    int resolution = static_cast<int>( pathLength/0.01 );

    double angleStep = (endAngle - startAngle) / resolution;

    double moveByAngle = 0;

    for(int i = 0; i < resolution; i++)
    {
        moveByAngle = startAngle + i*angleStep;
        Point point;

        switch(plane)
        {
            case MotionPlane::XY :
                point.x = center_x + radius * std::cos(moveByAngle);
                point.y = center_y + radius * std::sin(moveByAngle);
                point.z = start_z + (end_z - start_z) * (i / static_cast<double>(resolution - 1));
                break;
            case MotionPlane::XZ :
                point.x = center_x + radius * std::cos(moveByAngle);
                point.z = center_z + radius * std::sin(moveByAngle);
                point.y = start_y + (end_y - start_y) * (i / static_cast<double>( resolution - 1));
                break;
            case MotionPlane::YZ :
                point.y = center_y + radius * std::cos(moveByAngle);
                point.z = center_z + radius * std::sin(moveByAngle);
                point.x = start_x + (end_x - start_x) * (i / static_cast<double>( resolution - 1));
                break;

        }
        path.push_back(point);
    }
    return path;
}