#pragma once

#include "I2DSceneManipulator.hpp"

#include "QtQuickBased2DSceneManipulatorTool.hpp"

namespace rogii
{

namespace qt_quick
{

class LogTrackSceneCameraManipulator final : public I2DSceneManipulator
{
public:
    LogTrackSceneCameraManipulator(SceneCamera & camera);

    // I2DSceneManipulator implementation
    //@{
    void zoom(int zoomSteps) override;
    void zoom(int zoomSteps, QPoint pivotPoint) override;
    void showArea(const QRect & windowAreaToZoom) override;
    void shift(int dx, int dy) override;
    void showSceneArea(const QRectF & area) override;
    //@}

private:
    SceneCamera & mCamera;
    QtQuickBased2DSceneManipulatorTool mManipulatorTool;
};

} //~namespace qt_quick

} //~namespace rogii
