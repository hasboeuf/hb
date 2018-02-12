# ----------------
# Module Settings
# ----------------

MODULE.NAME = hb
MODULE.PATH = ../../..

# -----------------
# Project Settings
# -----------------

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
