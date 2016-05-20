#include "videoserver.h"
#include <QCoreApplication>
#include <QList>
#include <QLibrary>
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <qdebug.h>
#include "windowutils.h"
#include <QThread>
#include <eh.h>
#include <algorithm>
#include "xmlsettings.h"
#include <QTcpSocket>
#include "time.h"
#include "videoserversSvr.h"

SERIAL_MEMMBER_8(LoginServerInfo, name, ip, port, user, password, macAddress, factory, id)


QDataStream & operator << (QDataStream &dataStream, RecordFile &d)
{
    dataStream<<d.beginTime;
    dataStream<<d.channel;
    dataStream<<d.endTime;
    dataStream<<QString::fromLocal8Bit(d.name.c_str());
    dataStream<<d.size;
    dataStream<<d.getPrivateDataSize();
    if (d.getPrivateDataSize() > 0)
    {
        dataStream.writeBytes((char*)d.getPrivateData(), d.getPrivateDataSize());
    }

    return dataStream;
}

QDataStream & operator >> (QDataStream &dataStream, RecordFile &d)
{
    dataStream>>d.beginTime;
    dataStream>>d.channel;
    dataStream>>d.endTime;
    QString qName;
    dataStream>>qName;
    d.name = qName.toStdString();
    dataStream>>d.size;
    dataStream>>d.PrivateDataDataSize;
    if (d.PrivateDataDataSize > 0)
    {
        uint bufLen = d.PrivateDataDataSize;
        dataStream.readBytes(d.pPrivateData, bufLen);
        d.PrivateDataDataSize = bufLen;
    }

    return dataStream;
}

QDataStream & operator << (QDataStream &dataStream, LoginServerInfo &d)
{
    dataStream << (qint32)d.factory << d.ip << d.macAddress << d.name << d.password
                  << d.port << d.user <<d.id;

    return dataStream;
}

QDataStream & operator >> (QDataStream &dataStream, LoginServerInfo &d)
{
    qint32 f = 0;
    dataStream >> f;
    d.factory = (DeviceFactory)f;
    dataStream >> d.ip >> d.macAddress >> d.name >> d.password
                                    >> d.port >> d.user >> d.id;

    return dataStream;
}


std::deque<videoserverFactory *> videoserverFactory::s_Factorys;
std::recursive_mutex videoserverFactory::s_mutexFactorys;
std::vector<std::string> videoserverFactory::s_vcExternFunStrings;

OEMFacMap videoserverFactory::m_OEMXMFacMap;   //雄迈OEM系列
OEMFacMap videoserverFactory::m_OEMHIKFacMap;  //海康OEM系列
OEMFacMap videoserverFactory::m_OEMDHFacMap;   //大华OEM系列
OEMFacMap videoserverFactory::m_OEMWSDFacMap;  //沃仕达OEM系列
OEMFacMap videoserverFactory::m_OEMJiuAnFacMap;  //九安OEM系列
OEMFacMap videoserverFactory::m_OEMDongYangFacMap; //东阳OEM系统
OEMFacMap videoserverFactory::m_OEMZhongWeiFacMap; //中维OEM系列


downloadEvent::downloadEvent(videoserver* pSvr, qint64 totalSize, qint64 size, bool failed) :
   QEvent(SERVICE_CALLBACK_EVENT), m_pSvr(pSvr), m_totalSize(totalSize), m_size(size), m_failed(failed)
{

}


const std::deque<videoserverFactory*>& videoserverFactory::getFactorys()
{
    std::lock_guard<std::recursive_mutex> lock(s_mutexFactorys);
    
    if (s_Factorys.size() == 0)
    {
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__ << "s_Factorys.size() == 0";
        std::vector< int > vcFactorys;
        SvrFactory::getFactorys(vcFactorys);
        for (int i = 0; i < vcFactorys.size(); i++)
        {
            int f = vcFactorys[i];
            IVideoServerFactory* pFactory = new SvrFactory(f);
            videoserverFactory* pvsf = new videoserverFactory(pFactory);
            s_Factorys.push_back(pvsf);
            qDebug() << __FILE__ << __FUNCTION__ << __LINE__ << f;
            addFakeFactory(pFactory);
        }
    }

    return s_Factorys;
}

