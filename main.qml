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


    header: RowLayout{
        width: appWindow.width
        TabBar {
            id: tabs
            Layout.preferredWidth: 100
            TabButton {
                text: qsTr("Main")
                background: Rectangle { color: tabs.currentIndex === 0 ? "green" : "gray" }
                onClicked: {
                }
            }
        }
        Text {
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            text: ychPage.title + "  %  " + staPage.title
        }
        Text {
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            text: "# "
            //onClicked: folderDialog.open()
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
    }

//    FolderDialog{ //suka +widget and +QApplication needed
//        id: folderDialog
//    }


    Component.onCompleted: {
//        appWindow.cfg_root = "./ste"
    }



}
