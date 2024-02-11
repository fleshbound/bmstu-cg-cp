#ifndef MODEL_H
#define MODEL_H

#include "object/visibleobject/visibleobject.h"
#include "object/invisibleobject/kdtree/kdtree.h"

class Model: public VisibleObject
{
    friend class BaseBuilder;

public:
    Model() = default;
    ~Model() = default;

    void move(const QVector3D &) override;
    void scale(const bool scale_mirror, const QVector3D &, const QVector3D& a = QVector3D(0, 0, 0)) override;
    void update() override;
    bool hit(const Ray& r, const double t_min, const double t_max, HitInfo& hitdata) const override;
    void generate_kd_tree();
    void add(std::shared_ptr<Object> object);

protected:
    std::vector<std::shared_ptr<Object>> _objects;
    std::shared_ptr<KDtree> _kdtree;
    bool _has_kdtree = false;
};

#endif // MODEL_H
