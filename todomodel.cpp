#include "todomodel.h"
#include "todolist.h"

// What is our model, in general? This is our constructor!
ToDoModel::ToDoModel(QObject *parent)
    : QAbstractListModel(parent),
      mList(nullptr)
{
    // do nothing in constructor.
}

// Here we return the number of rows in our list.
// This function operates on itself; very masturbatory.
int ToDoModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.

    // What the above is saying: If this object (ToDoModel) has a parent, we don't count
    // the rows. We want the object we're operating upon to the the root.
    if (parent.isValid() || !mList)
        return 0;

    // Looking through the list to count the items therein..
    return mList->items().size();
}

// This function outputs data associated with our list.
// And does so in a role based manner.
QVariant ToDoModel::data(const QModelIndex &index, int role) const
{
    // A nullptr check: Return an empty object.
    if (!index.isValid() || !mList)
        return QVariant();

    // else we have data.

    //Let's grab the data associated with a particular index:
    const ToDoItem item = mList->items().at(index.row());
    // and use a switch statement to parse the roles.
    // The data outputted depends on the role provided to this function.
    switch (role) {
    case DoneRole:
        return QVariant(item.done);
    case DescriptionRole:
        return QVariant(item.description);
    }
}

// We can either set data successfully or fail to set data. Thus we return a bool.
bool ToDoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // null pointer check:
    if(!mList){
        return false;
    }

    // Grab item at particular index:
    ToDoItem item = mList->items().at(index.row());

    // And update the field(s) corresponding to a particular role.
    switch (role) {
    case DoneRole:
        item.done = value.toBool();
    case DescriptionRole:
        item.description = value.toString();
    }

    // Try to pop the updated item back into the list:
    if (mList->setItemAt(index.row(),item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    // But if we fail, we return false and the data was not set.
    return false;
}

// This is auto-generated:
Qt::ItemFlags ToDoModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

// Here we define how we want roleNames to be implemented:
QHash<int, QByteArray> ToDoModel::roleNames() const
{
    // We have a QHash object called names; these are the role names
    QHash<int,QByteArray> names;
    // What we are doing here is linking an integer role identifier (e.g. 0 or 1) with some
    // descriptive string (e.g. "done" or "description")
    names[DoneRole] = "done";
    names[DescriptionRole] = "description";
    // Once the links have been established. We return the names object.
    return names;
}

// Makeing the private list public:
ToDoList *ToDoModel::list() const
{
    return mList;
}

// Function declaration to set our list:
void ToDoModel::setList(ToDoList *list)
{
    // Notice that we are working with an intance of our ToDoList class.

    //  We are setting the list:
    beginResetModel();

    // If we have a list, we want to detach it from the parent class.
    if (mList){
        mList->disconnect(this);
    }

    // We set mList to list.
    mList = list;

    // Does our list exist?
    if(mList){
        // We wire up some functions here to the existing function.
        // *InsertRows and *RemoveRows are implemented in Qt. We just need to list
        connect(mList,&ToDoList::preItemAppended,this,[=](){
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(),index,index);
        });
        connect(mList,&ToDoList::postItemAppended,this,[=](){
            endInsertRows();
        });
        connect(mList,&ToDoList::preItemRemoved,this,[=](int index){
            beginRemoveRows(QModelIndex(),index,index);
        });
        connect(mList,&ToDoList::postItemRemoved,this,[=](){
            endRemoveRows();
        });
    }
    endResetModel();
}

void ToDoModel::exitHandler(){
    qDebug("Exiting...");
}
