# ----------------
# Module Settings
# ----------------

MODULE.NAME = hb
MODULE.PATH = ..

# -----------------
# Project Settings
# -----------------

PROJECT.NAME = HbNetworkBasicExample
PROJECT.TYPE = subdirs

SUBDIRS += \
    network-basic-common/HbNetworkBasicCommon.pro \
    network-basic-server/HbNetworkBasicServer.pro \
    network-basic-user/HbNetworkBasicUser.pro

network-basic-server.depends = network network-basic-common
network-basic-user.depends = network network-basic-common

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
