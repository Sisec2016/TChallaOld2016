#include "xmlsettings.h"

#include "XmlSettings.h"
#include <QDomDocument>
#include <QDebug>
#include "QApplication"

XmlSettings::XmlSettings( QString fname )
{
    if ( fname.isEmpty() )
    {
        fname = "settings.xml";
    }

    static const QSettings::Format XmlFormat = QSettings::registerFormat("xml", readXmlFile, writeXmlFile);
    m_pSettings = new QSettings( QApplication::applicationDirPath() + "/" + fname , XmlFormat );
}

XmlSettings::~XmlSettings()
{
    delete m_pSettings;
}

QVariant XmlSettings::value( const QString & key, const QVariant & defaultValue )
{
    if ( !settings().contains( key ) )
        settings().setValue( key, defaultValue );
    return settings().value( key );
}
void XmlSettings::setValue ( const QString & key, const QVariant & value )
{
    settings().setValue( key, value );
}

bool XmlSettings::readXmlFile(QIODevice &device, QSettings::SettingsMap &map)
{
    qDebug() << "-----readXmlSettings------";

    QDomDocument doc("");
    if ( !doc.setContent( &device ) ) return false;
    QDomElement root = doc.documentElement();

    processReadKey( "", map, root );

    return true;
}

bool XmlSettings::writeXmlFile(QIODevice &device, const QSettings::SettingsMap &map)
{
    qDebug() << "-----writeXmlSettings-----";


    QDomDocument doc("");
    QDomElement root = doc.createElement("Main");
    doc.appendChild(root);

    QMapIterator<QString, QVariant> i(map);
    while ( i.hasNext() )
    {
        i.next();

        QString  sKey = i.key();
        QVariant value = i.value();
        processWriteKey( doc, root, sKey, i.value() );
    };

    QDomNode xmlNode = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.insertBefore(xmlNode, doc.firstChild());

    QTextStream out( &device );
    doc.save(out, 4);

    return true;
}

void XmlSettings::processWriteKey( QDomDocument& doc, QDomElement& domElement, QString key, const QVariant& value )
{
    int slashPos = key.indexOf( '/' );


    if ( slashPos < 0 )
    {

        if ( key == "size" ) return;
        domElement.setAttribute( key, value.toString() );
        return;
    };


    QString groupName = key.left( slashPos );

    if ( groupName.toInt() )
    {
        groupName = "row_" + groupName;
        domElement.toElement().setAttribute("table", "1");
    };


    QDomElement groupElement;

    QDomNode findedGroupNode = domElement.namedItem( groupName );

    if ( findedGroupNode.isNull() )
    {
        groupElement = doc.createElement( groupName );
        domElement.appendChild( groupElement );
    }
    else
        groupElement = findedGroupNode.toElement();


    key = key.right( key.size() - slashPos - 1 );

    processWriteKey( doc, groupElement, key, value );
}

void XmlSettings::processReadKey( QString key, QSettings::SettingsMap &map, QDomElement& domElement )
{

    QDomNamedNodeMap namedNodeMap = domElement.attributes();

    for (int i = 0; i < namedNodeMap.count(); ++i)
    {
        QString name = namedNodeMap.item( i ).toAttr().name();
        QString value = namedNodeMap.item( i ).toAttr().value();
        map.insert( key + name, value );
    };

    QDomNodeList nlChild = domElement.childNodes();

    bool isTable = domElement.attribute("table", "0").toInt();
    if ( isTable )
        map.insert( key + "size", nlChild.count() );


    for (int i = 0; i < nlChild.count(); ++i)
    {
        QString childName = nlChild.item(i).toElement().tagName();
        if ( childName.contains("row_") )
            childName = childName.right( childName.size() - 4 );

        QString subKey = key + childName + "/";
        QDomElement subElement = nlChild.item(i).toElement();
        processReadKey( subKey, map, subElement );
    };
}
