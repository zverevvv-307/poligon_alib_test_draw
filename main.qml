import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import VxAnt
import Pie

Window {
    id: root
    width: 620
    height: 480
    visible: true
    title: qsTr("Hello Poligon")

    SmartSta {
        id: sta
        path: "./ste/sta/holoni.ste"/*PoligonBackend.selectedStaPath*/
    }

    SmartYch {
        id: ych
        path: PoligonBackend.selectedYchPath
    }

    PoligonSimplePainter{
        id: painter
        anchors.fill: parent
        //ych: ych
        sta: sta

        Timer{
          interval: 3000
          repeat: true
          running: true
          onTriggered: {
              painter.update();
          }
        }
    }


    component RowDelegate: Rectangle {
        id: delegate
        required property var model
        required property int index

        required property string key
        required property string path
        width: ychsView.width
        height: 20

        color: "transparent"
        border.color: "gray"
        radius: 4

        MouseArea {
            anchors.fill: delegate
            onClicked: {
                ychsView.currentIndex = delegate.index
//                PoligonBackend.selectedYchPath = path;
                PoligonBackend.selectedStaPath = path;
            }
        }

        Row{
            anchors.fill: parent
            spacing: 20
            Text { text: key }
            Text { text: path }
        }
    }

    ListView{
        id: ychsView
        width: 500
        height: 300
        anchors.centerIn: parent
//        model:    PoligonBackend.cfg_dir.model
        model:    PoligonBackend.sta_dir.model
        delegate: RowDelegate{}

        highlightMoveDuration: 80
        highlight: Rectangle { color: "#60300030" }
        ScrollBar.vertical: ScrollBar { id: vScrollBar }
    }

    PieObj{
        anchors.fill: parent
    }

    Component.onCompleted: {
    }
}
