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

        # Module requirements.
        MODULE.INSTALL = $$eval( $${MODULE.NAME}.INSTALL )
        isEmpty( MODULE.INSTALL ) {
            error( "Module install variable cannot be resolved" )
        }

        MODULE.LINKTYPE = $$eval( $${MODULE.NAME}.LINKTYPE )
        isEmpty( MODULE.LINKTYPE ) {
            error( "Module link type variable cannot be resolved" )
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
    # Project type.
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
        # Project Qt.
        isEmpty( PROJECT.QT ): {
            PROJECT.QT = $$eval( $${MODULE.NAME}.$$upper( $${PROJECT.ID} ).QT )
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

    CONFIG -= warn_off lex yacc static shared
    CONFIG -= ordered no_empty_targets
    CONFIG += qt warn_on thread largefile

    android: {
        CONFIG += mobility
    }

    contains( PROJECT.TYPE, app ):{
        winphone|winrt: {
            CONFIG += windeployqt
        }
    }

    contains( PROJECT.TYPE, dynlib ): CONFIG += shared
    contains( PROJECT.TYPE, staticlib ): CONFIG += static
    contains( PROJECT.TYPE, subdirs ): CONFIG += ordered no_empty_targets

# -----------
# Qt Modules
# -----------

    QT *= core
    QT *= $${PROJECT.QT}

# -----------------------
# Building Configuration
# -----------------------
    message( QMake-ing $${PROJECT.NAME} projects. )

    *msvc*|*g++*|winphone: {
        message( "Compilator supported." )
    } else {
        error( "Compilator not supported." )
    }

    *g++*: {
        QMAKE_CXXFLAGS += -std=c++0x
    }

    QMAKE_SPEC = $$(QMAKESPEC)
    isEmpty( QMAKE_SPEC ): QMAKE_SPEC = $$[QMAKESPEC]

    isEmpty( QMAKE_SPEC ) {
        error( "$${PROJECT.PRO}: Platform scope not defined. Is QMAKESPEC set?" )
    }

    contains( QMAKE_HOST.arch, x86 ) {
        *msvc*: QMAKE_LFLAGS *= /MACHINE:X86
    }

    contains( QMAKE_HOST.arch, x86_64 ) {
        *msvc*: QMAKE_LFLAGS *= /MACHINE:X64
    }


    BUILD.CONFIG = Qt$${QT_MAJOR_VERSION}$${QT_MINOR_VERSION}_$${QMAKE_SPEC}_$${QMAKE_HOST.arch}
    contains( $${MODULE.NAME}.LINKTYPE, staticlib ) {
        BUILD.CONFIG = $$replaceString( BUILD.CONFIG,, _static )
        BUILD.CONFIG = $$replace( BUILD.CONFIG, \\+, p ) # ar compiler does not handle path with '+' symbol.
    }

    CONFIG( debug, debug|release ): BUILD.MODE = debug
    CONFIG( release, debug|release ): BUILD.MODE = release

    isEmpty( BUILD.MODE ) {
        error( "$${PROJECT.PRO}: Building mode cannot be resolved" )
    }

    contains( $${MODULE.NAME}.LINKTYPE, dynlib ):{
        DEFINES += HB_SHARED
    }

    HB_DEV = $$(HBDEV)
    !isEmpty( HB_DEV ) {
        DEFINES += DEV
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
                message( Configuration file $$MODULE_CONF_FILE loaded. )
            }

            unset( MODULE_ENV_DIR )
        }

        unset( MODULE_CONF_FILE )

        isEmpty( MODULE_PATH ): error( Module path not defined.)

        MODULE_LINKTYPE = $$eval( $${MODULE_NAME}.LINKTYPE )
        MODULE_INC      = $${MODULE_PATH}/$$eval( $$upper( $${MODULE_NAME}.INSTALL ) )/inc
        MODULE_LIB      = $${MODULE_PATH}/$$eval( $$upper( $${MODULE_NAME}.INSTALL ) )/lib
        MODULE_BIN      = $${MODULE_PATH}/$$eval( $$upper( $${MODULE_NAME}.INSTALL ) )/bin
        MODULE_CONFIG   = Qt$${QT_MAJOR_VERSION}$${QT_MINOR_VERSION}_$${QMAKE_SPEC}_$${QMAKE_HOST.arch}

        contains( $${MODULE_NAME}.LINKTYPE, staticlib ) {
            MODULE_CONFIG = $$replaceString( MODULE_CONFIG,, _static )
            MODULE_CONFIG = $$replace( MODULE_CONFIG, \\+, p ) # ar compiler does not handle path with '+' symbol.
        }

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

                PACKAGE_INC =  $${MODULE_PATH}/$${PACKAGE_INTDIR}/$${PACKAGE_DIR}/inc
                PACKAGE_INC += $${MODULE_PATH}/$${PACKAGE_INTDIR}/$${PACKAGE_DIR}/generated/$${BUILD.CONFIG}/$${BUILD.MODE}/uic/
                PACKAGE_LIB =  $${MODULE_PATH}/$${PACKAGE_INTDIR}/$${PACKAGE_DIR}/lib/$${BUILD.CONFIG}
                PACKAGE_BIN =  $${MODULE_PATH}/$${PACKAGE_INTDIR}/$${PACKAGE_DIR}/bin/$${BUILD.CONFIG}
            }
            # External dependency
            else {
                PACKAGE_INC = $${MODULE_INC}/$${PACKAGE_INSTALL}/$${PACKAGE_DIR}
                PACKAGE_LIB = $${MODULE_LIB}/$${MODULE_CONFIG}/$${PACKAGE_INSTALL}/
                PACKAGE_BIN = $${MODULE_BIN}/$${MODULE_CONFIG}/$${PACKAGE_INSTALL}/
            }

            *g++*: {
                equals ( PACKAGE_TYPE, staticlib ): {
                    PRE_TARGETDEPS += $$clean_path( $${PACKAGE_LIB}/$$fullTarget( PACKAGE_NAME, staticlib ) )
                }
            }
