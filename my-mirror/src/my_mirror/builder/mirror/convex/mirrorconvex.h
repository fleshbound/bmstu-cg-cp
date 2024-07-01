#ifndef MIRRORCONVEX_H
#define MIRRORCONVEX_H

#include "builder/mirror/mirror.h"

class MirrorConvexBuilder: public MirrorBuilder
{
public:
    MirrorConvexBuilder(std::shared_ptr<Material> material = nullptr): MirrorBuilder("mirrorconvex", material) {};
    void build() override;
};

#endif
