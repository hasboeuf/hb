#ifndef MULTIPLESORTFILTERPROXYMODEL_H
#define MULTIPLESORTFILTERPROXYMODEL_H

/*! \file MultipleSortFilterProxyModel.h */

// Qt
#include <QtCore/QSortFilterProxyModel>
// Hb
#include <HbGlobal.h>
#include <HbTools.h>

namespace hb {
namespace tools {
class ModelFilter;

/*!
 * MultipleSortFilterProxyModel is a multiple QSortFilterProxyModel.
 * Used to set filters on several columns for example.
 */
class HB_TOOLS_DECL MultipleSortFilterProxyModel : public QSortFilterProxyModel {
    Q_OBJECT
    Q_DISABLE_COPY(MultipleSortFilterProxyModel)

public:
    MultipleSortFilterProxyModel(QObject* parent = nullptr);
    virtual ~MultipleSortFilterProxyModel() = default;

    void beginDeclareFilter();
    void endDeclareFilter();
    void setFilter(qint32 column,
                   const QVariant& value,
                   qint32 role = Qt::DisplayRole,
                   Qt::MatchFlags flags = Qt::MatchContains);
    void setFilterValue(qint32 column, const QVariant& value);
    void setFilterRole(qint32 column, qint32 role = Qt::DisplayRole);
    void setFilterFlags(qint32 column, const Qt::MatchFlags flags = Qt::MatchContains);
    void removeFilter(qint32 column);
    void removeFilters();

    QVariant filterValue(qint32 column) const;
    qint32 filterRole(qint32 column) const;
    Qt::MatchFlags filterFlags(qint32 column) const;

    bool isFiltered(qint32 column);

private:
    bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;

    QMap<qint32, ModelFilter> filters;
    bool mDeclaringFilter;
};

class ModelFilter {
public:
    ModelFilter(const QVariant& value = QVariant(),
                qint32 role = Qt::DisplayRole,
                const Qt::MatchFlags flags = Qt::MatchContains) {
        mValue = value;
        mRole = role;
        mFlags = flags;
    }

    ModelFilter(const ModelFilter& source) {
        mValue = source.mValue;
        mRole = source.mRole;
        mFlags = source.mFlags;
    }

    ModelFilter& operator=(const ModelFilter& source) {
        if (&source != this) {
            mValue = source.mValue;
            mRole = source.mRole;
            mFlags = source.mFlags;
        }
        return *this;
    }

    virtual ~ModelFilter() = default;

    bool acceptsValue(const QVariant& value) {
        // If we have no value we accept everything.
        if (!mValue.isValid() || !value.isValid()) {
            return true;
        }

        // QVariant based matching
        if (mFlags == Qt::MatchExactly) {
            if (mValue == value) {
                return true;
            }
        }
        // QString based matching
        else {
            Qt::CaseSensitivity cs = Qt::CaseInsensitive;
            if (mFlags.testFlag(Qt::MatchCaseSensitive)) {
                cs = Qt::CaseSensitive;
            }

            QString filterText = mValue.toString();
            QString modelText = value.toString();

            switch (mFlags) {
            case Qt::MatchRegExp:
                if (QRegExp(filterText, cs).exactMatch(modelText)) {
                    return true;
                }
                break;
            case Qt::MatchWildcard:
                if (QRegExp(filterText, cs, QRegExp::Wildcard).exactMatch(modelText)) {
                    return true;
                }
                break;
            case Qt::MatchStartsWith:
                if (modelText.startsWith(filterText, cs)) {
                    return true;
                }
                break;
            case Qt::MatchEndsWith:
                if (modelText.endsWith(filterText, cs)) {
                    return true;
                }
                break;
            case Qt::MatchFixedString:
                if (modelText.compare(filterText, cs) == 0) {
                    return true;
                }
                break;
            default:
                if (modelText.contains(filterText, cs)) {
                    return true;
                }
            }
        }
        return false;
    }

    QVariant mValue;
    qint32 mRole;
    Qt::MatchFlags mFlags;
};

} // namespace tools
} // namespace hb

#endif
