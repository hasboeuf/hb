# ------------------------------
# Common Routines & Definitions
# ------------------------------

    !include( $${PWD}/utils.pri ): \
    error( "QMake file utils.pri not found" )

# -----------
# Qt Version
# -----------

    lessThan( QT_MAJOR_VERSION, 5 ) {
        error( "$${PROJECT.PRO}: Cannot build project with Qt $$[QT_VERSION] (QT 5 minimum is required)" )
    }

# ----------------
# Module Settings
# ----------------

    !contains( PROJECT.TYPE, subdirs ) {
        isEmpty( MODULE.NAME ) {
            error( "$${PROJECT.PRO}: $${MODULE.NAME} variable cannot be resolved" )
        }

        isEmpty( MODULE.PATH ) {
            error( "$${PROJECT.PRO}: $${MODULE.PATH} variable cannot be resolved" )
        }

        isRelativePath( MODULE.PATH ) {
            error( "$${PROJECT.PRO}: $${MODULE.PATH} must define an absolute path" )
        }

        checkFilepath( MODULE.PATH )

        MODULE.NAME = $$upper( $${MODULE.NAME} )

        # Conf file.
        MODULE_CONF_FILE = $$clean_path( $${MODULE.PATH}/$${MODULE.NAME}.conf )

        !include( $$MODULE_CONF_FILE ) {
            error( "$${PROJECT.PRO}: Configuration file $${MODULE_CONF} not found" )
        } else {
            message ( Configuration file $$MODULE_CONF_FILEPATH loaded. )
        }

        unset( MODULE_CONF_FILE )

        # Module install.
        MODULE.INSTALL = $$eval( $${MODULE.NAME}.INSTALL )
        isEmpty( MODULE.INSTALL ) {
            error( "Module install variable cannot be resolved" )
        }
    }

# -----------------
# Project Settings
# -----------------

    PROJECT.PATH = $${_PRO_FILE_PWD_}/

    # Project name.
    isEmpty( PROJECT.NAME ): {
        PROJECT.NAME = $$eval( $${MODULE.NAME}.$$upper( $${PROJECT.ID} ).NAME )
    }
    isEmpty( PROJECT.NAME ): {
        error( "Project name must be defined." )
    }
    # Project type
    isEmpty( PROJECT.TYPE ): {
        PROJECT.TYPE = $$eval( $${MODULE.NAME}.$$upper( $${PROJECT.ID} ).TYPE )
    }
    isEmpty( PROJECT.TYPE ): {
        error( "Project type must be defined." )
    }
    !contains( PROJECT.TYPE, app|dynlib|staticlib|subdirs ) {
        error( "$${PROJECT.PRO}: Project $${TARGET} must be of type app, dynlib, staticlib or subdirs" )
    }

    !contains( PROJECT.TYPE, subdirs ) {
        # Project id.
        isEmpty( PROJECT.ID ): {
            error( "Project id must be defined." )
        }
        # Project dir.
        isEmpty( PROJECT.DIR ): {
            PROJECT.DIR = $$eval( $${MODULE.NAME}.$$upper( $${PROJECT.ID} ).DIR )
        }
        isEmpty( PROJECT.DIR ): {
            error( "Project ($${PROJECT.NAME}) dir must be defined." )
        }
        # Project intermediate dir.
        isEmpty( PROJECT.INTDIR ): {
            PROJECT.INTDIR = $$eval( $${MODULE.NAME}.$$upper( $${PROJECT.ID} ).INTDIR )
        }
        isEmpty( PROJECT.INTDIR ): {
            PROJECT.INTDIR = .
        }
        # Project install.
        isEmpty( PROJECT.INSTALL ): {
            PROJECT.INSTALL = $$eval( $${MODULE.NAME}.$$upper( $${PROJECT.ID} ).INSTALL )
        }
        isEmpty( PROJECT.INSTALL ): {
           PROJECT.INSTALL = .
        }
    }

