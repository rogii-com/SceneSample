#pragma once

#include <QTransform>

namespace rogii
{

namespace qt_quick
{

class Scene;

class SceneCamera final : public QObject
{
    Q_OBJECT

public:
    SceneCamera(const Scene & sceneItem);

    QTransform getViewMatrix() const;
    QTransform getProjectionMatrix() const;
    QTransform getViewProjectionMatrix() const;
    QTransform getInvertedViewProjectionMatrix() const;

    QSize getViewportSize() const;

    void setViewMatrix(const QTransform & matrix);
    void setProjectionMatrix(const QTransform & matrix);

    void setMatrixes(const QTransform & viewMatrix, const QTransform & projectionMatrix);

public:
    SceneCamera(const SceneCamera &) = delete;
    SceneCamera(SceneCamera &&) = delete;

    SceneCamera & operator=(const SceneCamera &) = delete;
    SceneCamera & operator=(SceneCamera &&) = delete;

Q_SIGNALS:
    void cameraChanged();

private:
    void updateDerivativeMatrixes();

private:
    const Scene & mScene;

    QTransform mViewMatrix;
    QTransform mProjectionMatrix;
    QTransform mViewProjectionMatrix;
    QTransform mInvertedViewProjectionMatrix;
};

} //~namespace qt_quick

} //~namespace rogii
