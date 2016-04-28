#ifndef SOURCEFILEWIDGET_H
#define SOURCEFILEWIDGET_H

#include <QWidget>
#include <vector>

#include "myfilecheckdirmodel.h"

namespace Ui {
    class SourcefileWidget;
}

class SourcefileWidget : public QWidget {
    Q_OBJECT
public:
    SourcefileWidget(QWidget *parent = 0);
    ~SourcefileWidget();
public:
    void setFileCheckedModel(bool bCheck=true);
    void setMyRootPath(QString pathName);
    std::vector<std::string>& getCheckedFile();
     bool getCheckedFile1(std::vector<std::string> &fileVector, std::string &strPathRoot);
private:
    void readCheckFile(QModelIndex &parentIndex);
    void readCheck(QModelIndex &parentIndex, std::vector<QString>& vcIndexs);
    bool deletePath(const QModelIndex &parentIndex);
protected slots:
    void onFilePlayBtn();
    void onFileDelBtn();
    void onCreateDirectoryBtn();
protected:
    void changeEvent(QEvent *e);

private:
    Ui::SourcefileWidget *ui;
private:
	QDirModel *m_myModel;
    std::vector<std::string> m_fileVector;
	std::string m_strPathRoot;
};

#endif // SOURCEFILEWIDGET_H
