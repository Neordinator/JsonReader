import QtQuick
import QtQuick.Controls

TextField {
    id: control
    property double storedDouble
    color: "white"
    text: model.jsonDoubleValue
    placeholderText: "real"
    font.pixelSize: 24
    validator: RegularExpressionValidator { regularExpression: /^-?\d*\.{0,1}\d+$/ }
    Component.onCompleted: storedDouble = storeDouble(model.jsonDoubleValue)
    onTextEdited: {
        storedDouble = storeDouble(text.toString())
    }
    function storeDouble(stringToDouble){
        return parseFloat(stringToDouble)
    }
    function sendValue() {
        jR.addValue(model.jsonKey, storedDouble)
    }
    Connections {
        target: jR
        function onThrowToHeap() {
            control.sendValue()
        }
    }
}
