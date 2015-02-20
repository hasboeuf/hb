/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef MESSAGECONTRACT_H
#define MESSAGECONTRACT_H

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

        class MessageContract : public HbComContract
        {

        public:

            MessageContract();
            virtual ~MessageContract() = default;
            MessageContract( const MessageContract & source );
            MessageContract & operator=( const MessageContract & source );

            MessageContract * create() const;

            virtual bool read ( QDataStream & stream );
            virtual bool write( QDataStream & stream ) const;

            virtual const QString & message() const final;
            virtual void setMessage( const QString & message ) final;

        protected:
            QString mMessage;
        };
    }
}

using hb::comexample::MessageContract;

#endif // MESSAGECONTRACT_H
