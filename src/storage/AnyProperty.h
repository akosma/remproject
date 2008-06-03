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
using Poco::RefAnyCast;
using Poco::Any;
using Poco::DateTime;
using std::string;
using std::type_info;

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
    class AnyProperty : public Property<string, Any>
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
        AnyProperty(const string&);

        //! Constructor.
        /*!
         * Constructor. Creates a property with a default name and value.
         * 
         * \param name A name for the current property.
         * \param value A value for the current property.
         */
        AnyProperty(const string&, const Any&);
        
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
         * \return An type_info reference.
         */
        const type_info& getType() const;

        //! Sets a value to the current instance.
        /*!
         * Sets a value to the current instance. 
         * Any previous value is discarded.
         * This function is inlined in the header 
         * file to avoid link problems.
         * 
         * \param input The new value for the property.
         */
        template <class T>
        void set(const T& input)
        {
            Any value(input);
            setValue(value);
        }

        //! Returns the value of the current instance.
        /*!
         * Returns the value of the current instance.
         * This function is inlined in the header 
         * file to avoid link problems.
         * 
         * \return The current string value.
         */
        template <class T>
        const T get() const
        {
            return RefAnyCast<T>(getValue());
        }

        //! Sets the current instance as "primary key".
        /*!
         * Sets the current instance as "primary key". This information
         * is used by AnyPropertyMap instances, when creating the statements
         * to create the table for a particular ActiveRecord class.
         */
        void setPrimaryKey();

        //! Returns the SQL statement that defines a SQLite column for this property.
        /*!
         * Returns the SQL statement that defines a SQLite column for this property.
         *
         * \return A string with a SQL statement.
         */
        const string getSQLiteColumnDefinition() const;
        
        //! Returns a string with the current value of this instance.
        /*!
         * Returns a string with the current value of this instance.
         * If the internal value held is a string, the value is 
         * surrounded by quotes, as required by SQL statements. This
         * method also takes care to avoid SQL injection problems.
         */
        const string getQuotedValue() const;
        
        //! Returns a string with both the name and the value of the current property.
        /*!
         * Returns a string with both the name and the value of the current property.
         * It uses the getQuotedValue() method to obtain a quoted string if the
         * internal value stored in the current instance is a string.
         * 
         * \return A string in the form "name = 'value'"
         */
        const string getNameValuePair() const;
        
    private:
        
        //! States whether the current property should be used as a primary key.
        bool _isPrimaryKey;
    };
}

#endif /* ANYPROPERTY_H_ */
