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

//! Contains the implementation of the storage::AnyProperty class.
/*!
 * \file AnyProperty.cpp
 *
 * Contains the implementation of the storage::AnyProperty class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/23/08
 */

#include "AnyProperty.h"
#include <typeinfo>
#include <sstream>

#include <Poco/Any.h>
#include <Poco/String.h>
#include <Poco/DateTime.h>

using Poco::Any;
using Poco::DateTime;
using Poco::replace;
using std::string;
using std::type_info;
using std::stringstream;

namespace storage
{
    AnyProperty::AnyProperty()
    : Property<string, Any>()
    , _isPrimaryKey(false)
    {
    }
    
    AnyProperty::AnyProperty(const string& name)
    : Property<string, Any>(name)
    , _isPrimaryKey(false)
    {
    }

    AnyProperty::AnyProperty(const string& name, const Any& value)
    : Property<string, Any>(name, value)
    , _isPrimaryKey(false)
    {
    }

    AnyProperty::AnyProperty(const AnyProperty& rhs)
    : Property<string, Any>(rhs)
    , _isPrimaryKey(rhs._isPrimaryKey)
    {
    }
    
    AnyProperty& AnyProperty::operator =(const AnyProperty& rhs)
    {
        if (this != &rhs)
        {
            Property<string, Any>::operator=(rhs);
            _isPrimaryKey = rhs._isPrimaryKey;
        }

        return *this;
    }

    AnyProperty::~AnyProperty()
    {
    }

    const type_info& AnyProperty::getType() const
    {
        return getValue().type();
    }
    
    void AnyProperty::setPrimaryKey()
    {
        _isPrimaryKey = true;
    }

    const string AnyProperty::getSQLiteColumnDefinition() const
    {
        const type_info& type = getValue().type();
        stringstream output;
        output << getName();
        output << " ";
        if(type == typeid(string))
        {
            output << "TEXT";
        }
        if(type == typeid(int))
        {
            output << "INTEGER";
            if (_isPrimaryKey)
            {
                output << " PRIMARY KEY";
            }
        }
        if(type == typeid(bool))
        {
            output << "BOOLEAN";
        }
        if(type == typeid(double))
        {
            output << "REAL";
        }
        if(type == typeid(DateTime))
        {
            output << "DATETIME";
        }
        return output.str();
    }
    
    const string AnyProperty::getQuotedValue() const
    {
        const type_info& type = getValue().type();
        stringstream output;
        if(type == typeid(string))
        {
            // This prevents SQL-injection attacks or corruptions on the file.
            string doubleQuote("'");
            string singleQuote("''");
            output << "'";
            output << replace<string>(get<string>(), doubleQuote, singleQuote);
            output << "'";
        }
        if(type == typeid(int))
        {
            output << get<int>();
        }
        if(type == typeid(bool))
        {
            output << get<bool>();
        }
        if(type == typeid(double))
        {
            output << get<double>();
        }
        if(type == typeid(DateTime))
        {
            output << get<DateTime>().utcTime();
        }
        return output.str();
    }
    
    const string AnyProperty::getNameValuePair() const
    {
        stringstream output;
        output << getName();
        output << " = ";
        output << getQuotedValue();
        return output.str();
    }
}
