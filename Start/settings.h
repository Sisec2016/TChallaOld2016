#ifndef SETTINGS_H
#define SETTINGS_H
#include <map>
#include <QString>

#define  SETTIN_TABLE_NAME  "SettingInfo"

#define  KEY_SERVER         "server_ip"
#define  KEY_CURVERSION     "cur_verstion"
#define  KEY_MD5            "cur_md5"
#define  KEY_FILE_URL       "cur_file_url"

#define  KEY_DOWNLOAD_VERSION   "download_verstion"
#define  KEY_DOWNLOAD_MD5       "download_md5"
#define  KEY_DOWNLOAD_FILE_URL  "download_file_url"

#define  KEY_SERVER_VERSION   "server_verstion"
#define  KEY_SERVER_MD5       "server_md5"
#define  KEY_SERVER_FILE_URL  "server_file_url"

#define  KEY_UPGRADE_STATE      "upgrade_state"
#define  KEY_UPGRADE_STATE_INSTALLED        ""
#define  KEY_UPGRADE_STATE_DOWNLOADING      "2"
#define  KEY_UPGRADE_STATE_DOWNLOADED       "3"
#define  KEY_UPGRADE_STATE_INSTALLING       "4"

class Settings
{
private:
    Settings();
public:
    static void createTable();
    static bool setItem(const QString &key, const QString &value);
    static QString getItem(const QString &key);
};

#endif // SETTINGS_H
