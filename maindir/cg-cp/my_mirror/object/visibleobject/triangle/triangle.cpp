#include "object/visibleobject/triangle/triangle.h"

Triangle::Triangle(QVector3D a, QVector3D b, QVector3D c, QVector3D normal, std::shared_ptr<Material> material, const bool& is_mirror)
{
    _points[0] = a;
    _points[1] = b;
    _points[2] = c;
    _material = material;
    _normal = normal;
    _normal.normalize();
    _is_mirror = is_mirror;

    Triangle::update();
}

void Triangle::move(const QVector3D& d)
{
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            _points[i][j] += d[j];

    for (size_t i = 0; i < 3; i++)
        _center[i] += d[i];

    Triangle::update();
}

void Triangle::scale(const bool scale_mirror, const QVector3D& k, const QVector3D& a)
{
    if (((!this->is_mirror()) && scale_mirror) || (this->is_mirror() && (!scale_mirror)))
        return;

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            _points[i][j] = _points[i][j] * k[j] + _points[i][2] * a[i];

    for (size_t i = 0; i < 3; i++)
        _center[i] = _center[i] * k[i] + _center[2] * a[i];

    Triangle::update();
}

void Triangle::update()
{
    float min_x = std::min(std::min(_points[0].x(), _points[1].x()), _points[2].x());
    float min_y = std::min(std::min(_points[0].y(), _points[1].y()), _points[2].y());
    float min_z = std::min(std::min(_points[0].z(), _points[1].z()), _points[2].z());
    float max_x = std::max(std::max(_points[0].x(), _points[1].x()), _points[2].x());
    float max_y = std::max(std::max(_points[0].y(), _points[1].y()), _points[2].y());
    float max_z = std::max(std::max(_points[0].z(), _points[1].z()), _points[2].z());
    QVector3D min_coords = {min_x, min_y, min_z};
    QVector3D max_coords = {max_x, max_y, max_z};
    _bbox = BBox(min_coords, max_coords);

    _center = {(_points[0].x() + _points[1].x() + _points[2].x()) / 3,
               (_points[0].y() + _points[1].y() + _points[2].y()) / 3,
               (_points[0].z() + _points[1].z() + _points[2].z()) / 3};
}

bool Triangle::hit(const Ray& r, const double t_min, const double t_max, HitInfo& hitdata) const
{
    QVector3D edge1 = _points[1] - _points[0];
    QVector3D edge2 = _points[2] - _points[0];
    QVector3D e1e2 =(QVector3D::crossProduct(edge1, edge2)).normalized();

    if (QVector3D::dotProduct(e1e2, r.get_direction()) < 1e-9f)
        e1e2 = -e1e2;

    QVector3D pvec = QVector3D::crossProduct(r.get_direction(), edge2);
    double det = QVector3D::dotProduct(edge1, pvec);

    if (det <= 1e-9f)
        return false;

    float inv_det = 1.0f / det;
    QVector3D tvec = r.get_origin() - _points[0];
    double u = QVector3D::dotProduct(tvec, pvec) * inv_det;
    QVector3D qvec = QVector3D::crossProduct(tvec, edge1);
    double v = QVector3D::dotProduct(r.get_direction(), qvec) * inv_det;

    if (u < 0.0f || v < 0.0f || (u + v) > 1.0f)
        return false;

    double t = QVector3D::dotProduct(edge2, qvec) * inv_det;

    if (t > t_max || t < t_min)
        return false;

    hitdata.t = t;
    hitdata.point = r.get_point_by_t(t);
    hitdata.normal = (QVector3D::crossProduct(edge1, edge2)).normalized();
    hitdata.material = _material;
    hitdata.object = shared_from_this();

    return true;
}
