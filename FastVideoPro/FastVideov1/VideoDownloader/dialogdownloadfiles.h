#ifndef DIALOGDOWNLOADFILES_H
#define DIALOGDOWNLOADFILES_H

#include "noflamedlg.h"
#include "videoserver.h"
#include "noflamedlg.h"
namespace Ui {
class DialogDownloadFiles;
}

class DialogDownloadFiles : public NoFlameDlg
{
    Q_OBJECT

public:
    explicit DialogDownloadFiles(std::shared_ptr<videoserver> pServer, std::vector<RecordFile>& files, QWidget *parent = 0);
    ~DialogDownloadFiles();

    void getSelectedFiles(std::vector<RecordFile*>& files);


protected:
    void customEvent(QEvent* event);
private slots:
    void on_closeButton_clicked();

    void on_pushButtonConnect_clicked();

    void on_checkBoxAll_toggled(bool checked);

private:
    Ui::DialogDownloadFiles *ui;
    std::vector<RecordFile>& mvcFiles;
    std::shared_ptr<videoserver> mpServer;
    int mIndex;
};

#endif // DIALOGDOWNLOADFILES_H
