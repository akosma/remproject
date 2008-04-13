/*!
 * \file AnyPropertyMapTest.cpp
 *
 * Contains the implementation of the tests::AnyPropertyMapTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/23/08
 */

#include "AnyPropertyMapTest.h"

#include <Poco/Exception.h>
#include <iostream>

#ifndef ANYPROPERTYMAP_H_
#include "../storage/AnyPropertyMap.h"
#endif

#ifndef ANYPROPERTY_H_
#include "../storage/AnyProperty.h"
#endif

/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    /*!
     * AnyPropertyMapTest Constructor.
     */
    AnyPropertyMapTest::AnyPropertyMapTest()
    {
    }
    
    /*!
     * AnyPropertyMapTest Virtual destructor.
     */
    AnyPropertyMapTest::~AnyPropertyMapTest()
    {
    }

    /*!
     * Called by CppUnit before each test.
     */
    void AnyPropertyMapTest::setUp()
    {
    }
    
    /*!
     * Called by CppUnit after each test.
     */
    void AnyPropertyMapTest::tearDown()
    {
    }

    /*!
     * Tests something.
     */
    void AnyPropertyMapTest::testAddAndRetrieveProperties()
    {
        storage::AnyPropertyMap map;

        std::string name1("prop1");
        std::string name2("prop2");
        std::string name3("prop3");
        std::string name4("prop4");
        
        bool ok = true;
        std::string someValue("name");
        int integer = 34;
        double d = 45.24;

        CPPUNIT_ASSERT(map.isEmpty());
        CPPUNIT_ASSERT_EQUAL(0, (int)map.count());
        CPPUNIT_ASSERT(!map.hasProperty(name1));
        CPPUNIT_ASSERT(!map.hasProperty(name2));
        CPPUNIT_ASSERT(!map.hasProperty(name3));
        CPPUNIT_ASSERT(!map.hasProperty(name4));
        
        map.setBooleanProperty(name1, ok);
        CPPUNIT_ASSERT_EQUAL(1, (int)map.count());

        map.setStringProperty(name2, someValue);
        CPPUNIT_ASSERT_EQUAL(2, (int)map.count());

        map.setIntegerProperty(name3, integer);
        CPPUNIT_ASSERT_EQUAL(3, (int)map.count());

        map.setDoubleProperty(name4, d);
        CPPUNIT_ASSERT_EQUAL(4, (int)map.count());

        CPPUNIT_ASSERT(map.hasProperty(name1));
        CPPUNIT_ASSERT(map.hasProperty(name2));
        CPPUNIT_ASSERT(map.hasProperty(name3));
        CPPUNIT_ASSERT(map.hasProperty(name4));
        
        CPPUNIT_ASSERT_EQUAL(ok, map.getBoolean(name1));
        CPPUNIT_ASSERT_EQUAL(someValue, map.getString(name2));
        CPPUNIT_ASSERT_EQUAL(integer, map.getInteger(name3));
        CPPUNIT_ASSERT_EQUAL(d, map.getDouble(name4));
        
        std::string tableName("test");
        const int id = 23;
        CPPUNIT_ASSERT_EQUAL(std::string("INSERT INTO test (prop1, prop2, prop3, prop4) VALUES (1, 'name', 34, 45.24);"), map.getStringForInsert(tableName));
        CPPUNIT_ASSERT_EQUAL(std::string("UPDATE test SET prop1 = 1, prop2 = 'name', prop3 = 34, prop4 = 45.24 WHERE id = 23;"), map.getStringForUpdate(tableName, id));
        CPPUNIT_ASSERT_EQUAL(std::string("CREATE TABLE test(\nprop1 BOOLEAN,\nprop2 TEXT,\nprop3 INTEGER,\nprop4 REAL);"), map.getStringForCreateTable(tableName));
    }
    
    void AnyPropertyMapTest::testRetrievingInvalidPropertiesRaiseException()
    {
        storage::AnyPropertyMap map;
        std::string name1("prop1");
        try
        {
            std::string value = map.getString(name1);
        }
        catch(Poco::BadCastException& e)
        {
            CPPUNIT_ASSERT_EQUAL(e.message(), std::string("RefAnyCast: Failed to convert between const Any types"));
        }
    }
}
