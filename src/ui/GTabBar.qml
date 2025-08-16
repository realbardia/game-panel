import QtQuick 2.15
import QtQuick.Controls.Material

Page {
    width: closedWidth

    property real closedWidth: 64
    property real openedWidth: 200

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

        Behavior on width {
            NumberAnimation { duration: 300; easing.type: Easing.OutCubic }
        }

        Rectangle {
            anchors.fill: parent
            color: Qt.darker(Material.backgroundColor)
        }
    }
}
