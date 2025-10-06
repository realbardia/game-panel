import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Controls.Material
import QtQuick.Layouts 1.3

import GamePanel 1.0

import "components"
import "MaterialIcons"

Page {
    id: page

    property alias games: listv.model

    ColumnLayout {
        anchors.fill: parent

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 60
            // TODO: Move all constant variable to a global qml file

            RowLayout {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 10
                spacing: 0

                GTextField {
                    Layout.preferredWidth: 200
                    placeholder: qsTr("Search")
                    icon: MaterialIcons.mdi_magnify
                }

                Item {
                    Layout.preferredHeight: 1
                    Layout.fillWidth: true
                }

                GIconOnlyButton {
                    text: MaterialIcons.mdi_heart_outline
                }

                GIconOnlyButton {
                    text: MaterialIcons.mdi_basket
                }

                GProfileButton {
                    materialIcon: MaterialIcons.mdi_account
                    username: "Bardia"
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
