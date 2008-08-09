# Rem - Requirements and Entity Modeler = UML + AOP + Open Source + Cross Platform
# Copyright (C) 2008 Adrian Kosmaczewski - http://remproject.org/
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

PROJECT (rem)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)
SET(CMAKE_COLOR_MAKEFILE ON)
SET(CMAKE_VERBOSE_MAKEFILE OFF)

SET (ui_SRCS
    ui/PlatformDefinitions.h

    ui/Application.h 
    ui/Application.cpp 

    ui/Window.h 
    ui/Window.cpp 

    ui/UseCaseDiagram.h 
    ui/UseCaseDiagram.cpp 

    ui/UMLDiagram.h 
    ui/UMLDiagram.cpp 
    
    ui/DiagramComponent.h
    ui/DiagramComponent.cpp
    
    ui/ProjectComponent.h
    ui/ProjectComponent.cpp
    
    ui/ProjectTabbedComponent.h
    ui/ProjectTabbedComponent.cpp
    
    ui/ActorFigure.h
    ui/ActorFigure.cpp

    ui/Figure.h
    ui/Figure.cpp

    ui/UseCaseFigure.h
    ui/UseCaseFigure.cpp
    
    ui/ArrowCanvas.h
    ui/ArrowCanvas.cpp

    ui/UseCaseDiagramToolbar.h
    ui/UseCaseDiagramToolbar.cpp

    ui/DiagramToolbar.h
    ui/DiagramToolbar.cpp

    ui/ActorToolbarButton.h
    ui/ActorToolbarButton.cpp

    ui/UseCaseToolbarButton.h
    ui/UseCaseToolbarButton.cpp
    
    ui/CommandDelegate.h
    ui/CommandDelegate.cpp
    
    ui/MenuBar.h
    ui/MenuBar.cpp
)

SET (ui_Main_SRCS
    ui/PlatformDefinitions.h

    ui/Main.cpp 
)

SET (notifications_SRCS
    notifications/FigureMoved.h
    notifications/FigureMoved.cpp
    
    notifications/FigureSelected.h
    notifications/FigureSelected.cpp
    
    notifications/ArrowCanvasClicked.h
    notifications/ArrowCanvasClicked.cpp
    
    notifications/ProjectTabbedComponentChangedTab.h
    notifications/ProjectTabbedComponentChangedTab.cpp
    
    notifications/ExportDiagramAsPNG.h
    notifications/ExportDiagramAsPNG.cpp
    
    notifications/DiagramToggleGrid.h
    notifications/DiagramToggleGrid.cpp

    notifications/NewUseCaseDiagramAdded.h
    notifications/NewUseCaseDiagramAdded.cpp
)

SET (storage_SRCS
    storage/ActiveRecord.h 
    storage/BelongsTo.h
    storage/HasMany.h

    storage/Persistable.cpp
    storage/Persistable.h

    storage/AnyProperty.cpp 
    storage/AnyProperty.h 

    storage/AnyPropertyMap.cpp 
    storage/AnyPropertyMap.h 
    
    storage/FindConditions.cpp
    storage/FindConditions.h

    storage/SQLiteWrapper.cpp 
    storage/SQLiteWrapper.h 
)

SET (tests_SRCS
    tests/FileControllerTest.cpp
    tests/FileControllerTest.h
    
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
    
    tests/ElementTest.cpp
    tests/ElementTest.h

    tests/main.cpp
)

SET (metamodel_SRCS
    metamodel/Diagram.cpp 
    metamodel/Diagram.h 

    metamodel/Element.cpp 
    metamodel/Element.h 

    metamodel/Project.cpp 
    metamodel/Project.h 
    
    metamodel/Member.cpp
    metamodel/Member.h
)

SET (controllers_SRCS
    controllers/FileController.cpp
    controllers/FileController.h
)

SET (utility_SRCS
    utility/Singleton.h
    utility/Property.h
)

SET (remtests_SRCS 
    ${tests_SRCS}
    ${ui_SRCS}
    ${notifications_SRCS}
    ${controllers_SRCS}
    ${metamodel_SRCS} 
    ${storage_SRCS}
    ${utility_SRCS}
)

SET (Rem_SRCS
    ${ui_Main_SRCS}
    ${ui_SRCS}
    ${notifications_SRCS}
    ${controllers_SRCS}
    ${metamodel_SRCS} 
    ${storage_SRCS}
    ${utility_SRCS}
)

