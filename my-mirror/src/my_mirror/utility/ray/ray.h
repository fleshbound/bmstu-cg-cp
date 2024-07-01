#ifndef RAY_H
#define RAY_H

#include <QVector3D>
#include <memory>

class Material;
class Object;

struct HitInfo
{
    QVector3D point;
    double t;
    QVector3D normal;
    std::shared_ptr<const Object> object;
    std::shared_ptr<const Material> material;
};

class Ray
{
public:
    Ray() = default;
    Ray(const QVector3D& origin, const QVector3D& direction);
    QVector3D get_direction() const;
    QVector3D get_origin() const;
    QVector3D get_point_by_t(const double t) const;

private:
    QVector3D _origin;
    QVector3D _direction;
};

#endif // RAY_H
