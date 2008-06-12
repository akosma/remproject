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

//! Contains the interface and implementation of the storage::ActiveRecord template class.
/*!
 * \file ActiveRecord.h
 *
 * Contains the interface and implementation of the storage::ActiveRecord template class.
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
#include <sstream>

#include <Poco/DateTime.h>

#ifndef SQLITEWRAPPER_H_
#include "SQLiteWrapper.h"
#endif

#ifndef ANYPROPERTYMAP_H_
#include "AnyPropertyMap.h"
#endif

#ifndef FINDCONDITIONS_H_
#include "FindConditions.h"
#endif

#ifndef PERSISTABLE_H_
#include "Persistable.h"
#endif

using storage::AnyPropertyMap;
using Poco::DateTime;
using Poco::Timestamp;
using std::string;
using std::vector;
using std::map;
using std::stringstream;

//! Framework for storing instances in SQLite files.
/*!
 * \namespace storage
 * Holds the classes used to store instances in SQLite files, allowing them
 * to be chained among them, using a simple syntax in class declarations.
 */
namespace storage
{
    //! Base class for all objects stored in SQLite files.
    /*!
     * \class ActiveRecord
     *
     * Base template class for all objects that can be saved into a SQLite file.
     * Its design is heavily inspired by the classes of the same name in the
     * Ruby on Rails web development framework:
     * http://rubyonrails.org/
     */
    template <class T>
    class ActiveRecord : public virtual Persistable
    {
    public:
        
        //! \name Constructors, Destructor and Assignment Operator
        //@{
        
        //! Default constructor
        /*!
         * Default constructor. Sets the ID to DEFAULT_ID. Used
         * to create instances that do not exist yet in the database.
         * 
         * \param className The subclass name of the current instance.
         */
        ActiveRecord(const string&);
        
        //! Constructor used for instances retrieved from the database
        /*!
         * Constructor. Used to create instances already existing in the database.
         * This constructor is called by the ActiveRecord::getVectorByQuery() method.
         * 
         * \param data An AnyPropertyMap containing the internal state of the instance
         */
        ActiveRecord(AnyPropertyMap&);
        
        //! Copy constructor.
        /*!
         * Copy constructor.
         * 
         * \param rhs The instance to copy data from.
         */
        ActiveRecord(const ActiveRecord&);

        //! Virtual destructor.
        /*!
         * Virtual destructor.
         */
        virtual ~ActiveRecord();

        //! Assignment operator.
        /*!
         * Assignment operator.
         * 
         * \param rhs The instance to copy from ("right hand side").
         */
        ActiveRecord& operator=(const ActiveRecord&);

        //@}

        //! \name Dynamic Object Public Methods
        //@{

        //! Set a property.
        /*!
         * Sets the value of the property whose name is the first parameter.
         * 
         * \param key The name of the property to set
         * \param value The value of the property to set
         */
        template <class U>
        void set(const string&, const U&);
        
        //! Get a property.
        /*!
         * Returns the value of the property whose name is passed as parameter.
         * 
         * \param key The name of the property to get
         * 
         * \return The current value of the named property
         */
        template <class U>
        const U& get(const string&);

        //@}

        //! \name Database Related Instance Methods
        //@{

        //! States whether the current instance should be saved.
        /*!
         * Returns a value indicating if the current instance has been
         * modified since it was retrieved from the database.
         * 
         * \return A boolean value.
         */
        const bool isDirty() const;
        
        //! States whether the current instance exists only in memory.
        /*!
         * Returns a value indicating whether the current instance
         * exists in the database or not.
         * 
         * \return A boolean value stating whether the current instance 
         * exists in the database (false) or not (true).
         */
        virtual const bool isNew() const;
        
        //! Gets the ID of the current instance.
        /*!
         * Returns the ID of the current instance.
         * 
         * \return An ID (long long) value.
         */
        virtual const ID getId() const;
        
        //! Sets the name of the current instance.
        /*!
         * Sets the name of the current instance, replacing any previous value.
         * 
         * \param name The name of the current instance.
         */
        void setName(const string&);
        
