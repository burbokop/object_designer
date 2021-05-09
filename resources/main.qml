import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.0
import KLib 1.0

Window {
    id: root
    width: 950
    height: 800
    visible: true

    AppCore {
        id: appCore
    }

    RowLayout {
        anchors.fill: parent
        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.margins: 4
                id: rootRect
                border.width: 1

                ListView {
                    anchors.fill: parent
                    anchors.margins: 2
                    model: appCore.moduleHandler.instances

                    spacing: 12

                    clip: true

                    delegate: KDelegateChooser {
                        id: chooser
                        width: rootRect.width - 4
                        height: 150

                        delegates: [
                            KDelegate {
                                Component.onCompleted: {
                                    //chooser.height = 150;
                                }
                                width: 100
                                height: 100
                                modelDataType: "Client1"
                                Client1Panel {
                                    property bool bbb: false
                                    anchors.fill: parent
                                    client: modelData
                                }
                            },
                            KDelegate {
                                modelDataType: "KLocalRetranslator"
                                Rectangle {
                                    anchors.fill: parent
                                    border.width: 1
                                    ListView {
                                        anchors.fill: parent
                                        anchors.margins: 2
                                        model: connections
                                        delegate: Text {
                                            text: modelData
                                        }
                                    }
                                }
                            },
                            KDelegate {
                                modelDataType: "Client2"
                                Rectangle {
                                    anchors.fill: parent
                                    border.width: 1
                                    TextEdit {
                                        anchors.fill: parent
                                        anchors.margins: 2
                                        text: modelData["text"]
                                        onTextChanged: {
                                            resText.text = appCore.parseFormula(text)
                                        }
                                    }

                                    Text {
                                        id: resText
                                        anchors.bottom: parent.bottom
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        text: "your friend on: " + initialInfo
                                    }
                                }
                            },
                            KDelegate {
                                Component.onCompleted: {
                                    chooser.height = 400;
                                }
                                modelDataType: "AcousticAntenna"

                                ColumnLayout {
                                    anchors.fill: parent
                                    Rectangle {
                                        Layout.fillWidth: true
                                        Layout.fillHeight: true
                                        color: "#343434"
                                        border.width: 1

                                        KAfterShiningMonitor {
                                            id: asm
                                            afterShiningIntencity: afCoefSlider.value
                                            anchors.fill: parent
                                            contentPaintedItem: LineMonitor {
                                                color: "#00ff00"
                                                id: lineMonitor
                                                sweep: modelData.sweep
                                                distance: modelData.distance
                                                minDistance: 0
                                                maxDistance: 360
                                                groupCount: modelData.xnCount
                                                trackCount: modelData.channelCount
                                                anchors.fill: parent
                                                sightRelativeX: sightXSlider.value
                                                sightRelativeY: sightYSlider.value
                                                sightOpacity: 0.2
                                                tan: 0.15
                                                sightRadius: 2
                                                sightCount: 12
                                                antialiasing: true
                                                smooth: true
                                            }
                                        }
                                        FastBlur { radius: 32; anchors.fill: asm; source: asm }

                                        HueSaturation {
                                            id: saturation
                                            anchors.fill: asm
                                            source: asm
                                            hue: -0.3
                                            saturation: 0.5
                                            lightness: -0.1
                                        }

                                        BeamTubeEffect {
                                            anchors.fill: asm
                                            source: asm
                                        }

                                        MouseArea {
                                            anchors.fill: asm
                                            onClicked: saturation.visible = !saturation.visible
                                        }

                                        RpItem {
                                            width: 200
                                            height: 200
                                            anchors.centerIn: parent
                                            shiftAngle: 12
                                            count: 12
                                            widthAngle: 10
                                            color: "#888800ff"
                                            rotation: -90
                                        }

                                        Rectangle {
                                            width: 8
                                            height: 80
                                            anchors.centerIn: parent
                                            rotation: rotor.resultAngle
                                            color: "#ff8800"

                                            Rectangle {
                                                color: "#ff8800"
                                                border.width: 2
                                                width: 4
                                                height: 4
                                                anchors.horizontalCenter: parent.horizontalCenter
                                                anchors.top: parent.top
                                                anchors.margins: 2
                                            }
                                        }
                                    }
                                    Rectangle {
                                        Layout.fillWidth: true
                                        Layout.preferredHeight: 70
                                        color: "#ff8000"
                                        RowLayout {
                                            anchors.fill: parent
                                            KSlider {
                                                color: "#88ffffff"
                                                Layout.fillWidth: true
                                                Layout.fillHeight: true
                                                id: sightXSlider
                                                caption: "sightX"
                                            }
                                            KSlider {
                                                color: "#88ffffff"
                                                Layout.fillWidth: true
                                                Layout.fillHeight: true
                                                id: sightYSlider
                                                caption: "sightY"
                                            }
                                            KSlider {
                                                color: "#88ffffff"
                                                Layout.fillWidth: true
                                                Layout.fillHeight: true
                                                id: afCoefSlider
                                                caption: "afCoef"
                                                from: 0.1
                                                to: 37
                                            }
                                        }
                                    }
                                }
                            }
                        ]
                    }
                }
            }
        }

        EditPopup {
            Layout.fillHeight: true
            Layout.preferredWidth: editCheckBox.checked ? parent.width * 0.6 : 0
            Behavior on Layout.preferredWidth { NumberAnimation { duration: 4000 } }
            id: editPopup
        }
    }

    CheckBox {
        z: 1
        x: 0
        y: 0
        text: "open"
        id: editCheckBox
        onCheckedChanged: {
            if(checked) {
                root.visibility = Window.FullScreen
            } else {
                root.visibility = Window.Windowed
            }
        }
    }
}
