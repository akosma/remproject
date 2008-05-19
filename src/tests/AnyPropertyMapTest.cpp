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

#if WIN32
#include <new>
#endif

#include <Poco/Exception.h>
#include <Poco/DateTime.h>

#ifndef ANYPROPERTYMAP_H_
#include "../storage/AnyPropertyMap.h"
#endif

using storage::AnyPropertyMap;

namespace tests
{
    AnyPropertyMapTest::AnyPropertyMapTest()
    {
    }

    AnyPropertyMapTest::~AnyPropertyMapTest()
    {
    }

    void AnyPropertyMapTest::setUp()
    {
    }

    void AnyPropertyMapTest::tearDown()
    {
    }

    void AnyPropertyMapTest::testAddAndRetrieveProperties()
    {
        AnyPropertyMap map;

        std::string name1("prop1");
        std::string name2("prop2");
        std::string name3("prop3");
        std::string name4("prop4");
        std::string name5("prop5");
        
        bool ok = true;
        std::string someValue("name");
        int integer = 34;
        double d = 45.24;
        Poco::DateTime now;

        CPPUNIT_ASSERT(map.isEmpty());
        CPPUNIT_ASSERT_EQUAL(0, (int)map.count());
        CPPUNIT_ASSERT(!map.hasProperty(name1));
        CPPUNIT_ASSERT(!map.hasProperty(name2));
        CPPUNIT_ASSERT(!map.hasProperty(name3));
        CPPUNIT_ASSERT(!map.hasProperty(name4));
        
        map.setBoolean(name1, ok);
        CPPUNIT_ASSERT_EQUAL(1, (int)map.count());

        map.setString(name2, someValue);
        CPPUNIT_ASSERT_EQUAL(2, (int)map.count());

        map.setInteger(name3, integer);
        CPPUNIT_ASSERT_EQUAL(3, (int)map.count());

        map.setDouble(name4, d);
        CPPUNIT_ASSERT_EQUAL(4, (int)map.count());

        map.setDateTime(name5, now);
        CPPUNIT_ASSERT_EQUAL(5, (int)map.count());

        CPPUNIT_ASSERT(map.hasProperty(name1));
        CPPUNIT_ASSERT(map.hasProperty(name2));
        CPPUNIT_ASSERT(map.hasProperty(name3));
        CPPUNIT_ASSERT(map.hasProperty(name4));
        CPPUNIT_ASSERT(map.hasProperty(name5));
        
        CPPUNIT_ASSERT_EQUAL(ok, map.getBoolean(name1));
        CPPUNIT_ASSERT_EQUAL(someValue, map.getString(name2));
        CPPUNIT_ASSERT_EQUAL(integer, map.getInteger(name3));
        CPPUNIT_ASSERT_EQUAL(d, map.getDouble(name4));
        CPPUNIT_ASSERT_EQUAL(now.utcTime(), map.getDateTime(name5).utcTime());
        
        std::stringstream insertQuery;
        insertQuery << "INSERT INTO test (prop1, prop2, prop3, prop4, prop5) VALUES ";
        insertQuery << "(1, 'name', 34, 45.24, ";
        insertQuery << now.utcTime();
        insertQuery << ");";
        
        std::stringstream updateQuery;
        updateQuery << "UPDATE test SET prop1 = 1, prop2 = 'name', prop3 = 34, prop4 = 45.24, prop5 = ";
        updateQuery << now.utcTime();
        updateQuery << " WHERE id = 23;";

        std::string createQuery("CREATE TABLE test(\nprop1 BOOLEAN,\nprop2 TEXT,\nprop3 INTEGER,\nprop4 REAL,\nprop5 DATETIME);");

        std::string tableName("test");
        const int id = 23;
        CPPUNIT_ASSERT_EQUAL(insertQuery.str(), map.getStringForInsert(tableName));
        CPPUNIT_ASSERT_EQUAL(updateQuery.str(), map.getStringForUpdate(tableName, id));
        CPPUNIT_ASSERT_EQUAL(createQuery, map.getStringForCreateTable(tableName));
    }
    
    void AnyPropertyMapTest::testRetrievingInvalidPropertiesRaiseException()
    {
        AnyPropertyMap map;
        std::string name1("prop1");
        try
        {
            std::string value = map.getString(name1);
        }
#if WIN32
		catch(std::bad_alloc& e)
		{
			std::string expectedMessage("bad allocation");
			std::string message(e.what());
			CPPUNIT_ASSERT_EQUAL(expectedMessage, message);
		}
#else
        catch(Poco::BadCastException& e)
        {
            CPPUNIT_ASSERT_EQUAL(e.message(), std::string("RefAnyCast: Failed to convert between const Any types"));
        }
#endif
    }
    
