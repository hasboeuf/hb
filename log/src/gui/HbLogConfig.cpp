// Qt
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QtXml/QDomDocument>
// Local
#include <gui/HbLogConfig.h>

using namespace hb::log;


const char *  HbLogConfig::msDefaultConfigXml = ":/config/default.hblog";
const quint32 HbLogConfig::msMaxLevel = 64;

HbLogConfig::HbLogConfig() :
    QObject()
{
    mMaxBuffer = 5000;
    mFont = QFont(QStringLiteral("Courier New"));

    quint32 currentmLevel = 1;
    while ( currentmLevel <= msMaxLevel )
    {
        mLevelColors.insert( currentmLevel, QColor( 0, 0, 0 ) );
        currentmLevel <<= 1;
    }
    mBackgroundColor = QColor( 255, 255, 255 );
}

HbLogConfig::HbLogConfig(const HbLogConfig & config) :
HbLogConfig()
{
    if (&config != this)
    {
        mMaxBuffer       = config.mMaxBuffer;
        mLevelColors     = config.mLevelColors;
        mFont            = config.mFont;
        mBackgroundColor = config.mBackgroundColor;
    }
}


HbLogConfig & HbLogConfig::operator =(const HbLogConfig & config)
{
    if (&config != this)
    {
        mMaxBuffer       = config.mMaxBuffer;
        mLevelColors     = config.mLevelColors;
        mFont            = config.mFont;
        mBackgroundColor = config.mBackgroundColor;
    }

    return *this;
}

void HbLogConfig::buildDomFromConfig(QDomElement& root) const
{
    QDomDocument dom = root.ownerDocument();

    // Max buffer
    QDomElement max_buffer = dom.createElement(QStringLiteral("maxBuffer"));
    max_buffer.appendChild(dom.createTextNode(QString::number(mMaxBuffer)));

    // Font
    QDomElement font = dom.createElement(QStringLiteral("font"));
    QDomElement font_family = dom.createElement(QStringLiteral("family"));
    font_family.appendChild(dom.createTextNode(mFont.family()));
    QDomElement font_size = dom.createElement(QStringLiteral("size"));
    font_size.appendChild(dom.createTextNode(QString::number(mFont.pointSize())));
    font.appendChild(font_family);
    font.appendChild(font_size);

    // Background color
    QDomElement background_color = dom.createElement(QStringLiteral("backgroundColor"));
    background_color.appendChild(dom.createTextNode(mBackgroundColor.name()));

    // Levels
    QDomElement levels = dom.createElement(QStringLiteral("levels"));
    QMap<quint32, QColor>::const_iterator it_c = mLevelColors.constBegin();
    while (it_c != mLevelColors.constEnd())
    {
        QDomElement level = dom.createElement(QStringLiteral("level"));
        level.setAttribute(QStringLiteral("id"), it_c.key());
        level.setAttribute(QStringLiteral("color"), it_c.value().name());

        levels.appendChild(level);

        ++it_c;
    }

    root.appendChild(max_buffer);
    root.appendChild(font);
    root.appendChild(background_color);
    root.appendChild(levels);
}

bool HbLogConfig::exportConfigXml(QString file_path, const HbLogConfig& config)
{
    QFile xml_doc(file_path);
    if (!xml_doc.open(QIODevice::WriteOnly))
    {
        qDebug() << "Erreur à l'écriture du document XML : " << xml_doc.errorString();
        return false;
    }

    QDomDocument dom(QStringLiteral("hbLogConfig"));
    QDomElement root = dom.createElement(QStringLiteral("hbLogConfig"));
    dom.appendChild(root);

    config.buildDomFromConfig(root);

    QTextStream ts(&xml_doc);
    ts << dom.toString();

    xml_doc.close();

    return true;
}

void HbLogConfig::buildConfigFromDom(QDomElement& root)
{
    QDomNode node = root.firstChild();

    while (!node.isNull())
    {
        QString tag = node.nodeName();

        if (tag == QLatin1String("maxBuffer"))
        {
            mMaxBuffer = node.toElement().text().toInt();
        }
        else if (tag == QLatin1String("font"))
        {
            QDomNodeList font_children = node.childNodes();

            for (qint32 i = 0; i < font_children.size(); ++i)
            {
                QString child_tag = font_children.at(i).toElement().tagName();
                if (child_tag == QLatin1String("family"))
                {
                    mFont.setFamily(font_children.at(i).toElement().text());
                }
                else if (child_tag == QLatin1String("size"))
                {
                    mFont.setPointSize(font_children.at(i).toElement().text().toInt());
                }
                else
                {
                    qDebug() << QStringLiteral("Unknown tag: logger > font > ") + tag;
                }
            }
        }
        else if (tag == QLatin1String("backgroundColor"))
        {
            mBackgroundColor = node.toElement().text();
        }
        else if (tag == QLatin1String("levels"))
        {
            QDomNodeList levels_children = node.childNodes();

            for (qint32 i = 0; i < levels_children.size(); ++i)
            {
                QString child_tag = levels_children.at(i).toElement().tagName();
                if (child_tag == QLatin1String("level"))
                {
                    QDomNode level = levels_children.at(i);

                    qint32  level_id = level.toElement().attribute(QStringLiteral("id")).toInt();
                    QString level_color = level.toElement().attribute(QStringLiteral("color"));

                    mLevelColors.insert(level_id, QColor(level_color));
                }
                else
                {
                    // qDebug() << QStringLiteral("Unknown tag: logger > levels > ") + tag;
                }
            }
        }
        else
        {
            // qDebug() << QStringLiteral("Unknown tag: logger > ") + tag;
        }

        node = node.nextSibling();
    }
}

