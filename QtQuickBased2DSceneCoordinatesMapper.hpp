#pragma once

#include "SceneCamera.hpp"

#include "Base2DSceneCoordinatedMapper.hpp"

namespace rogii
{

namespace qt_quick
{

class QtQuickBased2DSceneCoordinatesMapper : public Base2DSceneCoordinatedMapper
{
public:
    explicit QtQuickBased2DSceneCoordinatesMapper(const SceneCamera & camera);

    // Base2DSceneCoordinatesMapper override
    //@{
    using Base2DSceneCoordinatedMapper::mapToScene;
    using Base2DSceneCoordinatedMapper::mapFromScene;

    QPointF mapToScene(const QPoint & windowPosition) const override;
    QPoint mapFromScene(const QPointF & scenePosition) const override;
    //@}

public:
    QtQuickBased2DSceneCoordinatesMapper(const QtQuickBased2DSceneCoordinatesMapper &) = delete;
    QtQuickBased2DSceneCoordinatesMapper(QtQuickBased2DSceneCoordinatesMapper &&) = delete;

    QtQuickBased2DSceneCoordinatesMapper & operator=(const QtQuickBased2DSceneCoordinatesMapper &) = delete;
    QtQuickBased2DSceneCoordinatesMapper & operator=(QtQuickBased2DSceneCoordinatesMapper &&) = delete;

private:
    const SceneCamera & mCamera;
};

} //~namespace qt_quick

} //~namespace rogii
