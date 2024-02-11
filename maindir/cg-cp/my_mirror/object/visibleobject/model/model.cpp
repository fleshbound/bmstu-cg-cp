#include "object/visibleobject/model/model.h"

void Model::move(const QVector3D& d)
{
    for (size_t i = 0; i < 3; i++)
        _center[i] += d[i];

    for (auto& object : _objects)
        object->move(d);

    Model::update();
}

void Model::scale(const bool scale_mirror, const QVector3D& k, const QVector3D& a)
{
    if (((!this->is_mirror()) && scale_mirror) || (this->is_mirror() && (!scale_mirror)))
        return;

    QVector3D tmp_center = _center;

    this->move(-tmp_center);

    for (auto& object : _objects)
        object->scale(scale_mirror, k, a);

    this->move(tmp_center);

    Model::update();
}

void Model::update()
{
    _kdtree->update();
    _bbox = _kdtree->bbox();
}

bool Model::hit(const Ray& r, const double t_min, const double t_max, HitInfo& hitdata) const
{
    if (_bbox.hit(r))
        return _kdtree->hit(r, t_min, t_max, hitdata);

    return false;
}

void Model::generate_kd_tree()
{
    _kdtree = std::make_shared<KDtree>(_objects);
    _bbox.expand(_kdtree->bbox());
    _has_kdtree = true;
}

void Model::add(std::shared_ptr<Object> object)
{
    _objects.emplace_back(object);
}
