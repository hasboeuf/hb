#ifndef HBAUTHOBJECT_H
#define HBAUTHOBJECT_H

// Qt
#include <QtCore/QString>
// Hb
#include <core/HbEnum.h>
// Local
#include <HbAuth.h>

namespace hb {
namespace auth {
/*!
 * HbAuthObject represents an abstract API object.
 */
class HB_AUTH_DECL HbAuthObject {
    Q_GADGET

public:
    enum Source { UNKNOWN, FACEBOOK, GOOGLE };
    Q_ENUM(Source)

    enum Error { NONE, NETWORK, PARSING, API };
    Q_ENUM(Error)

    HbAuthObject() = default;
    virtual ~HbAuthObject() = default;

    /*!
     * \return True if object data are valid, false otherwise
     */
    bool isValid() const;

    /*!
     * Set object error
     */
    void setError(Error errorCode, QString errorMessage);

    /*!
     * \return Error code
     */
    int errorCode() const;

    /*!
     * \return Error message
     */
    QString errorMessage() const;

    /*!
     * \return Stringified object
     */
    virtual QString toString() const;

    /*!
     * Set object id
     * \param id Id to set
     */
    void setId(const QString& id);

    /*!
     * \return Object's id.
     */
    QString id() const;

    /*!
     * Set object source
     * \param Source to set
     */
    void setSource(Source source);

    /*!
     * \return Object source
     */
    Source source() const;

protected:
    Error mErrorCode = NONE;
    QString mErrorMessage;
    QString mId;
    Source mSource = UNKNOWN;
};
} // namespace auth
} // namespace hb

#endif // HBAUTHOBJECT_H