        //! Returns the name of the current instance.
        /*!
         * Returns the name of the current instance.
         *
         * \return A reference to a string with the name of the current instance.
         */
        const string& getName();
        
        //! Returns the moment of creation of the current instance.
        /*!
         * Returns the moment of creation of the current instance.
         *
         * \return A DateTime instance.
         */
        const DateTime& getCreationDateTime();

        //! Returns the moment of the last modification of the current instance.
        /*!
         * Returns the moment of the last modification of the current instance.
         *
         * \return A DateTime instance.
         */
        const DateTime& getLastModificationDateTime();

        //! Saves (inserts or updates) the current instance to disk.
        /*!
         * This method is the core of the ActiveRecord family of
         * classes. Clients use it to write the current state of
         * the instance into the database.
         */
        virtual void save();
        
        //! Deletes the current instance from disk.
        /*!
         * Deletes the current instance from disk. It does not deletes
         * the object from memory though.
         */
        virtual void destroy();

        //! Changes the "_isDirty" flag of the current instance.
        /*!
         * Used to change the "_isDirty" flag in the 
         * ActiveRecord base class; subclasses must call this method in
         * every "setter" method.
         */
        virtual void setDirty();

        //@}

        //! \name Database Related Class Methods
        //@{

    public:
        //! Deletes all the objects from disk.
        /*!
         * Deletes all the objects from disk, without loading them from disk first.
         */
        static void removeAll();

        //! Deletes from disk the object whose ID is passed as parameter.
        /*!
         * Deletes from disk the object whose ID is passed as parameter
         * without loading it from disk first.
         *
         * \param id The ID of the object to be deleted.
         */
        static void remove(const ID);

        //! Retrieves all objects from disk.
        /*!
         * Retrieves all objects from disk. Callers to this method are responsible
         * of disposing of the resulting pointer, or a leak may occur.
         *
         * \return A pointer to a vector of the specified type.
         */
        static vector<T>* findAll();

        //! Retrieves all objects from disk satisfying some conditions.
        /*!
         * Retrieves all objects from disk satisfying some conditions. 
         * Callers to this method are responsible of disposing of the
         * resulting pointer, or a leak may occur.
         *
         * \param conditions A map of properties specifying "WHERE" conditions
         * concatenated by "AND" boolean operators.
         *
         * \return A pointer to a vector of the specified type.
         */
        static vector<T>* findByCondition(const FindConditions&);
        
        //! Retrieves the object whose ID is passed as parameter.
        /*!
         * Retrieves the object whose ID is passed as parameter, or NULL.
         * Callers are responsible of disposing of the resulting object.
         *
         * \param id The ID of the requested object.
         *
         * \return A pointer to the requested object.
         */
        static T* findById(const ID);

        //@}

        //! \name Dynamic Object Protected Methods
        //@{

    protected:
        //! Adds a property to the current instance.
        /*!
         * Adds a property to the current instance.
         * 
         * \param key The name of the property to add.
         */
        template <class U>
        void addProperty(const string&);

        //@}

        //! \name Private Instance Methods
        //@{

    private:
        //! Called by "save()" on objects that do not exist yet in the database.
        /*!
         * Called by "save()" on objects that do not exist yet in the database.
         * If required, this method will create the database tables for the object.
         *
         * \return The ID of the instance that has been inserted, or DEFAULT_ID 
         * if the instance could not be inserted propertly.
         */
        void insert();

        //! Called by "save()" on objects that already exist on the database.
        /*!
         * Called by "save()" on objects that already exist on the database.
         */
        void update();
        
        //! Sets the ID of the parent object, if any.
        /*!
         * Sets the ID of the parent object, if any. This is called
         * right before saving the object to disk.
         */
        void setParentId(const ID value);
        
        //! Called whenever the current instance is updated.
        /*!
         * Called whenever the current instance is updated.
         */
        void setLastModificationDateTimeToNow();

