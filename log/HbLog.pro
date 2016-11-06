# ----------------
# Module Settings
# ----------------

MODULE.NAME = hb
MODULE.PATH = ..

# -----------------
# Project Settings
# -----------------

PROJECT.NAME = HbLog

SUBDIRS += inputs \
           outputs \
           gui

EXCLUDED_HEADERS +=

# ------------
# Qt Settings
# ------------

# -----------------
# Modules Settings
# -----------------

hb += HbTools

# -------------
# C++ Settings
# -------------
DEFINES += HB_LOG_SHARED

# -----------------
# Install Settings
# -----------------


# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
