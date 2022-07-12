import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import VxAnt

Pane {
    id: root
    padding: 2

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
        radius: 4

        MouseArea {
            anchors.fill: delegate
            onClicked: {
                view.currentIndex = delegate.index
                //PoligonBackend.selectedStaPath = path;
                //PoligonBackend.selectedYchPath = path;
            }
        }

        Row{
            anchors.fill: parent
            anchors.margins: 4
            spacing: 20
            Text { text: key }
            //            Text { text: path }
        }
    }

    ListView{
        id: view
        anchors.fill: parent

        spacing: 1
        clip: true
        //model:    PoligonBackend.ych_dir.model
        model:    PoligonBackend.sta_dir.model
        delegate: RowDelegate{}

        highlightMoveDuration: 80
        highlight: Rectangle { color: "gold"; radius: 4 }
        ScrollBar.vertical: ScrollBar { id: vScrollBar }
    }
}
