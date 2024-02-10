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
    Material(const QVector3D& ambient, const QVector3D& diffuse, const QVector3D& reflective, const double &polish = 0):
        _ambient(diffuse * ambient),
        _diffuse(diffuse),
        _reflective(reflective),
        _polish(polish)
    {};
    QVector3D get_diffuse() const;
    QVector3D get_reflective() const;
    QVector3D get_ambient() const;
    double get_polish() const;
    //QVector3D get_color() const;
    Ray get_reflect_ray(const Ray& r, const HitInfo& hitdata, QVector3D& refl_coef, double& shine_coef) const;

private:
    QVector3D _diffuse;
    QVector3D _ambient;
    QVector3D _reflective;
    double _polish;
    //QVector3D _color;
};

#endif // MATERIAL_H
