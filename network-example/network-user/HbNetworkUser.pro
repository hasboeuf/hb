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
PROJECT.DIR     = network-server
PROJECT.INTDIR  = network-example
PROJECT.INSTALL = network-example
PROJECT.QT      = gui widgets network
PROJECT.TYPE    = app

# ---------------
# Debug Settings
# ---------------

# ------------
# QT Settings
# ------------


# -----------------
# Modules Settings
# -----------------

HB += network link log tools

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
