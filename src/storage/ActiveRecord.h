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
 * Holds the classes used to store instances in SQLite files, allowing them
 * to be chained among them, using a simple syntax in class declarations.
 */
namespace storage
{
    /*!
     * \class NoParent
     *
     * Dummy class used by ActiveRecord subclasses who do not wish
     * to be related to a "parent" class. It implements many methods
     * required during template instantiation at compile-time.
     */
    class NoParent
    {
    public:
        /*!
         * Constructor
         */
        NoParent() 
        : _parentColumn("no_parent") 
        {
        }

        /*!
         * Virtual destructor
         */
        virtual ~NoParent() 
        {
        }

        /*!
         * Placeholder method required at template instantiation time
         */
        const std::string& getParentColumn() const
        {
            return _parentColumn;
        }

        /*!
         * Placeholder method required at template instantiation time
         */
        static std::string& getTableName()
        { 
            static std::string tableName("no_parent");
            return tableName; 
        }

        /*!
         * Placeholder method required at template instantiation time
         */
        const ID getId() const
        {
            return DEFAULT_ID;
        }

        /*!
         * Placeholder method required at template instantiation time
         */
        void setDirty()
        {
        }
        
        /*!
         * Placeholder method required at template instantiation time
         */
        const bool hasParent() const
        {
            return false;
        }
        
        /*!
         * Placeholder method required at template instantiation time
         */
        const ID getParentId() const
        {
            return DEFAULT_ID;
        }
    private:
        //! Used to return a valid string reference only
        std::string _parentColumn;
    };

    /*!
     * \class NoChildren
     *
     * Dummy class used by ActiveRecord subclasses who do not wish
     * to have related "child" instances. It implements many methods
     * required during template instantiation at compile-time.
     */
    class NoChildren
    {
    public:
        /*!
         * Constructor
         */
        NoChildren()
        {
        }
        
        /*!
         * Virtual destructor
         */
        virtual ~NoChildren()
        {
        }
        
        /*!
         * Placeholder method required at template instantiation time
         */
        void save() 
        {
        }

        /*!
         * Placeholder method required at template instantiation time
         */
        void saveChildren()
        {
        }
        
        /*!
         * Placeholder method required at template instantiation time
         */
        void destroy()
        {
        }
    };
    
