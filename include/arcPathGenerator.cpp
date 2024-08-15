#include "arcPathGenerator.h"
#include <vector>
#include "motionPlaneEnum.h"
#include "arcDistanceMode.h"
#include "distanceMode.h"
#include <cmath>
#include <iostream>


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

    double dx = abs( center_x - end_x );
    double dy = abs( center_y - end_y );
    double dz = abs( center_z - end_z );

    double radius = 0;
    double startAngle = 0;
    double endAngle = 0;

    switch (plane)
    {
        case MotionPlane::XY :
            radius = std::sqrt( dx*dx + dy*dy );
            startAngle = std::atan2( start_y - center_y, start_x - center_x );
            endAngle = std::atan2( end_y - center_y, end_x - center_x );
            break;

        case MotionPlane::XZ :
            radius = std::sqrt( dx*dx + dz*dz );
            startAngle = std::atan2( start_z - center_z, start_x - center_x );
            endAngle = std::atan2( end_z - center_z, end_x - center_x );
            break;    

        case MotionPlane::YZ :
            radius = std::sqrt( dy*dy + dz*dz );
            startAngle = std::atan2( start_z - center_z, start_y - center_y );
            endAngle = std::atan2( end_z - center_z, end_y - center_y );
            break;
    
        default:
            break;
    }


    if(!clockwise)
    {
        if( startAngle > endAngle )
            startAngle -= 2*PI;
    }
    else
    {
        if( startAngle < endAngle )
        {
            endAngle -= 2*PI;
        }
        else
        {
        }
    }
        


    double angle = abs( endAngle - startAngle );
    if(angle == 0)
    {
        angle = 2*PI;
        endAngle += 2*PI;
    }
    double partOfCircle = angle/(2*PI);
    double pathLength = (2*PI*radius)*partOfCircle;
    int resolution = static_cast<int>( pathLength/0.1 );
    if((resolution - 1) == 0)
    {
        std::cout << "ERROR HUGE F" << std::endl;
        resolution += 1;
    }

    double angleStep = (endAngle - startAngle) / resolution;

    double moveByAngle = 0;

    std::cout << "ARC GOOD???!!! Angle: "<< angle << std::endl;
    std::cout << "ARC GOOD???!!! CirclePercent: "<< partOfCircle << std::endl;
    std::cout << "ARC GOOD???!!! PTH LEN: "<< pathLength << std::endl;
    std::cout << "ARC GOOD???!!! RES: "<< resolution << std::endl;

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

    for(int i = 0; i < path.size(); i++)
        std::cout << "PATH: \t X: " << path[i].x << "\t Y: " << path[i].y << " \t Z:" << path[i].z << std::endl;

    return path;
}