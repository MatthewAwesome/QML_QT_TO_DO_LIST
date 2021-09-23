/* This is our list view. It contains a to-do list,
 each item in said list possessing a TextField description and
 and CheckBox to indicate doneness.
*/

// Import the Qt QML modules:
import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

// Import our module.
import ToDo 1.0

/* What is ToDo and where does it come from?

It is a C++ class and is accessible via QML via the following line in main.cpp:

    qmlRegisterType<ToDoModel>("ToDo",1,0,"ToDoModel");

Which is simply a call to the function qmlRegisterType, a function described as

This template function registers the C++ type in the QML system.
Instances of this type cannot be created from the QML system.

Basically we have a c++ class ToDoModel.

The Qurl associated with our class is ToDo.

The version number is 1.0

And our QML reference is ToDoModel.

Thus, by 'import ToDo 1.0' we can interact with the ToDoModel via QML.

We will also need a reference to our list, which we do as follows:

engine.rootContext()->setContextProperty(QStringLiteral("toDoList"),&toDoList);

*/
ColumnLayout{
    Frame {
        ListView {
            implicitWidth: 250
            implicitHeight: 250
            clip: true
            anchors.fill: parent
            // We link our model here.
            // The model needs reference to a list.
            model: ToDoModel {
                list: toDoList
                objectName:"duder"
            }

            delegate: RowLayout {
                width: parent.width
                CheckBox {
                    checked: model.done
                    onClicked: model.done = checked
                }
                TextField {
                    text: model.description
                    onEditingFinished: model.description = text
                    Layout.fillHeight: true
                }
            }
        }
    }
    RowLayout{
        Button{
            text: qsTr("Add New Item")
            Layout.fillWidth: true
            onClicked: {toDoList.appendItem(); toDoList.exitHandler(); }
        }
        Button{
            text: qsTr("Remove Completed")
            Layout.fillWidth: true
            onClicked: toDoList.removeCompletedItem()
        }
    }
}
