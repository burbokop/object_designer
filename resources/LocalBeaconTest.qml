import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12

import KLib 1.0

Window {
    visible: true
    width: 400
    height: 200

    KLocalBeacon {
        id: beacon
    }

    KLocalSyncronizer {
        id: syncronizer
        onFrameReady: (array) => {
                          textArea.text = array
                      }
    }

    Component.onCompleted: {
        beacon.start(2361);
        syncronizer.bind(2361);
    }

    ColumnLayout {
        Text {
            text: "becon.retranslator " + beacon.retranslator
        }
        Text {
            text: beacon.retranslator === null ? "becon.retranslator.connections: null" : "becon.retranslator.connections " + beacon.retranslator.connections.length
        }
        Rectangle {
            width: 400
            height: 100
            color: "#cccccc"
            TextArea {
                anchors.fill: parent
                id: textArea
            }
        }
        TextField {
            width: 400
            height: 40
            onTextChanged: {
                syncronizer.write(text);
            }
        }
    }
}
