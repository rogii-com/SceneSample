#pragma once

#include "SceneCamera.hpp"
#include "SceneArea.hpp"
#include "QtQuickBased2DSceneCoordinatesMapper.hpp"

namespace rogii
{

namespace qt_quick
{

class QtQuickBased2DSceneManipulatorTool final
{

public:
    QtQuickBased2DSceneManipulatorTool(SceneCamera & camera);

    SceneArea getSceneArea() const;
    void showSceneArea(const SceneArea & area);

    QPointF mapToScene(const QPoint & point) const;
    QPointF mapToScene(const QPoint & point, const SceneArea & sceneArea) const;

public:
    QtQuickBased2DSceneManipulatorTool(const QtQuickBased2DSceneManipulatorTool &) = delete;
    QtQuickBased2DSceneManipulatorTool(QtQuickBased2DSceneManipulatorTool &&) = delete;

    QtQuickBased2DSceneManipulatorTool & operator=(const QtQuickBased2DSceneManipulatorTool &) = delete;
    QtQuickBased2DSceneManipulatorTool & operator=(QtQuickBased2DSceneManipulatorTool &&) = delete;

private:
    SceneCamera & mCamera;
    QtQuickBased2DSceneCoordinatesMapper mMapper;
};

} //~namespace qt_quick

} //~namespace rogii
