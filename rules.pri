# ----------------------
# Internal documentation
# ----------------------
#
# Suppose we have a foo module where bar project stands.
#
# MODULE.PATH: relative path between leaf project and root module.
# MODULE.NAME: module name that the project belongs to.
# MODULE.LINKTYPE: staticlib | dynlib (used for external project linking)
# MODULE.DIR: pwd of foo.pro (foo.dir var)
# MODULE.INSTALL: relative location where results will be copied (foo.install var)
# MODULE.BUILD: relative location where build objects will stand
#
# PROJECT.NAME: name of the project (bar)
# PROJECT.TYPE: app | staticlib | dynlib
# PROJECT.PATH: pwd of bar.pro
# PROJECT.QT: bar Qt dependencies
# PROJECT.DIR: relative path from foo.pro to bar.pro
#
# BUILD.MODE: debug | release
# BUILD.BASECONFIG: foo shadow build label: Qt57-msvc-x86_64-debug
# BUILD.CONFIG: bar shadow build label: Qt57-msvc-x86_64-debug-static

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

    isEmpty( MODULE.PATH ) {
        error( "$${PROJECT.PRO}: MODULE.PATH must be defined" )
    }

    isRelativePath( MODULE.PATH ) {
        error( "$${PROJECT.PRO}: $${MODULE.PATH} must be an absolute path" )
    }

    checkFilepath( MODULE.PATH )

    isEmpty( MODULE.NAME ) {
        error( "$${PROJECT.PRO}: MODULE.NAME must be defined" )
    }

    # Conf file.
    MODULE_CONF_FILE = $${MODULE.PATH}/$${MODULE.NAME}.conf
    !include( $$MODULE_CONF_FILE ) {
        error( "$${PROJECT.PRO}: Configuration file $${MODULE_CONF_FILE} not found" )
    } else {
        message ( "Configuration file $$MODULE_CONF_FILE loaded" )
    }
    unset( MODULE_CONF_FILE )

    # Module requirements.
    MODULE.LINKTYPE = $$eval( $${MODULE.NAME}.linktype )
    MODULE.DIR = $$clean_path( $$eval( $${MODULE.NAME}.dir) )
    MODULE.INSTALL = $$clean_path( $${MODULE.DIR}/$$eval( $${MODULE.NAME}.install ) )
    MODULE.BUILD = $$clean_path( $${MODULE.DIR}/build )

    isEmpty( MODULE.LINKTYPE ) {
        error( "$${PROJECT.PRO}: $${MODULE.NAME}.linktype must be defined" )
    }

    isEmpty( MODULE.DIR ) {
        error( "$${PROJECT.PRO}: $${MODULE.NAME}.dir must be defined" )
    }

    isEmpty( MODULE.INSTALL ) {
        error( "$${PROJECT.PRO}: $${MODULE.NAME}.install must be defined" )
    }

    isEmpty( MODULE.BUILD ) {
        error( "$${PROJECT.PRO}: $${MODULE.NAME}.build must be defined" )
    }

