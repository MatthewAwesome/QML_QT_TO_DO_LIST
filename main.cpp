#include <QGuiApplication>
#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QObject>
#include "todolist.h"
#include "todomodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    // Register the model.We just make this available.
    qmlRegisterType<ToDoModel>("ToDo",1,0,"ToDoModel");

    // Register the list. This is NOT a QML component, but a QML variable.
    qmlRegisterUncreatableType<ToDoList>("ToDo",1,0,"ToDoList",QStringLiteral("ToDoList should not be created in QML!"));

    // Both get imported to QML via import ToDo 1.0.

    // Make a ToDoList class here (not in QML...since its not possible...UncreatableType!)
    ToDoList toDoList;

    // Note, this is not to be confused with the qml file. We should change the name of
    // that to eliminate confusion.

    // Instantiate the application engine.
    QQmlApplicationEngine engine;

    // Give the Engine some context. We are linking our application to the toDoList.
    engine.rootContext()->setContextProperty(QStringLiteral("toDoList"),&toDoList);

    // We load up the main application:
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    // We grab the root object from out engine:
    QObject *root = engine.rootObjects()[0];

    // And search it for a particular child:
    QObject *lister = root->findChild<QObject*>("duder");

    // If we find the child, we want to connect a signal to it:
    if (lister){
        qDebug("found to do list");
        // When we initiate the exit sequence of our app, it emits a signal
        // called aboutToQuit(). We connct this to a slot of our and let it go to work.
        QObject::connect(&app,SIGNAL(aboutToQuit()),lister ,SLOT(exitHandler()));
        qDebug("Connected");

    }
    else{
        qDebug("did not find list");
    }


    // And execute the program in earnest:
//    QObject::connect(a, SIGNAL(aboutToQuit()), &server, SLOT(exitHandler()));
    return app.exec();
}
