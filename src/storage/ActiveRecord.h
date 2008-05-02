/*!
 * \file ActiveRecord.h
 *
 * Contains the interface of the storage::ActiveRecord class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/17/08
 */

#ifndef ACTIVERECORD_H_
#define ACTIVERECORD_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>

#include <Poco/DateTime.h>

#ifndef SQLITEWRAPPER_H_
#include "SQLiteWrapper.h"
#endif

#ifndef ANYPROPERTYMAP_H_
#include "AnyPropertyMap.h"
#endif

/*!
 * \namespace storage
 * Insert a description for the namespace here
 */
namespace storage
{
    //! Represents the ID stored in the database for each ActiveRecord instance.
    typedef long long ID;

    /*!
     * Provides the default value given to
     * 
     * \li New instances (those that have not yet been saved in database
     * \li Instances that failed to be saved in the database.
     */
    const ID DEFAULT_ID = -1;

    class NoParent
    {
    public:
        NoParent() : _parentColumn("no_parent") {}
        virtual ~NoParent() {}
        const std::string& getParentColumn() const { return _parentColumn; }
        static std::string& getTableName()
        { 
            static std::string tableName("no_parent");
            return tableName; 
        }
        const ID getId() const
        {
            return DEFAULT_ID;
        }
        const ID getParentId() const
        {
            return DEFAULT_ID;
        }
    private:
        std::string _parentColumn;
    };

    class NoChildren
    {
    public:
        NoChildren() {}
        virtual ~NoChildren() {}
        void save() {}
        void saveChildren() {}
        void destroy() {}
    };
    
    /*!
     * \class ActiveRecord
     *
     *  
     */
    template <class T
             , class P = NoParent
             , class C = NoChildren>
    class ActiveRecord : public P
                       , public C
    {
    public:

        /*!
         * Default constructor. Sets the ID to DEFAULT_ID. Used
         * to create instances that do not exist yet in the database.
         */
        ActiveRecord(std::string);
        
        /*!
         * Constructor. Used to create instances whose state is
         * already present in the database.
         */
        ActiveRecord(std::string&, ID, AnyPropertyMap&);
        
        /*!
         * Copy constructor.
         * 
         * \param rhs The instance to copy from ("right hand side").
         */
        ActiveRecord(const ActiveRecord& rhs);

        /*!
         *  ActiveRecord virtual destructor.
         */
        virtual ~ActiveRecord();

        /*!
         * Assignment operator.
         * 
         * \param rhs The instance to copy from ("right hand side").
         */
        ActiveRecord& operator=(const ActiveRecord& rhs);

        /*!
         * Returns a value indicating if the current instance has been
         * modified since it was retrieved from the database.
         * 
         * \return A boolean value.
         */
        const bool isDirty() const;
        
        /*!
         * Returns a value indicating whether the current instance
         * exists in the database or not.
         * 
         * \return A boolean value.
         */
        const bool isNew() const;
        
        /*!
         * Returns the ID of the current instance.
         * 
         * \return An ID (long long) value.
         */
        const ID getId() const;
        void setName(std::string&);
        std::string getName();

        /*!
         * This method is the core of the ActiveRecord family of
         * classes. Clients use it to write the current state of
         * the instance into the database.
         * 
         * This is a "template method", that provides the basic 
         * framework for subclasses, that must provide an implementation
         * to "insert()" and "update()". 
         */
        void save();
        
        void destroy();
        static void removeAll();
        static void remove(const ID id);

        static std::vector<T>* findAll();
        static std::vector<T>* findByCondition(const storage::AnyPropertyMap&);
        static T* findById(const ID id);

        void setString(const std::string&, const std::string&);
        void setInteger(const std::string&, const int);
        void setBoolean(const std::string&, const bool);
        void setDouble(const std::string&, const double);
        void setDateTime(const std::string&, const Poco::DateTime&);

        const std::string getString(const std::string&);
        const int getInteger(const std::string&);
        const bool getBoolean(const std::string&);
        const double getDouble(const std::string&);
        const Poco::DateTime getDateTime(const std::string&);
        
        const Poco::DateTime getCreationDateTime();
        const Poco::DateTime getLastModificationDateTime();

        /*!
         * Used to change the "_isDirty" flag in the 
         * ActiveRecord base class; subclasses must call this method in
         * every "setter" method.
         */
        void setDirty();

    protected:

        void addStringProperty(const std::string&);
        void addIntegerProperty(const std::string&);
        void addBooleanProperty(const std::string&);
        void addDoubleProperty(const std::string&);
        void addDateTimeProperty(const std::string&);

    private:
        /*!
         * Used to store the state in the database for the first time, using the
         * "INSERT" SQL statement.
         * 
         * \return The ID of the current instance, as provided by SQLite.
         */
        const ID insert();

        /*!
         * Used to store the state in the database afterwards, using the
         * "UPDATE" SQL statement.
         */
        void update();

    private:
        static std::vector<storage::AnyPropertyMap>* getPropertyMaps(std::map<std::string, std::string>&);
        static std::vector<T>* getVectorByQuery(std::string&);

    private:

        //! The ID of the current instance.
        ID _id;
    
        //! A flag indicating whether this instance exists in database or not.
        bool _isNew;
    
        //! A flag indicating whether this instance has been modified or not.
        bool _isDirty;
        
        //! An instance of AnyPropertyMap which contains the data for this instance
        AnyPropertyMap _data;

        std::string _className;
    };
    
