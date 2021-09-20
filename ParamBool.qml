import QtQuick
import QtQuick.Controls

CheckBox {
    id: control
    property bool storedBool
    checkState: Qt.Unchecked
    Component.onCompleted: {
        (model.jsonBoolValue == "true") ? checkState = Qt.Checked : checkState = Qt.Unchecked
        storedBool = isTrue()
    }
    onCheckStateChanged: {
        storedBool = isTrue()
    }
    function sendValue() {
        jR.addValue(model.jsonKey, storedBool)
    }
    function isTrue(){
        if(checkState == Qt.Unchecked){
            return false
        } else {
            return true
        }
    }
    Connections {
        target: jR
        function onThrowToHeap() {
            control.sendValue()
        }
    }
}
