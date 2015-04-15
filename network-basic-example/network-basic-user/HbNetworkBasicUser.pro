# ----------------
# Module Settings
# ----------------

MODULE.NAME = HB
MODULE.PATH = ../..

# -----------------
# Project Settings
# -----------------

PROJECT.ID      = network-basic-user
PROJECT.NAME    = HbNetworkBasicUser
PROJECT.DIR     = network-basic-user
PROJECT.INTDIR  = network-basic-example
PROJECT.INSTALL = network-basic-example
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

HB += network-basic-common network link log tools

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
