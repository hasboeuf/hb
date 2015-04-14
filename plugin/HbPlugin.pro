# ----------------
# Module Settings
# ----------------

MODULE.NAME = HB
MODULE.PATH = ..

# -----------------
# Project Settings
# -----------------

PROJECT.ID = plugin

# ------------
# Qt Settings
# ------------

# -----------------
# Modules Settings
# -----------------

HB += log tools

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
