import QtQuick
import QtQuick.Controls
import QtQuick.VirtualKeyboard
import QtQuick.Dialogs
import QtQuick.Window
import JR 0.1
import FW 0.1

ApplicationWindow {
    id: root
    width: 480
    height: 640
    visible: true
    title: qsTr("Json Reader")
    FileForm {
        id: fileForm
    }
    JsonReader {
        id: jR
    }
    FileWorker {
        id: fW
    }
    Button {
        id: buttonOpen
        x: 10
        y: parent.height - 60
        width: parent.width / 4
        height: 50
        text: qsTr("OPEN")

        onClicked: {
            fileForm.fileMode = FileDialog.OpenFile
            fileForm.open();
        }
    }
    Button {
        id: buttonSave
        x: parent.width - width - 10
        y: parent.height - 60
        width: parent.width / 4
        height: 50
        text: qsTr("SAVE")
        onClicked: {
            fileForm.fileMode = FileDialog.SaveFile
            fileForm.open()
        }
    }
    ListModel {
        id: listModel
    }
    Component{
        id: rowItem
        Row {
            x: 5
            width: listView.width - 10
            height: 50

            Component.onCompleted: {
                var valueEnum = model.jsonEnum
                var comp
                if(valueEnum === 1){
                    comp = Qt.createComponent("ParamString.qml")
                }
                if(valueEnum === 2){
                    comp = Qt.createComponent("ParamInt.qml")
                }
                if(valueEnum === 3){
                    comp = Qt.createComponent("ParamDouble.qml")
                }
                if(valueEnum === 4){
                    comp = Qt.createComponent("ParamBool.qml")
                }
                comp.createObject(parametre)
            }
            Rectangle {
                width: parent.width / 2
                Text {
                    x: 5
                    y: 10
                    text: qsTr(model.jsonKey)
                    color: "white"
                    font.pixelSize: 24
                    verticalAlignment: Text.AlignBottom
                }
            }
            Rectangle {
                id: parametre
                x: parent.width / 2
                width: parent.width / 2
            }
        }
    }
    ScrollView {
        id: scrollView
        x: 5
        y: 30
        width: root.width - 10
        height: root.height - 110
        anchors { left: parent.left; right: parent.right }
        clip: true
        ListView {
            id: listView
            x: 5
            y: 5
            height: scrollView.height - 10
            width: scrollView - 10
            model: listModel
            clip: true
            delegate: rowItem
        }
    }
    Item {
        x: 5
        y: 5
        width: root.width - 10
        height: 30
        Text {
            id: textFileDirectory
            x: 5
            y: parent.height - height - 8
            width: parent.width - 10
            height: font.pixelSize + 4

            color: "white"
            text: qsTr("Choose valid .json file")
            font.pixelSize: 13
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.Wrap
            font.underline: true
        }
    }
    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: parent.height
        width: parent.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: parent.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
