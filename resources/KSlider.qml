import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import KLib 1.0


Rectangle {
    id: root
    readonly property double value: slider.value
    property double from: 0
    property double to: 1
    property double stepSize: 0.001
    property string caption

    ColumnLayout {
        anchors.fill: parent
        Text {
            id: captionText
            Layout.leftMargin: 20
            Layout.fillWidth: true
            Layout.preferredWidth: root.caption === "" ? 0 : 14
            text: root.caption
        }
        Slider {
            Layout.fillWidth: true
            Layout.fillHeight: true
            id: slider
            from: root.from
            to: root.to
            stepSize: root.stepSize
        }
        Text {
            Layout.leftMargin: 20
            Layout.fillWidth: true
            Layout.preferredWidth: 14
            text: slider.value.toFixed(2);
        }
    }
}
