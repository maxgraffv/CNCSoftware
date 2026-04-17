#include "CoordinateSystem.h" 



CoordinateSystem::CoordinateSystem(double Id, double offsetX, double offsetY, double offsetZ)
    :Id(Id), offsetX(offsetX), offsetY(offsetY), offsetZ(offsetZ)
{


}
    
bool CoordinateSystem::operator<( const CoordinateSystem& other ) const
{
    return Id < other.Id;
}
