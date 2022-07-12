import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import VxAnt

Page {
    id: root
    padding: 2

    title: staView.name

    property alias path_model:  txtView.model
    property string selected_key: ""
    property string selected_path: ""

    component TxtDelegate: Rectangle {
        id: delegate
        required property var model
        required property int index

        required property string key
        required property string path

        height: txtView.height
        width: txt.implicitWidth+8
        color: mouseArea.containsMouse ? "yellow" : "#808c8c8c"

        MouseArea {
            id: mouseArea
            hoverEnabled: true
            anchors.fill: delegate
            onClicked: {
                txtView.currentIndex = delegate.index
                root.selected_path = path
                root.selected_key = key
                PoligonBackend.selectedStaPath = path;
            }
        }

        Text {
            id: txt
            anchors.centerIn: parent
            text: key
        }
        ToolTip.delay: 300
        ToolTip.timeout: 3000
        ToolTip.text: path
        ToolTip.visible: mouseArea.containsMouse
    }


    StaView {
        id: staView
        anchors.fill: parent
        sta_path: root.selected_path
    }

    ListView{
            id: txtView
            height: 20
            anchors {
                left: staView.left
                right: staView.right
                top: staView.top
            }
            orientation: ListView.Horizontal

            spacing: 1
            clip: true
            delegate: TxtDelegate{ }
            highlightMoveDuration: 80
            highlight: Rectangle { color: "green"; }
            //ScrollBar.horizontal: ScrollBar { id: scrollBar }
        }
}
