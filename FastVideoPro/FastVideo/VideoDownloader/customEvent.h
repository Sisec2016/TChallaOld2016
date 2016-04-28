#ifndef CUSTONEVENT_H
#define CUSTONEVENT_H
#include <QEvent>
enum
{
    CUSTOM_EVENT_BEG = 5000,
    CUSTOM_SERVER_CALLBACK,
    CUSTOM_DOWNTASK,
    CUSTOM_LOGIN,
	CUSTOM_FINISH,
	CUSTOM_START,
    CUSTOM_ADD_ROW,
    CUSTOM_SERRCH_FINISH,
    CUSTOM_DOWNLOAD_FOR_WIDGET,
    CUSTOM_ADD_DEVICE,
    CUSTOM_FIND_IP,
    CUSTOM_TEXT,
    CUSTOM_DEVICE_UNCONNECTED
};

const QEvent::Type SERVICE_CALLBACK_EVENT = (QEvent::Type)CUSTOM_SERVER_CALLBACK;
const QEvent::Type CUSTOM_DOWNTASK_EVENT = (QEvent::Type)CUSTOM_DOWNTASK;
const QEvent::Type CUSTOM_LOGIN_EVENT = (QEvent::Type)CUSTOM_LOGIN;
const QEvent::Type CUSTOM_DEVICE_UNCONNECTED_EVENT = (QEvent::Type)CUSTOM_DEVICE_UNCONNECTED;
const QEvent::Type CUSTOM_FINISH_EVENT = (QEvent::Type)CUSTOM_FINISH;
const QEvent::Type CUSTOM_START_EVENT = (QEvent::Type)CUSTOM_START;
const QEvent::Type CUSTOM_ADD_ROW_EVENT = (QEvent::Type)CUSTOM_ADD_ROW;
const QEvent::Type CUSTOM_SERRCH_FINISH_EVENT = (QEvent::Type)CUSTOM_SERRCH_FINISH;
const QEvent::Type CUSTOM_DOWNLOAD_FOR_WIDGET_EVENT = (QEvent::Type)CUSTOM_DOWNLOAD_FOR_WIDGET;

const QEvent::Type CUSTOM_ADD_DEVICE_EVENT = (QEvent::Type)CUSTOM_ADD_DEVICE;
const QEvent::Type CUSTOM_FIND_IP_EVENT = (QEvent::Type)CUSTOM_FIND_IP;
const QEvent::Type CUSTOM_TEXT_EVENT = (QEvent::Type)CUSTOM_TEXT;
class taskEvent : public QEvent
{
public:
    taskEvent(QObject* pSender, quint32 downloadsize, bool failed) :
       QEvent(CUSTOM_DOWNTASK_EVENT), m_Sender(pSender), m_downloadsize(downloadsize), m_failed(failed)
    {

    }
    QObject* m_Sender;
    quint64 m_downloadsize;
    bool m_failed;
};
class loginEvent : public QEvent
{
public:
    loginEvent(QObject* pSender) :
       QEvent(CUSTOM_LOGIN_EVENT), m_Sender(pSender)
    {

    }
    QObject* m_Sender;
};

class AddDownloadRowEvent : public QEvent
{
public:
    AddDownloadRowEvent() :
       QEvent(CUSTOM_ADD_ROW_EVENT)
    {

    }

};
class FindIPEvent : public QEvent
{
public:
    FindIPEvent(const QString& ip) :
       QEvent(CUSTOM_FIND_IP_EVENT), mIP(ip)
    {

    }
    QString mIP;
};

class TextEvent : public QEvent
{
public:
    TextEvent(const QString& text) :
       QEvent(CUSTOM_TEXT_EVENT), mText(text)
    {

    }
    QString mText;
};

class FinishEvent : public QEvent
{
public:
    FinishEvent() :
         QEvent(CUSTOM_FINISH_EVENT)
    {

    }


};

class StartEvent : public QEvent
{
public:
	StartEvent() :
		QEvent(CUSTOM_FINISH_EVENT)
	{

	}


};
#endif // CUSTONEVENT_H
