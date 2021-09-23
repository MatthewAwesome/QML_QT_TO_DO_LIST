#ifndef TODOMODEL_H
#define TODOMODEL_H

#include <QAbstractListModel>

// We will use ToDoList here in the model.
class ToDoList;

// This class was created using Qt Item Model Class Generator:
class ToDoModel : public QAbstractListModel
{
    Q_OBJECT

    // To allow our model to interact with our list, of type ToDoList class,
    // we define a Q_PROPERTY.

    // When, via QML, we seek to access (i.e. READ) the list, we cal the list() function.
    // When we seek to update the list, we call the setList function.
    // Both list and setList belong to the model class.

    Q_PROPERTY(ToDoList *list READ list WRITE setList)

// Laying out the members of our ToDoModel class:
public:
    // Define a constructor:
    explicit ToDoModel(QObject *parent = nullptr);

    // And an enumerator to work with our ListModel in QML.
    // This essentially lays out a list of roles.
    enum{
        DoneRole = Qt::UserRole,
        DescriptionRole
    };

    // This is created automatically via the Generator :
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // As is this.
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:(also auto-generated)
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    // My guess is that this is triggered everytime we we do something,
    // and this is where the roles come in.

    // Likewise auto-generated.
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // We override the roleNames function belonging to the base class,
    // QAbstractItemModel. QT implements some out of the box roles, but we want more. So here we are.

    // Oh this is virtual. Virtual functions are member functions whose behavior can be overridden in derived classes!
    virtual QHash<int,QByteArray> roleNames() const override;

    // The function is used to grab the list associated with this model.
    ToDoList *list() const;

    // This function is used to update the list associated with this model.
    void setList(ToDoList *list);

public slots:
    void exitHandler();

private:
    // We add another field, mList. This one is private an is used to update list.
    ToDoList *mList;
};

#endif // TODOMODEL_H
