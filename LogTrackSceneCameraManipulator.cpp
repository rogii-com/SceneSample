#include "LogTrackSceneCameraManipulator.hpp"

namespace rogii
{

namespace qt_quick
{

const double gZoomFactor(0.01);

const double gDefaultMinimalScalePower(-23.5);
const double gDefaultMaximalScalePower(10);

template<typename T>
T clamp(T start, T end, T value)
{
    return std::max(start, std::min(end, value));
}

LogTrackSceneCameraManipulator::LogTrackSceneCameraManipulator(SceneCamera & camera)
    : mCamera(camera)
    , mManipulatorTool(camera)
{
}

void LogTrackSceneCameraManipulator::zoom(int zoomSteps)
{
    const QSizeF & viewportSize(mCamera.getViewportSize());
    const QPoint center(viewportSize.width() / 2.0, viewportSize.height() / 2.0);
    zoom(zoomSteps, center);
}

void LogTrackSceneCameraManipulator::zoom(int zoomSteps, QPoint pivotPoint)
{
    SceneArea sceneArea(mManipulatorTool.getSceneArea());

    const QPointF pivotPointOnSceneBeforeZoom(mManipulatorTool.mapToScene(pivotPoint, sceneArea));
    const double powerDelta(zoomSteps * gZoomFactor);
    const double powerY(std::log2(std::abs(mCamera.getViewportSize().height()
                                           / sceneArea.getHeight())));

    const double newPowerY(clamp(gDefaultMinimalScalePower, gDefaultMaximalScalePower, powerY + powerDelta));

    const double scaleY(std::pow(2, -(newPowerY - powerY)));

    sceneArea.setHeight(sceneArea.getHeight() * scaleY);

    const QPointF pivotPointOnSceneAfterZoom(mManipulatorTool.mapToScene(pivotPoint, sceneArea));

    sceneArea.translate(pivotPointOnSceneBeforeZoom - pivotPointOnSceneAfterZoom);

    mManipulatorTool.showSceneArea(sceneArea);
}

void LogTrackSceneCameraManipulator::showArea(const QRect & windowAreaToZoom)
{
    const QSizeF & viewportSize(mCamera.getViewportSize());
    const double minimalSceneAreaHeigth(viewportSize.height() / std::pow(2, gDefaultMaximalScalePower));
    const double requiredSceneAreaHeight((mManipulatorTool.mapToScene(QPoint(0, windowAreaToZoom.height()))
                                          - mManipulatorTool.mapToScene(QPoint(0, 0))).y());
    const double newSceneAreaHeight(std::min(minimalSceneAreaHeigth,
                                             requiredSceneAreaHeight));

    SceneArea newSceneArea(mManipulatorTool.mapToScene(windowAreaToZoom.center()),
                           QSizeF(2.0, newSceneAreaHeight));

    mManipulatorTool.showSceneArea(newSceneArea);
}

void LogTrackSceneCameraManipulator::shift(int dx, int dy)
{
    /** TODO: check limits. Maybe this has to be done inmManipulatorTool.showSceneArea(sceneArea);
     */

    SceneArea sceneArea(mManipulatorTool.getSceneArea());

    const QPointF deltaInScene(
                mManipulatorTool.mapToScene(QPoint(0, 0), sceneArea)
                - mManipulatorTool.mapToScene(QPoint(dx, dy), sceneArea));

    sceneArea.translate(deltaInScene);

    mManipulatorTool.showSceneArea(sceneArea);
}

void LogTrackSceneCameraManipulator::showSceneArea(const QRectF & area)
{
    /** TODO: check limits. Maybe this has to be done inmManipulatorTool.showSceneArea(sceneArea);
     */

    SceneArea sceneArea(area);

    {
        sceneArea.setCenter(0.0, sceneArea.getCenterY());
        sceneArea.setWidth(2.0);
    }

    mManipulatorTool.showSceneArea(sceneArea);
}

} //~namespace qt_quick

} //~namespace rogii
