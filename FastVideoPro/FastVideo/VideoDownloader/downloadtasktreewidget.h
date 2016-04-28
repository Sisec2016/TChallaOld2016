#ifndef DOWNLOADTASKTREEWIDGET_H
#define DOWNLOADTASKTREEWIDGET_H

#include <QTreeWidget>
#include <qevent.h>
#include <map>
#include <deque>
#include <set>
#include <thread>
#include <mutex>
#include "downloadtask.h"
#include "videoserver.h"
#include "downloadwidget.h"
#include "taskwidget.h"


class DownloadTaskTreeWidget : public QTreeWidget
{
    Q_OBJECT
    friend class DownloadTask;
public:
    explicit DownloadTaskTreeWidget(QWidget *parent = 0);
    ~DownloadTaskTreeWidget();
public slots:
	void dealCancelAll(TaskWidget *task);
private slots:
    void dealSel(TaskWidget *task);
    void dealDowloadfinished(DownloadWidget *souce, int channel,
                             bool complete, bool closed);
private:

};

#endif // DOWNLOADTASKTREEWIDGET_H
