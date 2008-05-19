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
#include "Property.h"
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
     * \class AnyProperty
     *
     *  
     */
    class AnyProperty : public Property<std::string, Poco::Any>
    {
    public:

        /*!
         *  AnyProperty constructor.
         */
        AnyProperty();
        AnyProperty(const std::string&);
        AnyProperty(const std::string&, const Poco::Any&);
        AnyProperty(const AnyProperty&);
        AnyProperty& operator =(const AnyProperty&);
        

        /*!
         *  AnyProperty virtual destructor.
         */
        virtual ~AnyProperty();

        const std::type_info& getType() const;

        void setString(const std::string&);
        void setInteger(const int);
        void setDouble(const double);
        void setBoolean(const bool);
        void setDateTime(const Poco::DateTime&);
        void setPrimaryKey();

        const std::string getString() const;
        const int getInteger() const;
        const double getDouble() const;
        const bool getBoolean() const;
        const Poco::DateTime getDateTime() const;

        const std::string getSQLiteColumnDefinition() const;
        const std::string getQuotedValue() const;
        const std::string getNameValuePair() const;
        
    private:
        bool _isPrimaryKey;
    };
}

#endif /* ANYPROPERTY_H_ */
