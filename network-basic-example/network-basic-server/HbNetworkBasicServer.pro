# ----------------
# Module Settings
# ----------------

MODULE.NAME = hb
MODULE.PATH = ../..

# -----------------
# Project Settings
# -----------------

PROJECT.NAME    = HbNetworkBasicServer
PROJECT.DIR     = network-basic-example/network-basic-server
#PROJECT.INTDIR  = network-basic-example
#PROJECT.INSTALL = network-basic-example
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

hb += HbNetworkBasicCommon HbNetwork HbLink HbLog HbTools

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
