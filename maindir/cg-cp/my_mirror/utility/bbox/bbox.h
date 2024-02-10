#ifndef BBOX_H
#define BBOX_H

#include "utility/ray/ray.h"

class BBox
{
public:
    BBox() = default;
    BBox(const QVector3D min_coords, const QVector3D max_coords): _min_coords(min_coords), _max_coords(max_coords) {};
    QVector3D get_min() const;
    QVector3D get_max() const;
    bool hit(const Ray& r) const;
    void expand(const BBox& box);
private:
    QVector3D _min_coords;
    QVector3D _max_coords;
};

#endif // BBOX_H
