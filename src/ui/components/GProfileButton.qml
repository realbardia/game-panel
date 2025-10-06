import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material

GButton {
    implicitWidth: Math.max(130, rowItem.width + rowItem.x*2)

    property alias materialIcon: iconLabel.text
    property alias username: username.text
    property alias viewProfileText: profileBtn.text

    RowLayout {
        id: rowItem
        x: 10
        anchors.verticalCenter: parent.verticalCenter
        spacing: 2

        GMaterialIcon {
            id: iconLabel
            Layout.preferredHeight: 26
            Layout.preferredWidth: 26
        }

        ColumnLayout {
            spacing: 0

            GLabel {
                id: username
                font.pixelSize: 10
            }

            GLabel {
                id: profileBtn
                font.pixelSize: 8
                color: Material.accentColor
                text: qsTr("View profile")
            }
        }
    }
}
