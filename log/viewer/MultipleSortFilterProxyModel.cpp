// Qt
#include <QtCore/QRegExp>
// Local
#include <MultipleSortFilterProxyModel.h>

/*!
    Usage:

    MultipleSortFilterProxyModel * filterModel = q_check_ptr( new MultipleSortFilterProxyModel(parent) );
    filterModel->setSourceModel( sourceModel );
    filterModel->beginDeclareFilter();
    filterModel->setFilter( 1, QVariant( "SomeStringValue" ), Qt::DisplayRole,Qt::MatchExactly );
    // Remove some old filter.
    filterModel->removeFilter( 2 );
    filterModel->setFilter( 5, QVariant( 1234 ), Qt::DisplayRole, Qt::MatchExactly );
    filterModel->endDeclateFilter();

    Now the model will filter column 1 and 5, to be accepted by the filtermodel a row needs to pass all filters.
*/

using namespace hb::tools;

/*!
    Constructs a new MultipleSortFilterProxyModel with \a parent.
 */
MultipleSortFilterProxyModel::MultipleSortFilterProxyModel(QObject* parent) : QSortFilterProxyModel(parent) {
    mDeclaringFilter = false;
}

/*!
    \brief Tells the model you want to declare a new filter.

    If you have a lot of data in your model it can be slow to declare more than one filter,
    because the model will always rebuild itself. If you call this member before setting the
    new filters the model will invalidate its contents not before you call.

    \sa endDeclareFilter()
 */
void MultipleSortFilterProxyModel::beginDeclareFilter() {
    mDeclaringFilter = true;
}

/*!
    \brief Stops the filter declaration and invalidates the filter.

    \sa beginDeclareFilter()
 */
void MultipleSortFilterProxyModel::endDeclareFilter() {
    if (mDeclaringFilter) {
        mDeclaringFilter = false;
        invalidateFilter();
    }
}

/*!
    \reimp
 */
bool MultipleSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const {
    QList<qint32> filter_columns = filters.keys();

    // If the column specified by the user is -1
    // that means all columns need to pass the filter to get into the result.
    if (filter_columns.contains(-1)) {
        ModelFilter filter = filters[-1];

        qint32 column_count = sourceModel()->columnCount(source_parent);
        for (qint32 column = 0; column < column_count; ++column) {
            QModelIndex source_index = sourceModel()->index(source_row, column, source_parent);
            QVariant key = sourceModel()->data(source_index, filter.mRole);
            if (!filter.acceptsValue(key)) {
                return false;
            }
        }
    } else {
        for (qint32 current_column : filter_columns) {
            ModelFilter filter = filters[current_column];

            QModelIndex source_index = sourceModel()->index(source_row, current_column, source_parent);
            if (!source_index.isValid()) // The column may not exist.
            {
                continue;
            }

            QVariant key = sourceModel()->data(source_index, filter.mRole);
            if (!filter.acceptsValue(key)) {
                return false;
            }
        }
    }

    return true;
}

/*!
    \brief Sets the filter with \a value, \a role and \a flags to the given \a column
 */
void MultipleSortFilterProxyModel::setFilter(qint32 column,
                                               const QVariant& value,
                                               qint32 role,
                                               Qt::MatchFlags flags) {
    // Could overwrite current filter.
    filters[column] = ModelFilter(value, role, flags);

    if (!mDeclaringFilter) {
        invalidateFilter();
    }
}

/*!
    \brief Removes the filter from the given \a column
 */
void MultipleSortFilterProxyModel::removeFilter(qint32 column) {
    if (filters.remove(column) > 0) {
        if (!mDeclaringFilter) {
            invalidateFilter();
        }
    }
}

/*!
    \brief Removes filters of all columns
 */
void MultipleSortFilterProxyModel::removeFilters() {
    filters.clear();

    if (!mDeclaringFilter) {
        invalidateFilter();
    }
}

/*!
    \brief Sets the filter \a value for the given \a column
 */
void MultipleSortFilterProxyModel::setFilterValue(qint32 column, const QVariant& value) {
    if (filters.contains(column)) {
        filters[column].mValue = value;
    } else {
        filters.insert(column, ModelFilter(value));
    }

    if (!mDeclaringFilter) {
        invalidateFilter();
    }
}

/*!
    \brief Sets the filter \a role for the given \a column
 */
void MultipleSortFilterProxyModel::setFilterRole(qint32 column, qint32 role) {
    if (filters.contains(column)) {
        filters[column].mRole = role;
    } else {
        filters.insert(column, ModelFilter(QVariant(), role));
    }

    if (!mDeclaringFilter) {
        invalidateFilter();
    }
}

/*!
    \brief Sets the filter \a flags for the given \a column
 */
void MultipleSortFilterProxyModel::setFilterFlags(qint32 column, const Qt::MatchFlags flags) {
    if (filters.contains(column)) {
        filters[column].mFlags = flags;
    } else {
        filters.insert(column, ModelFilter(QVariant(), Qt::DisplayRole, flags));
    }

    if (!mDeclaringFilter) {
        invalidateFilter();
    }
}

/*!
    \brief Returns the filter value for the given \a column
    \bold {Note:} if the column is not filtered it will return a null variant
 */
QVariant MultipleSortFilterProxyModel::filterValue(qint32 column) const {
    if (filters.contains(column)) {
        return filters[column].mValue;
    }

    return QVariant();
}

/*!
    \brief Returns the filter role for the given \a column
    \bold {Note:} if the column is not filtered it will return \c -1
*/
qint32 MultipleSortFilterProxyModel::filterRole(qint32 column) const {
    if (filters.contains(column)) {
        return filters[column].mRole;
    }

    return -1;
}

/*!
    \brief Returns the filter flags for the given \a column
    \bold {Note:} if the column is not filtered it will return the default value
 */
Qt::MatchFlags MultipleSortFilterProxyModel::filterFlags(qint32 column) const {
    if (filters.contains(column)) {
        return filters[column].mFlags;
    }

    return Qt::MatchContains;
}

/*!
    Returns true if the \a column is filtered
 */
bool MultipleSortFilterProxyModel::isFiltered(qint32 column) {
    return filters.contains(column);
}
