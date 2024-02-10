#include "builder/mirror/mirror.h"

void MirrorBuilder::build()
{
    BaseBuilder::build();
    BaseBuilder::set_mirror_flag();
}