void videoserverFactory::initOEMFacList()
{
	// 迪智浦OEM
	{
		m_OEMXMFacMap["巨峰科技"] = SISC_IPC_JF;
		m_OEMXMFacMap["施耐安"] = SISC_IPC_SNA;
		m_OEMXMFacMap["雄迈"] = SISC_IPC_XM;
		m_OEMXMFacMap["海视泰"] = SISC_IPC_HAISHITAI;
		m_OEMXMFacMap["新达共创"] = SISC_IPC_XINDAGONGCHUANG;
		m_OEMXMFacMap["天视达"] = SISC_IPC_TIANSHIDA;
		m_OEMXMFacMap["守卫者"] = SISC_IPC_SHOUWEIZHE;
		m_OEMXMFacMap["深圳思浪"] = SISC_IPC_SILANG;
		m_OEMXMFacMap["霍尼韦尔"] = SISC_IPC_HUONIWEIER;
		m_OEMXMFacMap["云典视"] = SISC_IPC_YUNDIANSHI;
		m_OEMXMFacMap["世星安防"] = SISC_IPC_SHIXINGANFANG;
		m_OEMXMFacMap["立安达"] = SISC_IPC_LIANDA;
		m_OEMXMFacMap["南宁冠泰"] = SISC_IPC_NANNINGGUANGTAI;
		m_OEMXMFacMap["云典视"] = SISC_IPC_YUNDIANSHI;
		m_OEMXMFacMap["德加拉"] = SISC_IPC_DEJIALA;


 		m_OEMXMFacMap["美防伟业"] = SISC_IPC_MEIFANGWEIYE;
 		m_OEMXMFacMap["邦世电子"] = SISC_IPC_GUANGZHOUBANGSHI;
 		m_OEMXMFacMap["视安安防"] = SISC_IPC_GUANGZHOUSHIAN;
 		m_OEMXMFacMap["乔安科技"] = SISC_IPC_QIAOAN;
        m_OEMXMFacMap["朗视兴"] = SISC_IPC_LANGSHIXIN;
        m_OEMXMFacMap["亚安"] = SISC_IPC_YAAN;
 		m_OEMXMFacMap["泰威高科"] = SISC_IPC_TAIWEIGAOKE;
        m_OEMXMFacMap["广州亿视"] = SISC_IPC_GUANGZHOUYISHI;
        m_OEMXMFacMap["深圳宏康威视OEM雄迈"] = SISC_IPC_HONGKANGWEISHIOEMXM;

        m_OEMXMFacMap["臻视顺"] = SISC_IPC_ZHENSHISHUN;                      // 臻视顺
        m_OEMXMFacMap["金山品科"] = SISC_IPC_JINSHANPINKE;                            // 金山品科
        m_OEMXMFacMap["旭峰威视"] = SISC_IPC_XUFENGWS;                                // 旭峰威视
        m_OEMXMFacMap["欣视宝"] = SISC_IPC_XINGSHIBAO;                              // 欣视宝

        m_OEMXMFacMap["佳视安"] = SISC_IPC_ZSB;                      // 佳视安
        m_OEMXMFacMap["开尔瑞"] = SISC_IPC_KER;                            // 开尔瑞
        m_OEMXMFacMap["安尼"] = SISC_IPC_AN;                                // 安尼
        m_OEMXMFacMap["奥威拓"] = SISC_IPC_AWT;                              // 奥威拓

        m_OEMXMFacMap["君安安"] = SISC_IPC_JAA;                      // 君安安
        m_OEMXMFacMap["鑫捷讯"] = SISC_IPC_XJX;                            // 鑫捷讯
        m_OEMXMFacMap["华洋"] = SISC_IPC_HY;                                // 华洋
        m_OEMXMFacMap["巧芯"] = SISC_IPC_QX;                              // 巧芯

        m_OEMXMFacMap["邮科"] = SISC_IPC_YK;                      // 邮科
        m_OEMXMFacMap["居安宝"] = SISC_IPC_JAB;                            // 居安宝
        m_OEMXMFacMap["南中"] = SISC_IPC_NZ;                                // 南中
        m_OEMXMFacMap["龙之净"] = SISC_IPC_LZJ;                              // 龙之净

        m_OEMXMFacMap["世星"] = SISC_IPC_SX;                      // 世星
        m_OEMXMFacMap["玮特视"] = SISC_IPC_WTS;                            // 玮特视
        m_OEMXMFacMap["安之讯"] = SISC_IPC_AZX;                                // 安之讯
        m_OEMXMFacMap["百科博"] = SISC_IPC_BKB;                              // 百科博

        m_OEMXMFacMap["大唐华强"] = SISC_IPC_DTHQ;                      // 大唐华强
        m_OEMXMFacMap["海伊"] = SISC_IPC_HAIY;                            // 海伊
        m_OEMXMFacMap["安联锐视"] = SISC_IPC_ALKJ;                                // 安联锐视
        m_OEMXMFacMap["旭霆科技"] = SISC_IPC_XTKJ;                              // 旭霆科技

        m_OEMXMFacMap["华翔国际"] = SISC_IPC_HXGJ;                      // 华翔国际
        m_OEMXMFacMap["尔佳"] = SISC_IPC_ERJIA;                            // 尔佳
        m_OEMXMFacMap["宏为视讯"] = SISC_IPC_HWSX;                                // 宏为视讯
        m_OEMXMFacMap["欣荣泉"] = SISC_IPC_XINGRQ;                              // 欣荣泉

        m_OEMXMFacMap["谐美电子"] = SISC_IPC_XMDZ;                      // 谐美电子
        m_OEMXMFacMap["恒润睿视"] = SISC_IPC_AOKS;                            // 澳科森
        m_OEMXMFacMap["恒润睿视"] = SISC_IPC_HRRS;                                // 恒润睿视
        m_OEMXMFacMap["安嘉科技"] = SISC_IPC_AJKJ;                              // 安嘉科技

        m_OEMXMFacMap["尼安科技"] = SISC_IPC_NAKJ;                      // 尼安科技
        m_OEMXMFacMap["蓝图视讯"] = SISC_IPC_LTSX;                            // 蓝图视讯
        m_OEMXMFacMap["威迪斯"] = SISC_IPC_WEIDS;                                // 威迪斯
        m_OEMXMFacMap["深圳市本德"] = SISC_IPC_SZSBD;                              // 深圳市本德

        m_OEMXMFacMap["印梦科技"] = SISC_IPC_YMKJ;                      // 印梦科技
        m_OEMXMFacMap["锐郎特"] = SISC_IPC_RUILT;                            // 锐郎特
        m_OEMXMFacMap["英飞拓"] = SISC_IPC_YINGFT;                                // 英飞拓
        m_OEMXMFacMap["龙安天下"] = SISC_IPC_LATX;                              // 龙安天下

        m_OEMXMFacMap["维邦电子"] = SISC_IPC_WBDZ;                      // 维邦电子
        m_OEMXMFacMap["新锐华科"] = SISC_IPC_XRHK;                            // 新锐华科
        m_OEMXMFacMap["点博电子"] = SISC_IPC_DBDZ;                                // 点博电子
        m_OEMXMFacMap["飞鸿信"] = SISC_IPC_FEIHX;                              // 飞鸿信

        m_OEMXMFacMap["超本乐"] = SISC_IPC_CHAOBL;                      // 超本乐
        m_OEMXMFacMap["宇烁商贸"] = SISC_IPC_YSSM;                            // 宇烁商贸
        m_OEMXMFacMap["帕尼柯"] = SISC_IPC_PANK;                                // 帕尼柯
        m_OEMXMFacMap["宝视佳"] = SISC_IPC_BAOJS;                              // 宝视佳

        m_OEMXMFacMap["科兰"] = SISC_IPC_KELAN;                      // 科兰
        m_OEMXMFacMap["北视通"] = SISC_IPC_BEIST;                            // 北视通
        m_OEMXMFacMap["科达科技"] = SISC_IPC_KDKJ;                                // 科达科技
        m_OEMXMFacMap["山本智能"] = SISC_IPC_SBZN;                              // 山本智能

        m_OEMXMFacMap["精达锐"] = SISC_IPC_JINGDR;                      // 精达锐
        m_OEMXMFacMap["杭州圣尚"] = SISC_IPC_HZSS;                            // 杭州圣尚
        m_OEMXMFacMap["汉和东方"] = SISC_IPC_HTDF;                                // 汉和东方
        m_OEMXMFacMap["星宝威视"] = SISC_IPC_XBWS;                              // 星宝威视

        m_OEMXMFacMap["北京英康嘉业"] = SISC_IPC_BJYKJY;                      // 北京英康嘉业
        m_OEMXMFacMap["广州市泰豪"] = SISC_IPC_GZSTH;                            // 广州市泰豪
        m_OEMXMFacMap["深圳市安裕"] = SISC_IPC_SZSAY;                                // 深圳市安裕
        m_OEMXMFacMap["广州左田"] = SISC_IPC_GZZT;                              // 广州左田
	}
	
	// 海康OEM
	{
		m_OEMHIKFacMap["广东领域"] = SISC_IPC_GUANGDONGLINYU;

        m_OEMHIKFacMap["旷视安"] = SISC_IPC_KUANGSHIAN;
		m_OEMHIKFacMap["广州宏翔"] = SISC_IPC_GZHX;

		m_OEMHIKFacMap["宝欣盛"] = SISC_IPC_BAOXINGSHENG;
		m_OEMHIKFacMap["立安达OEM"] = SISC_IPC_LANDAOEMHK;
		m_OEMHIKFacMap["西安海方"] = SISC_IPC_XIANHAIFANG;
		m_OEMHIKFacMap["北京正方时代"] = SISC_IPC_BEIJINGZHENGFANG;
		m_OEMHIKFacMap["泰康伟业OEM海康"] = SISC_IPC_TAIKANGWEIYEOEMHK;
		m_OEMHIKFacMap["天敏"] = SISC_IPC_TIANMIN;
		m_OEMHIKFacMap["科恩"] = SISC_IPC_KEEN;
		m_OEMHIKFacMap["安居鸟"] = SISC_IPC_ANJULIAO;
		m_OEMHIKFacMap["北京益融冠世"] = SISC_IPC_YIRONGGUANSHI;
		m_OEMHIKFacMap["东大金智平台"] = SISC_IPC_DONGDAJIZHI;
		m_OEMHIKFacMap["GE硬盘录像机"] = SISC_IPC_GERECORDER;
		m_OEMHIKFacMap["广州米卡61系列"] = SISC_IPC_MIKA61;
		m_OEMHIKFacMap["广州米卡8081系列NVR"] = SISC_IPC_MIKA8081;
		m_OEMHIKFacMap["恒忆"] = SISC_IPC_HENGYI;
		m_OEMHIKFacMap["深圳八安"] = SISC_IPC_BAAN;
		m_OEMHIKFacMap["深圳百汇"] = SISC_IPC_BAIHUI;
		m_OEMHIKFacMap["深圳海视安"] = SISC_IPC_HAISHIAN;
		m_OEMHIKFacMap["深圳巨罦"] = SISC_IPC_JUFU;
		m_OEMHIKFacMap["深圳赛清"] = SISC_IPC_SAIQING;
		m_OEMHIKFacMap["深圳兴科安"] = SISC_IPC_XINGKEAN;
		m_OEMHIKFacMap["天天佑"] = SISC_IPC_TIANTIANYOU;
	}
	
	// 沃仕达OEM
	{
		m_OEMWSDFacMap["鑫鹏安防"] = SISC_IPC_XP;
	}
	
	// 九安光电OEM
	{
		m_OEMJiuAnFacMap["泰康伟业"] = SISC_IPC_TAIKANGWEIYE;
	}
	
	// 东阳国际OEM
	{
		m_OEMDongYangFacMap["宏康威视"] = SISC_IPC_HONGKANGWEISHI;
	}
	
	// 中维OEM
	{
		m_OEMZhongWeiFacMap["狮安联讯"] = SISC_IPC_SALX;
		m_OEMZhongWeiFacMap["广州利凌"] = SISC_IPC_GZLL;
		m_OEMZhongWeiFacMap["中田安保"] = SISC_IPC_ZHONGTIANANBAO;
		m_OEMZhongWeiFacMap["吉锐"] = SISC_IPC_JIRUI;
		m_OEMZhongWeiFacMap["华邦海视"] = SISC_IPC_HUABANGHAISHI;
	}
}

