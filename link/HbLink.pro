# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   =      link

SUBDIRS +=  client \
            server

# ------------
# Qt Settings
# ------------

QT *=		gui network

# -----------------
# Modules Settings
# -----------------

HB += tools log

# -------------
# C++ Settings
# -------------
DEFINES += HB_LINK_BUILD

# -----------------
# Install Settings
# -----------------


# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
