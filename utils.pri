# -------------------
# Common Definitions
# -------------------

PROJECT.PRO = $$basename( _PRO_FILE_ )

# ---------------
# QMake Settings
# ---------------

unix {

#	QMAKE_COPY			= cp -f
#	QMAKE_COPY_FILE			= $(COPY)
#	QMAKE_COPY_DIR			= $(COPY) -r
#	QMAKE_MOVE			= mv -f
#	QMAKE_DEL_FILE			= rm -f
#	QMAKE_DEL_DIR			= rmdir
#	QMAKE_MKDIR			= mkdir -p
}

win32 {

        QMAKE_COPY		= xcopy /s /f /y /i #copy /y
#	QMAKE_COPY_FILE		= $(COPY)
        QMAKE_COPY_DIR          = xcopy /s /f /y /i
#	QMAKE_MOVE              = move
        QMAKE_MKDIR             = mkdir
        QMAKE_DEL_FILE          = del /f /q		# QMAKE_DEL_FILE = del
        QMAKE_DEL_DIR           = rmdir /q		# QMAKE_DEL_DIR = rmdir
}

# -------------------------
# Common Filepath Routines
# -------------------------

defineReplace( sysFilepath ) {

    filename = $$1
    filename ~= s,/,$${QMAKE_DIR_SEP},g

    return( $${filename} )
}

defineTest( checkFilepath ) {

        variable = $$1
        filepaths = $$eval( $${variable} )

        for( filepath, filepaths ) {

                spaces = $$find( filepath, " " )
                !isEmpty( spaces ): error( "$${PROJECT.PRO}: Path \"$${filepath}\" defined in ${$${variable}} shall not contains spaces" )
        }
}

defineTest( isRelativePath ) {

        filepath = $$first( $$1 )

        contains( QMAKE_HOST.os, Windows ){
            relative = $$find( filepath, ^[A-Za-z]:.* )
        }
        else { # uname -o
            relative = $$find( filepath, ^/.* )
        }

        isEmpty( relative ): relative = true
        else: relative = false

        return( $$relative )
}


# -------------------------
# Common Variable Routines
# -------------------------

defineReplace( resolveVariable ) {

    string = $$eval( $$1 )
    variable = $$2

    !isEmpty( variable ) {

                name = $$eval( $${variable}.name )
                value = $$eval( $${variable}.value )

                !isEmpty( $${value} ): string = $$replace( string, %$${name}%, $$eval( $${value} ) )
        }

        return( $${string} )
}

defineReplace( resolveVariables ) {

    string = $$eval( $$1 )
    variables = $$eval( PROJECT.VAR )

        for( variable, variables ) {

                resolve = $$find( string, $${variable} )
                !isEmpty( resolve ): string = $$resolveVariable( string, $${variable} )
        }

        return( $${string} )
}


# ----------------------
# Common Other Routines
# ----------------------

defineReplace( replaceString ) {

        string = $$eval( $$1 )
        prepend = $$2
        append = $$3

        !isEmpty( string ): for( item, string ) {
                result += $$join( item,, $${prepend}, $${append} )
        }

        return( $${result} )
}

defineReplace( fullTarget ) {

        target = $$eval( $$1 )
        type = $$2

        !contains( type, app|dynlib|staticlib ): \
            error( "$${PROJECT.PRO}: Project $${TARGET} must be of type app, dynlib or staticlib" )

        *-msvc*: {
                CONFIG( debug, debug|release ): target = $$replaceString( target,, d )
                contains( type, app ): target = $$replaceString( target,, .exe )
                contains( type, dynlib ): target = $$replaceString( target,, .dll )
                contains( type, staticlib ): target = $$replaceString( target,, .lib )
        }

        else: mingw: {

                CONFIG( debug, debug|release ): target = $$replaceString( target,, d )
                contains( type, app ): target = $$replaceString( target,, .exe )
                contains( type, dynlib ): target = $$replaceString( target,, .dll )
                contains( type, staticlib ): target = $$replaceString( target, lib, .a )
        }

        else: unix: {

                CONFIG( debug, debug|release ): target = $$replaceString( target,, d )
                contains( type, dynlib ): target = $$replaceString( target, lib, .so )
                contains( type, staticlib ): target = $$replaceString( target, lib, .a )
        }

        return( $${target} )
}
