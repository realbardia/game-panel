import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0
import QtQuick.Controls.Material

ApplicationWindow {
    width: 1024
    height: 600
    visible: true
    title: qsTr("Hello World")

    Material.theme: Material.Dark
    Material.accent: "#0d80ec"

    MainPage {
        anchors.fill: parent
    }
}
