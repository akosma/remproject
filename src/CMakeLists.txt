project (rem)

set (ui_SRCS
    ui/Application.h 
    ui/Application.cpp 

    ui/Window.h 
    ui/Window.cpp 

    ui/ContentComponent.h 
    ui/ContentComponent.cpp 

    ui/Main.cpp 
)

set (storage_SRCS
    storage/ActiveRecord.h 

    storage/Property.h 

    storage/AnyProperty.cpp 
    storage/AnyProperty.h 

    storage/AnyPropertyMap.cpp 
    storage/AnyPropertyMap.h 

    storage/SQLiteWrapper.cpp 
    storage/SQLiteWrapper.h 
)

set (tests_SRCS
    tests/ActiveRecordTest.cpp 
    tests/ActiveRecordTest.h 

    tests/PropertyTest.cpp 
    tests/PropertyTest.h 

    tests/AnyPropertyMapTest.cpp 
    tests/AnyPropertyMapTest.h 

    tests/DiagramTest.cpp 
    tests/DiagramTest.h 

    tests/ProjectTest.cpp 
    tests/ProjectTest.h 

    tests/SQLiteWrapperTest.cpp 
    tests/SQLiteWrapperTest.h 

    tests/main.cpp
)

set (metamodel_SRCS
    metamodel/Container.h 

    metamodel/Actor.cpp 
    metamodel/Actor.h 

    metamodel/Diagram.cpp 
    metamodel/Diagram.h 

    metamodel/Element.cpp 
    metamodel/Element.h 

    metamodel/Project.cpp 
    metamodel/Project.h 

    metamodel/UseCaseDiagram.cpp 
    metamodel/UseCaseDiagram.h 
)

set (remtests_SRCS 
    ${metamodel_SRCS} 
    ${tests_SRCS}
    ${storage_SRCS}
)

set (Rem_SRCS
    ${ui_SRCS}
)

IF (APPLE)
    # Build against the correct binaries, depending on the processor architecture
    IF (CMAKE_OSX_ARCHITECTURES MATCHES i386)
        SET (POCO_LIB_DIR ${rem_SOURCE_DIR}/../lib/poco/lib/Darwin/Intel)
    ELSE (CMAKE_OSX_ARCHITECTURES MATCHES i386)
        SET (POCO_LIB_DIR ${rem_SOURCE_DIR}/../lib/poco/lib/Darwin/Power_Macintosh)
    ENDIF (CMAKE_OSX_ARCHITECTURES MATCHES i386)

    # This information is needed to compile the GUI application as a "bundle".
    # Info on how to use OSX frameworks taken from
    # http://www.vtk.org/Wiki/CMake:HowToUseExistingOSXFrameworks
    FIND_LIBRARY(CARBON_LIBRARY Carbon)
    FIND_LIBRARY(QUICKTIME_LIBRARY QuickTime)
    FIND_LIBRARY(APP_SERVICES_LIBRARY ApplicationServices)
    FIND_LIBRARY(AGL AGL)
    FIND_LIBRARY(CORE_AUDIO CoreAudio)
    FIND_LIBRARY(CORE_SERVICES CoreServices)
    FIND_LIBRARY(IO_KIT IOKit)
    FIND_LIBRARY(OPEN_GL OpenGL)
    MARK_AS_ADVANCED (CARBON_LIBRARY)
    MARK_AS_ADVANCED (QUICKTIME_LIBRARY)
    MARK_AS_ADVANCED (APP_SERVICES_LIBRARY)
    MARK_AS_ADVANCED (AGL)
    MARK_AS_ADVANCED (CORE_AUDIO)
    MARK_AS_ADVANCED (CORE_SERVICES)
    MARK_AS_ADVANCED (IO_KIT)
    MARK_AS_ADVANCED (OPEN_GL)
    SET(EXTRA_LIBS 
        ${CARBON_LIBRARY} 
        ${QUICKTIME_LIBRARY} 
        ${APP_SERVICES_LIBRARY} 
        ${AGL} 
        ${CORE_AUDIO} 
        ${CORE_SERVICES} 
        ${IO_KIT} 
        ${OPEN_GL}
    )

    # Header files are located in these directories
    include_directories (
        metamodel 
        storage 
        tests 
        /usr/local/include 
        /usr/include 
        ${rem_SOURCE_DIR}/../lib/poco/Foundation/include
        ${rem_SOURCE_DIR}/../lib/juce
    )

    # Libraries are located in these directories
    link_directories (
        /usr/lib/ 
        /usr/local/lib 
        ${POCO_LIB_DIR}
        ${rem_SOURCE_DIR}/../lib/juce/bin
    )

    # This is bundle metadata to create "bundles" and "Universal Binaries" on Mac OS X
    # http://www.cmake.org/Wiki/CMake_FAQ#How_do_I_build_universal_binaries_on_Mac_OS_X.3F
    SET(CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.5.sdk)
    SET(MACOSX_BUNDLE_ICON_FILE icon.icns)
    SET(MACOSX_BUNDLE_BUNDLE_NAME Rem)
    SET(MACOSX_BUNDLE_BUNDLE_VERSION ${VERSION})
    SET(MACOSX_BUNDLE_SHORT_VERSION_STRING ${VERSION})
    SET(MACOSX_BUNDLE_LONG_VERSION_STRING "Version ${VERSION}")

    # These are the symbols for the linker
    link_libraries(
        cppunit 
        sqlite3 
        PocoFoundation
        juce
    )

    add_executable (remtest 
        ${remtests_SRCS}
    )

    add_executable (Rem MACOSX_BUNDLE
        ${Rem_SRCS}
    )

    target_link_libraries(Rem ${EXTRA_LIBS})

    add_custom_command(TARGET Rem POST_BUILD
        COMMAND mkdir
            ARGS -p ${CMAKE_CURRENT_BINARY_DIR}/Rem.app/Contents/Resources
        COMMAND cp
            ARGS ${CMAKE_CURRENT_SOURCE_DIR}/../build/mac/*.icns
                ${CMAKE_CURRENT_BINARY_DIR}/Rem.app/Contents/Resources/
    )

    enable_testing()
    add_test(remtest ${rem_SOURCE_DIR}/../bin/remtest)

ENDIF (APPLE)