void videoserverFactory::addFakeFactory(IVideoServerFactory *pFactory)
{
	switch(pFactory->factory())
	{
		case SISC_IPC_DIZHIPU:
		{
			OEMFacMap::iterator itr = m_OEMXMFacMap.begin();
			for(itr; itr !=m_OEMXMFacMap.end(); itr++)
			{
				IVideoServerFactory* pOEMFactory = new OEMFactory((DeviceFactory)itr->second, true, (char *)itr->first.c_str(), pFactory);
				if (nullptr != pFactory)
				{
					videoserverFactory* pvsf = new videoserverFactory(pOEMFactory);
					s_Factorys.push_back(pvsf);
				}
			}
			
			break;
		}
		case SISC_IPC_HIKVISION:
		{
			OEMFacMap::iterator itr = m_OEMHIKFacMap.begin();
			for(itr; itr !=m_OEMHIKFacMap.end(); itr++)
			{
				IVideoServerFactory* pOEMFactory = new OEMFactory((DeviceFactory)itr->second, true, (char *)itr->first.c_str(), pFactory);
				if (nullptr != pFactory)
				{
					videoserverFactory* pvsf = new videoserverFactory(pOEMFactory);
					s_Factorys.push_back(pvsf);
				}
			}
			
			break;
		}
		case SISC_IPC_WSD:
		{
			OEMFacMap::iterator itr = m_OEMWSDFacMap.begin();
			for(itr; itr !=m_OEMWSDFacMap.end(); itr++)
			{
				IVideoServerFactory* pOEMFactory = new OEMFactory((DeviceFactory)itr->second, true, (char *)itr->first.c_str(), pFactory);
				if (nullptr != pFactory)
				{
					videoserverFactory* pvsf = new videoserverFactory(pOEMFactory);
					s_Factorys.push_back(pvsf);
				}
			}
			
			break;
		}
		case SISC_IPC_JIUAN:
		{
			OEMFacMap::iterator itr = m_OEMJiuAnFacMap.begin();
			for(itr; itr !=m_OEMJiuAnFacMap.end(); itr++)
			{
				IVideoServerFactory* pOEMFactory = new OEMFactory((DeviceFactory)itr->second, true, (char *)itr->first.c_str(), pFactory);
				if (nullptr != pFactory)
				{
					videoserverFactory* pvsf = new videoserverFactory(pOEMFactory);
					s_Factorys.push_back(pvsf);
				}
			}
			
			break;
		}
		case SISC_IPC_DOANGYANG:
		{
			 OEMFacMap::iterator itr = m_OEMDongYangFacMap.begin();
			for(itr; itr !=m_OEMDongYangFacMap.end(); itr++)
			{
				IVideoServerFactory* pOEMFactory = new OEMFactory((DeviceFactory)itr->second, true, (char *)itr->first.c_str(), pFactory);
				if (nullptr != pFactory)
				{
					videoserverFactory* pvsf = new videoserverFactory(pOEMFactory);
					s_Factorys.push_back(pvsf);
				}
			}
			
			break;
		}	
		case SISC_IPC_ZHONGWEI:
		{
			OEMFacMap::iterator itr = m_OEMZhongWeiFacMap.begin();
			for(itr; itr !=m_OEMZhongWeiFacMap.end(); itr++)
			{
				IVideoServerFactory* pOEMFactory = new OEMFactory((DeviceFactory)itr->second, true, (char *)itr->first.c_str(), pFactory);
				if (nullptr != pFactory)
				{
					videoserverFactory* pvsf = new videoserverFactory(pOEMFactory);
					s_Factorys.push_back(pvsf);
				}
			}
			
			break;
		}	
		default:
			break;
	}
}

