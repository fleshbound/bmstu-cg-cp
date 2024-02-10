#ifndef PYRAMIDEPENTA_H
#define PYRAMIDEPENTA_H

#include "builder/basebuilder.h"

class PyramidePentaBuilder: public BaseBuilder
{
public:
    PyramidePentaBuilder(std::shared_ptr<Material> material = nullptr): BaseBuilder("pyramidepenta", false, material) {};
    void build() override;
};

#endif
