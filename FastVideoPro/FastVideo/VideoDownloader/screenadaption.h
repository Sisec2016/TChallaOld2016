#ifndef SCREENADAPTION_H
#define SCREENADAPTION_H
#include <QWidget>
class ScreenAdaption
{

    static ScreenAdaption* pInstance;
    double mWidthScaleFactor;
    double mHeightScaleFactor;
    bool mNeedAdapt;
public:
    static ScreenAdaption& instance();
    void init(int devWidth, int devHeight);
    void adpte(QWidget* p);
    void showInCenter(QWidget* p);
    double getWidthFactor()
    {
        return mWidthScaleFactor;
    }
    double getHeightFactor()
    {
        return mHeightScaleFactor;
    }

private:
    ScreenAdaption();
};

#endif // SCREENADAPTION_H
