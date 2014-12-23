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
# QT Modules
# -----------

    !contains( QT, core ): QT += core

# -----------------------
# Building Configuration
# -----------------------

    win32-g++: QMAKE_CXXFLAGS += -std=c++0x

    QMAKE_SPEC = $$(QMAKESPEC)
    isEmpty( QMAKE_SPEC ): QMAKE_SPEC = $$[QMAKESPEC]

    isEmpty( QMAKE_SPEC ) {
        error( "$${PROJECT.PRO}: Platform scope not defined" )
    }

    contains( QMAKE_HOST.arch, x86 ) {
        win32-msvc*: QMAKE_LFLAGS *= /MACHINE:X86
    }

    contains( QMAKE_HOST.arch, x86_64 ) {
        win32-msvc*: QMAKE_LFLAGS *= /MACHINE:X64
    }

    BUILD.CONFIG = $$(QMAKESPEC)_$${QMAKE_HOST.arch}

    message("config=" $$BUILD.CONFIG)

    CONFIG( debug, debug|release ): BUILD.MODE = debug
    CONFIG( release, debug|release ): BUILD.MODE = release

    isEmpty( BUILD.MODE ) {
        error( "$${PROJECT.PRO}: Building mode cannot be resolved" )
    }

# -----------------
# Project Settings
# -----------------

    PROJECT.PATH = $${_PRO_FILE_PWD_}/

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

            unset( MODULE_CONF_FILE )
            unset( MODULE_ENV_DIR )
        }

        MODULE_INC =	$${MODULE_PATH}/$$eval( $$upper( $${MODULE_NAME}.INC ) )
        MODULE_LIB =    $${MODULE_PATH}/$$eval( $$upper( $${MODULE_NAME}.LIB ) )
        MODULE_BIN =    $${MODULE_PATH}/$$eval( $$upper( $${MODULE_NAME}.BIN ) )

        PACKAGES = $$eval($$MODULE_NAME)
        for( PACKAGE, PACKAGES ) {

            equals( MODULE_NAME, $${MODULE.NAME} ) { # Internal dependency
                PACKAGE_INC =	$$MODULE_PATH/$$eval( $$upper( $${MODULE_NAME}.$${PACKAGE}.INC ) )/inc
            } else {
                PACKAGE_INC =	$${MODULE_INC}/$$eval( $$upper( $${MODULE_NAME}.$${PACKAGE}.INC ) )
            }
            PACKAGE_TARGET =    $$eval( $$upper( $${MODULE_NAME}.$${PACKAGE}.TARGET ) )
            PACKAGE_QT =        $$eval( $$upper( $${MODULE_NAME}.$${PACKAGE}.QT ) )
            PACKAGE_TYPE =      $$eval( $$upper( $${MODULE_NAME}.$${PACKAGE}.TYPE ) )

            message ( TOTO $$PACKAGE_INC )

            QT *= $$PACKAGE_QT

            INCLUDEPATH *= $$PACKAGE_INC

            #equals ( PACKAGE_TYPE, dynlib ): \
            #    PRE_TARGETDEPS += $$clean_path( $${MODULE_LIB}/$${BUILD.CONFIG}/$$fullTarget( PACKAGE_TARGET, dynlib ) )
            #
            #equals ( PACKAGE_TYPE, staticlib ): \
            #    PRE_TARGETDEPS += $$clean_path( $${MODULE_LIB}/$${BUILD.CONFIG}/$$fullTarget( PACKAGE_TARGET, staticlib ) )

            CONFIG( debug, debug|release ): PACKAGE_TARGET = $$replaceString( PACKAGE_TARGET,, d )

            equals( MODULE_NAME, $${MODULE.NAME} ) { # Internal dependency
                DEPENDPATH *= $$clean_path( $$MODULE_PATH/$$eval( $$upper( $${MODULE_NAME}.$${PACKAGE}.INC ) )/bin/$${BUILD.CONFIG} )
                LIBS *= -L$$clean_path( $$MODULE_PATH/$$eval( $$upper( $${MODULE_NAME}.$${PACKAGE}.INC ) )/bin/$${BUILD.CONFIG} )
                LIBS *= -L$$clean_path( $$MODULE_PATH/$$eval( $$upper( $${MODULE_NAME}.$${PACKAGE}.INC ) )/lib/$${BUILD.CONFIG} )
            } else {
                DEPENDPATH *= $$clean_path( $${MODULE_BIN}/$${BUILD.CONFIG} )
                LIBS *= -L$$clean_path( $${MODULE_BIN}/$${BUILD.CONFIG} )
                LIBS *= -L$$clean_path( $${MODULE_LIB}/$${BUILD.CONFIG} )
            }

            #win32-msvc*:LIBS *= -l$${PACKAGE_TARGET}.lib # Dependency purpose.
            LIBS *= -l$${PACKAGE_TARGET}

            message ( LIBS=$$LIBS )

            unset( PACKAGE_INC )
            unset( PACKAGE_TARGET )
            unset( PACKAGE_QT )
            unset( PACKAGE_TYPE )
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

    !contains( PROJECT.TYPE, app|dynlib|staticlib|subdirs ) {
        error( "$${PROJECT.PRO}: Project $${TARGET} must be of type app, dynlib, staticlib or subdirs" )
    }

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

    EXTS_H = .h .hpp
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

        export( INCLUDEPATH )
        export( HEADERS )
        export( SOURCES )
        export( FORMS )
        export( RESOURCES )
    }

    INCLUDEPATH += $$clean_path( $${PROJECT.PATH}/inc )

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
        contains( PROJECT.TYPE, app ): OUTPUT_DIR = bin
        contains( PROJECT.TYPE, staticlib ): OUTPUT_DIR = lib
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

    # Copy lib file.
    contains( PROJECT_TYPE , dynlib|staticlib ) {
        FULLPATH_LIB = $$DESTDIR/$$fullTarget( PROJECT_NAME, staticlib ) # Force to staticlib to get .lib.
        exists( $${FULLPATH_LIB} ) {
            copy_lib.path  = $$clean_path( $${MODULE.PATH}/$$eval( $${MODULE.NAME}.LIB )/$${BUILD.CONFIG} )
            copy_lib.files = $${FULLPATH_LIB}

            INSTALLS += copy_lib
        }
    }


