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

#ifndef PROPERTY_H_
#include "../storage/Property.h"
#endif

#ifndef ANYPROPERTY_H_
#include "../storage/AnyProperty.h"
#endif

using namespace storage;

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

        Property<std::string, bool> prop1(name1, ok);
        CPPUNIT_ASSERT_EQUAL(ok, prop1());
        CPPUNIT_ASSERT_EQUAL(ok, prop1.getValue());
        CPPUNIT_ASSERT_EQUAL(name1, prop1.getName());

        Property<std::string, std::string> prop2(name2, someValue);
        CPPUNIT_ASSERT_EQUAL(someValue, prop2());
        CPPUNIT_ASSERT_EQUAL(someValue, prop2.getValue());
        CPPUNIT_ASSERT_EQUAL(name2, prop2.getName());

        Property<std::string, int> prop3(name3, integer);
        CPPUNIT_ASSERT_EQUAL(integer, prop3());
        CPPUNIT_ASSERT_EQUAL(integer, prop3.getValue());
        CPPUNIT_ASSERT_EQUAL(name3, prop3.getName());

        Property<std::string, double> prop4(name4, d);
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
        AnyProperty prop(name);
        CPPUNIT_ASSERT_EQUAL(name, prop.getName());

        prop.setBoolean(ok);
        bool stored1 = prop.getBoolean();
        CPPUNIT_ASSERT_EQUAL(ok, stored1);
        CPPUNIT_ASSERT_EQUAL(std::string("prop = 1"), prop.getNameValuePair());

        prop.setInteger(integer);
        int stored2 = prop.getInteger();
        CPPUNIT_ASSERT_EQUAL(integer, stored2);
        CPPUNIT_ASSERT_EQUAL(std::string("prop = 34"), prop.getNameValuePair());

        prop.setString(someValue);
        std::string stored3 = prop.getString();
        CPPUNIT_ASSERT_EQUAL(someValue, stored3);
        CPPUNIT_ASSERT_EQUAL(std::string("prop = 'name'"), prop.getNameValuePair());

        prop.setDouble(d);
        double stored4 = prop.getDouble();
        CPPUNIT_ASSERT_EQUAL(d, stored4);
        CPPUNIT_ASSERT_EQUAL(std::string("prop = 45.24"), prop.getNameValuePair());
    }
    
    void PropertyTest::testCanUseCopyConstructorSafely()
    {
        bool ok = true;
        std::string someValue("name");
        int integer = 34;
        double d = 45.24;
        
        std::string name("prop");

        AnyProperty prop(name);
        AnyProperty propCopy(prop);
        CPPUNIT_ASSERT_EQUAL(propCopy.getName(), prop.getName());

        prop.setBoolean(ok);
        AnyProperty propCopy2(prop);
        bool stored1 = propCopy2.getBoolean();
        CPPUNIT_ASSERT_EQUAL(ok, stored1);
        CPPUNIT_ASSERT_EQUAL(std::string("prop = 1"), propCopy2.getNameValuePair());

        prop.setInteger(integer);
        AnyProperty propCopy3(prop);
        int stored2 = propCopy3.getInteger();
        CPPUNIT_ASSERT_EQUAL(integer, stored2);
        CPPUNIT_ASSERT_EQUAL(std::string("prop = 34"), propCopy3.getNameValuePair());

        prop.setString(someValue);
        AnyProperty propCopy4(prop);
        std::string stored3 = propCopy4.getString();
        CPPUNIT_ASSERT_EQUAL(someValue, stored3);
        CPPUNIT_ASSERT_EQUAL(std::string("prop = 'name'"), propCopy4.getNameValuePair());

        prop.setDouble(d);
        AnyProperty propCopy5(prop);
        double stored4 = propCopy5.getDouble();
        CPPUNIT_ASSERT_EQUAL(d, stored4);
        CPPUNIT_ASSERT_EQUAL(std::string("prop = 45.24"), propCopy5.getNameValuePair());        
    }
    
    void PropertyTest::testCanUseAssignmentOperatorSafely()
    {
        bool ok = true;
        std::string someValue("name");
        int integer = 34;
        double d = 45.24;
        
        std::string name("prop");

        AnyProperty prop(name);
        AnyProperty propCopy = prop;
        CPPUNIT_ASSERT_EQUAL(propCopy.getName(), prop.getName());

        prop.setBoolean(ok);
        AnyProperty propCopy2 = prop;
        bool stored1 = propCopy2.getBoolean();
        CPPUNIT_ASSERT_EQUAL(ok, stored1);
        CPPUNIT_ASSERT_EQUAL(std::string("prop = 1"), propCopy2.getNameValuePair());

        prop.setInteger(integer);
        AnyProperty propCopy3 = prop;
        int stored2 = propCopy3.getInteger();
        CPPUNIT_ASSERT_EQUAL(integer, stored2);
        CPPUNIT_ASSERT_EQUAL(std::string("prop = 34"), propCopy3.getNameValuePair());

        prop.setString(someValue);
        AnyProperty propCopy4 = prop;
        std::string stored3 = propCopy4.getString();
        CPPUNIT_ASSERT_EQUAL(someValue, stored3);
        CPPUNIT_ASSERT_EQUAL(std::string("prop = 'name'"), propCopy4.getNameValuePair());

        prop.setDouble(d);
        AnyProperty propCopy5 = prop;
        double stored4 = propCopy5.getDouble();
        CPPUNIT_ASSERT_EQUAL(d, stored4);
        CPPUNIT_ASSERT_EQUAL(std::string("prop = 45.24"), propCopy5.getNameValuePair());        
    }
}
