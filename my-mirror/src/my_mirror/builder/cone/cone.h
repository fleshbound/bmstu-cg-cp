#ifndef CONE_H
#define CONE_H

#include "builder/basebuilder.h"

class ConeBuilder: public BaseBuilder
{
public:
    ConeBuilder(std::shared_ptr<Material> material = nullptr): BaseBuilder("cone", false, material) {};
    void build() override;
};

#endif
