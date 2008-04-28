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
 * Insert a description for the namespace here
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
    
    void AnyPropertyMap::setStringProperty(const std::string& key, const std::string& value)
    {
        Poco::Any any(value);
        AnyProperty prop(key, any);
        _map[key] = prop;
    }

    void AnyPropertyMap::setIntegerProperty(const std::string& key, const int value)
    {
        Poco::Any any(value);
        AnyProperty prop(key, any);
        _map[key] = prop;
    }

    void AnyPropertyMap::setBooleanProperty(const std::string& key, const bool value)
    {
        Poco::Any any(value);
        AnyProperty prop(key, any);
        _map[key] = prop;
    }

    void AnyPropertyMap::setDoubleProperty(const std::string& key, const double value)
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
    
    std::string AnyPropertyMap::getString(const std::string& key)
    {
        return _map[key].getString();
    }
    
    int AnyPropertyMap::getInteger(const std::string& key)
    {
        return _map[key].getInteger();            
    }
    
    bool AnyPropertyMap::getBoolean(const std::string& key)
    {
        return _map[key].getBoolean();            
    }
    
    double AnyPropertyMap::getDouble(const std::string& key)
    {
        return _map[key].getDouble();            
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