    /*!
     * Default constructor. Sets the ID to DEFAULT_ID. Used
     * to create instances that do not exist yet in the database.
     */
    template <class T, class P, class C>
    ActiveRecord<T, P, C>::ActiveRecord(std::string className)
    : P()
    , C()
    , _id        (DEFAULT_ID)
    , _isNew     (true)
    , _isDirty   (true)
    , _data      ()
    , _className (className)
    {
    }

    /*!
     * Constructor. Used to create instances whose state is
     * already present in the database.
     */
    template <class T, class P, class C>
    ActiveRecord<T, P, C>::ActiveRecord(std::string& className, ID id, AnyPropertyMap& data)
    : P()
    , C()
    , _id        (id)
    , _isNew     (false)
    , _isDirty   (false)
    , _data      (data)
    , _className (className)
    {
    }

    /*!
     * Copy constructor.
     * 
     * \param rhs The instance to copy from ("right hand side").
     */
    template <class T, class P, class C>
    ActiveRecord<T, P, C>::ActiveRecord(const ActiveRecord& rhs)
    : P(rhs)
    , C(rhs)
    , _id        (rhs._id)
    , _isNew     (rhs._isNew)
    , _isDirty   (rhs._isDirty)
    , _data      (rhs._data)
    , _className (rhs._className)
    {
    }

    /*!
     * Virtual destructor.
     */
    template <class T, class P, class C>
    ActiveRecord<T, P, C>::~ActiveRecord()
    {
    }

