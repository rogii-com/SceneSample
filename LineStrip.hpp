#ifndef LINESTRIP_HPP
#define LINESTRIP_HPP

#include <QVector>

#include "SceneItem.hpp"

class LineStrip : public rogii::qt_quick::SceneItem
{
    Q_OBJECT

public:
    LineStrip(QQuickItem * scene = nullptr);

public Q_SLOTS:
    void reserve(int count);
    void appendPoint(const QPointF & p);
    void setColor(QColor color);

protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

private:
    QVector<QPointF> mPoints;
    bool mChanged = false;
    QColor mColor = Qt::black;
};

#endif // LINESTRIP_HPP
