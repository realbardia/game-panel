import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Controls.Material

RoundButton {
    radius: ComponentsGlobals.radius
    Material.elevation: 0
    Material.background: Qt.darker(parent.Material.background)
}
