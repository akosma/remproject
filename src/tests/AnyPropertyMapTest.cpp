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

//! Contains the implementation of the tests::AnyPropertyMapTest class.
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

#include <sstream>

#if defined(_WIN32)
#include <new>
using std::bad_alloc;
#endif

#include <Poco/Exception.h>
#include <Poco/DateTime.h>

#ifndef ANYPROPERTYMAP_H_
#include "../storage/AnyPropertyMap.h"
#endif

using storage::AnyPropertyMap;
using Poco::DateTime;
using Poco::BadCastException;
using std::string;
using std::stringstream;

namespace tests
{
    AnyPropertyMapTest::AnyPropertyMapTest()
    {
    }

    AnyPropertyMapTest::~AnyPropertyMapTest()
    {
    }

    void AnyPropertyMapTest::testAddAndRetrieveProperties()
    {
        AnyPropertyMap map;

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

        CPPUNIT_ASSERT(map.isEmpty());
        CPPUNIT_ASSERT_EQUAL(0, (int)map.count());
        CPPUNIT_ASSERT(!map.hasProperty(name1));
        CPPUNIT_ASSERT(!map.hasProperty(name2));
        CPPUNIT_ASSERT(!map.hasProperty(name3));
        CPPUNIT_ASSERT(!map.hasProperty(name4));
        
        map.set<bool>(name1, ok);
        CPPUNIT_ASSERT_EQUAL(1, (int)map.count());

        map.set<string>(name2, someValue);
        CPPUNIT_ASSERT_EQUAL(2, (int)map.count());

        map.set<int>(name3, integer);
        CPPUNIT_ASSERT_EQUAL(3, (int)map.count());

        map.set<double>(name4, d);
        CPPUNIT_ASSERT_EQUAL(4, (int)map.count());

        map.set<DateTime>(name5, now);
        CPPUNIT_ASSERT_EQUAL(5, (int)map.count());

        CPPUNIT_ASSERT(map.hasProperty(name1));
        CPPUNIT_ASSERT(map.hasProperty(name2));
        CPPUNIT_ASSERT(map.hasProperty(name3));
        CPPUNIT_ASSERT(map.hasProperty(name4));
        CPPUNIT_ASSERT(map.hasProperty(name5));
        
        CPPUNIT_ASSERT_EQUAL(ok, map.get<bool>(name1));
        CPPUNIT_ASSERT_EQUAL(someValue, map.get<string>(name2));
        CPPUNIT_ASSERT_EQUAL(integer, map.get<int>(name3));
        CPPUNIT_ASSERT_EQUAL(d, map.get<double>(name4));
        CPPUNIT_ASSERT_EQUAL(now.utcTime(), map.get<DateTime>(name5).utcTime());
        
        stringstream insertQuery;
        insertQuery << "INSERT INTO test (prop1, prop2, prop3, prop4, prop5) VALUES ";
        insertQuery << "(1, 'name', 34, 45.24, ";
        insertQuery << now.utcTime();
        insertQuery << ");";
        
        stringstream updateQuery;
        updateQuery << "UPDATE test SET prop1 = 1, prop2 = 'name', prop3 = 34, prop4 = 45.24, prop5 = ";
        updateQuery << now.utcTime();
        updateQuery << " WHERE id = 23;";

        string createQuery("CREATE TABLE test(\nprop1 BOOLEAN,\nprop2 TEXT,\nprop3 INTEGER,\nprop4 REAL,\nprop5 DATETIME);");

        string tableName("test");
        const int id = 23;
        CPPUNIT_ASSERT_EQUAL(insertQuery.str(), map.getStringForInsert(tableName));
        CPPUNIT_ASSERT_EQUAL(updateQuery.str(), map.getStringForUpdate(tableName, id));
        CPPUNIT_ASSERT_EQUAL(createQuery, map.getStringForCreateTable(tableName));
    }
    
    void AnyPropertyMapTest::testRetrievingInvalidPropertiesRaiseException()
    {
        AnyPropertyMap map;
        string name1("prop1");
        try
        {
            string value = map.get<string>(name1);
        }
#if defined(_WIN32)
        catch(bad_alloc& e)
        {
            string expectedMessage("bad allocation");
            string message(e.what());
            CPPUNIT_ASSERT_EQUAL(expectedMessage, message);
        }
#else
        catch(BadCastException& e)
        {
            CPPUNIT_ASSERT_EQUAL(e.message(), string("RefAnyCast: Failed to convert between const Any types"));
        }
#endif
    }
    
