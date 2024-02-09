#ifndef OBJECT_H
#define OBJECT_H

#include "utility/bbox/bbox.h"
#include "utility/material/material.h"
#include "utility/ray/ray.h"

class Object: public std::enable_shared_from_this<Object>
{
public:
    virtual void move(QVector3D &) = 0;
    virtual bool is_visible() = 0;
    virtual void update() = 0;
    virtual void set_material(const QVector3D& new_m, const double& polish) {};
    virtual void hit(const Ray& r, const double t_min, const double t_max, HitInfo& hitdata) const = 0;

    QVector3D get_center() const
    {
        return _center;
    }

    BBox get_bbox() const
    {
        return _bbox;
    }
protected:
    std::shared_ptr<Material> _material;
    BBox _bbox;
    QVector3D _center;
};

#endif // OBJECT_H