//<<<<<<<<<<<<<add by zhangyaofa 2016/5/19
OEMFacMap videoserverFactory::GetFakeFactory(int nDeviceFactory)
{
	switch (nDeviceFactory)
	{
	case SISC_IPC_DIZHIPU:
		return m_OEMWSDFacMap;
	case SISC_IPC_HIKVISION:
	case SISC_IPC_WSD:
	case SISC_IPC_JIUAN:
	case SISC_IPC_DOANGYANG:
	case SISC_IPC_ZHONGWEI:
	default:
		break;
	}
}
//>>>>>>>>>>>add end

videoserverFactory* videoserverFactory::getFactory(DeviceFactory f)
{
    getFactorys();
    std::lock_guard<std::recursive_mutex> lock(s_mutexFactorys);
    for (int index = 0; index < s_Factorys.size(); index++)
    {
        if (s_Factorys[index]->factory() == f)
        {
            return s_Factorys[index];
        }
    }
    return nullptr;
}



void videoserverFactory::releaseVideoServerFactory()
{
    std::lock_guard<std::recursive_mutex> lock(s_mutexFactorys);
    for (int i = 0; i < s_Factorys.size(); i++)
    {
        delete s_Factorys[i];
    }
    s_Factorys.clear();
}

videoserverFactory::videoserverFactory(IVideoServerFactory *p)
    :  mpFactory(p), mInit(false)
{
	initOEMFacList();
    sheInit();
}

videoserverFactory::~videoserverFactory()
{
    mpFactory->destroy();
}

std::shared_ptr<videoserver> videoserverFactory::create(bool nullSver)
{
    if (!mInit)
    {        
        mInit = sheInit();
        mInit = true;
    }
    std::shared_ptr<videoserver> p;
    if (mInit)
    {        
        std::lock_guard<std::recursive_mutex> lock(m_mutexService);
        for (auto it =  m_vcServices.begin(); it != m_vcServices.end(); it++)
        {
            if ((*it)->isRelease())
            {   
                if ((*it)->isNull())
                {
                    if (nullSver || nullptr == mpFactory)
                    {                       
                        p = *it;
                        break;
                    }
                }
                else
                {
                    if (!nullSver && nullptr != mpFactory)
                    {                       
                        p = *it;
                        break;
                    }
                }
            }
        }

        if (!p)
        {
            std::vector< std::shared_ptr<videoserver> > s_vcServices;
            if (nullptr == mpFactory || nullSver)
            {                
                p = std::shared_ptr<videoserver>(new videoserver(nullptr, this));
            }
            else{
                IVideoServer* pvr = mpFactory->create();               
                if (pvr != nullptr)
                {
                   
                    p = std::shared_ptr<videoserver>(new videoserver(pvr, this));
                }
            }
        }
    }

    if (p)
    {       
        p->setRelease(false);
    }

    return p;
}
void videoserverFactory::destroy(videoserver* p){
    std::lock_guard<std::recursive_mutex> lock(m_mutexService);
    for (auto it = m_vcServices.begin(); it != m_vcServices.end(); it++)
    {
        if ((*it).get() == p)
        {
            m_vcServices.erase(it);
            return;
        }
    }
}
IVideoServer* videoserverFactory::createDerect()
{
    if (!mInit)
    {
        mInit = sheInit();
        mInit = true;
    }

    if (mInit)
    {
        if (nullptr == mpFactory)
        {
            return nullptr;
        }

        return mpFactory->create();
    }

    return nullptr;
}

PlayBackPosCaculator::PlayBackPosCaculator()
{
    _time64(&mStartPlayTime);
}

int PlayBackPosCaculator::getPos()
{
    if (mPlaySeconds <= 0)
    {
        return 100;
    }

    __time64_t nowPlayTime;
    _time64(&nowPlayTime);

    __time64_t pos =  (nowPlayTime - mStartPlayTime) * 100 / mPlaySeconds;
    if (pos > 100)
    {
        return 100;
    }

    return pos;
}

void PlayBackPosCaculator::setPos(unsigned int pos)
{
    if (mPlaySeconds <= 0)
    {
        return;
    }

    __time64_t nowPlayTime;
    _time64(&nowPlayTime);

    mStartPlayTime = nowPlayTime - (pos * mPlaySeconds) / 100;
}
__int64 DownloadPosCaculator::getFileSize(const std::string& sFile)
{
    QFile f(QString::fromLocal8Bit(sFile.c_str()));
    if (f.exists())
    {
        return f.size();
    }
    else
    {
        return 0;
    }
}
DownloadPosCaculator::DownloadPosCaculator()
{
    mTotalSize = 0;
}

int DownloadPosCaculator::getPos(__int64& totalSize, __int64& currentSize)
{
    currentSize = getFileSize(mSaveFile);
    totalSize = mTotalSize;
    if (totalSize > 0 && totalSize >= currentSize)
    {
        return currentSize * 100 / totalSize;
    }

    return 100;
}
videoserver* videoserver::getServerByPort(int port)
{
    return nullptr;
}
videoserver::videoserver(IVideoServer *p, videoserverFactory *f) :
    mpServer(p), mpFactory(f), mStop(false), mpThrDowload(nullptr)
{
    m_bRelease = true;
}

