#ifndef PLAYRECORDFILEWIDGET_H
#define PLAYRECORDFILEWIDGET_H
#include <QDialog>
#include "videoserver.h"
#include <QThread>
#include <thread>
#include <mutex>
#include <QTimer>
#include "noflamedlg.h"
namespace Ui {
class PlayRecordFilewidget;
}

class PlayRecordFilewidget : public NoFlameDlg
{
    Q_OBJECT

public:
    explicit PlayRecordFilewidget(RecordFile &f, std::shared_ptr<videoserver> pServer, QWidget *parent = 0);
    ~PlayRecordFilewidget();
    QWidget& getPlayWidget();
protected:
    std::shared_ptr<videoserver>  mpService;
    RecordFile &mFile;
    play_handle_t m_playfile;
    int m_Pause;


private slots:    
    void on_CloseButton_clicked();

    void initplay();

    void on_btnPlay_clicked();

    void on_btnStop_clicked();

    void on_Playtime_sliderReleased();
    void sliderTimeout();
    void on_Playtime_sliderPressed();

private:
    Ui::PlayRecordFilewidget *ui;
    std::thread* m_pThrDowload;
    QTimer mSliderTimer;
    QTimer *timePlay;
};

#endif // PLAYRECORDFILEWIDGET_H


