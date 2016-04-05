/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef REQUESTSUMCONTRACT_H
#define REQUESTSUMCONTRACT_H

// Qt
// Hb
#include <HbGlobal.h>
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>
// Local
#include <ResponseSumContract.h> // Covariance


namespace hb
{
    namespace networkexample
    {

        class RequestSumContract : public HbNetworkContract
        {

        public:

            RequestSumContract();
            virtual ~RequestSumContract() = default;
            RequestSumContract( const RequestSumContract & source );
            RequestSumContract & operator=( const RequestSumContract & source );

            virtual ResponseSumContract * takeReply() const;

            virtual QString toString() const;

            virtual bool read ( QDataStream & stream );
            virtual bool write( QDataStream & stream ) const;

            virtual qint32 intA() const final;
            virtual void setIntA( qint32 a ) final;

            virtual qint32 intB( ) const final;
            virtual void setIntB( qint32 b ) final;

        protected:
            virtual RequestSumContract * create() const override;

        protected:
            qint32 mIntA;
            qint32 mIntB;
        };
    }
}

using hb::networkexample::RequestSumContract;

#endif // REQUESTSUMCONTRACT_H
