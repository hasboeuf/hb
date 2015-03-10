# ------------------------------
# Common Routines & Definitions
# ------------------------------

!include( $$(HBDIR)/utils.pri ): \
error( "QMake file utils.pri not found" )

# ----------------
# Module Settings
# ----------------

isEmpty( MODULE.NAME ) {

	MODULE.NAME = $$basename( _FILE_ )
	MODULE.NAME = $$replace( MODULE.NAME, .pri, )
}

!isEmpty( MODULE.PATH ) {
	!isRelativePath( MODULE.PATH ) {
            error( "$$basename( _PRO_FILE_ ) : ${MODULE.PATH} must define a relative path" )
	}
	
        MODULE.PATH = $${_PRO_FILE_PWD_}/$${MODULE.PATH}
}
else: MODULE.PATH = $${PWD}

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

