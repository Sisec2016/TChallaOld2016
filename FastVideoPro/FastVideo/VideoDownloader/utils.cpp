#include "utils.h"
#include "qdebug.h"
#include <QDir>

Utils::Utils()
{

}

void Utils::CreateIfNotExist(const QString& spath)
{

    QDir d(spath);
    if (!d.exists())
    {
        d.mkpath(spath);
    }
}

bool In(wchar_t start, wchar_t end, wchar_t code)
{
    if (code >= start && code <= end)
    {
        return true;
    }
    return false;
}

char convert(int n)
{
    if (In(0xB0A1, 0xB0C4, n)) return 'a';
    if (In(0XB0C5, 0XB2C0, n)) return 'b';
    if (In(0xB2C1, 0xB4ED, n)) return 'c';
    if (In(0xB4EE, 0xB6E9, n)) return 'd';
    if (In(0xB6EA, 0xB7A1, n)) return 'e';
    if (In(0xB7A2, 0xB8c0, n)) return 'f';
    if (In(0xB8C1, 0xB9FD, n)) return 'g';
    if (In(0xB9FE, 0xBBF6, n)) return 'h';
    if (In(0xBBF7, 0xBFA5, n)) return 'j';
    if (In(0xBFA6, 0xC0AB, n)) return 'k';
    if (In(0xC0AC, 0xC2E7, n)) return 'l';
    if (In(0xC2E8, 0xC4C2, n)) return 'm';
    if (In(0xC4C3, 0xC5B5, n)) return 'n';
    if (In(0xC5B6, 0xC5BD, n)) return 'o';
    if (In(0xC5BE, 0xC6D9, n)) return 'p';
    if (In(0xC6DA, 0xC8BA, n)) return 'q';
    if (In(0xC8BB, 0xC8F5, n)) return 'r';
    if (In(0xC8F6, 0xCBF0, n)) return 's';
    if (In(0xCBFA, 0xCDD9, n)) return 't';
    if (In(0xCDDA, 0xCEF3, n)) return 'w';
    if (In(0xCEF4, 0xD188, n)) return 'x';
    if (In(0xD1B9, 0xD4D0, n)) return 'y';
    if (In(0xD4D1, 0xD7F9, n)) return 'z';
    return '\0';
}

QString Utils::getChineseSpell(const QString& src)
{
    wchar_t wchr;
    QString strPinYin;
    for (int i = 0; i < src.length(); i++)
    {
        QString str = src.at(i);
        QByteArray arr = str.toLocal8Bit();
        wchr = (arr.at(0) & 0xff) << 8;
        wchr |= (arr.at(1) & 0xff);
        strPinYin.append(convert(wchr));
    }

    return strPinYin;
}


long getIpNum(const QString& ipAddress) {
    auto ips = ipAddress.split(".");
    if (ips.size() < 4)
    {
        return 0;
    }
    long a = ips.at(0).toULong();
    long b = ips.at(1).toULong();
    long c = ips.at(2).toULong();
    long d = ips.at(3).toULong();

    long ipNum = a * 256 * 256 * 256 + b * 256 * 256 + c * 256 + d;
    return ipNum;
}

bool isInner(long userIp, long begin, long end){
    return (userIp >= begin) && (userIp <= end);
}
bool Utils::isInnerIP(const QString& ipAddress){
    bool isInnerIp = false;
    long ipNum = getIpNum(ipAddress);
    /**
    私有IP：A类  10.0.0.0-10.255.255.255
    B类  172.16.0.0-172.31.255.255
    C类  192.168.0.0-192.168.255.255
    当然，还有127这个网段是环回地址
    **/
    long aBegin = getIpNum("10.0.0.0");
    long aEnd = getIpNum("10.255.255.255");
    long bBegin = getIpNum("172.16.0.0");
    long bEnd = getIpNum("172.31.255.255");
    long cBegin = getIpNum("192.168.0.0");
    long cEnd = getIpNum("192.168.255.255");
    isInnerIp = isInner(ipNum, aBegin, aEnd) || isInner(ipNum, bBegin, bEnd) || isInner(ipNum, cBegin, cEnd);
    return isInnerIp;
}
