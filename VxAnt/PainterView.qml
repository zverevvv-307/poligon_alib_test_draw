import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import VxAnt

Item {
    id: root

    property alias sta:  painter.sta
    property alias ych:  painter.ych


    ColumnLayout{
        anchors.fill: parent

        PoligonSimplePainter{
            id: painter
            Layout.fillWidth: true
            Layout.fillHeight: true

            scale: scale.value

            //ych: ych
            //sta: sta
        }

//        Rectangle{
//            Layout.fillWidth: true
//            color: "gray"
//            height: 1
//        }

        Slider{
            id: scale
            Layout.fillWidth: true
            Layout.preferredHeight: 20
            from: 0.01
            to: 2
            value: 1
        }

        Connections{
            target:painter.sta
            function onNeedUpdate(){
                painter.update();
            }
        }

    }

    Timer{
        interval: 3000
        repeat: true
        running: true
        onTriggered: {
            painter.update();
        }
    }
}
