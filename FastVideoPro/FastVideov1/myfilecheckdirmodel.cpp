#include "myfilecheckdirmodel.h"


MyFileDirModel::MyFileDirModel()
{
}
//改列表名为中文
QVariant MyFileDirModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal)
    {
        switch(section)
        {
        case 0:
            return QStringLiteral("名称");
        case 1:
            return QStringLiteral("大小");
        case 2:
            return QStringLiteral("文件类型");
        case 3:
            return QStringLiteral("修改时间");
        case 4:
            return QStringLiteral("修改时间");
        }
    }

     return QAbstractItemModel::headerData(section, orientation, role);
}

//
MyFileCheckDirModel::MyFileCheckDirModel()
{
}

Qt::ItemFlags MyFileCheckDirModel::flags(const QModelIndex &index) const
{
    int column = index.column();
    if(0 == column)
    {
       return QDirModel::flags(index) | Qt::ItemIsUserCheckable;
    }
    else
    {
        return QDirModel::flags(index);
    }
}
/*
int MyFileCheckDirModel::columnCount(const QModelIndex &parent)const
{
    return QDirModel::columnCount(parent);
   // return 5;

}
*/
QVariant MyFileCheckDirModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::CheckStateRole)
    {
         int column = index.column();
         if(0 == column)
         {
            return (Qt::CheckState)noteCheckedMap[index];
         }

         return QDirModel::data(index, role);

    }
	/*else if (role == Qt::SizeHintRole)
	{
		//return QDirModel::data(index, role);
		return QSize(100, 35);
	}*/
    else
    {
        return QDirModel::data(index, role);
    }
}
bool MyFileCheckDirModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::CheckStateRole)
    {
      // qDebug()<<" setData CheckStateRole"<<value.toInt();
            if(0 == index.column())
            {
              if(hasChildren(index) == true)
              {
                  updateChildCheck(index, value);
              }

              noteCheckedMap[index] = (Qt::CheckState)value.toInt();
              emit dataChanged(index, index);
              //当前状态更新后才更新父节点
              if(index.parent().isValid())
              {
                  updateParentCheck(index);
              }
              return true;

        }
    }

    return QDirModel::setData(index, value, role);
}

bool MyFileCheckDirModel::updateParentCheck(const QModelIndex &index)
{
	if (index.parent().isValid())
	{
		QModelIndex parentIndex = index.parent();
		//QPersistentModelIndex parentIndex = QPersistentModelIndex(index.parent());

        int i;
        int childrenCount = rowCount(parentIndex);
        QModelIndex child;
        Qt::CheckState state;
        for(i=0; i<childrenCount; i++)
        {
            child = QDirModel::index(i, 0, parentIndex);
            if(0 == child.column())
            {
                if(i==0)
                {
                   state = (Qt::CheckState)child.data(Qt::CheckStateRole).toInt();
                   continue;
                }
                Qt::CheckState stateTmp =(Qt::CheckState) child.data(Qt::CheckStateRole).toInt();
                if(stateTmp!=state)
                {
                    state = Qt::PartiallyChecked;
                     break;
                }

            }
        }
        noteCheckedMap[parentIndex] = state;
        QDirModel::setData(parentIndex, state, Qt::CheckStateRole);
        emit dataChanged(parentIndex, parentIndex);
        updateParentCheck(parentIndex);
       return true;
    }
    return false;
}

bool MyFileCheckDirModel::updateChildCheck(const QModelIndex &index, const QVariant &value)
{
    if(hasChildren(index))
    {
        int i;
        int childrenCount = rowCount(index);
        QModelIndex child;
        for(i=0; i<childrenCount; i++)
        {
            child = QDirModel::index(i, 0, index);
            if(0 == child.column())
            {
                noteCheckedMap[child] = (Qt::CheckState)value.toInt();
                emit dataChanged(child, child);
                updateChildCheck(child,value);
            }
        }
       return true;
    }
    return false;
}