IF (WIN32)
    # ============ BUILD SETTINGS FOR WINDOWS ============
    # ============  USING VISUAL STUDIO 2008  ============
    # /Od -> disable optimization
    # /W3 -> warning level
    # /ZI -> program database for edit & continue
    # /Gm -> enable minimal rebuild
    # /RTC1 -> runtime checks: stack frames + uninitialized variables
    # /MTd -> Multi-threaded Debug
    
    # Given this bug in the NMake generator related to 'manifest files' in CMake 2.6
    # http://www.cmake.org/Bug/view.php?id=7222
    # it is recommended to use CMake 2.4.7 in Windows, so that both the 
    # application and the installer can be built from the command line.

    SET(CMAKE_CXX_FLAGS_DEBUG "/RTC1 /Gm /MTd /ZI /W3 /Od")
    SET(CMAKE_CXX_FLAGS_RELEASE "/RTC1 /Gm /MT")
    SET(CMAKE_EXE_LINKER_FLAGS "/MACHINE:X86 /DYNAMICBASE:NO /MANIFEST:NO")

    SET (win_resources_SRCS
        ${rem_SOURCE_DIR}/../build/windows/resource.rc
        ${rem_SOURCE_DIR}/../build/windows/resource.h
        ${rem_SOURCE_DIR}/../build/windows/rem.ico
    )

    # Header files are located in these directories
    INCLUDE_DIRECTORIES (
        ${rem_SOURCE_DIR}/../lib/poco/Foundation/include
        ${rem_SOURCE_DIR}/../lib/juce
        ${rem_SOURCE_DIR}/../lib/sqlite
    )

    # Libraries are located in these directories
    LINK_DIRECTORIES (
        ${rem_SOURCE_DIR}/../lib/poco/lib
        ${rem_SOURCE_DIR}/../lib/juce/bin
        ${rem_SOURCE_DIR}/../lib/sqlite
    )

    ADD_EXECUTABLE (Rem WIN32
        ${Rem_SRCS}
        ${win_resources_SRCS}
    )

    # These are the symbols for the linker
    TARGET_LINK_LIBRARIES(Rem
        jucelib_static_Win32
        sqlite3 
        PocoFoundation
    )

    INSTALL(FILES 
            ${CMAKE_CURRENT_SOURCE_DIR}/../lib/poco/bin/PocoFoundation.dll
            ${CMAKE_CURRENT_SOURCE_DIR}/../lib/sqlite/sqlite3.dll 
            ${CMAKE_CURRENT_BINARY_DIR}/Rem.exe
            "C:/Program Files/Microsoft Visual Studio 9.0/VC/redist/x86/Microsoft.VC90.CRT/msvcm90.dll"
            "C:/Program Files/Microsoft Visual Studio 9.0/VC/redist/x86/Microsoft.VC90.CRT/msvcp90.dll"
            "C:/Program Files/Microsoft Visual Studio 9.0/VC/redist/x86/Microsoft.VC90.CRT/msvcr90.dll"
            "C:/Program Files/Microsoft Visual Studio 9.0/VC/redist/x86/Microsoft.VC90.CRT/Microsoft.VC90.CRT.manifest"
        DESTINATION bin
    )

    SET(CPACK_PACKAGE_NAME "Rem")
    SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Rem UML Editor")
    SET(CPACK_PACKAGE_VENDOR "Adrian Kosmaczewski")
    SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Rem is a UML Editor")
    SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_BINARY_DIR}/../LICENSE.txt")
    SET(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_BINARY_DIR}/../README.txt")
    SET(CPACK_PACKAGE_VERSION_MAJOR "1")
    SET(CPACK_PACKAGE_VERSION_MINOR "0")
    SET(CPACK_PACKAGE_VERSION_PATCH "0")
    SET(CPACK_PACKAGE_INSTALL_DIRECTORY "Rem")
    SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "Rem 1.0.0")
    SET(CPACK_PACKAGE_EXECUTABLES "Rem;Rem")
    SET(CPACK_GENERATOR "NSIS")
    SET(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR};${CMAKE_PROJECT_NAME};ALL;/")
    SET(CPACK_NSIS_DISPLAY_NAME "Rem")
    SET(CPACK_NSIS_INSTALLER_ICON_CODE "")
    INCLUDE(CPack)
    
