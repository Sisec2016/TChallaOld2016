#include "noflamedlg.h"
#include "screenadaption.h"

NoFlameDlg::NoFlameDlg(QWidget *parent) : QDialog(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window );

}

NoFlameDlg::~NoFlameDlg()
{

}

