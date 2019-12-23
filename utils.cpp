#include "utils.hpp"

namespace rogii
{

namespace qt_quick
{

QPointF mapFromScreenToNormalized(const QSize & viewportSize, const QPoint & screenPoint)
{
    const qreal width(viewportSize.width() == 0 ? 1 : viewportSize.width());
    const qreal height(viewportSize.height() == 0 ? 1 : viewportSize.height());

    return QPointF(qreal(2)*screenPoint.x() / width - qreal(1),
                   -((qreal(2)*screenPoint.y() / height - qreal(1))));
}

QPoint mapFromNormalizedToScreen(const QSize & viewportSize, const QPointF & normalizedPoint)
{
    return QPoint(std::abs(viewportSize.width()) * (normalizedPoint.x() + 1) / 2,
                  -(std::abs(viewportSize.height()) * (normalizedPoint.y() - 1) / 2));
}

QPointF mapFromSceneToNormalized(const QTransform & normalizingMatrix, const QPointF & scenePoint)
{
//    const QVector4D sceneVec4(scenePoint.x(), scenePoint.y(), 0.f, 1.f);
//    const QVector4D normalizedVec4(normalizingMatrix * sceneVec4);

    return normalizingMatrix.map(scenePoint);

//    return {normalizedVec4.x(), normalizedVec4.y()};
}

QPointF mapFromNormalizedToScene(const QTransform & invertedNormalizingMatrix, const QPointF & normalizedPoint)
{
//    const QVector4D norimalizedVec4(normalizedPoint.x(), normalizedPoint.y(), 0.f, 1.f);
//    const QVector4D sceneVec4(invertedNormalizingMatrix * norimalizedVec4);
//    return {sceneVec4.x(), sceneVec4.y()};

    return invertedNormalizingMatrix.map(normalizedPoint);
}

QPointF mapToScene(const QSize & viewportSize, const QTransform &invertedNormalizingMatrix, const QPoint & screenPoint)
{
    return mapFromNormalizedToScene(invertedNormalizingMatrix, mapFromScreenToNormalized(viewportSize, screenPoint));
}

QPoint mapFromScene(const QSize & viewportSize, const QTransform &normalizingMatrix, const QPointF & scenePoint)
{
    return mapFromNormalizedToScreen(viewportSize, mapFromSceneToNormalized(normalizingMatrix, scenePoint));
}

} //~namespace qt_quick

} //~namespace rogii
