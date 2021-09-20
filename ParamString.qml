import QtQuick
import QtQuick.Controls

TextField {
    id: control
    property string storedString
    text: model.jsonStringValue
    placeholderText: "string"
    color: "white"
    font.pixelSize: 24
    function sendValue() {
        jR.addValue(model.jsonKey, text.toString())
    }
    onTextChanged: {
        storedString = text.toString()
    }
    Connections {
        target: jR
        function onThrowToHeap() {
            control.sendValue()
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
