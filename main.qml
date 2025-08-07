import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0
import QtQuick.Controls.Material

import GamePanel 1.0

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Material.theme: Material.Dark
    Material.accent: "#0d80ec"

    GameSourceManager {
        id: sourceManager
        Component.onCompleted: {
            addSource(GameSourceManager.SteamSource, "Steam Test", "/home/bardia/.local/share/Steam")

            const configs = saveConfigs();
            console.debug(configs);
        }
    }

    ScrollView {
        anchors.fill: parent

        ListView {
            id: listv
            model: sourceManager.games
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
