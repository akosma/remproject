/*!
 * \file Actor.cpp
 *
 * Contains the implementation of the metamodel::Actor class.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      3/16/08
 */

#include "Actor.h"

/*!
 * \namespace metamodel
 * Insert a description for the namespace here
 */
namespace metamodel
{
    /*!
     * Actor Constructor.
     */
    Actor::Actor(const std::string& name)
    : Element(name)
    {
    }
    
    /*!
     * Actor Virtual destructor.
     */
    Actor::~Actor()
    {
    }
}
