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
    {
    }
    
    AnyProperty::AnyProperty(const std::string& name)
    : Property<std::string, Poco::Any>(name)
    {
    }

    AnyProperty::AnyProperty(const std::string& name, const Poco::Any& value)
    : Property<std::string, Poco::Any>(name, value)
    {
    }

    AnyProperty::AnyProperty(const AnyProperty& source)
    : Property<std::string, Poco::Any>(source)
    {
    }
    
    /*!
     * AnyProperty Virtual destructor.
     */
    AnyProperty::~AnyProperty()
    {
    }

    const std::type_info& AnyProperty::getType() const
    {
        return this->getValue().type();
    }
    
    void AnyProperty::setString(const std::string& input)
    {
        Poco::Any value(input);
        this->setValue(value);
    }

    void AnyProperty::setInteger(const int input)
    {
        Poco::Any value(input);
        this->setValue(value);
    }

    void AnyProperty::setDouble(const double input)
    {
        Poco::Any value(input);
        this->setValue(value);
    }
    
    void AnyProperty::setBoolean(const bool input)
    {
        Poco::Any value(input);
        this->setValue(value);
    }
    
    std::string AnyProperty::getString() const
    {
        return Poco::RefAnyCast<std::string>(this->getValue());
    }
    
    int AnyProperty::getInteger() const
    {
        return Poco::RefAnyCast<int>(this->getValue());
    }
    
    double AnyProperty::getDouble() const
    {
        return Poco::RefAnyCast<double>(this->getValue());
    }
    
    bool AnyProperty::getBoolean() const
    {
        return Poco::RefAnyCast<bool>(this->getValue());
    }
    
    const std::string AnyProperty::getQuotedValue() const
    {
        const std::type_info& type = this->getValue().type();
        std::stringstream output;
        if(type == typeid(std::string))
        {
            output << "'";
            output << this->getString();
            output << "'";
        }
        if(type == typeid(int))
        {
            output << this->getInteger();
        }
        if(type == typeid(bool))
        {
            output << this->getBoolean();
        }
        if(type == typeid(double))
        {
            output << this->getDouble();
        }
        return output.str();
    }
    
    const std::string AnyProperty::getNameValuePair() const
    {
        std::stringstream output;
        output << this->getName();
        output << " = ";
        output << this->getQuotedValue();
        return output.str();
    }
}