# -----------------
# Project Settings
# -----------------

    isEmpty( PROJECT.NAME ) {
        error( "$${PROJECT.PRO}: PROJECT.NAME must be defined" )
    }

    isEmpty( PROJECT.TYPE ) {
        PROJECT.TYPE = $$eval( $${PROJECT.NAME}.type )
        isEmpty( PROJECT.TYPE ) {
            PROJECT.TYPE = subdirs
        }
    }

    !contains( PROJECT.TYPE, app|dynlib|staticlib|subdirs ) {
        error( "$${PROJECT.PRO}: $${PROJECT.NAME}.type must be of type app, dynlib, staticlib or subdirs" )
    }

    !contains( PROJECT.TYPE, subdirs ) {
        isEmpty( PROJECT.DIR ) {
            PROJECT.DIR = $$eval( $${PROJECT.NAME}.dir )
        }
        PROJECT.PATH = $$clean_path($${_PRO_FILE_PWD_})

        isEmpty( PROJECT.QT ) {
            PROJECT.QT = $$eval( $${PROJECT.NAME}.qt )
        }

        isEmpty( PROJECT.DIR ) {
            error( "$${PROJECT.PRO}: $${PROJECT.NAME}.dir variable cannot be resolved" )
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

    isEmpty( QT_ARCH ) {
        error( "Arch not defined. Is QT_ARCH set?" )
    }

    contains( QT_ARCH, x86_64 ) {
        *msvc*: QMAKE_LFLAGS *= /MACHINE:X64
    } else {
        contains( QT_ARCH, x86 ) {
            *msvc*: QMAKE_LFLAGS *= /MACHINE:X86
        }
    }

    CONFIG( debug, debug|release ): BUILD.MODE = debug
    CONFIG( release, debug|release ): BUILD.MODE = release

    isEmpty( BUILD.MODE ) {
        error( "Building mode cannot be resolved" )
    }

    BUILD.BASECONFIG = Qt$${QT_MAJOR_VERSION}$${QT_MINOR_VERSION}-$${QMAKE_COMPILER}-$${QT_ARCH}-$${BUILD.MODE}
    BUILD.CONFIG = $${BUILD.BASECONFIG}
    contains( MODULE.LINKTYPE, staticlib ) {
        BUILD.CONFIG = $$replaceString( BUILD.CONFIG, , -static )
    }

    PROJECT.BUILD = $$clean_path( $${MODULE.BUILD}/$${PROJECT.DIR}/$${BUILD.CONFIG} )

# ---------------------
# Modules Dependencies
# ---------------------

    defineTest( resolveModuleDependency ) {

        MODULE_NAME = $$1
        MODULE_CONF_FILE = $${MODULE_NAME}.conf

        # Internal dependency, conf file already included.
        equals( MODULE_NAME, $${MODULE.NAME} ) {
            MODULE_DIR = $${MODULE.DIR}
            MODULE_DEST = $${MODULE.BUILD}

            checkFilepath( MODULE_DIR )
            checkFilepath( MODULE_DEST )
        }
        # External dependency
        else {
            MODULE_DIR = $($$upper( $${MODULE_NAME} )_HOME)
            MODULE_CONF_FILE = $$clean_path( $$MODULE_DIR/$$MODULE_CONF_FILE )

            !include( $$MODULE_CONF_FILE ) {
                error( "$${PROJECT.PRO}: Configuration file $${MODULE_CONF_FILE} not found" )
            } else {
                message( Configuration file $$MODULE_CONF_FILE loaded. )
            }

            MODULE_LINKTYPE = $$eval( $${MODULE_NAME}.linktype )
            MODULE_DEST = $$clean_path( $$MODULE_DIR/$$eval( $${MODULE_NAME}.install ) )
            isEmpty( MODULE_DEST ) {
                error( "$${PROJECT.PRO}: $${MODULE_NAME}.install must be defined" )
            }

            unset( MODULE_DIR )
        }

        unset( MODULE_CONF_FILE )

        PACKAGES = $$eval( $$MODULE_NAME )
        for( PACKAGE, PACKAGES ) {

            PACKAGE_NAME    = $${PACKAGE}
            PACKAGE_DIR     = $$eval( $${PACKAGE_NAME}.dir )
            PACKAGE_QT      = $$eval( $${PACKAGE_NAME}.qt )
            PACKAGE_TYPE    = $$eval( $${PACKAGE_NAME}.type )

            isEmpty( PACKAGE_DIR ): error( PACKAGE_DIR must be defined)
            isEmpty( PACKAGE_TYPE ): error( PACKAGE_TYPE must be defined)

            # Internal dependency
            equals( MODULE_NAME, $${MODULE.NAME} ) {
                PACKAGE_BUILD = $${MODULE_DEST}/$${PACKAGE_DIR}/$${BUILD.CONFIG}
                PACKAGE_INC = $${MODULE_DIR}/$${PACKAGE_DIR}
                PACKAGE_INC += $$PACKAGE_BUILD
                PACKAGE_LIB =  $$PACKAGE_BUILD
                PACKAGE_BIN =  $$PACKAGE_BUILD
                unset( PACKAGE_BUILD )
            }
            # External dependency
            else {
                PACKAGE_INC = $$shell_path( $$clean_path( $${MODULE_DEST}/$${PACKAGE_DIR} ) )

                PACKAGE_CONFIG = $${BUILD.BASECONFIG}
                contains( MODULE_LINKTYPE, staticlib ) {
                    PACKAGE_CONFIG = $$replaceString( PACKAGE_CONFIG, , -static )
                }

                PACKAGE_LIB = $$clean_path( $${MODULE_DEST}/lib/$$PACKAGE_CONFIG )
                PACKAGE_BIN = $$clean_path( $${MODULE_DEST}/bin/$$PACKAGE_CONFIG )

                unset( PACKAGE_CONFIG )
            }

            PACKAGE_NAME = $$targetName( PACKAGE_NAME, $$PACKAGE_TYPE )

            *g++*: {
                equals ( PACKAGE_TYPE, staticlib ): {
                    PRE_TARGETDEPS += $$clean_path( $${PACKAGE_LIB}/$$fullTarget(PACKAGE_NAME, $$PACKAGE_TYPE) )
                }
            }

            QT *= $$PACKAGE_QT

            INCLUDEPATH *= $${PACKAGE_INC}

            DEPENDPATH *= $$clean_path( $${PACKAGE_BIN} )

            LIBS *= -L$$clean_path( $${PACKAGE_BIN} )
            LIBS *= -L$$clean_path( $${PACKAGE_LIB} )
            LIBS *= -l$${PACKAGE_NAME}

            unset( PACKAGE_NAME )
            unset( PACKAGE_DIR )
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

        unset( MODULE_DIR )
        unset( MODULE_DEST )
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
            win32: RC_ICONS = $$clean_path( $$(HB_HOME)/tools/resources/HbLogo.ico ) # Default HB icon.
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
        isEmpty( SUBDIRS ): error( "SUBDIRS must be defined" )
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
                exists( $${PROJECT.PATH}/$${subdir}/*$${EXT_H} ) {
                    HEADERS *= $$files( $$clean_path( $${PROJECT.PATH}/$${subdir}/*$${EXT_H} ) )
                }
            }

            for( EXT_CPP, EXTS_CPP ) {
                exists( $${PROJECT.PATH}/$${subdir}/*$${EXT_CPP} ) {
                    SOURCES *= $$files( $$clean_path( $${PROJECT.PATH}/$${subdir}/*$${EXT_CPP} ) )
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

    INCLUDEPATH += $$clean_path( $${PROJECT.PATH} )
    SUBDIRS *= .

    scanDirectories( SUBDIRS )
}

# ----------------
# Generated Files
# ----------------

    OBJECTS_DIR = $${PROJECT.BUILD}
    MOC_DIR = $${PROJECT.BUILD}
    RCC_DIR = $${PROJECT.BUILD}
    UI_DIR = $${PROJECT.BUILD}
    DESTDIR = $${PROJECT.BUILD}

# ---------------
# Build Settings
# ---------------

    !contains( PROJECT.TYPE, subdirs ) {
        TARGET = $$targetName( PROJECT.NAME, $${PROJECT.TYPE} )
    }

# ------------------------
# Install & Clean Settings
# ------------------------

isEmpty( $${MODULE.NAME}.NO_INSTALL_TARGETS ) {
    defineTest( addCopyEvent ) {

        files        = $$1
        dest_path    = $$clean_path( $$2 )
        install_name = $$3

        $${install_name}.files = $$files
        $${install_name}.path  = $$clean_path( $$dest_path )
        $${install_name}.CONFIG += no_check_exist

        INSTALLS *= $${install_name}

        export( $${install_name}.files )
        export( $${install_name}.path )
        export( $${install_name}.CONFIG )
        export( INSTALLS )
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
    PROJECT_INC = $$clean_path( $${PROJECT.PATH} )
    PROJECT_TYPE = $${PROJECT.TYPE}
    PROJECT_NAME = $${PROJECT.NAME}
    PROJECT_UI = $${PROJECT.BUILD}

    PROJECT_DEST = $${PROJECT.BUILD}

    # Delivery
    DELIVERY_LIB = $$clean_path( $${MODULE.INSTALL}/lib/$${BUILD.CONFIG} )
    DELIVERY_BIN = $$clean_path( $${MODULE.INSTALL}/bin/$${BUILD.CONFIG} )
    DELIVERY_INC = $$clean_path( $${MODULE.INSTALL}/inc/$${PROJECT.DIR} )

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

                addCopyEvent( $$HEADERS_TO_COPY, $$DELIVERY_INC/$$HEADER_DIR, $$install_name )

                unset( HEADERS_TO_COPY )
            }

            addCleanDirEvent( $$DELIVERY_INC )

            # Remove excluded headers. To be finished.
            #for( EXCLUDED_HEADER, EXCLUDED_HEADERS ) {
            #    !isRelativePath( EXCLUDED_HEADER ): \
            #        error( "Excluded headers must define a relative path." )
            #
            #    # ex: gui/*.h
            #    EXCLUDED_HEADER = $$clean_path( $$replaceString( EXCLUDED_HEADER, $$PROJECT_INC/, ) )
            #
            #    # ex: C:/hb/log/gui/*.h
            #    EXCLUDED_HEADER_FILES *= $$files( $$EXCLUDED_HEADER )
            #
            #    # ex: C:/hb/log/gui/foo1.h C:/hb/log/gui/foo2.h
            #
            #    for( EXCLUDED_HEADER_FILE, EXCLUDED_HEADER_FILES ) {
            #        # Replace root path.
            #        EXCLUDED_HEADER_FILES_TMP *= $$clean_path( $$replace( EXCLUDED_HEADER_FILE, $$PROJECT_INC, $$DELIVERY_INC ) )
            #    }
            #    EXCLUDED_HEADER_FILES = $$EXCLUDED_HEADER_FILES_TMP
            #    unset( EXCLUDED_HEADER_FILES_TMP )
            #
            #    # ex: C:/hb/delivery/inc/log/gui/foo1.h C:/hb/delivery/inc/log/gui/foo2.h
            #    EXCLUDED_HEADERS_TMP *= $$EXCLUDED_HEADER_FILES
            #    unset( EXCLUDED_HEADER_FILES )
            #}
            #EXCLUDED_HEADERS = $$EXCLUDED_HEADERS_TMP

            #unset( EXCLUDED_HEADERS_TMP )
            #unset( EXCLUDED_HEADER )
        }
    }

    # UI FILES
    {
        contains( PROJECT_TYPE , dynlib|staticlib ) {
            UI_FILES = $$files( $$clean_path( $${PROJECT_UI}/ui_*.h ) )

            addCopyEvent( $$UI_FILES, $$DELIVERY_INC, copy_ui )

            unset( UI_FILES )
        }
    }

    # STATIC
    {
        contains( PROJECT_TYPE , staticlib ) {
            LIB_NAME = $$targetName( PROJECT_NAME, $$PROJECT_TYPE )
            LIB_NAME = $$fullTarget( LIB_NAME, $$PROJECT_TYPE )
            LIB_SOURCE = $$PROJECT_DEST/$$LIB_NAME

            addCopyEvent( $$LIB_SOURCE, $$DELIVERY_LIB, copy_lib )
            addCleanFileEvent( $$DELIVERY_LIB/$$LIB_NAME )

            unset( LIB_SOURCE )
            unset( LIB_NAME )
        }
    }

    # DYNAMIC
    {
        contains( PROJECT_TYPE, dynlib ) {
            LIB_NAME = $$targetName( PROJECT_NAME, $$PROJECT_TYPE )
            LIB_NAME = $$fullTarget( LIB_NAME, $$PROJECT_TYPE )
            LIB_SOURCE = $$PROJECT_DEST/$$LIB_NAME

            addCopyEvent( $$LIB_SOURCE, $$DELIVERY_BIN, copy_dll )
            addCleanFileEvent( $$DELIVERY_BIN/$$LIB_NAME )

            unset( LIB_SOURCE )
            unset( LIB_NAME )
        }
    }

    # MSVC SPECIFIC
    *msvc*: {
        contains( PROJECT_TYPE , staticlib|dynlib ) {
            LIB_TARGET_NAME = $$targetName( PROJECT_NAME, $$PROJECT_TYPE )
            LIB_NAME = $$fullTarget( LIB_TARGET_NAME, vcdynlib )
            PDB_NAME = $$fullTarget( LIB_TARGET_NAME, vcpdb )

            LIB_SOURCE = $$PROJECT_DEST/$$LIB_NAME
            PDB_SOURCE = $$PROJECT_DEST/$$PDB_NAME

            addCopyEvent( $$LIB_SOURCE, $$DELIVERY_LIB, copy_import )
            addCopyEvent( $$PDB_SOURCE, $$DELIVERY_LIB, copy_pdb )
            addCleanFileEvent( $$DELIVERY_LIB/$$LIB_NAME )
            addCleanFileEvent( $$DELIVERY_LIB/$$PDB_NAME )

            unset( LIB_TARGET_NAME )
            unset( LIB_NAME )
            unset( PDB_NAME )
            unset( LIB_SOURCE )
            unset( PDB_SOURCE )
        }
    }

    # BINARY FILES
    {
        contains( PROJECT_TYPE, app ) {
            BIN_NAME = $$targetName( PROJECT_NAME, $$PROJECT_TYPE )
            BIN_NAME   = $$fullTarget( BIN_NAME, app )
            BIN_SOURCE = $$PROJECT_DEST/$$BIN_NAME

            addCopyEvent( $$BIN_SOURCE, $$DELIVERY_BIN, copy_exe )
            addCleanFileEvent( $$DELIVERY_BIN/$$BIN_NAME )

            unset( BIN_SOURCE )
            unset( BIN_NAME )
        }
    }

    unset( PROJECT_INC )
    unset( PROJECT_UI )
    unset( PROJECT_LIB )
    unset( PROJECT_BIN )
    unset( PROJECT_TYPE )
    unset( PROJECT_NAME )
    unset( DELIVERY_INC )
}

# -------------------
# Deployment Settings
# -------------------

# Android default deployment.
include( deployment.pri )
