#ifndef MIRRORPLANE_H
#define MIRRORPLANE_H

#include "builder/mirror/mirror.h"

class MirrorPlaneBuilder: public MirrorBuilder
{
public:
    MirrorPlaneBuilder(std::shared_ptr<Material> material = nullptr):
        MirrorBuilder("mirrorplane", material) {};
    void build() override;
};

#endif
