#pragma once

#include <QRectF>
#include <QLineF>

#include "I2DSceneCoordinatesMapper.hpp"

namespace rogii
{

class Base2DSceneCoordinatedMapper : public I2DSceneCoordinatesMapper
{
public:
	// Base2DSceneCoordinatesMapper override
	//@{
	using I2DSceneCoordinatesMapper::mapToScene;
	QRectF mapToScene(const QRect & windowRectangle) const override;
	QLineF mapToScene(const QLine & windowLine) const override;

	using I2DSceneCoordinatesMapper::mapFromScene;
	QRect mapFromScene(const QRectF & sceneRectangle) const override;
	QLine mapFromScene(const QLineF & sceneLine) const override;

	QPointF mapDeltaToScene(const QPoint & deltaInScreen) const override;
	//@}
};

} //~namespace rogii
