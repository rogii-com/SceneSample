#pragma once

class QEvent;
class QQuickItem;

namespace rogii
{

namespace qt_quick
{

class IChildMouseEventListener
{
public:
	virtual ~IChildMouseEventListener() = default;

	virtual bool childMouseEvent(QQuickItem * item, QEvent * event) = 0;
};

} //~namespace qt_quick

} //~namespace rogii
