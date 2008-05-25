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

//! Contains the interface of the storage::SQLiteWrapper class.
/*!
 * \file SQLiteWrapper.h
 *
 * Contains the interface of the storage::SQLiteWrapper class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/23/08
 */

#ifndef SQLITEWRAPPER_H_
#define SQLITEWRAPPER_H_

#include <string>
#include <vector>
#include <map>
#include <sqlite3.h>

#ifndef SINGLETON_H_
#include "../utility/Singleton.h"
#endif

using utility::Singleton;

//! Framework for storing instances in SQLite files.
/*!
 * \namespace storage
 * Holds the classes used to store instances in SQLite files, allowing them
 * to be chained among them, using a simple syntax in class declarations.
 */
namespace storage
{
    //! Represents the ID stored in the database for each ActiveRecord instance.
    typedef long long ID;

    //! Provides the default value given to new instances.
    /*!
     * Provides the default value given to new instances.
     * 
     * \li New instances (those that have not yet been saved in database
     * \li Instances that failed to be saved in the database.
     */
    const ID DEFAULT_ID = -1;

    //! Proxy class used to access SQLite databases.
    /*!
     * \class SQLiteWrapper
     * Proxy class used to access the SQLite database where all the information
     * about diagrams and projects is stored. This class is a wrapper
     * around the SQLite API, adapted from 
     * http://souptonuts.sourceforge.net/code/simplesqlite3cpp2.cc.html
     * and it is also a Singleton, which clients can retrieve calling
     * the "get()" static method.
     * This class is also adapted and extended from the one used 
     * in the "BirthdayCard" project by Adrian Kosmaczewski
     * http://kosmaczewski.net/projects/birthdaycard/
     */
    class SQLiteWrapper : public Singleton<SQLiteWrapper>
    {
    public:

        //! SQLiteWrapper virtual destructor.
        /*!
         *  SQLiteWrapper virtual destructor.
         */
        virtual ~SQLiteWrapper();

        //! Sets the file name of the SQLite database.
        /*!
         * Sets the file name of the SQLite database. If no name is
         * given, the "untitled.db" name is used.
         * 
         * \param fileName A string with the file name.
         */
        static void setFileName(const std::string&);

        //! Opens the connection to the SQLite database.
        /*!
         * Opens the connection to the SQLite database. Clients must
         * call this method before "executeQuery()" or they will get 
         * a runtime error.
         * 
         * \return A boolean value; true in case of success, false otherwise.
         */
        const bool open();

        //! Executes the query passed as parameter.
        /*!
         * This is the heart of the class; this method takes a SQL query
         * in a std::string and sets the internal state of the class
         * to inform clients about the result of the query.
         * 
         * \param query The query to execute.
         * 
         * \return A boolean value; true in case of success, false otherwise.
         */
        const bool executeQuery(const std::string&);

        //! Closes the connection to the SQLite database.
        /*!
         * Closes the connection to the SQLite database. Clients must call
         * this method when they have finished using the database file.
         * 
         * The database also is closed automatically by the destructor.
         */
        void close();

        //! Returns the ID of the last element inserted or updated in the database.
        /*!
         * Returns the ID of the last element inserted or updated in the database.
         * 
         * \return A long long value (very long!)
         */
        const ID getLastRowId() const;

        //! Returns the last result code given by SQLite upon execution of the last query.
        /*!
         * Returns the last result code given by SQLite upon execution of the last query.
         * 
         * \return An integer value.
         */
        const int getLastResultCode() const;

        //! Returns the last query executed by this instance.
        /*!
         * Returns the last query executed by this instance,
         * regardless of it being successful or not.
         * 
         * \return A string.
         */
        const std::string& getLastQuery() const;

        //! Returns the last error message provided by SQLite.
        /*!
         * Returns the last error message provided by SQLite.
         * 
         * \return A string.
         */
        const std::string& getLastErrorMsg() const;

        //! Returns the headers of the last resultset.
        /*!
         * Returns a const reference to a vector, holding
         * the table headers corresponding to the last resultset
         * retrieved from the database.
         * 
         * \return A vector of string.
         */
        const std::vector<std::string>& getTableHeaders() const;

        //! Returns the data retrieved by the last query.
        /*!
         * Returns a const reference to a vector holding the data
         * of the last resultset retrieved from the database.
         * 
         * \return A vector of string.
         */
        const std::vector<std::string>& getData() const;
        
        //! Tests whether the table passed as parameter exists in the database.
        /*!
         * Tests whether the table passed as parameter exists in the database.
         *
         * \param tableName The name of the table being tested.
         * 
         * \return A boolean stating whether the table exists (true) or not (false)
         */
        const bool tableExists(const std::string&);
        
        //! Returns the column names of the table passed as parameter.
        /*!
         * Returns a map with the name and type of the columns of the table
         * whose name is passed as parameter.
         * 
         * \param tableName The name of the table whose schema is sought.
         *
         * \return An std::map instance with pairs representing: [column name = column type]
         */
        const std::map<std::string, std::string> getTableSchema(const std::string&);

    private:
        //! Private constructor.
        /*!
         * Private constructor.
         */
        SQLiteWrapper();

        //! Allow the Singleton template class to access the private constructor.
        friend SQLiteWrapper& Singleton<SQLiteWrapper>::get();

    private:

        //! The file name of the SQLite database used by this class.
        static std::string _fileName;

    private:

        //! The result code of the last query executed on the database
        int _resultCode;

        //! The number of rows returned by the last query.
        int _numRows;

        //! The number of columns returned by the last query.
        int _numColumns;

        //! The ID of the last element inserted or updated in the database.
        ID _lastRowId;

        //! An error message returned by SQLite.
        std::string _errorMsg;

        //! The last query executed.
        std::string _lastQuery;

        //! A vector containing the headers of the last resultset.
        std::vector<std::string> _columnHeaders;

        //! A vector containing the data retrieved from the database.
        std::vector<std::string> _data;

        //! A variable representing the SQLite database itself.
        sqlite3* _db;
    };
}

#endif /* SQLITEWRAPPER_H_ */
