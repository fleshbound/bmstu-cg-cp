#ifndef MATERIAL_H
#define MATERIAL_H

#include "object/object.h"
#include "utility/ray/ray.h"
#include <QVector3D>

class Material
{
    friend class Model;
    friend class VisibleObject;
    friend class BaseBuilder;

public:
    QVector3D get_diffuse() const;
    QVector3D get_reflective() const;
    QVector3D get_ambient() const;
    double get_polish() const;
    Ray get_reflect_ray(Ray& r, const HitInfo& hitdata, QVector3D& refl_coef, double& shine_coef) const;

private:
    QVector3D _diffuse;
    QVector3D _ambient;
    QVector3D _reflective;
    double _polish;
};

#endif // MATERIAL_H
