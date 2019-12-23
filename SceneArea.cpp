#include "SceneArea.hpp"

namespace rogii
{

namespace qt_quick
{

SceneArea::SceneArea(const QPointF & center, const QSizeF & size)
    : mCenter(center)
    , mSize(size)
{
}

SceneArea::SceneArea(const QRectF & rect)
    : mCenter(rect.center())
    , mSize(rect.size())
{
}

QPointF SceneArea::getCenter() const
{
    return mCenter;
}

QSizeF SceneArea::getSize() const
{
    return mSize;
}

double SceneArea::getCenterX() const
{
    return mCenter.x();
}

double SceneArea::getCenterY() const
{
    return mCenter.y();
}

double SceneArea::getWidth() const
{
    return mSize.width();
}

double SceneArea::getHeight() const
{
    return mSize.height();
}

void SceneArea::translate(double dx, double dy)
{
    mCenter.rx() += dx;
    mCenter.ry() += dy;
}

void SceneArea::translate(const QPointF & delta)
{
    mCenter += delta;
}

void SceneArea::setCenter(double x, double y)
{
    mCenter.setX(x);
    mCenter.setY(y);
}

void SceneArea::setCenter(const QPointF & point)
{
    mCenter = point;
}

void SceneArea::setSize(double width, double height)
{
    mSize.setWidth(width);
    mSize.setHeight(height);
}

void SceneArea::setSize(const QSizeF & size)
{
    mSize = size;
}

void SceneArea::setWidth(double width)
{
    mSize.setWidth(width);
}

void SceneArea::setHeight(double height)
{
    mSize.setHeight(height);
}

QRectF SceneArea::toRectF() const
{
    QRectF rect(QPointF(0.0, 0.0), mSize);
    rect.moveCenter(mCenter);
    return rect;
}

} //~namespace qt_quick

} //~namespace rogii
