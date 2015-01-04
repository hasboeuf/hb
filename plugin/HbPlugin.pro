# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   =          plugin

# ------------
# Qt Settings
# ------------

QT *= gui widgets

# -----------------
# Modules Settings
# -----------------

HB += tools log

# -------------
# C++ Settings
# -------------


# -----------------
# Install Settings
# -----------------


# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
