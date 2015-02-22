# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		../..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   =      network-basic-user
PROJECT.NAME =      HbNetworkBasicUser
PROJECT.TYPE =      app

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

HB  += tools log link network network-basic-common

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
