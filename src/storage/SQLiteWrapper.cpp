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

/*!
 * \file SQLiteWrapper.cpp
 *
 * Contains the implementation of the storage::SQLiteWrapper class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/23/08
 */

#include "SQLiteWrapper.h"
#include <sstream>
#include <iostream>
#include <map>

/*!
 * \namespace storage
 * Holds the classes used to store instances in SQLite files, allowing them
 * to be chained among them, using a simple syntax in class declarations.
 */
namespace storage
{
    //! The file name of the SQLite database used by this class.
    std::string SQLiteWrapper::_fileName = "untitled.db";

    /*!
     * Private constructor. Since this class is a singleton, 
     * only the static method "get()" is used to build a unique
     * instance for all the application. This singleton is not
     * thread-safe, but for this application, this is more than
     * enough.
     */
    SQLiteWrapper::SQLiteWrapper()
    : _resultCode    (0)
    , _numRows       (0)
    , _numColumns    (0)
    , _lastRowId     (0)
    , _errorMsg      ("")
    , _lastQuery     ("")
    , _columnHeaders (std::vector<std::string>())
    , _data          (std::vector<std::string>())
    , _db            (0)
    {
        open();
    }

    /*!
     * Virtual destructor.
     */
    SQLiteWrapper::~SQLiteWrapper()
    {
        sqlite3_close(_db);
    }

    /*!
     * Sets the file name of the SQLite database. If no name is
     * given, the name "untitled.db" is used.
     * 
     * \param fileName A string with the file name.
     */
    void SQLiteWrapper::setFileName(const std::string& fileName)
    {
        _fileName = fileName;
    }

    /*!
     * Returns the singleton instance of this class.
     * 
     * \return A reference to the singleton instance.
     */
    SQLiteWrapper& SQLiteWrapper::get()
    {
        // Optimized Singleton instance for single-threaded applications
        // taken from http://www.inquiry.com/techtips/cpp_pro/10min/10min0200.asp
        static SQLiteWrapper _dal;
        return _dal;
    }

