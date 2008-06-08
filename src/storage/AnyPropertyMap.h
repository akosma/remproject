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

//! Contains the interface of the storage::AnyPropertyMap class.
/*!
 * \file AnyPropertyMap.h
 *
 * Contains the interface of the storage::AnyPropertyMap class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/23/08
 */

#ifndef ANYPROPERTYMAP_H_
#define ANYPROPERTYMAP_H_

#include <string>
#include <map>

#include <Poco/DateTime.h>

#ifndef ANYPROPERTY_H_
#include "AnyProperty.h"
#endif

using Poco::DateTime;
using std::string;
using std::map;
using std::pair;

//! Framework for storing instances in SQLite files.
/*!
 * \namespace storage
 * Holds the classes used to store instances in SQLite files, allowing them
 * to be chained among them, using a simple syntax in class declarations.
 */
namespace storage
{
    //! Collection of AnyProperty instances.
    /*!
     * \class AnyPropertyMap
     *
     * Wrapper around an map of string and AnyProperties.
     * It offers several methods that allow for the creation of 
     * SQL statements representing the structure and contents
     * of the values inside the map.
     */
    class AnyPropertyMap
    {
    public:

        //! Constructor.
        /*!
         *  Constructor.
         */
        AnyPropertyMap();
        
        //! Copy constructor.
        /*!
         * Copy constructor.
         * 
         * \param rhs The instance to copy from.
         */
        AnyPropertyMap(const AnyPropertyMap&);
        
        //! Assignment operator.
        /*!
         * Assignment operator.
         * 
         * \param rhs The instance to assign from.
         * 
         * \return A reference to the current instance.
         */
        AnyPropertyMap& operator=(const AnyPropertyMap&);

        //! Virtual destructor.
        /*!
         *  Virtual destructor.
         */
        virtual ~AnyPropertyMap();

        //! Square bracket operator.
        /*!
         * Square bracket operator. Returns a reference to the property
         * whose key is passed as parameter.
         * 
         * \param key The key to the object being sought.
         *
         * \return A reference to the sought property.
         */
        AnyProperty& operator[](const string&);
        
        //! States whether the object referenced by the key exists in the current instance.
        /*!
         * States whether the object referenced by the key exists in the current instance.
         * 
         * \param key The key to the object being sought.
         *
         * \return A boolean; true if the object exists, false otherwise.
         */
        const bool hasProperty(const string&) const;
        
        //! States whether the current instance has any contained items.
        /*!
         * States whether the current instance has any contained items.
         * 
         * \return A boolean value.
         */
        const bool isEmpty() const;
        
        //! Returns the number of items stored in the current instance.
        /*!
         * Returns the number of items stored in the current instance.
         * 
         * \return The number of items stored.
         */
        const unsigned int count() const;
        
        //! Adds a property to the current instance.
        /*!
         * Adds a property to the current instance.
         * This function is inlined in the header file to avoid linker errors.
         * 
         * \param key The name of the property to add.
         */
        template <class T>
        void addProperty(const string&);
        
        //! Sets the value of the property whose name is the first parameter.
        /*!
         * Sets the value of the property whose name is the first parameter.
         * This function is inlined in the header file to avoid linker errors.
         * 
         * \param key The name of the property to set
         * \param value The value of the property to set
         */
        template <class T>
        void set(const string& key, const T&);

        //! Returns the string value of the property whose name is passed as parameter.
        /*!
         * Returns the string value of the property whose name is passed as parameter.
         * This function is inlined in the header file to avoid linker errors.
         * 
         * \param key The name of the property to get
         * 
         * \return The current string value of the named property
         */
        template <class T>
        const T& get(const string&);

        //! Creates an integer property marked as "primary key".
        /*!
         * Creates an integer property marked as "primary key".
         * 
         * \param key The name of the new property.
         */
        void createPrimaryKey(const string&);

        //! Generates a CREATE TABLE SQL statement.
        /*!
         * Generates a CREATE TABLE SQL statement.
         * 
         * \return A string.
         */
        const string getStringForCreateTable(string&) const;

        //! Generates an INSERT SQL statement.
        /*!
         * Generates an INSERT SQL statement.
         * 
         * \return A string.
         */
        const string getStringForInsert(string&) const;

        //! Generates an UPDATE SQL statement.
        /*!
         * Generates an UPDATE SQL statement.
         * 
         * \return A string.
         */
        const string getStringForUpdate(string&, const int id) const;

    protected:
        
        //! Used by the getStringForInsert() method.
        /*!
         * Used by the getStringForInsert() method. Generates a list
         * of columns used in the INSERT SQL statement.
         * 
         * \return A string.
         */
        const string getColumnList() const;

        //! Pointer to some private methods used by joinMap.
        /*!
         * Several methods in this class must iterate on all the elements of
         * the map, extract some value and build a string out of them.
         * This typedef helps abstracting the algorithm from these methods,
         * who just pass a pointer of this type to joinMap to get the required string.
         * The definition follows the instructions set in 
         * http://www.parashift.com/c++-faq-lite/pointers-to-members.html#faq-33.5
         */
        typedef const string (AnyPropertyMap::*Extractor)(const pair<string, AnyProperty>&) const;
        #define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))
        
        //! Iterates over the internal map of AnyProperty applying a transformation.
        /*!
         * Iterates over the internal map of AnyProperty applying a transformation.
         * The method applies an "Extractor" method to the current map of AnyProperty
         * and extracts a string
         * 
         * \param e A pointer to a method taking a pair of string and AnyProperty and
         * returning a string.
         * \param separator A string used to separate each value in the map.
         * 
         * \return A string.
         */
        const string joinMap(AnyPropertyMap::Extractor, const string&) const;
        
        //! Used by joinMap
        const string getKey(const pair<string, AnyProperty>&) const;

        //! Used by joinMap
        const string getSQLiteColumnDefinition(const pair<string, AnyProperty>&) const;

        //! Used by joinMap
        const string getQuotedValue(const pair<string, AnyProperty>&) const;

        //! Used by joinMap
        const string getNameValuePair(const pair<string, AnyProperty>&) const;

    private:
        //! The wrapped map of properties.
        map<string, AnyProperty> _map;
    };

    template <class T>
    void AnyPropertyMap::addProperty(const string& key)
    {
        if (!hasProperty(key))
        {
            set<T>(key, T());
        }
    }
    
    template <class T>
    void AnyPropertyMap::set(const string& key, const T& value)
    {
        Any any(value);
        AnyProperty prop(key, any);
        _map[key] = prop;
    }

    template <class T>
    const T& AnyPropertyMap::get(const string& key)
    {
        return _map[key].get<T>();
    }
}

#endif /* ANYPROPERTYMAP_H_ */
