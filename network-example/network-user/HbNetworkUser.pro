# ----------------
# Module Settings
# ----------------

MODULE.NAME = HB
MODULE.PATH = ../..

# -----------------
# Project Settings
# -----------------

PROJECT.ID      = network-user
PROJECT.NAME    = HbNetworkUser
PROJECT.DIR     = network-user
PROJECT.INTDIR  = network-example
PROJECT.INSTALL = network-example
PROJECT.QT      = gui widgets network
PROJECT.TYPE    = app

# ---------------
# Debug Settings
# ---------------

# ------------
# Qt Settings
# ------------


# -----------------
# Modules Settings
# -----------------

HB += network-common network link log tools

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
