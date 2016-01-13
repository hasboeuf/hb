# ----------------
# Module Settings
# ----------------

MODULE.NAME = HB
MODULE.PATH = ..

# -----------------
# Project Settings
# -----------------

PROJECT.ID = network

SUBDIRS +=  com \
            com/tcp \
            config/peer \
            config/service \
            config/service/auth \
            config/service/channel \
            config/service/presence \
            config/com \
            contract \
            contract/general \
            contract/auth \
            contract/presence \
            contract/channel \
            service \
            service/auth \
            service/channel \
            service/presence \
            user \
            listener \
            mock

# ------------
# Qt Settings
# ------------


# -----------------
# Modules Settings
# -----------------

HB += link log tools

# -------------
# C++ Settings
# -------------
DEFINES += HB_NETWORK_SHARED

# -----------------
# Install Settings
# -----------------

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
