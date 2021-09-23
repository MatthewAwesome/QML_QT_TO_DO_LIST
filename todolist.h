#ifndef TODOLIST_H
#define TODOLIST_H

#include <QObject>
#include <QVector>

// Define an item structure; 2 fields deep; fields are description and done.

// We u se this below to create a vector of ToDoItems.
struct ToDoItem
{
    bool done;
    QString description;
};

// We define our ToDoList class. It is an instance of QObject that we extend for our purposes.
class ToDoList : public QObject
{
    Q_OBJECT
public:
    explicit ToDoList(QObject *parent = nullptr);
    QVector<ToDoItem> items() const;
    bool setItemAt(int index, const ToDoItem &item);

// We send out these signals:
signals:
    void preItemAppended();
    void postItemAppended();
    void preItemRemoved(int index);
    void postItemRemoved();

// And receive signals in these slots:
public slots:
    void appendItem();
    void removeCompletedItem();
    void exitHandler();

// This is our list vector!
private:
    QVector<ToDoItem> mItems;
};

#endif // TODOLIST_H
