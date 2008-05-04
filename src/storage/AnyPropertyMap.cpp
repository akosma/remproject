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
 * \file AnyPropertyMap.cpp
 *
 * Contains the implementation of the storage::AnyPropertyMap class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/23/08
 */

#include "AnyPropertyMap.h"
#include <Poco/Any.h>
#include <sstream>

/*!
 * \namespace storage
 * Holds the classes used to store instances in SQLite files, allowing them
 * to be chained among them, using a simple syntax in class declarations.
 */
namespace storage
{
    /*!
     * AnyPropertyMap Constructor.
     */
    AnyPropertyMap::AnyPropertyMap()
    : _map()
    {
    }

    /*!
     * AnyPropertyMap Virtual destructor.
     */
    AnyPropertyMap::~AnyPropertyMap()
    {
        _map.clear();
    }

    AnyPropertyMap::AnyPropertyMap(const AnyPropertyMap& source)
    : _map (source._map)
    {
    }

    AnyPropertyMap& AnyPropertyMap::operator=(const AnyPropertyMap& source)
    {
        if (this == &source)
        {
            return *this;
        }
        
        this->_map = source._map;
        return *this;
    }

    AnyProperty& AnyPropertyMap::operator[](const std::string& key)
    {
        return _map[key.c_str()];
    }

    const bool AnyPropertyMap::hasProperty(const std::string& key) const
    {
        std::map<std::string, storage::AnyProperty>::const_iterator it = _map.find(key);
        return (it != _map.end());
    }

    const bool AnyPropertyMap::isEmpty() const
    {
        return _map.empty();
    }
    
    const unsigned int AnyPropertyMap::count() const
    {
        return (unsigned int)_map.size();
    }

    void AnyPropertyMap::addStringProperty(const std::string& key)
    {
        if (!hasProperty(key))
        {
            setString(key, "");
        }
    }

    void AnyPropertyMap::addIntegerProperty(const std::string& key)
    {
        if (!hasProperty(key))
        {
            setInteger(key, 0);
        }
    }

    void AnyPropertyMap::addBooleanProperty(const std::string& key)
    {
        if (!hasProperty(key))
        {
            setBoolean(key, false);
        }
    }

    void AnyPropertyMap::addDoubleProperty(const std::string& key)
    {
        if (!hasProperty(key))
        {
            setDouble(key, 0.0);
        }
    }
    
    void AnyPropertyMap::addDateTimeProperty(const std::string& key)
    {
        if (!hasProperty(key))
        {
            Poco::DateTime now;
            setDateTime(key, now);
        }
    }
    
    void AnyPropertyMap::setString(const std::string& key, const std::string& value)
    {
        Poco::Any any(value);
        AnyProperty prop(key, any);
        _map[key] = prop;
    }

    void AnyPropertyMap::setInteger(const std::string& key, const int value)
    {
        Poco::Any any(value);
        AnyProperty prop(key, any);
        _map[key] = prop;
    }

    void AnyPropertyMap::setBoolean(const std::string& key, const bool value)
    {
        Poco::Any any(value);
        AnyProperty prop(key, any);
        _map[key] = prop;
    }

    void AnyPropertyMap::setDouble(const std::string& key, const double value)
    {
        Poco::Any any(value);
        AnyProperty prop(key, any);
        _map[key] = prop;
    }
    
    void AnyPropertyMap::setDateTime(const std::string& key, const Poco::DateTime& value)
    {
        Poco::Any any(value);
        AnyProperty prop(key, any);
        _map[key] = prop;
    }
    
    void AnyPropertyMap::createPrimaryKey(const std::string& key)
    {
        Poco::Any any(0);
        AnyProperty prop(key, any);
        prop.setPrimaryKey();
        _map[key] = prop;
    }
    
    const std::string AnyPropertyMap::getString(const std::string& key)
    {
        return _map[key].getString();
    }
    
    const int AnyPropertyMap::getInteger(const std::string& key)
    {
        return _map[key].getInteger();            
    }
    
    const bool AnyPropertyMap::getBoolean(const std::string& key)
    {
        return _map[key].getBoolean();            
    }
    
    const double AnyPropertyMap::getDouble(const std::string& key)
    {
        return _map[key].getDouble();            
    }
    
    const Poco::DateTime AnyPropertyMap::getDateTime(const std::string& key)
    {
        return _map[key].getDateTime();
    }
    
    const std::string AnyPropertyMap::getColumnList() const
    {
        std::stringstream output;
        std::map<std::string, storage::AnyProperty>::const_iterator it;
        for (it = _map.begin(); it != _map.end(); ++it)
        {
            output << it->first;
            output << ", ";
        }
        std::string str = output.str();
        int len = str.length();
        if (len > 2)
        {
            str = str.substr(0, len - 2);
        }
        return str;
    }
    
    const std::string AnyPropertyMap::getStringForCreateTable(std::string& tableName) const
    {
        std::stringstream output;
        std::map<std::string, storage::AnyProperty>::const_iterator it;
        output << "CREATE TABLE ";
        output << tableName;
        output << "(\n";
        for (it = _map.begin(); it != _map.end(); ++it)
        {
            output << (it->second.getSQLiteColumnDefinition());
            output << ",\n";
        }
        std::string str = output.str();
        int len = str.length();
        if (len > 2)
        {
            str = str.substr(0, len - 2);
        }
        std::stringstream output2;
        output2 << str;
        output2 << ");";
        return output2.str();
    }
    
    const std::string AnyPropertyMap::getStringForInsert(std::string& tableName) const
    {
        std::stringstream output;
        output << "INSERT INTO ";
        output << tableName;
        output << " (";
        output << this->getColumnList();
        output << ") VALUES (";
        std::map<std::string, storage::AnyProperty>::const_iterator it;
        for (it = _map.begin(); it != _map.end(); ++it)
        {
            output << (it->second.getQuotedValue());
            output << ", ";
        }
        std::string str = output.str();
        int len = str.length();
        if (len > 2)
        {
            str = str.substr(0, len - 2);
        }
        std::stringstream output2;
        output2 << str;
        output2 << ");";
        return output2.str();
    }
    
    const std::string AnyPropertyMap::getStringForUpdate(std::string& tableName, const int id) const
    {
        std::stringstream output;
        output << "UPDATE ";
        output << tableName;
        output << " SET ";
        std::map<std::string, storage::AnyProperty>::const_iterator it;
        for (it = _map.begin(); it != _map.end(); ++it)
        {
            output << (it->second.getNameValuePair());
            output << ", ";
        }
        std::string str = output.str();
        int len = str.length();
        if (len > 2)
        {
            str = str.substr(0, len - 2);
        }
        std::stringstream output2;
        output2 << str;
        output2 << " WHERE id = ";
        output2 << id;
        output2 << ";";
        return output2.str();
    }
    
    const std::string AnyPropertyMap::getStringForWhere() const
    {
        std::stringstream output;
        std::map<std::string, storage::AnyProperty>::const_iterator it;
        for (it = _map.begin(); it != _map.end(); ++it)
        {
            output << (it->second.getNameValuePair());
            output << " AND ";
        }
        std::string str = output.str();
        int len = str.length();
        if (len > 5)
        {
            str = str.substr(0, len - 5);
        }
        return str;
    }
}
