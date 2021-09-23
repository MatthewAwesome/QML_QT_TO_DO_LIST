/*
 *This is a to-do list class.
 *
 *
 *
 */
#include "todolist.h"

// Consructor
ToDoList::ToDoList(QObject *parent) : QObject(parent)
{
    // Add a couple itmems to our list.
    mItems.append({true,QStringLiteral("Wash the Dog")});
    mItems.append({true,QStringLiteral("Milk to cow")});
}

// We return of vector of items:
QVector<ToDoItem> ToDoList::items() const
{
    return mItems;
}

// We set an item at a particular index:
bool ToDoList::setItemAt(int index, const ToDoItem &item)
{
    // If we can't access the item, return false and exit the function.
    if(index < 0 || index >= mItems.size()){
        return false;
    }
    // If we can access the item at 'index', we do so.
    const ToDoItem &oldItem = mItems.at(index);
    if(item.done == oldItem.done && item.description == oldItem.description){
        return false;
    }
    mItems[index] = item;
    return true;
}

// We are adding an item to our list:
void ToDoList::appendItem()
{
    // Begin appending item:
    emit preItemAppended();
    // Instantiate an item:
    ToDoItem item;
    // Define it's done field as false.
    item.done = false;
    // And tack it on the list. (QVector as a method called append)
    mItems.append(item);
    // And emit the signal saying that we are done here.
    emit postItemAppended();
}

// Removing completed items:
void ToDoList::removeCompletedItem()
{
    // Look through the items and remove those checked as done:
    for(int i = 0; i<mItems.size();){
        if(mItems.at(i).done){
            emit preItemRemoved(i);
            mItems.removeAt(i);
            emit postItemRemoved();
        }
        else{
            ++i;
        }
    }
}

void ToDoList::exitHandler(){
    qDebug("In exit handler");
}
