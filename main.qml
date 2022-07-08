import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.settings 1.0

import VxAnt

Window {
    id: appWindow
    width: 620
    height: 480
    visible: true
    title: qsTr("Hello Poligon")

    SmartSta {
        id: sta
        //        path: "./ste/sta/holoni.ste"
        path: PoligonBackend.selectedStaPath
    }

    //    SmartYch {
    //        id: ych
    //        path: PoligonBackend.selectedYchPath
    //    }

    Pane{
        anchors.fill: parent
        padding: 4

        SplitView{
            anchors.fill: parent
            padding: 0

            CfgListView{
                SplitView.minimumWidth: 50
                SplitView.preferredWidth: 150
                SplitView.maximumWidth: 300
            }

            PainterView {
                SplitView.fillHeight: true
                SplitView.fillWidth: true
                sta: sta
            }
        }
    }


    Settings {
        id: settings
        property alias x: appWindow.x
        property alias y: appWindow.y
        property alias width: appWindow.width
        property alias height: appWindow.height
    }
}
