// This is our window container. Main window container.
import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ToDoLister {
        anchors.centerIn: parent
        id:lister
        objectName:"lister"
    }
}
