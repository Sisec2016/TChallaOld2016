#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logManagerDlg.h"

#include <qdialog.h>


namespace Ui {
    class MainWindow;
}


class MainDialog;
class MainWindow : public QDialog {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void setProductUi();
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    //去掉标题栏，能拖动窗口移动
	
protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
	void showEvent(QShowEvent* event);
private slots:
    void onMinClicked();
	void onCloseClicked();
	void onAboutClicked();
    void onHelpClicked();
    void onUpdateClicked();
    void onDiskBtnclicked();
    void onShareBtnclicked();
    void onFTPBtnclicked();
	void onToolBtnclicked();
    void onVideoBtnclicked();
	void onScreenBtnclicked();
    void onFileBtnclicked();
    void onNetBtnclicked();
    void onLogBtnclicked();

private:
    void createAllDialog();

private:
    QPoint mLastMousePosition;
    bool mMoving;
    MainDialog* mpVideoDownloadDlg;
//
};

#endif // MAINWINDOW_H
