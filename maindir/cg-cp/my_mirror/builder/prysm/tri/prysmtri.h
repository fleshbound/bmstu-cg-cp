#ifndef PRYSMTRI_H
#define PRYSMTRI_H

#include "builder/basebuilder.h"

class PrysmTriBuilder: public BaseBuilder
{
public:
    PrysmTriBuilder(std::shared_ptr<Material> material = nullptr): BaseBuilder("prysmtri", false, material) {};
    void build() override;
};

#endif
