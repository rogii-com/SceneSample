#include "QtQuickBased2DSceneCoordinatesMapper.hpp"

#include "utils.hpp"

namespace rogii
{

namespace qt_quick
{

QtQuickBased2DSceneCoordinatesMapper::QtQuickBased2DSceneCoordinatesMapper(const SceneCamera & camera)
    : mCamera(camera)
{
}

QPointF QtQuickBased2DSceneCoordinatesMapper::mapToScene(const QPoint & windowPosition) const
{
    const QPointF result(::rogii::qt_quick::mapToScene(mCamera.getViewportSize(),
                                               mCamera.getInvertedViewProjectionMatrix(),
                                               windowPosition));
    return result;
}

QPoint QtQuickBased2DSceneCoordinatesMapper::mapFromScene(const QPointF & scenePosition) const
{
    return ::rogii::qt_quick::mapFromScene(mCamera.getViewportSize(),
                                   mCamera.getViewProjectionMatrix(),
                                   scenePosition);
}

} //~namespace qt_quick

} //~namespace rogii
