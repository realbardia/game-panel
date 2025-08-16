import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Controls.Material
import QtQuick.Layouts 1.3

import GamePanel 1.0

Page {
    id: page

    property alias games: listv.model

    ColumnLayout {
        anchors.fill: parent

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 64
            // TODO: Move all constant variable to a global qml file

            RowLayout {

                TextField {
                    Layout.preferredWidth: 200
                    placeholderText: qsTr("Search")
                }

                Button {
                    text: "T"
                }
            }
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ListView {
                id: listv
                delegate: ItemDelegate {
                    width: listv.width
                    text: modelData.title
                    icon.source: modelData.icon
                    icon.height: 22
                    icon.width: 22
                }
            }
        }
    }
}
