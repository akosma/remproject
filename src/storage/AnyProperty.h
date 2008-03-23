/*!
 * \file AnyProperty.h
 *
 * Contains the interface of the Storage::AnyProperty class.
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
using Poco::Any;

#ifndef PROPERTY_H_
#include "Property.h"
#endif

/*!
 * \namespace Storage
 * Insert a description for the namespace here
 */
namespace Storage
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

        /*!
         *  AnyProperty virtual destructor.
         */
        virtual ~AnyProperty();
        
        const std::type_info& getType() const;
        
        void setString(const std::string&);
        void setInteger(const int);
        void setDouble(const double);
        void setBoolean(const bool);
        
        std::string getString() const;
        int getInteger() const;
        double getDouble() const;
        bool getBoolean() const;
    };
}

#endif /* ANYPROPERTY_H_ */
