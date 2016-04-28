#include "uiutils.h"
#include "qgiflabel.h"
#include "screenadaption.h"
#include <QListWidget>
#include <QMessageBox>
#include "messageboxdlg.h"

UIUtils::UIUtils()
{
}



void UIUtils::showTip(QWidget &w, const QString &text, const QPoint &pos, int seconds)
{
    QLabel* l = new QLabel(text, nullptr, Qt::FramelessWindowHint | Qt::ToolTip);
    l->setFixedWidth((int)(150 * ScreenAdaption::instance().getWidthFactor()));
    l->setWordWrap(true);
    l->setAlignment(Qt::AlignHCenter);
    QString s("border-image: url(:/png/input-move.png);"
            "font-size:%1px;"
            "color:black;"
            "font:Microsoft Yahei bold;");
    l->setStyleSheet(s.arg((int)(18 * ScreenAdaption::instance().getWidthFactor())));

    l->move(w.mapToGlobal(pos));

    l->show();
    QTimer::singleShot(seconds * 1000, l, SLOT(deleteLater()));
}

void UIUtils::addToListWidget(QListWidget& lw, QWidget& itemWidget)
{
    lw.addItem(QString::fromLocal8Bit(""));
    lw.item(lw.count() - 1)->setSizeHint(itemWidget.size());
    lw.setItemWidget(lw.item(lw.count() - 1), &itemWidget);
}

void UIUtils::insertToListWidget(QListWidget& lw, QWidget& itemWidget, int row)
{
    QListWidgetItem *item = new QListWidgetItem();
    lw.insertItem(row, item);
    lw.setItemWidget(item, &itemWidget);
}

void UIUtils::getChildrenSortByX(QWidget& parent, std::vector<QWidget*>& mvcChildren)
{
    mvcChildren.clear();
    for (int i = 0; i < parent.children().size(); i++)
    {
        if (nullptr != parent.children().at(i)
                && parent.children().at(i)->isWidgetType())
        {
            mvcChildren.push_back((QWidget*)(parent.children().at(i)));
        }
    }

    std::sort(mvcChildren.begin(), mvcChildren.end(),
              [](QWidget* left, QWidget* right)
    {
        return left->geometry().x() > right->geometry().x();
    });
}

bool UIUtils::showQuetionBox(const QString& title, const QString& msg, const QString& sYes,
    const QString& sNo){

    MessageBoxDlg msgDlg(msg, MsgButton::Yes, MsgButton::No, title);
    msgDlg.setBtnText(sYes, sNo);
    msgDlg.exec();
    
    return msgDlg.isConfirm() == MsgButton::Yes;
}

bool UIUtils::showQuetionBox(const QString& title, const QString& msg){
    return showQuetionBox(title, msg, QString::fromLocal8Bit("ÊÇ"), QString::fromLocal8Bit("·ñ"));
}