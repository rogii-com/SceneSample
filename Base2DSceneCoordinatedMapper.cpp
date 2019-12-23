#include "Base2DSceneCoordinatedMapper.hpp"

namespace rogii
{

namespace
{

QPoint getQRectTrueBottomRight(const QRect & rect)
{
    return rect.topLeft() + QPoint(rect.width(), rect.height());
}

QRect createQRectWithTrueBottomRightPoint(const QPoint & topLeft, const QPoint & bottomRight)
{
    return QRect(topLeft, QSize(bottomRight.x() - topLeft.x(),
                                bottomRight.y() - topLeft.y()));
}

} // anonymous namespace

QRectF Base2DSceneCoordinatedMapper::mapToScene(const QRect & windowRectangle) const
{
    const QPointF topLeft(mapToScene(windowRectangle.topLeft()));
    const QPointF bottomRight(mapToScene(getQRectTrueBottomRight(windowRectangle)));
    return { topLeft, bottomRight };
}

QLineF Base2DSceneCoordinatedMapper::mapToScene(const QLine & windowLine) const
{
	const QLineF mappedLine(mapToScene(windowLine.p1()), mapToScene(windowLine.p2()));
	return mappedLine;
}

QRect Base2DSceneCoordinatedMapper::mapFromScene(const QRectF & sceneRectangle) const
{
	return (createQRectWithTrueBottomRightPoint(mapFromScene(sceneRectangle.topLeft()),
												mapFromScene(sceneRectangle.bottomRight()))
			.normalized());
}

QLine Base2DSceneCoordinatedMapper::mapFromScene(const QLineF & sceneLine) const
{
	const QLine mappedLine(mapFromScene(sceneLine.p1()), mapFromScene(sceneLine.p2()));
	return mappedLine;
}

QPointF Base2DSceneCoordinatedMapper::mapDeltaToScene(const QPoint & deltaInScreen) const
{
	const QPointF zeroOnScene(mapToScene(QPoint(0, 0)));
	const QPointF mappedPoint(mapToScene(deltaInScreen));

	return mappedPoint - zeroOnScene;
}

} //~namespace rogii
