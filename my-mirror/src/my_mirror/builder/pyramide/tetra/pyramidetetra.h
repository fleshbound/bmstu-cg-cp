#ifndef PyramideTetra_H
#define PyramideTetra_H

#include "builder/basebuilder.h"

class PyramideTetraBuilder: public BaseBuilder
{
public:
    PyramideTetraBuilder(std::shared_ptr<Material> material = nullptr): BaseBuilder("pyramidetetra", false, material) {};
    void build() override;
};

#endif
