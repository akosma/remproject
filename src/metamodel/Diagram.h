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

#include <map>
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

/*!
 * \namespace metamodel
 * Insert a description for the namespace here
 */
namespace metamodel
{
    class Project;
    class Element;

    /*!
     * \class Diagram
     *
     *  
     */
    class Diagram : public storage::ActiveRecord<Diagram>
                  , public storage::BelongsTo<Project>
                  , public storage::HasMany<Element>
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
