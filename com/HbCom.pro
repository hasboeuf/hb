# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   =      com

SUBDIRS +=  tcp \
            contract \
            config

# ------------
# Qt Settings
# ------------

QT *=		network sql

# -----------------
# Modules Settings
# -----------------

HB +=		tools log

# -------------
# C++ Settings
# -------------
DEFINES += HB_COM_BUILD

# -----------------
# Install Settings
# -----------------

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
