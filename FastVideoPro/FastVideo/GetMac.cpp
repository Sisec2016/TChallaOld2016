#include "GetMac.h"
#include <QtNetwork/QNetworkInterface>

void byte2Hex(unsigned char bData, unsigned char hex[])
{
	int high = bData / 16, low = bData % 16;
	hex[0] = (high < 10) ? ('0' + high) : ('A' + high - 10);
	hex[1] = (low < 10) ? ('0' + low) : ('A' + low - 10);
}

//obtain the Physical Address of Local NIC
bool getLocalMac(QString& PhysicalAddr)
{
	bool bSuccess = false;

	foreach(QNetworkInterface nif, QNetworkInterface::allInterfaces())
	{
		const QString LocalAdpterName("本地连接");
		QString msg("flags:%1, mac:%2, humanRN:%3, index:%4, isValid:%5, name:%6");
		if (LocalAdpterName == nif.humanReadableName()){
			PhysicalAddr = nif.hardwareAddress();
			bSuccess = true; break;
			qDebug() << msg.arg(nif.flags())
				.arg(nif.hardwareAddress())
				.arg(nif.humanReadableName())
				.arg(nif.index())
				.arg(nif.isValid())
				.arg(nif.name());
		}
	}

	return bSuccess;
}

bool ReadAuthorizationFile(string &filedat)
{
	QFile file(AuthorFile);
	QString str;
	if (file.open(QIODevice::ReadOnly))//QIODevice ReadOnly
	{
		QDataStream stream(&file);
		stream >> str;
		filedat = str.toStdString();
		file.close();
	}
	else
	{
		return false;
	}

	return true;
}