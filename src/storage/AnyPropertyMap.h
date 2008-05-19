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
    /*!
     * \class AnyPropertyMap
     *
     *  
     */
    class AnyPropertyMap
    {
    public:

        /*!
         *  AnyPropertyMap constructor.
         */
        AnyPropertyMap();
        AnyPropertyMap(const AnyPropertyMap&);
        AnyPropertyMap& operator=(const AnyPropertyMap&);

        /*!
         *  AnyPropertyMap virtual destructor.
         */
        virtual ~AnyPropertyMap();
        
        AnyProperty& operator[](const std::string&);
        const bool hasProperty(const std::string&) const;
        const bool isEmpty() const;
        const unsigned int count() const;
        
        void addStringProperty(const std::string&);
        void addIntegerProperty(const std::string&);
        void addBooleanProperty(const std::string&);
        void addDoubleProperty(const std::string&);
        void addDateTimeProperty(const std::string&);
        
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
        void setDateTime(const std::string& key, const Poco::DateTime& value);

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

        void createPrimaryKey(const std::string&);

        const std::string getStringForCreateTable(std::string&) const;
        const std::string getStringForInsert(std::string&) const;
        const std::string getStringForUpdate(std::string&, const int id) const;
        const std::string getStringForWhere() const;

    private:
        const std::string getColumnList() const;

    private:
        std::map<std::string, AnyProperty> _map;
    };
}

#endif /* ANYPROPERTYMAP_H_ */
