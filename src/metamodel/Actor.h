/*!
 * \file Actor.h
 *
 * Contains the interface of the MetaModel::Actor class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/16/08
 */

#ifndef ACTOR_H_
#define ACTOR_H_

#ifndef ELEMENT_H_
#include "Element.h"
#endif

#include <string>
#include <vector>

/*!
 * \namespace MetaModel
 * Insert a description for the namespace here
 */
namespace MetaModel
{
    /*!
     * \class Actor
     *
     *  
     */
    class Actor : public Element
    {
    public:

        /*!
         *  Actor constructor.
         */
        Actor(const std::string&);

        /*!
         *  Actor virtual destructor.
         */
        virtual ~Actor();
    };
}

#endif /* rem_Actor */
