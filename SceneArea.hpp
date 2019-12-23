#pragma once

#include <QPointF>
#include <QSizeF>
#include <QRectF>

namespace rogii
{

namespace qt_quick
{

class SceneArea final
{
public:
    SceneArea(const QPointF & center, const QSizeF & size);
    SceneArea(const QRectF & rect);

    QPointF getCenter() const;

    QSizeF getSize() const;

    double getCenterX() const;
    double getCenterY() const;

    double getWidth() const;
    double getHeight() const;

    void translate(double dx, double dy);
    void translate(const QPointF & delta);

    void setCenter(double x, double y);
    void setCenter(const QPointF & point);

    void setSize(double width, double height);
    void setSize(const QSizeF & size);

    void setWidth(double width);
    void setHeight(double height);

    QRectF toRectF() const;

private:
    QPointF mCenter;
    QSizeF mSize;
};

} //~namespace qt_quick

} //~namespace rogii
