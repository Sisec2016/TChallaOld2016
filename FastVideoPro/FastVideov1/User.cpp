#include "User.h"
#include <QByteArray>
#include <QCryptographicHash>
SERIAL_MEMMBER_3(User, mName, mPasswords, mUserType)

#define MD5_PRE   "csdfsfmdgpre"
QString passwordEncrypte(const QString& passwords){
    auto md5Byte = QCryptographicHash::hash((QString(MD5_PRE) + passwords).toLatin1(), QCryptographicHash::Md5);
    return QString(md5Byte.toHex());
}

bool User::login(int UserType, const QString& sPassword){
    if (!User::setUserType(UserType))
    {
        return false;
    }

    return spCurrent->isCollectPasswords(sPassword);
}

User& User::current(){
    if (!spCurrent)
    {
        spCurrent = std::make_shared<User>();
    }

    return *spCurrent;
}

bool User::setUserType(int type){
    if (type <= USER_TYPE_NULL || type > USER_TYPE_NUM)
    {
        qDebug() << "UserType not correct!";
        return false;
    }
    std::vector< std::shared_ptr<User> > mResults = query(std::make_pair("mUserType", type));
    if (mResults.size() > 0)
    {
        spCurrent = mResults[0];
    }
    else{
        spCurrent = std::make_shared<User>();
        spCurrent->init(type);
    }

    return true;
}
std::shared_ptr<User> User::spCurrent;
User::User()
{
    mUserType = USER_TYPE_NULL;
    mHaveLogin = false;
}
User::~User()
{
}
void User::init(int UserType){
    if (UserType <= USER_TYPE_NULL || UserType > USER_TYPE_NUM)
    {
        qDebug() << "UserType not correct!";
        return;
    }
    switch (UserType){
    case USER_TYPE_COLLECT:
        this->mName = QStringLiteral("采集员");
        setPassword("sisec_admin");
        break;
    case USER_TYPE_EXPORT:
        this->mName = QStringLiteral("导出员");
        setPassword("sisec_admin");
        break;
    case USER_TYPE_ADMIN:
        this->mName = QStringLiteral("管理员");
        setPassword("sisec_admin");
        break;
    default:
        setPassword("sisec_admin");
        break;
    }
    this->mUserType = UserType;
    this->save();
}
bool User::isCollectPasswords(const QString& sPasswords){
    if (mUserType <= USER_TYPE_NULL || mUserType > USER_TYPE_NUM)
    {
        return false;
    }

    mHaveLogin = (mPasswords == passwordEncrypte(sPasswords + mName));
    return mHaveLogin;
}

void User::setPassword(const QString& password){
    this->mPasswords = passwordEncrypte(password + mName);
    this->save();
}

