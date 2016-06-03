#include "tooldlg.h"

#include <QStandardItemModel>
#include <QMessageBox>
#include <QMenu>
#include <QMouseEvent>
#include <Windows.h>
#include <tchar.h>
#include <shellapi.h>
#include <ProductDialog.h>
tooldlg::tooldlg(QWidget *parent)
: MyBaseDialog(parent)
{
    ui.setupUi(this);
    connect(ui.hikBtn, SIGNAL(clicked()), this, SLOT(onHikToolClicked()));
    connect(ui.dahuaBtn, SIGNAL(clicked()), this, SLOT(onDahuaToolClicked()));
    connect(ui.browserBtn, SIGNAL(clicked()), this, SLOT(onbrowserBtnClicked()));
    connect(ui.videoPlayBtn, SIGNAL(clicked()), this, SLOT(onvideoPlayBtnClicked()));
    connect(ui.product_setBtn, SIGNAL(clicked()), this, SLOT(onproduct_setBtnClicked()));

}

tooldlg::~tooldlg()
{

}

void tooldlg::onHikToolClicked()
{
    ShellExecute(GetDesktopWindow(), _T("open"), _T("hikPlay\\APT-LPB.exe"), NULL, NULL, SW_SHOWNORMAL);
}

void tooldlg::onDahuaToolClicked()
{
    ShellExecute(GetDesktopWindow(), _T("open"), _T("DaHuaTool\\DiskCopy.exe"), NULL, NULL, SW_SHOWNORMAL);
}

void tooldlg::onbrowserBtnClicked()
{
    ShellExecute(GetDesktopWindow(), _T("open"), _T("C:\\Program Files\\Internet Explorer\\iexplore.exe"), NULL, NULL, SW_SHOWNORMAL);
}

void tooldlg::onvideoPlayBtnClicked()
{
    ShellExecute(GetDesktopWindow(), _T("open"), _T("C:\\Program Files (x86)\\OVPlayer\\OVPlayer.exe"), NULL, NULL, SW_SHOWNORMAL);
}

void tooldlg::onproduct_setBtnClicked()
{
    ProductDialog dlg(this);
    dlg.exec();
    //ShellExecute(GetDesktopWindow(), _T("open"), _T("DaHuaTool\\DiskCopy.exe"), NULL, NULL, SW_SHOWNORMAL);
}
