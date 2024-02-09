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

double Material::get_polish() const
{
    return _polish;
}

Ray Material::get_reflect_ray(Ray& r, const HitInfo& hitdata, QVector3D& refl_coef, double& shine_coef) const
{
    refl_ray = Ray(hitdata.point, hitdata.normal - 2.0f * dotProduct(hitdata.normal, r.get_direction().normalized()))
}
