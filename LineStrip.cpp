#include "LineStrip.hpp"

#include <QSGGeometryNode>

#include "FlatColorSceneMaterial.hpp"

LineStrip::LineStrip(QQuickItem *scene)
    : rogii::qt_quick::SceneItem(scene)
{

}

void LineStrip::reserve(int count)
{
    mPoints.reserve(count);
}

void LineStrip::appendPoint(const QPointF &p)
{
    mPoints.append(p);
    mChanged = true;
    update();
}

void LineStrip::setColor(QColor color)
{
    mColor = color;
    mChanged = true;
    update();
}

QSGNode *LineStrip::updatePaintNode(QSGNode * oldNode, QQuickItem::UpdatePaintNodeData *)
{
    if (getScene() == nullptr)
        return nullptr;

    QSGGeometryNode * node(static_cast<QSGGeometryNode*>(oldNode));

    if (node == nullptr)
    {
        node = new QSGGeometryNode;

        QSGGeometry * g = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 0);
        g->setDrawingMode(QSGGeometry::DrawLineStrip);

        node->setGeometry(g);
        node->setFlag(QSGNode::OwnsGeometry);

        node->setMaterial(new rogii::qt_quick::FlatColorSceneMaterial(*getScene()));
        node->setFlag(QSGNode::OwnsMaterial);
    }

    if (mChanged)
    {
        mChanged = false;

        QSGGeometry * geometry(node->geometry());
        auto * material(static_cast<rogii::qt_quick::FlatColorSceneMaterial *>(node->material()));

        material->setModelMatrix(getModelMatrix());
        material->setColor(mColor);

        auto points = mPoints;
        geometry->allocate(points.size());

        QSGGeometry::Point2D * vertex = geometry->vertexDataAsPoint2D();
        for (int i(0), count(geometry->vertexCount()); i < count; ++i)
        {
            const auto & v(points[i]);
            vertex[i].set(v.x(), v.y());
        }

        node->markDirty(QSGNode::DirtyMaterial);
        node->markDirty(QSGNode::DirtyGeometry);
    }

    return node;
}
