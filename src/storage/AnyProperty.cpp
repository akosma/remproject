/*!
 * \file AnyProperty.cpp
 *
 * Contains the implementation of the Storage::AnyProperty class.
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

/*!
 * \namespace Storage
 * Insert a description for the namespace here
 */
namespace Storage
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
    
    std::string AnyProperty::getString() const
    {
        return Poco::RefAnyCast<std::string>(this->getValue());
    }
    
    int AnyProperty::getInt() const
    {
        return Poco::RefAnyCast<int>(this->getValue());
    }
    
    double AnyProperty::getDouble() const
    {
        return Poco::RefAnyCast<double>(this->getValue());
    }
    
    bool AnyProperty::getBool() const
    {
        return Poco::RefAnyCast<bool>(this->getValue());
    }
}
