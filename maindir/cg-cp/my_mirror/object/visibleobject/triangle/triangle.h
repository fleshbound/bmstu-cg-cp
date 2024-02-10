#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object/visibleobject/visibleobject.h"

class Triangle: public VisibleObject
{
public:
    Triangle(QVector3D a, QVector3D b, QVector3D c, QVector3D normal, std::shared_ptr<Material> material);
    void move(const QVector3D &) override;
    void scale(const bool scale_mirror, const QVector3D& k) override;
    void update() override;
    bool hit(const Ray& r, const double t_min, const double t_max, HitInfo& hitdata) const override;
private:
    QVector3D _normal;
    QVector3D _points[3];
};

#endif // TRIANGLE_H
