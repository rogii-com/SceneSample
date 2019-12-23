#include <QSize>
#include <QPointF>
#include <QTransform>

namespace rogii
{

namespace qt_quick
{

QPointF mapFromScreenToNormalized(const QSize & viewportSize, const QPoint & screenPoint);

QPoint mapFromNormalizedToScreen(const QSize & viewportSize, const QPointF & normalizedPoint);

QPointF mapFromSceneToNormalized(const QTransform & normalizingMatrix, const QPointF & scenePoint);

QPointF mapFromNormalizedToScene(const QTransform & invertedNormalizingMatrix, const QPointF & normalizedPoint);

QPointF mapToScene(const QSize & viewportSize, const QTransform &invertedNormalizingMatrix, const QPoint & screenPoint);

QPoint mapFromScene(const QSize & viewportSize, const QTransform &normalizingMatrix, const QPointF & scenePoint);

} //~namespace qt_quick

} //~namespace rogii
