import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import VxAnt

Pane {
    id: root
    padding: 2

    property alias ych_path:  ych.path
    property alias name:  ych.name
    property alias enable_autoupdate:  timer.running

    SmartYch {  id: ych }

    ColumnLayout{
        anchors.fill: parent

        Item{
            Layout.fillWidth: true
            Layout.fillHeight: true
            PoligonSimplePainter{
                id: painter
                anchors.fill: parent
                scale: control.scale_value
                rotation: control.rotation_value
                ych: ych

            }
            RenderControlsForm{
                id: control
                anchors{
                    right: parent.right
                    bottom: parent.bottom
                }
            }
        }

        Connections{
            target: ych
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
