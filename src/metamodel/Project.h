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

#ifndef CONTAINER_H_
#include "Container.h"
#endif

#ifndef DIAGRAM_H_
#include "Diagram.h"
#endif

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
     * \class Project
     *
     *  
     */
    class Project : public Container<Diagram>//, public storage::ActiveRecord<Project>
    {
    public:

        /*!
         *  Project constructor.
         */
        Project();

        /*!
         * Project virtual destructor.
         */
        virtual ~Project();
	};
}

#endif /* PROJECT_H_ */
