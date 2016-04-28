#ifndef FASTVIDEO_H
#define FASTVIDEO_H

#include <QtWidgets/QMainWindow>
#include "ui_fastvideo.h"

class FastVideo : public QMainWindow
{
	Q_OBJECT

public:
	FastVideo(QWidget *parent = 0);
	~FastVideo();

private:
	Ui::FastVideoClass ui;
};

#endif // FASTVIDEO_H
