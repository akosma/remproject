/*!  
 * \file Project.h
 * 
 * Contains the interface of the MetaModel::Project class.
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

/*!
 * \namespace MetaModel
 * Insert a description for the namespace here
 */
namespace MetaModel
{
    /*!
     * \class Project "$URL$"
     *
     *  
     */
    class Project : public Container<Diagram>
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