videoserver::~videoserver()
{
    std::lock_guard<std::recursive_mutex> lockeThread(mMutexThread);
    if (mpThrDowload != nullptr)
    {
        mStop = true;
        mpThrDowload->join();
        delete mpThrDowload;
    }
    if (nullptr != mpServer)
    {
        mpServer->destroy();
        mpServer = nullptr;
    }
     

}

//用于删除厂商时登录和析构
void videoserver::remove()
{
	delete this;
}
void videoserver::destroy()
{
    
}
std::shared_ptr<videoserver>  videoserver::clone()
{
    auto pNewServer = mpFactory->create(true);
    if (nullptr == mpServer || !pNewServer)
    {
        return pNewServer;
    }
    
    IVideoServer* p = mpServer->clone();
    if (p != nullptr)
    {
        pNewServer->mpServer = p;
		bool bStop = false;
        if (pNewServer->login(mpLoginInfo, &bStop))
        {
            return pNewServer;
        }
        else
        {
            p->destroy();
            pNewServer->mpServer = nullptr;
            pNewServer->setRelease(true);
        }
    }

    return std::shared_ptr<videoserver>();
}
videoserver* videoserver::cloneDerect()
{
    if (nullptr == mpServer)
    {
        return new videoserver(nullptr, mpFactory);
    }

    IVideoServer* p = mpServer->clone();
    if (p != nullptr)
    {
        return new videoserver(p, mpFactory);
    }

    return nullptr;
}

bool videoserver::PlayBackByRecordFile(RecordFile& file, QWidget &w, play_handle_t& playbackHandle)
{

    if (nullptr != mpServer)
    {
        if (!mpServer->PlayBackByRecordFile(file, (HWND)w.winId(), playbackHandle))
        {
            this->mLastError = mpServer->getLastError();
            return false;
        }

        mMpPlayBackPosCaculators[playbackHandle].setPlaySeconds(file.endTime - file.beginTime);
        return true;
    }

    return false;

}

bool videoserver::SetPlayBack(play_handle_t playbackHandle, qint32 pos)
{

    if (nullptr != mpServer)
    {
        bool r = mpServer->SetPlayBack(playbackHandle, pos);
        if (!r)
        {
            addLog("SetPlayBack", __LINE__);
        }
        else
        {
            mMpPlayBackPosCaculators[playbackHandle].setPos(pos);
        }

        return r;
    }

    return false;

}

bool videoserver::getPlayBackPos(play_handle_t playbackHandle, qint32& pos)
{
    if (nullptr != mpServer)
    {
        bool r = mpServer->getPlayBackPos(playbackHandle, &pos);
        if (!r)
        {
            pos = mMpPlayBackPosCaculators[playbackHandle].getPos();
            return true;
        }
        return r;
    }

    return false;

}

bool videoserver::StopPlayBack(play_handle_t playbackHandle, int mPause)
{

    if (nullptr != mpServer)
    {
        bool r = mpServer->StopPlayBack(playbackHandle, mPause);
        if (!r)
        {
            addLog("StopPlayBack", __LINE__);
        }
        else
        {
            mMpPlayBackPosCaculators.erase(playbackHandle);
        }

        return r;
    }

    return false;

}


void getCommonFactorys(std::vector<videoserverFactory *>& factorys)
{
    factorys.clear();
    XmlSettings setings("cf");
    auto fs = videoserverFactory::getFactorys();
    std::vector< std::pair<int, int> > vcSorts;
    for (auto it = fs.begin(); it != fs.end(); it++)
    {
        videoserverFactory* pF = (*it);
		factorys.push_back(pF);
//         vcSorts.push_back(std::make_pair(pF->factory(),
//                                          setings.value(QString::number(pF->factory()), 0).toInt()));
    }
//     std::stable_sort(vcSorts.begin(), vcSorts.end(),
//               [](const std::pair<int, int>& f, const std::pair<int, int>& s)
//     {
//         return f.second > s.second;
//     });

//     for (int i = 0; i < vcSorts.size(); i++)
//     {
//         factorys.push_back((DeviceFactory)vcSorts[i].first);
//     }
}

void plusCommonFactorySort(const std::vector<DeviceFactory>& factories, int index)
{
    if (index >= factories.size())
    {
        return;
    }

    XmlSettings setings("cf");
    int nSort = setings.value(QString::number(factories[index]), 0).toInt() + 1;
    setings.setValue(QString::number(factories[index]), nSort);
}

