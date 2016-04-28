#include "mystyle.h"

#include <QtGui>

#define backgoundColor QColor(0, 70, 191)

#define toolbuttonColor QColor(64, 182, 255)
#define toolbuttonColorMouseOver QColor(90, 182, 255)
#define toolbuttonColorSunken QColor(120, 182, 255)

#define baseColor QColor(175,175,216)
#define hightlightColor QColor(135,200,255)

void MyStyle::polish(QPalette &palette)
{

}
/*
void MyStyle::polish(QWidget *widget)
{
    if (qobject_cast<QPushButton *>(widget)
            || qobject_cast<QComboBox *>(widget))
        widget->setAttribute(Qt::WA_Hover, true);
}

void MyStyle::unpolish(QWidget *widget)
{
    if (qobject_cast<QPushButton *>(widget)
            || qobject_cast<QComboBox *>(widget))
        widget->setAttribute(Qt::WA_Hover, false);
}
*/
int MyStyle::pixelMetric(PixelMetric metric,
                                    const QStyleOption *option,
                                    const QWidget *widget) const
{
    switch (metric) {
    case PM_ComboBoxFrameWidth:
        return 8;
    case PM_ScrollBarExtent:
		return QStyle::pixelMetric(metric, option, widget) + 4;
    default:
		return QStyle::pixelMetric(metric, option, widget);
    }
}

int MyStyle::styleHint(StyleHint hint, const QStyleOption *option,
                                  const QWidget *widget,
                                  QStyleHintReturn *returnData) const
{

	return QStyle::styleHint(hint, option, widget, returnData);

}

void MyStyle::drawPrimitive(PrimitiveElement element,
                                       const QStyleOption *option,
                                       QPainter *painter,
                                       const QWidget *widget) const
{
    switch (element) {

    case PE_FrameFocusRect:
        {
        }
           break;
    default:

		QStyle::drawPrimitive(element, option, painter, widget);
    }
}


void MyStyle::drawControl(QStyle::ControlElement element,
                                     const QStyleOption *option,
                                     QPainter *painter,
                                     const QWidget *widget) const
{
	QStyle::drawControl(element, option, painter, widget);

}


