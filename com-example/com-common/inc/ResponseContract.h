/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef RESPONSECONTRACT_H
#define RESPONSECONTRACT_H

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

        class ResponseContract : public HbComContract
        {

        public:

            ResponseContract();
            virtual ~ResponseContract() = default;
            ResponseContract( const ResponseContract & source );
            ResponseContract & operator=( const ResponseContract & source );

            virtual const QString toString() const;

            virtual bool read ( QDataStream & stream );
            virtual bool write( QDataStream & stream ) const;

            virtual const QString & response() const final;
            virtual void setResponse( const QString & response ) final;

        protected:
            ResponseContract * create() const;

        protected:
            QString mResponse;
        };
    }
}

using hb::comexample::ResponseContract;

#endif // RESPONSECONTRACT_H
