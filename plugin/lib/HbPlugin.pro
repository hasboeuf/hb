# ----------------
# Module Settings
# ----------------

MODULE.NAME = hb
MODULE.PATH = ../..

# -----------------
# Project Settings
# -----------------


# ------------
# Qt Settings
# ------------

# -----------------
# Modules Settings
# -----------------

hb += HbLog HbTools

# -------------
# C++ Settings
# -------------

DEFINES += HB_PLUGIN_SHARED

# -----------------
# Install Settings
# -----------------


# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
