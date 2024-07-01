#include "object/invisibleobject/light/light.h"

void Light::move(const QVector3D& d)
{
    _pos += d;
}

void Light::update()
{
    _pos.normalize();
}

bool Light::hit(const Ray& r, const double t_min, const double t_max, HitInfo& hitdata) const
{
    return false;
}

QVector3D Light::get_pos() const
{
    return _pos;
}

QVector3D Light::get_ints() const
{
    return _ints;
}

void Light::set_ints(const QVector3D& new_ints)
{
    _ints = new_ints;
}

Ray Light::get_ray(const QVector3D& hit_p) const
{
    return Ray(hit_p, _pos.normalized());
}
