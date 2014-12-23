#ifndef MULTIPLESORTFILTERPROXYMODEL_H
#define MULTIPLESORTFILTERPROXYMODEL_H

// Qt
#include <QtCore/QSortFilterProxyModel>
// Hb
#include <HbTools.h>
#include <HbGlobal.h>

namespace hb
{
    namespace logviewer
	{
        class ModelFilter;


        class HB_TOOLS_DECL HbMultipleSortFilterProxyModel final : public QSortFilterProxyModel
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbMultipleSortFilterProxyModel )


        public :

            HbMultipleSortFilterProxyModel( QObject *parent = nullptr );
            virtual ~HbMultipleSortFilterProxyModel() = default;

            void beginDeclareFilter();
            void endDeclareFilter();
            void setFilter( qint32 column, const QVariant &value, qint32 role = Qt::DisplayRole, Qt::MatchFlags flags = Qt::MatchContains );
            void setFilterValue( qint32 column, const QVariant &value );
            void setFilterRole( qint32 column, qint32 role = Qt::DisplayRole );
            void setFilterFlags( qint32 column, const Qt::MatchFlags flags = Qt::MatchContains );
            void removeFilter( qint32 column );

            QVariant filterValue( qint32 column ) const;
            qint32 filterRole( qint32 column ) const;
            Qt::MatchFlags filterFlags( qint32 column ) const;

            bool isFiltered( qint32 column );

        private :

            bool filterAcceptsRow( int source_row, const QModelIndex &source_parent ) const;


        private :

            QMap< qint32, ModelFilter > filters;
            bool mDeclaringFilter;
        };


        class ModelFilter final
        {
            Q_DEFAULT_COPY( ModelFilter )


        public :

            ModelFilter( const QVariant &value = QVariant(), qint32 role = Qt::DisplayRole, const Qt::MatchFlags flags = Qt::MatchContains ) :
                mValue( value ), mRole( role ), mFlags( flags ) {}
            virtual ~ModelFilter() = default;

            bool acceptsValue( const QVariant & value )
            {
                // If we have no value we accept everything
                if( !mValue.isValid() || !value.isValid() )
                    return true;

                Qt::CaseSensitivity cs = mFlags.testFlag( Qt::MatchCaseSensitive ) ? Qt::CaseSensitive : Qt::CaseInsensitive;
                mFlags &= ~Qt::MatchCaseSensitive;

                // QVariant based matching
                if( mFlags == Qt::MatchExactly ){
                    if( mValue == value )
                        return true;
                }
                // QString based matching
                else {
                    QString filterText = mValue.toString();
                    QString modelText = value.toString();
                    switch( mFlags )
                    {
                    case Qt::MatchRegExp:
                        if( QRegExp( filterText, cs ).exactMatch( modelText ) )
                            return true;
                        break;
                    case Qt::MatchWildcard:
                        if( QRegExp( filterText, cs, QRegExp::Wildcard ).exactMatch( modelText ) )
                            return true;
                        break;
                    case Qt::MatchStartsWith:
                        if( modelText.startsWith( filterText, cs ) )
                            return true;
                        break;
                    case Qt::MatchEndsWith:
                        if( modelText.endsWith( filterText, cs ) )
                            return true;
                        break;
                    case Qt::MatchFixedString:
                        if( modelText.compare( filterText, cs ) == 0 )
                            return true;
                        break;
                    default:
                        if( modelText.contains( filterText, cs ) )
                            return true;
                    }
                }
                return false;
            }


        // TODO A REVOIR POUR CHANGER LE SCOPE EN PRIVATE
        public :

            QVariant        mValue;
            qint32          mRole;
            Qt::MatchFlags  mFlags;
        };


    }
}

#endif