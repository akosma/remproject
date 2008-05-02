/*!
 * \file AnyProperty.h
 *
 * Contains the interface of the storage::AnyProperty class.
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
#include <Poco/DateTime.h>

#ifndef PROPERTY_H_
#include "Property.h"
#endif

/*!
 * \namespace storage
 * Insert a description for the namespace here
 */
namespace storage
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
        AnyProperty& operator =(const AnyProperty&);
        

        /*!
         *  AnyProperty virtual destructor.
         */
        virtual ~AnyProperty();

        const std::type_info& getType() const;

        void setString(const std::string&);
        void setInteger(const int);
        void setDouble(const double);
        void setBoolean(const bool);
        void setDateTime(const Poco::DateTime&);
        void setPrimaryKey();

        const std::string getString() const;
        const int getInteger() const;
        const double getDouble() const;
        const bool getBoolean() const;
        const Poco::DateTime getDateTime() const;

        const std::string getSQLiteColumnDefinition() const;
        const std::string getQuotedValue() const;
        const std::string getNameValuePair() const;
        
    private:
        bool _isPrimaryKey;
    };
}

#endif /* ANYPROPERTY_H_ */
