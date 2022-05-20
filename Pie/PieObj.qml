import Pie
import QtQuick

Item {
    width: 800; height: 800

    PieChart {
        id: aPieChart
        anchors.fill: parent
        name: "./ste/sta/holoni.ste"
        color: "red"
    }

    Text {
        anchors {
            top: parent.top
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }
        text: aPieChart.name
    }
}
