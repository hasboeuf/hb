# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		../..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   =      network-user
PROJECT.NAME =      HbNetworkUser
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

HB  += tools log link network

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
