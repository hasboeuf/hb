# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   =      network

SUBDIRS +=  com \
            com/tcp \
            config/peer \
            config/service \
            config/service/auth \
            config/service/channel \
            config/service/presence \
            config/com \
            contract \
            contract/auth \
            contract/presence \
            service \
            service/auth \
            service/channel \
            service/presence \
            user \
            listener

# ------------
# Qt Settings
# ------------

QT *=		network sql

# -----------------
# Modules Settings
# -----------------

HB +=		tools log link

# -------------
# C++ Settings
# -------------
DEFINES += HB_NETWORK_BUILD

# -----------------
# Install Settings
# -----------------

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
