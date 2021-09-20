import QtQuick
import QtQuick.Dialogs

FileDialog {
    title: "Please choose a file"
    nameFilters: [ "JSON files (*.json)", "All files (*)" ]
    fileMode: FileDialog.OpenFile
    Connections {
        target: fW
        function onFileWrited() {
            textFileDirectory.text = "Выбранный файл:  " + fW.getFileName()
        }
        function onFileReaded() {
            textFileDirectory.text = "Выбранный файл:  " + fW.getFileName()
        }
        function onBufferStringChanged() {
            jR.readJson(fW.getBufferString())
        }
        function onParseDataRequest() {
            let jsonKeys = new Array
            for(let i = 0; i < listModel.count; i++) {
                jsonKeys.push(listModel.get(i).jsonKey)
            }
            jR.setKeysToSave(jsonKeys)
            delete jsonKeys
        }
    }
    Connections {
        target: jR
        function onListChanging() {
            listModel.clear()
        }
        function onValueString() {
            listModel.insert(listModel.count, { "jsonKey": jR.getCurrentKey(), "jsonStringValue": jR.getCurrentValue(), "jsonEnum": 1 })
        }
        function onValueBool() {
            var value = jR.getCurrentValue()
            listModel.insert(listModel.count, { "jsonKey": jR.getCurrentKey(), "jsonBoolValue": value, "jsonEnum": 4 })
        }
        function onValueInt() {
            listModel.insert(listModel.count, { "jsonKey": jR.getCurrentKey(), "jsonIntValue": jR.getCurrentValue(), "jsonEnum": 2 })
        }
        function onValueDouble() {
            listModel.insert(listModel.count, { "jsonKey": jR.getCurrentKey(), "jsonDoubleValue": jR.getCurrentValue().toString(), "jsonEnum": 3 })
        }
        function onFinalizeCreation() {
            fW.writeFileData(jR.getJsonDoc())
        }
    }
    onAccepted: {
        if(fileMode == FileDialog.OpenFile){
            fW.setToRead(selectedFile)
        } else {
            fW.setToWrite(selectedFile)
        }
        close()
    }
    onRejected: {
        close()
    }
    Component.onCompleted: visible = false
}
/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
