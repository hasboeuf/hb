#ifndef LOGCONFIG_H
#define LOGCONFIG_H

/*! \file LogConfig.h */

// Qt
#include <QtCore/QMap>
#include <QtGui/QColor>
#include <QtGui/QFont>
#include <QtXml/QDomElement>
// Local
#include <HbLog.h>

namespace hb {
namespace logviewer {
/*!
 * TODOC.
 */
class HB_LOG_DECL LogConfig {
public:
    static const LogConfig importConfigXml(QString file_path);
    static bool exportConfigXml(QString file_path, const LogConfig& config);

    LogConfig();
    LogConfig(const LogConfig& config);
    virtual ~LogConfig() = default;

    LogConfig& operator=(const LogConfig& config);

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
} // namespace logviewer
} // namespace hb

#endif // LOGCONFIG_H
