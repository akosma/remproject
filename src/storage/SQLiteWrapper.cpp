/*!
 * \file SQLiteWrapper.cpp
 *
 * Contains the implementation of the Storage::SQLiteWrapper class.
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

/*!
 * \namespace Storage
 * Insert a description for the namespace here
 */
namespace Storage
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
    bool SQLiteWrapper::open()
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
    bool SQLiteWrapper::executeQuery(const std::string& query)
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
                _data.push_back(resultSet[_numColumns + i]);
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
     * \return A long long value (very long!)
     */
    const long long SQLiteWrapper::getLastRowId() const
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
}
