#pragma once
#include "SqlUtils.h"
#include "SqlTableMembers.h"

#define USER_TYPE_NULL     0
#define USER_TYPE_COLLECT  1
#define USER_TYPE_EXPORT   2
#define USER_TYPE_ADMIN    3
#define USER_TYPE_NUM      3
class User : public SqlTable<User>
{
    SERIAL_MEMMBER_HEAD()
public:
    static bool login(int UserType, const QString& sPassword);
    static User& current();
    static bool setUserType(int type);
private:
    static std::shared_ptr<User> spCurrent;
    bool mHaveLogin;
public:
    User();
    ~User();
    void init(int nUserType);
    bool isCollectPasswords(const QString& sPasswords);
    bool isLogined(){
        return mHaveLogin;
    }
    bool isExport(){
        return mUserType == USER_TYPE_EXPORT;
    }
    bool isCollect(){
        return mUserType == USER_TYPE_COLLECT;
    }
    bool isAdmin(){
        return mUserType == USER_TYPE_ADMIN;
    }
    void setPassword(const QString& password);
    QString mName;
    QString mPasswords;
    int mUserType;
};

