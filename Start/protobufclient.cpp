#undef UNICODE
#include "protobufclient.h"
#include <qdebug.h>
#include "settings.h"
#include "../common/protobuf/pos_request.pb.h"
#include "../common/protobuf/SettingInfo.pb.h"
#include "../common/protobuf/Device.pb.h"
#include "../common/protobuf/DeviceType.pb.h"
#include "../common/protobuf/VersionInfo.pb.h"
#include <QApplication>

#ifdef VERSION_SSD
#define SETTING_TALBE "settinginfo_ssd"
#else
#define SETTING_TALBE "settinginfo"
#endif

#define TABLE_DEVICE "device"
#define TABLE_DEVICETYPE "devicetype"
#define TABLE_VERSIONINFO "versioninfo"

ProtobufClient *ProtobufClient::pInstance = nullptr;

ProtobufClient::ProtobufClient() : QObject(nullptr)
{
    mStrServerIP = Settings::getItem(KEY_SERVER);
    if (mStrServerIP.isEmpty()){
        mStrServerIP = "http://202.103.191.73/fast_video/api/server.php";
    }
    _uploadManager = new QNetworkAccessManager(this);
    connect(_uploadManager,SIGNAL(finished(QNetworkReply*)),SLOT(replyFinished(QNetworkReply*)));
}

bool ProtobufClient::loadSetting(const QString& sn){
    QByteArray resp;
    if (!this->getDownloadData(resp, SETTING_TALBE, "")){
        qDebug()<<__FILE__<<__FUNCTION__<<__LINE__;
        return false;
    }
    SettingInfos infos;
    infos.ParseFromArray(resp.data(), resp.size());
    for (int i = 0; i < infos.data_size(); i++){
        auto d = infos.data(i);
        Settings::setItem(d.key().c_str(),  d.value().c_str());
    }

    resp.clear();
    if (!this->getDownloadData(resp, TABLE_DEVICE, std::string("sn='") + sn.toLocal8Bit().data() + "'")){
        qDebug()<<__FILE__<<__FUNCTION__<<__LINE__;
        return false;
    }

    Devices devices;
    devices.ParseFromArray(resp.data(), resp.size());
    if (devices.data_size() <= 0){
        qDebug()<<__FILE__<<__FUNCTION__<<__LINE__;
        return false;
    }

    resp.clear();
    QString sCondtion = QString("`id`=%1").arg(devices.data(0).devicetype_id());
    qDebug()<<sCondtion;
    if (!this->getDownloadData(resp, TABLE_DEVICETYPE,
             sCondtion.toStdString())){
        qDebug()<<__FILE__<<__FUNCTION__<<__LINE__;
        return false;
    }
    DeviceTypes dvcetypes;
    dvcetypes.ParseFromArray(resp.data(), resp.size());
    if (dvcetypes.data_size() <= 0){
        qDebug()<<__FILE__<<__FUNCTION__<<__LINE__;
        return false;
    }

    resp.clear();
    sCondtion = QString("`id`=%1").arg(dvcetypes.data(0).version_id());
    qDebug()<<sCondtion<<dvcetypes.data(0).name().c_str();
    if (!this->getDownloadData(resp, TABLE_VERSIONINFO,
             sCondtion.toStdString())){
        qDebug()<<__FILE__<<__FUNCTION__<<__LINE__;
        return false;
    }
    VersionInfos vrsns;
    vrsns.ParseFromArray(resp.data(), resp.size());
    if (vrsns.data_size() <= 0){
        qDebug()<<__FILE__<<__FUNCTION__<<__LINE__;
        return false;
    }
    auto d = vrsns.data(0);
    Settings::setItem(KEY_SERVER_VERSION, d.name().c_str());
    Settings::setItem(KEY_SERVER_MD5, d.md5().c_str());
    Settings::setItem(KEY_SERVER_FILE_URL, d.url().c_str());

    return true;
}

bool ProtobufClient::getDownloadData(QByteArray &rspArray, const std::string& sTableName, const std::string& sCondtion) {
qDebug()<<__FUNCTION__<<__LINE__<<sTableName.c_str();
    pos_request request;
    request.set_table_name(sTableName);
    request.set_condtion(sCondtion);
    request.set_type(pos_request::DOWN_LOAD);
    if (!this->post(rspArray, QString::fromStdString(request.SerializeAsString()))){
        qDebug()<<__FUNCTION__<<__LINE__;
        return false;
    }

    pos_respone pos_resp;
    if (!pos_resp.ParseFromArray(rspArray.data(), rspArray.size()))
    {
        qDebug()<<__FUNCTION__<<__LINE__;
        return false;
    }

    if (!pos_resp.error().empty()){
        qDebug()<<__FUNCTION__<<__LINE__<<pos_resp.error().c_str();
        return false;
    }

    if (pos_resp.pbdata_size() == 0){
        qDebug()<<__FUNCTION__<<__LINE__<< "no pb_data!";
        return false;
    }

    rspArray = pos_resp.pbdata(0).c_str();
    qDebug()<<rspArray;
    return true;
}


const int TIMEOUT = (30 * 1000);
bool ProtobufClient::post(QByteArray &rsp, const QString &data)
{

    QNetworkRequest _request;
    qDebug()<<mStrServerIP;
    _request.setUrl(mStrServerIP);
    QSslConfiguration _sslCon = _request.sslConfiguration();
    _sslCon.setPeerVerifyMode(QSslSocket::VerifyNone);
    _request.setSslConfiguration(_sslCon);
    _request.setHeader(QNetworkRequest::ContentTypeHeader,
                       QString("application/x-www-form-urlencoded"));

    QNetworkReply *_reply = _uploadManager->post(_request, data.toLatin1());
    _reply->ignoreSslErrors();


    QTime _t;
    _t.start();

    bool _timeout = false;

    while (!_reply->isFinished()) {
        QApplication::processEvents();
        if (_t.elapsed() >= TIMEOUT) {
            _timeout = true;
            break;
        }
    }

    bool bOk = (!_timeout && _reply->error() == QNetworkReply::NoError);
    if (bOk) {
        rsp = _reply->readAll();
    }
    else{
        qDebug()<<"_timeout:"<< " _reply->errorString:" << _reply->errorString();
    }
    _reply->deleteLater();

    return bOk;

}
void ProtobufClient::post_async(const QString &data)
{

     QNetworkRequest request( mStrServerIP );

     _reply = _uploadManager->post( request , data.toLatin1() );

     connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(upLoadError(QNetworkReply::NetworkError)));
     connect(_reply, SIGNAL(uploadProgress ( qint64 ,qint64 )), this, SLOT( OnUploadProgress(qint64 ,qint64 )));

}


void ProtobufClient::replyFinished(QNetworkReply *reply)
{
     if(reply->error() == QNetworkReply::NoError)
     {
         qDebug()<<"no error.....";
         //QByteArray bytes = reply->readAll();  //获取字节
         //QString result(bytes);  //转化为字符串
         //qDebug()<<result;
     }
     else{
         qDebug() << "replyFinished:  " << reply->error() << " " <<reply->errorString();
     }

     QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
     qDebug()<<status_code;
 }

void ProtobufClient::upLoadError(QNetworkReply::NetworkError errorCode)
{
    qDebug() << "upLoadError  errorCode: " << (int)errorCode;
}

void ProtobufClient::OnUploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    qDebug() << "bytesSent: " << bytesSent << "  bytesTotal: "<< bytesTotal;
}


