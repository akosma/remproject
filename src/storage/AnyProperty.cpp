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

/*!
 * \namespace storage
 * Insert a description for the namespace here
 */
namespace storage
{
    /*!
     * AnyProperty Constructor.
     */
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

    
    /*!
     * AnyProperty Virtual destructor.
     */
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
            output << "'";
            output << getString();
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
