#ifndef QTDRAWER_H
#define QTDRAWER_H

#include <QPainter>
#include <QPen>
#include "drawer/basedrawer.h"

class QtDrawer: public BaseDrawer
{
public:
    QtDrawer() = default;
    ~QtDrawer() = default;
    explicit QtDrawer(const QtDrawer &);
    QtDrawer(QtDrawer &&) noexcept;
    explicit QtDrawer(std::shared_ptr<QPainter>);

    void draw_pixel(const int i, const int j, const QVector3D& ints) override;

private:
    std::shared_ptr<QPainter> _painter;
};

#endif // QTDRAWER_H
