import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material

import "components"
import "MaterialIcons"

Page {
    id: tabBar
    width: closedWidth

    property real closedWidth: 64
    property real openedWidth: 200

    readonly property real ratio: (marea.width - (closedWidth - 1)) / (openedWidth - (closedWidth - 1))

    Rectangle {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        color: Material.foreground
        width: 1
        opacity: 0.1
    }

    MouseArea {
        id: marea
        hoverEnabled: true
        height: parent.height
        width: containsMouse? openedWidth : closedWidth - 1
        clip: true

        Behavior on width {
            NumberAnimation { duration: 300; easing.type: Easing.OutCubic }
        }

        Rectangle {
            anchors.fill: parent
            color: Qt.darker(Material.backgroundColor)
        }

        ListView {
            id: itemsListView
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: openedWidth
            model: 10
            delegate: GItemDelegate {
                width: itemsListView.width
                onClicked: itemsListView.currentIndex = index

                property color foregroundColors: itemsListView.currentIndex == index? Material.accentColor : tabBar.Material.foreground
                Material.foreground: foregroundColors

                Behavior on foregroundColors {
                    ColorAnimation { duration: 300; easing.type: Easing.OutCubic }
                }

                RowLayout {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 0

                    GMaterialIcon {
                        Layout.alignment: Qt.AlignVCenter
                        Layout.preferredWidth: closedWidth
                        text: MaterialIcons.mdi_controller_classic_outline
                    }

                    GLabel {
                        Layout.alignment: Qt.AlignVCenter
                        Layout.fillWidth: true
                        text: qsTr("Item %1").arg(index)
                    }
                }
            }

            highlight: Item {
                Rectangle {
                    anchors.left: parent.left
                    anchors.leftMargin: marea.width - width - height
                    height: 3
                    width: parent.height
                    rotation: -90
                    transformOrigin: Item.TopRight
                    opacity: 0.8
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: "transparent" }
                        GradientStop { position: 1.0; color: tabBar.Material.accentColor }
                    }
                }
            }
            highlightMoveDuration: 300
        }
    }
}