    /*!
     * Opens the connection to the SQLite database. Clients must
     * call this method before "executeQuery()" or they will get 
     * a runtime error.
     * 
     * \return A boolean value; true in case of success, false otherwise.
     */
    const bool SQLiteWrapper::open()
    {
        _resultCode = sqlite3_open(_fileName.c_str(), &_db);
        if(_resultCode)
        {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(_db));
            close();
        }
        else
        {
            // Enhance the performance of SQLite 3
            // http://www.sqlite.org/pragma.html
            executeQuery("PRAGMA synchronous = OFF;");
            executeQuery("PRAGMA encoding = \"UTF-8\";");
        }
        return (_resultCode == SQLITE_OK);
    }

    /*!
     * This is the heart of the class; this method takes a SQL query
     * in a std::string and sets the internal state of the class
     * to inform clients about the result of the query.
     * 
     * \param query The query to execute.
     * 
     * \return A boolean value; true in case of success, false otherwise.
     */
    const bool SQLiteWrapper::executeQuery(const std::string& query)
    {
        char* error;
        char** resultSet;
        _lastQuery.clear();
        _lastQuery.append(query);
        _resultCode = sqlite3_get_table(
            _db,            // An open database
            query.c_str(),  // SQL to be executed
            &resultSet,     // Result written to a char*[] that this points to
            &_numRows,      // Number of result rows written here
            &_numColumns,   // Number of result columns written here
            &error          // Error msg written here
        );

        if (NULL != error)
        {
            _errorMsg.clear();
            _errorMsg.append(error);
        }

        if (_columnHeaders.size() > 0)
        {
            _columnHeaders.clear();
        }
        if (_data.size() > 0)
        {
            _data.clear();
        }

        if (SQLITE_OK == _resultCode)
        {
            for (int i = 0; i < _numColumns; ++i)
            {
                _columnHeaders.push_back(resultSet[i]); // First row heading
            }

            for (int i = 0; i < _numColumns * _numRows; ++i)
            {
                // It could happen that a cell is empty!
                char* str = resultSet[_numColumns + i];
                if (str)
                {
                    _data.push_back(str);
                }
                else
                {
                    _data.push_back("");
                }
            }
        }
        _lastRowId = sqlite3_last_insert_rowid(_db);
        sqlite3_free_table(resultSet);
        return (_resultCode == SQLITE_OK);
    }

    /*!
     * Closes the connection to the SQLite database. Clients must call
     * this method when they have finished using the database file.
     * 
     * The database also is closed automatically by the destructor.
     */
    void SQLiteWrapper::close()
    {
        _resultCode = sqlite3_close(_db);
    }

    /*!
     * Returns the ID of the last element inserted or updated in the database.
     * 
     * \return A ID value (very long!)
     */
    const ID SQLiteWrapper::getLastRowId() const
    {
        return _lastRowId;
    }

    /*!
     * Returns the last result code given by SQLite upon execution
     * of the last query.
     * 
     * \return An integer value.
     */
    const int SQLiteWrapper::getLastResultCode() const
    {
        return _resultCode;
    }

    /*!
     * Returns the last query executed by this instance,
     * regardless of it being successful or not.
     * 
     * \return A string.
     */
    const std::string& SQLiteWrapper::getLastQuery() const
    {
        return _lastQuery;
    }

    /*!
     * Returns the last error message provided by SQLite.
     * 
     * \return A string.
     */
    const std::string& SQLiteWrapper::getLastErrorMsg() const
    {
        return _errorMsg;
    }

    /*!
     * Returns a const reference to a vector, holding
     * the table headers corresponding to the last resultset
     * retrieved from the database.
     * 
     * \return A vector of string.
     */
    const std::vector<std::string>& SQLiteWrapper::getTableHeaders() const
    {
        return _columnHeaders;
    }

    /*!
     * Returns a const reference to a vector holding the data
     * of the last resultset retrieved from the database.
     * 
     * \return A vector of string.
     */
    const std::vector<std::string>& SQLiteWrapper::getData() const
    {
        return _data;
    }

    /*!
     * Tests whether the table passed as parameter exists in the database.
     *
     * \param tableName The name of the table being tested.
     * 
     * \return A boolean stating whether the table exists (true) or not (false)
     */
    const bool SQLiteWrapper::tableExists(const std::string& tableName)
    {
        // This method uses the "table_info" PRAGMA command described here:
        // http://www.sqlite.org/pragma.html
        std::stringstream query;
        query << "PRAGMA table_info(\"";
        query << tableName;
        query << "\");";

        // This method does not use the "executeQuery()" method to
        // avoid modifying the internal state of the current SQLiteWrapper instance.
        char* error;
        char** resultSet;
        int numRows;
        int numColumns;
        
        sqlite3_get_table(
            _db,                  // An open database
            query.str().c_str(),  // SQL to be executed
            &resultSet,           // Result written to a char*[] that this points to
            &numRows,             // Number of result rows written here
            &numColumns,          // Number of result columns written here
            &error                // Error msg written here
        );
        return numRows > 0;
    }

    /*!
     * Returns a map with the name and type of the columns of the table
     * whose name is passed as parameter.
     * 
     * \param tableName The name of the table whose schema is sought.
     *
     * \return An std::map instance with pairs representing: [column name = column type]
     */
    const std::map<std::string, std::string> SQLiteWrapper::getTableSchema(const std::string& tableName)
    {
        // This method uses the "table_info" PRAGMA command described here:
        // http://www.sqlite.org/pragma.html
        std::stringstream query;
        query << "PRAGMA table_info(\"";
        query << tableName;
        query << "\");";

        std::map<std::string, std::string> schema;
        bool ok = executeQuery(query.str());
        if(ok)
        {
            const std::vector<std::string>& data = getData();
            const size_t numberOfHeaders = 6;
            const size_t dataItems = data.size();

            for (size_t i = 0; i < dataItems;
                             i = i + numberOfHeaders)
            {
                schema[data[i + 1]] = data[i + 2];
            }            
        }
        return schema;
    }
}
