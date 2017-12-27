# ----------------
# Module Settings
# ----------------

MODULE.NAME = hb
MODULE.PATH = ../../..

# -----------------
# Project Settings
# -----------------

PROJECT.NAME = HbNetworkBasicCommon

# ---------------
# Debug Settings
# ---------------

# ------------
# Qt Settings
# ------------

# -----------------
# Modules Settings
# -----------------

hb += HbNetwork HbLog HbTools

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
