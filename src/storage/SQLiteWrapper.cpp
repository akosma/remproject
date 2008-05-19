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

//! Contains the implementation of the storage::SQLiteWrapper class.
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

namespace storage
{
    std::string SQLiteWrapper::_fileName = "untitled.db";

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

    SQLiteWrapper::~SQLiteWrapper()
    {
        sqlite3_close(_db);
    }

    void SQLiteWrapper::setFileName(const std::string& fileName)
    {
        _fileName = fileName;
    }

    SQLiteWrapper& SQLiteWrapper::get()
    {
        // Optimized Singleton instance for single-threaded applications
        // taken from http://www.inquiry.com/techtips/cpp_pro/10min/10min0200.asp
        static SQLiteWrapper _dal;
        return _dal;
    }

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

    void SQLiteWrapper::close()
    {
        _resultCode = sqlite3_close(_db);
    }

    const ID SQLiteWrapper::getLastRowId() const
    {
        return _lastRowId;
    }

    const int SQLiteWrapper::getLastResultCode() const
    {
        return _resultCode;
    }

    const std::string& SQLiteWrapper::getLastQuery() const
    {
        return _lastQuery;
    }

    const std::string& SQLiteWrapper::getLastErrorMsg() const
    {
        return _errorMsg;
    }

    const std::vector<std::string>& SQLiteWrapper::getTableHeaders() const
    {
        return _columnHeaders;
    }

    const std::vector<std::string>& SQLiteWrapper::getData() const
    {
        return _data;
    }

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
