#ifndef CYLINDER_H
#define CYLINDER_H

#include "builder/basebuilder.h"

class CylinderBuilder: public BaseBuilder
{
public:
    CylinderBuilder(std::shared_ptr<Material> material = nullptr): BaseBuilder("cylinder", false, material) {};
    void build() override;
};

#endif
