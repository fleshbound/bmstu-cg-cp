#include "utility/material/material.h"

QVector3D Material::get_diffuse() const
{
    return _diffuse;
}

QVector3D Material::get_reflective() const
{
    return _reflective;
}

QVector3D Material::get_ambient() const
{
    return _ambient;
}

/*
QVector3D Material::get_color() const
{
    return _color;
}
*/

double Material::get_polish() const
{
    return _polish;
}

Ray Material::get_reflect_ray(const Ray& r, const HitInfo& hitdata, QVector3D& refl_coef, double& shine_coef) const
{
    QVector3D l = r.get_direction();
    QVector3D n = hitdata.normal;
    QVector3D refl_dir = l - 2.0f * QVector3D::dotProduct(n, l.normalized()) * n;
    Ray refl_ray = Ray(hitdata.point, refl_dir);
    QVector3D rr = refl_ray.get_direction().normalized();
    QVector3D v = - r.get_direction().normalized();
    shine_coef = std::pow(QVector3D::dotProduct(rr, v) / (rr.length() * v.length()), _polish);
    refl_coef = _reflective;

    return refl_ray;
}