    /*!
     * Assignment operator.
     * 
     * \param rhs The instance to copy from ("right hand side").
     */
    template <class T, class P, class C>
    ActiveRecord<T, P, C>& ActiveRecord<T, P, C>::operator=(const ActiveRecord& rhs)
    {
        if (this != &rhs)
        {
            P::operator=(rhs);
            C::operator=(rhs);
            
            _id = rhs._id;
            _isDirty = rhs._isDirty;
            _isNew = rhs._isNew;
            _className = rhs._className;
            _data = rhs._data;
        }
        return *this;
    }
    
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::setString(const std::string& key, const std::string& value)
    {
        setDirty();
        _data.setString(key, value);
    }

    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::setInteger(const std::string& key, const int value)
    {
        setDirty();
        _data.setInteger(key, value);
    }

    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::setBoolean(const std::string& key, const bool value)
    {
        setDirty();
        _data.setBoolean(key, value);
    }

    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::setDouble(const std::string& key, const double value)
    {
        setDirty();
        _data.setDouble(key, value);
    }
    
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::setDateTime(const std::string& key, const Poco::DateTime& value)
    {
        setDirty();
        _data.setDateTime(key, value);
    }
    
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::addStringProperty(const std::string& key)
    {
        if (!_data.hasProperty(key))
        {
            _data.setString(key, "");
        }
    }

    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::addIntegerProperty(const std::string& key)
    {
        if (!_data.hasProperty(key))
        {
            _data.setInteger(key, 0);
        }
    }

    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::addBooleanProperty(const std::string& key)
    {
        if (!_data.hasProperty(key))
        {
            _data.setBoolean(key, false);
        }
    }

    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::addDoubleProperty(const std::string& key)
    {
        if (!_data.hasProperty(key))
        {
            _data.setDouble(key, 0.0);
        }
    }
    
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::addDateTimeProperty(const std::string& key)
    {
        if (!_data.hasProperty(key))
        {
            Poco::DateTime now;
            _data.setDateTime(key, now);
        }
    }
    
    template <class T, class P, class C>
    const std::string ActiveRecord<T, P, C>::getString(const std::string& key)
    {
        return _data.getString(key);
    }
    
    template <class T, class P, class C>
    const int ActiveRecord<T, P, C>::getInteger(const std::string& key)
    {
        return _data.getInteger(key);
    }
    
    template <class T, class P, class C>
    const bool ActiveRecord<T, P, C>::getBoolean(const std::string& key)
    {
        return _data.getBoolean(key);
    }
    
    template <class T, class P, class C>
    const double ActiveRecord<T, P, C>::getDouble(const std::string& key)
    {
        return _data.getDouble(key);
    }
    
    template <class T, class P, class C>
    const Poco::DateTime ActiveRecord<T, P, C>::getDateTime(const std::string& key)
    {
        return _data.getDateTime(key);
    }
    
    template <class T, class P, class C>
    const Poco::DateTime ActiveRecord<T, P, C>::getCreationDateTime()
    {
        return _data.getDateTime("created_on");
    }
    
    template <class T, class P, class C>
    const Poco::DateTime ActiveRecord<T, P, C>::getLastModificationDateTime()
    {
        return _data.getDateTime("updated_on");
    }

    /*!
     * This method is the core of the ActiveRecord family of
     * classes. Clients use it to write the current state of
     * the instance into the database.
     * 
     * This is a "template method", that provides the basic 
     * framework for subclasses, that must provide an implementation
     * to "insert()" and "update()". 
     */
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::save()
    {
        ID parentId = P::getParentId();
        if (parentId != DEFAULT_ID)
        {
            setInteger(P::getParentColumn(), parentId);
        }
        if (_isNew)
        {
            _id = insert();
            if (_id != DEFAULT_ID)
            {
                _isNew = false;
                _isDirty = false;
            }
        }
        else
        {
            update();
            _isDirty = false;
        }        
        C::saveChildren();
    }
        
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::update()
    {
        SQLiteWrapper& wrapper = SQLiteWrapper::get();
        bool ok = wrapper.open();
        if (ok)
        {
            Poco::DateTime now;
            setDateTime("updated_on", now);
            ok = wrapper.executeQuery(_data.getStringForUpdate(T::getTableName(), _id));
        }
        wrapper.close();
    }
    
    template <class T, class P, class C>
    const ID ActiveRecord<T, P, C>::insert()
    {
        SQLiteWrapper& wrapper = SQLiteWrapper::get();
        bool ok = wrapper.open();
        if (!wrapper.tableExists(T::getTableName()))
        {
            addIntegerProperty(P::getParentColumn());
            addDateTimeProperty("created_on");
            addDateTimeProperty("updated_on");
            _data.createPrimaryKey("id");
            ok = wrapper.executeQuery(_data.getStringForCreateTable(T::getTableName()));
        }
        if (ok)
        {
            setString("class", _className);
            Poco::DateTime now;
            setDateTime("created_on", now);
            setDateTime("updated_on", now);
            ok = wrapper.executeQuery(_data.getStringForInsert(T::getTableName()));
        }
        wrapper.close();
        if (ok)
        {
            return wrapper.getLastRowId();            
        }
        else
        {
            return DEFAULT_ID;
        }
    }

