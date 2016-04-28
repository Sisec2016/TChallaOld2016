#include "downloadtasktreewidget.h"
#include <qstandarditemmodel.h>
#include "channelwidget.h"
#include "uiutils.h"
#include "downloadwidget.h"
#include "taskwidget.h"
#include <QMessageBox>
#include <QTreeWidget>
#include <QThread>
#include <QApplication>


DownloadTaskTreeWidget::DownloadTaskTreeWidget( QWidget *parent) :
    QTreeWidget(parent)
{
    setIndentation(10);
    setHeaderHidden(true);
    setColumnCount(1);

}

DownloadTaskTreeWidget::~DownloadTaskTreeWidget()
{
}


void DownloadTaskTreeWidget::dealDowloadfinished(DownloadWidget *souce, int channel, bool complete, bool closed)
{
    if (closed)
    {
        for (int i = 0; i < this->topLevelItemCount(); i++)
        {
            QTreeWidgetItem* pTask = this->topLevelItem(i);
            if (pTask == nullptr)
            {
                continue;
            }

            for (int j = 0; j < pTask->childCount(); j++)
            {
                DownloadWidget* w = dynamic_cast<DownloadWidget *>
                        (this->itemWidget(pTask->child(j), 0));
                if (w == souce)
                {
                    pTask->removeChild(pTask->child(j));
                    if (pTask->childCount() == 0)
                    {
                         delete pTask;
                    }
                    return;
                }
            }
        }
    }
}





void DownloadTaskTreeWidget::dealCancelAll(TaskWidget *task)
{
    qDebug() << "DownloadTaskTreeWidget beg" << __FILE__ << __FUNCTION__ << __LINE__;
    for (int i = 0; i < this->topLevelItemCount(); i++)
    {
        QTreeWidgetItem* pTask = this->topLevelItem(i);
        if (pTask == nullptr)
        {
            continue;
        }
        TaskWidget* t = dynamic_cast<TaskWidget *>
                (this->itemWidget(pTask, 0));
        if (t != task)
        {
            continue;
        }
        this->collapseItem(pTask);
        while (pTask->childCount())
        {
            DownloadWidget* w = dynamic_cast<DownloadWidget *>
                    (this->itemWidget(pTask->child(0), 0));
            if (w != nullptr)
            {
                w->cancel();
                w->close();
                w->deleteLater();
            }
            pTask->removeChild(pTask->child(0));
       }
        qDebug() << "DownloadTaskTreeWidget beg" << __FILE__ << __FUNCTION__ << __LINE__;
        delete pTask;
        qDebug() << "DownloadTaskTreeWidget beg" << __FILE__ << __FUNCTION__ << __LINE__;
        break;
    }
}

void DownloadTaskTreeWidget::dealSel(TaskWidget *task)
{
    for (int i = 0; i < this->topLevelItemCount(); i++)
    {
        QTreeWidgetItem* pTask = this->topLevelItem(i);
        if (pTask == nullptr)
        {
            continue;
        }
        TaskWidget* t = dynamic_cast<TaskWidget *>
                (this->itemWidget(pTask, 0));
        if (t != task)
        {
            continue;
        }
        if (!this->isItemExpanded(pTask))
        {
            this->expandItem(pTask);
        }
        else
        {
            this->collapseItem(pTask);
        }

        break;
    }
}