bool videoserver::login(std::shared_ptr<LoginServerInfo> p, bool *pbStop)
{
	if (!p || *pbStop)
    {
        Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, error:%4").arg(__FILE__)
            .arg(__FUNCTION__).arg(__LINE__).arg(*pbStop));
        return false;
    }

    mpLoginInfo = p;


    if (SISC_IPC_UNDEFINE == mpFactory->factory())
    {
        Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, error:%4").arg(__FILE__)
            .arg(__FUNCTION__).arg(__LINE__).arg(SISC_IPC_UNDEFINE));
		std::vector<videoserverFactory *> factorys;
        getCommonFactorys(factorys);
        int nPort = 0;
        QString sUser;
        QString sPasswords;
		std::shared_ptr<LoginServerInfo> tmpLoginfo = std::make_shared<LoginServerInfo>();
        for(int i = 0; i < factorys.size(); i++)
        {
			if (*pbStop)
			{
				return false;
			}
			
			videoserverFactory *f = factorys[i];
            if (f == nullptr)
            {
                Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, error:f == nullptr").arg(__FILE__)
                    .arg(__FUNCTION__).arg(__LINE__));
                continue;
            }

            if (SISC_IPC_UNDEFINE == f->factory() || f->IsOEMFac())
			{
                Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, oem factory:%4").arg(__FILE__)
                    .arg(__FUNCTION__).arg(__LINE__).arg(f->name()));
				continue;
			}

            IVideoServer* pServer = f->createDerect();
            if (pServer == nullptr)
            {
                Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, error:f->createDerect == nullptr").arg(__FILE__)
                    .arg(__FUNCTION__).arg(__LINE__));
                continue;
            }

            if (p->port == 0)
            {
                nPort = f->port();
            }
            else
            {
                nPort = p->port;
            }

            if (p->user == UNDEFIN_DEVICE_DEFAULT_USER)
            {
                sUser = f->defaultUser();
            }
            else
            {
                sUser = p->user;
            }

            if (p->password == UNDEFIN_DEVICE_DEFAULT_PASSWORD)
            {
                sPasswords = f->defaultPasswords();
            }
            else
            {
                sPasswords = p->password;
            }
					
            if (sheLogin(pServer, p->ip.toStdString(), nPort, sUser.toStdString(), sPasswords.toStdString()))
            {
				Log::instance().AddLog(QString("OK!") + mpFactory->name() + "," + f->name() + " " + p->ip);
                mpServer = pServer;
                this->mpFactory = f;
                p->factory = f->factory();
				p->name = f->name() + "(" + p->ip + ")";
                p->user = sUser;
                p->password = sPasswords;
                p->port = nPort;
				mpLoginInfo = p;
				mpLoginInfo->ip = p->ip;
                return true;
            }
            else
            {
				Log::instance().AddLog(QString("Failed!") + mpFactory->name() + "," + f->name() + " " + p->ip);
                pServer->destroy();
            }
        }

        mLastError = "无法识别的设备!";
        return false;
    }

	if (p->user == UNDEFIN_DEVICE_DEFAULT_USER)
	{
		p->user = mpFactory->defaultUser();
	}

	if (p->password == UNDEFIN_DEVICE_DEFAULT_PASSWORD)
	{
		p->password = mpFactory->defaultPasswords();
	}

    if (sheLogin(mpServer, p->ip.toStdString(), p->port, p->user.toStdString(), p->password.toStdString()))
    {
        return true;
    }
    return false;
}

//<<<<<<<<<<<<<add by zhangyaofa 2016/5/18
bool videoserver::loginByBroadcast(int nFactory, std::shared_ptr<LoginServerInfo> p, bool *pbStop)
{
	if (!p || *pbStop)
	{
		Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, error:%4").arg(__FILE__)
			.arg(__FUNCTION__).arg(__LINE__).arg(*pbStop));
		return false;
	}

	std::vector<videoserverFactory *> factorys;
	getCommonFactorys(factorys);
	int nPort = 0;
	QString sUser;
	QString sPasswords;

	for (int i = 0; i < factorys.size(); i++)
	{
		if (*pbStop)
		{
			return false;
		}

		videoserverFactory *f = factorys[i];
		if (f == nullptr)
		{
			Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, error:f == nullptr").arg(__FILE__)
				.arg(__FUNCTION__).arg(__LINE__));
			continue;
		}

		if (SISC_IPC_UNDEFINE == f->factory() || f->IsOEMFac())
		{
			Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, oem factory:%4").arg(__FILE__)
				.arg(__FUNCTION__).arg(__LINE__).arg(f->name()));
			continue;
		}

		if (f->factory() != nFactory)
		{
			continue;
		}

		//auto pServer = f->create();
		IVideoServer* pServer = f->createDerect();
		if (pServer == nullptr)
		{
			Log::instance().AddLog(QString("File:%1, Function:%2, Line:%3, error:f->createDerect == nullptr").arg(__FILE__)
				.arg(__FUNCTION__).arg(__LINE__));
			continue;
		}

		if (p->name.trimmed().isEmpty())
		{
			p->name = QString("%1(%2)").arg(f->name()).arg(p->ip);
		}

		if (p->port == 0)
		{
			nPort = f->port();
		}
		else
		{
			nPort = p->port;
		}

		if (p->user == UNDEFIN_DEVICE_DEFAULT_USER)
		{
			sUser = f->defaultUser();
		}
		else
		{
			sUser = p->user;
		}

		if (p->password == UNDEFIN_DEVICE_DEFAULT_PASSWORD)
		{
			sPasswords = f->defaultPasswords();
		}
		else
		{
			sPasswords = p->password;
		}

		if (sheLogin(pServer, p->ip.toStdString(), nPort, sUser.toStdString(), sPasswords.toStdString()))
		{
			Log::instance().AddLog(QString("OK!") + mpFactory->name() + "," + f->name() + " " + p->ip);
			mpServer = pServer;
			this->mpFactory = f;
			p->factory = f->factory();
			p->name = f->name() + "(" + p->ip + ")";
			p->user = sUser;
			p->password = sPasswords;
			p->port = nPort;
			mpLoginInfo = p;
			mpLoginInfo->ip = p->ip;
			return true;
		}
		else
		{
			Log::instance().AddLog(QString("Failed!") + mpFactory->name() + "," + f->name() + " " + p->ip);
			pServer->destroy();

			return false;
		}
		
	}	

	return false;
}
//>>>>>>>>>>>add end


void videoserver::DealDownLoadCallback(download_handle_t h, qint64 totalSize, qint64 size, bool failed)
{
    if (nullptr == mpServer)
    {
        return;
    }

    std::lock_guard<std::recursive_mutex> locker(mMutexEventRecievers);
    if (failed)
    {
        size = 0;
    }
    if (mEventReceivers.find(h) != mEventReceivers.end() && NULL != mEventReceivers[h])
    {

       QCoreApplication::postEvent(mEventReceivers[h], new downloadEvent(this, totalSize, size, failed));
    }

    if (failed || totalSize <= size)
    {
        if (mEventReceivers.find(h) != mEventReceivers.end() && NULL != mEventReceivers[h])
        {
            stopDownload(mEventReceivers[h]);
        }
        else
        {
            mpServer->stopDownload(h);
        }
    }
}

void videoserver::SendDownLoadHeartbeat(download_handle_t h)
{
    std::lock_guard<std::recursive_mutex> locker(mMutexEventRecievers);

    if (mEventReceivers.find(h) != mEventReceivers.end() && NULL != mEventReceivers[h])
    {
        QCoreApplication::postEvent(mEventReceivers[h], new heartbeatEvent(this));
    }
}

void videoserver::DealDisconnectCallback()
{
    std::lock_guard<std::recursive_mutex> locker(mMutexEventRecievers);
    for (std::map<download_handle_t, QObject*>::iterator it = mEventReceivers.begin(); it != mEventReceivers.end();
         it++)
    {
        if (NULL != it->second)
        {
            QCoreApplication::postEvent(it->second, new disconnectEvent(this));
        }
    }
}

