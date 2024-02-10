#ifndef PRYSMTETRA_H
#define PRYSMTETRA_H

#include "builder/basebuilder.h"

class PrysmTetraBuilder: public BaseBuilder
{
public:
    PrysmTetraBuilder(std::shared_ptr<Material> material = nullptr): BaseBuilder("prysmtetra", false, material) {};
    void build() override;
};

#endif
