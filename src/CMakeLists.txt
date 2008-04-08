project (rem)

include_directories (
    metamodel 
    storage 
    tests 
    /usr/local/include 
    /usr/include 
    ${rem_SOURCE_DIR}/../lib/poco/Foundation/include
)

link_directories (
    /usr/lib/ 
    /usr/local/lib 
    ${rem_SOURCE_DIR}/../lib/poco/lib/Darwin/Power_Macintosh
)

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
