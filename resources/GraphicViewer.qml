import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Shapes 1.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import KLib 1.0

Item {
    id: root

    MouseSpy {
        id: mouseSpy
        target: root
    }

    property QtObject selectedObject: null

    property KConnection currentEditedConnection: KConnection {}
    property bool senderChoosed: false

    Item {
        id: scene
        anchors.fill: parent

        Component {
            id: objComponent

            Rectangle {
                z: 0
                property QtObject object
                readonly property KPropertyView props: propeView
                id: rootRect
                width: 100
                height: 200
                border.width: 1
                border.color: "#FFAA00"

                ColumnLayout {
                    anchors.fill: parent
                    Rectangle {
                        border.width: object == selectedObject ? 2 : 1
                        border.color: object == selectedObject ? "#ffaa00" : Qt.darker("#FFAA00")
                        Layout.alignment: Qt.AlignTop
                        Layout.fillWidth: true
                        height: 40
                        clip: true

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                            anchors.margins: 4
                            clip: true
                            text: object ? object.objectName : "null"
                        }

                        MouseArea {
                            id: ma
                            anchors.fill: parent
                            property double startX: 0
                            property double startY: 0
                            onPressed: {
                                startX = mouseX;
                                startY = mouseY;
                                root.selectedObject = object
                            }

                            onMouseXChanged: rootRect.x = mapToItem(scene, mouseX, mouseY).x - startX;
                            onMouseYChanged: rootRect.y = mapToItem(scene, mouseX, mouseY).y - startY;
                        }
                    }

                    Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        KPropertyView {
                            id: propeView
                            anchors.fill: parent
                            anchors.margins: 4

                            modelObject: object

                            delegate: Rectangle {
                                clip: !extendedMode
                                property bool extendedMode: false
                                border.width: 1
                                width: 92
                                height: 18
                                color: (senderChoosed && currentEditedConnection.sender === object.objectName && currentEditedConnection.senderProperty === modelData) ? "#0000ff" : "#ffffff"
                                Text {
                                    anchors.centerIn: parent.extendedMode ? parent : undefined
                                    anchors.left: parent.extendedMode ? undefined : parent.left
                                    anchors.leftMargin: 2
                                    text: parent.extendedMode ? modelData + " " + object[modelData] : modelData
                                    color: writableProperty ? "#000000" : "#ff4000"
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        if(newConnectionMode.checked) {
                                            if(senderChoosed) {
                                                currentEditedConnection.reciever = object.objectName;
                                                currentEditedConnection.recieverProperty = modelData;
                                                appCore.linker.addConnection(
                                                            currentEditedConnection.sender,
                                                            currentEditedConnection.senderProperty,
                                                            currentEditedConnection.reciever,
                                                            currentEditedConnection.recieverProperty
                                                            );
                                                senderChoosed = false;
                                            } else {
                                                currentEditedConnection.sender = object.objectName;
                                                currentEditedConnection.senderProperty = modelData;
                                                senderChoosed = true;
                                            }
                                        } else {
                                            parent.extendedMode = !parent.extendedMode;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        KObjectMap {
            id: itemsMap
        }

        Connections {
            target: KObjectLifeTracker
            function onWatcherTriggered(arg) {
                if(arg.type === "destroy") {
                    arg.object.destroy();
                }
            }
        }

        Timer {
            id: updateTimer
            interval: 100
            running: false
            repeat: false
            onTriggered: repeater.updateArrows();
        }

        Connections {
            target: appCore.linker
            function onObjectAdded(obj) {
                const item = objComponent.createObject(root, { object: obj, x: Math.random() * 400, y: Math.random() * 400 });
                KObjectLifeTracker.registerWatcher(obj, { type: "destroy", object: item });
                itemsMap.insert(obj, item);
                updateTimer.running = true;
            }

            function onConnectionsChanged() {
                repeater.updateArrows();
            }

            function onActiveChanged() {
                repeater.updateArrows();
            }
        }

        ColumnLayout {
            RowLayout {
                Button {
                    text: "update"
                    onClicked: {
                        repeater.updateArrows();
                    }
                }
                ComboBox {
                    id: classesComboBox
                    model: appCore.availableClasses
                }
                Button {
                    text: "new"
                    onClicked: {
                        appCore.newInstance(classesComboBox.currentText, newInstanceNameField.text, selectedObject);
                    }
                }
            }
            TextField {
                id: newInstanceNameField
                text: "prop1"
            }
            CheckBox {
                text: "c+"
                id: newConnectionMode
            }
        }
    }

    Repeater {
        z: 1
        function updateArrows () {
            for (var i = 0; i < repeater.count; i++) {
                repeater.itemAt(i).updateArrow();
            }
        }

        id: repeater;
        model: appCore.linker.connections
        Arrow {
            Timer {
                id: ttt
                interval: 1000
                repeat: false
                onTriggered: {
                    arr.transmitting = false;
                    arr.blocked = false;
                }
            }

            Connections {
                target: modelData
                function onDataTransferred() {
                    ttt.running = true;
                    arr.transmitting = true;
                }
                function onDataBlocked() {
                    ttt.running = true;
                    arr.blocked = true;
                }
            }

            z: 1
            sceneItem: scene
            id: arr

            function updateArrow() {
                arr.item1 = itemFromPair(sender, senderProperty);
                arr.item2 = itemFromPair(reciever, recieverProperty);

                if(!(arr.item1 === undefined && arr.item2 === undefined)) {
                    if(item1 === undefined) {
                        item1 = internetPoint;
                    }
                    if(item2 === undefined) {
                        item2 = internetPoint;
                    }
                }

                arr.active = modelData.active;
            }

            function itemFromPair(objectName, propertyName) {
                const object = appCore.linker.objectOfName(objectName);
                if(object) {
                    const item = itemsMap.value(object);
                    if(item) {
                        const propItem = item.props.record(propertyName);
                        return propItem;
                    }
                }
            }
        }
    }

    Rectangle {
        id: internetPoint
        x: 0
        y: (root.height - height) / 2
        z: 1
        width: 60
        height: 100
        border.width: 1

        Text {
            anchors.centerIn: parent
            text: qsTr("Internet")
        }
    }


    Rectangle {
        id: mousePoint
        x: mouseSpy.mouseX - width / 2
        y: mouseSpy.mouseY - height / 2
        z: 1
        width: 8
        height: 8
        border.width: 1
    }
}
