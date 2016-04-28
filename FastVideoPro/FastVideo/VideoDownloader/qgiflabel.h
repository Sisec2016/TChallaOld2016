#ifndef QGIFLABEL_H
#define QGIFLABEL_H

#include <QLabel>
#include <QMovie>
#include <qdebug.h>

class QGifLabel : public QLabel
{
    Q_OBJECT
public:
    /*
     * 构造函数
     *  @param [in] parent 父对象
     *  @return void
     */
    QGifLabel(QWidget *parent = 0);
    void loadGif();
private:
    QMovie mMovie;

};

#endif // QGIFLABEL_H