.
            QT *= $$PACKAGE_QT

            INCLUDEPATH *= $${PACKAGE_INC}

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

# ----------------
# Target Settings
# ----------------

    contains( PROJECT.TYPE, app ) {
        TEMPLATE = app

        isEmpty( PROJECT.ICON ) {
            win32: RC_ICONS = $$clean_path( $$(HBDIR)/tools/resources/HbLogo.ico ) # Default HB icon.
        } else: {
            win32: RC_ICONS = $${PROJECT.ICON}
        }
    }

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
    UI_DIR = $${PROJECT.PATH}/generated/$${BUILD.CONFIG}/$${BUILD.MODE}/uic/

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
        CONFIG( debug, debug|release ):      TARGET = $$replaceString( TARGET,, d )
    }

# ------------------------
# Install & Clean Settings
# ------------------------

isEmpty( $${MODULE.NAME}.NO_INSTALL_TARGETS ) {
    defineTest( addCopyEvent ) {

        files        = $$1
        dest_path    = $$clean_path( $$2 )
        install_name = $$3

        *g++*: {
            $${install_name}.files = $$files
            $${install_name}.path  = $$clean_path( $$dest_path )

            INSTALLS *= $${install_name}

            export( $${install_name}.files )
            export( $${install_name}.path )
            export( INSTALLS )
        }
        *msvc*: {
            for( file, files ) {
                QMAKE_POST_LINK += $${QMAKE_COPY} \
                                    \"$$file\" \
                                    \"$$dest_path/* )\" $$escape_expand(\n\t)
            }

            export( QMAKE_POST_LINK )
        }
    }

    defineTest( addCleanFileEvent ) {
        file = $$1

        QMAKE_CLEAN *= $$file
        export( QMAKE_CLEAN )
    }

    defineTest( addCleanDirEvent ) {
        dir = $$1

        QMAKE_CLEAN *= $$dir
        export( QMAKE_CLEAN )
    }


    # Local
    PROJECT_INC       = $$clean_path( $${PROJECT.PATH}/inc/ )
    PROJECT_UI        = $$UI_DIR
    PROJECT_TYPE      = $${PROJECT.TYPE}
    PROJECT_NAME      = $${PROJECT.NAME}
    PROJECT_DIR       = $$clean_path( $${PROJECT.DIR} )
    PROJECT_INSTALL   = $$clean_path( $${PROJECT.INSTALL} )
    PROJECT_LIB       = $$clean_path( $${PROJECT.PATH}/lib/$${BUILD.CONFIG}/ )
    PROJECT_BIN       = $$clean_path( $${PROJECT.PATH}/bin/$${BUILD.CONFIG}/ )
    PROJECT_GENERATED = $$clean_path( $${PROJECT.PATH}/generated/$${BUILD.CONFIG}/$${BUILD.MODE} )

    # Delivery
    DELIVERY_LIB      = $$clean_path( $${MODULE.PATH}/$$eval( $${MODULE.NAME}.INSTALL )/lib/$${BUILD.CONFIG}/$${PROJECT_INSTALL} )
    DELIVERY_BIN      = $$clean_path( $${MODULE.PATH}/$$eval( $${MODULE.NAME}.INSTALL )/bin/$${BUILD.CONFIG}/$${PROJECT_INSTALL} )
    DELIVERY_INC      = $$clean_path( $${MODULE.PATH}/$$eval( $${MODULE.NAME}.INSTALL )/inc/$${PROJECT_INSTALL}/$${PROJECT_DIR} )

    addCleanDirEvent( $$PROJECT_GENERATED )

    # HEADER FILES
    {
        contains( PROJECT_TYPE , dynlib|staticlib ) {
            # Copy all headers.
            for( HEADER_DIR, SUBDIRS ) {
                HEADERS_TO_COPY = $$files( $$clean_path( $$PROJECT_INC/$$HEADER_DIR/*.h ) )

                !equals( HEADER_DIR, . ) {
                    suffix = _$$clean_path( $$HEADER_DIR )
                } else { suffix = }

                install_name = copy_headers$$suffix
                install_name = $$replace( install_name , /, _ ) # e.g.: copy_header_com/tcp to copy_header_com_tcp

                addCopyEvent( $$HEADERS_TO_COPY, $$clean_path( $$DELIVERY_INC/$$HEADER_DIR ), $$install_name )

                unset( HEADERS_TO_COPY )
            }

            addCleanDirEvent( $$DELIVERY_INC )

            # Remove excluded headers. To be finished.
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

    # UI FILES
    {
        contains( PROJECT_TYPE , dynlib|staticlib ) {
            UI_FILES = $$clean_path( $${PROJECT_UI}/ui_*.h )

            exists( $$UI_FILES ) {
                addCopyEvent( $$UI_FILES, $$DELIVERY_INC, copy_ui )
            }

            unset( UI_FILES )
        }
    }

    # STATIC
    {
        contains( PROJECT_TYPE , staticlib ) {
            LIB_NAME     = $$fullTarget( PROJECT_NAME, staticlib )
            LIB_SOURCE   = $$PROJECT_LIB/$$LIB_NAME

            addCopyEvent( $$LIB_SOURCE, $$DELIVERY_LIB, copy_lib )
            addCleanFileEvent( $$LIB_SOURCE )
            addCleanFileEvent( $$DELIVERY_LIB/$$LIB_NAME )

            unset( LIB_SOURCE )
            unset( LIB_NAME )
        }
    }

    # DYNAMIC
    {
        contains( PROJECT_TYPE, dynlib ) {
            DLL_NAME   = $$fullTarget( PROJECT_NAME, dynlib )
            DLL_SOURCE = $$DESTDIR/$$DLL_NAME

            addCopyEvent( $$DLL_SOURCE, $$DELIVERY_BIN, copy_dll )
            addCleanFileEvent( $$DLL_SOURCE )
            addCleanFileEvent( $$DELIVERY_BIN/$$DLL_NAME )

            *msvc*: {
                LIB_NAME   = $$fullTarget( PROJECT_NAME, staticlib )
                LIB_SOURCE = $$PROJECT_LIB/$$LIB_NAME
                PDB_NAME   = $$replaceString( TARGET,, .pdb )
                PDB_SOURCE = $$DESTDIR/$$PDB_NAME

                addCopyEvent( $$LIB_SOURCE, $$DELIVERY_LIB, copy_import )
                addCleanFileEvent( $$LIB_SOURCE )
                addCleanFileEvent( $$DELIVERY_LIB/$$LIB_NAME )

                exists( $$PDB_SOURCE ) {
                    addCopyEvent( $$PDB_SOURCE, $$DELIVERY_BIN, copy_pdb )
                    addCleanFileEvent( $$PDB_SOURCE )
                    addCleanFileEvent( $$DELIVERY_BIN/$$PDB_NAME )
                }

                unset( PDB_SOURCE )
                unset( PDB_NAME )
                unset( LIB_SOURCE )
                unset( LIB_NAME )
            }

            unset( DLL_SOURCE )
            unset( DLL_NAME )
        }
    }

    # BINARY FILES
    {
        contains( PROJECT_TYPE, app ) {
            BIN_NAME   = $$fullTarget( PROJECT_NAME, app )
            BIN_SOURCE = $$DESTDIR/$$BIN_NAME

            addCopyEvent( $$BIN_SOURCE, $$DELIVERY_BIN, copy_exe )
            addCleanFileEvent( $$BIN_SOURCE )
            addCleanFileEvent( $$DELIVERY_BIN/$$BIN_NAME )

            unset( BIN_SOURCE )
            unset( BIN_NAME )
        }
    }

    unset( PROJECT_INC       )
    unset( PROJECT_UI        )
    unset( PROJECT_LIB       )
    unset( PROJECT_BIN       )
    unset( PROJECT_GENERATED )
    unset( PROJECT_TYPE      )
    unset( PROJECT_NAME      )
    unset( PROJECT_DIR       )
    unset( PROJECT_INSTALL   )
    unset( DELIVERY_INC      )
    unset( DELIVERY_LIB      )
    unset( DELIVERY_BIN      )

    # Debug
    message( clean=$$QMAKE_CLEAN )
    *g++*: message( post_copy=$$INSTALLS )
    *msvc*: message( post_copy=$$QMAKE_POST_LINK )

}

# -------------------
# Deployment Settings
# -------------------

# Android default deployment.
include( deployment.pri )
