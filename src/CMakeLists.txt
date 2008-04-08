project (rem)

include_directories (
    metamodel 
    storage 
    tests 
    /usr/local/include 
    /usr/include 
    ${rem_SOURCE_DIR}/../lib/poco/Foundation/include
)

IF (APPLE)
    IF (CMAKE_OSX_ARCHITECTURES MATCHES i386)
        SET (POCO_LIB_DIR ${rem_SOURCE_DIR}/../lib/poco/lib/Darwin/Intel)
    ELSE (CMAKE_OSX_ARCHITECTURES MATCHES i386)
        SET (POCO_LIB_DIR ${rem_SOURCE_DIR}/../lib/poco/lib/Darwin/Power_Macintosh)
    ENDIF (CMAKE_OSX_ARCHITECTURES MATCHES i386)

    link_directories (
        /usr/lib/ 
        /usr/local/lib 
        ${POCO_LIB_DIR}
    )
ENDIF (APPLE)


link_libraries(
    cppunit 
    sqlite3 
    PocoFoundation
)

add_executable (remtest 
    storage/AnyProperty.cpp 
    storage/AnyPropertyMap.cpp 
    storage/SQLiteWrapper.cpp 
    metamodel/Actor.cpp 
    metamodel/Diagram.cpp 
    metamodel/Element.cpp 
    metamodel/Project.cpp 
    metamodel/UseCaseDiagram.cpp 
    tests/ActiveRecordTest.cpp 
    tests/PropertyTest.cpp 
    tests/AnyPropertyMapTest.cpp 
    tests/DiagramTest.cpp 
    tests/ProjectTest.cpp 
    tests/SQLiteWrapperTest.cpp 
    tests/main.cpp
)

enable_testing()
add_test(remtest ${rem_SOURCE_DIR}/../bin/remtest)
