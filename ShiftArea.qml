import QtQuick 2.9

MouseArea {
    preventStealing: true
    acceptedButtons: Qt.AllButtons
    cursorShape: internal.capturedPoint !== undefined ? Qt.ClosedHandCursor : Qt.ArrowCursor

    Component.onDestruction: cursorShape = Qt.ArrowCursor

    QtObject {
        id: internal
        property var capturedPoint: undefined

        function resetCapturedPoint()
        {
            internal.capturedPoint = undefined
        }
    }

    signal shift(real deltaX, real deltaY)
    signal zoom(real step, point pivotPoint)

    onPressed: {
        if (mouse.buttons === Qt.LeftButton)
        {
            internal.capturedPoint = Qt.point(mouse.x, mouse.y)
        }
    }

    onPositionChanged: {
        if (internal.capturedPoint !== undefined)
        {
            var deltaY = mouse.y - internal.capturedPoint.y
            var deltaX = mouse.x - internal.capturedPoint.x
            if (Math.abs(deltaY) > 0 || Math.abs(deltaX) > 0)
                shift(deltaX, deltaY)

            internal.capturedPoint = Qt.point(mouse.x, mouse.y)
        }
    }

    onReleased: internal.resetCapturedPoint()
    onCanceled: internal.resetCapturedPoint()

    onWheel: {
        const gMouseWheelZoomStep = 1
        const gMouseUnitsToDegreesCoef = 0.125

        const zoomStep = gMouseWheelZoomStep * wheel.angleDelta.y * gMouseUnitsToDegreesCoef

        zoom(-zoomStep, Qt.point(wheel.x, wheel.y))
    }
}
