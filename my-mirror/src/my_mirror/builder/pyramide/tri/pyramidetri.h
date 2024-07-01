#ifndef PyramideTri_H
#define PyramideTri_H

#include "builder/basebuilder.h"

class PyramideTriBuilder: public BaseBuilder
{
public:
    PyramideTriBuilder(std::shared_ptr<Material> material = nullptr): BaseBuilder("pyramidetri", false, material) {};
    void build() override;
};

#endif
