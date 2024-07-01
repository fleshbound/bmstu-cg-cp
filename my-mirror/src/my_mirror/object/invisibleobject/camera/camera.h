#ifndef CAMERA_H
#define CAMERA_H

#include "object/invisibleobject/invisibleobject.h"

class Camera: public InvisibleObject
{
public:
    Camera(const QVector3D& pos, const QVector3D& view, const double k);

    void move(const QVector3D &) override;
    void scale(const bool scale_mirror, const QVector3D &, const QVector3D& a = QVector3D(0, 0, 0)) override { throw "can't scale camera"; }
    void update() override;
    bool hit(const Ray& r, const double t_min, const double t_max, HitInfo& hitdata) const override;

    QVector3D get_pos() const;
    QVector3D get_view() const;
    void rotate(const QVector3D& angle);
    Ray get_ray(const double i, const double j) const;

private:
    QVector3D _view;
    double _k;
    QVector3D _horizontal;
    QVector3D _vertical;
    QVector3D _lower_left;
    QVector3D _update_view;
    QVector3D _up = {0, 0, 1};
};

#endif // CAMERA_H
