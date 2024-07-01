#ifndef PRYSMPENTA_H
#define PRYSMPENTA_H

#include "builder/basebuilder.h"

class PrysmPentaBuilder: public BaseBuilder
{
public:
    PrysmPentaBuilder(std::shared_ptr<Material> material = nullptr): BaseBuilder("prysmpenta", false, material) {};
    void build() override;
};

#endif
