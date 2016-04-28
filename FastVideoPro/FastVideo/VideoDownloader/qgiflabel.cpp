#include "qgiflabel.h"
#include <QMovie>
#include <QMessageBox>

QGifLabel::QGifLabel(QWidget *parent) :
    QLabel(parent)
{
    loadGif();
}


void QGifLabel::loadGif()
{
    QString sStyleSheet(this->styleSheet());
    sStyleSheet.replace(" ", "");
    int begin = sStyleSheet.indexOf("border-image:url");
    if (begin != -1)
    {
        this->setStyleSheet("");
        begin += strlen("border-image:url(");
        int end = sStyleSheet.indexOf(".gif", begin);
        if (end != -1)
        {
            this->setStyleSheet("");
            end += strlen(".gif");
            QString gif(sStyleSheet.mid(begin, end - begin));//
            mMovie.setFileName(gif);
            mMovie.setBackgroundColor(QColor(Qt::black));
            mMovie.setPaused(false);
            mMovie.setScaledSize(this->size());
            setMovie(&mMovie);
            mMovie.start();
        }
    }
}
