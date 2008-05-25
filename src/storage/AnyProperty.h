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

//! Contains the interface of the storage::AnyProperty class.
/*!
 * \file AnyProperty.h
 *
 * Contains the interface of the storage::AnyProperty class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/23/08
 */

#ifndef ANYPROPERTY_H_
#define ANYPROPERTY_H_

#include <string>
#include <typeinfo>

#include <Poco/Any.h>
#include <Poco/DateTime.h>

#ifndef PROPERTY_H_
#include "../utility/Property.h"
#endif

using utility::Property;
using Poco::Any;
using Poco::DateTime;

//! Framework for storing instances in SQLite files.
/*!
 * \namespace storage
 * Holds the classes used to store instances in SQLite files, allowing them
 * to be chained among them, using a simple syntax in class declarations.
 */
namespace storage
{
    //! Specialized Property with a name and an "Any" value.
    /*!
     * \class AnyProperty
     *
     * This class specializes the Property class, creating named instances
     * of the Any class (Poco namespace). The Any class is a derived version of the Boost
     * class of the same name, which can hold values of any type, preserving
     * their original types and avoiding the use of void* pointers. 
     * To avoid clients to handle the Any class, as well as having to
     * "manually" cast back to the original type, this class provides setters
     * and getters for the types stored in SQLite tables.
     * Whenever a client sets a property of a certain type, it must make sure
     * that it uses the corresponding getter; otherwise a runtime exception is
     * thrown to the caller.
     */
    class AnyProperty : public Property<std::string, Any>
    {
    public:

        //! Constructor.
        /*!
         *  Constructor. Creates a property without a name or a default value.
         */
        AnyProperty();
        
        //! Constructor.
        /*!
         * Constructor. Creates a property without a default value, but with a name.
         * 
         * \param name A name for the current property.
         */
        AnyProperty(const std::string&);

        //! Constructor.
        /*!
         * Constructor. Creates a property with a default name and value.
         * 
         * \param name A name for the current property.
         * \param value A value for the current property.
         */
        AnyProperty(const std::string&, const Any&);
        
        //! Copy constructor.
        /*!
         * Copy constructor.
         * 
         * \param rhs The property to copy state from.
         */
        AnyProperty(const AnyProperty&);
        
        //! Assignment operator.
        /*!
         * Assignment operator.
         * 
         * \param rhs The property to assign to.
         * 
         * \return A reference to the current property.
         */
        AnyProperty& operator =(const AnyProperty&);

        //! Virtual destructor.
        /*!
         *  Virtual destructor.
         */
        virtual ~AnyProperty();

        //! Returns the underlying type of the current instance.
        /*!
         * Returns a platform-specific information stating 
         * the underlying type of the current instance.
         * 
         * \return An std::type_info reference.
         */
        const std::type_info& getType() const;

        //! Sets a string value to the current instance.
        /*!
         * Sets a string value to the current instance. 
         * Any previous value is discarded.
         * 
         * \param input The new value for the property.
         */
        void setString(const std::string&);

        //! Sets an integer value to the current instance.
        /*!
         * Sets an integer value to the current instance. 
         * Any previous value is discarded.
         * 
         * \param input The new value for the property.
         */
        void setInteger(const int);

        //! Sets a double value to the current instance.
        /*!
         * Sets a double value to the current instance. 
         * Any previous value is discarded.
         * 
         * \param input The new value for the property.
         */
        void setDouble(const double);
        
        //! Sets a boolean value to the current instance.
        /*!
         * Sets a boolean value to the current instance. 
         * Any previous value is discarded.
         * 
         * \param input The new value for the property.
         */
        void setBoolean(const bool);

        //! Sets a DateTime value to the current instance.
        /*!
         * Sets a DateTime value to the current instance. 
         * Any previous value is discarded.
         * 
         * \param input The new value for the property.
         */
        void setDateTime(const DateTime&);

        //! Sets the current instance as "primary key".
        /*!
         * Sets the current instance as "primary key". This information
         * is used by AnyPropertyMap instances, when creating the statements
         * to create the table for a particular ActiveRecord class.
         */
        void setPrimaryKey();

        //! Returns the string value of the current instance.
        /*!
         * Returns the string value of the current instance.
         * 
         * \return The current string value.
         */
        const std::string getString() const;

        //! Returns the integer value of the current instance.
        /*!
         * Returns the integer value of the current instance.
         * 
         * \return The current integer value.
         */
        const int getInteger() const;

        //! Returns the double value of the current instance.
        /*!
         * Returns the double value of the current instance.
         * 
         * \return The current double value.
         */
        const double getDouble() const;

        //! Returns the boolean value of the current instance.
        /*!
         * Returns the boolean value of the current instance.
         * 
         * \return The current boolean value.
         */
        const bool getBoolean() const;
        
        //! Returns the DateTime value of the current instance.
        /*!
         * Returns the DateTime value of the current instance.
         * 
         * \return The current DateTime value.
         */
        const DateTime getDateTime() const;

        //! Returns the SQL statement that defines a SQLite column for this property.
        /*!
         * Returns the SQL statement that defines a SQLite column for this property.
         *
         * \return A string with a SQL statement.
         */
        const std::string getSQLiteColumnDefinition() const;
        
        //! Returns a string with the current value of this instance.
        /*!
         * Returns a string with the current value of this instance.
         * If the internal value held is a string, the value is 
         * surrounded by quotes, as required by SQL statements. This
         * method also takes care to avoid SQL injection problems.
         */
        const std::string getQuotedValue() const;
        
        //! Returns a string with both the name and the value of the current property.
        /*!
         * Returns a string with both the name and the value of the current property.
         * It uses the getQuotedValue() method to obtain a quoted string if the
         * internal value stored in the current instance is a string.
         * 
         * \return A string in the form "name = 'value'"
         */
        const std::string getNameValuePair() const;
        
    private:
        
        //! States whether the current property should be used as a primary key.
        bool _isPrimaryKey;
    };
}

#endif /* ANYPROPERTY_H_ */
