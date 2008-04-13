/*!
 * \file Element.h
 *
 * Contains the interface of the metamodel::Element class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/16/08
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <string>
#include <map>

#ifndef ACTIVERECORD_H_
#include "../storage/ActiveRecord.h"
#endif

/*!
 * \namespace metamodel
 * Insert a description for the namespace here
 */
namespace metamodel
{
    /*!
     * \class Element
     *
     *  
     */
    class Element : public storage::ActiveRecord<Element>
    {
    public:

        /*!
         *  Element constructor.
         */
        Element(std::string);

        /*!
         *  Element virtual destructor.
         */
        virtual ~Element();
        
        void setName(std::string&);
        std::string getName();
        
        virtual void createAllPropertiesForSchema();
        
        static std::string& getTableName();
    };
}

#endif /* ELEMENT_H_ */