void videoserver::DealReconnectCallback()
{
    std::lock_guard<std::recursive_mutex> locker(mMutexEventRecievers);
    for (std::map<download_handle_t, QObject*>::iterator it = mEventReceivers.begin();
         it != mEventReceivers.end();
         it++)
    {
        if (NULL != it->second)
        {
            QCoreApplication::postEvent(it->second, new reconnectEvent(this));
        }
    }
}


bool videoserver::logout()
{
    if (!stopDownloadAll())
    {
        return false;
    }

    if (nullptr != mpServer)
    {
        if (!mpServer->logout())
        {
            return false;
        }

        return true;
    }

    return true;

}
bool videoserver::reLogin(){
    //this->logout();
    return sheLogin(mpServer, mpLoginInfo->ip.toStdString(), mpLoginInfo->port, mpLoginInfo->user.toStdString(), mpLoginInfo->password.toStdString());
}
bool videoserver::GetRecordFileList(std::vector<RecordFile>& files, /*int nChannelId */ std::vector<int>& channelVec, const QDateTime& timeStart, const QDateTime& timeEnd)
{

    if (nullptr != mpServer)
    {

        QTime tmS(timeStart.time());
        QTime tmE(timeEnd.time());
        QDate dtE(timeStart.date());
        const int DAYS = 3;
        for (QDate start(timeStart.date()); start <= timeEnd.date(); start = start.addDays(DAYS))
        {
            std::vector<RecordFile> daysFiles;
            if (start == timeStart.date())
            {
                tmS = timeStart.time();
            }
            else{
                tmS = QTime(0, 0);
            }
            dtE = start.addDays(DAYS - 1);
            if (dtE >= timeEnd.date())
            {
                dtE = timeEnd.date();
                tmE = timeEnd.time();
            }
            else{
                tmE = QTime(23, 59);
            }
            bool r = mpServer->GetRecordFileList(daysFiles, channelVec, QDateTime(start, tmS).toTime_t(), QDateTime(dtE, tmE).toTime_t());
            if (!r)
            {
                return false;
            }

            for (int i = 0; i < daysFiles.size(); i++)
            {
                files.push_back(daysFiles[i]);
            }
            
        }
		
        std::stable_sort(files.begin(), files.end(), [](const RecordFile& a, const RecordFile& b){
            return a.channel < b.channel;
        });

        return true;
    }

    return false;

}

bool videoserver::GetRecordFileListZone(std::vector<RecordFile>& files, /*int nChannelId*/std::vector<int>& channelVec,
                           const QDateTime& timeStart, const QDateTime& timeEnd)
{
    for (QDate start(timeStart.date()); start <= timeEnd.date(); start = start.addDays(1))
    {
        std::vector<RecordFile> oneDayFiles;
		if (GetRecordFileList(oneDayFiles, channelVec, QDateTime(start, timeStart.time()),
                              QDateTime(start, timeEnd.time())))
        {
            for (int i = 0; i < oneDayFiles.size(); i++)
            {
                files.push_back(oneDayFiles[i]);
            }
        }
        else
        {
            return false;
        }
    }

    return true;
}
#define SLEEP_MILLISECONDE                      500
#define DISCONNECT_TIME                         1
#define CONNECTD_TIME                           20
bool videoserver::downLoad(const QString& saveFileName, const RecordFile& file, QObject* eventReceiver)
{
    if (nullptr == mpServer)
    {
        return false;
    }

    if (DownloadPosCaculator::getFileSize(saveFileName.toLocal8Bit().data()) >= file.size){
        QCoreApplication::postEvent(eventReceiver, new downloadEvent(this, file.size, file.size, false));
        return true;
    }

    download_handle_t hdl;
    try
    {
        if (shedownLoadByRecordFile(saveFileName.toLocal8Bit().data(), file, hdl))
		{
            std::lock_guard<std::recursive_mutex> locker(mMutexEventRecievers);
            std::lock_guard<std::recursive_mutex> lockeThread(mMutexThread);
            mMpDownloadPosCaculators[hdl].init(file.size, saveFileName.toLocal8Bit().data());
            mEventReceivers[hdl] = eventReceiver;
            if (nullptr == mpThrDowload)
            {
                mpThrDowload = new std::thread([&](videoserver* pThis)
                {
                    int mTimes = 0;
                    int totalTime = 20;
                    bool isconnect = false;
                    qint64  totalSize = 0;
                    qint64 currentSize = 0;
                    bool failed = false;

                    while (!mStop)
                    {
                        mTimes = mTimes + 2;
                        QThread::msleep(2000);
                        if (mTimes >= totalTime)
                        {
                            isconnect = WindowUtils::isConnecteTo(pThis->ip());
                            if (!isconnect)
                            {
                                //Log::instance().AddLog(QString("################### 05"));
                                DealDisconnectCallback();
                                //Log::instance().AddLog(QString("################### 06"));
                                totalTime = DISCONNECT_TIME;
                            }
                            else if (totalTime == DISCONNECT_TIME)
                            {
                                isconnect = pThis->reLogin();
                            }
                            if (isconnect)
                            {
                                totalTime = CONNECTD_TIME;
                            }
                            mTimes = 0;
                        }
                        if (!isconnect)
                        {
                            continue;
                        }
                         std::lock_guard<std::recursive_mutex> locker(mMutexEventRecievers);
                         for (std::map<download_handle_t, QObject*>::iterator it = mEventReceivers.begin();
                               it != mEventReceivers.end(); /*it++*/)
                         {
							 std::map<download_handle_t, QObject*>::iterator itTmp = it;
							 it++;
							 if (pThis->mpServer->getDownloadPos(itTmp->first, &totalSize, &currentSize, &failed))
                             {
								 DealDownLoadCallback(itTmp->first, totalSize, currentSize, failed);
                             }
                             else
                             {
							     pThis->mMpDownloadPosCaculators[itTmp->first].getPos(totalSize, currentSize);
								 DealDownLoadCallback(itTmp->first, totalSize, currentSize, failed);
                             }
                         }

                    }
                }, this);
            }

            return true;
        }
        else
        {
            this->mLastError = mpServer->getLastError();
            Log::instance().AddLog(QString("%1:%2-%3  %4(%5)").arg(__FILE__)
                .arg(__LINE__).arg(this->mpFactory->name()).arg("download failed:").arg(getLastError()));
            return false;
        }
    }
    catch(...)
    {
		Log::instance().AddLog(QString("################### exception"));
        return false;
    }
}

