/*
 * Rem - Requirements and Entity Modeler = UML + AOP + Open Source + Cross Platform
 * Copyright (C) 2008 Adrian Kosmaczewski - http://remproject.org/
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

//! Contains the implementation of the tests::PropertyTest class.
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

#include <sstream>

#include <Poco/DateTime.h>

#ifndef PROPERTY_H_
#include "../utility/Property.h"
#endif

#ifndef ANYPROPERTY_H_
#include "../storage/AnyProperty.h"
#endif

using utility::Property;
using storage::AnyProperty;
using Poco::DateTime;
using std::string;
using std::stringstream;

namespace tests
{
    PropertyTest::PropertyTest()
    {
    }

    PropertyTest::~PropertyTest()
    {
    }

    void PropertyTest::testCanCreatePropertiesOfDifferentTypes()
    {
        string name1("prop1");
        string name2("prop2");
        string name3("prop3");
        string name4("prop4");
        string name5("prop5");
        
        bool ok = true;
        string someValue("name");
        int integer = 34;
        double d = 45.24;
        DateTime now;

        Property<string, bool> prop1(name1, ok);
        CPPUNIT_ASSERT_EQUAL(ok, prop1());
        CPPUNIT_ASSERT_EQUAL(ok, prop1.getValue());
        CPPUNIT_ASSERT_EQUAL(name1, prop1.getName());

        Property<string, string> prop2(name2, someValue);
        CPPUNIT_ASSERT_EQUAL(someValue, prop2());
        CPPUNIT_ASSERT_EQUAL(someValue, prop2.getValue());
        CPPUNIT_ASSERT_EQUAL(name2, prop2.getName());

        Property<string, int> prop3(name3, integer);
        CPPUNIT_ASSERT_EQUAL(integer, prop3());
        CPPUNIT_ASSERT_EQUAL(integer, prop3.getValue());
        CPPUNIT_ASSERT_EQUAL(name3, prop3.getName());

        Property<string, double> prop4(name4, d);
        CPPUNIT_ASSERT_EQUAL(d, prop4());
        CPPUNIT_ASSERT_EQUAL(d, prop4.getValue());
        CPPUNIT_ASSERT_EQUAL(name4, prop4.getName());
        
        Property<string, DateTime> prop5(name5, now);
        CPPUNIT_ASSERT_EQUAL(now.utcTime(), prop5().utcTime());
        CPPUNIT_ASSERT_EQUAL(now.utcTime(), prop5.getValue().utcTime());
        CPPUNIT_ASSERT_EQUAL(name5, prop5.getName());
    }
    
    void PropertyTest::testDefaultPropertiesAcceptAnyValue()
    {
        bool ok = true;
        string someValue("name");
        int integer = 34;
        double d = 45.24;
        DateTime now;
        
        string name("prop");
        AnyProperty prop(name);
        CPPUNIT_ASSERT_EQUAL(name, prop.getName());

        prop.set<bool>(ok);
        bool stored1 = prop.get<bool>();
        CPPUNIT_ASSERT_EQUAL(ok, stored1);
        CPPUNIT_ASSERT_EQUAL(string("prop = 1"), prop.getNameValuePair());

        prop.set<int>(integer);
        int stored2 = prop.get<int>();
        CPPUNIT_ASSERT_EQUAL(integer, stored2);
        CPPUNIT_ASSERT_EQUAL(string("prop = 34"), prop.getNameValuePair());

        prop.set<string>(someValue);
        string stored3 = prop.get<string>();
        CPPUNIT_ASSERT_EQUAL(someValue, stored3);
        CPPUNIT_ASSERT_EQUAL(string("prop = 'name'"), prop.getNameValuePair());

        prop.set<double>(d);
        double stored4 = prop.get<double>();
        CPPUNIT_ASSERT_EQUAL(d, stored4);
        CPPUNIT_ASSERT_EQUAL(string("prop = 45.24"), prop.getNameValuePair());
        
        prop.set<DateTime>(now);
        DateTime stored5 = prop.get<DateTime>();
        stringstream nameValue;
        nameValue << "prop = ";
        nameValue << now.utcTime();
        CPPUNIT_ASSERT_EQUAL(now.utcTime(), stored5.utcTime());
        CPPUNIT_ASSERT_EQUAL(nameValue.str(), prop.getNameValuePair());
    }
    
    void PropertyTest::testCanUseCopyConstructorSafely()
    {
        bool ok = true;
        string someValue("name");
        int integer = 34;
        double d = 45.24;
        DateTime now;
        
        string name("prop");

        AnyProperty prop(name);
        AnyProperty propCopy(prop);
        CPPUNIT_ASSERT_EQUAL(propCopy.getName(), prop.getName());

        prop.set<bool>(ok);
        AnyProperty propCopy2(prop);
        bool stored1 = propCopy2.get<bool>();
        CPPUNIT_ASSERT_EQUAL(ok, stored1);
        CPPUNIT_ASSERT_EQUAL(string("prop = 1"), propCopy2.getNameValuePair());

        prop.set<int>(integer);
        AnyProperty propCopy3(prop);
        int stored2 = propCopy3.get<int>();
        CPPUNIT_ASSERT_EQUAL(integer, stored2);
        CPPUNIT_ASSERT_EQUAL(string("prop = 34"), propCopy3.getNameValuePair());

        prop.set<string>(someValue);
        AnyProperty propCopy4(prop);
        string stored3 = propCopy4.get<string>();
        CPPUNIT_ASSERT_EQUAL(someValue, stored3);
        CPPUNIT_ASSERT_EQUAL(string("prop = 'name'"), propCopy4.getNameValuePair());

        prop.set<double>(d);
        AnyProperty propCopy5(prop);
        double stored4 = propCopy5.get<double>();
        CPPUNIT_ASSERT_EQUAL(d, stored4);
        CPPUNIT_ASSERT_EQUAL(string("prop = 45.24"), propCopy5.getNameValuePair());        

        prop.set<DateTime>(now);
        AnyProperty propCopy6(prop);
        DateTime stored5 = propCopy6.get<DateTime>();
        stringstream nameValue;
        nameValue << "prop = ";
        nameValue << now.utcTime();
        CPPUNIT_ASSERT_EQUAL(now.utcTime(), stored5.utcTime());
        CPPUNIT_ASSERT_EQUAL(nameValue.str(), propCopy6.getNameValuePair());
    }
    
    void PropertyTest::testCanUseAssignmentOperatorSafely()
    {
        bool ok = true;
        string someValue("name");
        int integer = 34;
        double d = 45.24;
        DateTime now;
        
        string name("prop");

        AnyProperty prop(name);
        AnyProperty propCopy = prop;
        CPPUNIT_ASSERT_EQUAL(propCopy.getName(), prop.getName());

        prop.set<bool>(ok);
        AnyProperty propCopy2 = prop;
        bool stored1 = propCopy2.get<bool>();
        CPPUNIT_ASSERT_EQUAL(ok, stored1);
        CPPUNIT_ASSERT_EQUAL(string("prop = 1"), propCopy2.getNameValuePair());

        prop.set<int>(integer);
        AnyProperty propCopy3 = prop;
        int stored2 = propCopy3.get<int>();
        CPPUNIT_ASSERT_EQUAL(integer, stored2);
        CPPUNIT_ASSERT_EQUAL(string("prop = 34"), propCopy3.getNameValuePair());

        prop.set<string>(someValue);
        AnyProperty propCopy4 = prop;
        string stored3 = propCopy4.get<string>();
        CPPUNIT_ASSERT_EQUAL(someValue, stored3);
        CPPUNIT_ASSERT_EQUAL(string("prop = 'name'"), propCopy4.getNameValuePair());

        prop.set<double>(d);
        AnyProperty propCopy5 = prop;
        double stored4 = propCopy5.get<double>();
        CPPUNIT_ASSERT_EQUAL(d, stored4);
        CPPUNIT_ASSERT_EQUAL(string("prop = 45.24"), propCopy5.getNameValuePair());        

        prop.set<DateTime>(now);
        AnyProperty propCopy6 = prop;
        DateTime stored5 = propCopy6.get<DateTime>();
        stringstream nameValue;
        nameValue << "prop = ";
        nameValue << now.utcTime();
        CPPUNIT_ASSERT_EQUAL(now.utcTime(), stored5.utcTime());
        CPPUNIT_ASSERT_EQUAL(nameValue.str(), propCopy6.getNameValuePair());
    }
}