const HbLogConfig HbLogConfig::importConfigXml(QString file_path)
{
    HbLogConfig config;

    QFile xml_doc(file_path);
    if (!xml_doc.open(QIODevice::ReadOnly))
    {
        qDebug() << QStringLiteral("Erreur %1 [%2] à l'ouverture du document XML %3")
            .arg(xml_doc.error())
            .arg(xml_doc.errorString())
            .arg(xml_doc.fileName());

        return config;
    }

    QDomDocument *dom = q_check_ptr(new QDomDocument(QStringLiteral("hbLogConfig")));

    if (!dom->setContent(&xml_doc))
    {
        xml_doc.close();
        qDebug() << "Erreur à l'ouverture du document XML";
        return config;
    }

    xml_doc.close();

    QDomElement root = dom->documentElement();

    config.buildConfigFromDom(root);

    return config;
}

bool HbLogConfig::isValid() const
{
    return true; // TODO
}

void HbLogConfig::loadSettings()
{
    QSettings settings;

    if (settings.childGroups().isEmpty()) // First start, we load the default XML config file.
    {
        this->operator=(HbLogConfig::importConfigXml(QString::fromLatin1(HbLogConfig::msDefaultConfigXml)));
        saveSettings();
        return;
    }

    // Max buffer
    mMaxBuffer = settings.value(QStringLiteral("general/maxBuffer"), 500).toInt();
    // Font
    mFont.setFamily(settings.value(QStringLiteral("font/family"), QStringLiteral("Courier")).toString());
    mFont.setPointSize(settings.value(QStringLiteral("font/size"), 8).toInt());
    // Background color
    mBackgroundColor.setNamedColor(settings.value(QStringLiteral("general/backgroundColor"), QStringLiteral("#ffffff")).toString());

    // Colors
    QMap<qint32, QString> colors;
    settings.beginGroup(QStringLiteral("levels/colors"));
    mLevelColors.clear();
    QStringList levels = settings.childKeys();

    foreach(QString level, levels)
    {
        QColor color;
        color.setNamedColor(settings.value(level).toString());

        mLevelColors[level.toInt()] = color;
    }
    settings.endGroup();

}

void HbLogConfig::saveSettings()
{
    QSettings settings;

    // Max buffer
    settings.setValue(QStringLiteral("general/maxBuffer"), mMaxBuffer);
    // Font
    settings.setValue(QStringLiteral("font/family"), mFont.family());
    settings.setValue(QStringLiteral("font/size"), mFont.pointSize());
    // Background color
    settings.setValue(QStringLiteral("general/backgroundColor"), mBackgroundColor.name());

    // Colors
    QMap<quint32, QColor>::const_iterator icolor = mLevelColors.constBegin();
    settings.beginGroup(QStringLiteral("levels/colors"));
    settings.remove(QString()); // All keys in the current group() are removed.
    while (icolor != mLevelColors.constEnd())
    {
        settings.setValue(QString::number(icolor.key()), icolor.value().name());
        ++icolor;
    }
    settings.endGroup();

    settings.sync(); // Commit.
}


const QColor HbLogConfig::colorByIdLevel(quint32 color_id) const
{
    if (mLevelColors.contains(color_id))
    {
        return mLevelColors.value(color_id);
    }
    else return QColor(0, 0, 0);
}

quint32 HbLogConfig::maxBuffer() const
{
    return mMaxBuffer;
}

const QFont HbLogConfig::font() const
{
    return mFont;
}

const QMap<quint32, QColor> &HbLogConfig::levelColor() const
{
    return mLevelColors;
}

const QColor HbLogConfig::backgroundColor() const
{
    return mBackgroundColor;
}

void HbLogConfig::setMaxBuffer(quint32 maxBuffer)
{
    mMaxBuffer = maxBuffer;
}

void HbLogConfig::setFont(QFont& font)
{
    mFont = font;
}

void HbLogConfig::setColorById(qint32 color_id, QColor& color)
{
    mLevelColors.insert(color_id, color);
}

void HbLogConfig::setBackgroundColor(QColor &color)
{
    mBackgroundColor = color;
}
