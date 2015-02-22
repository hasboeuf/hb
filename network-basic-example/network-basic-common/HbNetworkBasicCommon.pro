# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		../..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   =      network-basic-common
PROJECT.NAME =      HbNetworkBasicCommon
PROJECT.TYPE =      staticlib

# ---------------
# Debug Settings
# ---------------

# ------------
# QT Settings
# ------------

QT *= gui widgets network

# -----------------
# Modules Settings
# -----------------

HB  += tools log network

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
