/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGCONFIG_H
#define HBLOGCONFIG_H

/*! \file HbLogConfig.h */

// Qt
#include <QtCore/QMap>
#include <QtGui/QColor>
#include <QtGui/QFont>
#include <QtXml/QDomElement>
// Local
#include <HbLog.h>

namespace hb {
namespace log {
/*!
 * TODOC.
 */
class HB_LOG_DECL HbLogConfig {
public:
    static const HbLogConfig importConfigXml(QString file_path);
    static bool exportConfigXml(QString file_path, const HbLogConfig& config);

    HbLogConfig();
    HbLogConfig(const HbLogConfig& config);
    virtual ~HbLogConfig() = default;

    HbLogConfig& operator=(const HbLogConfig& config);

    quint32 maxBuffer() const;
    const QFont font() const;
    const QMap<quint32, QColor>& levelColor() const;
    const QColor colorByIdLevel(quint32 color_id) const;
    const QColor backgroundColor() const;

    void setMaxBuffer(quint32 maxBuffer);
    void setFont(QFont& font);
    void setColorById(qint32 color_id, QColor& color);
    void setBackgroundColor(QColor& color);

    bool isValid() const;

    void loadSettings();
    void saveSettings();

    static const char* msDefaultConfigXml;
    static const quint32 msMaxLevel;

protected:
    virtual void buildDomFromConfig(QDomElement& root) const;
    virtual void buildConfigFromDom(QDomElement& root);

    quint32 mMaxBuffer;
    QFont mFont;
    QMap<quint32, QColor> mLevelColors;
    QColor mBackgroundColor;
};
} // namespace log
} // namespace hb

#endif // HBLOGCONFIG_H
