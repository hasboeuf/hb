# ----------------
# Module Settings
# ----------------

MODULE.NAME = HB
MODULE.PATH = ../..

# -----------------
# Project Settings
# -----------------

PROJECT.ID      = network-basic-common

# ---------------
# Debug Settings
# ---------------

# ------------
# QT Settings
# ------------

# -----------------
# Modules Settings
# -----------------

HB += network log tools

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
