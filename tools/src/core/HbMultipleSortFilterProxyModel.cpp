// Qt
#include <QtCore/QRegExp>
// Local
#include <core/HbMultipleSortFilterProxyModel.h>


/*!
    \class QxtSortFilterProxyModel
    \inmodule QxtWidgets
    \brief The QxtSortFilterProxyModel class is a multi column filter model.
    
    The QxtSortFilterProxyModel makes it possible to filter over multiple columns.

    \code
    QxtSortFilterProxyModel * filterModel = q_check_ptr( new QxtSortFilterProxyModel(parent) );
    filterModel->setSourceModel(sourceModel);
    filterModel->beginDeclareFilter();
    filterModel->setFilter(1,QVariant("SomeStringValue"),Qt::DisplayRole,Qt::MatchExactly);
    //remove some old filter
    filterModel->removeFilter(2);
    filterModel->setFilter(5,QVariant(1234),Qt::DisplayRole,Qt::MatchExactly);
    filterModel->endDeclateFilter();
    \endcode

    Now the model will filter column 1 and 5, to be accepted by the filtermodel a row needs to pass all filters
*/

using namespace hb::logviewer;


/*!
    Constructs a new QxtSortFilterProxyModel with \a parent.
 */
HbMultipleSortFilterProxyModel::HbMultipleSortFilterProxyModel ( QObject *parent) : QSortFilterProxyModel(parent)
{
    mDeclaringFilter = false;
}


/*!
    \brief tells the model you want to declare a new filter

    If you have a lot of data in your model it can be slow to declare more than one filter,
    because the model will always rebuild itself. If you call this member before setting the
    new filters the model will invalidate its contents not before you call
    
    \sa endDeclareFilter()
 */
void HbMultipleSortFilterProxyModel::beginDeclareFilter ( )
{
    mDeclaringFilter = true;
}

/*!
    \brief stops the filter declaration and invalidates the filter 

    \sa beginDeclareFilter()
 */
void HbMultipleSortFilterProxyModel::endDeclareFilter ( )
{
    if(mDeclaringFilter){
        mDeclaringFilter = false;
        invalidateFilter();
    }
}

/*!
    \reimp
 */
bool HbMultipleSortFilterProxyModel::filterAcceptsRow ( int source_row, const QModelIndex &source_parent ) const
{
    QList<qint32> filterColumns = filters.keys();
    foreach( qint32 currCol, filterColumns ){
        ModelFilter filter = filters[currCol];
        // if the column specified by the user is -1 
        // that means all columns need to pass the filter to get into the result
        if (currCol == -1) {
            qint32 column_count = sourceModel()->columnCount( source_parent );
            for (qint32 column = 0; column < column_count; ++column) {
                QModelIndex source_index = sourceModel()->index(source_row, column, source_parent);
                QVariant key = sourceModel()->data(source_index, filter.mRole);
                if (!filter.acceptsValue(key))
                   return false;
            }
            continue;
        }
        QModelIndex source_index = sourceModel()->index(source_row, currCol , source_parent);
        if (!source_index.isValid()) // the column may not exist
            continue;
        QVariant key = sourceModel()->data(source_index, filter.mRole);
        if(!filter.acceptsValue(key))
            return false;
    }
    return true;
}

/*!
    \brief Sets the filter with \a value, \a role and \a flags to the given \a column
 */
void HbMultipleSortFilterProxyModel::setFilter( qint32 column, const QVariant &value, qint32 role, Qt::MatchFlags flags )
{
    if(filters.contains(column))
        filters[column] = ModelFilter(value,role,flags);
    else
        filters.insert(column,ModelFilter(value,role,flags));

    if(!mDeclaringFilter)
        invalidateFilter();
}

/*!
    \brief Removes the filter from the given \a column
 */
void HbMultipleSortFilterProxyModel::removeFilter ( qint32 column )
{
    if(filters.contains(column)){
        filters.remove(column);

        if(!mDeclaringFilter)
            invalidateFilter();
    }
}

/*!
    \brief Sets the filter \a value for the given \a column
 */
void HbMultipleSortFilterProxyModel::setFilterValue ( qint32 column , const QVariant &value )
{
    if(filters.contains(column))
        filters[column].mValue = value;
    else
        filters.insert(column,ModelFilter(value));

    if(!mDeclaringFilter)
        invalidateFilter();
}

/*!
    \brief Sets the filter \a role for the given \a column
 */
void HbMultipleSortFilterProxyModel::setFilterRole ( qint32 column , qint32 role )
{
    if(filters.contains(column))
        filters[column].mRole=role;
    else
        filters.insert(column,ModelFilter(QVariant(),role));

    if(!mDeclaringFilter)
        invalidateFilter();
}

/*!
    \brief Sets the filter \a flags for the given \a column
 */
void HbMultipleSortFilterProxyModel::setFilterFlags ( qint32 column , const Qt::MatchFlags flags )
{
    if(filters.contains(column))
        filters[column].mFlags = flags;
    else
        filters.insert(column,ModelFilter(QVariant(),Qt::DisplayRole,flags));

    if(!mDeclaringFilter)
        invalidateFilter();
}

/*!
    \brief Returns the filter value for the given \a column

    \bold {Note:} if the column is not filtered it will return a null variant
 */
QVariant HbMultipleSortFilterProxyModel::filterValue ( qint32 column ) const
{
    if(filters.contains(column))
        return filters[column].mValue;
    return QVariant();
}

/*!
    \brief Returns the filter role for the given \a column

    \bold {Note:} if the column is not filtered it will return \c -1    
*/
qint32 HbMultipleSortFilterProxyModel::filterRole ( qint32 column ) const
{
    if(filters.contains(column))
        return filters[column].mRole;
    return -1;
}

/*!
    \brief returns the filter flags for the given \a column

    \bold {Note:} if the column is not filtered it will return the default value
 */
Qt::MatchFlags HbMultipleSortFilterProxyModel::filterFlags ( qint32 column ) const
{
    if(filters.contains(column))
        return filters[column].mFlags;
    return Qt::MatchContains;
}

/*!
    Returns true if the \a column is filtered
 */
bool HbMultipleSortFilterProxyModel::isFiltered ( qint32 column )
{
    return filters.contains(column);
}