#include "myipaddressedit.h"
#include "ui_myipaddressedit.h"

#pragma once


#include <QIntValidator>
#include <QKeyEvent>

MyIpPartLineEdit::MyIpPartLineEdit(QWidget *parent/* = 0*/)
: QLineEdit(parent)
{
    next_tab_ = NULL;

    this->setMaxLength(3);
    this->setFrame(false);
    this->setAlignment(Qt::AlignCenter);

    QValidator *validator = new QIntValidator(0, 255, this);
    this->setValidator(validator);

    connect(this, SIGNAL(textEdited(const QString&)), this, SLOT(text_edited(const QString&)));
}

MyIpPartLineEdit::~MyIpPartLineEdit(void)
{
}

void MyIpPartLineEdit::focusInEvent(QFocusEvent *e)
{
    this->selectAll();
    QLineEdit::focusInEvent(e);
}

void MyIpPartLineEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Period)
    {
        QString ipaddr = this->text();
        if (next_tab_ && ipaddr.size()!=0)
        {
            next_tab_->setFocus();
            next_tab_->selectAll();
        }
    }
    QLineEdit::keyPressEvent(event);
}

void MyIpPartLineEdit::text_edited(const QString& text)
{
    QIntValidator v(0, 255, this);
    QString ipaddr = text;
    int pos = 0;
    QValidator::State state = v.validate(ipaddr, pos);
    if (state == QValidator::Acceptable)
    {
        if (ipaddr.size() > 1)
        {
            if (ipaddr.size() == 2)
            {
                int ipnum = ipaddr.toInt();

                if (ipnum > 25)
                {
                    if (next_tab_)
                    {
                        next_tab_->setFocus();
                        next_tab_->selectAll();
                    }
                }
            }
            else
            {
                if (next_tab_)
                {
                    next_tab_->setFocus();
                    next_tab_->selectAll();
                }
            }
        }
    }
}

MyIPAddressEdit::MyIPAddressEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyIPAddressEdit)
{
    ui->setupUi(this);

    QWidget::setTabOrder(ui->IPlineEdit1, ui->IPlineEdit2);
    QWidget::setTabOrder(ui->IPlineEdit2, ui->IPlineEdit3);
    QWidget::setTabOrder(ui->IPlineEdit3, ui->IPlineEdit4);
    ((MyIpPartLineEdit*)ui->IPlineEdit1)->set_nexttab_edit(ui->IPlineEdit2);
    ((MyIpPartLineEdit*)ui->IPlineEdit2)->set_nexttab_edit(ui->IPlineEdit3);
    ((MyIpPartLineEdit*)ui->IPlineEdit3)->set_nexttab_edit(ui->IPlineEdit4);


    connect(ui->IPlineEdit1, SIGNAL(textChanged(const QString&)), this, SLOT(textchangedslot(const QString&)));
    connect(ui->IPlineEdit2, SIGNAL(textChanged(const QString&)), this, SLOT(textchangedslot(const QString&)));
    connect(ui->IPlineEdit3, SIGNAL(textChanged(const QString&)), this, SLOT(textchangedslot(const QString&)));
    connect(ui->IPlineEdit4, SIGNAL(textChanged(const QString&)), this, SLOT(textchangedslot(const QString&)));

    connect(ui->IPlineEdit1, SIGNAL(textEdited (const QString&)), this, SLOT(texteditedslot(const QString&)));
    connect(ui->IPlineEdit2, SIGNAL(textEdited (const QString&)), this, SLOT(texteditedslot(const QString&)));
    connect(ui->IPlineEdit3, SIGNAL(textEdited (const QString&)), this, SLOT(texteditedslot(const QString&)));
    connect(ui->IPlineEdit4, SIGNAL(textEdited (const QString&)), this, SLOT(texteditedslot(const QString&)));

}

MyIPAddressEdit::~MyIPAddressEdit()
{
    delete ui;
}

void MyIPAddressEdit::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}



