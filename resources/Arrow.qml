import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Shapes 1.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import KLib 1.0

Shape {
    z: 1
    property Item sceneItem

    id: arrow2
    property var item1
    property var item2

    property point _p1: Qt.point(100, 10)
    property point _p2: Qt.point(200, 10)

    property int offset: 10

    Timer {
        running: transmitting || blocked
        interval: 100
        repeat: true
        onTriggered: {
            transmittingColor = !transmittingColor;
        }
        onRunningChanged: {
            transmittingColor = false;
        }
    }
    property bool transmittingColor: false

    property color lineColor: active ? (transmittingColor ? (blocked ? "#ff0000" : "#180773") : "#7CE700") : "#444444"

    property bool active: false
    property bool transmitting: false
    property bool blocked: false

    QtObject {
        id: __

        property double item1width: (item1 !== undefined && item1 !== null) ? item1.width : 0
        property double item2width: (item2 !== undefined && item2 !== null) ? item2.width : 0

        property double startX: arrow2._p1.x - ((arrow2._p1.x < arrow2._p2.x) ? 0 : item1width)
        property double startY: arrow2._p1.y

        property double endX: arrow2._p2.x - ((arrow2._p1.x > arrow2._p2.x) ? 0 : item2width)
        property double endY: arrow2._p2.y


        function coord(c1, c2, coef) {
            if(coef + 1 === 0)
                return 0;

            return (c2 + coef * c1) / (1 + coef);
        }

        function coord2(x1, y1, x2, y2, dst) {
            const l = Math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
            const k = dst / l;
            return { x: coord(x1, x2, k), y: coord(y1, y2, k) };
        }

        property double midX: coord2(startX, startY, endX, endY, 12).x;
        property double midY: coord2(startX, startY, endX, endY, 12).y;
    }

    ShapePath {
        fillColor: "transparent"
        strokeColor: lineColor
        strokeWidth: active ? 2 : 1
        startX: __.startX
        startY: __.startY
        PathLine { x: __.midX; y: __.midY }
    }

    ShapePath {
        fillColor: "transparent"
        strokeColor: Qt.darker(lineColor)
        strokeWidth: active ? 4 : 1
        startX: __.midX
        startY: __.midY
        PathLine { x: __.endX; y: __.endY }
    }

    visible: item1 !== null && item1 !== undefined && item2 !== null && item2 !== undefined;

    property var _item1 : null
    property var _item2 : null

    onItem2Changed: {
        if (_item2 !== null) {
            var it = _item2;
            while (it !== sceneItem && it !== null && it !== undefined) {
                it.xChanged.disconnect(setP2)
                it.yChanged.disconnect(setP2)
                it = it.parent
            }
        }
        _item2 = item2
        setP2()
        var itt = item2;
        while (itt !== sceneItem && itt !== null && itt !== undefined) {
            itt.xChanged.connect(setP2)
            itt.yChanged.connect(setP2)
            itt = itt.parent
        }
    }

    onItem1Changed: {
        if (_item1 !== null) {
            var it = _item1;
            while (it !== sceneItem && it !== null && it !== undefined) {
                try{
                    it.xChanged.disconnect(setP1)
                    it.yChanged.disconnect(setP1)
                } catch (err) { break; }
                it = it.parent
            }
        }
        _item1 = item1
        setP1()
        var itt = item1;
        while (itt !== sceneItem && itt !== null && itt !== undefined) {
            itt.xChanged.connect(setP1)
            itt.yChanged.connect(setP1)
            itt = itt.parent
        }
    }

    function setP1() { if(item1 === undefined || item1 === null || item1.parent === null) return; _p1 = sceneItem.mapFromItem(item1.parent, item1.x + item1.width, item1.y + item1.height / 2); }
    function setP2() { if(item2 === undefined || item2 === null || item2.parent === null) return; _p2 = sceneItem.mapFromItem(item2.parent, item2.x + item2.width, item2.y + item2.height / 2); }
}
