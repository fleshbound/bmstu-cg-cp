#ifndef QTDRAWERFACTORY_H
#define QTDRAWERFACTORY_H

#include <QPainter>
#include "drawer/qtdrawer.h"
#include "factory/abstractfactory.h"

class QtDrawerFactory: public AbstractFactory
{
public:
    std::unique_ptr<BaseDrawer> create_drawer(std::shared_ptr<QPainter>) override;
};

#endif // QTDRAWERFACTORY_H