#    # Copy header files.
#
#    for( EXCLUDED_HEADER, EXCLUDED_HEADERS ) { # Normalize filenames.
#        EXCLUDED_HEADERS_TMP += $$clean_path( $$EXCLUDED_HEADER )
#    }
#    EXCLUDED_HEADERS = $$EXCLUDED_HEADERS_TMP
#
#
#    for( EXCLUDED_HEADER, EXCLUDED_HEADERS_TMP ) {
#        # ex: EXCLUDED_HEADERS = inputs/*.h
#        !isRelativePath( EXCLUDED_HEADER ) {
#            error( "$${PROJECT.PRO}: $${EXCLUDED_HEADER} must define an relative path" )
#        }
#
#        EXCLUDED_HEADERS -= $$EXCLUDED_HEADER
#        EXCLUDED_HEADER  = $$files( $$clean_path( $$replaceString( EXCLUDED_HEADER, $${PROJECT.PATH}/inc/, ) ) )
#        EXCLUDED_HEADERS += $$EXCLUDED_HEADER
#        # ex: EXCLUDED_HEADERS = C:/my_project/inputs/toto.h C:/my_project/inputs/toto.h
#    }
#
#    HEADERS_TO_COPY = $$HEADERS
#    HEADERS_TO_COPY -= $$EXCLUDED_HEADERS # Substract excluded headers.
#
#    for( HEADER, HEADERS_TO_COPY ) {
#        HEADER_DIR = $$dirname( HEADER ) # Only take the subdir part of the header path.
#        HEADER_DIR = $$replace( HEADER_DIR, $$clean_path( $${PROJECT.PATH}/inc ), )
#
#        QMAKE_POST_LINK += $${QMAKE_COPY} \
#                            \"$$HEADER\" \
#                            \"$$clean_path( $${MODULE.PATH}/$$eval( $${MODULE.NAME}.INC )/$$eval( $${MODULE.NAME}.$$upper( $${PROJECT.ID} ).INC )/$${HEADER_DIR}/* )\" $$escape_expand(\n\t)
#    }
#
#    # Copy ui files.
#    exists( $${UI_DIR}/ui_*.h ) {
#        QMAKE_POST_LINK += $${QMAKE_COPY} \
#                            \"$$UI_DIR/ui_*.h\" \
#                            \"$$clean_path( $${MODULE.PATH}/$$eval( $${MODULE.NAME}.INC )/$$eval( $${MODULE.NAME}.$$upper( $${PROJECT.ID} ).INC )/* )\" $$escape_expand(\n\t)
#    }
#
#    PROJECT_TYPE = $${PROJECT.TYPE}
#    PROJECT_NAME = $${PROJECT.NAME}
#
#    # Copy lib file.
#    contains( PROJECT_TYPE , dynlib|staticlib ) {
#        FULLPATH_LIB = $$DESTDIR/$$fullTarget( PROJECT_NAME, staticlib ) # Force to staticlib to get .lib.
#        exists( $${FULLPATH_LIB} ) {
#            QMAKE_POST_LINK += $${QMAKE_COPY} \
#                                \"$${FULLPATH_LIB}\" \
#                                \"$$clean_path( $${MODULE.PATH}/$$eval( $${MODULE.NAME}.LIB )/$${BUILD.CONFIG} )/* )\" $$escape_expand(\n\t)
#        }
#    }
#
#    # Copy dll and pdb file.
#    contains( PROJECT_TYPE, dynlib ) {
#        FULLPATH_DLL = $$DESTDIR/$$fullTarget( PROJECT_NAME, dynlib )
#        exists( $${FULLPATH_DLL} ) {
#            QMAKE_POST_LINK += $${QMAKE_COPY} \
#                                \"$${FULLPATH_DLL}\" \
#                                \"$$clean_path( $${MODULE.PATH}/$$eval( $${MODULE.NAME}.BIN )/$${BUILD.CONFIG} )/* )\" $$escape_expand(\n\t)
#        }
#
#        win32: {
#            FULLPATH_PDB = $$DESTDIR/$$replaceString( TARGET,, .pdb )
#            exists( $${FULLPATH_PDB} ) {
#                QMAKE_POST_LINK += $${QMAKE_COPY} \
#                                    \"$${FULLPATH_PDB}\" \
#                                    \"$$clean_path( $${MODULE.PATH}/$$eval( $${MODULE.NAME}.BIN )/$${BUILD.CONFIG} )/* )\" $$escape_expand(\n\t)
#            }
#
#        }
#    }
#
#    # Copy exe file.
#    contains( PROJECT_TYPE, app ) {
#
#        QMAKE_POST_LINK += $${QMAKE_COPY} \
#                            \"$$DESTDIR/$$fullTarget( PROJECT_NAME, app )\" \
#                            \"$$clean_path( $${MODULE.PATH}/$$eval( $${MODULE.NAME}.BIN )/$${BUILD.CONFIG} )/* )\" $$escape_expand(\n\t)
#
#    }
#
#    message ( post_build=$$QMAKE_POST_LINK )

