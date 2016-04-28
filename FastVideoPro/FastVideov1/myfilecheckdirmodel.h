#ifndef MYFILECHECKDIRMODEL_H
#define MYFILECHECKDIRMODEL_H

#include <QDirModel>
//#include <QFileSystemModel>
#include <QTreeView>
#include <QMap>

#include <vector>
#include <string>

class MyFileDirModel : public  QDirModel
{
public:
    MyFileDirModel();
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};


class MyFileCheckDirModel : public MyFileDirModel
{
public:
    MyFileCheckDirModel();

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
 //   int columnCount(const QModelIndex &parent)const;
private:
    bool updateParentCheck(const QModelIndex &index);
    bool updateChildCheck(const QModelIndex &index, const QVariant &value);
private:
        QMap<QPersistentModelIndex, Qt::CheckState> noteCheckedMap;
};

#endif // MYFILECHECKDIRMODEL_H
