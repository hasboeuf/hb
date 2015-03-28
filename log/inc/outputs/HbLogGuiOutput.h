/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGGUIOUTPUT_H
#define HBLOGGUIOUTPUT_H

/*! \file HbLogGuiOutput.h */

#include <outputs/HbLogAbstractOutput.h>

namespace hb
{
    namespace log
    {

        class HbLogGuiNotifier;


        /*! 
        * TODOC
        * \brief The %HbLogGuiOutput class defines a GUI output.
        *
        * %HbLogGuiOutput inherits from HbLogAbstractOutput.\n
        */
        class HbLogGuiOutput final : public HbLogAbstractOutput
        {
            Q_DISABLE_COPY( HbLogGuiOutput )


        public:

            HbLogGuiOutput() = delete;
            HbLogGuiOutput( HbLogGuiNotifier * notifier, HbLogger::Levels level = HbLogger::LEVEL_ALL );
            virtual ~HbLogGuiOutput();

        private:

            void processMessage( const HbLogMessage & message );


        private:

            HbLogGuiNotifier * mpNotifier;
        };
    }
}

#endif
