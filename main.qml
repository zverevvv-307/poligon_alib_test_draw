import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.settings
import Qt.labs.platform

import VxAnt

ApplicationWindow {
    id: appWindow
    width: 620
    height: 480
    visible: true
    title: qsTr("Hello Poligon")


    property string cfg_root
    onCfg_rootChanged: {
        PoligonBackend.cfg_root = cfg_root
        console.log("*** Root Dir:", cfg_root);
    }

    Menu {
        id: fileMenu
        title: qsTr("&File")
        MenuItem {
            text: qsTr("&Open Root")
            icon.name: "document-open"
            onTriggered: folderDialog.open()
        }

        Menu {
            id: recentFilesSubMenu
            title: qsTr("Recent Files")
            enabled: recentFilesInstantiator.count > 0

            Instantiator {
                id: recentFilesInstantiator
                model: settings.recentFiles
                delegate: MenuItem {
                    text: model.modelData
                    onTriggered: cfg_root = model.modelData
                }

                onObjectAdded: recentFilesSubMenu.insertItem(index, object)
                onObjectRemoved: recentFilesSubMenu.removeItem(object)
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Clear Recent Files")
                onTriggered: settings.clearRecentFiles()
            }
        }
    }

    header: RowLayout{
        width: appWindow.width
        TabBar {
            id: tabs
            Layout.preferredWidth: 100
            TabButton {
                text: qsTr("General")
                background: Rectangle { color: tabs.currentIndex === 0 ? "green" : "gray" }
                onClicked: {
                }
            }
            TabButton {
                text: qsTr("Tools")
                background: Rectangle { color: tabs.currentIndex === 1 ? "green" : "gray" }
                onClicked: {
                }
            }
        }
        Text {
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            text: ychPage.title + "  %  " + staPage.title
        }
        Button {
            Layout.preferredHeight: 20
            Layout.preferredWidth:  20
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            text: "#"
            onClicked: fileMenu.open()
        }
    }

    ColumnLayout{
        anchors.fill: parent
        spacing: 0
        SwipeView {
            id: view
            Layout.fillWidth: true
            Layout.fillHeight: true

            currentIndex: indicator.currentIndex
            PageYch {
                id: ychPage
                path_model: PoligonBackend.ych_dir.model
            }
            PageSta {
                id: staPage
                path_model: PoligonBackend.sta_dir.model
            }
            //CfgListView{}
        }


        PageIndicator {
            id: indicator
            Layout.preferredHeight: 16
            Layout.alignment: Qt.AlignCenter

            count: view.count
            currentIndex: view.currentIndex
            interactive: true
        }
    }


    Settings {
        id: settings
        property alias x: appWindow.x
        property alias y: appWindow.y
        property alias width: appWindow.width
        property alias height: appWindow.height
        property alias cfg_root: appWindow.cfg_root
        property var   recentFiles: ["./"]

        function clearRecentFiles() { recentFiles.clear(); }
        function addRecentFiles(path) {
            recentFiles.push(path);
            if(recentFiles.length>7)
                recentFiles.pop();
        }
    }

    FolderDialog {
        id: folderDialog
        onAccepted:{
           cfg_root = stripFileUrlToPath(folder);
           settings.addRecentFiles(cfg_root);
        }
        function stripFileUrlToPath(url) {
            var urlString = url.toString();
            //    path = path.replace(/^(file:\/{2})|(qrc:\/{2})|(http:\/{2})/,""); not portable
            var s
            if (urlString.startsWith("file:///")) {
                var k = urlString.charAt(9) === ':' ? 8 : 7
                s = urlString.substring(k)
            } else {
                s = urlString
            }
            return decodeURIComponent(s);//unescape html codes like '%23' for '#'
        }
    }


    Component.onCompleted: {
    }

}
