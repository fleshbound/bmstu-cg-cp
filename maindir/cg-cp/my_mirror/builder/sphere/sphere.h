#ifndef SPHERE_H
#define SPHERE_H

#include "builder/basebuilder.h"

class SphereBuilder: public BaseBuilder
{
public:
    SphereBuilder(std::shared_ptr<Material> material = nullptr):
        BaseBuilder("sphere", false, material) {};
    void build() override;
};

#endif
