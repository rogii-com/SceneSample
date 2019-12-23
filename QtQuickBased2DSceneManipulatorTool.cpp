#include "QtQuickBased2DSceneManipulatorTool.hpp"

namespace rogii
{

namespace qt_quick
{

QtQuickBased2DSceneManipulatorTool::QtQuickBased2DSceneManipulatorTool(SceneCamera & camera)
    : mCamera(camera)
    , mMapper(camera)
{
}

SceneArea QtQuickBased2DSceneManipulatorTool::getSceneArea() const
{
    const QRect rect(QRect(QPoint(0, 0), mCamera.getViewportSize()));
    const QRectF result(mMapper.mapToScene(rect));
    return result;
}

void QtQuickBased2DSceneManipulatorTool::showSceneArea(const SceneArea & area)
{
//    QMatrix4x4 scaleMatrix;
    QTransform scaleMatrix;
    scaleMatrix.scale((qFuzzyIsNull(area.getWidth())
                            ? 1
                            : 2 / area.getWidth()),
                      (qFuzzyIsNull(area.getHeight())
                            ? 1
                            : -2 / area.getHeight()));

    const QPointF center(area.getCenter());
    QTransform translateMatrix;
//    translateMatrix.translate(-QVector3D(center.x(), center.y(), 0.0));
    translateMatrix.translate(-center.x(), -center.y());

    mCamera.setMatrixes(translateMatrix, scaleMatrix);
}

QPointF QtQuickBased2DSceneManipulatorTool::mapToScene(const QPoint & point) const
{
    return mMapper.mapToScene(point);
}

QPointF QtQuickBased2DSceneManipulatorTool::mapToScene(const QPoint & point, const SceneArea & sceneArea) const
{
    const QSizeF & viewportSize(mCamera.getViewportSize());
    return QPointF(sceneArea.getCenterX() + sceneArea.getWidth() * point.x() / viewportSize.width() - sceneArea.getWidth() / 2,
                   sceneArea.getCenterY() + sceneArea.getHeight() * point.y() / viewportSize.height() - sceneArea.getHeight() / 2);
}

} //~namespace qt_quick

} //~namespace rogii
