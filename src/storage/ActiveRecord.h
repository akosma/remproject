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
#include <iostream>

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

    /*!
     * \class ActiveRecord
     *
     *  
     */
	template <class T>
    class ActiveRecord
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
        ActiveRecord(std::vector<std::string>&, std::string&);
        
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

        static std::vector<T>* findAll();
        static T* findById(const ID id);
        
        void setStringProperty(const std::string&, const std::string&);
        void setIntegerProperty(const std::string&, const int);
        void setBooleanProperty(const std::string&, const bool);
        void setDoubleProperty(const std::string&, const double);

        std::string getString(const std::string&);
        int getInteger(const std::string&);
        bool getBoolean(const std::string&);
        double getDouble(const std::string&);

    protected:

        /*!
         * Used by subclasses to change the "_isDirty" flag in the 
         * ActiveRecord base class; subclasses must call this method in
         * every "setter" method.
         */
        void setDirty();

        void addStringProperty(const std::string&);
        void addIntegerProperty(const std::string&);
        void addBooleanProperty(const std::string&);
        void addDoubleProperty(const std::string&);

        virtual void createAllPropertiesForSchema() = 0;

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

        //! The ID of the current instance.
        ID _id;
    
        //! A flag indicating whether this instance exists in database or not.
        bool _isNew;
    
        //! A flag indicating whether this instance has been modified or not.
        bool _isDirty;
        
        //! An instance of AnyPropertyMap which contains the data for this instance
        AnyPropertyMap _data;

        std::string _tableName;
    };
    
    /*!
     * Default constructor. Sets the ID to DEFAULT_ID. Used
     * to create instances that do not exist yet in the database.
     */
    template <class T>
    ActiveRecord<T>::ActiveRecord(std::string tableName)
    : _id        (DEFAULT_ID)
    , _isNew     (true)
    , _isDirty   (true)
    , _tableName (tableName)
    {
    }

    /*!
     * Constructor. Used to create instances whose state is
     * already present in the database.
     */
    template <class T>
    ActiveRecord<T>::ActiveRecord(std::vector<std::string>& elements, std::string& tableName)
    : _id        (DEFAULT_ID)
    , _isNew     (true)
    , _isDirty   (true)
    , _tableName (tableName)
    {
    }

    /*!
     * Copy constructor.
     * 
     * \param rhs The instance to copy from ("right hand side").
     */
    template <class T>
    ActiveRecord<T>::ActiveRecord(const ActiveRecord& rhs)
    : _id        (rhs._id)
    , _isNew     (rhs._isNew)
    , _isDirty   (rhs._isDirty)
    , _tableName (rhs._tableName)
    {
    }

    /*!
     * Virtual destructor.
     */
    template <class T>
    ActiveRecord<T>::~ActiveRecord()
    {
    }

    /*!
     * Assignment operator.
     * 
     * \param rhs The instance to copy from ("right hand side").
     */
    template <class T>
    ActiveRecord<T>& ActiveRecord<T>::operator=(const ActiveRecord& rhs)
    {
    	if (this == &rhs)
    	{
    		return *this;
    	}
    	_id = rhs._id;
    	_isDirty = rhs._isDirty;
    	_isNew = rhs._isNew;
    	_tableName = rhs._tableName;
    	return *this;
    }
    
    template <class T>
    void ActiveRecord<T>::setStringProperty(const std::string& key, const std::string& value)
    {
        setDirty();
        _data.setStringProperty(key, value);
    }

    template <class T>
    void ActiveRecord<T>::setIntegerProperty(const std::string& key, const int value)
    {
        setDirty();
        _data.setIntegerProperty(key, value);
    }

    template <class T>
    void ActiveRecord<T>::setBooleanProperty(const std::string& key, const bool value)
    {
        setDirty();
        _data.setBooleanProperty(key, value);
    }

    template <class T>
    void ActiveRecord<T>::setDoubleProperty(const std::string& key, const double value)
    {
        setDirty();
        _data.setDoubleProperty(key, value);
    }
    
    template <class T>
    void ActiveRecord<T>::addStringProperty(const std::string& key)
    {
        if (!_data.hasProperty(key))
        {
            _data.setStringProperty(key, "");
        }
    }

    template <class T>
    void ActiveRecord<T>::addIntegerProperty(const std::string& key)
    {
        if (!_data.hasProperty(key))
        {
            _data.setIntegerProperty(key, 0);
        }
    }

    template <class T>
    void ActiveRecord<T>::addBooleanProperty(const std::string& key)
    {
        if (!_data.hasProperty(key))
        {
            _data.setBooleanProperty(key, false);
        }
    }

    template <class T>
    void ActiveRecord<T>::addDoubleProperty(const std::string& key)
    {
        if (!_data.hasProperty(key))
        {
            _data.setDoubleProperty(key, 0.0);
        }
    }
    
    template <class T>
    std::string ActiveRecord<T>::getString(const std::string& key)
    {
        return _data.getString(key);
    }
    
    template <class T>
    int ActiveRecord<T>::getInteger(const std::string& key)
    {
        return _data.getInteger(key);
    }
    
    template <class T>
    bool ActiveRecord<T>::getBoolean(const std::string& key)
    {
        return _data.getBoolean(key);
    }
    
    template <class T>
    double ActiveRecord<T>::getDouble(const std::string& key)
    {
        return _data.getDouble(key);
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
    template <class T>
    void ActiveRecord<T>::save()
    {
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
    		if (_isDirty)
    		{
    			update();
    			_isDirty = false;
    		}
    	}
    }
        
    template <class T>
    void ActiveRecord<T>::update()
    {
    	SQLiteWrapper& wrapper = SQLiteWrapper::get();
    	bool ok = wrapper.open();
    	if (ok)
    	{
    	    ok = wrapper.executeQuery(_data.getStringForUpdate(_tableName, _id));
    	}
		wrapper.close();
    }
    
    template <class T>
    const ID ActiveRecord<T>::insert()
    {
    	SQLiteWrapper& wrapper = SQLiteWrapper::get();
    	bool ok = wrapper.open();
    	if (!wrapper.tableExists(_tableName))
    	{
            createAllPropertiesForSchema();
            _data.createPrimaryKey("id");
            ok = wrapper.executeQuery(_data.getStringForCreateTable(_tableName));
    	}
    	if (ok)
    	{
    	    ok = wrapper.executeQuery(_data.getStringForInsert(_tableName));
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
    template <class T>
    const bool ActiveRecord<T>::isDirty() const
    {
    	return _isDirty;
    }

    /*!
     * Returns a value indicating whether the current instance
     * exists in the database or not.
     * 
     * \return A boolean value.
     */
    template <class T>
    const bool ActiveRecord<T>::isNew() const
    {
    	return _isNew;
    }

    /*!
     * Returns the ID of the current instance.
     * 
     * \return A ActiveRecordId (long long) value.
     */
    template <class T>
    const ID ActiveRecord<T>::getId() const
    {
    	return _id;
    }

    /*!
     * Used by subclasses to change the "_isDirty" flag in the 
     * ActiveRecord base class; subclasses must call this method in
     * every "setter" method.
     */
    template <class T>
    void ActiveRecord<T>::setDirty()
    {
    	_isDirty = true;
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
    template <class T>
    T* ActiveRecord<T>::findById(const ID id)
    {
    	T* item = NULL;
    	SQLiteWrapper& wrapper = SQLiteWrapper::get();
    	bool ok = wrapper.open();
    	if (ok)
    	{
    		ok = wrapper.executeQuery(T::getStringForSelect(id));
    		wrapper.close();
    		if (ok)
    		{
    			const std::vector<std::string>& data = wrapper.getData();
    			const size_t dataItems = data.size();

                // const ActiveRecordId id = atoi(data[0].c_str());
                // const std::string firstName(data[1]);
                // const std::string lastName(data[2]);
				item = new T(data);
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
    template <class T>
    std::vector<T>* ActiveRecord<T>::findAll()
    {
    	std::vector<T>* items = new std::vector<T>;
    	SQLiteWrapper& wrapper = SQLiteWrapper::get();
    	bool ok = wrapper.open();
    	if (ok)
    	{
    		ok = wrapper.executeQuery(T::getStringForSelect());
    		wrapper.close();
    		if (ok)
    		{
    			const std::vector<std::string>& data = wrapper.getData();
    			const size_t numberOfHeaders = wrapper.getTableHeaders().size();
    			const size_t dataItems = data.size();

    			for (size_t i = 0; i < dataItems;
    								i = i + numberOfHeaders)
    			{
                    // const ActiveRecordId id = atoi(data[i].c_str());
                    // const std::string firstName(data[i + 1]);
                    // const std::string lastName(data[i + 2]);
    				const T item(data, i);
    				items->push_back(item);
    			}
    		}
    	}
    	return items;
    }
}

#endif /* ACTIVERECORD_H_ */
