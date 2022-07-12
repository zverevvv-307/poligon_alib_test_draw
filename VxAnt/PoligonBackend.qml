pragma Singleton

import QtQuick
import VxAnt


Item {
    id: root

    property string cfg_root: ""


    readonly property JSONListModel ych_dir: JSONListModel{
        query:"$.items.*"
    }
    readonly property JSONListModel sta_dir: JSONListModel{
        query:"$.items.*"
    }

    YchList{
        path: cfg_root
        onJsonChanged: (txt) => {
            ych_dir.json = txt;
            console.log("*** New Model", txt)
        }
    }

    StaList{
        path: cfg_root
        onJsonChanged: (txt) => {
            sta_dir.json = txt;
            console.log("*** New Model", txt)
        }
    }

    property string selectedYchPath: ""
    onSelectedYchPathChanged: console.log("***", selectedYchPath);

    property string selectedStaPath: ""
    onSelectedStaPathChanged: console.log("***", selectedStaPath);




    Component.onCompleted: {
    }
}
