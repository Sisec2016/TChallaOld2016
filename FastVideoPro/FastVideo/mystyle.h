#ifndef MYSTYLE_H
#define MYSTYLE_H
/*
#include <QWindowsXPStyle>
#include <QWindowsStyle>
#include <QCommonStyle>
#include <QMotifStyle>*/
#include <qstyle.h>
#include <QPalette>

QT_BEGIN_NAMESPACE
class QPainterPath;
QT_END_NAMESPACE

class MyStyle : public QStyle
{
Q_OBJECT
public:
    explicit MyStyle(){}

   void polish(QPalette &palette);
  // void polish(QWidget *widget);
  // void unpolish(QWidget *widget);
   int pixelMetric(PixelMetric metric, const QStyleOption *option,
                   const QWidget *widget) const;
   int styleHint(StyleHint hint, const QStyleOption *option,
                 const QWidget *widget, QStyleHintReturn *returnData) const;
   void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                      QPainter *painter, const QWidget *widget) const;
   void drawControl(QStyle::ControlElement control, const QStyleOption *option,
                    QPainter *painter, const QWidget *widget) const;


  /*
       QRect subElementRect(SubElement r, const QStyleOption *option, const QWidget *widget = 0) const;
       QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *option, SubControl sc,
                            const QWidget *widget = 0) const;
       void drawComplexControl(ComplexControl cc, const QStyleOptionComplex *option, QPainter *p,
                               const QWidget *widget = 0) const;
       QSize sizeFromContents(ContentsType ct, const QStyleOption *option, const QSize &contentsSize,
                              const QWidget *widget = 0) const;
     */
   private:

signals:

public slots:

};

#endif // MYSTYLE_H
