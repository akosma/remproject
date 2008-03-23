/*!
 * \file UseCaseDiagram.h
 *
 * Contains the interface of the metamodel::UseCaseDiagram class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/16/08
 */

#ifndef USECASEDIAGRAM_H_
#define USECASEDIAGRAM_H_

#ifndef DIAGRAM_H_
#include "Diagram.h"
#endif

#include <string>

/*!
 * \namespace metamodel
 * Insert a description for the namespace here
 */
namespace metamodel
{
    /*!
     * \class UseCaseDiagram
     *
     *  
     */
    class UseCaseDiagram : public Diagram
    {
    public:

        /*!
         *  UseCaseDiagram constructor.
         */
        UseCaseDiagram(const std::string&);

        /*!
         *  UseCaseDiagram virtual destructor.
         */
        virtual ~UseCaseDiagram();

    };
}

#endif /* USECASEDIAGRAM_H_ */
