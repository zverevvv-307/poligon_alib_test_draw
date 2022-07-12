import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    implicitWidth: 300
    implicitHeight: 100

    property alias scale_value: scaleSlider.value
    property alias rotation_value: rotateSlider.value

    anchors.margins: 20

    Rectangle {
        anchors.fill: parent
        color: "lightgrey"
        opacity: 0.5
        radius: 4
    }

    GridLayout {
        anchors.fill: parent
        anchors.margins: 8
        rowSpacing: 2
        columns: 2

        Label {
            text: qsTr("Scale")
        }
        Slider {
            id: scaleSlider
            Layout.fillWidth: true
            value: 1
            from: 0.1
            to: 3
        }
        Label {
            text: qsTr("Rotate")
        }
        Slider {
            id: rotateSlider
            Layout.fillWidth: true
            value: 0
            from: -180
            to: 180
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:100;width:300}
}
##^##*/
