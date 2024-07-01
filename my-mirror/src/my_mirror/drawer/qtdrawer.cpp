#include "drawer/qtdrawer.h"

QtDrawer::QtDrawer(std::shared_ptr<QPainter> painter)
{
    _painter = painter;
}

QtDrawer::QtDrawer(const QtDrawer& drawer)
{
    _painter = drawer._painter;
}

QtDrawer::QtDrawer(QtDrawer&& drawer) noexcept
{
    _painter = drawer._painter;
}

void QtDrawer::draw_pixel(const int i, const int j, const QVector3D& ints)
{
    int r = 255 * ints[0];
    int g = 255 * ints[1];
    int b = 255 * ints[2];

    _painter->setPen(QColor((r > 255 ? 255 : r),
                            (g > 255 ? 255 : g),
                            (b > 255 ? 255 : b)));
    _painter->drawPoint(i, j);
}
