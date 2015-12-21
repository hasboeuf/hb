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
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>
// Local


namespace hb
{
    namespace networkexample
    {

        class ResponseContract : public HbNetworkContract
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
            virtual ResponseContract * create() const override;

        protected:
            QString mResponse;
        };
    }
}

using hb::networkexample::ResponseContract;

#endif // RESPONSECONTRACT_H
