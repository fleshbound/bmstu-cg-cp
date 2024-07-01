#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include <memory>
#include <QPainter>
#include "drawer/basedrawer.h"

class AbstractFactory
{
public:
    AbstractFactory() = default;
    virtual std::unique_ptr<BaseDrawer> create_drawer(std::shared_ptr<QPainter>) = 0;
};

#endif // ABSTRACTFACTORY_H
