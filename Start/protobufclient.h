#ifndef PROTOBUF_CLIENT_H
#define PROTOBUF_CLIENT_H
#include <QString>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "../common/protobuf/SettingInfo.pb.h"

class ProtobufClient : public QObject
{
    Q_OBJECT
public:

    ProtobufClient();

    static ProtobufClient *pInstance;
public:
    static ProtobufClient &instance()
    {
        if (pInstance == nullptr)
        {
            pInstance = new  ProtobufClient();
        }

        return *pInstance;
    }
public:
    bool loadSetting(const QString& sn);
    void post_async(const QString &data);
    bool getDownloadData(QByteArray &rsp, const std::string& sTableName, const std::string& sCondtion);
    bool post(QByteArray &rsp, const QString &data);
private:
    QNetworkAccessManager *_uploadManager;
    QNetworkReply *_reply;

private slots:
    void replyFinished(QNetworkReply *reply);
    void upLoadError(QNetworkReply::NetworkError errorCode);
    void OnUploadProgress(qint64 bytesSent, qint64 bytesTotal);
private:
    QString mStrServerIP;
    SettingInfos mSettingInfos;
};

#endif // PROTOBUF_CLIENT_H