bool videoserver::stopDownload(QObject* eventReceiver)
{
    if (nullptr != mpServer)
    {
        std::lock_guard<std::recursive_mutex> locker(mMutexEventRecievers);
        for (std::map<download_handle_t, QObject*>::iterator it = mEventReceivers.begin();
             it != mEventReceivers.end(); it++)
        {
            if (it->second == eventReceiver)
            {
				mpServer->stopDownload(it->first);
				mMpDownloadPosCaculators.erase(it->first);
				it = mEventReceivers.erase(it);
				return true;
//                 if (mpServer->stopDownload(it->first))
// 				{
// 					mMpDownloadPosCaculators.erase(it->first);
// 					it = mEventReceivers.erase(it);
//                     return true;
//                 }
// 
//                 return false;
            }
        }
    }

    return true;
}

bool videoserver::stopDownloadAll()
{
    if (nullptr == mpServer)
    {
        return true;
    }
    std::lock_guard<std::recursive_mutex> locker(mMutexEventRecievers);
    for (std::map<download_handle_t, QObject*>::iterator it = mEventReceivers.begin();
         it != mEventReceivers.end(); /*it++*/)
    {
        if (!mpServer->stopDownload(it->first))
        {
            return false;
        }
        else
        {
            it = mEventReceivers.erase(it);
        }
    }
    mStop = true;
    mpThrDowload->join();
    delete mpThrDowload;
    mpThrDowload = nullptr;
    return true;
}

QString videoserver::getChannelName(int channel)
{
    if (m_channels.find(channel) != m_channels.end())
    {
         QString s = QString::fromLocal8Bit(m_channels.at(channel).c_str());
         if (s.isEmpty())
         {
             s = QString::fromLocal8Bit("通道%1").arg(channel);
         }
         s.replace(" ", "");
         return s;
    }

    return "";
}
QString videoserver::getFileName(const RecordFile &f)
{
    return f.name.c_str();
}
void videoserver::addLog(const char* sLog, int nLine)
{
    qDebug() << sLog;
    Log::instance().AddLog(QString("%1:%2-%3  %4(%5)").arg(__FILE__)
        .arg(nLine).arg(this->mpFactory->name()).arg(sLog).arg(getLastError()));
}

bool videoserver::shedownLoadByRecordFile(const std::string& saveFileName, const RecordFile& file, download_handle_t& hdl)
{
    if (nullptr == mpServer)
    {
        return false;
    }
    SHE_BEGING
        bool r = mpServer->downLoadByRecordFile(saveFileName.c_str(), file, hdl);
    if (!r)
    {
        // addLog("downLoadByRecordFile", __LINE__);
        return false;
    }
    std::cout << "she try end" << std::endl;
    return r;
    SHE_END_RETURN_FALSE
}
bool videoserver::shegetDownloadPos(download_handle_t h, qint64* totalSize, qint64* currentSize, bool* failed)
{
    if (nullptr == mpServer)
    {
        return false;
    }
    SHE_BEGING

        bool r = mpServer->getDownloadPos(h, totalSize, currentSize, failed);
    std::cout << "she try end" << std::endl;
    if (!r)
    {
        addLog("getDownloadPos", __LINE__);
    }
    return r;
    SHE_END_RETURN_FALSE
}
bool videoserver::shestopDownload(download_handle_t h)
{
    if (nullptr == mpServer)
    {
        return true;
    }
    SHE_BEGING
        bool r = mpServer->stopDownload(h);
    std::cout << "she try end" << std::endl;
    if (!r)
    {
        addLog("shestopDownload", __LINE__);
    }
    return r;

    SHE_END_RETURN_FALSE
}

bool videoserver::sheLogin(IVideoServer* pServer, const std::string& IP, int port, const std::string& user, const std::string& password)
{
    if (nullptr == pServer)
    {
        return false;
    }

	
    SHE_BEGING

        bool r = pServer->login(IP.c_str(), port, user.c_str(), password.c_str(), m_channels);

    if (!r)
	{
		
        this->mLastError = pServer->getLastError();
		addLog(IP.c_str(), __LINE__);			
		char szPort[10] = { 0 };
		itoa(port, szPort, 10);
		addLog(szPort, __LINE__);
		addLog(user.c_str(), __LINE__);
		addLog(password.c_str(), __LINE__);
        addLog("videoserver::sheLogin failed", __LINE__);
    }
    else{
		addLog(IP.c_str(), __LINE__);		
		char szPort[10] = { 0 };
		itoa(port, szPort, 10);
		addLog(szPort, __LINE__);
		addLog(user.c_str(), __LINE__);
		addLog(password.c_str(), __LINE__);
        addLog("videoserver::sheLogin true", __LINE__);
    }
    return r;

    SHE_END_RETURN_FALSE
}

OEMFactory::OEMFactory()
{
	m_name[32] = {0};
	m_FacID = SISC_IPC_UNDEFINE;
	m_OemFlag = false;
	m_pFactory = NULL;
}

OEMFactory::OEMFactory(DeviceFactory FacID, bool bOEMFlag, char *FacName, IVideoServerFactory *pFactory)
{
	m_FacID = FacID;
	m_OemFlag = bOEMFlag;
	strcpy_s(m_name, FacName);
	m_pFactory = pFactory;

 	m_port = 0;
	memset(m_usr, 0, strlen(m_usr));
	memset(m_pass, 0, strlen(m_pass));

	switch (m_FacID)
	{
	case SISC_IPC_GZLL:
	case SISC_IPC_JIRUI:
	case SISC_IPC_HUABANGHAISHI:
		strcpy_s(m_usr, "admin");
		strcpy_s(m_pass, "");
        m_OemFlag = (m_FacID != SISC_IPC_GZLL);
		m_port = 9101;
		break;
	case SISC_IPC_SALX:
		strcpy_s(m_usr, "admin");
		strcpy_s(m_pass, "123456");
		m_port = 34567;
        m_OemFlag = false;
		break;
	default:
		break;
	}
}

const char* OEMFactory::name()
{
	return m_name;
}

DeviceFactory OEMFactory::factory()
{
	return m_FacID;
}
