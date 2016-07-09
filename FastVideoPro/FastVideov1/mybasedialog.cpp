#include "mybasedialog.h"
#include "qss.h"
#include <qapplication.h>

MyBaseDialog::MyBaseDialog(QWidget *parent):QDialog(parent)
{
    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowSystemMenuHint| Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);

    setMouseTracking( true );

	//this->setStyleSheet("QLabel{color:white;}QDialog{background-image: url(images/mainBackgound.png);background-repeat: no-repeat;background-color:rgb(48,68,137);}");
	
	this->setStyleSheet(QLatin1String("QDialog\n"
		"{\n"
		"	border-image: url(:/images/mainBackgound.png);\n"
		"}\n"
		"QWidget\n"
		"{\n"
		"  	font-size:18px;\n"
		"}\n"
		"QPushButton\n"
		"{\n"
		"	font-size:18px;\n"
		"	font-family:Microsoft Yahei;\n"
		"}\n"
		"QPushButton\n"
		"{\n"
		"background-color: rgb(192, 192, 224);\n"
		"border-color: rgb(176, 186, 221);\n"
		"border-width: 2px;\n"
		"border-style: solid;\n"
		"border-radius: 4;\n"
		"}\n"
		"QPushButton:hover\n"
		"{\n"
		"border-color: rgb(240, 240, 240);\n"
		"}\n"
		"QPushButton:pressed\n"
		"{\n"
		"		border-color: rgb(240, 240, 240);\n"
		"}\n"
		"QLineEdit\n"
		"{\n"
		"border-width: 0px;\n"
		"border-style: solid;\n"
		"border-radius: 4;\n"
		"background-color:rgb(89, 107, 169);"
		"selection-background-color:rgb(136,150,199);"
		"color:white;"
		"}\n"
		"QCheckBox\n"
		"{\n"
		"  	font-size:18px;\n"
		"	color: rgb(255, 255, 255);\n"
		"	font-family:Microsoft Yahei;\n"
		"}\n"
		"QLabel\n"
		"{\n"
		"font-size:18px;\n"
		"color: rgb(255, 255, 255);\n"
		"font-family:Microsoft Yahei;\n"
		"}\n"
		"QGroupBox\n"
		"{\n"
		"font-size:20px;\n"
		"font-family:Microsoft Yahei;\n"
		"}\n"
		"QTreeView::item{height: 35px; }"
		"\n"
		"QTableWidget,QTableView,QTreeView{\n"
		"background: rgb(229,227,231);\n"
		"selection-color:black;\n"
		"}\n"
		"QHeaderView{"
			"background-color: rgb(201, 212, 242);"
			"border-bottom:1px;"
			"border-style:solid;"
			"border-color: rgb(160, 160, 160);"
		"}"
		"QHeaderView::section{"
			"height:25px;"
			"margin-top:5px;"
			"margin-bottom:5px;"
			"background-color: rgb(201, 212, 242);"
			"color:black;"
			"border:0px;"
			"border-right:1px solid;"
			"border-color:rgb(94, 98, 143);"
			"}"
		"QTableWidget::item{"
			"height:45px;"
			"border-bottom:1px solid;"
			"border-color: rgb(198, 207, 214);"
		"}"
		"QTableWidget::item:selected{"
			"background-color: rgb(175, 211, 237);"
		"}"
		));
	this->setGeometry(QRect(0, 0, 1364, 766));
    closeBtn = new QPushButton(this);
    closeBtn->setObjectName(QString::fromUtf8("closeBtn"));
    closeBtn->setGeometry(QRect(this->width() - 55, 4, 45, 45));
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/images/close.png"), QSize(), QIcon::Normal, QIcon::Off);
    closeBtn->setIcon(icon);
    closeBtn->setIconSize(QSize(45, 45));

   minBtn = new QPushButton(this);
   minBtn->setObjectName(QString::fromUtf8("minBtn"));
   minBtn->setGeometry(QRect(934, 4, 45, 45));
   QIcon icon1;
   icon1.addFile(QString::fromUtf8(":/images/min.png"), QSize(), QIcon::Normal, QIcon::Off);
   minBtn->setIcon(icon1);
   minBtn->setIconSize(QSize(45, 45));

   minBtn->hide();
  // closeBtn->hide();

   backBtn = new QPushButton(this);
   backBtn->setObjectName(QString::fromUtf8("backBtn"));
   backBtn->setGeometry(QRect(10, 10, 32, 32));
   QIcon icon2;
   icon2.addFile(QString::fromUtf8(":/images/back.png"), QSize(), QIcon::Normal, QIcon::Off);
   backBtn->setIcon(icon2);
   backBtn->setIconSize(QSize(32, 32));

   title_label = new QLabel(this);
   title_label->setObjectName(QString::fromUtf8("title_label"));
   title_label->setGeometry(QRect(this->width() / 2 - 80, 5, 200, 40));
  // QFont font;
 //  font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
 // font.setPointSize(22);//ui setStyleSheet设置UI
 //  title_label->setFont(font);
   title_label->setStyleSheet("color:white;font-size:35px");

   closeBtn->setStyleSheet(transparentBtn_StyleSheet);
   minBtn->setStyleSheet(transparentBtn_StyleSheet);
   backBtn->setStyleSheet(transparentBtn_StyleSheet);

   connect(closeBtn,SIGNAL(clicked()),this,SLOT(onCloseClicked()));
   connect(minBtn,SIGNAL(clicked()),this,SLOT(onMinClicked()));
   connect(backBtn,SIGNAL(clicked()),this,SLOT(onBackClicked()));

}

 MyBaseDialog::~MyBaseDialog()
 {
    delete closeBtn;
    delete minBtn;
    delete backBtn;
    delete title_label;
 }

 void MyBaseDialog::onCloseClicked()
 {
    // this->accept();
     this->close();
 }

 void MyBaseDialog::onMinClicked()
 {
     this->showMinimized();
 }

 void MyBaseDialog::onBackClicked()
 {
     this->close();
    // this->accept();
 }

void MyBaseDialog::mousePressEvent(QMouseEvent* event)
{
    QDialog::mousePressEvent(event);
    if(event->button() == Qt::LeftButton)
    {
        mMoving = true;
        mLastMousePosition = event->globalPos();
    }
}

void MyBaseDialog::mouseMoveEvent(QMouseEvent* event)
{
    QDialog::mouseMoveEvent(event);
    if( event->buttons().testFlag(Qt::LeftButton) && mMoving)
    {
      //  this->move(this->pos() + (event->globalPos() - mLastMousePosition));
     //   mLastMousePosition = event->globalPos();
    }
}

void MyBaseDialog::mouseReleaseEvent(QMouseEvent* event)
{
    QDialog::mouseReleaseEvent(event);
    if(event->button() == Qt::LeftButton)
    {
        mMoving = false;
    }
}

void MyBaseDialog::showEvent(QShowEvent* event)
{
	QDialog::showEvent(event);
	QWidget* pParent = NULL;// this->parentWidget();
	if (pParent == NULL)
	{
		pParent = (QWidget*)QApplication::desktop();
	}
	this->move((pParent->width() -this->width()) / 2, (pParent->height() - this->height()) / 2 );
	
}

void MyBaseDialog::setTitleName(QString name)
{
    title_label->setText(name);
}