    /*!
     * Returns a value indicating if the current instance has been
     * modified since it was retrieved from the database.
     * 
     * \return A boolean value.
     */
    template <class T, class P, class C>
    const bool ActiveRecord<T, P, C>::isDirty() const
    {
        return _isDirty;
    }

    /*!
     * Returns a value indicating whether the current instance
     * exists in the database or not.
     * 
     * \return A boolean value.
     */
    template <class T, class P, class C>
    const bool ActiveRecord<T, P, C>::isNew() const
    {
        return _isNew;
    }

    /*!
     * Returns the ID of the current instance.
     * 
     * \return A ActiveRecordId (long long) value.
     */
    template <class T, class P, class C>
    const ID ActiveRecord<T, P, C>::getId() const
    {
        return _id;
    }
    
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::setName(std::string& name)
    {
        setString("name", name);
    }

    template <class T, class P, class C>
    std::string ActiveRecord<T, P, C>::getName()
    {
        return getString("name");
    }    

    /*!
     * Used by subclasses to change the "_isDirty" flag in the 
     * ActiveRecord base class; subclasses must call this method in
     * every "setter" method.
     */
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::setDirty()
    {
        _isDirty = true;
    }
    
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::destroy()
    {
        if (_id != DEFAULT_ID)
        {
            ActiveRecord<T, P, C>::remove(_id);
            _isDirty = true;
            _isNew = true;
        }
    }

    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::remove(const ID id)
    {
        std::stringstream query;
        query << "DELETE FROM ";
        query << T::getTableName();
        query << " WHERE id = ";
        query << id;
        query << ";";
        
        SQLiteWrapper& wrapper = SQLiteWrapper::get();
        bool ok = wrapper.open();
        if (ok)
        {
            ok = wrapper.executeQuery(query.str());
            wrapper.close();
        }
    }
    
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::removeAll()
    {
        std::stringstream query;
        query << "DELETE FROM ";
        query << T::getTableName();
        query << ";";
        
        SQLiteWrapper& wrapper = SQLiteWrapper::get();
        bool ok = wrapper.open();
        if (ok)
        {
            ok = wrapper.executeQuery(query.str());
            wrapper.close();
        }
    }
    
    /*!
     * Static factory method that returns the instance of the
     * class that corresponds to the ID passed in parameter.
     * Clients should assert or verify that the instance has been
     * retrieved successfully before operating on it.
     *
     * \param id The ID of the instance sought.
     *
     * \return A pointer to an instance, or NULL.
     */
    template <class T, class P, class C>
    T* ActiveRecord<T, P, C>::findById(const ID id)
    {
        std::stringstream query;
        query << "SELECT * FROM ";
        query << T::getTableName();
        query << " WHERE id = ";
        query << id;
        query << ";";
        
        T* item = NULL;
        SQLiteWrapper& wrapper = SQLiteWrapper::get();
        bool ok = wrapper.open();
        if (ok)
        {
            std::map<std::string, std::string> schema = wrapper.getTableSchema(T::getTableName());
            ok = wrapper.executeQuery(query.str());
            wrapper.close();
            if (ok)
            {
                std::vector<storage::AnyPropertyMap>* maps = getPropertyMaps(schema);
                std::vector<storage::AnyPropertyMap>::iterator iter;
                for (iter = maps->begin(); iter != maps->end(); ++iter)
                {
                    std::string className = iter->getString("class");
                    ID currentId = iter->getInteger("id");
                    item = new T(className, currentId, *iter);
                }
                delete maps;
            }
        }
        return item;
    }

