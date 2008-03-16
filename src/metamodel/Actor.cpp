/*!
 * \file Actor.cpp
 *
 * Contains the implementation of the MetaModel::Actor class.
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
 * \namespace MetaModel
 * Insert a description for the namespace here
 */
namespace MetaModel
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
