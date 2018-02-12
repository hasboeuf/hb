# ----------------
# Module Settings
# ----------------

MODULE.NAME = hb
MODULE.PATH = ../../..

# -----------------
# Project Settings
# -----------------

PROJECT.TYPE = test

# ------------
# Qt Settings
# ------------


# -----------------
# Modules Settings
# -----------------

hb += HbTools

# -------------
# C++ Settings
# -------------
DEFINES +=

# -----------------
# Install Settings
# -----------------

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
