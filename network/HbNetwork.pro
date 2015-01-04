# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   =      network
			
SUBDIRS +=  auth \
            channel \
            protocol \
            tcp \
            update
			
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
