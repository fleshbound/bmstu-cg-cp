#include "utility/bbox/bbox.h"

QVector3D BBox::get_min() const
{
    return _min_coords;
}

QVector3D BBox::get_max() const
{
    return _max_coords;
}

bool BBox::hit(const Ray& r) const
{
    QVector3D d = r.get_direction();
    QVector3D o = r.get_origin();

    if (std::abs(d.length()) < 1e-8 || ((std::abs(d.x()) < 1e-8) || (std::abs(d.y()) < 1e-8) || (std::abs(d.z()) < 1e-8)))
        return false;

    QVector3D inv_d = QVector3D(1, 1, 1) / d;
    int buffer_sign[3];
    QVector3D buffer_bounds[2] = { _min_coords, _max_coords };

    for (size_t  i = 0; i < 3; i++)
        buffer_sign[i] = inv_d[i] < 0 ? 1 : 0;

    bool init = false;
    double lo, hi;

    for (size_t i = 0; i < 3; i++)
    {
        double t_min = inv_d[i] * (buffer_bounds[buffer_sign[i]][i] - o[i]);
        double t_max = inv_d[i] * (buffer_bounds[1 - buffer_sign[i]][i] - o[i]);

        if (!init)
        {
            init = true;
            lo = t_min;
            hi = t_max;
        }
        else
        {
            if ((lo > t_max) || (hi < t_min))
                return false;

            if (t_min > lo)
                lo = t_min;

            if (t_max < hi)
                hi = t_max;
        }
    }

    double t = lo;

    if (t < 0)
    {
        t = hi;

        if (t < 0)
            return false;
    }

    return true;
}

void BBox::expand(const BBox& box)
{
    for (size_t i = 0; i < 3; i++)
    {
        _min_coords[i] = std::min(_min_coords[i], box._min_coords[i]);
        _max_coords[i] = std::max(_max_coords[i], box._max_coords[i]);
    }
}
