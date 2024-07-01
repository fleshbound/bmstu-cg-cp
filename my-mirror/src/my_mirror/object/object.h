#ifndef OBJECT_H
#define OBJECT_H

#include "utility/bbox/bbox.h"
#include "utility/material/material.h"
#include "utility/ray/ray.h"

class Object: public std::enable_shared_from_this<Object>
{
public:
    virtual void move(const QVector3D &) = 0;
    virtual void scale(const bool scale_mirror, const QVector3D &, const QVector3D& a = QVector3D(0, 0, 0)) = 0;
    virtual bool is_visible() = 0;
    virtual void update() = 0;
    virtual void set_material(const QVector3D& reflective, const double& polish, const QVector3D& diffuse) {};
    virtual bool hit(const Ray& r, const double t_min, const double t_max, HitInfo& hitdata) const = 0;

    QVector3D get_center() const
    {
        return _center;
    }

    BBox bbox() const
    {
        return _bbox;
    }

    virtual bool is_mirror()
    {
        return _is_mirror;
    }
protected:
    std::shared_ptr<Material> _material;
    BBox _bbox;
    QVector3D _center;
    bool _is_mirror = false;
};

#endif // OBJECT_H
