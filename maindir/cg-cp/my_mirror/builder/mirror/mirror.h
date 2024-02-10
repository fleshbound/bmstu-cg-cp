#ifndef MIRROR_H
#define MIRROR_H

#include "builder/basebuilder.h"

class MirrorBuilder: public BaseBuilder
{
public:
    MirrorBuilder(std::string name, std::shared_ptr<Material> material = nullptr):
        BaseBuilder(name, true, material) {}
    void build() override;
};

#endif // MIRROR_H
