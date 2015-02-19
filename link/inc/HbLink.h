/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLINK_H
#define HBLINK_H

#if !defined( HB_LINK_DECL )
#    if defined( HB_LINK_BUILD )
#        define HB_LINK_DECL Q_DECL_EXPORT
#    else
#        define HB_LINK_DECL Q_DECL_IMPORT
#    endif
#endif

#endif // HBLINK_H
