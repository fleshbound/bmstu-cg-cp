#ifndef KDTREE_H
#define KDTREE_H

#include "object/invisibleobject/invisibleobject.h"

class KDtree: public InvisibleObject
{
public:
    KDtree(std::vector<std::shared_ptr<Object>> objects);
    void move(const QVector3D &) override { throw "can't move KDtree"; }
    void update() override;
    void set_material(const QVector3D& reflective, const double& polish, const QVector3D& diffuse) override;
    bool hit(const Ray& r, const double t_min, const double t_max, HitInfo& hitdata) const override;
    void scale(const bool scale_mirror, const QVector3D &) override { throw "can't scale kdtree"; }

private:
    struct KDnode: public std::enable_shared_from_this<KDnode>
    {
        void update();
        void set_material(const QVector3D& reflective, const double& polish, const QVector3D& diffuse);
        bool hit(const Ray& r, const double t_min, const double t_max, HitInfo& hitdata) const;

        BBox bbox;
        size_t axis;
        size_t depth;
        std::vector<std::shared_ptr<Object>> objects;
        std::shared_ptr<KDnode> left;
        std::shared_ptr<KDnode> right;
    };

    std::shared_ptr<KDnode> _create_tree(std::vector<std::shared_ptr<Object>> objects, const int depth);
    std::shared_ptr<KDnode> _root;
};

#endif // KDTREE_H
