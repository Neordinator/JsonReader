import QtQuick
import QtQuick.Controls

TextField {
    id: control
    property int storedInt
    color: "white"
    text: model.jsonIntValue.toString()
    placeholderText: "integer"
    font.pixelSize: 24
    validator: IntValidator{
        top: 2147483647
        bottom: -2147483647
    }
    Component.onCompleted: storedInt = parseInt(model.jsonIntValue)
    onTextEdited: {
        storedInt = parseInt(text.toString())
    }
    function sendValue() {
        jR.addValue(model.jsonKey, storedInt)
    }
    Connections {
        target: jR
        function onThrowToHeap() {
            control.sendValue()
        }
    }
}