    /*!
     * Static factory method that returns all the instances that 
     * exist in the database.
     *
     * \return A vector of instances.
     */
    template <class T, class P, class C>
    std::vector<T>* ActiveRecord<T, P, C>::findAll()
    {
        std::stringstream query;
        query << "SELECT * FROM ";
        query << T::getTableName();
        query << ";";
        
        std::string q = query.str();
        return getVectorByQuery(q);
    }
    
    template <class T, class P, class C>
    std::vector<T>* ActiveRecord<T, P, C>::findByCondition(const storage::AnyPropertyMap& conditions)
    {
        std::stringstream query;
        query << "SELECT * FROM ";
        query << T::getTableName();
        query << " WHERE ";
        query << conditions.getStringForWhere();
        query << ";";
        
        std::string q = query.str();
        return getVectorByQuery(q);
    }
    
    template <class T, class P, class C>
    std::vector<storage::AnyPropertyMap>* ActiveRecord<T, P, C>::getPropertyMaps(std::map<std::string, std::string>& schema)
    {
        SQLiteWrapper& wrapper = SQLiteWrapper::get();
        std::vector<storage::AnyPropertyMap>* maps = new std::vector<storage::AnyPropertyMap>();
        const std::vector<std::string>& data = wrapper.getData();
        const size_t numberOfHeaders = wrapper.getTableHeaders().size();
        const size_t dataItems = data.size();
        const std::vector<std::string>& headers = wrapper.getTableHeaders();

        for (size_t i = 0; i < dataItems;
                         i = i + numberOfHeaders)
        {
            AnyPropertyMap instanceData;
            for (int j = 0; j < numberOfHeaders; ++j)
            {
                const std::string& currentHeader = headers[j];
                std::string& currentDataType = schema[currentHeader];
                const std::string& currentValue = data[i + j];
                
                if(currentDataType == "TEXT")
                {
                    instanceData.setString(currentHeader, currentValue);
                }
                else if (currentDataType == "INTEGER")
                {
                    instanceData.setInteger(currentHeader, atoi(currentValue.c_str()));
                }
                else if (currentDataType == "BOOLEAN")
                {
                    instanceData.setBoolean(currentHeader, atoi(currentValue.c_str()));
                }
                else if (currentDataType == "REAL")
                {
                    instanceData.setDouble(currentHeader, atof(currentValue.c_str()));
                }
                else if (currentDataType == "DATETIME")
                {
                    // We have to use the "long long atoll(const*)" function to 
                    // cast the string value coming from the DB layer into an int64 value,
                    // that is used to create a Timestamp, used to create a proper DateTime instance.
                    long long num = atoll(currentValue.c_str());
                    Poco::DateTime date(Poco::Timestamp::fromUtcTime(num));
                    instanceData.setDateTime(currentHeader, date);
                }
            }
            maps->push_back(instanceData);
        }
        return maps;
    }
    
    template <class T, class P, class C>
    std::vector<T>* ActiveRecord<T, P, C>::getVectorByQuery(std::string& query)
    {
        std::vector<T>* items = new std::vector<T>;
        SQLiteWrapper& wrapper = SQLiteWrapper::get();
        bool ok = wrapper.open();
        if (ok)
        {
            std::map<std::string, std::string> schema = wrapper.getTableSchema(T::getTableName());
            ok = wrapper.executeQuery(query);
            if (ok)
            {
                std::vector<storage::AnyPropertyMap>* maps = getPropertyMaps(schema);
                std::vector<storage::AnyPropertyMap>::iterator iter;
                for (iter = maps->begin(); iter != maps->end(); ++iter)
                {
                    std::string className = iter->getString("class");
                    ID currentId = iter->getInteger("id");
                    T item(className, currentId, *iter);
                    items->push_back(item);
                }
                delete maps;
            }
            wrapper.close();
        }
        return items;        
    }
}

#endif /* ACTIVERECORD_H_ */
