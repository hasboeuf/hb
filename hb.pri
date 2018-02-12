# ------------------------------
# Common Routines & Definitions
# ------------------------------

!include( $$(HB_HOME)/utils.pri ): \
error( "QMake file utils.pri not found" )

# ----------------
# Module Settings
# ----------------

isEmpty( MODULE.NAME ) {

    # Current parsing file is the module definition.
    MODULE.NAME = $$basename(_PRO_FILE_)
    MODULE.NAME = $$replace( MODULE.NAME, .pro, )
    MODULE.PATH = $$clean_path($$PWD)

} else {
    isEmpty(MODULE.PATH) {
        error($${PROJECT.PRO}: MODULE.PATH not defined)
    }

    !isRelativePath(MODULE.PATH) {
        error( "$${PROJECT.PRO}: ${MODULE.PATH} must define a relative path" )
    }

    MODULE.PATH = $$clean_path($$PWD) # /home/.../hb

    PRO_FILE = $$_PRO_FILE_ # /home/.../hb/tools/lib/HbTools.pro
    PROJECT.DIR = $$relative_path($$dirname(PRO_FILE), $${MODULE.PATH}) # tools/lib
    PROJECT.NAME = $$basename(PRO_FILE) # HbTools.pro
    PROJECT.NAME = $$replace(PROJECT.NAME, .pro, ) # HbTools
    unset(PRO_FILE)
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

!include( $$(HB_HOME)/rules.pri ): \
error( "QMake file rules.pri not found" )

