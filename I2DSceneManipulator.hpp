#pragma once

#include <QPoint>
#include <QRect>

namespace rogii
{

class I2DSceneManipulator
{
public:
	virtual ~I2DSceneManipulator()
	{
	}

	/**
	 * @brief Zooms @a zoomSteps in or out the scene.
	 */
	virtual void zoom(int zoomSteps) = 0;

	/**
	 * @brief Zooms @a zoomSteps in or out the scene relative to @a pivotPoint.
	 */
	virtual void zoom(int zoomSteps, QPoint pivotPoint) = 0;

	/**
	 * @brief Zooms and shifts the scene so the selected area occupies the whole widget.
	 * @param newSceneRect is in widget coordinates
	 */
	virtual void showArea(const QRect & windowAreaToZoom) = 0;

	/**
	 * @brief Shifts the scene by screen shifts
	 * @param dx in window coordinates
	 * @param dy in window coordinates
	 */
	virtual void shift(int dx, int dy) = 0;

	/**
	 * @brief Zooms and shifts the scene the best way to show \a area.
	 * @param rect is in scene coordinates
	 */
	virtual void showSceneArea(const QRectF & area) = 0;
};

} //~namespace rogii
