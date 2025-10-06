import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Controls.Material
import "../MaterialIcons"

TextField {
    id: field

    property alias placeholder: placeholderLabel.text
    property alias icon: iconLabel.text

    leftPadding: iconLabel.visible? iconLabel.width : 10
    bottomPadding: 10
    topPadding: 10
    background: Rectangle {
        color: Qt.darker(Material.background)
        radius: ComponentsGlobals.radius
    }

    Label {
        id: iconLabel
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        leftPadding: 10
        rightPadding: 10
        verticalAlignment: Qt.AlignVCenter
        font.family: MaterialIcons.family
        font.pixelSize: 14
        visible: text.length > 0
    }

    Label {
        id: placeholderLabel
        anchors.fill: parent
        bottomPadding: field.bottomPadding
        topPadding: field.topPadding
        leftPadding: field.leftPadding
        rightPadding: field.rightPadding
        font: field.font
        verticalAlignment: Qt.AlignVCenter
        opacity: 0.5
        visible: field.text.length === 0
    }

    MouseArea {
        id: buttonMouseArea
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.margins: 4
        width: height * 4/3
        hoverEnabled: true
        scale: buttonMouseArea.pressed? 0.9 : 1

        Behavior on scale {
            NumberAnimation { easing.type: Easing.OutCubic; duration: 200 }
        }

        Rectangle {
            radius: ComponentsGlobals.radius * 6 / 8
            color: Material.background
            anchors.fill: parent
            opacity: buttonMouseArea.pressed? 1 : buttonMouseArea.containsMouse? 0.9 : 0.8

            Behavior on opacity {
                NumberAnimation { easing.type: Easing.OutCubic; duration: 200 }
            }
        }

        Label {
            anchors.centerIn: parent
            font.family: MaterialIcons.family
            font.pixelSize: ComponentsGlobals.iconsSize * 0.8
            text: MaterialIcons.mdi_cogs
        }
    }
}
