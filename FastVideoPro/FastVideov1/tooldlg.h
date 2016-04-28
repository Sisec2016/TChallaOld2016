#ifndef TOOLDLG_H
#define TOOLDLG_H

#include <QDialog>
#include "ui_tooldlg.h"

#include "MyBaseDialog.h"

class tooldlg : public MyBaseDialog
{
	Q_OBJECT

public:
	tooldlg(QWidget *parent = 0);
	~tooldlg();

private slots:
	void onHikToolClicked();
	void onDahuaToolClicked();
    void onbrowserBtnClicked();
    void onvideoPlayBtnClicked();
    void onproduct_setBtnClicked();
private:
	Ui::tooldlg ui;
};

#endif // TOOLDLG_H
