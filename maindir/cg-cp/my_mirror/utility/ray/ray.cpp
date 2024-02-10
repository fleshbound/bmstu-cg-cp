#include "utility/ray/ray.h"

Ray::Ray(const QVector3D& origin, const QVector3D& direction)
{
    _origin = origin;
    _direction = direction;
}

QVector3D Ray::get_direction() const
{
    return _direction;
}

QVector3D Ray::get_origin() const
{
    return _origin;
}

QVector3D Ray::get_point_by_t(const double t) const
{
    return t * _direction + _origin;
}
