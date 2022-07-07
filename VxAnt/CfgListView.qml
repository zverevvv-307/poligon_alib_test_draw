import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import VxAnt


Item {
    id: root

    component RowDelegate: Rectangle {
        id: delegate
        required property var model
        required property int index

        required property string key
        required property string path
        width: view.width
        height: 24


        color: "transparent"
        border.color: "gray"
        radius: 2

        MouseArea {
            anchors.fill: delegate
            onClicked: {
                view.currentIndex = delegate.index
//                PoligonBackend.selectedYchPath = path;
                PoligonBackend.selectedStaPath = path;
            }
        }

        Row{
            anchors.fill: parent
            anchors.margins: 4
            spacing: 20
            //Text { text: key }
            Text { text: path }
        }
    }

    ListView{
        id: view
        spacing: 1
        anchors.fill: parent
//        model:    PoligonBackend.cfg_dir.model
        model:    PoligonBackend.sta_dir.model
        delegate: RowDelegate{}

        highlightMoveDuration: 80
        highlight: Rectangle { color: "#60300030" }
        ScrollBar.vertical: ScrollBar { id: vScrollBar }
    }

}
