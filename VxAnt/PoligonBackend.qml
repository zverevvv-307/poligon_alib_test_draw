pragma Singleton

import QtQuick
import VxAnt



Item {
    id: root

    property string selectedYchPath: ""
    onSelectedYchPathChanged: console.log("***", selectedYchPath);

    property string selectedStaPath: ""
    onSelectedStaPathChanged: console.log("***", selectedStaPath);


    property string root_dir: ""


    readonly property JSONListModel cfg_dir: JSONListModel{
        query:"$.items.*"
    }
    readonly property JSONListModel sta_dir: JSONListModel{
        query:"$.items.*"
    }

    YchList{
        path: root_dir
        onJsonChanged: (txt) => { cfg_dir.json = txt; }
    }

    StaList{
        path: root_dir
        onJsonChanged: (txt) => { sta_dir.json = txt; }
    }


    Component.onCompleted: {
        root.root_dir = "./ste"
    }
}
