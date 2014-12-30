# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   =      log
PROJECT.NAME =		HbLog
PROJECT.TYPE =		dynlib

SUBDIRS +=	inputs \
			outputs \
			gui
EXCLUDED_HEADERS +=

# ------------
# Qt Settings
# ------------

QT *=		xml widgets network

# -----------------
# Modules Settings
# -----------------

HB +=		tools

# -------------
# C++ Settings
# -------------
DEFINES += HB_LOG_BUILD

# -----------------
# Install Settings
# -----------------


# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
