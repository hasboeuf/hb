# ----------------
# Module Settings
# ----------------

MODULE.NAME = hb
MODULE.PATH = ../..

# -----------------
# Project Settings
# -----------------

PROJECT.NAME    = HbNetworkUser
PROJECT.DIR     = network-example/network-user
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

hb += HbNetworkCommon HbNetwork HbLink HbLog HbTools

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
