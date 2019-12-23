#include "SceneCamera.hpp"

#include "Scene.hpp"

#include <QQuickWindow>

namespace rogii
{

namespace qt_quick
{

SceneCamera::SceneCamera(const Scene & scene)
    : mScene(scene)
{
}

QTransform SceneCamera::getViewMatrix() const
{
    return mViewMatrix;
}

QTransform SceneCamera::getProjectionMatrix() const
{
    return mProjectionMatrix;
}

QTransform SceneCamera::getViewProjectionMatrix() const
{
    return mViewProjectionMatrix;
}

QTransform SceneCamera::getInvertedViewProjectionMatrix() const
{
    return mInvertedViewProjectionMatrix;
}

QSize SceneCamera::getViewportSize() const
{
    return QSize(mScene.width(), mScene.height());
}

void SceneCamera::setViewMatrix(const QTransform &matrix)
{
    if (mViewMatrix == matrix)
        return;

    mViewMatrix = matrix;
    updateDerivativeMatrixes();

    Q_EMIT(cameraChanged());
}

void SceneCamera::setProjectionMatrix(const QTransform &matrix)
{
    if (mProjectionMatrix == matrix)
        return;

    mProjectionMatrix = matrix;
    updateDerivativeMatrixes();

    Q_EMIT(cameraChanged());
}

void SceneCamera::setMatrixes(const QTransform &viewMatrix, const QTransform &projectionMatrix)
{
    if (mViewMatrix == viewMatrix && mProjectionMatrix == projectionMatrix)
        return;

    mViewMatrix = viewMatrix;
    mProjectionMatrix = projectionMatrix;

    updateDerivativeMatrixes();

    Q_EMIT(cameraChanged());
}

void SceneCamera::updateDerivativeMatrixes()
{
//    mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
    mViewProjectionMatrix = mViewMatrix * mProjectionMatrix;

    bool invertible(false);
    mInvertedViewProjectionMatrix = mViewProjectionMatrix.inverted(&invertible);

    Q_ASSERT(invertible);
}

} //~namespace qt_quick

} //~namespace rogii
