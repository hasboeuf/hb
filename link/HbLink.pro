# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   =      link

SUBDIRS +=  google \
			facebook

# ------------
# Qt Settings
# ------------

QT *=		gui

# -----------------
# Modules Settings
# -----------------


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
