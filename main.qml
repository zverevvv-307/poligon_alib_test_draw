import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import VxAnt

Window {
    id: root
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


    SplitView{
        anchors.fill: parent

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


//    Component.onCompleted: {
//    }
}
