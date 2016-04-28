#include "formfactoryitem.h"
#include "ui_formfactoryitem.h"

FormFactoryItem::FormFactoryItem(QWidget *parent) :
    ListViewItem(parent),
    ui(new Ui::FormFactoryItem),
    mpFactory(nullptr)
{
    ui->setupUi(this);
}

FormFactoryItem::~FormFactoryItem()
{
    delete ui;
}

void FormFactoryItem::setFactory(videoserverFactory *pFactory)
{
    mpFactory = pFactory;
    if (nullptr != mpFactory)
    {
        ui->label->setText(mpFactory->name());
    }
    else
    {
        ui->label->setText("");
    }
}
