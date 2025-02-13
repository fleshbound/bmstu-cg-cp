#include "builder/basebuilder.h"

void BaseBuilder::build()
{
    _model = std::make_shared<Model>();
    _model->_material = _material;
    _model->_is_mirror = _is_mirror;
    stl_reader::StlMesh <float, unsigned int> mesh (MODELS_FILE + _name + MODELS_TYPE);

    for(size_t itri = 0; itri < mesh.num_tris(); ++itri)
    {
        QVector3D p[3];

        for (size_t icorner = 0; icorner < 3; icorner++)
        {
            const float *c = mesh.tri_corner_coords(itri, icorner);
            p[icorner] = QVector3D(c[0], c[1], c[2]);
        }

        const float *n = mesh.tri_normal(itri);
        QVector3D normal(n[0], n[1], n[2]);
        _model->add(std::make_shared<Triangle>(p[0], p[1], p[2], normal, _material, _is_mirror));
    }

    _model->generate_kd_tree();
}

std::shared_ptr<Model> BaseBuilder::get_model()
{
    return this->_model;
}

std::string BaseBuilder::get_name()
{
    return _name;
}
