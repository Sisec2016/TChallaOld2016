#ifndef UIUTILS_H
#define UIUTILS_H


#include <QString>
#include <QToolTip>
#include <QWidget>
#include <QPoint>
#include <string>
#include <QTimer>
#include <QThread>
#include <QLabel>
#include <QListWidget>
class UIUtils
{
public:
    static void showTip(QWidget &w, const QString &text, const QPoint &pos = QPoint(0, 0), int seconds = 3);
    static void addToListWidget(QListWidget& lw, QWidget& itemWidget);
    static void insertToListWidget(QListWidget& lw, QWidget& itemWidget, int row);
    static void getChildrenSortByX(QWidget& parent, std::vector<QWidget*>& mvcChildren);
    static bool showQuetionBox(const QString& title, const QString& msg);
    static bool showQuetionBox(const QString& title, const QString& msg, const QString& sYes,
                    const QString& sNo);
private:
    /*
     * 构造函数
     *  @return void
     */
    UIUtils();
};

#endif // UIUTILS_H
