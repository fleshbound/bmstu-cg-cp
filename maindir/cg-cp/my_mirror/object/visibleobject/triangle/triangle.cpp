#include "object/visibleobject/triangle/triangle.h"

Triangle::Triangle(QVector3D a, QVector3D b, QVector3D c, QVector3D normal, std::shared_ptr<Material> material)
{
    _points[0] = a;
    _points[0] = b;
    _points[0] = c;
    _material = material;
    _normal = normal;
    _normal.normalize();

    Triangle::update();
}

void Triangle::move(const QVector3D& d)
{
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            _points[i][j] = d[j];

    for (size_t i = 0; i < 3; i++)
        _center[i] = d[i];

    Triangle::update();
}

void Triangle::scale(const bool scale_mirror, const QVector3D& k)
{
    if ((!this->is_mirror() && scale_mirror) || (this->is_mirror() && !scale_mirror))
        return;

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            _points[i][j] *= k[j];

    for (size_t i = 0; i < 3; i++)
        _center[i] *= k[i];

    Triangle::update();
}

void Triangle::update()
{
    float min_x = std::min(std::min(_points[0].x(), _points[1].x()), _points[2].x());
    float min_y = std::min(std::min(_points[0].x(), _points[1].x()), _points[2].x());
    float min_z = std::min(std::min(_points[0].x(), _points[1].x()), _points[2].x());
    float max_x = std::max(std::max(_points[0].x(), _points[1].x()), _points[2].x());
    float max_y = std::max(std::max(_points[0].x(), _points[1].x()), _points[2].x());
    float max_z = std::max(std::max(_points[0].x(), _points[1].x()), _points[2].x());
    QVector3D min_coords = {min_x, min_y, min_z};
    QVector3D max_coords = {max_x, max_y, max_z};
    _bbox = BBox(min_coords, max_coords);

    _center = {(_points[0].x() + _points[1].x() + _points[2].x()) / 3,
               (_points[0].y() + _points[1].y() + _points[2].y()) / 3,
               (_points[0].z() + _points[1].z() + _points[2].z()) / 3};
}

bool Triangle::hit(const Ray& r, const double t_min, const double t_max, HitInfo& hitdata) const
{
    QVector3D d = r.get_direction();
    QVector3D e1 = _points[1] - _points[0];
    QVector3D e2 = _points[2] - _points[0];
    QVector3D p = QVector3D::crossProduct(d, e2);
    double det = QVector3D::dotProduct(p, e2);

    if (std::abs(det) < 1e-8f)
        return false;

    QVector3D o = r.get_origin();
    QVector3D tvec = o - _points[0];
    QVector3D q = QVector3D::crossProduct(tvec, e1);
    double inv_det = 1 / det;
    double u = QVector3D::dotProduct(p, tvec) * inv_det;
    double v = QVector3D::dotProduct(q, d) * inv_det;

    if ((u < 0) || (v < 0) || (u + v >= 1))
        return false;

    double t = QVector3D::dotProduct(q, e2) * inv_det;

    if ((t > t_max) || (t < t_min))
        return false;

    hitdata.t = t;
    hitdata.point = r.get_point_by_t(t);
    QVector3D normal = QVector3D::crossProduct(e1, e2).normalized();

    if (QVector3D::dotProduct(normal, d) < 1e-8f)
        normal = -normal;

    hitdata.normal = normal;
    hitdata.material = _material;
    hitdata.object = shared_from_this();
    printf("hit triangle\n");

    return true;
}
