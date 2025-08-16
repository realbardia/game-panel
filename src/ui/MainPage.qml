import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Controls.Material

import GamePanel 1.0

Page {

    GameSourceManager {
        id: sourceManager
        storeFileName: "source-manager"
        Component.onCompleted: {
            // TODO: make this dynamic
            addSource(GameSourceManager.SteamSource, "Steam Test", "/home/bardia/.local/share/Steam")
            saveConfigs();
        }
    }

    GTabBar {
        id: tabBar
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        z: 1000
    }

    HomePage {
        id: home
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: tabBar.right
        anchors.right: parent.right
        games: sourceManager.games
    }
}
