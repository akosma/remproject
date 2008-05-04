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

/*!
 * \namespace storage
 * Holds the classes used to store instances in SQLite files, allowing them
 * to be chained among them, using a simple syntax in class declarations.
 */
namespace storage
{
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
    class SQLiteWrapper
    {
    public:

        /*!
         *  SQLiteWrapper virtual destructor.
         */
        virtual ~SQLiteWrapper();

        /*!
         * Sets the file name of the SQLite database. If no name is
         * given, the "untitled.db" name is used.
         * 
         * \param fileName A string with the file name.
         */
        static void setFileName(const std::string& fileName);

        /*!
         * Returns the singleton instance of this class.
         * 
         * \return A reference to the singleton instance.
         */
        static SQLiteWrapper& get();

        /*!
         * Opens the connection to the SQLite database. Clients must
         * call this method before "executeQuery()" or they will get 
         * a runtime error.
         * 
         * \return A boolean value; true in case of success, false otherwise.
         */
        bool open();

        /*!
         * This is the heart of the class; this method takes a SQL query
         * in a std::string and sets the internal state of the class
         * to inform clients about the result of the query.
         * 
         * \param query The query to execute.
         * 
         * \return A boolean value; true in case of success, false otherwise.
         */
        bool executeQuery(const std::string& query);

        /*!
         * Closes the connection to the SQLite database. Clients must call
         * this method when they have finished using the database file.
         * 
         * The database also is closed automatically by the destructor.
         */
        void close();

        /*!
         * Returns the ID of the last element inserted or updated in the database.
         * 
         * \return A long long value (very long!)
         */
        const long long getLastRowId() const;

        /*!
         * Returns the last result code given by SQLite upon execution
         * of the last query.
         * 
         * \return An integer value.
         */
        const int getLastResultCode() const;

        /*!
         * Returns the last query executed by this instance,
         * regardless of it being successful or not.
         * 
         * \return A string.
         */
        const std::string& getLastQuery() const;

        /*!
         * Returns the last error message provided by SQLite.
         * 
         * \return A string.
         */
        const std::string& getLastErrorMsg() const;

        /*!
         * Returns a const reference to a vector, holding
         * the table headers corresponding to the last resultset
         * retrieved from the database.
         * 
         * \return A vector of string.
         */
        const std::vector<std::string>& getTableHeaders() const;

        /*!
         * Returns a const reference to a vector holding the data
         * of the last resultset retrieved from the database.
         * 
         * \return A vector of string.
         */
        const std::vector<std::string>& getData() const;
        
        const bool tableExists(const std::string&);
        
        std::map<std::string, std::string> getTableSchema(const std::string&);

    private:

        /*!
         * Private constructor. Since this class is a singleton, 
         * only the static method "get()" is used to build a unique
         * instance for all the application. This singleton is not
         * thread-safe, but for this application, this is more than
         * enough.
         */
        SQLiteWrapper();

        /*!
         * Private copy constructor.
         * 
         * This trick comes from "Effective C++, Third Edition"
         * by Scott Meyers (ISBN 0-321-33487-6)
         * "Item 6: Explicitly disallow the use of compiler-generated
         * functions you do not want", page 37
         * 
         * \param rhs The SQLiteWrapper reference to copy from.
         */
        SQLiteWrapper(const SQLiteWrapper& rhs);

        /*!
         * Private assignment operator.
         * 
         * This trick comes from "Effective C++, Third Edition"
         * by Scott Meyers (ISBN 0-321-33487-6)
         * "Item 6: Explicitly disallow the use of compiler-generated
         * functions you do not want", page 37
         * 
         * \param rhs The SQLiteWrapper reference to copy from.
         * 
         * \return A reference to the current SQLiteWrapper.
         */
        SQLiteWrapper& operator=(const SQLiteWrapper& rhs);

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
        long long _lastRowId;

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
