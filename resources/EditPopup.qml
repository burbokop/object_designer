import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.0
import KLib 1.0

Item {
    id: root
    
    RowLayout {
        anchors.fill: parent
        spacing: 2
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#aaaaaa"

            ColumnLayout {
                anchors.fill: parent
                RowLayout {
                    ComboBox {
                        width: 70
                        height: 40
                        model: appCore.moduleHandler.availableModes

                        onCurrentTextChanged: {
                            appCore.moduleHandler.mode = currentText;
                        }
                    }

                    ConnectionInput {
                        Layout.fillWidth: true
                        height: 40
                        onResultReady: {
                            appCore.linker.addConnection(prop1, prop2, prop3, prop4)
                        }
                    }
                }

                TabBar {
                    Layout.fillWidth: true
                    height: 40
                    id: tabBar
                    TabButton {
                        height: 40
                        Layout.fillWidth: true
                        Layout.margins: 4
                        text: qsTr("connections")
                    }
                    TabButton {
                        height: 40
                        Layout.fillWidth: true
                        Layout.margins: 4
                        text: qsTr("objects")
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.margins: 4
                    border.width: 1
                    color: "#dddddd"

                    Layout.fillHeight: true

                    StackLayout {
                        anchors.fill: parent
                        anchors.margins: 4
                        currentIndex: tabBar.currentIndex
                        ListView {
                            spacing: 2
                            clip: true
                            id: connectionListView
                            //anchors.fill: parent
                            anchors.margins: 4
                            model: appCore.linker.connections

                            delegate: Rectangle {
                                width: connectionListView.width
                                height: 40
                                color: modelData.active ? "#55dddd" : "#44aaaa"
                                RowLayout {
                                    anchors.fill: parent
                                    Text {
                                        function lastInArray(arr) {
                                            return arr[arr.length - 1];
                                        }

                                        function aaa(str) {
                                            const arr = str.split('.');
                                            const last = lastInArray(arr);

                                            let result = "";
                                            for(let i = 0; i < arr.length - 1; ++i) {
                                                const a = arr[i];
                                                if(a.length > 0) {
                                                    result += (a[0] + '.');
                                                }
                                            }
                                            result += last;
                                            return result;
                                        }

                                        Layout.fillWidth: true
                                        anchors.margins: 4
                                        text: aaa(sender) + "->" + senderProperty + " => " + aaa(reciever) + "->" + recieverProperty
                                    }
                                    CheckBox {
                                        width: 50
                                        checked: true
                                        text: "enable"
                                        onCheckedChanged: {
                                            modelData.active = checked
                                        }
                                    }
                                    Button {
                                        width: 50
                                        text: "remove"
                                        onClicked: {
                                            appCore.linker.removeConnection(modelData);
                                        }
                                    }
                                }
                            }
                        }

                        ListView {
                            spacing: 2
                            clip: true
                            id: objectsListView
                            //anchors.fill: parent
                            anchors.margins: 4
                            model: appCore.linker.objects
                            delegate: Rectangle {
                                width: objectsListView.width
                                height: 40
                                color: "#aa44aa"
                                Text {
                                    anchors.centerIn: parent
                                    anchors.margins: 4
                                    text: modelData.objectName
                                }
                            }
                        }

                    }
                }
            }
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#aaaaaa"

            GraphicViewer {
                anchors.fill: parent
            }
        }
    }
}
