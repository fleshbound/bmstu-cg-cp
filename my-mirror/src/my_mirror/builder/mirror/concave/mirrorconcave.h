#ifndef MIRRORCONCAVE_H
#define MIRRORCONCAVE_H

#include "builder/mirror/mirror.h"

class MirrorConcaveBuilder: public MirrorBuilder
{
public:
    MirrorConcaveBuilder(std::shared_ptr<Material> material = nullptr): MirrorBuilder("mirrorconcave", material) {};
    void build() override;
};

#endif