    /*!
     * \class ActiveRecord
     *
     * Base template class for all objects that can be saved into a SQLite class.
     * Its design is heavily inspired by the classes of the same name in the
     * Ruby on Rails web development framework:
     * http://rubyonrails.org/
     */
    template <class T
             , class P = NoParent
             , class C = NoChildren>
    class ActiveRecord : public P
                       , public C
    {
    public:
        /** \name ConstructorsDestructor Constructors, destructor and assignment operator
        }**/
        //@{

        /*!
         * Default constructor. Sets the ID to DEFAULT_ID. Used
         * to create instances that do not exist yet in the database.
         * 
         * \param className The subclass name of the current instance.
         */
        ActiveRecord(const std::string&);
        
        /*!
         * Constructor. Used to create instances already existing in the database.
         * This constructor is called by the ActiveRecord::getVectorByQuery() method.
         * 
         * \param className The subclass name of the current instance.
         * \param id The ID of the current instance
         * \param data An AnyPropertyMap containing the internal state of the instance
         */
        ActiveRecord(const std::string&, const ID, AnyPropertyMap&);
        
        /*!
         * Copy constructor.
         * 
         * \param rhs The instance to copy data from.
         */
        ActiveRecord(const ActiveRecord&);

        /*!
         * Virtual destructor.
         */
        virtual ~ActiveRecord();

        /*!
         * Assignment operator.
         * 
         * \param rhs The instance to copy from ("right hand side").
         */
        ActiveRecord& operator=(const ActiveRecord&);

        //@}
    
    public:
        /** \name DynamicObjectMethods Instance methods helping to work with dynamic objects.
        }**/
        //@{

        /*!
         * Sets the string value of the property whose name is the first parameter.
         * 
         * \param key The name of the property to set
         * \param value The value of the property to set
         */
        void setString(const std::string&, const std::string&);
        
        /*!
         * Sets the integer value of the property whose name is the first parameter.
         * 
         * \param key The name of the property to set
         * \param value The value of the property to set
         */
        void setInteger(const std::string&, const int);

        /*!
         * Sets the boolean value of the property whose name is the first parameter.
         * 
         * \param key The name of the property to set
         * \param value The value of the property to set
         */
        void setBoolean(const std::string&, const bool);

        /*!
         * Sets the double value of the property whose name is the first parameter.
         * 
         * \param key The name of the property to set
         * \param value The value of the property to set
         */
        void setDouble(const std::string&, const double);

        /*!
         * Sets the date/time value of the property whose name is the first parameter.
         * 
         * \param key The name of the property to set
         * \param value The value of the property to set
         */
        void setDateTime(const std::string&, const Poco::DateTime&);

        /*!
         * Returns the string value of the property whose name is passed as parameter.
         * 
         * \param key The name of the property to get
         * 
         * \return The current string value of the named property
         */
        const std::string getString(const std::string&);

        /*!
         * Returns the integer value of the property whose name is passed as parameter.
         * 
         * \param key The name of the property to get
         * 
         * \return The current integer value of the named property
         */
        const int getInteger(const std::string&);

        /*!
         * Returns the boolean value of the property whose name is passed as parameter.
         * 
         * \param key The name of the property to get
         * 
         * \return The current boolean value of the named property
         */
        const bool getBoolean(const std::string&);

        /*!
         * Returns the double value of the property whose name is passed as parameter.
         * 
         * \param key The name of the property to get
         * 
         * \return The current double value of the named property
         */
        const double getDouble(const std::string&);

        /*!
         * Returns the date/time value of the property whose name is passed as parameter.
         * 
         * \param key The name of the property to get
         * 
         * \return The current date/time value of the named property
         */
        const Poco::DateTime getDateTime(const std::string&);

    protected:
        void addStringProperty(const std::string&);
        void addIntegerProperty(const std::string&);
        void addBooleanProperty(const std::string&);
        void addDoubleProperty(const std::string&);
        void addDateTimeProperty(const std::string&);

        //@}

    public:
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
         * \return A boolean value stating whether the current instance 
         * exists in the database (false) or not (true).
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
        const Poco::DateTime getCreationDateTime();
        const Poco::DateTime getLastModificationDateTime();

        /*!
         * This method is the core of the ActiveRecord family of
         * classes. Clients use it to write the current state of
         * the instance into the database.
         */
        void save();
        
        void destroy();

        /*!
         * Used to change the "_isDirty" flag in the 
         * ActiveRecord base class; subclasses must call this method in
         * every "setter" method.
         */
        void setDirty();

    public:
        static void removeAll();
        static void remove(const ID);

        static std::vector<T>* findAll();
        static std::vector<T>* findByCondition(const storage::AnyPropertyMap&);
        static T* findById(const ID);

    protected:
        virtual void createSchemaStructure() = 0;

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
        
        void setParentId(const ID value);
        void setLastModificationDateTimeToNow();
        void setCreationDateTimeToNow();
        void setClassName(const std::string&);

    private:
        static std::vector<storage::AnyPropertyMap>* getPropertyMaps(std::map<std::string, std::string>&);
        static std::vector<T>* getVectorByQuery(std::string&);

#if __WORDSIZE != 64
        /*!
         * 32-bit implementation of the atoll() function, taken from
         * http://www.koders.com/c/fid41B415AF8E97572E9336D135F2329BD2D56E1B07.aspx
         * 
         * \param s An array of char
         *
         * \return A long long value (64-bit long integer)
         */
        static long long int atoll(const char*);
#endif

    private:
        //! The ID of the current instance.
        ID _id;
    
        //! A flag indicating whether this instance exists in database or not.
        bool _isNew;
    
        //! A flag indicating whether this instance has been modified or not.
        bool _isDirty;
        
        //! An instance of AnyPropertyMap which contains the data for this instance
        AnyPropertyMap _data;

        //! The subclass name of the current instance.
        std::string _className;
    };
    
