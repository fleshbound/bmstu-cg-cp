#ifndef BASEBUILDER_H
#define BASEBUILDER_H

#include <QDebug>
#include "object/visibleobject/model/model.h"
#include "object/visibleobject/triangle/triangle.h"
#include "stl_reader/stl_reader.h"

#ifndef MODELS_FILE
#define MODELS_FILE "./data/stl/"
#endif

#ifndef MODELS_TYPE
#define MODELS_TYPE ".stl"
#endif

class BaseBuilder
{
public:
    BaseBuilder(std::string name, bool is_mirror = false, std::shared_ptr<Material> material = nullptr):
        _name(name),
        _is_mirror(is_mirror)
    {
        if (material)
            _material = material;
        else if (is_mirror)
            _material = std_mirror_material;
        else
            _material = std_object_material;
    }
    virtual void build();
    std::shared_ptr<Model> get_model();
    std::string get_name();

protected:
    std::shared_ptr<Model> _model;
    std::string _name = "";
    std::shared_ptr<Material> _material;
    bool _is_mirror;

    std::shared_ptr<Material> std_mirror_material =
            std::make_shared<Material>(
                QVector3D(0.3, 0.3, 0.3),
                QVector3D(0.8, 0.6, 0.48),
                QVector3D(0.9, 0.9, 0.9),
                100
            );

    std::shared_ptr<Material> std_object_material =
            std::make_shared<Material>(
                QVector3D(0.3, 0.3, 0.3),
                QVector3D(0.5, 0.6, 0.48),
                QVector3D(0.2, 0.2, 0.2),
                60
            );
};

#endif // BASEBUILDER_H
