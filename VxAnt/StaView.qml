import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import VxAnt

Pane {
    id: root
    padding: 2

    property alias sta_path:  sta.path
    property alias name:  sta.name
    property alias enable_autoupdate:  timer.running

    SmartSta {  id: sta }

    ColumnLayout{
        anchors.fill: parent

        PoligonSimplePainter{
            id: painter
            Layout.fillWidth: true
            Layout.fillHeight: true
            scale: scale.value
            sta: sta
        }

        Slider{
            id: scale
            Layout.fillWidth: true
            Layout.preferredHeight: 20
            from: 0.01
            to: 2
            value: 1
        }

        Connections{
            target: sta
            function onNeedUpdate(){
                painter.update();
            }
        }
    }

    Timer{
        id: timer
        interval: 3000
        repeat:   true
        running:  false
        onTriggered: painter.update();
    }
}
