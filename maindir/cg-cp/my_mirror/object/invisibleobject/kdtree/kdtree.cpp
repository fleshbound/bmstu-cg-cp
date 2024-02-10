#include "object/invisibleobject/kdtree/kdtree.h"

// kdtree

KDtree::KDtree(std::vector<std::shared_ptr<Object>> objects)
{
    _root = _create_tree(objects, 0);
    _bbox = _root->bbox;
}

void KDtree::update()
{
    _root->update();
    _bbox = _root->bbox;
}

void KDtree::set_material(const QVector3D& reflective, const double& polish, const QVector3D& diffuse)
{
    _root->set_material(reflective, polish, diffuse);
}

bool KDtree::hit(const Ray& r, const double t_min, const double t_max, HitInfo& hitdata) const
{
    hitdata.t = t_max;

    if (_root)
        return _root->hit(r, t_min, t_max, hitdata);

    throw "hit: no KDtree";
}

std::shared_ptr<KDtree::KDnode> KDtree::_create_tree(std::vector<std::shared_ptr<Object>> objects, const int depth)
{
    auto node = std::make_shared<KDnode>();
    node->left = 0;
    node->right = 0;
    node->axis = 0;

    if (objects.size() == 0)
        return node;

    node->bbox = objects[0]->bbox();

    QVector3D average_position(0.0f, 0.0f, 0.0f);

    for (auto& object : objects)
    {
        average_position += object->get_center();
        node->bbox.expand(object->bbox());
    }

    average_position /= objects.size();

    if (objects.size() <= 4 || depth > 8)
    {
        for (auto &object : objects)
            node->objects.emplace_back(object);

        return node;
    }

    const QVector3D boundingBoxSize = node->bbox.get_max() - node->bbox.get_min();
    size_t buffer_axis;

    if (boundingBoxSize[0] >= boundingBoxSize[1] && boundingBoxSize[0] >= boundingBoxSize[2])
        buffer_axis = 0;
    else if (boundingBoxSize[1] >= boundingBoxSize[2])
        buffer_axis = boundingBoxSize[1] >= boundingBoxSize[2];
    else
        buffer_axis = 2;

    node->axis = buffer_axis;

    std::vector<std::shared_ptr<Object>> left_objects;
    std::vector<std::shared_ptr<Object>> right_objects;

    for (auto& object : objects)
        if (object->get_center()[buffer_axis] < average_position[buffer_axis])
            left_objects.emplace_back(object);
        else
            right_objects.emplace_back(object);

    if (left_objects.size() > 0)
    {
        node->left = _create_tree(left_objects, depth + 1);
        node->bbox.expand(node->left->bbox);
    }

    if (right_objects.size() > 0)
    {
        node->right = _create_tree(right_objects, depth + 1);
        node->bbox.expand(node->right->bbox);
    }

    return node;
}


// kdnode

void KDtree::KDnode::update()
{
    //qInfo( "update kdnode" );

    if (left)
    {
        left->update();
        bbox = left->bbox;
    }

    if (!left && right)
    {
        right->update();
        bbox = right->bbox;
    }
    else if (left && right)
    {
        right->update();
        bbox.expand(right->bbox);
    }

    if (objects.size())
    {
        bbox = objects[0]->bbox();

        for (auto& object : objects)
            bbox.expand(object->bbox());

        return;
    }
}

void KDtree::KDnode::set_material(const QVector3D& reflective, const double& polish, const QVector3D& diffuse)
{
    if (left)
        left->set_material(reflective, polish, diffuse);

    if (right)
        right->set_material(reflective, polish, diffuse);

    if (objects.size())
        for (auto& object : objects)
            if (object->is_mirror())
                object->set_material(reflective, polish, diffuse);
}

bool KDtree::KDnode::hit(const Ray& r, const double t_min, const double t_max, HitInfo& hitdata) const
{
    if (!bbox.hit(r))
        return false;

    std::shared_ptr<KDnode> le = left;
    std::shared_ptr<KDnode> ri = right;

    if (r.get_direction()[axis] <= 0)
    {
        le = right;
        ri = left;
    }

    bool hit_le = false, hit_ri = false;
    double tmp_t_max = t_max;

    if (le)
    {
        hit_le = le->hit(r, t_min, tmp_t_max, hitdata);

        if (hit_le)
            tmp_t_max = hitdata.t;
    }

    if (ri)
    {
        hit_ri = ri->hit(r, t_min, tmp_t_max, hitdata);

        if (hit_ri)
            tmp_t_max = hitdata.t;
    }

    if (hit_ri || hit_le)
    {
        printf("hit kdnode\n");
        return true;
    }

    double closest_t = tmp_t_max;
    HitInfo bufferdata;

    for (const auto object : objects)
        if (object->hit(r, t_min, closest_t, bufferdata))
            closest_t = hitdata.t;

    return closest_t < t_max;
}
