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
     * Wrapper around an std::map of string and AnyProperties.
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
        AnyProperty& operator[](const std::string&);
        
        //! States whether the object referenced by the key exists in the current instance.
        /*!
         * States whether the object referenced by the key exists in the current instance.
         * 
         * \param key The key to the object being sought.
         *
         * \return A boolean; true if the object exists, false otherwise.
         */
        const bool hasProperty(const std::string&) const;
        
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
        
        //! Adds a string property to the current instance.
        /*!
         * Adds a string property to the current instance.
         * 
         * \param key The name of the property to add.
         */
        void addStringProperty(const std::string&);

        //! Adds an integer property to the current instance.
        /*!
         * Adds an integer property to the current instance.
         * 
         * \param key The name of the property to add.
         */
        void addIntegerProperty(const std::string&);

        //! Adds a boolean property to the current instance.
        /*!
         * Adds a boolean property to the current instance.
         * 
         * \param key The name of the property to add.
         */
        void addBooleanProperty(const std::string&);

        //! Adds a double property to the current instance.
        /*!
         * Adds a double property to the current instance.
         * 
         * \param key The name of the property to add.
         */
        void addDoubleProperty(const std::string&);

        //! Adds a DateTime property to the current instance.
        /*!
         * Adds a DateTime property to the current instance.
         * 
         * \param key The name of the property to add.
         */
        void addDateTimeProperty(const std::string&);
        
        //! Sets the string value of the property whose name is the first parameter.
        /*!
         * Sets the string value of the property whose name is the first parameter.
         * 
         * \param key The name of the property to set
         * \param value The value of the property to set
         */
        void setString(const std::string&, const std::string&);

        //! Sets the string value of the property whose name is the first parameter.
        /*!
         * Sets the integer value of the property whose name is the first parameter.
         * 
         * \param key The name of the property to set
         * \param value The value of the property to set
         */
        void setInteger(const std::string&, const int);

        //! Sets the boolean value of the property whose name is the first parameter.
        /*!
         * Sets the boolean value of the property whose name is the first parameter.
         * 
         * \param key The name of the property to set
         * \param value The value of the property to set
         */
        void setBoolean(const std::string&, const bool);

        //! Sets the double value of the property whose name is the first parameter.
        /*!
         * Sets the double value of the property whose name is the first parameter.
         * 
         * \param key The name of the property to set
         * \param value The value of the property to set
         */
        void setDouble(const std::string&, const double);

        //! Sets the date/time value of the property whose name is the first parameter.
        /*!
         * Sets the date/time value of the property whose name is the first parameter.
         * 
         * \param key The name of the property to set
         * \param value The value of the property to set
         */
        void setDateTime(const std::string& key, const Poco::DateTime& value);

        //! Returns the string value of the property whose name is passed as parameter.
        /*!
         * Returns the string value of the property whose name is passed as parameter.
         * 
         * \param key The name of the property to get
         * 
         * \return The current string value of the named property
         */
        const std::string getString(const std::string&);

        //! Returns the integer value of the property whose name is passed as parameter.
        /*!
         * Returns the integer value of the property whose name is passed as parameter.
         * 
         * \param key The name of the property to get
         * 
         * \return The current integer value of the named property
         */
        const int getInteger(const std::string&);

        //! Returns the boolean value of the property whose name is passed as parameter.
        /*!
         * Returns the boolean value of the property whose name is passed as parameter.
         * 
         * \param key The name of the property to get
         * 
         * \return The current boolean value of the named property
         */
        const bool getBoolean(const std::string&);

        //! Returns the double value of the property whose name is passed as parameter.
        /*!
         * Returns the double value of the property whose name is passed as parameter.
         * 
         * \param key The name of the property to get
         * 
         * \return The current double value of the named property
         */
        const double getDouble(const std::string&);

        //! Returns the date/time value of the property whose name is passed as parameter.
        /*!
         * Returns the date/time value of the property whose name is passed as parameter.
         * 
         * \param key The name of the property to get
         * 
         * \return The current date/time value of the named property
         */
        const Poco::DateTime getDateTime(const std::string&);

        //! Creates an integer property marked as "primary key".
        /*!
         * Creates an integer property marked as "primary key".
         * 
         * \param key The name of the new property.
         */
        void createPrimaryKey(const std::string&);

        //! Generates a CREATE TABLE SQL statement.
        /*!
         * Generates a CREATE TABLE SQL statement.
         * 
         * \return A string.
         */
        const std::string getStringForCreateTable(std::string&) const;

        //! Generates an INSERT SQL statement.
        /*!
         * Generates an INSERT SQL statement.
         * 
         * \return A string.
         */
        const std::string getStringForInsert(std::string&) const;

        //! Generates an UPDATE SQL statement.
        /*!
         * Generates an UPDATE SQL statement.
         * 
         * \return A string.
         */
        const std::string getStringForUpdate(std::string&, const int id) const;

        //! Generates a CREATE TABLE SQL statement.
        /*!
         * Generates a CREATE TABLE SQL statement.
         * 
         * \return A string.
         */
        const std::string getStringForWhere() const;

    private:
        
        //! Used by the getStringForInsert() method.
        /*!
         * Used by the getStringForInsert() method. Generates a list
         * of columns used in the INSERT SQL statement.
         * 
         * \return A string.
         */
        const std::string getColumnList() const;

    private:
        //! The wrapped map of properties.
        std::map<std::string, AnyProperty> _map;
    };
}

#endif /* ANYPROPERTYMAP_H_ */
