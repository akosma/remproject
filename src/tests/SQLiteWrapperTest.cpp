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

/*!
 * \namespace tests
 * This namespace holds the classes that derive from 
 * CppUnit::TestFixture, containing unit tests for the application.
 */
namespace tests
{
    /*!
     * Constructor.
     */
    SQLiteWrapperTest::SQLiteWrapperTest()
    : _filename("test.db")
    {
    }
    
    /*!
     * Virtual destructor.
     */
    SQLiteWrapperTest::~SQLiteWrapperTest()
    {
    }
    
    /*!
     * Called by CppUnit before each test.
     */
    void SQLiteWrapperTest::setUp()
    {
    }
    
    /*!
     * Called by CppUnit after each test.
     */
    void SQLiteWrapperTest::tearDown()
    {
    }
    
    /*!
     * Tests the automatic creation of a database file.
     */
    void SQLiteWrapperTest::testCreateDatabase()
    {
        // Delete the file if it already exists
        remove(_filename.c_str());
    
        // Calling the singleton "automagically" creates the file
        storage::SQLiteWrapper::setFileName(_filename);
        storage::SQLiteWrapper::get();
    
        // Check that the file exists
        std::fstream fin;
        fin.open(_filename.c_str(), std::fstream::in);
        CPPUNIT_ASSERT(fin.is_open());
        fin.close();
    }
    
    /*!
     * Tests the creation of tables.
     */
    void SQLiteWrapperTest::testCreateTable()
    {
        storage::SQLiteWrapper& dal = storage::SQLiteWrapper::get();
        bool ok = dal.open();
        CPPUNIT_ASSERT(ok);
        CPPUNIT_ASSERT(!dal.tableExists("test"));
        ok = dal.executeQuery("CREATE TABLE test(test1 int, test2 varchar);");
        CPPUNIT_ASSERT(ok);
        CPPUNIT_ASSERT(dal.tableExists("test"));
        dal.close();
    }
    
    /*!
     * Tests the insertion of values in the table created previously.
     */
    void SQLiteWrapperTest::testInsertion()
    {
        storage::SQLiteWrapper& dal = storage::SQLiteWrapper::get();
        bool ok = true;
        for (int i = 0; i < 1000; i++)
        {
            ok = dal.open();
            CPPUNIT_ASSERT(ok);
            ok = dal.executeQuery("INSERT INTO test (test1, test2) VALUES (1, '2');");
            CPPUNIT_ASSERT(ok);
            dal.close();
        }
    }
    
    /*!
     * Tests the reading of values stored previously.
     */
    void SQLiteWrapperTest::testSelect()
    {
        storage::SQLiteWrapper& dal = storage::SQLiteWrapper::get();
        bool ok = dal.open();
        CPPUNIT_ASSERT(ok);
        ok = dal.executeQuery("SELECT test1, test2 FROM test");
        CPPUNIT_ASSERT(ok);
        dal.close();
        
        const std::vector<std::string>& data = dal.getData();
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
