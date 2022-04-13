#ifndef USERMODEL_H
#define USERMODEL_H
#include <QAbstractItemModel>


class UserModel : public QAbstractItemModel
{
  Q_OBJECT

public:
    UserModel(int nCol, QObject *parent = Q_NULLPTR);
    ~UserModel();

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;

    QModelIndex parent(const QModelIndex& index) const;

    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;

    void append(const QList<QString>& data);

    void insert(const QList<QString>& data, int index);

    void deleteList(int row);

    void reset();

    QString getData(int row, int col);
    QList<QString> getLine(int row);
private:

    int _nCol;
    QVector<QList<QString>> mDatas;

};
#endif // USERMODEL_H