    /** \name ConstructorsDestructor Constructors, destructor and assignment operator
    }**/
    //@{

    /*!
     * Default constructor. Sets the ID to DEFAULT_ID. Used
     * to create instances that do not exist yet in the database.
     * 
     * \param className The subclass name of the current instance.
     */
    template <class T, class P, class C>
    ActiveRecord<T, P, C>::ActiveRecord(const std::string& className)
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
     * Constructor. Used to create instances already existing in the database.
     * This constructor is called by the ActiveRecord::getVectorByQuery() method.
     * 
     * \param className The subclass name of the current instance.
     * \param id The ID of the current instance
     * \param data An AnyPropertyMap containing the internal state of the instance
     */
    template <class T, class P, class C>
    ActiveRecord<T, P, C>::ActiveRecord(const std::string& className, const ID id, AnyPropertyMap& data)
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
     * \param rhs The instance to copy data from.
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
    
    //@}
    
    /** \name DynamicObjectMethods Instance methods helping to work with dynamic objects.
    }**/
    //@{
    
    /*!
     * Sets the string value of the property whose name is the first parameter.
     * 
     * \param key The name of the property to set
     * \param value The value of the property to set
     */
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::setString(const std::string& key, const std::string& value)
    {
        setDirty();
        _data.setString(key, value);
    }

    /*!
     * Sets the integer value of the property whose name is the first parameter.
     * 
     * \param key The name of the property to set
     * \param value The value of the property to set
     */
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::setInteger(const std::string& key, const int value)
    {
        setDirty();
        _data.setInteger(key, value);
    }

    /*!
     * Sets the boolean value of the property whose name is the first parameter.
     * 
     * \param key The name of the property to set
     * \param value The value of the property to set
     */
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::setBoolean(const std::string& key, const bool value)
    {
        setDirty();
        _data.setBoolean(key, value);
    }

    /*!
     * Sets the double value of the property whose name is the first parameter.
     * 
     * \param key The name of the property to set
     * \param value The value of the property to set
     */
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::setDouble(const std::string& key, const double value)
    {
        setDirty();
        _data.setDouble(key, value);
    }
    
    /*!
     * Sets the date/time value of the property whose name is the first parameter.
     * 
     * \param key The name of the property to set
     * \param value The value of the property to set
     */
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::setDateTime(const std::string& key, const Poco::DateTime& value)
    {
        setDirty();
        _data.setDateTime(key, value);
    }
    
    /*!
     * Returns the string value of the property whose name is passed as parameter.
     * 
     * \param key The name of the property to get
     * 
     * \return The current string value of the named property
     */
    template <class T, class P, class C>
    const std::string ActiveRecord<T, P, C>::getString(const std::string& key)
    {
        return _data.getString(key);
    }
    
    /*!
     * Returns the integer value of the property whose name is passed as parameter.
     * 
     * \param key The name of the property to get
     * 
     * \return The current integer value of the named property
     */
    template <class T, class P, class C>
    const int ActiveRecord<T, P, C>::getInteger(const std::string& key)
    {
        return _data.getInteger(key);
    }
    
    /*!
     * Returns the boolean value of the property whose name is passed as parameter.
     * 
     * \param key The name of the property to get
     * 
     * \return The current boolean value of the named property
     */
    template <class T, class P, class C>
    const bool ActiveRecord<T, P, C>::getBoolean(const std::string& key)
    {
        return _data.getBoolean(key);
    }
    
    /*!
     * Returns the double value of the property whose name is passed as parameter.
     * 
     * \param key The name of the property to get
     * 
     * \return The current double value of the named property
     */
    template <class T, class P, class C>
    const double ActiveRecord<T, P, C>::getDouble(const std::string& key)
    {
        return _data.getDouble(key);
    }
    
