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

#include <Poco/String.h>

namespace storage
{
    AnyProperty::AnyProperty()
    : Property<std::string, Poco::Any>()
    , _isPrimaryKey(false)
    {
    }
    
    AnyProperty::AnyProperty(const std::string& name)
    : Property<std::string, Poco::Any>(name)
    , _isPrimaryKey(false)
    {
    }

    AnyProperty::AnyProperty(const std::string& name, const Poco::Any& value)
    : Property<std::string, Poco::Any>(name, value)
    , _isPrimaryKey(false)
    {
    }

    AnyProperty::AnyProperty(const AnyProperty& source)
    : Property<std::string, Poco::Any>(source)
    , _isPrimaryKey(source._isPrimaryKey)
    {
    }
    
    AnyProperty& AnyProperty::operator =(const AnyProperty& source)
    {
        if (this == &source)
        {
            return *this;
        }

        Property<std::string, Poco::Any>::operator=(source);
        _isPrimaryKey = source._isPrimaryKey;

        return *this;
    }

    AnyProperty::~AnyProperty()
    {
    }

    const std::type_info& AnyProperty::getType() const
    {
        return getValue().type();
    }
    
    void AnyProperty::setString(const std::string& input)
    {
        Poco::Any value(input);
        setValue(value);
    }

    void AnyProperty::setInteger(const int input)
    {
        Poco::Any value(input);
        setValue(value);
    }

    void AnyProperty::setDouble(const double input)
    {
        Poco::Any value(input);
        setValue(value);
    }
    
    void AnyProperty::setBoolean(const bool input)
    {
        Poco::Any value(input);
        setValue(value);
    }
    
    void AnyProperty::setDateTime(const Poco::DateTime& input)
    {
        Poco::Any value(input);
        setValue(value);
    }
    
    void AnyProperty::setPrimaryKey()
    {
        _isPrimaryKey = true;
    }
    
    const std::string AnyProperty::getString() const
    {
        return Poco::RefAnyCast<std::string>(getValue());
    }
    
    const int AnyProperty::getInteger() const
    {
        return Poco::RefAnyCast<int>(getValue());
    }
    
    const double AnyProperty::getDouble() const
    {
        return Poco::RefAnyCast<double>(getValue());
    }
    
    const bool AnyProperty::getBoolean() const
    {
        return Poco::RefAnyCast<bool>(getValue());
    }
    
    const Poco::DateTime AnyProperty::getDateTime() const
    {
        return Poco::RefAnyCast<Poco::DateTime>(getValue());
    }
    
    const std::string AnyProperty::getSQLiteColumnDefinition() const
    {
        const std::type_info& type = getValue().type();
        std::stringstream output;
        output << getName();
        output << " ";
        if(type == typeid(std::string))
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
        if(type == typeid(Poco::DateTime))
        {
            output << "DATETIME";
        }
        return output.str();
    }
    
    const std::string AnyProperty::getQuotedValue() const
    {
        const std::type_info& type = getValue().type();
        std::stringstream output;
        if(type == typeid(std::string))
        {
            // This prevents SQL-injection attacks or corruptions on the file.
            std::string doubleQuote("'");
            std::string singleQuote("''");
            output << "'";
            output << Poco::replace<std::string>(getString(), doubleQuote, singleQuote);
            output << "'";
        }
        if(type == typeid(int))
        {
            output << getInteger();
        }
        if(type == typeid(bool))
        {
            output << getBoolean();
        }
        if(type == typeid(double))
        {
            output << getDouble();
        }
        if(type == typeid(Poco::DateTime))
        {
            output << getDateTime().utcTime();
        }
        return output.str();
    }
    
    const std::string AnyProperty::getNameValuePair() const
    {
        std::stringstream output;
        output << getName();
        output << " = ";
        output << getQuotedValue();
        return output.str();
    }
}
