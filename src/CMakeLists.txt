project (rem)

IF (APPLE)
    IF (CMAKE_OSX_ARCHITECTURES MATCHES i386)
        SET (POCO_LIB_DIR ${rem_SOURCE_DIR}/../lib/poco/lib/Darwin/Intel)
    ELSE (CMAKE_OSX_ARCHITECTURES MATCHES i386)
        SET (POCO_LIB_DIR ${rem_SOURCE_DIR}/../lib/poco/lib/Darwin/Power_Macintosh)
    ENDIF (CMAKE_OSX_ARCHITECTURES MATCHES i386)

    include_directories (
        metamodel 
        storage 
        tests 
        /usr/local/include 
        /usr/include 
        ${rem_SOURCE_DIR}/../lib/poco/Foundation/include
        ${rem_SOURCE_DIR}/../lib/juce
    )

    link_directories (
        /usr/lib/ 
        /usr/local/lib 
        ${POCO_LIB_DIR}
        ${rem_SOURCE_DIR}/../lib/juce/bin
    )
    
    # http://www.cmake.org/Wiki/CMake_FAQ#How_do_I_build_universal_binaries_on_Mac_OS_X.3F
    SET(CMAKE_OSX_ARCHITECTURES ppc)
    SET(CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.5.sdk)
    SET(PROGNAME Rem)

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
    SET(EXTRA_LIBS ${CARBON_LIBRARY} ${QUICKTIME_LIBRARY} ${APP_SERVICES_LIBRARY} ${AGL} ${CORE_AUDIO} ${CORE_SERVICES} ${IO_KIT} ${OPEN_GL})

ENDIF (APPLE)

link_libraries(
    cppunit 
    sqlite3 
    PocoFoundation
    juce
)

add_executable (remtest 
    storage/ActiveRecord.h 
    
    storage/Property.h 

    storage/AnyProperty.cpp 
    storage/AnyProperty.h 

    storage/AnyPropertyMap.cpp 
    storage/AnyPropertyMap.h 

    storage/SQLiteWrapper.cpp 
    storage/SQLiteWrapper.h 

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

add_executable (Rem MACOSX_BUNDLE
    ui/RemApplication.h 
    ui/RemApplication.cpp 

    ui/RemWindow.h 
    ui/RemWindow.cpp 

    ui/RemContentComponent.h 
    ui/RemContentComponent.cpp 

    ui/Main.cpp 
)

target_link_libraries(Rem ${EXTRA_LIBS})

enable_testing()
add_test(remtest ${rem_SOURCE_DIR}/../bin/remtest)
