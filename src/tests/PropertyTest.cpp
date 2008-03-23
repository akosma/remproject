/*!
 * \file PropertyTest.cpp
 *
 * Contains the implementation of the tests::PropertyTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/23/08
 */

#include "PropertyTest.h"
#include <Poco/Any.h>
#include <iostream>

#ifndef PROPERTY_H_
#include "../storage/Property.h"
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
     * PropertyTest Constructor.
     */
    PropertyTest::PropertyTest()
    {
    }
    
    /*!
     * PropertyTest Virtual destructor.
     */
    PropertyTest::~PropertyTest()
    {
    }

    /*!
     * Called by CppUnit before each test.
     */
    void PropertyTest::setUp()
    {
    }
    
    /*!
     * Called by CppUnit after each test.
     */
    void PropertyTest::tearDown()
    {
    }

    /*!
     * Tests something.
     */
    void PropertyTest::testCanCreatePropertiesOfDifferentTypes()
    {
        std::string name1("prop1");
        std::string name2("prop2");
        std::string name3("prop3");
        std::string name4("prop4");
        
        bool ok = true;
        std::string someValue("name");
        int integer = 34;
        double d = 45.24;

        storage::Property<std::string, bool> prop1(name1, ok);
        CPPUNIT_ASSERT_EQUAL(ok, prop1());
        CPPUNIT_ASSERT_EQUAL(ok, prop1.getValue());
        CPPUNIT_ASSERT_EQUAL(name1, prop1.getName());

        storage::Property<std::string, std::string> prop2(name2, someValue);
        CPPUNIT_ASSERT_EQUAL(someValue, prop2());
        CPPUNIT_ASSERT_EQUAL(someValue, prop2.getValue());
        CPPUNIT_ASSERT_EQUAL(name2, prop2.getName());

        storage::Property<std::string, int> prop3(name3, integer);
        CPPUNIT_ASSERT_EQUAL(integer, prop3());
        CPPUNIT_ASSERT_EQUAL(integer, prop3.getValue());
        CPPUNIT_ASSERT_EQUAL(name3, prop3.getName());

        storage::Property<std::string, double> prop4(name4, d);
        CPPUNIT_ASSERT_EQUAL(d, prop4());
        CPPUNIT_ASSERT_EQUAL(d, prop4.getValue());
        CPPUNIT_ASSERT_EQUAL(name4, prop4.getName());
    }
    
    void PropertyTest::testDefaultPropertiesAcceptAnyValue()
    {
        bool ok = true;
        std::string someValue("name");
        int integer = 34;
        double d = 45.24;
        
        std::string name("prop");
        storage::AnyProperty prop(name);
        CPPUNIT_ASSERT_EQUAL(name, prop.getName());

        prop.setBoolean(ok);
        bool stored1 = prop.getBoolean();
        CPPUNIT_ASSERT_EQUAL(ok, stored1);

        prop.setInteger(integer);
        int stored2 = prop.getInteger();
        CPPUNIT_ASSERT_EQUAL(integer, stored2);

        prop.setString(someValue);
        std::string stored3 = prop.getString();
        CPPUNIT_ASSERT_EQUAL(someValue, stored3);

        prop.setDouble(d);
        double stored4 = prop.getDouble();
        CPPUNIT_ASSERT_EQUAL(d, stored4);
    }
}
