/*!  
 * \file Project.h
 * 
 * Contains the interface of the metamodel::Project class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      2008-03-16
 */

#ifndef PROJECT_H_
#define PROJECT_H_

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
     * \class Project
     *
     *  
     */
    class Project : public ActiveRecord<Project
                         , BelongsTo<NoParent>
                         , HasMany<Diagram, Project> >
    {
    public:

        /*!
         *  Project constructor.
         */
        Project();

        Project(std::string&, storage::ID, storage::AnyPropertyMap&);

        /*!
         * Project virtual destructor.
         */
        virtual ~Project();

        static std::string& getTableName();

    private:
        void createSchemaStructure();
    };
}

#endif /* PROJECT_H_ */
