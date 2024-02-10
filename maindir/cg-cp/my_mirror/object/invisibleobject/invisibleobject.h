#ifndef INVISIVLEOBJECT_H
#define INVISIVLEOBJECT_H

#include "object/object.h"

class InvisibleObject: public Object
{
public:
    bool is_visible() override
    {
        return false;
    }
};

#endif // INVISIVLEOBJECT_H
