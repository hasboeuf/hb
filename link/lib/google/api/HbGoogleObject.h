#ifndef HBGOOGLEOBJECT_H
#define HBGOOGLEOBJECT_H

// Qt
#include <QtCore/QString>
// Hb
#include <core/HbEnum.h>
// Local
#include <HbLink.h>

namespace hb {
namespace link {
/*!
 * HbGoogleObject represents an abstract Google object.
 */
class HB_LINK_DECL HbGoogleObject {
    Q_GADGET

public:
    enum ObjectType { OBJECT_NONE = 0, OBJECT_USER };
    Q_ENUM(ObjectType)
    HB_ENUM(ObjectType)

    HbGoogleObject();
    virtual ~HbGoogleObject() = default;

    /*!
     * Create object from a JSON document.
     * \todo May be a factory?
     * \param doc JSON document.
     */
    virtual void load(const QJsonDocument& doc) = 0;

    /*!
     * Convenient method to print Google object informations.
     * \return Stringified object.
     */
    virtual QString toString() const;

    /*!
     * Set the Google id of the object.
     * \param id Google id.
     */
    virtual void setId(const QString& id);

    /*!
     * Return the Google id.
     * \return Google id.
     */
    virtual const QString& id() const;

    /*!
     * Return the object type.
     * \return Object type.
     * \sa ObjectType
     */
    virtual ObjectType type() const;

protected:
    QString mId;
    ObjectType mType;
};
} // namespace link
} // namespace hb

using hb::link::HbGoogleObject;

#endif // HBGOOGLEOBJECT_H
