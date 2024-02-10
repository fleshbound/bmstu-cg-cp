#ifndef BASEDRAWER_H
#define BASEDRAWER_H

#include <QVector3D>

class BaseDrawer
{
public:
    virtual void draw_pixel(const int i, const int j, const QVector3D& ints) = 0;
};

#endif // BASEDRAWER_H