    void AnyPropertyMapTest::testCanUseCopyConstructorSafely()
    {
        AnyPropertyMap map;

        std::string name1("prop1");
        std::string name2("prop2");
        std::string name3("prop3");
        std::string name4("prop4");
        std::string name5("prop5");
        
        bool ok = true;
        std::string someValue("name");
        int integer = 34;
        double d = 45.24;
        Poco::DateTime now;
        
        map.setBoolean(name1, ok);
        map.setString(name2, someValue);
        map.setInteger(name3, integer);
        map.setDouble(name4, d);
        map.setDateTime(name5, now);
        
        AnyPropertyMap mapCopy(map);

        CPPUNIT_ASSERT_EQUAL(5, (int)mapCopy.count());
        CPPUNIT_ASSERT(mapCopy.hasProperty(name1));
        CPPUNIT_ASSERT(mapCopy.hasProperty(name2));
        CPPUNIT_ASSERT(mapCopy.hasProperty(name3));
        CPPUNIT_ASSERT(mapCopy.hasProperty(name4));
        CPPUNIT_ASSERT(mapCopy.hasProperty(name5));
        CPPUNIT_ASSERT_EQUAL(ok, mapCopy.getBoolean(name1));
        CPPUNIT_ASSERT_EQUAL(someValue, mapCopy.getString(name2));
        CPPUNIT_ASSERT_EQUAL(integer, mapCopy.getInteger(name3));
        CPPUNIT_ASSERT_EQUAL(d, mapCopy.getDouble(name4));
        CPPUNIT_ASSERT_EQUAL(now.utcTime(), mapCopy.getDateTime(name5).utcTime());

        std::stringstream insertQuery;
        insertQuery << "INSERT INTO test (prop1, prop2, prop3, prop4, prop5) VALUES ";
        insertQuery << "(1, 'name', 34, 45.24, ";
        insertQuery << now.utcTime();
        insertQuery << ");";
        
        std::stringstream updateQuery;
        updateQuery << "UPDATE test SET prop1 = 1, prop2 = 'name', prop3 = 34, prop4 = 45.24, prop5 = ";
        updateQuery << now.utcTime();
        updateQuery << " WHERE id = 23;";

        std::string createQuery("CREATE TABLE test(\nprop1 BOOLEAN,\nprop2 TEXT,\nprop3 INTEGER,\nprop4 REAL,\nprop5 DATETIME);");

        std::string tableName("test");
        const int id = 23;
        CPPUNIT_ASSERT_EQUAL(insertQuery.str(), mapCopy.getStringForInsert(tableName));
        CPPUNIT_ASSERT_EQUAL(updateQuery.str(), mapCopy.getStringForUpdate(tableName, id));
        CPPUNIT_ASSERT_EQUAL(createQuery, mapCopy.getStringForCreateTable(tableName));
    }
    
    void AnyPropertyMapTest::testCanUseAssignmentOperatorSafely()
    {
        AnyPropertyMap map;

        std::string name1("prop1");
        std::string name2("prop2");
        std::string name3("prop3");
        std::string name4("prop4");
        std::string name5("prop5");

        bool ok = true;
        std::string someValue("name");
        int integer = 34;
        double d = 45.24;
        Poco::DateTime now;
        
        map.setBoolean(name1, ok);
        map.setString(name2, someValue);
        map.setInteger(name3, integer);
        map.setDouble(name4, d);
        map.setDateTime(name5, now);
        
        AnyPropertyMap mapCopy = map;

        CPPUNIT_ASSERT_EQUAL(5, (int)mapCopy.count());
        CPPUNIT_ASSERT(mapCopy.hasProperty(name1));
        CPPUNIT_ASSERT(mapCopy.hasProperty(name2));
        CPPUNIT_ASSERT(mapCopy.hasProperty(name3));
        CPPUNIT_ASSERT(mapCopy.hasProperty(name4));
        CPPUNIT_ASSERT(mapCopy.hasProperty(name5));
        CPPUNIT_ASSERT_EQUAL(ok, mapCopy.getBoolean(name1));
        CPPUNIT_ASSERT_EQUAL(someValue, mapCopy.getString(name2));
        CPPUNIT_ASSERT_EQUAL(integer, mapCopy.getInteger(name3));
        CPPUNIT_ASSERT_EQUAL(d, mapCopy.getDouble(name4));
        CPPUNIT_ASSERT_EQUAL(now.utcTime(), mapCopy.getDateTime(name5).utcTime());

        std::stringstream insertQuery;
        insertQuery << "INSERT INTO test (prop1, prop2, prop3, prop4, prop5) VALUES ";
        insertQuery << "(1, 'name', 34, 45.24, ";
        insertQuery << now.utcTime();
        insertQuery << ");";
        
        std::stringstream updateQuery;
        updateQuery << "UPDATE test SET prop1 = 1, prop2 = 'name', prop3 = 34, prop4 = 45.24, prop5 = ";
        updateQuery << now.utcTime();
        updateQuery << " WHERE id = 23;";

        std::string createQuery("CREATE TABLE test(\nprop1 BOOLEAN,\nprop2 TEXT,\nprop3 INTEGER,\nprop4 REAL,\nprop5 DATETIME);");

        std::string tableName("test");
        const int id = 23;
        CPPUNIT_ASSERT_EQUAL(insertQuery.str(), mapCopy.getStringForInsert(tableName));
        CPPUNIT_ASSERT_EQUAL(updateQuery.str(), mapCopy.getStringForUpdate(tableName, id));
        CPPUNIT_ASSERT_EQUAL(createQuery, mapCopy.getStringForCreateTable(tableName));
    }
}
