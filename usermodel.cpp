#include "usermodel.h"

UserModel::UserModel(int nCol, QObject *parent)
    :_nCol(nCol), QAbstractItemModel(parent)
{

}

UserModel::~UserModel()
{
}

void UserModel::deleteList(int row) {
    mDatas.remove(row);
}


QVariant UserModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
           return QVariant();
       if ( role == Qt::DisplayRole)
       {
           if (mDatas.count() == 0)
           {
               return QVariant();
           }
           const QList<QString>& vItem = mDatas[index.row()];
           switch (index.column()){
                   case 0: return vItem[0];
                   case 1: return vItem[1];
                   case 2: return vItem[2];
                   case 3: return vItem[3];
       }


    }
       return QVariant();
}

QModelIndex UserModel::index(int row, int column, const QModelIndex& parent) const{
    Q_UNUSED(parent);
    int rowMax = mDatas.count();
    if(row < rowMax && row >= 0 && column < _nCol && column >= 0)
    {
        return createIndex(row, column);
    }
    return QModelIndex();
}

QModelIndex UserModel::parent(const QModelIndex& index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}

int UserModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return _nCol;
}

int UserModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return mDatas.count();
}

void UserModel::append(const QList<QString>& data)
{
   mDatas.append(data);
}

void UserModel::insert(const QList<QString> &data, int index){
    mDatas.insert(index, data);
}

void UserModel::reset()
{
    QAbstractItemModel::beginResetModel();
    QAbstractItemModel::endResetModel();

}

QString UserModel::getData(int row, int col)
{
    return mDatas[row][col];
}

QList<QString> UserModel::getLine(int row){
    return mDatas[row];
}
