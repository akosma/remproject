/*!
 * \file AnyPropertyMap.h
 *
 * Contains the interface of the storage::AnyPropertyMap class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/23/08
 */

#ifndef ANYPROPERTYMAP_H_
#define ANYPROPERTYMAP_H_

#include <string>
#include <map>

#ifndef ANYPROPERTY_H_
#include "AnyProperty.h"
#endif

/*!
 * \namespace storage
 * Insert a description for the namespace here
 */
namespace storage
{
    /*!
     * \class AnyPropertyMap
     *
     *  
     */
    class AnyPropertyMap
    {
    public:

        /*!
         *  AnyPropertyMap constructor.
         */
        AnyPropertyMap();

        /*!
         *  AnyPropertyMap virtual destructor.
         */
        virtual ~AnyPropertyMap();
        
        AnyProperty& operator[](const std::string&);
        const bool hasProperty(const std::string&) const;
        const bool isEmpty() const;
        const unsigned int count() const;
        
        void setStringProperty(const std::string&, const std::string&);
        void setIntegerProperty(const std::string&, const int);
        void setBooleanProperty(const std::string&, const bool);
        void setDoubleProperty(const std::string&, const double);
        
        std::string getString(const std::string&);
        int getInteger(const std::string&);
        bool getBoolean(const std::string&);
        double getDouble(const std::string&);

        const std::string getStringForCreateTable(std::string&) const;
        const std::string getColumnList() const;
        const std::string getStringForSelect(std::string&) const;
        const std::string getStringForSelect(std::string&, const int id) const;
        const std::string getStringForInsert(std::string&) const;
        const std::string getStringForUpdate(std::string&, const int id) const;

    protected:

    private:
        std::map<std::string, AnyProperty> _map;
    };
}

#endif /* ANYPROPERTYMAP_H_ */