        //! Called when the instance is first saved to disk.
        /*!
         * Called when the instance is first saved to disk.
         */
        void setCreationDateTimeToNow();

        //@}

        //! \name Private Class Methods
        //@{

    private:
        //! Casts the result of the SQLite query into the columns required by the current instance.
        /*!
         * Casts the result of the SQLite query into the columns 
         * required by the current instance. Used internally when retrieving items from disk.
         * This method assumes that the SQLiteWrapper has not changed since the last query.
         * 
         * \param schema A map of strings representing the schema of the table
         * corresponding to the current class.
         * 
         * \return A vector of property maps.
         */
        static vector<AnyPropertyMap>* getPropertyMaps(map<string, string>&);
        
        //! Returns a vector of instances as requested by the input query.
        /*!
         * Returns a vector of instances as requested by the input query.
         * Called by "findAll()" and "findByCondition()". The callers delegate
         * to their own callers the responsibility of deleting this pointer.
         * 
         * \param query The query to use on the database.
         *
         * \return A pointer to a vector of instances of the required type.
         */
        static vector<T>* getVectorByQuery(string&);

        //@}

        //! \name Platform-Specific Class Method
        //@{

#if __WORDSIZE != 64
        //! 32-bit implementation of the atoll() function.
        /*!
         * 32-bit implementation of the atoll() function, taken from
         * http://www.koders.com/c/fid41B415AF8E97572E9336D135F2329BD2D56E1B07.aspx
         * This is required for 32-bit platforms, like Windows XP.
         * 
         * \param s An array of char
         *
         * \return A long long value (64-bit long integer)
         */
        static long long int atoll(const char*);
#endif

        //@}

        //! \name Private Instance Fields
        //@{

    private:
        //! The ID of the current instance.
        ID _id;
    
        //! A flag indicating whether this instance exists in database or not.
        bool _isNew;
    
        //! A flag indicating whether this instance has been modified or not.
        bool _isDirty;
        
        //! An instance of AnyPropertyMap which contains the data for this instance
        AnyPropertyMap _data;

        //@}

    };

    template <class T>
    ActiveRecord<T>::ActiveRecord(const string& className)
    : _id        (DEFAULT_ID)
    , _isNew     (true)
    , _isDirty   (true)
    , _data      ()
    {
        _data.set<string>("class", className);
    }

    template <class T>
    ActiveRecord<T>::ActiveRecord(AnyPropertyMap& data)
    : _id        (data.get<int>("id"))
    , _isNew     (false)
    , _isDirty   (false)
    , _data      (data)
    {
    }

    template <class T>
    ActiveRecord<T>::ActiveRecord(const ActiveRecord& rhs)
    : _id        (rhs._id)
    , _isNew     (rhs._isNew)
    , _isDirty   (rhs._isDirty)
    , _data      (rhs._data)
    {
    }

    template <class T>
    ActiveRecord<T>::~ActiveRecord()
    {
    }

    template <class T>
    ActiveRecord<T>& ActiveRecord<T>::operator=(const ActiveRecord& rhs)
    {
        if (this != &rhs)
        {
            _id = rhs._id;
            _isDirty = rhs._isDirty;
            _isNew = rhs._isNew;
            _data = rhs._data;
        }
        return *this;
    }

    template <class T>
    template <class U>
    void ActiveRecord<T>::set(const string& key, const U& value)
    {
        setDirty();
        _data.set<U>(key, value);
    }

    template <class T>
    template <class U>
    const U& ActiveRecord<T>::get(const string& key)
    {
        return _data.get<U>(key);
    }
    
    template <class T>
    template <class U>
    void ActiveRecord<T>::addProperty(const string& key)
    {
        _data.addProperty<U>(key);
    }

    template <class T>
    const DateTime& ActiveRecord<T>::getCreationDateTime()
    {
        return _data.get<DateTime>("created_on");
    }

    template <class T>
    void ActiveRecord<T>::setCreationDateTimeToNow()
    {
        // Do not call "setDirty()" here!
        DateTime now;
        _data.set<DateTime>("created_on", now);
        _data.set<DateTime>("updated_on", now);
    }
    