    void AnyPropertyMapTest::testCanUseCopyConstructorSafely()
    {
        AnyPropertyMap map;

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
        
        map.set<bool>(name1, ok);
        map.set<string>(name2, someValue);
        map.set<int>(name3, integer);
        map.set<double>(name4, d);
        map.set<DateTime>(name5, now);
        
        AnyPropertyMap mapCopy(map);

        CPPUNIT_ASSERT_EQUAL(5, (int)mapCopy.count());
        CPPUNIT_ASSERT(mapCopy.hasProperty(name1));
        CPPUNIT_ASSERT(mapCopy.hasProperty(name2));
        CPPUNIT_ASSERT(mapCopy.hasProperty(name3));
        CPPUNIT_ASSERT(mapCopy.hasProperty(name4));
        CPPUNIT_ASSERT(mapCopy.hasProperty(name5));
        CPPUNIT_ASSERT_EQUAL(ok, mapCopy.get<bool>(name1));
        CPPUNIT_ASSERT_EQUAL(someValue, mapCopy.get<string>(name2));
        CPPUNIT_ASSERT_EQUAL(integer, mapCopy.get<int>(name3));
        CPPUNIT_ASSERT_EQUAL(d, mapCopy.get<double>(name4));
        CPPUNIT_ASSERT_EQUAL(now.utcTime(), mapCopy.get<DateTime>(name5).utcTime());

        stringstream insertQuery;
        insertQuery << "INSERT INTO test (prop1, prop2, prop3, prop4, prop5) VALUES ";
        insertQuery << "(1, 'name', 34, 45.24, ";
        insertQuery << now.utcTime();
        insertQuery << ");";
        
        stringstream updateQuery;
        updateQuery << "UPDATE test SET prop1 = 1, prop2 = 'name', prop3 = 34, prop4 = 45.24, prop5 = ";
        updateQuery << now.utcTime();
        updateQuery << " WHERE id = 23;";

        string createQuery("CREATE TABLE test(\nprop1 BOOLEAN,\nprop2 TEXT,\nprop3 INTEGER,\nprop4 REAL,\nprop5 DATETIME);");

        string tableName("test");
        const int id = 23;
        CPPUNIT_ASSERT_EQUAL(insertQuery.str(), mapCopy.getStringForInsert(tableName));
        CPPUNIT_ASSERT_EQUAL(updateQuery.str(), mapCopy.getStringForUpdate(tableName, id));
        CPPUNIT_ASSERT_EQUAL(createQuery, mapCopy.getStringForCreateTable(tableName));
    }
    
    void AnyPropertyMapTest::testCanUseAssignmentOperatorSafely()
    {
        AnyPropertyMap map;

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
        
        map.set<bool>(name1, ok);
        map.set<string>(name2, someValue);
        map.set<int>(name3, integer);
        map.set<double>(name4, d);
        map.set<DateTime>(name5, now);
        
        AnyPropertyMap mapCopy = map;

        CPPUNIT_ASSERT_EQUAL(5, (int)mapCopy.count());
        CPPUNIT_ASSERT(mapCopy.hasProperty(name1));
        CPPUNIT_ASSERT(mapCopy.hasProperty(name2));
        CPPUNIT_ASSERT(mapCopy.hasProperty(name3));
        CPPUNIT_ASSERT(mapCopy.hasProperty(name4));
        CPPUNIT_ASSERT(mapCopy.hasProperty(name5));
        CPPUNIT_ASSERT_EQUAL(ok, mapCopy.get<bool>(name1));
        CPPUNIT_ASSERT_EQUAL(someValue, mapCopy.get<string>(name2));
        CPPUNIT_ASSERT_EQUAL(integer, mapCopy.get<int>(name3));
        CPPUNIT_ASSERT_EQUAL(d, mapCopy.get<double>(name4));
        CPPUNIT_ASSERT_EQUAL(now.utcTime(), mapCopy.get<DateTime>(name5).utcTime());

        stringstream insertQuery;
        insertQuery << "INSERT INTO test (prop1, prop2, prop3, prop4, prop5) VALUES ";
        insertQuery << "(1, 'name', 34, 45.24, ";
        insertQuery << now.utcTime();
        insertQuery << ");";
        
        stringstream updateQuery;
        updateQuery << "UPDATE test SET prop1 = 1, prop2 = 'name', prop3 = 34, prop4 = 45.24, prop5 = ";
        updateQuery << now.utcTime();
        updateQuery << " WHERE id = 23;";

        string createQuery("CREATE TABLE test(\nprop1 BOOLEAN,\nprop2 TEXT,\nprop3 INTEGER,\nprop4 REAL,\nprop5 DATETIME);");

        string tableName("test");
        const int id = 23;
        CPPUNIT_ASSERT_EQUAL(insertQuery.str(), mapCopy.getStringForInsert(tableName));
        CPPUNIT_ASSERT_EQUAL(updateQuery.str(), mapCopy.getStringForUpdate(tableName, id));
        CPPUNIT_ASSERT_EQUAL(createQuery, mapCopy.getStringForCreateTable(tableName));
    }
}
