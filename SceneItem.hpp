#pragma once

#include <QQuickItem>
#include <QTransform>

namespace rogii
{
namespace qt_quick
{

class Scene;

class SceneItem : public QQuickItem
{
    Q_OBJECT

public:
    explicit SceneItem(QQuickItem * scene = nullptr);

    const QTransform & getModelMatrix() const;
    void setModelMatrix(const QTransform & matrix);

public:
    SceneItem(const SceneItem &) = delete;
    SceneItem(SceneItem &&) = delete;

    SceneItem & operator=(const SceneItem &) = delete;
    SceneItem & operator=(SceneItem &&) = delete;

protected:
    const Scene * getScene() const;
    Scene * getScene();

private:
    friend class Scene;

private:
    void setScene(Scene * scene);

private Q_SLOTS:
    void onSceneCombinedMatrixChanged();

private:
    QTransform mModelMatrix;

    QMetaObject::Connection mSceneCombinedMatrixChangedConnection;
};

} //~namespace qt_quick
} //~namespace rogii
