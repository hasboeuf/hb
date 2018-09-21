/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBPLUGINSERVICE_H
#define HBPLUGINSERVICE_H

/*! \file HbPluginService.h */

// Qt
#include <QtCore/QObject>
// Local
#include <HbPlugin.h>

namespace hb {
namespace plugin {
/*!
 * HbPluginService identifies a service.
 */
class HB_PLUGIN_DECL HbPluginService : public QObject {
    Q_OBJECT
public:
    explicit HbPluginService(const QString& name, const QString& version, QObject* parent = nullptr);

    const QString& name() const;
    const QString& version() const;

protected:
    QString mName;
    QString mVersion;
};
} // namespace plugin
} // namespace hb

#endif // HBPLUGINSERVICE_H