    template <class T>
    const DateTime& ActiveRecord<T>::getLastModificationDateTime()
    {
        return _data.get<DateTime>("updated_on");
    }

    template <class T>
    void ActiveRecord<T>::setLastModificationDateTimeToNow()
    {
        // Do not call "setDirty()" here!
        DateTime now;
        _data.set<DateTime>("updated_on", now);
    }

    template <class T>
    const ID ActiveRecord<T>::getId() const
    {
        return _id;
    }
    
    template <class T>
    void ActiveRecord<T>::setName(const string& name)
    {
        set<string>("name", name);
    }

    template <class T>
    const string& ActiveRecord<T>::getName()
    {
        return get<string>("name");
    }
    
    template <class T>
    void ActiveRecord<T>::setParentId(const ID value)
    {
        // Do not call "setDirty()" here!
        _data.set<int>(T::getParentColumnName(), (int)value);
    }

    template <class T>
    void ActiveRecord<T>::save()
    {
        SQLiteWrapper& wrapper = SQLiteWrapper::get();
        bool ok = wrapper.open();
        if (ok)
        {
            if (hasParent())
            {
                // This should work always!
                // hasParent() means that getParent() won't return NULL;
                // and moreover, children's call to "save()" comes AFTER the 
                // parent's call to "save()"
                // (see the "saveChildren()" call at the end of this method...)
                setParentId(getParent()->getId());
            }
            if (_isNew)
            {
                insert();
                _id = wrapper.getLastRowId();
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
            saveChildren();
        }
        wrapper.close();
    }

    template <class T>
    void ActiveRecord<T>::update()
    {
        SQLiteWrapper& wrapper = SQLiteWrapper::get();
        setLastModificationDateTimeToNow();
        wrapper.executeQuery(_data.getStringForUpdate(T::getTableName(), _id));
    }

    template <class T>
    void ActiveRecord<T>::insert()
    {
        SQLiteWrapper& wrapper = SQLiteWrapper::get();
        bool ok = false;
        if (!wrapper.tableExists(T::getTableName()))
        {
            // Ask the subclass to create its own structure
            createSchemaStructure();
            
            // Add some more required properties
            addProperty<int>(T::getParentColumnName());
            addProperty<string>("class");
            addProperty<string>("name");
            addProperty<DateTime>("created_on");
            addProperty<DateTime>("updated_on");
            _data.createPrimaryKey("id");
            ok = wrapper.executeQuery(_data.getStringForCreateTable(T::getTableName()));
        }
        setCreationDateTimeToNow();
        ok = wrapper.executeQuery(_data.getStringForInsert(T::getTableName()));
    }

    template <class T>
    const bool ActiveRecord<T>::isDirty() const
    {
        return _isDirty;
    }

    template <class T>
    const bool ActiveRecord<T>::isNew() const
    {
        return _isNew;
    }

    template <class T>
    void ActiveRecord<T>::setDirty()
    {
        _isDirty = true;
        if (hasParent())
        {
            getParent()->setDirty();
        }
    }

    template <class T>
    void ActiveRecord<T>::destroy()
    {
        if (_id != DEFAULT_ID)
        {
            ActiveRecord<T>::remove(_id);
            _isDirty = true;
            _isNew = true;
        }
    }

    template <class T>
    void ActiveRecord<T>::remove(const ID id)
    {
        stringstream query;
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
    
    template <class T>
    void ActiveRecord<T>::removeAll()
    {
        stringstream query;
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

    template <class T>
    T* ActiveRecord<T>::findById(const ID id)
    {
        stringstream query;
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
            map<string, string> schema = wrapper.getTableSchema(T::getTableName());
            ok = wrapper.executeQuery(query.str());
            wrapper.close();
            if (ok)
            {
                vector<AnyPropertyMap>* maps = getPropertyMaps(schema);
                vector<AnyPropertyMap>::iterator iter;
                for (iter = maps->begin(); iter != maps->end(); ++iter)
                {
                    item = new T(*iter);
                }
                delete maps;
            }
        }
        return item;
    }

    template <class T>
    vector<T>* ActiveRecord<T>::findAll()
    {
        stringstream query;
        query << "SELECT * FROM ";
        query << T::getTableName();
        query << ";";
        
        string q = query.str();
        return getVectorByQuery(q);
    }
    
    template <class T>
    vector<T>* ActiveRecord<T>::findByCondition(const FindConditions& conditions)
    {
        stringstream query;
        query << "SELECT * FROM ";
        query << T::getTableName();
        query << " WHERE ";
        query << conditions.getStringForWhere();
        query << ";";
        
        string q = query.str();
        return getVectorByQuery(q);
    }
    
    template <class T>
    vector<AnyPropertyMap>* ActiveRecord<T>::getPropertyMaps(map<string, string>& schema)
    {
        SQLiteWrapper& wrapper = SQLiteWrapper::get();
        vector<AnyPropertyMap>* maps = new vector<AnyPropertyMap>();
        const vector<string>& data = wrapper.getData();
        const size_t numberOfHeaders = wrapper.getTableHeaders().size();
        const size_t dataItems = data.size();
        const vector<string>& headers = wrapper.getTableHeaders();

        for (size_t i = 0; i < dataItems; i = i + numberOfHeaders)
        {
            AnyPropertyMap instanceData;
            for (int j = 0; j < numberOfHeaders; ++j)
            {
                const string& currentHeader = headers[j];
                string& currentDataType = schema[currentHeader];
                const string& currentValue = data[i + j];
                
                if(currentDataType == "TEXT")
                {
                    instanceData.set<string>(currentHeader, currentValue);
                }
                else if (currentDataType == "INTEGER")
                {
                    instanceData.set<int>(currentHeader, atoi(currentValue.c_str()));
                }
                else if (currentDataType == "BOOLEAN")
                {
                    instanceData.set<bool>(currentHeader, atoi(currentValue.c_str()));
                }
                else if (currentDataType == "REAL")
                {
                    instanceData.set<double>(currentHeader, atof(currentValue.c_str()));
                }
                else if (currentDataType == "DATETIME")
                {
                    // We have to use the "long long atoll(const*)" function to 
                    // cast the string value coming from the DB layer into an int64 value,
                    // that is used to create a Timestamp, used to create a proper DateTime instance.
                    long long num = atoll(currentValue.c_str());
                    DateTime date(Timestamp::fromUtcTime(num));
                    instanceData.set<DateTime>(currentHeader, date);
                }
            }
            maps->push_back(instanceData);
        }
        return maps;
    }
    
    template <class T>
    vector<T>* ActiveRecord<T>::getVectorByQuery(string& query)
    {
        vector<T>* items = new vector<T>;
        SQLiteWrapper& wrapper = SQLiteWrapper::get();
        bool ok = wrapper.open();
        if (ok)
        {
            map<string, string> schema = wrapper.getTableSchema(T::getTableName());
            ok = wrapper.executeQuery(query);
            if (ok)
            {
                vector<AnyPropertyMap>* maps = getPropertyMaps(schema);
                vector<AnyPropertyMap>::iterator iter;
                for (iter = maps->begin(); iter != maps->end(); ++iter)
                {
                    T item(*iter);
                    items->push_back(item);
                }
                delete maps;
            }
            wrapper.close();
        }
        return items;        
    }

#if __WORDSIZE != 64
    template <class T>
    long long int ActiveRecord<T>::atoll(const char* s) 
    {
        long long int v = 0;
        int sign = 1;
        while(*s == ' ' || (unsigned int)(*s - 9) < 5u) ++s;
        switch (*s) 
        {
            case '-': sign=-1;
            case '+': ++s;
        }
        while ((unsigned int) (*s - '0') < 10u) 
        {
            v = v * 10 + *s - '0'; ++s;
        }
        return sign == -1 ? -v : v;
    }
#endif
}

#endif /* ACTIVERECORD_H_ */
