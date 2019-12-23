import QtQuick 2.7

import ROGII.QtQuick 1.0

Item {
    Rectangle {
        id: row

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        width: Math.round(0.4 * parent.width)

        color: Qt.lighter('red')

        Scene {
            objectName: 'scene1'

            anchors.fill: parent
            anchors.margins: 5

            Rectangle {
                anchors.fill: parent

                color: Qt.lighter('gray')
            }

            ShiftArea {
                objectName: 'sceneMouseArea'

                anchors.fill: parent
            }

            LineStrip {
                Component.onCompleted: {
                    var stepCount = 600;
                    var pointCount = stepCount + 1;
                    var minValue = -5;
                    var maxValue = 5;

                    setColor('red')
                    reserve(pointCount)

                    for (var i = 0; i < pointCount; ++i)
                    {
                        const factor = i / stepCount;
                        var oneMinusFactor = (stepCount - i) / stepCount;

                        var y = minValue * oneMinusFactor + maxValue * factor;
                        var randomDelta = (1 - 2 * Math.random()) * 0.05
                        var x = Math.cos(y) + randomDelta;
                        appendPoint(Qt.point(x, y));
                    }
                }
            }
        }
    }

    Item {
        id: column

        anchors.left: row.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        Rectangle {
            id: rect1

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: Math.round(parent.height * 0.5)

            color: 'gray'

            Scene {
                objectName: 'scene2'

                anchors.fill: parent
                anchors.margins: 5

                Rectangle {
                    anchors.fill: parent

                    color: Qt.lighter('yellow')
                }

                ShiftArea {
                    objectName: 'sceneMouseArea'

                    anchors.fill: parent
                }

                LineStrip {
                    Component.onCompleted: {
                        var stepCount = 400;
                        var pointCount = stepCount + 1;
                        var minValue = 0.01
                        var maxValue = 10

                        reserve(pointCount)

                        for (var i = 0; i < pointCount; ++i)
                        {
                            const factor = i / stepCount;
                            var oneMinusFactor = (stepCount - i) / stepCount;

                            var x = minValue * oneMinusFactor + maxValue * factor
                            var randomDelta = (1 - 2 * Math.random()) * 0.05
                            var y = Math.log(x) + randomDelta
                            appendPoint(Qt.point(x, y));
                        }
                    }
                }

                LineStrip {
                    Component.onCompleted: {
                        var stepCount = 300;
                        var pointCount = stepCount + 1;
                        var minValue = 0.01
                        var maxValue = 10

                        setColor('brown')
                        reserve(pointCount)

                        for (var i = 0; i < pointCount; ++i)
                        {
                            const factor = i / stepCount;
                            var oneMinusFactor = (stepCount - i) / stepCount;

                            var x = minValue * oneMinusFactor + maxValue * factor
                            var randomDelta = (1 - 2 * Math.random()) * 0.05
                            var y = 0.7 * Math.sin(Math.log(x) + 0.6) + randomDelta
                            appendPoint(Qt.point(x, y));
                        }
                    }
                }
            }
        }

        Rectangle {
            anchors.top: rect1.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            color: 'blue'

            Scene {
                objectName: 'scene3'

                anchors.fill: parent
                anchors.margins: 5

                Rectangle {
                    anchors.fill: parent

                    color: Qt.lighter('yellow')
                }

                ShiftArea {
                    objectName: 'sceneMouseArea'

                    anchors.fill: parent
                }

                LineStrip {
                    Component.onCompleted: {
                        var stepCount = 400;
                        var pointCount = stepCount + 1;
                        var minValue = 0.01
                        var maxValue = 10

                        reserve(pointCount)

                        for (var i = 0; i < pointCount; ++i)
                        {
                            const factor = i / stepCount;
                            var oneMinusFactor = (stepCount - i) / stepCount;

                            var x = minValue * oneMinusFactor + maxValue * factor
                            var randomDelta = (1 - 2 * Math.random()) * 0.05
                            var y = Math.log(x) + randomDelta
                            appendPoint(Qt.point(x, y));
                        }
                    }
                }

                LineStrip {
                    Component.onCompleted: {
                        var stepCount = 300;
                        var pointCount = stepCount + 1;
                        var minValue = 0.01
                        var maxValue = 10

                        setColor('brown')
                        reserve(pointCount)

                        for (var i = 0; i < pointCount; ++i)
                        {
                            const factor = i / stepCount;
                            var oneMinusFactor = (stepCount - i) / stepCount;

                            var x = minValue * oneMinusFactor + maxValue * factor
                            var randomDelta = (1 - 2 * Math.random()) * 0.05
                            var y = 0.7 * Math.sin(Math.log(x) + 0.6) + randomDelta
                            appendPoint(Qt.point(x, y));
                        }
                    }
                }

                LineStrip {
                    Component.onCompleted: {
                        var stepCount = 1000;
                        var pointCount = stepCount + 1;
                        var minValue = 0.01
                        var maxValue = 10

                        setColor('green')
                        reserve(pointCount)

                        for (var i = 0; i < pointCount; ++i)
                        {
                            const factor = i / stepCount;
                            var oneMinusFactor = (stepCount - i) / stepCount;

                            var x = minValue * oneMinusFactor + maxValue * factor
                            var randomDelta = (1 - 2 * Math.random()) * 0.05
                            var y = 3 * Math.cos(x + 0.6) + randomDelta
                            appendPoint(Qt.point(x, y));
                        }
                    }
                }
            }
        }
    }
}
