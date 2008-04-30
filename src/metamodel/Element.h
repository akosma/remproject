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

#ifndef ACTIVERECORD_H_
#include "../storage/ActiveRecord.h"
#endif

#ifndef BELONGSTO_H_
#include "../storage/BelongsTo.h"
#endif

#ifndef HASMANY_H_
#include "../storage/HasMany.h"
#endif

using namespace storage;

/*!
 * \namespace metamodel
 * Insert a description for the namespace here
 */
namespace metamodel
{
    class Diagram;

    /*!
     * \class Element
     *
     *  
     */
    class Element : public ActiveRecord<Element
                         , BelongsTo<Diagram> 
                         , HasMany<NoChildren, Element> >
    {
    public:

        /*!
         *  Element constructor.
         */
        Element(std::string&);

        Element(std::string&, storage::ID, AnyPropertyMap&);

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
