# ----------------
# Module Settings
# ----------------

MODULE.NAME = HB
MODULE.PATH = ../..

# -----------------
# Project Settings
# -----------------

PROJECT.ID      = network-common
PROJECT.NAME    = HbNetworkCommon
PROJECT.DIR     = network-common
PROJECT.INTDIR  = network-example
PROJECT.INSTALL = network-example
PROJECT.QT      = gui widgets network
PROJECT.TYPE    = staticlib

# ---------------
# Debug Settings
# ---------------

# ------------
# Qt Settings
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
