#ifndef HBFACEBOOKOBJECT_H
#define HBFACEBOOKOBJECT_H

/*! \file HbFacebookObject.h */

// Qt
#include <QtCore/QString>
// Hb
#include <core/HbEnum.h>
// Local
#include <HbLink.h>

namespace hb {
namespace link {
/*!
 * HbFacebookObject represents an abstract Facebook object.
 */
class HB_LINK_DECL HbFacebookObject {
    Q_GADGET

public:
    enum ObjectType { OBJECT_NONE = 0, OBJECT_USER };
    Q_ENUM(ObjectType)
    HB_ENUM(ObjectType)

    HbFacebookObject();
    virtual ~HbFacebookObject() = default;

    /*!
     * Create object from a JSON document.
     * \todo May be a factory?
     * \param doc JSON document.
     */
    virtual void load(const QJsonDocument& doc) = 0;

    /*!
     * Convenient method to print Facebook object informations.
     * \return Stringified object.
     */
    virtual QString toString() const;

    /*!
     * Set the Facebook id of the object.
     * \param id Facebook id.
     */
    virtual void setId(const QString& id);

    /*!
     * Return the Facebook id.
     * \return Facebook id.
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

using hb::link::HbFacebookObject;

#endif // HBFACEBOOKOBJECT_H
