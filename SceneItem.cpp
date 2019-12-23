#include "SceneItem.hpp"

#include "Scene.hpp"

namespace rogii
{
namespace qt_quick
{

SceneItem::SceneItem(QQuickItem * scene)
    : QQuickItem(scene)
    , mModelMatrix()
{
    setFlag(QQuickItem::ItemHasContents);

    if (getScene() != nullptr)
    {
        mSceneCombinedMatrixChangedConnection = connect(getScene(), &Scene::combinedMatrixChanged,
                                                        this, &SceneItem::onSceneCombinedMatrixChanged);
    }
}

const QTransform & SceneItem::getModelMatrix() const
{
    return mModelMatrix;
}

void SceneItem::setModelMatrix(const QTransform & matrix)
{
    mModelMatrix = matrix;

    update();
}

const Scene * SceneItem::getScene() const
{
    return qobject_cast<Scene *>(parentItem());
}

Scene *SceneItem::getScene()
{
    return qobject_cast<Scene *>(parentItem());
}

void SceneItem::setScene(Scene *scene)
{
    setParentItem(scene);

    disconnect(mSceneCombinedMatrixChangedConnection);

    if (getScene() != nullptr)
    {
        mSceneCombinedMatrixChangedConnection = connect(getScene(), &Scene::combinedMatrixChanged,
                                                        this, &SceneItem::onSceneCombinedMatrixChanged);
    }
}

void SceneItem::onSceneCombinedMatrixChanged()
{
    update();
}

} //~namespace qt_quick
} //~namespace rogii

