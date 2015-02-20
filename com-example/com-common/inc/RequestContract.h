/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef REQUESTCONTRACT_H
#define REQUESTCONTRACT_H

// Qt
// Hb
#include <HbGlobal.h>
#include <HbCom.h>
#include <contract/HbComContract.h>
// Local


namespace hb
{
    namespace comexample
    {

        class RequestContract : public HbComContract
        {

        public:

            RequestContract();
            virtual ~RequestContract() = default;
            RequestContract( const RequestContract & source );
            RequestContract & operator=( const RequestContract & source );

            RequestContract * create() const;

            RequestContract * reply() const;

            virtual bool read ( QDataStream & stream );
            virtual bool write( QDataStream & stream ) const;

            virtual const QString & request() const final;
            virtual void setRequest( const QString & request ) final;

        protected:
            QString mRequest;
        };
    }
}

using hb::comexample::RequestContract;

#endif // REQUESTCONTRACT_H
