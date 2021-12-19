import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import KLib 1.0

Rectangle {
    border.width: 1
    clip: true
    property QtObject client
    property double formulaResult
    property string substituteResult

    GridLayout {
        anchors.fill: parent
        anchors.margins: 6
        rows: 2
        columns: 2


        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            width: 150
            height: 50
            border.width: 1

            TextInput {
                anchors.margins: 2
                anchors.fill: parent
                text: ""
                onTextChanged: {
                    client.sendMessage(text);
                    formulaResult = appCore.parseFormula(text);
                    substituteResult = appCore.substitute(text);
                }
            }
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            width: 150
            height: 50
            border.width: 1

            Timer {
                running: true
                repeat: true
                interval: 40
                onTriggered: {
                    const speed = 0.5
                    if(but1.pressed) {
                        client.angle = KMath.constrainDegrees(client.angle - speed)
                    } else if(but2.pressed) {
                        client.angle = KMath.constrainDegrees(client.angle + speed)
                    }
                }
            }

            ColumnLayout {
                anchors.fill: parent
                RowLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Button {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        Layout.margins: 16
                        id: but1
                        text: "<"
                    }

                    Button {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        Layout.margins: 16
                        width: 60
                        height: 40
                        id: but2
                        text: ">"
                    }
                }
                RowLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    CheckBox {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        onCheckedChanged: {
                            client.checkBox = checked;
                        }
                    }

                    Slider {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        enabled: false
                        value: client != null && Math.sin(client.angle2 * 0.1)
                    }

                    KLamp {
                        Layout.preferredWidth: height
                        Layout.fillHeight: true
                        state: client != null && client.lamp
                        Layout.margins: 8
                    }
                }
            }
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            width: 150
            height: 50
            border.width: 1

            GridLayout {
                anchors.fill: parent
                KSlider {
                    onValueChanged: client.slider1 = value
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //stepSize: 1
                    to: 10
                }
                KSlider {
                    onValueChanged: client.slider2 = value
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    to: 5
                }
                KSlider {
                    onValueChanged: client.slider3 = value
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    to: 100
                }
                KSlider {
                    onValueChanged: client.slider4 = value
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    to: 360
                }
                KSlider {
                    onValueChanged: client.slider5 = value
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    from: 0
                    to: 4
                }
            }
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            width: 150
            height: 50
            border.width: 1
            Flickable {
                clip: true
                focus: true
                anchors.fill: parent
                Text {
                    anchors.centerIn: parent
                    clip: true
                    //text: "your friend on: " + client.initialInfo
                    text: formulaResult
                }
            }
        }
    }
}