# ------------
# Qt Settings
# ------------

    CONFIG += qt warn_on thread largefile
    CONFIG -= warn_off lex yacc static shared
    CONFIG -= ordered no_empty_targets

    contains( PROJECT.TYPE, dynlib ): CONFIG += shared
    contains( PROJECT.TYPE, staticlib ): CONFIG += static
    contains( PROJECT.TYPE, subdirs ): CONFIG += ordered no_empty_targets

# -----------
# Qt Modules
# -----------

    QT *= core

# -----------------------
# Building Configuration
# -----------------------
    message( ------------------------------------ )
    message( QMake-ing $${PROJECT.NAME} projects. )
    message( ------------------------------------ )

    win32-msvc*|win32-g++: {
        message( "Compilator supported." )
    } else {
        error( "Compilator not supported." )
    }

    win32-g++: QMAKE_CXXFLAGS += -std=c++0x

    QMAKE_SPEC = $$(QMAKESPEC)
    isEmpty( QMAKE_SPEC ): QMAKE_SPEC = $$[QMAKESPEC]

    isEmpty( QMAKE_SPEC ) {
        error( "$${PROJECT.PRO}: Platform scope not defined" )
    }

    contains( QMAKE_HOST.arch, x86 ) {
        win32-msvc*: QMAKE_LFLAGS *= /MACHINE:X86
    }

    contains( QMAKE_HOST.ar-ch, x86_64 ) {
        win32-msvc*: QMAKE_LFLAGS *= /MACHINE:X64
    }

    BUILD.CONFIG = Qt$${QT_MAJOR_VERSION}$${QT_MINOR_VERSION}_$${QMAKE_SPEC}_$${QMAKE_HOST.arch}

    message("config=" $$BUILD.CONFIG)

    CONFIG( debug, debug|release ): BUILD.MODE = debug
    CONFIG( release, debug|release ): BUILD.MODE = release

    isEmpty( BUILD.MODE ) {
        error( "$${PROJECT.PRO}: Building mode cannot be resolved" )
    }

