/*!
 * \file Diagram.h
 *
 * Contains the interface of the metamodel::Diagram class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/16/08
 */

#ifndef DIAGRAM_H_
#define DIAGRAM_H_

#ifndef CONTAINER_H_
#include "Container.h"
#endif

#ifndef ELEMENT_H_
#include "Element.h"
#endif

#ifndef ACTIVERECORD_H_
#include "../storage/ActiveRecord.h"
#endif

#include <map>
#include <string>

/*!
 * \namespace metamodel
 * Insert a description for the namespace here
 */
namespace metamodel
{
    /*!
     * \class Diagram
     *
     *  
     */
    class Diagram : public Container<Element>, public storage::ActiveRecord<Diagram>
    {
    public:

        /*!
         *  Diagram constructor.
         */
        Diagram(std::string&);

        Diagram(std::string&, storage::ID, storage::AnyPropertyMap&);

        /*!
         *  Diagram virtual destructor.
         */
        virtual ~Diagram();

        static std::string& getTableName();

    private:
        void createSchemaStructure();
	};
}

#endif /* DIAGRAM_H_ */
