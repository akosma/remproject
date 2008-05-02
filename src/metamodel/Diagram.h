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

#ifndef BELONGSTO_H_
#include "../storage/BelongsTo.h"
#endif

#ifndef HASMANY_H_
#include "../storage/HasMany.h"
#endif

#ifndef ACTIVERECORD_H_
#include "../storage/ActiveRecord.h"
#endif

using namespace storage;

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
    class Diagram : public ActiveRecord<Diagram
                         , BelongsTo<Project>
                         , HasMany<Element, Diagram> >
    {
    public:

        /*!
         *  Diagram constructor.
         */
        Diagram(std::string&);

        Diagram(std::string&, storage::ID, AnyPropertyMap&);

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
