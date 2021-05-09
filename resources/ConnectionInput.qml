import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import KLib 1.0

RowLayout {
    id: root
    property string prop1
    property string prop2
    property string prop3
    property string prop4

    signal resultReady

    Rectangle {
        color: input1.focus ? "#eeee00" : "#aaaa00"
        Layout.fillWidth: true
        height: parent.height
        KSearchInput {
            id: input1
            model: appCore.linker.objects
            anchors.fill: parent
            anchors.margins: 4
            role: "objectName"
            onAccepted: {
                prop1 = text
                input2.focus = true;
            }
        }
    }

    Rectangle {
        color: input2.focus ? "#eeee00" : "#aaaa00"
        Layout.fillWidth: true
        height: parent.height
        KSearchInput {
            id: input2
            model: appCore.linker.objectOfName(prop1)
            anchors.fill: parent
            anchors.margins: 4
            role: "objectName"
            onAccepted: {
                prop2 = text
                input3.focus = true;
            }
        }
    }

    Rectangle {
        color: input3.focus ? "#eeee00" : "#aaaa00"
        Layout.fillWidth: true
        height: parent.height
        KSearchInput {
            id: input3
            model: appCore.linker.objects
            anchors.fill: parent
            anchors.margins: 4
            role: "objectName"
            onAccepted: {
                prop3 = text
                input4.focus = true;
            }
        }
    }

    Rectangle {
        color: input4.focus ? "#eeee00" : "#aaaa00"
        Layout.fillWidth: true
        height: parent.height
        KSearchInput {
            id: input4
            model: appCore.linker.objectOfName(prop3)
            anchors.fill: parent
            anchors.margins: 4
            role: "objectName"
            onAccepted: {
                prop4 = text
                input4.focus = false;
                resultReady(prop1, prop2, prop3, prop4)
            }
        }
    }
}

