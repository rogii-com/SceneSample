#pragma once

class QPoint;
class QPointF;
class QRect;
class QRectF;
class QLine;
class QLineF;

namespace rogii
{

class I2DSceneCoordinatesMapper
{
public:
	virtual ~I2DSceneCoordinatesMapper()
	{
	}

	/**
	 * @param windowPosition In widget coordinates,
	 * so the coordinates of the scene topLeft point is not 0, 0
	 */
	virtual QPointF mapToScene(const QPoint & windowPosition) const = 0;
	/**
	 * @brief Map screen \a windowRectangle coordinates to scene coordinates.
	 * TopLeft point of \a windowRectangle matches topLeft point of the result rectangle.
	 * Same about bottomRightPoint.
	 * Depending on the direction of the axis can return a not normalized rectangle.
	 * @param windowRectangle In widget coordinates,
	 * so the coordinates of the scene topLeft point is not 0, 0
	 */
	virtual QRectF mapToScene(const QRect & windowRectangle) const = 0;
	/**
	 * @param windowLine In widget coordinates,
	 * so the coordinates of the scene topLeft point is not 0, 0
	 */
	virtual QLineF mapToScene(const QLine & windowLine) const = 0;

	/**
	 * @return In widget coordinates,
	 * so the coordinates of the scene topLeft point is not 0, 0
	 */
	virtual QPoint mapFromScene(const QPointF & scenePosition) const = 0;
	/**
	 * @brief Map scene \a sceneRectangle coordinates to screen coordinates.
	 * Normalized rectangle always returns regardless of the axis direction.
	 * @return In widget coordinates,
	 * so the coordinates of the scene topLeft point is not 0, 0
	 */
	virtual QRect mapFromScene(const QRectF & sceneRectangle) const = 0;
	/**
	 * @return In widget coordinates,
	 * so the coordinates of the scene topLeft point is not 0, 0
	 */
	virtual QLine mapFromScene(const QLineF & sceneLine) const = 0;

	/** Use this function to avoid float fail. See description in IChartController2.
	 */
	virtual QPointF mapDeltaToScene(const QPoint & deltaInScreen) const = 0;
};

} //~namespace rogii