ELSE (WIN32)

    IF (UNIX)
        IF (APPLE)
            # This is bundle metadata to create "bundles" and "Universal Binaries" on Mac OS X
            # http://www.cmake.org/Wiki/CMake_FAQ#How_do_I_build_universal_binaries_on_Mac_OS_X.3F
            # By the way, there is a bug in the cross-compilation SDKs for Tiger in Leopard, 
            # so you need to follow these instructions:
            # http://groups.google.com/group/vim_mac/browse_thread/thread/064da55ec412e768
            # which means typing the following command in Terminal.app:
            # $ sudo ln -s /Developer/SDKs/MacOSX10.4u.sdk/usr/lib/crt1.o /Developer/SDKs/MacOSX10.4u.sdk/usr/lib/crt1.10.5.o
            SET(CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.4u.sdk)
            SET(CMAKE_OSX_ARCHITECTURES ppc;i386)
            SET(CMAKE_FIND_ROOT_PATH /Developer/SDKs/MacOSX10.4u.sdk)
            SET(MACOSX_BUNDLE_ICON_FILE icon.icns)
            SET(MACOSX_BUNDLE_BUNDLE_NAME Rem)
            SET(MACOSX_BUNDLE_BUNDLE_VERSION ${VERSION})
            SET(MACOSX_BUNDLE_SHORT_VERSION_STRING ${VERSION})
            SET(MACOSX_BUNDLE_LONG_VERSION_STRING "Version ${VERSION}")

            # ============ BUILD SETTINGS FOR MAC ============
            # ============     USING MAKEFILE     ============
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
            INCLUDE_DIRECTORIES (
                /usr/local/include/cppunit/../  # Somehow the tests won't build if not specified like this!
                ${rem_SOURCE_DIR}/../lib/poco-universal/poco/include
                ${rem_SOURCE_DIR}/../lib/juce
            )
        
            # Libraries are located in these directories
            LINK_DIRECTORIES (
                /usr/local/lib/
                ${rem_SOURCE_DIR}/../lib/poco-universal/poco/lib
                ${rem_SOURCE_DIR}/../lib/juce/bin
            )
        
            ADD_EXECUTABLE (remtest 
                ${remtests_SRCS}
            )
        
            ADD_EXECUTABLE (Rem MACOSX_BUNDLE
                ${Rem_SRCS}
            )
        
            # These are the symbols for the linker
            TARGET_LINK_LIBRARIES(Rem 
                ${EXTRA_LIBS}
                juce
                sqlite3 
                PocoFoundation
            )
        
            TARGET_LINK_LIBRARIES(remtest
                ${EXTRA_LIBS}
                juce
                cppunit 
                sqlite3 
                PocoFoundation
            )
        
            ADD_CUSTOM_COMMAND(TARGET Rem POST_BUILD
            
                # Copy the application icon into the bundle
                COMMAND mkdir
                    ARGS -p ${CMAKE_CURRENT_BINARY_DIR}/Rem.app/Contents/Resources
        
                COMMAND cp
                    ARGS ${CMAKE_CURRENT_SOURCE_DIR}/../build/mac/*.icns
                        ${CMAKE_CURRENT_BINARY_DIR}/Rem.app/Contents/Resources/

                # Create the disk image from a temporary subfolder
                COMMAND mkdir 
                    ARGS ${CMAKE_CURRENT_BINARY_DIR}/Rem
                        
                COMMAND cp
                    ARGS -r ${CMAKE_CURRENT_BINARY_DIR}/Rem.app
                        ${CMAKE_CURRENT_BINARY_DIR}/Rem
                        
                COMMAND ln
                    ARGS -s /Applications ${CMAKE_CURRENT_BINARY_DIR}/Rem
                        
                COMMAND hdiutil 
                    ARGS create -srcfolder ${CMAKE_CURRENT_BINARY_DIR}/Rem ${CMAKE_CURRENT_BINARY_DIR}/Rem.dmg
                        
                COMMAND rm 
                    ARGS -r ${CMAKE_CURRENT_BINARY_DIR}/Rem
            )

            ENABLE_TESTING()
            ADD_TEST(remtest ${CMAKE_CURRENT_BINARY_DIR}/remtest)
            
            # The support for Mac OS X bundle installation is available for version 2.6 of CMake:
            # http://www.cmake.org/pipermail/cmake/2007-October/016893.html
            INSTALL(TARGETS Rem
                # If not using ".." the package would not build correctly
                # or even worse, it would install the app in /usr
                BUNDLE DESTINATION ../Applications
            )
            
            SET(CPACK_PACKAGE_NAME "Rem")
            SET(CPACK_SYSTEM_NAME "Darwin")
            SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Rem UML Editor")
            SET(CPACK_PACKAGE_VENDOR "Adrian Kosmaczewski")
            SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Rem is a UML Editor")
            SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_BINARY_DIR}/../LICENSE.txt")
            SET(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_BINARY_DIR}/../README.txt")
            SET(CPACK_PACKAGE_VERSION_MAJOR "1")
            SET(CPACK_PACKAGE_VERSION_MINOR "0")
            SET(CPACK_PACKAGE_VERSION_PATCH "0")
            SET(CPACK_PACKAGE_INSTALL_DIRECTORY "Rem ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
            SET(CPACK_PACKAGE_EXECUTABLES "Rem;Rem")
            SET(CPACK_GENERATOR "PackageMaker")
            SET(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR};${CMAKE_PROJECT_NAME};ALL;/")
            INCLUDE(CPack)
        
        ELSE (APPLE)
            # ============ BUILD SETTINGS FOR KUBUNTU LINUX ============
            # ============         USING MAKEFILE           ============
            SET(EXTRA_LIBS
                freetype 
                pthread 
                rt 
                X11 
                GL 
                GLU 
                Xinerama 
                asound
            )
            # Header files are located in these directories
            INCLUDE_DIRECTORIES (
                "/usr/local/include/"
                "/usr/include"
                ${rem_SOURCE_DIR}/../lib/juce
            )
        
            # Libraries are located in these directories
            LINK_DIRECTORIES (
                "/usr/local/lib/"
                "/usr/X11R6/lib/"
                ${rem_SOURCE_DIR}/../lib/juce/bin
                ${rem_SOURCE_DIR}/../lib/poco/lib/Linux/i686
            )
            
            ADD_DEFINITIONS(
                -DLINUX
            )
        
            ADD_EXECUTABLE (Rem
                ${Rem_SRCS}
            )

            ADD_EXECUTABLE (remtest 
                ${remtests_SRCS}
            )

            # These are the symbols for the linker
            TARGET_LINK_LIBRARIES(Rem 
                ${EXTRA_LIBS}
                juce
                sqlite3 
                PocoFoundation
            )

            TARGET_LINK_LIBRARIES(remtest
                cppunit 
                sqlite3 
                PocoFoundation
            )

            ENABLE_TESTING()
            ADD_TEST(remtest ${CMAKE_CURRENT_BINARY_DIR}/remtest)

            INSTALL(TARGETS Rem
                RUNTIME DESTINATION bin
            )
            
            INSTALL(FILES 
                    ${rem_SOURCE_DIR}/../lib/poco/lib/Linux/i686/libPocoFoundation.so.5
                    ${rem_SOURCE_DIR}/../build/linux/install.sh
                DESTINATION bin
            )
        
            SET(CPACK_PACKAGE_NAME "Rem")
            SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Rem UML Editor")
            SET(CPACK_PACKAGE_VENDOR "Adrian Kosmaczewski")
            SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Rem is a UML Editor")
            SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_BINARY_DIR}/../LICENSE.txt")
            SET(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_BINARY_DIR}/../README.txt")
            SET(CPACK_PACKAGE_VERSION_MAJOR "1")
            SET(CPACK_PACKAGE_VERSION_MINOR "0")
            SET(CPACK_PACKAGE_VERSION_PATCH "0")
            SET(CPACK_PACKAGE_INSTALL_DIRECTORY "Rem")
            SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "Rem 1.0.0")
            SET(CPACK_PACKAGE_EXECUTABLES "Rem;Rem")
            SET(CPACK_GENERATOR "TGZ")
            SET(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR};${CMAKE_PROJECT_NAME};ALL;/")
            INCLUDE(CPack)

        ENDIF (APPLE)
    ENDIF (UNIX)
ENDIF (WIN32)