    /*!
     * Returns the date/time value of the property whose name is passed as parameter.
     * 
     * \param key The name of the property to get
     * 
     * \return The current date/time value of the named property
     */
    template <class T, class P, class C>
    const Poco::DateTime ActiveRecord<T, P, C>::getDateTime(const std::string& key)
    {
        return _data.getDateTime(key);
    }
    
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::addStringProperty(const std::string& key)
    {
        _data.addStringProperty(key);
    }

    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::addIntegerProperty(const std::string& key)
    {
        _data.addIntegerProperty(key);
    }

    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::addBooleanProperty(const std::string& key)
    {
        _data.addBooleanProperty(key);
    }

    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::addDoubleProperty(const std::string& key)
    {
        _data.addDoubleProperty(key);
    }
    
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::addDateTimeProperty(const std::string& key)
    {
        _data.addDateTimeProperty(key);
    }

    //@}
    
    /** \name SpecialProperties Getters and setters for some special properties
    }**/
    //@{
    
    template <class T, class P, class C>
    const Poco::DateTime ActiveRecord<T, P, C>::getCreationDateTime()
    {
        return _data.getDateTime("created_on");
    }

    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::setCreationDateTimeToNow()
    {
        // Do not call "setDirty()" here!
        Poco::DateTime now;
        _data.setDateTime("created_on", now);
        _data.setDateTime("updated_on", now);
    }
    
    template <class T, class P, class C>
    const Poco::DateTime ActiveRecord<T, P, C>::getLastModificationDateTime()
    {
        return _data.getDateTime("updated_on");
    }

    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::setLastModificationDateTimeToNow()
    {
        // Do not call "setDirty()" here!
        Poco::DateTime now;
        _data.setDateTime("updated_on", now);
    }

    /*!
     * Returns the ID of the current instance.
     * 
     * \return An ID (long long) value.
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
    
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::setParentId(const ID value)
    {
        // Do not call "setDirty()" here!
        _data.setInteger(P::getParentColumn(), (int)value);
    }

    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::setClassName(const std::string& value)
    {
        // Do not call "setDirty()" here!
        _data.setString("class", value);
    }
    
    //@}

    /*!
     * This method is the core of the ActiveRecord family of
     * classes. Clients use it to write the current state of
     * the instance into the database.
     */
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::save()
    {
        ID parentId = P::getParentId();
        if (parentId != DEFAULT_ID)
        {
            setParentId(parentId);
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
            setLastModificationDateTimeToNow();
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
            // Ask the subclass to create its own structure
            createSchemaStructure();
            
            // Add some more required properties
            addIntegerProperty(P::getParentColumn());
            addStringProperty("class");
            addStringProperty("name");
            addDateTimeProperty("created_on");
            addDateTimeProperty("updated_on");
            _data.createPrimaryKey("id");
            ok = wrapper.executeQuery(_data.getStringForCreateTable(T::getTableName()));
        }
        if (ok)
        {
            setClassName(_className);
            setCreationDateTimeToNow();
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
     * Used by subclasses to change the "_isDirty" flag in the 
     * ActiveRecord base class; subclasses must call this method in
     * every "setter" method.
     */
    template <class T, class P, class C>
    void ActiveRecord<T, P, C>::setDirty()
    {
        _isDirty = true;
        if (P::hasParent())
        {
            P::getParent()->setDirty();
        }
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

#if __WORDSIZE != 64
    /*!
     * 32-bit implementation of the atoll() function, taken from
     * http://www.koders.com/c/fid41B415AF8E97572E9336D135F2329BD2D56E1B07.aspx
     * 
     * \param s An array of char
     *
     * \return A long long value (64-bit long integer)
     */
    template <class T, class P, class C>
    long long int ActiveRecord<T, P, C>::atoll(const char* s) 
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
