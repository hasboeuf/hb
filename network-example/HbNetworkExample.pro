# ----------------
# Module Settings
# ----------------

MODULE.NAME = hb
MODULE.PATH = ..

# -----------------
# Project Settings
# -----------------

PROJECT.NAME = HbNetworkExample
PROJECT.TYPE = subdirs

SUBDIRS += \
    network-common/HbNetworkCommon.pro \
    network-server/HbNetworkServer.pro \
    network-user/HbNetworkUser.pro

network-server.depends = network network-common
network-user.depends = network network-common

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
