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

//! Contains the implementation of the tests::SQLiteWrapperTest class.
/*!
 * \file SQLiteWrapperTest.cpp
 *
 * Contains the implementation of the tests::SQLiteWrapperTest class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/23/08
 */

#include "SQLiteWrapperTest.h"

#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <sqlite3.h>

#ifndef SQLITEWRAPPER_H_
#include "../storage/SQLiteWrapper.h"
#endif

using storage::SQLiteWrapper;
using std::string;
using std::vector;
using std::fstream;

namespace tests
{
    SQLiteWrapperTest::SQLiteWrapperTest()
    : _filename("test.db")
    {
    }

    SQLiteWrapperTest::~SQLiteWrapperTest()
    {
    }

    void SQLiteWrapperTest::testCreateDatabase()
    {
        // Delete the file if it already exists
        remove(_filename.c_str());
    
        // Calling the singleton "automagically" creates the file
        SQLiteWrapper& dal = SQLiteWrapper::get();
        dal.setFileName(_filename);

        // We force here to have something in the database
        bool ok = dal.open();
        CPPUNIT_ASSERT(ok);
        ok = dal.executeQuery("CREATE TABLE createTable(test1 int, test2 varchar);");
        CPPUNIT_ASSERT(ok);
        dal.close();
    
        // Check that the file exists
        fstream fin;
        fin.open(_filename.c_str(), fstream::in);
        CPPUNIT_ASSERT(fin.is_open());
        fin.close();
    }

    void SQLiteWrapperTest::testCreateTable()
    {
        SQLiteWrapper& dal = SQLiteWrapper::get();
        bool ok = dal.open();
        CPPUNIT_ASSERT(ok);
        CPPUNIT_ASSERT(!dal.tableExists("test"));
        ok = dal.executeQuery("CREATE TABLE test(test1 int, test2 varchar);");
        CPPUNIT_ASSERT(ok);
        CPPUNIT_ASSERT(dal.tableExists("test"));
        dal.close();
    }

    void SQLiteWrapperTest::testInsertion()
    {
        SQLiteWrapper& dal = SQLiteWrapper::get();
        bool ok = true;
        ok = dal.open();
        for (int i = 0; i < 1000; i++)
        {
            CPPUNIT_ASSERT(ok);
            ok = dal.executeQuery("INSERT INTO test (test1, test2) VALUES (1, '2');");
            CPPUNIT_ASSERT(ok);
        }
        dal.close();
    }

    void SQLiteWrapperTest::testSelect()
    {
        SQLiteWrapper& dal = SQLiteWrapper::get();
        bool ok = dal.open();
        CPPUNIT_ASSERT(ok);
        ok = dal.executeQuery("SELECT test1, test2 FROM test");
        CPPUNIT_ASSERT(ok);
        dal.close();
        
        const vector<string>& data = dal.getData();
        const size_t numberOfHeaders = dal.getTableHeaders().size();
        const size_t dataItems = data.size();
        
        CPPUNIT_ASSERT(dataItems == 2000);
        CPPUNIT_ASSERT(numberOfHeaders == 2);
        
        // Iterate over the data to see what's there
        for (size_t i = 0; i < dataItems / numberOfHeaders; i = i + numberOfHeaders)
        {
            CPPUNIT_ASSERT(data[i] == "1");
            CPPUNIT_ASSERT(data[i + 1] == "2");
        }
    }
}
