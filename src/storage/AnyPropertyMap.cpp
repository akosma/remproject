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
#include <algorithm>

using storage::AnyProperty;
using Poco::DateTime;
using Poco::Any;
using std::string;
using std::stringstream;
using std::map;
using std::merge;

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

    template <>
    void AnyPropertyMap::set<AnyProperty>(const string& key, const AnyProperty& value)
    {
        _map[key] = value;
    }
    
    void AnyPropertyMap::merge(AnyPropertyMap& otherMap)
    {
        map<string, AnyProperty>::const_iterator it;
        for (it = otherMap._map.begin(); it != otherMap._map.end(); ++it)
        {
            const pair<string, AnyProperty>& p = (*it);
            set<AnyProperty>(p.first, p.second);
        }
    }
    
    void AnyPropertyMap::dump()
    {
        std::cout << "========================" << std::endl;
        std::cout << "AnyPropertyMap instance:" << std::endl;
        std::cout << joinMap(&AnyPropertyMap::getNameValuePair, "\n");
        std::cout << std::endl << std::endl;
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
        return joinMap(&AnyPropertyMap::getKey, ", ");
    }
    
    const string AnyPropertyMap::getStringForCreateTable(string& tableName) const
    {
        stringstream output;
        output << "CREATE TABLE ";
        output << tableName;
        output << "(\n";
        output << joinMap(&AnyPropertyMap::getSQLiteColumnDefinition, ",\n");
        output << ");";
        return output.str();
    }
    
    const string AnyPropertyMap::getStringForInsert(string& tableName) const
    {
        stringstream output;
        output << "INSERT INTO ";
        output << tableName;
        output << " (";
        output << this->getColumnList();
        output << ") VALUES (";
        output << joinMap(&AnyPropertyMap::getQuotedValue, ", ");
        output << ");";
        return output.str();
    }
    
    const string AnyPropertyMap::getStringForUpdate(string& tableName, const int id) const
    {
        stringstream output;
        output << "UPDATE ";
        output << tableName;
        output << " SET ";
        output << joinMap(&AnyPropertyMap::getNameValuePair, ", ");
        output << " WHERE id = ";
        output << id;
        output << ";";
        return output.str();
    }
    
    const string AnyPropertyMap::joinMap(AnyPropertyMap::Extractor e, const string& separator) const
    {
        stringstream output;
        map<string, AnyProperty>::const_iterator it;
        for (it = _map.begin(); it != _map.end(); ++it)
        {
            output << CALL_MEMBER_FN(*this, e)(*it);
            output << separator;
        }
        const int separatorLength = separator.length();
        string str = output.str();
        const int len = str.length();
        if (len > separatorLength)
        {
            str = str.substr(0, len - separatorLength);
        }
        return str;
    }
    
    const string AnyPropertyMap::getKey(const pair<string, AnyProperty>& p) const
    {
        return p.first;
    }
    
    const string AnyPropertyMap::getSQLiteColumnDefinition(const pair<string, AnyProperty>& p) const
    {
        return p.second.getSQLiteColumnDefinition();
    }
    
    const string AnyPropertyMap::getQuotedValue(const pair<string, AnyProperty>& p) const
    {
        return p.second.getQuotedValue();
    }
    
    const string AnyPropertyMap::getNameValuePair(const pair<string, AnyProperty>& p) const
    {
        return p.second.getNameValuePair();
    }
}
