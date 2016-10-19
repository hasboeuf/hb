# ------------------------------
# Common Routines & Definitions
# ------------------------------

!include( $$(HBDIR)/utils.pri ): \
error( "QMake file utils.pri not found" )

# ----------------
# Module Settings
# ----------------

isEmpty( MODULE.NAME ) {

    # Current parsing file is the module definition.
    MODULE.NAME = $$basename(_PRO_FILE_)
    MODULE.NAME = $$replace( MODULE.NAME, .pro, )
    MODULE.PATH = $$clean_path($${PWD})

} else {
    isEmpty(MODULE.PATH) {
        error($${PROJECT.PRO}: MODULE.PATH not defined)
    }

    !isRelativePath(MODULE.PATH) {
        error( "$${PROJECT.PRO}: ${MODULE.PATH} must define a relative path" )
    }

    MODULE.PATH = $$clean_path($${_PRO_FILE_PWD_}/$${MODULE.PATH})
}

# -------------------
# QMake Dependencies
# -------------------

# ---------------
# QMake Settings
# ---------------

CONFIG -= flat

# ---------------
# QMake Includes
# ---------------

!include( $$(HBDIR)/rules.pri ): \
error( "QMake file rules.pri not found" )

