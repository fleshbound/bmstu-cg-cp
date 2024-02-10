#ifndef LIGHT_H
#define LIGHT_H

#include "object/invisibleobject/invisibleobject.h"

class Light: public InvisibleObject
{
public:
    Light(const QVector3D& pos, const QVector3D& ints): _pos(pos), _ints(ints) {}
    void move(const QVector3D &) override;
    void scale(const bool scale_mirror, const QVector3D &) override { throw "can't scale light"; }
    void update() override;
    bool hit(const Ray& r, const double t_min, const double t_max, HitInfo& hitdata) const override;

    QVector3D get_pos() const;
    QVector3D get_ints() const;
    void set_ints(const QVector3D& new_ints);
    Ray get_ray(const QVector3D& hit_p) const;

private:
    QVector3D _pos;
    QVector3D _ints;
};

#endif // LIGHT_H