void MyIPAddressEdit::textchangedslot(const QString& /*text*/)
{
    QString ippart1, ippart2, ippart3, ippart4;
    ippart1 = ui->IPlineEdit1->text();
    ippart2 = ui->IPlineEdit2->text();
    ippart3 = ui->IPlineEdit1->text();
    ippart4 = ui->IPlineEdit4->text();

    QString ipaddr = QString("%1.%2.%3.%4")
                     .arg(ippart1)
                     .arg(ippart2)
                     .arg(ippart3)
                     .arg(ippart4);

    emit textchanged(ipaddr);
}

void MyIPAddressEdit::texteditedslot(const QString &/*text*/)
{
    QString ippart1, ippart2, ippart3, ippart4;
    ippart1 = ui->IPlineEdit1->text();
    ippart2 = ui->IPlineEdit2->text();
    ippart3 = ui->IPlineEdit3->text();
    ippart4 = ui->IPlineEdit4->text();

    QString ipaddr = QString("%1.%2.%3.%4")
        .arg(ippart1)
        .arg(ippart2)
        .arg(ippart3)
        .arg(ippart4);

    emit textedited(ipaddr);
}

void MyIPAddressEdit::settext(const QString &text)
{
    QString ippart1, ippart2, ippart3, ippart4;
    QString qstring_validate = text;

    // IP地址验证
    QRegExp regexp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    QRegExpValidator regexp_validator(regexp, this);
    int nPos = 0;
    QValidator::State state = regexp_validator.validate(qstring_validate, nPos);
    // IP合法
    if (state == QValidator::Acceptable)
    {
        QStringList ippartlist = text.split(".");

        int strcount = ippartlist.size();
        int index = 0;
        if (index < strcount)
        {
            ippart1 = ippartlist.at(index);
        }
        if (++index < strcount)
        {
            ippart2 = ippartlist.at(index);
        }
        if (++index < strcount)
        {
            ippart3 = ippartlist.at(index);
        }
        if (++index < strcount)
        {
            ippart4 = ippartlist.at(index);
        }
    }

    ui->IPlineEdit1->setText(ippart1);
    ui->IPlineEdit2->setText(ippart2);
    ui->IPlineEdit3->setText(ippart3);
    ui->IPlineEdit4->setText(ippart4);
}

void MyIPAddressEdit::setDefaultText(QString text)
{
    QString ippart1, ippart2, ippart3, ippart4;

    QStringList ippartlist = text.split(".");

    int strcount = ippartlist.size();
    int index = 0;
    if (index < strcount)
    {
        ippart1 = ippartlist.at(index);
    }
    if (++index < strcount)
    {
        ippart2 = ippartlist.at(index);
    }
    if (++index < strcount)
    {
        ippart3 = ippartlist.at(index);
    }
    if (++index < strcount)
    {
        ippart4 = ippartlist.at(index);
    }


    ui->IPlineEdit1->setText(ippart1);
    ui->IPlineEdit2->setText(ippart2);
    ui->IPlineEdit3->setText(ippart3);
    ui->IPlineEdit4->setText(ippart4);
}

QString MyIPAddressEdit::text()
{
    QString ippart1, ippart2, ippart3, ippart4;
    ippart1 = ui->IPlineEdit1->text().trimmed();
    ippart2 = ui->IPlineEdit2->text().trimmed();
    ippart3 = ui->IPlineEdit3->text().trimmed();
    ippart4 = ui->IPlineEdit4->text().trimmed();

    if(!ippart1.isEmpty())
    {
        ippart1 = QString("%1").arg(ippart1.toInt());
    }
    if(!ippart2.isEmpty())
    {
        ippart2 = QString("%1").arg(ippart2.toInt());
    }
    if(!ippart3.isEmpty())
    {
        ippart3 = QString("%1").arg(ippart3.toInt());
    }
    if(!ippart4.isEmpty())
    {
        ippart4 = QString("%1").arg(ippart4.toInt());
    }

    return QString("%1.%2.%3.%4")
        .arg(ippart1)
        .arg(ippart2)
        .arg(ippart3)
        .arg(ippart4);
}

void MyIPAddressEdit::setStyleSheet(const QString &styleSheet)
{
    ui->IPlineEdit1->setStyleSheet(styleSheet);
    ui->IPlineEdit2->setStyleSheet(styleSheet);
    ui->IPlineEdit3->setStyleSheet(styleSheet);
    ui->IPlineEdit4->setStyleSheet(styleSheet);
}
