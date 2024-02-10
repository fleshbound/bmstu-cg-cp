#ifndef VISIBLEOBJECT_H
#define VISIBLEOBJECT_H

#include "object/object.h"

class VisibleObject: public Object
{
public:
    virtual void set_material(const QVector3D& reflective, const double& polish, const QVector3D& diffuse) override
    {
        _material->_reflective = reflective;
        _material->_polish = polish;
        _material->_diffuse = diffuse;
        _material->_ambient = _material->_ambient * diffuse;
    }

    bool is_visible() override
    {
        return true;
    }
};

#endif // VISIBLEOBJECT_H