# ---------------------
# Modules Dependencies
# ---------------------

    defineTest( resolveModuleDependency ) {

        MODULE_NAME = $$1
        MODULE_CONF_FILE = $${MODULE_NAME}.conf

        # Internal dependency, conf file already included.
        equals( MODULE_NAME, $${MODULE.NAME} ) {
            MODULE_PATH = $${MODULE.PATH}
        }
        # External dependency
        else {
            MODULE_ENV_DIR = $($${MODULE_NAME}DIR)/
            MODULE_CONF_FILE = $$replaceString( MODULE_CONF_FILE, $$MODULE_ENV_DIR , )
            MODULE_PATH = $$MODULE_ENV_DIR

            !include( $$MODULE_CONF_FILE ) {
                error( "$${PROJECT.PRO}: Configuration file $${MODULE_CONF_FILE} not found" )
            } else {
                message ( Configuration file $$MODULE_CONF_FILE loaded. )
            }

            unset( MODULE_ENV_DIR )
        }

        unset( MODULE_CONF_FILE )

        isEmpty( MODULE_PATH ): error( Module path not defined.)

        MODULE_INC =	$${MODULE_PATH}/$$eval( $$upper( $${MODULE_NAME}.INSTALL ) )/inc
        MODULE_LIB =    $${MODULE_PATH}/$$eval( $$upper( $${MODULE_NAME}.INSTALL ) )/lib
        MODULE_BIN =    $${MODULE_PATH}/$$eval( $$upper( $${MODULE_NAME}.INSTALL ) )/bin

        PACKAGES = $$eval($$MODULE_NAME)
        for( PACKAGE, PACKAGES ) {

            PACKAGE_NAME    = $$eval( $$upper( $${MODULE_NAME}.$${PACKAGE}.NAME ) )
            PACKAGE_DIR     = $$eval( $$upper( $${MODULE_NAME}.$${PACKAGE}.DIR ) )
            PACKAGE_INTDIR  = $$eval( $$upper( $${MODULE_NAME}.$${PACKAGE}.INTDIR ) )
            PACKAGE_INSTALL = $$eval( $$upper( $${MODULE_NAME}.$${PACKAGE}.INSTALL ) )
            PACKAGE_QT      = $$eval( $$upper( $${MODULE_NAME}.$${PACKAGE}.QT ) )
            PACKAGE_TYPE    = $$eval( $$upper( $${MODULE_NAME}.$${PACKAGE}.TYPE ) )

            isEmpty( PACKAGE_NAME ): {
                error( PACKAGE_NAME not defined ($${PROJECT.NAME})($${MODULE_NAME}.$${PACKAGE}.NAME).)
            }
            isEmpty( PACKAGE_DIR  ): error( PACKAGE_DIR not defined.)
            isEmpty( PACKAGE_INTDIR  ): PACKAGE_INTDIR = .
            isEmpty( PACKAGE_TYPE ): error( PACKAGE_TYPE not defined.)
            isEmpty( PACKAGE_INSTALL ): PACKAGE_INSTALL = .

            # Internal dependency
            equals( MODULE_NAME, $${MODULE.NAME} ) {

                PACKAGE_INC = $${MODULE_PATH}/$${PACKAGE_INTDIR}/$${PACKAGE_DIR}/inc
                PACKAGE_LIB = $${MODULE_PATH}/$${PACKAGE_INTDIR}/$${PACKAGE_DIR}/lib/$${BUILD.CONFIG}
                PACKAGE_BIN = $${MODULE_PATH}/$${PACKAGE_INTDIR}/$${PACKAGE_DIR}/bin/$${BUILD.CONFIG}
            }
            # External dependency
            else {
                PACKAGE_INC = $${MODULE_INC}/$${PACKAGE_INSTALL}/$${PACKAGE_DIR}
                PACKAGE_LIB = $${MODULE_LIB}/$${BUILD.CONFIG}/$${PACKAGE_INSTALL}/
                PACKAGE_BIN = $${MODULE_BIN}/$${BUILD.CONFIG}/$${PACKAGE_INSTALL}/
            }

            *-g++: {
                equals ( PACKAGE_TYPE, staticlib ): {
                    PRE_TARGETDEPS += $$clean_path( $${PACKAGE_LIB}/$$fullTarget( PACKAGE_NAME, staticlib ) )
                }
            }
.
            QT *= $$PACKAGE_QT

            INCLUDEPATH *= $${PACKAGE_INC}

            message( inc=$$INCLUDEPATH )

            DEPENDPATH *= $$clean_path( $${PACKAGE_BIN} )

            CONFIG( debug, debug|release ): PACKAGE_NAME = $$replaceString( PACKAGE_NAME,, d )

            LIBS *= -L$$clean_path( $${PACKAGE_BIN} )
            LIBS *= -L$$clean_path( $${PACKAGE_LIB} )
            LIBS *= -l$${PACKAGE_NAME}

            unset( PACKAGE_NAME )
            unset( PACKAGE_DIR )
            unset( PACKAGE_INTDIR )
            unset( PACKAGE_INSTALL )
            unset( PACKAGE_QT )
            unset( PACKAGE_TYPE )
            unset( PACKAGE_INC )
            unset( PACKAGE_LIB )
            unset( PACKAGE_BIN )
        }

        export( QT )
        export( INCLUDEPATH )
        export( DEPENDPATH )
        export( LIBS )
        export( PRE_TARGETDEPS )

        unset( MODULE_INC )
        unset( MODULE_LIB )
        unset( MODULE_BIN )
        unset( MODULE_PATH )
        unset( MODULE_NAME )
    }

    LINKED_MODULES *= $${MODULE.NAME} # To force inclusion of .conf file.
    for( LINKED_MODULE, LINKED_MODULES ) {
        resolveModuleDependency( $$LINKED_MODULE )
    }

    message( Qt=$$QT )

