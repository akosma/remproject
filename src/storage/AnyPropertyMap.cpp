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

//! Contains the implementation of the storage::AnyPropertyMap class.
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
#include <Poco/DateTime.h>
#include <sstream>

using storage::AnyProperty;
using Poco::DateTime;
using Poco::Any;
using std::string;
using std::stringstream;
using std::map;

namespace storage
{
    AnyPropertyMap::AnyPropertyMap()
    : _map()
    {
    }

    AnyPropertyMap::~AnyPropertyMap()
    {
        _map.clear();
    }

    AnyPropertyMap::AnyPropertyMap(const AnyPropertyMap& rhs)
    : _map (rhs._map)
    {
    }

    AnyPropertyMap& AnyPropertyMap::operator=(const AnyPropertyMap& rhs)
    {
        if (this != &rhs)
        {
            this->_map = rhs._map;
        }
        
        return *this;
    }

    AnyProperty& AnyPropertyMap::operator[](const string& key)
    {
        return _map[key.c_str()];
    }

    const bool AnyPropertyMap::hasProperty(const string& key) const
    {
        map<string, AnyProperty>::const_iterator it = _map.find(key);
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

    void AnyPropertyMap::createPrimaryKey(const string& key)
    {
        Any any(0);
        AnyProperty prop(key, any);
        prop.setPrimaryKey();
        _map[key] = prop;
    }
    
    const string AnyPropertyMap::getColumnList() const
    {
        stringstream output;
        map<string, AnyProperty>::const_iterator it;
        for (it = _map.begin(); it != _map.end(); ++it)
        {
            output << it->first;
            output << ", ";
        }
        string str = output.str();
        int len = str.length();
        if (len > 2)
        {
            str = str.substr(0, len - 2);
        }
        return str;
    }
    
    const string AnyPropertyMap::getStringForCreateTable(string& tableName) const
    {
        stringstream output;
        map<string, AnyProperty>::const_iterator it;
        output << "CREATE TABLE ";
        output << tableName;
        output << "(\n";
        for (it = _map.begin(); it != _map.end(); ++it)
        {
            output << (it->second.getSQLiteColumnDefinition());
            output << ",\n";
        }
        string str = output.str();
        int len = str.length();
        if (len > 2)
        {
            str = str.substr(0, len - 2);
        }
        stringstream output2;
        output2 << str;
        output2 << ");";
        return output2.str();
    }
    
    const string AnyPropertyMap::getStringForInsert(string& tableName) const
    {
        stringstream output;
        output << "INSERT INTO ";
        output << tableName;
        output << " (";
        output << this->getColumnList();
        output << ") VALUES (";
        map<string, AnyProperty>::const_iterator it;
        for (it = _map.begin(); it != _map.end(); ++it)
        {
            output << (it->second.getQuotedValue());
            output << ", ";
        }
        string str = output.str();
        int len = str.length();
        if (len > 2)
        {
            str = str.substr(0, len - 2);
        }
        stringstream output2;
        output2 << str;
        output2 << ");";
        return output2.str();
    }
    
    const string AnyPropertyMap::getStringForUpdate(string& tableName, const int id) const
    {
        stringstream output;
        output << "UPDATE ";
        output << tableName;
        output << " SET ";
        map<string, AnyProperty>::const_iterator it;
        for (it = _map.begin(); it != _map.end(); ++it)
        {
            output << (it->second.getNameValuePair());
            output << ", ";
        }
        string str = output.str();
        int len = str.length();
        if (len > 2)
        {
            str = str.substr(0, len - 2);
        }
        stringstream output2;
        output2 << str;
        output2 << " WHERE id = ";
        output2 << id;
        output2 << ";";
        return output2.str();
    }
    
    const string AnyPropertyMap::getStringForWhere() const
    {
        stringstream output;
        map<string, AnyProperty>::const_iterator it;
        for (it = _map.begin(); it != _map.end(); ++it)
        {
            output << (it->second.getNameValuePair());
            output << " AND ";
        }
        string str = output.str();
        int len = str.length();
        if (len > 5)
        {
            str = str.substr(0, len - 5);
        }
        return str;
    }
}
