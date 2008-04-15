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
        Element(std::string&);

        Element(std::string&, storage::ID, storage::AnyPropertyMap&);

        /*!
         *  Element virtual destructor.
         */
        virtual ~Element();
        
        static std::string& getTableName();
        
    private:
        void createSchemaStructure();
        
    };
}

#endif /* ELEMENT_H_ */