# ----------------
# Target Settings
# ----------------

    contains( PROJECT.TYPE, app ): TEMPLATE = app
    contains( PROJECT.TYPE, dynlib|staticlib ): TEMPLATE = lib
    contains( PROJECT.TYPE, subdirs ): TEMPLATE = subdirs

    contains( PROJECT.TYPE, app ) {
        CONFIG( debug, debug|release ): CONFIG *= console
    }

    contains( PROJECT.TYPE, subdirs ) {
        isEmpty( SUBDIRS ): error( "$${PROJECT.PRO}: Variable ${SUBDIRS} must be defined" )
    }

# ---------------
# Projects Files
# ---------------

!contains( PROJECT.TYPE, subdirs ) {

    EXTS_H = .h
    EXTS_CPP = .cpp
    EXT_UI = .ui
    EXT_TS = .ts
    EXT_RC = .qrc

    defineTest( scanDirectories ) {

        subdirs = $$eval( $${1} )
        !contains( subdirs, . ): subdirs += .
        subdirs = $$unique( subdirs )
        checkFilepath( subdirs )
        subdirs = $$replaceString( subdirs, ./ )

        for( subdir, subdirs ) {
            !isRelativePath( subdir ): \
                error( "$${PROJECT.PRO}: ${$${1}.SUBDIRS} must define a relative path" )

            checkFilepath( subdir )

            for( EXT_H, EXTS_H ) {
                exists( $${PROJECT.PATH}/inc/$${subdir}/*$${EXT_H} ) {
                    HEADERS *= $$files( $$clean_path( $${PROJECT.PATH}/inc/$${subdir}/*$${EXT_H} ) ) # $$files( $$clean_path( inc/$${subdir}/*$${EXT_H} ) )
                    # INCLUDEPATH += $$clean_path( $${PROJECT.PATH}/inc/$${subdir} ) We wont that.
                }
            }

            for( EXT_CPP, EXTS_CPP ) {
                exists( $${PROJECT.PATH}/src/$${subdir}/*$${EXT_CPP} ) {
                    SOURCES *= $$files( $$clean_path( $${PROJECT.PATH}/src/$${subdir}/*$${EXT_CPP} ) )
                }
            }

            exists( $${PROJECT.PATH}/forms/$${subdir}/*$${EXT_UI} ) {
                FORMS *= $${PROJECT.PATH}/forms/$${subdir}/*$${EXT_UI}
            }

            exists( $${PROJECT.PATH}/resources/$${subdir}/*$${EXT_RC} ) {
                RESOURCES *= $${PROJECT.PATH}/resources/$${subdir}/*$${EXT_RC}
            }
        }

        unset( subdir )

        export( INCLUDEPATH )
        export( HEADERS )
        export( SOURCES )
        export( FORMS )
        export( RESOURCES )
    }

    INCLUDEPATH += $$clean_path( $${PROJECT.PATH}/inc )

    SUBDIRS *= .
    scanDirectories( SUBDIRS )
}
	
# ----------------
# Generated Files
# ----------------

    OBJECTS_DIR = $${PROJECT.PATH}/generated/$${BUILD.CONFIG}/$${BUILD.MODE}/obj/
    MOC_DIR = $${PROJECT.PATH}/generated/$${BUILD.CONFIG}/$${BUILD.MODE}/moc/
    RCC_DIR = $${PROJECT.PATH}/generated/$${BUILD.CONFIG}/$${BUILD.MODE}/qrc/
    UI_DIR = $${PROJECT.PATH}/generated/$${BUILD.CONFIG}/$${BUILD.MODE}/uic/ # TODO est-ce utile de differencier par config?

# ---------------
# Build Settings
# ---------------

    !contains( PROJECT.TYPE, subdirs ) {
        contains( PROJECT.TYPE, app ): OUTPUT_DIR = bin/$${BUILD.CONFIG}
        contains( PROJECT.TYPE, staticlib ): OUTPUT_DIR = lib/$${BUILD.CONFIG}
	contains( PROJECT.TYPE, dynlib ) {
                OUTPUT_DIR = lib/$${BUILD.CONFIG}
                OUTPUT_DIR_DLL = bin/$${BUILD.CONFIG}
	}
	
	isEmpty( OUTPUT_DIR ) {
		error( "$${PROJECT.PRO}: Project $${TARGET} output directory cannot be resolved" )
	}
	
        DESTDIR = $$clean_path( $${PROJECT.PATH}/$${OUTPUT_DIR}/ )

	!isEmpty( OUTPUT_DIR_DLL ): DLLDESTDIR = $${PROJECT.PATH}/$${OUTPUT_DIR_DLL}/

        TARGET = $${PROJECT.NAME}
        CONFIG( debug, debug|release ): TARGET = $$replaceString( TARGET,, d )
    }

# ---------------
# Clean Settings
# ---------------

    defineTest( cleanFiles ) {

        files = $$1
        basename = $$basename( files )

        !isEmpty( basename ) {

            files = $$sysFilepath( $${files} )

            isEmpty( QMAKE_CLEAN ): QMAKE_CLEAN += $${files} $$escape_expand(\\n\\t)
            else: QMAKE_CLEAN += -$(DEL_FILE) $${files} $$escape_expand(\\n\\t)

            export( QMAKE_CLEAN )
        }
    }

    defineTest( cleanDirectory ) {

        directory = $$clean_path($$1)

        exists($$directory)
        {

            directory = $$sysFilepath( $${directory} )
            emptymode = $$2

            #isEmpty( QMAKE_CLEAN ): QMAKE_CLEAN += null $$escape_expand(\\n\\t)

            unix {

                contains( emptymode, true ) {

                        QMAKE_CLEAN += @find $${directory} -type d -depth -empty -exec rmdir {}
                        QMAKE_CLEAN += $$escape_expand(\\n\\t) -@$${QMAKE_DEL_DIR} $${directory}
                }

                else: QMAKE_CLEAN += -@$${QMAKE_DEL_FILE} -r $${directory}
                QMAKE_CLEAN += $$escape_expand(\\n\\t)
            }

            win32 {

                contains( emptymode, true ) {

                    QMAKE_CLEAN += -@for /f %%f in (\' dir /b %%d ^| find /v /c \""\" \""\" \') do @if '%%f'=='0' rd /q %%d # Delete folder if empty
                    #QMAKE_CLEAN += $$escape_expand(\\n\\t) -@$${QMAKE_DEL_DIR} $${directory} # Force to add \n in the makefile
                }
                else: QMAKE_CLEAN += -$${QMAKE_DEL_DIR} /s $${directory}
                #QMAKE_CLEAN += $$escape_expand(\\n\\t)
            }

            export( QMAKE_CLEAN )
        }
    }

    build_pass {

        #cleanFiles( $${DESTDIR}/$${TARGET}.* )
        #!isEmpty( DLLDESTDIR ): cleanFiles( $${DLLDESTDIR}/$${TARGET}.* )

        cleanDirectory( $${PROJECT.PATH}/generated/$${BUILD.CONFIG}/$${BUILD.MODE}/ )
        #cleanDirectory( $${PROJECT.PATH}/generated/$${BUILD.CONFIG}/, true )
        #cleanDirectory( $${PROJECT.PATH}/generated/, true )

        isEmpty( OUTPUT_DIR ) {

            #cleanDirectory( $${DESTDIR}, true )
            #!isEmpty( DLLDESTDIR ): cleanDirectory( $${DLLDESTDIR}/, true )
        }

        else {

            #cleanDirectory( $${PROJECT.PATH}/$${OUTPUT_DIR}/, true )
            #cleanDirectory( $${PROJECT.PATH}/$$dirname( OUTPUT_DIR )/, true )

            !isEmpty( DLLDESTDIR ) {

                #cleanDirectory( $${PROJECT.PATH}/$${OUTPUT_DIR_DLL}/, true )
                #cleanDirectory( $${PROJECT.PATH}/$$dirname( OUTPUT_DIR_DLL )/, true )
            }
        }

        #QMAKE_CLEAN += -$(DEL_FILE)
    }

# -----------------
# Install Settings
# -----------------

# General variables.
PROJECT_INC  = $$clean_path( $${PROJECT.PATH}/inc/ )
PROJECT_UI   = $$UI_DIR
PROJECT_LIB  = $$clean_path( $${PROJECT.PATH}/lib/$${BUILD.CONFIG}/ )
PROJECT_BIN  = $$clean_path( $${PROJECT.PATH}/bin/$${BUILD.CONFIG}/ )
PROJECT_TYPE = $${PROJECT.TYPE}
PROJECT_NAME = $${PROJECT.NAME}
PROJECT_DIR  = $${PROJECT.DIR}
PROJECT_INSTALL = $${PROJECT.INSTALL}

DELIVERY_INC = $$clean_path( $${MODULE.PATH}/$$eval( $${MODULE.NAME}.INSTALL )/inc/$${PROJECT_INSTALL}/$${PROJECT_DIR} )
DELIVERY_LIB = $$clean_path( $${MODULE.PATH}/$$eval( $${MODULE.NAME}.INSTALL )/lib/$${BUILD.CONFIG}/$${PROJECT_INSTALL} )
DELIVERY_BIN = $$clean_path( $${MODULE.PATH}/$$eval( $${MODULE.NAME}.INSTALL )/bin/$${BUILD.CONFIG}/$${PROJECT_INSTALL} )

# Copy header files.
{
    contains( PROJECT_TYPE , dynlib|staticlib ) {
        # Copy all headers.
        for( HEADER_DIR, SUBDIRS ) {
            HEADERS_TO_COPY = $$files( $$clean_path( $$PROJECT_INC/$$HEADER_DIR/*.h ) )

            win32-g++: {
                !equals( HEADER_DIR, . ) {
                    suffix = _$$HEADER_DIR
                } else { suffix = }

                install_name = copy_headers$$suffix

                $${install_name}.files = $$HEADERS_TO_COPY
                $${install_name}.path  = $$clean_path( $$DELIVERY_INC/$${HEADER_DIR} )

                INSTALLS *= $${install_name}
            }
            win32-msvc*: {
                for( HEADER_TO_COPY, HEADERS_TO_COPY ) {
                    QMAKE_POST_LINK += $${QMAKE_COPY} \
                                        \"$$HEADER_TO_COPY\" \
                                        \"$$clean_path( $$DELIVERY_INC/$${HEADER_DIR}/* )\" $$escape_expand(\n\t)
                }
            }

            unset( HEADERS_TO_COPY )
        }

        # Remove excluded headers.
        for( EXCLUDED_HEADER, EXCLUDED_HEADERS ) {
            !isRelativePath( EXCLUDED_HEADER ): \
                error( "Excluded headers must define a relative path." )

            # ex: gui/*.h
            EXCLUDED_HEADER = $$clean_path( $$replaceString( EXCLUDED_HEADER, $$PROJECT_INC/, ) )

            # ex: C:/hb/log/gui/*.h
            EXCLUDED_HEADER_FILES *= $$files( $$EXCLUDED_HEADER )

            # ex: C:/hb/log/gui/foo1.h C:/hb/log/gui/foo2.h

            for( EXCLUDED_HEADER_FILE, EXCLUDED_HEADER_FILES ) {
                # Replace root path.
                EXCLUDED_HEADER_FILES_TMP *= $$clean_path( $$replace( EXCLUDED_HEADER_FILE, $$PROJECT_INC, $$DELIVERY_INC ) )
            }
            EXCLUDED_HEADER_FILES = $$EXCLUDED_HEADER_FILES_TMP
            unset( EXCLUDED_HEADER_FILES_TMP )

            # ex: C:/hb/delivery/inc/log/gui/foo1.h C:/hb/delivery/inc/log/gui/foo2.h
            EXCLUDED_HEADERS_TMP *= $$EXCLUDED_HEADER_FILES
            unset( EXCLUDED_HEADER_FILES )
        }
        EXCLUDED_HEADERS = $$EXCLUDED_HEADERS_TMP

        unset( EXCLUDED_HEADERS_TMP )
        unset( EXCLUDED_HEADER )
    }
}

# Copy ui files.
{
    contains( PROJECT_TYPE , dynlib|staticlib ) {
        UI_FILES = $$clean_path( $${PROJECT_UI}/ui_*.h )
        exists( $$UI_FILES ) {
            win32-g++: {
                copy_ui.files = $$UI_FILES
                copy_ui.path  = $$DELIVERY_INC

                INSTALLS *= copy_ui
            }
            win32-msvc*: {

                QMAKE_POST_LINK += $${QMAKE_COPY} \
                                    \"$${UI_FILES}\" \
                                    \"$${DELIVERY_INC}/* )\" $$escape_expand(\n\t)
            }
        }

        unset( UI_FILES )
    }
}

# Copy lib file.
{
    contains( PROJECT_TYPE , dynlib|staticlib ) {
        FULLPATH_LIB = $$DESTDIR/$$fullTarget( PROJECT_NAME, staticlib ) # Force to staticlib to get .lib.

        win32-g++ : {
            copy_lib.files = $$FULLPATH_LIB
            copy_lib.path  = $$DELIVERY_LIB

            INSTALLS *= copy_lib
        }
        win32-msvc* : {
            QMAKE_POST_LINK += $${QMAKE_COPY} \
                                \"$${FULLPATH_LIB}\" \
                                \"$${DELIVERY_LIB}/*\" $$escape_expand(\n\t)
        }

        unset( FULLPATH_LIB )
    }
}

# Copy dll and pdb file.
{
    contains( PROJECT_TYPE, dynlib ) {
        FULLPATH_DLL = $$DESTDIR/$$fullTarget( PROJECT_NAME, dynlib )

        win32-g++ : {
            copy_dll.files = $$FULLPATH_DLL
            copy_dll.path  = $$DELIVERY_BIN

            INSTALLS *= copy_dll
        }
        win32-msvc* : {
            FULLPATH_PDB = $$DESTDIR/$$replaceString( TARGET,, .pdb )

            QMAKE_POST_LINK += $${QMAKE_COPY} \
                                \"$${FULLPATH_DLL}\" \
                                \"$${DELIVERY_BIN}/*\" $$escape_expand(\n\t)

            QMAKE_POST_LINK += $${QMAKE_COPY} \
                                \"$${FULLPATH_PDB}\" \
                                \"$${DELIVERY_BIN}/*\" $$escape_expand(\n\t)
        }

        unset( FULLPATH_DLL )
    }
}

# Copy exe file.
{
    contains( PROJECT_TYPE, app ) {
        FULLPATH_BIN = $$DESTDIR/$$fullTarget( PROJECT_NAME, app )
        win32-g++ : {
            copy_exe.files = $$FULLPATH_BIN
            copy_exe.path  = $$DELIVERY_BIN

            INSTALLS *= copy_exe
        }
        win32-msvc* : {
            QMAKE_POST_LINK += $${QMAKE_COPY} \
                                \"$${FULLPATH_BIN}\" \
                                \"$${DELIVERY_BIN}/*\" $$escape_expand(\n\t)
        }

        unset( FULLPATH_BIN )
    }
}

# Debug
win32-g++: message ( post_build=$$INSTALLS )
win32-msvc*: message ( post_build=$$QMAKE_POST_LINK )
