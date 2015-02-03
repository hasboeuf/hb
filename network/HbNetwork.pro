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

HB +=		log tools

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
